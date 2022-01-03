#pragma once

D_SEC( E ) PVOID PebGetModule( _In_ ULONG Hash );
D_SEC( E ) PVOID PeGetFuncEat( _In_ PVOID Image, _In_ ULONG Hash );
D_SEC( E ) UINT32 HashString( _In_ PVOID Buffer, _In_opt_ ULONG Length );
D_SEC( E ) INT custatoi( _In_ PCHAR String1 );
D_SEC( E ) VOID cpymem( _In_ const PVOID Destination, _In_ const PVOID Source, _In_ SIZE_T Length );
D_SEC( E ) INT cmpstr( _In_ LPCSTR String1, _In_ LPCSTR String2 );
D_SEC( E ) VOID splitpathw( _In_ PWCHAR Path, _In_ PWCHAR Name );