__int64 __usercall sub_3780EC@<X0>(__int64 a1@<X0>, __int64 a2@<X8>)
{
  __int64 v2; // x24
  __int64 v3; // x0
  __int64 v4; // x1
  __int64 v5; // x0
  __int64 v6; // x1
  __int64 result; // x0
  _QWORD v8[4]; // [xsp-F0h] [xbp-110h] BYREF
  _QWORD v9[2]; // [xsp-D0h] [xbp-F0h] BYREF
  char v10; // [xsp-C0h] [xbp-E0h]
  __int64 v11; // [xsp-B0h] [xbp-D0h]
  __int64 v12; // [xsp-A8h] [xbp-C8h]
  __int64 v13; // [xsp-A0h] [xbp-C0h]
  __int64 v14; // [xsp-98h] [xbp-B8h]
  __int64 v15; // [xsp-70h] [xbp-90h] BYREF
  _QWORD v16[4]; // [xsp-40h] [xbp-60h] BYREF
  __int64 v17; // [xsp-20h] [xbp-40h]
  __int64 v18; // [xsp-10h] [xbp-30h]
  __int64 *v19; // [xsp+8h] [xbp-18h]
  __int64 v20; // [xsp+10h] [xbp-10h]
  __int64 v21; // [xsp+18h] [xbp-8h]

  v21 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x378114*/
  if ( *(_DWORD *)sub_3780EC >> 26 == 5 /*0x378428*/
    || *(_DWORD *)sub_3780EC >> 21 == 1697
    || loc_3780F0 >> 10 == 3508160
    || loc_3780F4 >> 10 == 3508160 )
  {
    _ReadStatusReg(TPIDR_EL0); /*0x37839c*/
    abort(); /*0x3783b0*/
  }
  v19 = &v15; /*0x378140*/
  v20 = a2; /*0x378180*/
  v18 = a2; /*0x378184*/
  v17 = a1; /*0x378188*/
  ((void (__fastcall *)(_QWORD *__return_ptr))sub_5B8524)(v16); /*0x378190*/
  v2 = sub_3B33B4(96); /*0x37819c*/
  v3 = sub_3B33B8(v16); /*0x3781ac*/
  v14 = v4; /*0x3781b0*/
  v13 = v3; /*0x3781b4*/
  sub_3B33BC(v2, v3, v4, 0); /*0x3781c8*/
  sub_120658(v19, v2, 0, 0, 0); /*0x3781ec*/
  v5 = sub_B6F98(v17); /*0x3781fc*/
  v12 = v6; /*0x378200*/
  v11 = v5; /*0x378204*/
  sub_1221B4(v19, v5, v6); /*0x378214*/
  v10 = 0; /*0x378220*/
  sub_122DB4(v8, v19, -1); /*0x378238*/
  sub_13F770(v9, v8); /*0x378250*/
  sub_CF83C(v9[0], v9[1], 1); /*0x378268*/
  sub_D2AC4(v8); /*0x378274*/
  sub_121460(v19); /*0x37827c*/
  sub_141BD0(v16); /*0x37828c*/
  v10 = 1; /*0x378298*/
  sub_3B33C4(v19); /*0x378320*/
  result = sub_74539C(v16); /*0x378328*/
  _ReadStatusReg(TPIDR_EL0); /*0x37832c*/
  return result; /*0x37835c*/
}