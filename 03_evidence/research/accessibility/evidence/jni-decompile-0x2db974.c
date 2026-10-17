__int64 __fastcall sub_2DB974(__int64 a1)
{
  __int64 v1; // x0
  __int64 v2; // x25
  __int64 v3; // x0
  __int64 v4; // x0
  __int64 v5; // x0
  __int64 v6; // x23
  __int64 v7; // x1
  __int64 v8; // x23
  __int64 v9; // x24
  __int64 v10; // x1
  __int64 v11; // x2
  __int64 *v12; // x19
  __int64 *v13; // x20
  __int64 v14; // x0
  __int64 v15; // x0
  __int64 v16; // x0
  __int64 v17; // x21
  __int64 v18; // x0
  __int64 v19; // x0
  __int64 v20; // x21
  __int64 v21; // x1
  __int64 v22; // x21
  __int64 v24; // [xsp-110h] [xbp-150h] BYREF
  __int64 v25; // [xsp-100h] [xbp-140h] BYREF
  __int64 v26; // [xsp-F0h] [xbp-130h] BYREF
  __int64 v27; // [xsp-E0h] [xbp-120h] BYREF
  __int64 v28; // [xsp-D0h] [xbp-110h] BYREF
  __int64 v29; // [xsp-C0h] [xbp-100h] BYREF
  __int64 v30; // [xsp-B0h] [xbp-F0h]
  __int64 v31; // [xsp-A0h] [xbp-E0h] BYREF
  __int64 v32; // [xsp-90h] [xbp-D0h]
  __int64 v33; // [xsp-80h] [xbp-C0h] BYREF
  __int64 v34; // [xsp-60h] [xbp-A0h] BYREF
  __int64 v35; // [xsp-50h] [xbp-90h]
  _BYTE v36[16]; // [xsp-40h] [xbp-80h] BYREF
  _QWORD v37[4]; // [xsp-30h] [xbp-70h] BYREF
  __int64 v38; // [xsp-10h] [xbp-50h]
  __int64 *v39; // [xsp+0h] [xbp-40h]
  __int64 *v40; // [xsp+8h] [xbp-38h]
  __int64 *v41; // [xsp+10h] [xbp-30h]
  __int64 *v42; // [xsp+18h] [xbp-28h]
  __int64 *v43; // [xsp+20h] [xbp-20h]
  __int64 *v44; // [xsp+28h] [xbp-18h]
  __int64 *v45; // [xsp+30h] [xbp-10h]
  __int64 v46; // [xsp+38h] [xbp-8h]

  v46 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x2db99c*/
  if ( *(_DWORD *)sub_2DB974 >> 26 == 5 /*0x2dbd6c*/
    || *(_DWORD *)sub_2DB974 >> 21 == 1697
    || loc_2DB978 >> 10 == 3508160
    || loc_2DB97C >> 10 == 3508160 )
  {
    _ReadStatusReg(TPIDR_EL0); /*0x2dbce4*/
    abort(); /*0x2dbcf8*/
  }
  v45 = &v33; /*0x2db9ec*/
  v44 = &v29; /*0x2dba10*/
  v42 = &v28; /*0x2dba1c*/
  v39 = &v27; /*0x2dba28*/
  v41 = &v26; /*0x2dba34*/
  v40 = &v25; /*0x2dba40*/
  v43 = &v24; /*0x2dba4c*/
  v38 = a1; /*0x2dba54*/
  v1 = sub_30542C(v37); /*0x2dba5c*/
  v37[2] = ((__int64 (__fastcall *)(__int64))loc_2DC9D8)(v1); /*0x2dba64*/
  v2 = v38; /*0x2dba68*/
  sub_305430(); /*0x2dba78*/
  ((void (__fastcall *)(_BYTE *, __int64, __int64))loc_2DD338)(v36, v2, v3); /*0x2dba88*/
  v4 = ((__int64 (__fastcall *)(__int64 *))loc_2DD788)(&v34); /*0x2dba90*/
  v35 = ((__int64 (__fastcall *)(__int64))loc_2DE92C)(v4); /*0x2dbaa8*/
  v5 = ((__int64 (__fastcall *)(__int64 *))loc_2DED98)(&v31); /*0x2dbab0*/
  v32 = sub_305434(v5); /*0x2dbac8*/
  v6 = v38; /*0x2dbacc*/
  v7 = sub_305438(v36); /*0x2dbad8*/
  v30 = ((__int64 (__fastcall *)(__int64, __int64, __int64, __int64))loc_2E00CC)(v6, v7, v35, v32); /*0x2dbaf8*/
  v8 = v38; /*0x2dbafc*/
  v9 = v38; /*0x2dbb00*/
  v10 = ((__int64 (__fastcall *)(_BYTE *))loc_2E05E0)(v36); /*0x2dbb0c*/
  v11 = ((__int64 (__fastcall *)(__int64, __int64, __int64))loc_2E0A2C)(v9, v10, v30); /*0x2dbb20*/
  v12 = v44; /*0x2dbb24*/
  sub_30543C(v44, v8, v11); /*0x2dbb3c*/
  v13 = v41; /*0x2dbb40*/
  v14 = ((__int64 (__fastcall *)(__int64 *))loc_2E1468)(v39); /*0x2dbb4c*/
  v15 = ((__int64 (__fastcall *)(__int64))loc_2E2270)(v14); /*0x2dbb5c*/
  *v42 = v15; /*0x2dbb68*/
  v16 = ((__int64 (__fastcall *)(__int64 *))loc_2E2614)(v40); /*0x2dbb70*/
  *v13 = sub_305440(v16); /*0x2dbb88*/
  v17 = v38; /*0x2dbb8c*/
  v18 = ((__int64 (__fastcall *)(_BYTE *))loc_2E05E0)(v36); /*0x2dbb94*/
  v19 = ((__int64 (__fastcall *)(__int64, __int64, __int64, __int64))loc_2E3E98)(v17, v18, *v42, *v13); /*0x2dbbac*/
  *v43 = v19; /*0x2dbbbc*/
  v20 = v38; /*0x2dbbc0*/
  v21 = ((__int64 (__fastcall *)(__int64 *))loc_2E49DC)(v12); /*0x2dbbcc*/
  v22 = ((__int64 (__fastcall *)(__int64, __int64, __int64))loc_2E4448)(v20, v21, *v43); /*0x2dbbe8*/
  sub_305444(v12); /*0x2dbbf0*/
  sub_305448(v36); /*0x2dbbf8*/
  _ReadStatusReg(TPIDR_EL0); /*0x2dbbfc*/
  return v22; /*0x2dbc30*/
}