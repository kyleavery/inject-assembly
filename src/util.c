#include "common.h"

D_SEC( E ) PVOID PebGetModule( _In_ ULONG Hash )
{
    PPEB                    Peb = NULL;
    PLIST_ENTRY             Hdr = NULL;
    PLIST_ENTRY             Ent = NULL;
    PLDR_DATA_TABLE_ENTRY   Ldr = NULL;

    Peb = NtCurrentPeb();
    Hdr = & Peb->Ldr->InLoadOrderModuleList;
    Ent = Hdr->Flink;

    for ( ; Hdr != Ent ; Ent = Ent->Flink ) {
        Ldr = C_PTR( Ent );
        if ( HashString( Ldr->BaseDllName.Buffer, Ldr->BaseDllName.Length ) == Hash )
        {
            return Ldr->DllBase;
        };
    };
    return NULL;
};

D_SEC( E ) PVOID PeGetFuncEat( _In_ PVOID Image, _In_ ULONG Hash ) 
{
    ULONG                       Idx = 0;
    PUINT16                     Aoo = NULL;
    PUINT32                     Aof = NULL;
    PUINT32                     Aon = NULL;
    PIMAGE_DOS_HEADER           Hdr = NULL;
    PIMAGE_NT_HEADERS           Nth = NULL;
    PIMAGE_DATA_DIRECTORY       Dir = NULL;
    PIMAGE_EXPORT_DIRECTORY     Exp = NULL;

    Hdr = C_PTR( Image );
    Nth = C_PTR( U_PTR( Hdr ) + Hdr->e_lfanew );
    Dir = & Nth->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ];

    if ( Dir->VirtualAddress )
    {
        Exp = C_PTR( U_PTR( Hdr ) + Dir->VirtualAddress );
        Aon = C_PTR( U_PTR( Hdr ) + Exp->AddressOfNames );
        Aof = C_PTR( U_PTR( Hdr ) + Exp->AddressOfFunctions );
        Aoo = C_PTR( U_PTR( Hdr ) + Exp->AddressOfNameOrdinals );

        for ( Idx = 0 ; Idx < Exp->NumberOfNames ; ++Idx )
        {
            if ( HashString( C_PTR( U_PTR( Hdr ) + Aon[ Idx ] ), 0 ) == Hash )
            {
                return C_PTR( U_PTR( Hdr ) + Aof[ Aoo[ Idx ] ] );
            };
        };
    };
    return NULL;
};


D_SEC( E ) UINT32 HashString( _In_ PVOID Buffer, _In_opt_ ULONG Length ) 
{
    UCHAR    Cur = 0;
    ULONG    Djb = 0;
    PUCHAR   Ptr = NULL;

    Djb = 5381;
    Ptr = C_PTR( Buffer );

    while ( TRUE ) {
        Cur = * Ptr;

        if ( ! Length )
        {
            if ( ! * Ptr )
            {
                break;
            };
        }
        else
        {
            if ( ( ULONG )( Ptr - ( PUCHAR ) Buffer ) >= Length )
            {
                break;
            };
            if ( ! * Ptr )
            {
                ++Ptr; continue;
            };
        };
        if ( Cur >= 'a' )
        {
            Cur -= 0x20;
        };

        /* Hash the character */
        Djb = ( ( Djb << 5 ) + Djb ) + Cur; ++Ptr;
    };
    return Djb;
};

D_SEC( E ) INT custatoi( _In_ PCHAR String1 )
{
    int res = 0;
    for ( int i = 0; String1[i] != '\0'; ++i )
    {
        res = res * 10 + String1[i] - '0';
    };
    return res;
};

// https://github.com/vxunderground/VX-API/blob/main/StringsAndData/CopyMemory.c
D_SEC( E ) VOID cpymem( _In_ const PVOID Destination, _In_ const PVOID Source, _In_ SIZE_T Length )
{
    PBYTE D = ( PBYTE ) Destination;
    PBYTE S = ( PBYTE ) Source;

    while ( Length-- )
    {
        *D++ = *S++;
    };
};

// https://github.com/vxunderground/VX-API/blob/main/StringsAndData/StringCompare/StringCompareA.c
D_SEC( E ) INT cmpstr( _In_ LPCSTR String1, _In_ LPCSTR String2 )
{
	for ( ; *String1 == *String2; String1++, String2++ )
	{
		if ( *String1 == '\0' )
        {
			return 0;
        };
	};
	return ( ( *( LPCSTR )String1 < *( LPCSTR )String2 ) ? -1 : +1 );
};

// https://doxygen.reactos.org/d0/d25/host_2wine_2unicode_8h.html#a9502b96564e16c6784bdef6bb203060d
D_SEC( E ) SIZE_T strlenw( _In_ PCWSTR String1 )
{
    PCWSTR String2 = String1;
    while( *String2 ) String2++;
    return ( unsigned int )(String2 - String1);
};

// https://doxygen.reactos.org/de/db9/rosapps_2applications_2winfile_2splitpath_8c.html#a724226c6f4fbdc7efbe2b3306b0e6b76
D_SEC( E ) VOID splitpathw( _In_ PWCHAR Path, _In_ PWCHAR Name )	
{
    PCWSTR end;
    PCWSTR p;
    PCWSTR s;
 
    end = Path + strlenw( Path );
 
    for( p = end; p > Path && *--p != '\\' && *p != '/'; )
        if (*p == '\0') {
            end = p;
            break;
        };

    for(p = end; p > Path; )
        if (*--p == '\\' || *p == '/') {
            p++;
            break;
        };

    for( s = p; s < end; )
        *Name++ = *s++;
    *Name = '\0';
};