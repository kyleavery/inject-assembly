#pragma once

typedef struct
{
    ICLRMetaHost*       MH;
    ICLRRuntimeInfo*    RI;
    ICorRuntimeHost*    RH;
    _MethodInfo*        EN;
    _MethodInfo*        EX;
    _MethodInfo*        FP;
    _AppDomain*         DA;
    _Assembly*          AS;
    _Assembly*          MS;
    _Type*              MI;
    _Type*              SE;
    _Type*              RM;
    _PropertyInfo*      HA;
    IUnknown*           AD;
    SAFEARRAY*          PR;
    SAFEARRAY*          AR;
    SAFEARRAY*          PS;
    SAFEARRAY*          ID;
    SAFEARRAY*          FA;
    SAFEARRAYBOUND      SB[1];
    PVOID               PD;
    OLECHAR             OC[1];
    INT                 AC;
    LONG                UC;
    LONG                LC;
    ULONG               LN;
    ULONG               CT;
    WCHAR**             AL;
    WCHAR               BF[257];
    VARIANT             V1;
    VARIANT             V2;
    VARIANT             V3;

} CLR, *PCLR;
