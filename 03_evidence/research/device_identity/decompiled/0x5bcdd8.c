__int64 __usercall sub_5BCDD8@<X0>(
        __int64 a1@<X0>,
        __int64 a2@<X1>,
        unsigned __int16 a3@<W2>,
        unsigned __int64 a4@<X3>,
        __int64 a5@<X8>)
{
  char v5; // w0
  int v6; // w21
  __int64 *v7; // x25
  char v8; // w21
  __int64 v9; // x0
  __int64 *v10; // x24
  _QWORD *v11; // x27
  __int64 v12; // x0
  __int64 v13; // x1
  __int64 v14; // x1
  __int64 *v15; // x26
  __int64 v16; // x24
  __int64 v17; // x0
  __int64 v18; // x0
  __int64 *v19; // x1
  __int64 *v20; // x19
  __int64 v21; // x0
  __int64 *v22; // x21
  __int64 v23; // x0
  __int64 *v24; // x8
  __int64 v25; // x0
  __int64 v26; // x19
  __int64 v27; // x0
  __int64 *v28; // x1
  __int64 *v29; // x22
  __int64 *v30; // x21
  __int64 v31; // x0
  __int64 *v32; // x24
  __int64 v33; // x0
  __int64 *v34; // x8
  __int64 v35; // x0
  __int64 *v36; // x9
  __int64 result; // x0
  __int64 v38; // [xsp-290h] [xbp-360h] BYREF
  __int64 v39; // [xsp-280h] [xbp-350h] BYREF
  __int64 v40; // [xsp-270h] [xbp-340h] BYREF
  __int64 v41; // [xsp-260h] [xbp-330h] BYREF
  __int64 v42; // [xsp-250h] [xbp-320h] BYREF
  __int64 v43; // [xsp-240h] [xbp-310h] BYREF
  __int64 v44; // [xsp-230h] [xbp-300h] BYREF
  __int64 v45; // [xsp-220h] [xbp-2F0h] BYREF
  __int64 v46; // [xsp-210h] [xbp-2E0h] BYREF
  __int64 v47; // [xsp-200h] [xbp-2D0h] BYREF
  __int64 v48; // [xsp-1F0h] [xbp-2C0h] BYREF
  __int64 v49; // [xsp-1E0h] [xbp-2B0h] BYREF
  __int64 v50; // [xsp-1D0h] [xbp-2A0h] BYREF
  __int64 v51; // [xsp-1C0h] [xbp-290h] BYREF
  __int64 v52; // [xsp-1A0h] [xbp-270h] BYREF
  _QWORD v53[6]; // [xsp-180h] [xbp-250h] BYREF
  __int64 v54; // [xsp-150h] [xbp-220h] BYREF
  _QWORD v55[2]; // [xsp-120h] [xbp-1F0h] BYREF
  __int64 v56; // [xsp-110h] [xbp-1E0h] BYREF
  int i; // [xsp-F0h] [xbp-1C0h]
  _BYTE v58[32]; // [xsp-E0h] [xbp-1B0h] BYREF
  __int64 v59; // [xsp-C0h] [xbp-190h] BYREF
  __int64 v60; // [xsp-B0h] [xbp-180h] BYREF
  _BYTE v61[32]; // [xsp-A0h] [xbp-170h] BYREF
  _BYTE v62[32]; // [xsp-80h] [xbp-150h] BYREF
  char v63; // [xsp-60h] [xbp-130h] BYREF
  unsigned __int64 v64; // [xsp-50h] [xbp-120h]
  unsigned __int16 v65; // [xsp-40h] [xbp-110h]
  __int64 v66; // [xsp-30h] [xbp-100h]
  _QWORD v67[5]; // [xsp-20h] [xbp-F0h] BYREF
  _QWORD *v68; // [xsp+8h] [xbp-C8h]
  __int64 *v69; // [xsp+10h] [xbp-C0h]
  __int64 *v70; // [xsp+18h] [xbp-B8h]
  __int64 *v71; // [xsp+20h] [xbp-B0h]
  __int64 *v72; // [xsp+28h] [xbp-A8h]
  __int64 *v73; // [xsp+30h] [xbp-A0h]
  _QWORD *v74; // [xsp+38h] [xbp-98h]
  __int64 *v75; // [xsp+40h] [xbp-90h]
  __int64 *v76; // [xsp+48h] [xbp-88h]
  __int64 *v77; // [xsp+50h] [xbp-80h]
  __int64 *v78; // [xsp+58h] [xbp-78h]
  __int64 *v79; // [xsp+60h] [xbp-70h]
  __int64 *v80; // [xsp+68h] [xbp-68h]
  __int64 *v81; // [xsp+70h] [xbp-60h]
  __int64 *v82; // [xsp+78h] [xbp-58h]
  char *v83; // [xsp+80h] [xbp-50h]
  __int64 *v84; // [xsp+88h] [xbp-48h]
  __int64 *v85; // [xsp+90h] [xbp-40h]
  __int64 *v86; // [xsp+98h] [xbp-38h]
  __int64 *v87; // [xsp+A0h] [xbp-30h]
  __int64 *v88; // [xsp+A8h] [xbp-28h]
  __int64 v89; // [xsp+B0h] [xbp-20h]
  __int64 *v90; // [xsp+B8h] [xbp-18h]
  __int64 v91; // [xsp+C0h] [xbp-10h]

  v91 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x5bce04*/
  if ( *(_DWORD *)sub_5BCDD8 >> 26 == 5 /*0x5bd640*/
    || *(_DWORD *)sub_5BCDD8 >> 21 == 1697
    || (loc_5BCDDC >> 10 == 3508160) ^ (loc_5BCDE0 >> 10 == 3508160)
     | (loc_5BCDDC >> 10 == 3508160 && loc_5BCDE0 >> 10 == 3508160) )
  {
    _ReadStatusReg(TPIDR_EL0); /*0x5bd584*/
    abort(); /*0x5bd598*/
  }
  v90 = &v60; /*0x5bce54*/
  v86 = &v59; /*0x5bce60*/
  v88 = &v56; /*0x5bce7c*/
  v87 = &v54; /*0x5bce90*/
  v68 = v53; /*0x5bcea4*/
  v85 = &v52; /*0x5bceb0*/
  v69 = &v51; /*0x5bcebc*/
  v84 = &v50; /*0x5bcec8*/
  v70 = &v49; /*0x5bced4*/
  v71 = &v48; /*0x5bcee0*/
  v80 = &v47; /*0x5bceec*/
  v72 = &v46; /*0x5bcef8*/
  v75 = &v45; /*0x5bcf04*/
  v73 = &v44; /*0x5bcf10*/
  v77 = &v43; /*0x5bcf1c*/
  v82 = &v42; /*0x5bcf28*/
  v76 = &v41; /*0x5bcf34*/
  v79 = &v40; /*0x5bcf40*/
  v78 = &v39; /*0x5bcf4c*/
  v81 = &v38; /*0x5bcf58*/
  v89 = a5; /*0x5bcf60*/
  v67[2] = a5; /*0x5bcf64*/
  v74 = v67; /*0x5bcf68*/
  v67[0] = a1; /*0x5bcf6c*/
  v66 = a2; /*0x5bcf70*/
  v65 = a3; /*0x5bcf74*/
  v64 = a4; /*0x5bcf78*/
  v5 = sub_5B8280(0, 15); /*0x5bcf84*/
  v83 = &v63; /*0x5bcffc*/
  v63 = (~(16 * v5) & 0x8F | (16 * v5) & 0x70) ^ (~byte_7AF3C8 & 0x8F | byte_7AF3C8 & 0x70) /*0x5bd000*/
      | ~(~(16 * v5) | ~byte_7AF3C8);
  sub_F6B78(v61, v66); /*0x5bd010*/
  sub_5CC2F0(v62, v61); /*0x5bd01c*/
  sub_5CC2F4((__int64)v61); /*0x5bd024*/
  sub_5CC2F8(v58, 12); /*0x5bd030*/
  *(_BYTE *)sub_5CC2FC(v58, 0) = 0; /*0x5bd048*/
  *(_BYTE *)sub_D81C8(v58, 1) = 0; /*0x5bd058*/
  v6 = HIBYTE(v65); /*0x5bd060*/
  *(_BYTE *)sub_D81C8(v58, 2) = v6; /*0x5bd070*/
  LOBYTE(v6) = v65; /*0x5bd078*/
  *(_BYTE *)sub_D81C8(v58, 3) = v6; /*0x5bd088*/
  for ( i = 0; i < 8; ++i ) /*0x5bd08c*/
  {
    v8 = v64 >> (56 - (~(~(_BYTE)i | 8) * (~(_BYTE)i & 8) + (i | 8) * (i & 8u))); /*0x5bd118*/
    *(_BYTE *)sub_D81C8(v58, i + 4) = v8; /*0x5bd144*/
  }
  v7 = v88; /*0x5bd0a4*/
  sub_F7B10(v55, v58); /*0x5bd168*/
  v9 = ((__int64 (__fastcall *)(__int64 *, _QWORD, _QWORD))loc_5BD64C)(v7, v55[0], v55[1]); /*0x5bd178*/
  v10 = v69; /*0x5bd180*/
  v11 = v68; /*0x5bd184*/
  ((void (__fastcall *)(__int64))loc_5BB788)(v9); /*0x5bd190*/
  v12 = sub_B6F98(v11); /*0x5bd1a0*/
  v53[5] = v13; /*0x5bd1a4*/
  v53[4] = v12; /*0x5bd1a8*/
  v14 = sub_5CC300(v12, v13, v62, v7, 0); /*0x5bd1c4*/
  v15 = v87; /*0x5bd1c8*/
  sub_120658(v87, v14, 0, 0, 0); /*0x5bd1e8*/
  sub_74539C(v11); /*0x5bd1f8*/
  sub_121F08(v15, *v74); /*0x5bd208*/
  sub_122DB4(v10, v15, -1); /*0x5bd224*/
  sub_11BF00(v10); /*0x5bd234*/
  sub_D2AC4((__int64)v10); /*0x5bd244*/
  sub_121460(v15); /*0x5bd24c*/
  *(_BYTE *)v84 = 0; /*0x5bd258*/
  v16 = v89; /*0x5bd25c*/
  sub_C445C(v89); /*0x5bd264*/
  v17 = sub_5CC304(v85); /*0x5bd26c*/
  sub_21AF94(v16, v17 + 15); /*0x5bd278*/
  sub_191F48(v89, v83); /*0x5bd290*/
  *(_BYTE *)v70 = HIBYTE(v65); /*0x5bd2a4*/
  sub_5CC308(v89); /*0x5bd2ac*/
  *(_BYTE *)v71 = v65; /*0x5bd2c0*/
  sub_19210C(v89); /*0x5bd2c8*/
  v18 = sub_D7F1C(v89); /*0x5bd2d4*/
  v19 = v72; /*0x5bd2d8*/
  *v72 = v18; /*0x5bd2dc*/
  v20 = v80; /*0x5bd2e0*/
  sub_5CC30C(v80, v19); /*0x5bd2e8*/
  v21 = sub_D7E30(v58); /*0x5bd2f0*/
  v22 = v75; /*0x5bd2f4*/
  *v75 = v21; /*0x5bd2f8*/
  v23 = sub_5CC310(v58); /*0x5bd300*/
  v24 = v73; /*0x5bd304*/
  *v73 = v23; /*0x5bd308*/
  v25 = ((__int64 (__fastcall *)(__int64, __int64, __int64, __int64))loc_5BE110)(v89, *v20, *v22, *v24); /*0x5bd31c*/
  *v77 = v25; /*0x5bd328*/
  v26 = v89; /*0x5bd32c*/
  v27 = sub_D7F1C(v89); /*0x5bd334*/
  v28 = v76; /*0x5bd338*/
  *v76 = v27; /*0x5bd33c*/
  v29 = v82; /*0x5bd340*/
  sub_5CC314(v82, v28); /*0x5bd348*/
  v30 = v85; /*0x5bd34c*/
  v31 = sub_1B2AF8(v85); /*0x5bd354*/
  v32 = v79; /*0x5bd358*/
  *v79 = v31; /*0x5bd35c*/
  v33 = sub_1B2BE4(v30); /*0x5bd364*/
  v34 = v78; /*0x5bd368*/
  *v78 = v33; /*0x5bd36c*/
  v35 = sub_22670C(v26, *v29, *v32, *v34); /*0x5bd380*/
  *v81 = v35; /*0x5bd390*/
  v36 = v84; /*0x5bd39c*/
  *(_BYTE *)v84 = 1; /*0x5bd3a0*/
  if ( (*(_BYTE *)v36 & 1) == 0 ) /*0x5bd3ac*/
    sub_C4640(v89); /*0x5bd4c0*/
  sub_C4640(v85); /*0x5bd4c8*/
  sub_5CC318(v87); /*0x5bd4d0*/
  ((void (__fastcall *)(__int64 *))loc_5BE6E4)(v88); /*0x5bd4d8*/
  sub_C4640(v58); /*0x5bd4e0*/
  result = ((__int64 (__fastcall *)(_BYTE *))loc_5BE6E4)(v62); /*0x5bd4e8*/
  _ReadStatusReg(TPIDR_EL0); /*0x5bd4ec*/
  return result; /*0x5bd51c*/
}