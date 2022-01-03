#pragma once

#define D_API( x )              __typeof__( x ) * x
#define D_SEC( x )              __attribute__(( section( ".text$" #x "" ) ))
#define C_PTR( x )              ( ( PVOID ) x )
#define U_PTR( x )              ( ( ULONG_PTR ) x )
#define ASIZE( x )              ( sizeof( x ) - 1 )
#define G_END( x )              ( ULONG_PTR )( GetIp() + 11 )
#define G_PTR( x )              ( ULONG_PTR )( GetIp() - ( ( ULONG_PTR ) & GetIp - ( ULONG_PTR ) x ) )

#define ADATA_SIZE( x )         ( sizeof( x ) - 1 )
#define NT_SUCCESS( x )         ( ( NTSTATUS ) ( x ) >= 0 )

#define NtCurrentProcess()      ( ( HANDLE ) (LONG_PTR ) -1 )
#define NtCurrentThread()       ( ( HANDLE )( LONG_PTR ) -2 )
