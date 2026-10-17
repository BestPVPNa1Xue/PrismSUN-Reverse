__int64 __usercall sub_4DFC3C@<X0>(__int64 a1@<X8>)
{
  __int64 v2; // x24
  __int64 v3; // x25
  __int64 v4; // x0
  __int64 result; // x0
  _BYTE v6[32]; // [xsp-90h] [xbp-A0h] BYREF
  _QWORD v7[4]; // [xsp-70h] [xbp-80h] BYREF
  __int64 v8[2]; // [xsp-50h] [xbp-60h] BYREF
  int v9; // [xsp-40h] [xbp-50h]
  _QWORD v10[8]; // [xsp-30h] [xbp-40h] BYREF

  v10[7] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x4dfc64*/
  if ( (*(_DWORD *)sub_4DFC3C >> 26 == 5 || *(_DWORD *)sub_4DFC3C >> 21 == 1697) /*0x4dfec8*/
    && (*(_DWORD *)sub_4DFC3C >> 26 == 5 || *(_DWORD *)sub_4DFC3C >> 21 == 1697)
    || loc_4DFC40 >> 10 == 3508160
    || loc_4DFC44 >> 10 == 3508160 )
  {
    _ReadStatusReg(TPIDR_EL0); /*0x4dfe24*/
    abort(); /*0x4dfe38*/
  }
  v10[4] = a1; /*0x4dfcb8*/
  ((void (__fastcall *)(_QWORD *__return_ptr))loc_5D8330)(v10); /*0x4dfcc0*/
  if ( (sub_CB11C(v10) & 1) != 0 ) /*0x4dfccc*/
  {
    sub_F7768(a1); /*0x4dfcd8*/
  }
  else
  {
    v2 = sub_141054(v10); /*0x4dfcf0*/
    v3 = sub_56BFCC(v10); /*0x4dfcfc*/
    v4 = sub_D038C((__int64)v10); /*0x4dfd04*/
    sub_56BFD0(v6, v2, v3 + v4); /*0x4dfd14*/
    sub_5B9DF4((__int64)v6, v7); /*0x4dfd2c*/
    sub_13F770(v8, v7); /*0x4dfd44*/
    sub_CF83C(v8[0], v8[1], 1, a1); /*0x4dfd5c*/
    sub_56BFD4((__int64)v7); /*0x4dfd6c*/
    sub_C4640(v6); /*0x4dfd74*/
  }
  v9 = 1; /*0x4dfce0*/
  result = sub_74539C(v10); /*0x4dfdc8*/
  _ReadStatusReg(TPIDR_EL0); /*0x4dfdcc*/
  return result; /*0x4dfdfc*/
}