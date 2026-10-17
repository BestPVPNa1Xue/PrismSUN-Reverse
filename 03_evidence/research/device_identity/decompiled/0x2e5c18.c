__int64 __usercall sub_2E5C18@<X0>(__int64 a1@<X0>, __int64 a2@<X8>)
{
  __int64 v3; // x0
  __int64 v4; // x24
  __int64 v5; // x25
  __int64 v6; // x1
  __int64 v7; // x2
  __int64 v8; // x0
  __int64 v9; // x0
  __int64 v10; // x22
  __int64 v11; // x1
  __int64 v12; // x22
  __int64 v13; // x23
  __int64 v14; // x1
  __int64 v15; // x3
  __int64 v16; // x4
  __int64 v17; // x5
  __int64 v18; // x6
  __int64 v19; // x7
  __int64 v20; // x2
  __int64 *v21; // x20
  __int64 v22; // x22
  __int64 v23; // x1
  __int64 result; // x0
  __int64 v25[2]; // [xsp-C0h] [xbp-F0h] BYREF
  __int64 v26; // [xsp-B0h] [xbp-E0h]
  __int64 v27; // [xsp-A8h] [xbp-D8h]
  __int64 v28[2]; // [xsp-A0h] [xbp-D0h] BYREF
  __int64 v29; // [xsp-90h] [xbp-C0h]
  __int64 v30; // [xsp-80h] [xbp-B0h] BYREF
  __int64 v31; // [xsp-70h] [xbp-A0h]
  __int64 v32; // [xsp-60h] [xbp-90h] BYREF
  __int64 v33; // [xsp-40h] [xbp-70h] BYREF
  _BYTE v34[16]; // [xsp-30h] [xbp-60h] BYREF
  __int64 v35; // [xsp-20h] [xbp-50h]
  __int64 v36; // [xsp-10h] [xbp-40h]
  __int64 *v37; // [xsp+8h] [xbp-28h]
  __int64 *v38; // [xsp+10h] [xbp-20h]
  __int64 *v39; // [xsp+18h] [xbp-18h]
  __int64 v40; // [xsp+20h] [xbp-10h]
  __int64 v41; // [xsp+28h] [xbp-8h]

  v41 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x2e5c40*/
  if ( *(_DWORD *)sub_2E5C18 >> 26 == 5 /*0x2e5f80*/
    || *(_DWORD *)sub_2E5C18 >> 21 == 1697
    || loc_2E5C1C >> 10 == 3508160
    || loc_2E5C20 >> 10 == 3508160 )
  {
    _ReadStatusReg(TPIDR_EL0); /*0x2e5efc*/
    abort(); /*0x2e5f10*/
  }
  v39 = &v33; /*0x2e5c6c*/
  v38 = &v32; /*0x2e5c80*/
  v37 = v25; /*0x2e5cb4*/
  v40 = a2; /*0x2e5cbc*/
  v36 = a2; /*0x2e5cc0*/
  v35 = a1; /*0x2e5cc4*/
  v3 = sub_2DB974(a1); /*0x2e5cd0*/
  sub_30551C(v34, a1, v3); /*0x2e5ce0*/
  v4 = v35; /*0x2e5ce4*/
  v5 = v35; /*0x2e5ce8*/
  v6 = sub_305520(v34); /*0x2e5cf4*/
  v7 = ((__int64 (__fastcall *)(__int64, __int64))loc_2E5F94)(v5, v6); /*0x2e5d08*/
  ((void (__fastcall *)(__int64 *, __int64, __int64))loc_2DD338)(v39, v4, v7); /*0x2e5d20*/
  v8 = ((__int64 (__fastcall *)(__int64 *))loc_2E62B0)(&v30); /*0x2e5d2c*/
  v31 = ((__int64 (__fastcall *)(__int64))loc_2E6CD0)(v8); /*0x2e5d3c*/
  v9 = sub_305524(v28); /*0x2e5d44*/
  v29 = ((__int64 (__fastcall *)(__int64))loc_2E8134)(v9); /*0x2e5d5c*/
  v10 = v35; /*0x2e5d60*/
  v11 = sub_305528(v39); /*0x2e5d6c*/
  v26 = sub_2E3E98(v10, v11, v31, v29); /*0x2e5d8c*/
  v12 = v35; /*0x2e5d90*/
  v13 = v35; /*0x2e5d94*/
  v14 = ((__int64 (__fastcall *)(_BYTE *))loc_2E49DC)(v34); /*0x2e5da0*/
  v20 = sub_2E4448(v13, v14, v26, v15, v16, v17, v18, v19, v25[0], v25[1], v26, v27, v28[0], v28[1], v29); /*0x2e5db4*/
  v21 = v37; /*0x2e5db8*/
  ((void (__fastcall *)(__int64 *, __int64, __int64))loc_2E8568)(v37, v12, v20); /*0x2e5dc8*/
  v22 = v35; /*0x2e5dd0*/
  v23 = sub_30552C(v21); /*0x2e5ddc*/
  sub_2E5024(v22, v23, v40); /*0x2e5df0*/
  sub_2E8D48(v21); /*0x2e5e00*/
  sub_305530(v39); /*0x2e5e08*/
  result = sub_2E4DD0(v34); /*0x2e5e10*/
  _ReadStatusReg(TPIDR_EL0); /*0x2e5e14*/
  return result; /*0x2e5e44*/
}