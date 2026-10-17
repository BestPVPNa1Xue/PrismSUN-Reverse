__int64 __usercall sub_58CD1C@<X0>(
        __int64 a1@<X0>,
        __int64 a2@<X1>,
        __int64 a3@<X2>,
        __int64 a4@<X3>,
        __int64 a5@<X4>,
        __int64 a6@<X5>,
        __int64 a7@<X6>,
        __int64 a8@<X7>,
        __int64 a9@<X8>)
{
  __int64 v10; // x2
  _QWORD *v11; // x3
  __int64 result; // x0
  __int64 v13; // x2
  _QWORD *v14; // x3
  __int64 v15; // x0
  __int64 v16[6]; // [xsp-D0h] [xbp-F0h] BYREF
  __int64 v17; // [xsp-A0h] [xbp-C0h] BYREF
  _BYTE v18[32]; // [xsp-90h] [xbp-B0h] BYREF
  _QWORD v19[2]; // [xsp-70h] [xbp-90h] BYREF
  _BYTE v20[32]; // [xsp-60h] [xbp-80h] BYREF
  unsigned int *v21; // [xsp-40h] [xbp-60h]
  __int64 v22; // [xsp-30h] [xbp-50h]
  unsigned __int8 v23; // [xsp-20h] [xbp-40h]
  __int64 v24; // [xsp-10h] [xbp-30h]
  __int64 *v25; // [xsp+8h] [xbp-18h]
  _DWORD *v26; // [xsp+10h] [xbp-10h]
  __int64 v27; // [xsp+18h] [xbp-8h]

  v27 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x58cd48*/
  if ( *(_DWORD *)sub_58CD1C >> 26 == 5 /*0x58d004*/
    || *(_DWORD *)sub_58CD1C >> 21 == 1697
    || ((((((loc_58CD20 >> 10 == 3508160) << 31 >> 31)
         + (((loc_58CD20 >> 10 == 3508160) ^ (loc_58CD24 >> 10 == 3508160)) << 31 >> 31)) << 31 >> 31)
       - (((loc_58CD20 >> 10 == 3508160) & (unsigned __int8)(loc_58CD24 >> 10 != 3508160)) << 31 >> 31))
      & 1) != 0 )
  {
    _ReadStatusReg(TPIDR_EL0); /*0x58cf50*/
    abort(); /*0x58cf64*/
  }
  v26 = v20; /*0x58cd84*/
  v25 = &v17; /*0x58cda8*/
  v24 = a9; /*0x58cdc0*/
  v23 = a1; /*0x58cdc4*/
  v22 = a2; /*0x58cdc8*/
  v21 = sub_4EA8B8(a1, a2, a3, a4, a5, a6, a7, a8, v16[0], v16[1], v16[2], v16[3], v16[4]); /*0x58cdd0*/
  if ( (((__int64 (__fastcall *)(unsigned int *, _QWORD))loc_4EAD4C)(v21, v23) & 1) != 0 ) /*0x58cde4*/
  {
    ((void (__fastcall *)(_QWORD *__return_ptr, unsigned int *, _QWORD))loc_4EB5B0)(v19, v21, v23); /*0x58ce1c*/
    if ( (sub_58F770(v19) & 1) != 0 ) /*0x58ce28*/
    {
      sub_58F774(v18, v22); /*0x58ce60*/
      v15 = ((__int64 (__fastcall *)(_QWORD *))loc_4EC358)(v19); /*0x58ce68*/
      (*(void (__fastcall **)(__int64 *__return_ptr, __int64, _BYTE *))(*(_QWORD *)v15 + 64LL))(v16, v15, v18); /*0x58ce7c*/
      ((void (__fastcall *)(__int64 *))loc_51E9C4)(v16); /*0x58ce94*/
      *v26 = 1; /*0x58cea8*/
      sub_2D9160((__int64)v16); /*0x58ceb0*/
    }
    else
    {
      sub_51FC30(a9, v18[16], v13, v14); /*0x58ce40*/
      *v26 = 1; /*0x58ce4c*/
    }
    result = ((__int64 (__fastcall *)(_QWORD *))loc_4ED374)(v19); /*0x58cef0*/
  }
  else
  {
    result = sub_51FC30(a9, v20[16], v10, v11); /*0x58cdfc*/
    *v26 = 1; /*0x58ce08*/
  }
  _ReadStatusReg(TPIDR_EL0); /*0x58cefc*/
  return result; /*0x58cf2c*/
}