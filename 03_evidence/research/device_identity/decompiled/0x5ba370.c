__int64 __usercall sub_5BA370@<X0>(__int64 a1@<X0>, __int64 a2@<X1>, __int64 a3@<X8>)
{
  __int64 v3; // x0
  __int64 v4; // x23
  __int64 v5; // x22
  __int64 *v6; // x24
  __int64 v7; // x0
  __int64 result; // x0
  __int64 v9; // [xsp-E0h] [xbp-110h] BYREF
  _BYTE v10[32]; // [xsp-D0h] [xbp-100h] BYREF
  __int64 v11; // [xsp-B0h] [xbp-E0h] BYREF
  _QWORD v12[2]; // [xsp-90h] [xbp-C0h] BYREF
  _QWORD v13[2]; // [xsp-80h] [xbp-B0h] BYREF
  _QWORD v14[2]; // [xsp-70h] [xbp-A0h] BYREF
  _QWORD v15[2]; // [xsp-60h] [xbp-90h] BYREF
  __int64 v16; // [xsp-50h] [xbp-80h] BYREF
  char *v17; // [xsp-40h] [xbp-70h]
  __int64 v18; // [xsp-30h] [xbp-60h] BYREF
  __int64 v19; // [xsp-20h] [xbp-50h]
  __int64 v20; // [xsp-10h] [xbp-40h]
  __int64 *v21; // [xsp+8h] [xbp-28h]
  __int64 *v22; // [xsp+10h] [xbp-20h]
  __int64 *v23; // [xsp+18h] [xbp-18h]
  __int64 v24; // [xsp+20h] [xbp-10h]
  __int64 v25; // [xsp+28h] [xbp-8h]

  v25 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x5ba398*/
  if ( *(_DWORD *)sub_5BA370 >> 26 == 5 /*0x5ba67c*/
    || *(_DWORD *)sub_5BA370 >> 21 == 1697
    || loc_5BA374 >> 10 == 3508160
    || loc_5BA378 >> 10 == 3508160 )
  {
    _ReadStatusReg(TPIDR_EL0); /*0x5ba5f4*/
    sub_5CC2D4(); /*0x5ba608*/
  }
  v22 = &v18; /*0x5ba3c8*/
  v23 = &v11; /*0x5ba41c*/
  v21 = &v9; /*0x5ba434*/
  v24 = a3; /*0x5ba43c*/
  v20 = a3; /*0x5ba440*/
  v19 = a1; /*0x5ba444*/
  v18 = a2; /*0x5ba448*/
  v3 = sub_5CC2BC(&v16); /*0x5ba450*/
  v17 = (char *)((__int64 (__fastcall *)(__int64))loc_5BB4AC)(v3); /*0x5ba458*/
  sub_B6704(v14, v17); /*0x5ba464*/
  sub_B6704(v13, &byte_34073); /*0x5ba474*/
  sub_11A5CC(v15, v14[0], v14[1], v13[0], v13[1]); /*0x5ba48c*/
  v4 = sub_11A7E8(v15) + 8; /*0x5ba498*/
  sub_5CC2C0(v12, v19); /*0x5ba4a4*/
  sub_F5BD0(v4, v12[0], v12[1]); /*0x5ba4b8*/
  v5 = sub_5CC2C4(v15); /*0x5ba4cc*/
  v6 = v22; /*0x5ba4d0*/
  sub_5CC2C8(*v22); /*0x5ba4d8*/
  sub_D038C(*v6); /*0x5ba4e4*/
  sub_5CC2CC(v5); /*0x5ba4f4*/
  v7 = sub_11A7E8(v15); /*0x5ba500*/
  sub_11A3BC(v7, (__int64)v10); /*0x5ba508*/
  sub_D29A8(v21, v10); /*0x5ba518*/
  sub_CF83C(*v21, v21[1], 1, v24); /*0x5ba534*/
  sub_D2AC4((__int64)v10); /*0x5ba544*/
  result = sub_F4328(v15); /*0x5ba54c*/
  _ReadStatusReg(TPIDR_EL0); /*0x5ba550*/
  return result; /*0x5ba580*/
}