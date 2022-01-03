#pragma once

typedef struct
{
    D_API( AllocConsole );
    D_API( CLRCreateInstance );
    D_API( CommandLineToArgvW );
    D_API( ConnectNamedPipe );
    D_API( CreateNamedPipeA );
    D_API( FreeConsole );
    D_API( GetConsoleWindow );
    D_API( GetStdHandle );
    D_API( GetSystemInfo );
    D_API( LdrLoadDll );
    D_API( LdrUnloadDll );
    D_API( MultiByteToWideChar );
    D_API( NtClose );
    D_API( NtProtectVirtualMemory );
    D_API( NtQueryVirtualMemory );
    D_API( OpenProcess );
    D_API( RtlAllocateHeap );
    D_API( RtlFreeHeap );
    D_API( RtlInitUnicodeString );
    D_API( SafeArrayAccessData );
    D_API( SafeArrayCreate );
    D_API( SafeArrayCreateVector );
    D_API( SafeArrayDestroy );
    D_API( SafeArrayGetLBound );
    D_API( SafeArrayGetUBound );
    D_API( SafeArrayPutElement );
    D_API( SafeArrayUnaccessData );
    D_API( SetStdHandle );
    D_API( ShowWindow );
    D_API( SysAllocString );
    D_API( SysFreeString );
    D_API( VirtualAlloc );
    D_API( VirtualFree );
    D_API( WaitForSingleObject );
    D_API( WriteFile );
    D_API( vsnprintf );

} API, *PAPI;
