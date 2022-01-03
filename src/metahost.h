#pragma warning( disable: 4049 )  

#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif 

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif 

#ifndef __metahost_h__
#define __metahost_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

 

#ifndef __ICLRRuntimeInfo_FWD_DEFINED__
#define __ICLRRuntimeInfo_FWD_DEFINED__
typedef interface ICLRRuntimeInfo ICLRRuntimeInfo;

#endif 	

#ifndef __ICLRMetaHost_FWD_DEFINED__
#define __ICLRMetaHost_FWD_DEFINED__
typedef interface ICLRMetaHost ICLRMetaHost;

#endif 	

#include "unknwn.h"
#include "oaidl.h"
#include "ocidl.h"
#include "mscoree.h"

 

#ifdef WINE_NO_UNICODE_MACROS
#undef LoadLibrary
#endif

extern RPC_IF_HANDLE __MIDL_itf_metahost_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_metahost_0000_0000_v0_0_s_ifspec;

#ifndef __ICLRRuntimeInfo_INTERFACE_DEFINED__
#define __ICLRRuntimeInfo_INTERFACE_DEFINED__

 

EXTERN_C const IID IID_ICLRRuntimeInfo;

typedef struct ICLRRuntimeInfoVtbl
{
    BEGIN_INTERFACE

    HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
        ICLRRuntimeInfo * This,
         REFIID riid,
         
        _COM_Outptr_  void **ppvObject);

    ULONG ( STDMETHODCALLTYPE *AddRef )( 
        ICLRRuntimeInfo * This);

    ULONG ( STDMETHODCALLTYPE *Release )( 
        ICLRRuntimeInfo * This);

    HRESULT ( STDMETHODCALLTYPE *GetVersionString )( 
        ICLRRuntimeInfo * This,
         LPWSTR pwzBuffer,
         DWORD *pcchBuffer);

    HRESULT ( STDMETHODCALLTYPE *GetRuntimeDirectory )( 
        ICLRRuntimeInfo * This,
         LPWSTR pwzBuffer,
         DWORD *pcchBuffer);

    HRESULT ( STDMETHODCALLTYPE *IsLoaded )( 
        ICLRRuntimeInfo * This,
         HANDLE hndProcess,
         BOOL *pbLoaded);

    HRESULT ( STDMETHODCALLTYPE *LoadErrorString )( 
        ICLRRuntimeInfo * This,
         UINT iResourceID,
         LPWSTR pwzBuffer,
         DWORD *pcchBuffer,
         LONG iLocaleid);

    HRESULT ( STDMETHODCALLTYPE *LoadLibrary )( 
        ICLRRuntimeInfo * This,
         LPCWSTR pwzDllName,
         HMODULE *phndModule);

    HRESULT ( STDMETHODCALLTYPE *GetProcAddress )( 
        ICLRRuntimeInfo * This,
         LPCSTR pszProcName,
         LPVOID *ppProc);

    HRESULT ( STDMETHODCALLTYPE *GetInterface )( 
        ICLRRuntimeInfo * This,
         REFCLSID rclsid,
         REFIID riid,
         LPVOID *ppUnk);

    HRESULT ( STDMETHODCALLTYPE *IsLoadable )( 
        ICLRRuntimeInfo * This,
         BOOL *pbLoadable);

    HRESULT ( STDMETHODCALLTYPE *SetDefaultStartupFlags )( 
        ICLRRuntimeInfo * This,
         DWORD dwStartupFlags,
         LPCWSTR pwzHostConfigFile);

    HRESULT ( STDMETHODCALLTYPE *GetDefaultStartupFlags )( 
        ICLRRuntimeInfo * This,
         DWORD *pdwStartupFlags,
         LPWSTR pwzHostConfigFile,
         DWORD *pcchHostConfigFile);

    HRESULT ( STDMETHODCALLTYPE *BindAsLegacyV2Runtime )( 
        ICLRRuntimeInfo * This);

    HRESULT ( STDMETHODCALLTYPE *IsStarted )( 
        ICLRRuntimeInfo * This,
         BOOL *pbStarted,
         DWORD *pdwStartupFlags);

    END_INTERFACE
} ICLRRuntimeInfoVtbl;

interface ICLRRuntimeInfo
{
    CONST_VTBL struct ICLRRuntimeInfoVtbl *lpVtbl;
};

#endif 	

 

typedef HRESULT ( __stdcall *CallbackThreadSetFnPtr )( void);

typedef HRESULT ( __stdcall *CallbackThreadUnsetFnPtr )( void);

typedef void ( __stdcall *RuntimeLoadedCallbackFnPtr )( 
    ICLRRuntimeInfo *pRuntimeInfo,
    CallbackThreadSetFnPtr pfnCallbackThreadSet,
    CallbackThreadUnsetFnPtr pfnCallbackThreadUnset);

DEFINE_GUID(CLSID_CLRDebuggingLegacy, 0xDF8395B5,0xA4BA,0x450b,0xA7,0x7C,0xA9,0xA4,0x77,0x62,0xC5,0x20);
DEFINE_GUID(CLSID_CLRMetaHost, 0x9280188d,0x0e8e,0x4867,0xb3,0x0c,0x7f,0xa8,0x38,0x84,0xe8,0xde);

extern RPC_IF_HANDLE __MIDL_itf_metahost_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_metahost_0000_0001_v0_0_s_ifspec;

#ifndef __ICLRMetaHost_INTERFACE_DEFINED__
#define __ICLRMetaHost_INTERFACE_DEFINED__

 

EXTERN_C const IID IID_ICLRMetaHost;

typedef struct ICLRMetaHostVtbl
{
    BEGIN_INTERFACE

    HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
        ICLRMetaHost * This,
         REFIID riid,
         
        _COM_Outptr_  void **ppvObject);

    ULONG ( STDMETHODCALLTYPE *AddRef )( 
        ICLRMetaHost * This);

    ULONG ( STDMETHODCALLTYPE *Release )( 
        ICLRMetaHost * This);

    HRESULT ( STDMETHODCALLTYPE *GetRuntime )( 
        ICLRMetaHost * This,
         LPCWSTR pwzVersion,
         REFIID iid,
         LPVOID *ppRuntime);

    HRESULT ( STDMETHODCALLTYPE *GetVersionFromFile )( 
        ICLRMetaHost * This,
         LPCWSTR pwzFilePath,
         LPWSTR pwzBuffer,
         DWORD *pcchBuffer);

    HRESULT ( STDMETHODCALLTYPE *EnumerateInstalledRuntimes )( 
        ICLRMetaHost * This,
         IEnumUnknown **ppEnumerator);

    HRESULT ( STDMETHODCALLTYPE *EnumerateLoadedRuntimes )( 
        ICLRMetaHost * This,
         HANDLE hndProcess,
         IEnumUnknown **ppEnumerator);

    HRESULT ( STDMETHODCALLTYPE *RequestRuntimeLoadedNotification )( 
        ICLRMetaHost * This,
         RuntimeLoadedCallbackFnPtr pCallbackFunction);

    HRESULT ( STDMETHODCALLTYPE *QueryLegacyV2RuntimeBinding )( 
        ICLRMetaHost * This,
         REFIID riid,
         LPVOID *ppUnk);

    HRESULT ( STDMETHODCALLTYPE *ExitProcess )( 
        ICLRMetaHost * This,
         INT32 iExitCode);

    END_INTERFACE
} ICLRMetaHostVtbl;

interface ICLRMetaHost
{
    CONST_VTBL struct ICLRMetaHostVtbl *lpVtbl;
};

#endif 	

 

HRESULT WINAPI CLRCreateInstance(REFCLSID clsid, REFIID riid, LPVOID *ppInterface);

extern RPC_IF_HANDLE __MIDL_itf_metahost_0000_0002_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_metahost_0000_0002_v0_0_s_ifspec;

#ifdef __cplusplus
}
#endif

#endif

