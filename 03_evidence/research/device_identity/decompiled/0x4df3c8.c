__int64 __usercall sub_4DF3C8@<X0>(__int64 a1@<X8>)
{
  __int64 v2; // x0
  __int64 v3; // x24
  __int64 v4; // x25
  __int64 v5; // x0
  __int64 result; // x0
  _BYTE v7[32]; // [xsp-90h] [xbp-A0h] BYREF
  _QWORD v8[4]; // [xsp-70h] [xbp-80h] BYREF
  _QWORD v9[2]; // [xsp-50h] [xbp-60h] BYREF
  int v10; // [xsp-40h] [xbp-50h]
  _QWORD v11[8]; // [xsp-30h] [xbp-40h] BYREF

  v11[7] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x4df3f0*/
  if ( (*(_DWORD *)sub_4DF3C8 >> 26 == 5 && *(_DWORD *)sub_4DF3C8 >> 21 == 1697) /*0x4df62c*/
     | (*(_DWORD *)sub_4DF3C8 >> 26 == 5) ^ (*(_DWORD *)sub_4DF3C8 >> 21 == 1697)
    || loc_4DF3CC >> 10 == 3508160
    || loc_4DF3D0 >> 10 == 3508160 )
  {
    _ReadStatusReg(TPIDR_EL0); /*0x4df59c*/
    abort(); /*0x4df5b0*/
  }
  v11[4] = a1; /*0x4df43c*/
  v2 = sub_56BFB4(); /*0x4df440*/
  sub_5AE1D4(v2, (__int64)v11); /*0x4df448*/
  if ( (sub_CB11C(v11) & 1) != 0 ) /*0x4df454*/
  {
    sub_F7768(a1); /*0x4df45c*/
  }
  else
  {
    v3 = sub_141054(v11); /*0x4df474*/
    v4 = sub_141054(v11); /*0x4df480*/
    v5 = sub_D038C(v11); /*0x4df488*/
    ((void (__fastcall *)(_BYTE *, __int64, __int64))loc_4DF640)(v7, v3, v4 + v5); /*0x4df498*/
    sub_5B9DF4(v8, v7); /*0x4df4b0*/
    sub_56BFB8(v9, v8); /*0x4df4c0*/
    sub_CF83C(v9[0], v9[1], 1); /*0x4df4d4*/
    sub_D2AC4(v8); /*0x4df4e4*/
    sub_56BFBC(v7); /*0x4df4ec*/
  }
  v10 = 1; /*0x4df464*/
  result = sub_74539C(v11); /*0x4df544*/
  _ReadStatusReg(TPIDR_EL0); /*0x4df548*/
  return result; /*0x4df578*/
}