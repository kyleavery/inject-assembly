#ifdef _WIN32
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif
#include <rpc.h>
#include <rpcndr.h>
#endif

#ifndef COM_NO_WINDOWS_H
#include <windows.h>
#include <ole2.h>
#endif

#ifndef __mscoree_h__
#define __mscoree_h__

#ifndef __IGCThreadControl_FWD_DEFINED__
#define __IGCThreadControl_FWD_DEFINED__
typedef interface IGCThreadControl IGCThreadControl;
#ifdef __cplusplus
interface IGCThreadControl;
#endif 
#endif

#ifndef __IGCHostControl_FWD_DEFINED__
#define __IGCHostControl_FWD_DEFINED__
typedef interface IGCHostControl IGCHostControl;
#ifdef __cplusplus
interface IGCHostControl;
#endif 
#endif

#ifndef __IDebuggerThreadControl_FWD_DEFINED__
#define __IDebuggerThreadControl_FWD_DEFINED__
typedef interface IDebuggerThreadControl IDebuggerThreadControl;
#ifdef __cplusplus
interface IDebuggerThreadControl;
#endif 
#endif

#ifndef __ICorConfiguration_FWD_DEFINED__
#define __ICorConfiguration_FWD_DEFINED__
typedef interface ICorConfiguration ICorConfiguration;
#ifdef __cplusplus
interface ICorConfiguration;
#endif 
#endif

#ifndef __ICLRControl_FWD_DEFINED__
#define __ICLRControl_FWD_DEFINED__
typedef interface ICLRControl ICLRControl;
#ifdef __cplusplus
interface ICLRControl;
#endif 
#endif

#ifndef __IHostControl_FWD_DEFINED__
#define __IHostControl_FWD_DEFINED__
typedef interface IHostControl IHostControl;
#ifdef __cplusplus
interface IHostControl;
#endif 
#endif

#ifndef __ICorRuntimeHost_FWD_DEFINED__
#define __ICorRuntimeHost_FWD_DEFINED__
typedef interface ICorRuntimeHost ICorRuntimeHost;
#ifdef __cplusplus
interface ICorRuntimeHost;
#endif 
#endif

#ifndef __ICLRRuntimeHost_FWD_DEFINED__
#define __ICLRRuntimeHost_FWD_DEFINED__
typedef interface ICLRRuntimeHost ICLRRuntimeHost;
#ifdef __cplusplus
interface ICLRRuntimeHost;
#endif 
#endif

#ifndef __IManagedObject_FWD_DEFINED__
#define __IManagedObject_FWD_DEFINED__
typedef interface IManagedObject IManagedObject;
#ifdef __cplusplus
interface IManagedObject;
#endif 
#endif

#include <unknwn.h>

HRESULT     WINAPI CorBindToRuntimeHost(LPCWSTR,LPCWSTR,LPCWSTR,VOID*,DWORD,REFCLSID,REFIID,LPVOID*);
void        WINAPI CorExitProcess(int);
HRESULT     WINAPI GetCORSystemDirectory(LPWSTR,DWORD,DWORD*);
HRESULT     WINAPI GetCORVersion(LPWSTR,DWORD,DWORD*);
HRESULT     WINAPI GetRequestedRuntimeInfo(LPCWSTR,LPCWSTR,LPCWSTR,DWORD,DWORD,LPWSTR,DWORD,DWORD*,LPWSTR,DWORD,DWORD*);
HRESULT     WINAPI LoadLibraryShim(LPCWSTR,LPCWSTR,LPVOID,HMODULE*);
#ifdef WINE_STRICT_PROTOTYPES
typedef HRESULT (__stdcall *FLockClrVersionCallback)(void);
#else
typedef HRESULT (__stdcall *FLockClrVersionCallback)();
#endif
HRESULT     WINAPI LockClrVersion(FLockClrVersionCallback,FLockClrVersionCallback*,FLockClrVersionCallback*);
typedef void *HDOMAINENUM;
typedef enum RUNTIME_INFO_FLAGS {
    RUNTIME_INFO_UPGRADE_VERSION = 0x1,
    RUNTIME_INFO_REQUEST_IA64 = 0x2,
    RUNTIME_INFO_REQUEST_AMD64 = 0x4,
    RUNTIME_INFO_REQUEST_X86 = 0x8,
    RUNTIME_INFO_DONT_RETURN_DIRECTORY = 0x10,
    RUNTIME_INFO_DONT_RETURN_VERSION = 0x20,
    RUNTIME_INFO_DONT_SHOW_ERROR_DIALOG = 0x40
} RUNTIME_INFO_FLAGS;
typedef HRESULT (__stdcall *FExecuteInAppDomainCallback)(void *cookie);
/*****************************************************************************
 * IGCThreadControl interface
 */
#ifndef __IGCThreadControl_INTERFACE_DEFINED__
#define __IGCThreadControl_INTERFACE_DEFINED__

DEFINE_GUID(IID_IGCThreadControl, 0xf31d1788, 0xc397, 0x4725, 0x87,0xa5, 0x6a,0xf3,0x47,0x2c,0x27,0x91);

typedef struct IGCThreadControlVtbl {
    BEGIN_INTERFACE

    
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IGCThreadControl *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IGCThreadControl *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IGCThreadControl *This);

    
    HRESULT (STDMETHODCALLTYPE *ThreadIsBlockingForSuspension)(
        IGCThreadControl *This);

    HRESULT (STDMETHODCALLTYPE *SuspensionStarting)(
        IGCThreadControl *This);

    HRESULT (STDMETHODCALLTYPE *SuspensionEnding)(
        IGCThreadControl *This,
        DWORD generation);

    END_INTERFACE
} IGCThreadControlVtbl;

interface IGCThreadControl {
    CONST_VTBL IGCThreadControlVtbl* lpVtbl;
};

#endif  

/*****************************************************************************
 * IGCHostControl interface
 */
#ifndef __IGCHostControl_INTERFACE_DEFINED__
#define __IGCHostControl_INTERFACE_DEFINED__

DEFINE_GUID(IID_IGCHostControl, 0x5513d564, 0x8374, 0x4cb9, 0xae,0xd9, 0x00,0x83,0xf4,0x16,0x0a,0x1d);

typedef struct IGCHostControlVtbl {
    BEGIN_INTERFACE

    
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IGCHostControl *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IGCHostControl *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IGCHostControl *This);

    
    HRESULT (STDMETHODCALLTYPE *RequestVirtualMemLimit)(
        IGCHostControl *This,
        SIZE_T nMaxVirtualMemMB,
        SIZE_T *nNewMaxVirtualMemMB);

    END_INTERFACE
} IGCHostControlVtbl;

interface IGCHostControl {
    CONST_VTBL IGCHostControlVtbl* lpVtbl;
};

#endif  

/*****************************************************************************
 * IDebuggerThreadControl interface
 */
#ifndef __IDebuggerThreadControl_INTERFACE_DEFINED__
#define __IDebuggerThreadControl_INTERFACE_DEFINED__

DEFINE_GUID(IID_IDebuggerThreadControl, 0x23d86786, 0x0bb5, 0x4774, 0x8f,0xb5, 0xe3,0x52,0x2a,0xdd,0x62,0x46);

typedef struct IDebuggerThreadControlVtbl {
    BEGIN_INTERFACE

    
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDebuggerThreadControl *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IDebuggerThreadControl *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IDebuggerThreadControl *This);

    
    HRESULT (STDMETHODCALLTYPE *ThreadIsBlockingForDebugger)(
        IDebuggerThreadControl *This);

    HRESULT (STDMETHODCALLTYPE *ReleaseAllRuntimeThreads)(
        IDebuggerThreadControl *This);

    HRESULT (STDMETHODCALLTYPE *StartBlockingForDebugger)(
        IDebuggerThreadControl *This,
        DWORD dwUnused);

    END_INTERFACE
} IDebuggerThreadControlVtbl;

interface IDebuggerThreadControl {
    CONST_VTBL IDebuggerThreadControlVtbl* lpVtbl;
};

#endif  

/*****************************************************************************
 * ICorConfiguration interface
 */
#ifndef __ICorConfiguration_INTERFACE_DEFINED__
#define __ICorConfiguration_INTERFACE_DEFINED__

DEFINE_GUID(IID_ICorConfiguration, 0x5c2b07a5, 0x1e98, 0x11d3, 0x87,0x2f, 0x00,0xc0,0x4f,0x79,0xed,0x0d);

typedef struct ICorConfigurationVtbl {
    BEGIN_INTERFACE

    
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICorConfiguration *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICorConfiguration *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        ICorConfiguration *This);

    
    HRESULT (STDMETHODCALLTYPE *SetGCThreadControl)(
        ICorConfiguration *This,
        IGCThreadControl *GCThreadControl);

    HRESULT (STDMETHODCALLTYPE *SetGCHostControl)(
        ICorConfiguration *This,
        IGCHostControl *GCHostControl);

    HRESULT (STDMETHODCALLTYPE *SetDebuggerThreadControl)(
        ICorConfiguration *This,
        IDebuggerThreadControl *debuggerThreadControl);

    HRESULT (STDMETHODCALLTYPE *AddDebuggerSpecialThread)(
        ICorConfiguration *This,
        DWORD specialThreadId);

    END_INTERFACE
} ICorConfigurationVtbl;

interface ICorConfiguration {
    CONST_VTBL ICorConfigurationVtbl* lpVtbl;
};

#endif  

/*****************************************************************************
 * ICLRControl interface
 */
#ifndef __ICLRControl_INTERFACE_DEFINED__
#define __ICLRControl_INTERFACE_DEFINED__

DEFINE_GUID(IID_ICLRControl, 0x9065597e, 0xd1a1, 0x4fb2, 0xb6,0xba, 0x7e,0x1f,0xce,0x23,0x0f,0x61);

typedef struct ICLRControlVtbl {
    BEGIN_INTERFACE

    
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICLRControl *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICLRControl *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        ICLRControl *This);

    
    HRESULT (STDMETHODCALLTYPE *GetCLRManager)(
        ICLRControl *This,
        REFIID riid,
        void **ppObject);

    HRESULT (STDMETHODCALLTYPE *SetAppDomainManagerType)(
        ICLRControl *This,
        LPCWSTR appDomainManagerAssembly,
        LPCWSTR appDomainManagerType);

    END_INTERFACE
} ICLRControlVtbl;

interface ICLRControl {
    CONST_VTBL ICLRControlVtbl* lpVtbl;
};

#endif  

/*****************************************************************************
 * IHostControl interface
 */
#ifndef __IHostControl_INTERFACE_DEFINED__
#define __IHostControl_INTERFACE_DEFINED__

DEFINE_GUID(IID_IHostControl, 0x02ca073c, 0x7079, 0x4860, 0x88,0x0a, 0xc2,0xf7,0xa4,0x49,0xc9,0x91);

typedef struct IHostControlVtbl {
    BEGIN_INTERFACE

    
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IHostControl *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IHostControl *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IHostControl *This);

    
    HRESULT (STDMETHODCALLTYPE *GetHostManager)(
        IHostControl *This,
        REFIID riid,
        void **ppObject);

    HRESULT (STDMETHODCALLTYPE *SetAppDomainManager)(
        IHostControl *This,
        DWORD appDomainID,
        IUnknown *appDomainManager);

    END_INTERFACE
} IHostControlVtbl;

interface IHostControl {
    CONST_VTBL IHostControlVtbl* lpVtbl;
};

#endif  

DEFINE_GUID(CLSID_CorRuntimeHost, 0xcb2f6723,0xab3a,0x11d2,0x9c,0x40,0x00,0xc0,0x4f,0xa3,0x0a,0x3e);
/*****************************************************************************
 * ICorRuntimeHost interface
 */
#ifndef __ICorRuntimeHost_INTERFACE_DEFINED__
#define __ICorRuntimeHost_INTERFACE_DEFINED__

DEFINE_GUID(IID_ICorRuntimeHost, 0xcb2f6722, 0xab3a, 0x11d2, 0x9c,0x40, 0x00,0xc0,0x4f,0xa3,0x0a,0x3e);

typedef struct ICorRuntimeHostVtbl {
    BEGIN_INTERFACE

    
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICorRuntimeHost *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICorRuntimeHost *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        ICorRuntimeHost *This);

    
    HRESULT (STDMETHODCALLTYPE *CreateLogicalThreadState)(
        ICorRuntimeHost *This);

    HRESULT (STDMETHODCALLTYPE *DeleteLogicalThreadState)(
        ICorRuntimeHost *This);

    HRESULT (STDMETHODCALLTYPE *SwitchInLogicalThreadState)(
        ICorRuntimeHost *This,
        DWORD *fiberCookie);

    HRESULT (STDMETHODCALLTYPE *SwitchOutLogicalThreadState)(
        ICorRuntimeHost *This,
        DWORD **fiberCookie);

    HRESULT (STDMETHODCALLTYPE *LocksHeldByLogicalThread)(
        ICorRuntimeHost *This,
        DWORD *pCount);

    HRESULT (STDMETHODCALLTYPE *MapFile)(
        ICorRuntimeHost *This,
        HANDLE hFile,
        HMODULE *mapAddress);

    HRESULT (STDMETHODCALLTYPE *GetConfiguration)(
        ICorRuntimeHost *This,
        ICorConfiguration **pConfiguration);

    HRESULT (STDMETHODCALLTYPE *Start)(
        ICorRuntimeHost *This);

    HRESULT (STDMETHODCALLTYPE *Stop)(
        ICorRuntimeHost *This);

    HRESULT (STDMETHODCALLTYPE *CreateDomain)(
        ICorRuntimeHost *This,
        LPCWSTR friendlyName,
        IUnknown *identityArray,
        IUnknown **appDomain);

    HRESULT (STDMETHODCALLTYPE *GetDefaultDomain)(
        ICorRuntimeHost *This,
        IUnknown **pAppDomain);

    HRESULT (STDMETHODCALLTYPE *EnumDomains)(
        ICorRuntimeHost *This,
        HDOMAINENUM *hEnum);

    HRESULT (STDMETHODCALLTYPE *NextDomain)(
        ICorRuntimeHost *This,
        HDOMAINENUM hEnum,
        IUnknown **appDomain);

    HRESULT (STDMETHODCALLTYPE *CloseEnum)(
        ICorRuntimeHost *This,
        HDOMAINENUM hEnum);

    HRESULT (STDMETHODCALLTYPE *CreateDomainEx)(
        ICorRuntimeHost *This,
        LPCWSTR friendlyName,
        IUnknown *setup,
        IUnknown *evidence,
        IUnknown **appDomain);

    HRESULT (STDMETHODCALLTYPE *CreateDomainSetup)(
        ICorRuntimeHost *This,
        IUnknown **appDomainSetup);

    HRESULT (STDMETHODCALLTYPE *CreateEvidence)(
        ICorRuntimeHost *This,
        IUnknown **evidence);

    HRESULT (STDMETHODCALLTYPE *UnloadDomain)(
        ICorRuntimeHost *This,
        IUnknown *appDomain);

    HRESULT (STDMETHODCALLTYPE *CurrentDomain)(
        ICorRuntimeHost *This,
        IUnknown **appDomain);

    END_INTERFACE
} ICorRuntimeHostVtbl;

interface ICorRuntimeHost {
    CONST_VTBL ICorRuntimeHostVtbl* lpVtbl;
};

#endif  

DEFINE_GUID(CLSID_CLRRuntimeHost, 0x90f1a06e,0x7712,0x4762,0x86,0xb5,0x7a,0x5e,0xba,0x6b,0xdb,0x02);
/*****************************************************************************
 * ICLRRuntimeHost interface
 */
#ifndef __ICLRRuntimeHost_INTERFACE_DEFINED__
#define __ICLRRuntimeHost_INTERFACE_DEFINED__

DEFINE_GUID(IID_ICLRRuntimeHost, 0x90f1a06c, 0x7712, 0x4762, 0x86,0xb5, 0x7a,0x5e,0xba,0x6b,0xdb,0x02);

typedef struct ICLRRuntimeHostVtbl {
    BEGIN_INTERFACE

    
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICLRRuntimeHost *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICLRRuntimeHost *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        ICLRRuntimeHost *This);

    
    HRESULT (STDMETHODCALLTYPE *Start)(
        ICLRRuntimeHost *This);

    HRESULT (STDMETHODCALLTYPE *Stop)(
        ICLRRuntimeHost *This);

    HRESULT (STDMETHODCALLTYPE *SetHostControl)(
        ICLRRuntimeHost *This,
        IHostControl *pHostControl);

    HRESULT (STDMETHODCALLTYPE *GetCLRControl)(
        ICLRRuntimeHost *This,
        ICLRControl **pCLRControl);

    HRESULT (STDMETHODCALLTYPE *UnloadAppDomain)(
        ICLRRuntimeHost *This,
        DWORD dwAppDomainId,
        WINBOOL fWaitUntilDone);

    HRESULT (STDMETHODCALLTYPE *ExecuteInAppDomain)(
        ICLRRuntimeHost *This,
        DWORD dwAppDomainId,
        FExecuteInAppDomainCallback pCallback,
        void *cookie);

    HRESULT (STDMETHODCALLTYPE *GetCurrentAppDomainId)(
        ICLRRuntimeHost *This,
        DWORD *pdwAppDomainId);

    HRESULT (STDMETHODCALLTYPE *ExecuteApplication)(
        ICLRRuntimeHost *This,
        LPCWSTR pwzAppFullName,
        DWORD dwManifestPaths,
        LPCWSTR *ppwzManifestPaths,
        DWORD dwActivationData,
        LPCWSTR *ppwzActivationData,
        int *pReturnValue);

    HRESULT (STDMETHODCALLTYPE *ExecuteInDefaultAppDomain)(
        ICLRRuntimeHost *This,
        LPCWSTR pwzAssemblyPath,
        LPCWSTR pwzTypeName,
        LPCWSTR pwzMethodName,
        LPCWSTR pwzArgument,
        DWORD *pReturnValue);

    END_INTERFACE
} ICLRRuntimeHostVtbl;

interface ICLRRuntimeHost {
    CONST_VTBL ICLRRuntimeHostVtbl* lpVtbl;
};

#endif  

/*****************************************************************************
 * IManagedObject interface
 */
#ifndef __IManagedObject_INTERFACE_DEFINED__
#define __IManagedObject_INTERFACE_DEFINED__

DEFINE_GUID(IID_IManagedObject, 0xc3fcc19e, 0xa970, 0x11d2, 0x8b,0x5a, 0x00,0xa0,0xc9,0xb7,0xc9,0xc4);

typedef struct IManagedObjectVtbl {
    BEGIN_INTERFACE

    
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IManagedObject *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IManagedObject *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IManagedObject *This);

    
    HRESULT (STDMETHODCALLTYPE *GetSerializedBuffer)(
        IManagedObject *This,
        BSTR *pBSTR);

    HRESULT (STDMETHODCALLTYPE *GetObjectIdentity)(
        IManagedObject *This,
        BSTR *pBSTRGUID,
        int *AppDomainID,
        int *pCCW);

    END_INTERFACE
} IManagedObjectVtbl;

interface IManagedObject {
    CONST_VTBL IManagedObjectVtbl* lpVtbl;
};

#endif  

#endif 
