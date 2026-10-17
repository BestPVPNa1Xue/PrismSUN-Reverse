__int64 __usercall sub_5B9DF4@<X0>(__int64 a1@<X0>, _QWORD *a2@<X8>)
{
  __int64 *v2; // x26
  __int64 v3; // x28
  __int64 v4; // x0
  __int64 *v5; // x28
  _QWORD *v6; // x25
  __int64 v7; // x0
  __int64 v8; // x0
  __int64 *v9; // x1
  __int64 *v10; // x23
  __int64 v11; // x0
  __int64 *v12; // x24
  __int64 v13; // x0
  __int64 *v14; // x8
  __int64 v15; // x0
  __int64 v16; // x24
  __int64 v17; // x0
  __int64 *v18; // x8
  __int64 v19; // x1
  __int64 *v20; // x9
  __int64 result; // x0
  __int64 v22; // [xsp-1B0h] [xbp-220h] BYREF
  __int64 v23; // [xsp-1A0h] [xbp-210h] BYREF
  __int64 v24; // [xsp-190h] [xbp-200h] BYREF
  __int64 v25; // [xsp-160h] [xbp-1D0h] BYREF
  __int64 v26; // [xsp-150h] [xbp-1C0h] BYREF
  __int64 v27; // [xsp-140h] [xbp-1B0h] BYREF
  __int64 v28; // [xsp-130h] [xbp-1A0h] BYREF
  __int64 v29; // [xsp-120h] [xbp-190h] BYREF
  __int64 v30; // [xsp-110h] [xbp-180h] BYREF
  __int64 v31; // [xsp-100h] [xbp-170h]
  __int64 v32; // [xsp-F0h] [xbp-160h]
  __int64 v33; // [xsp-E0h] [xbp-150h] BYREF
  __int64 v34; // [xsp-D0h] [xbp-140h] BYREF
  __int64 v35; // [xsp-C0h] [xbp-130h] BYREF
  _BYTE v36[16]; // [xsp-80h] [xbp-F0h] BYREF
  _BYTE *v37; // [xsp-70h] [xbp-E0h]
  __int64 v38; // [xsp-68h] [xbp-D8h]
  _BYTE v39[32]; // [xsp-60h] [xbp-D0h] BYREF
  _QWORD v40[4]; // [xsp-40h] [xbp-B0h] BYREF
  _QWORD v41[4]; // [xsp-20h] [xbp-90h] BYREF
  __int64 *v42; // [xsp+0h] [xbp-70h]
  __int64 *v43; // [xsp+8h] [xbp-68h]
  __int64 *v44; // [xsp+10h] [xbp-60h]
  __int64 *v45; // [xsp+18h] [xbp-58h]
  __int64 *v46; // [xsp+20h] [xbp-50h]
  __int64 *v47; // [xsp+28h] [xbp-48h]
  __int64 *v48; // [xsp+30h] [xbp-40h]
  __int64 *v49; // [xsp+38h] [xbp-38h]
  _QWORD *v50; // [xsp+40h] [xbp-30h]
  __int64 *v51; // [xsp+48h] [xbp-28h]
  __int64 *v52; // [xsp+50h] [xbp-20h]
  __int64 *v53; // [xsp+58h] [xbp-18h]
  _QWORD *v54; // [xsp+60h] [xbp-10h]
  __int64 v55; // [xsp+68h] [xbp-8h]

  v55 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x5b9e1c*/
  if ( *(_DWORD *)sub_5B9DF4 >> 26 == 5 /*0x5ba35c*/
    || *(_DWORD *)sub_5B9DF4 >> 21 == 1697
    || loc_5B9DF8 >> 10 == 3508160
    || loc_5B9DFC >> 10 == 3508160 )
  {
    _ReadStatusReg(TPIDR_EL0); /*0x5ba2d8*/
    abort(); /*0x5ba2ec*/
  }
  v50 = v41; /*0x5b9e3c*/
  v53 = &v35; /*0x5b9e80*/
  v45 = &v34; /*0x5b9e8c*/
  v43 = &v30; /*0x5b9eb0*/
  v48 = &v29; /*0x5b9ebc*/
  v42 = &v28; /*0x5b9ec8*/
  v46 = &v27; /*0x5b9ed4*/
  v44 = &v26; /*0x5b9ee0*/
  v47 = &v25; /*0x5b9eec*/
  v52 = &v24; /*0x5b9ef8*/
  v49 = &v23; /*0x5b9f04*/
  v51 = &v22; /*0x5b9f10*/
  v54 = a2; /*0x5b9f18*/
  v41[2] = a2; /*0x5b9f1c*/
  v41[0] = a1; /*0x5b9f20*/
  ((void (__fastcall *)(_QWORD *__return_ptr))sub_5B8524)(v40); /*0x5b9f2c*/
  v36[0] = 103; /*0x5b9f34*/
  v36[1] = -42; /*0x5b9f3c*/
  v36[2] = -45; /*0x5b9f44*/
  v36[3] = 29; /*0x5b9f4c*/
  v36[4] = -50; /*0x5b9f54*/
  v36[5] = -87; /*0x5b9f5c*/
  v36[6] = -18; /*0x5b9f64*/
  v36[7] = -57; /*0x5b9f6c*/
  v36[8] = -70; /*0x5b9f74*/
  v36[9] = 27; /*0x5b9f7c*/
  v36[10] = 28; /*0x5b9f84*/
  v36[11] = -30; /*0x5b9f8c*/
  v36[12] = -56; /*0x5b9f94*/
  v36[13] = 123; /*0x5b9f9c*/
  v36[14] = -85; /*0x5b9fa4*/
  v36[15] = 123; /*0x5b9fa8*/
  v37 = v36; /*0x5b9fac*/
  v38 = 16; /*0x5b9fb8*/
  sub_5CC288(v39, v36, 16); /*0x5b9fc8*/
  v2 = v53; /*0x5b9fd0*/
  sub_C445C(v53); /*0x5b9fd8*/
  v3 = sub_5CC28C(*v50); /*0x5b9fe8*/
  v4 = sub_C4844(v39); /*0x5b9ff0*/
  sub_5CC290(v2, v3 + v4); /*0x5ba008*/
  v33 = sub_D7F1C(v2); /*0x5ba018*/
  v5 = v45; /*0x5ba01c*/
  sub_192060(v45, &v33); /*0x5ba028*/
  v6 = v50; /*0x5ba02c*/
  v32 = sub_1B2AF8(*v50); /*0x5ba038*/
  v31 = sub_5CC294(*v6); /*0x5ba044*/
  v7 = sub_5CC298(v2, *v5, v32, v31); /*0x5ba058*/
  *v43 = v7; /*0x5ba068*/
  v8 = sub_5CC29C(v2); /*0x5ba070*/
  v9 = v42; /*0x5ba074*/
  *v42 = v8; /*0x5ba078*/
  v10 = v48; /*0x5ba07c*/
  sub_5CC2A0(v48, v9); /*0x5ba084*/
  v11 = sub_1B2AF8(v39); /*0x5ba08c*/
  v12 = v46; /*0x5ba090*/
  *v46 = v11; /*0x5ba094*/
  v13 = sub_1B2BE4(v39); /*0x5ba09c*/
  v14 = v44; /*0x5ba0a0*/
  *v44 = v13; /*0x5ba0a4*/
  v15 = sub_22670C(v2, *v10, *v12, *v14); /*0x5ba0b8*/
  *v47 = v15; /*0x5ba0c4*/
  v16 = sub_5CC2A4(96); /*0x5ba0d0*/
  v17 = sub_B6F98(v40); /*0x5ba0dc*/
  v18 = v49; /*0x5ba0e0*/
  v49[1] = v19; /*0x5ba0e4*/
  *v18 = v17; /*0x5ba0e8*/
  sub_119F34(v16, *v18, v18[1], 0); /*0x5ba0fc*/
  sub_120658(v52, v16, 0, 0, 0); /*0x5ba120*/
  sub_1220EC(v52, v2); /*0x5ba138*/
  *(_BYTE *)v51 = 0; /*0x5ba148*/
  sub_122DB4(v54, v52, -1); /*0x5ba160*/
  sub_121460(v52); /*0x5ba174*/
  v20 = v51; /*0x5ba188*/
  *(_BYTE *)v51 = 1; /*0x5ba18c*/
  if ( (*(_BYTE *)v20 & 1) == 0 ) /*0x5ba19c*/
    sub_D2AC4(v54); /*0x5ba220*/
  sub_5CC2A8(v52); /*0x5ba230*/
  sub_5CC2AC(v2); /*0x5ba238*/
  sub_C4640(v39); /*0x5ba240*/
  result = sub_74539C(v40); /*0x5ba248*/
  _ReadStatusReg(TPIDR_EL0); /*0x5ba24c*/
  return result; /*0x5ba27c*/
}