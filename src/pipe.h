#pragma once

D_SEC( E ) HANDLE PipeInit( _In_ PAPI Api, _In_ PCHAR Name );
D_SEC( E ) BOOL PipeWait( _In_ PAPI Api, _In_ HANDLE Pipe );
D_SEC( E ) BOOL PipePrint( _In_ PAPI Api, _In_ HANDLE Pipe, _In_ PCHAR Format, ... );