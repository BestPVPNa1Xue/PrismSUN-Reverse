__int64 __fastcall sub_4C9D30(__int64 a1)
{
  __int64 result; // x0
  __int64 v2; // x0
  __int64 *v3; // x21
  __int64 v4; // x1
  __int64 v5; // x0
  __int64 v6; // x0
  _QWORD *v7; // x19
  __int64 v8; // x20
  __int64 v9; // x0
  char *v10; // x0
  unsigned __int64 v11; // x0
  char v12; // w0
  __int64 *v13; // x19
  __int64 v14; // x0
  __int64 v15; // x0
  __int64 *v16; // x19
  __int64 v17; // x0
  __int64 *v18; // x9
  __int64 *v19; // x19
  __int64 v20; // x0
  __int64 v21; // x0
  __int64 v22; // x0
  __int64 *v23; // x9
  __int64 v24; // x0
  __int64 v25; // x0
  __int64 v26; // x0
  __int64 *v27; // x9
  __int64 v28; // x0
  __int64 *v29; // x8
  __int64 v30; // x1
  __int64 v31; // [xsp-280h] [xbp-360h] BYREF
  __int64 v32; // [xsp-270h] [xbp-350h] BYREF
  __int64 v33; // [xsp-260h] [xbp-340h] BYREF
  __int64 v34; // [xsp-250h] [xbp-330h] BYREF
  __int64 *v35; // [xsp-240h] [xbp-320h]
  __int64 v36; // [xsp-230h] [xbp-310h] BYREF
  __int64 v37; // [xsp-220h] [xbp-300h] BYREF
  __int64 v38; // [xsp-210h] [xbp-2F0h] BYREF
  __int64 v39; // [xsp-200h] [xbp-2E0h] BYREF
  __int64 v40; // [xsp-1F0h] [xbp-2D0h] BYREF
  __int64 v41; // [xsp-1E0h] [xbp-2C0h] BYREF
  __int64 v42; // [xsp-1D0h] [xbp-2B0h] BYREF
  __int64 v43; // [xsp-1C0h] [xbp-2A0h] BYREF
  __int64 v44; // [xsp-1B0h] [xbp-290h] BYREF
  __int64 v45; // [xsp-1A0h] [xbp-280h] BYREF
  __int64 v46; // [xsp-190h] [xbp-270h] BYREF
  _QWORD v47[6]; // [xsp-170h] [xbp-250h] BYREF
  __int64 v48; // [xsp-140h] [xbp-220h] BYREF
  __int64 v49; // [xsp-130h] [xbp-210h] BYREF
  __int64 v50; // [xsp-120h] [xbp-200h] BYREF
  __int64 *v51; // [xsp-110h] [xbp-1F0h]
  __int64 v52; // [xsp-100h] [xbp-1E0h] BYREF
  __int64 v53; // [xsp-F0h] [xbp-1D0h] BYREF
  __int64 v54; // [xsp-E0h] [xbp-1C0h] BYREF
  __int64 v55; // [xsp-D0h] [xbp-1B0h]
  __int64 v56; // [xsp-C0h] [xbp-1A0h] BYREF
  _QWORD v57[2]; // [xsp-B0h] [xbp-190h] BYREF
  _QWORD *v58; // [xsp-A0h] [xbp-180h]
  __int64 v59; // [xsp-90h] [xbp-170h] BYREF
  __int64 v60; // [xsp-70h] [xbp-150h] BYREF
  __int64 v61; // [xsp-60h] [xbp-140h] BYREF
  __int64 v62; // [xsp-50h] [xbp-130h] BYREF
  _BYTE v63[16]; // [xsp-40h] [xbp-120h] BYREF
  _QWORD v64[6]; // [xsp-30h] [xbp-110h] BYREF
  __int64 *v65; // [xsp+0h] [xbp-E0h]
  __int64 *v66; // [xsp+8h] [xbp-D8h]
  __int64 *v67; // [xsp+10h] [xbp-D0h]
  __int64 *v68; // [xsp+18h] [xbp-C8h]
  __int64 *v69; // [xsp+20h] [xbp-C0h]
  __int64 *v70; // [xsp+28h] [xbp-B8h]
  __int64 *v71; // [xsp+30h] [xbp-B0h]
  __int64 *v72; // [xsp+38h] [xbp-A8h]
  __int64 *v73; // [xsp+40h] [xbp-A0h]
  __int64 *v74; // [xsp+48h] [xbp-98h]
  __int64 *v75; // [xsp+50h] [xbp-90h]
  __int64 *v76; // [xsp+58h] [xbp-88h]
  __int64 *v77; // [xsp+60h] [xbp-80h]
  __int64 *v78; // [xsp+68h] [xbp-78h]
  __int64 *v79; // [xsp+70h] [xbp-70h]
  __int64 *v80; // [xsp+78h] [xbp-68h]
  __int64 *v81; // [xsp+80h] [xbp-60h]
  __int64 v82; // [xsp+88h] [xbp-58h]
  __int64 *v83; // [xsp+90h] [xbp-50h]
  __int64 *v84; // [xsp+98h] [xbp-48h]
  _QWORD *v85; // [xsp+A0h] [xbp-40h]
  __int64 *v86; // [xsp+A8h] [xbp-38h]
  __int64 *v87; // [xsp+B0h] [xbp-30h]
  __int64 *v88; // [xsp+B8h] [xbp-28h]
  __int64 *v89; // [xsp+C0h] [xbp-20h]
  _QWORD *v90; // [xsp+C8h] [xbp-18h]
  __int64 v91; // [xsp+D0h] [xbp-10h]

  v91 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x4c9d58*/
  if ( *(_DWORD *)sub_4C9D30 >> 26 == 5 /*0x4ca778*/
    || *(_DWORD *)sub_4C9D30 >> 21 == 1697
    || loc_4C9D34 >> 10 == 3508160
    || loc_4C9D38 >> 10 == 3508160 )
  {
    _ReadStatusReg(TPIDR_EL0); /*0x4ca6f4*/
    abort(); /*0x4ca708*/
  }
  v90 = v64; /*0x4c9d74*/
  v88 = &v62; /*0x4c9d88*/
  v86 = &v61; /*0x4c9d94*/
  v83 = &v60; /*0x4c9da0*/
  v89 = &v59; /*0x4c9dac*/
  v87 = &v52; /*0x4c9de8*/
  v67 = &v50; /*0x4c9dfc*/
  v66 = &v49; /*0x4c9e08*/
  v65 = &v48; /*0x4c9e14*/
  v85 = v47; /*0x4c9e28*/
  v84 = &v46; /*0x4c9e34*/
  v80 = &v45; /*0x4c9e40*/
  v72 = &v44; /*0x4c9e4c*/
  v79 = &v43; /*0x4c9e58*/
  v77 = &v42; /*0x4c9e64*/
  v75 = &v41; /*0x4c9e70*/
  v81 = &v40; /*0x4c9e7c*/
  v69 = &v39; /*0x4c9e88*/
  v78 = &v38; /*0x4c9e94*/
  v76 = &v37; /*0x4c9ea0*/
  v74 = &v36; /*0x4c9eac*/
  v73 = &v34; /*0x4c9ec0*/
  v71 = &v33; /*0x4c9ecc*/
  v70 = &v32; /*0x4c9ed8*/
  v68 = &v31; /*0x4c9ee4*/
  v64[4] = a1; /*0x4c9eec*/
  v82 = a1; /*0x4c9ef4*/
  result = sub_56B834(); /*0x4c9ef8*/
  if ( (result & 1) != 0 ) /*0x4c9efc*/
  {
    v2 = sub_3B8C40(); /*0x4c9f10*/
    result = sub_4D92B4(v2); /*0x4c9f14*/
    if ( (result & 1) != 0 ) /*0x4c9f18*/
    {
      sub_2C031C(v90); /*0x4c9f24*/
      ((void (__fastcall *)(_BYTE *, __int64))loc_4113FC)(v63, v82 + 136); /*0x4c9f34*/
      if ( (((__int64 (__fastcall *)(__int64))loc_4D96FC)(v82 + 176) & 1) != 0 ) /*0x4c9f4c*/
      {
        *(_DWORD *)v83 = 1; /*0x4c9f60*/
      }
      else
      {
        ((void (__fastcall *)(_QWORD *, __int64))loc_4D99C8)(v90, v82 + 176); /*0x4c9f8c*/
        *(_DWORD *)v83 = 0; /*0x4c9f94*/
      }
      ((void (__fastcall *)(_BYTE *))loc_415B1C)(v63); /*0x4c9fa4*/
      v3 = v89; /*0x4c9fb0*/
      if ( !*(_DWORD *)v83 ) /*0x4c9fac*/
      {
        sub_2C031C(v89); /*0x4c9fc0*/
        v58 = v90; /*0x4c9fc8*/
        v57[0] = ((__int64 (__fastcall *)(_QWORD *))loc_4D76E4)(v90); /*0x4c9fd4*/
        v56 = ((__int64 (__fastcall *)(_QWORD *))loc_4D7B90)(v58); /*0x4c9fe0*/
        while ( (((__int64 (__fastcall *)(_QWORD *, __int64 *))loc_4D7F40)(v57, &v56) & 1) != 0 ) /*0x4c9ff8*/
        {
          v55 = ((__int64 (__fastcall *)(_QWORD *))loc_4D83C8)(v57); /*0x4ca01c*/
          v54 = ((__int64 (__fastcall *)(__int64, __int64))loc_4DA164)(v82 + 200, v55); /*0x4ca038*/
          v53 = ((__int64 (__fastcall *)(__int64))loc_4DA6A8)(v82 + 200); /*0x4ca048*/
          if ( (((__int64 (__fastcall *)(__int64 *, __int64 *))loc_4D9C9C)(&v54, &v53) & 1) != 0 ) /*0x4ca05c*/
            sub_56B838(v3, v55); /*0x4ca070*/
          ((void (__fastcall *)(_QWORD *))loc_4D8768)(v57); /*0x4ca0c0*/
        }
        *(_DWORD *)v83 = 2; /*0x4ca00c*/
        if ( (((__int64 (__fastcall *)(__int64 *))loc_4D96FC)(v3) & 1) != 0 ) /*0x4ca0dc*/
        {
          *(_DWORD *)v83 = 1; /*0x4ca0ec*/
        }
        else
        {
          v4 = sub_2A8358(); /*0x4ca0fc*/
          sub_4DAA54(v87, v4); /*0x4ca10c*/
          v51 = v3; /*0x4ca110*/
          v5 = ((__int64 (__fastcall *)(__int64 *))loc_4D76E4)(v3); /*0x4ca118*/
          *v67 = v5; /*0x4ca120*/
          v6 = ((__int64 (__fastcall *)(__int64 *))loc_4D7B90)(v51); /*0x4ca128*/
          *v66 = v6; /*0x4ca130*/
          while ( (((__int64 (__fastcall *)(__int64 *))loc_4D7F40)(v67) & 1) != 0 ) /*0x4ca144*/
          {
            v9 = ((__int64 (__fastcall *)(__int64 *))loc_4D83C8)(v67); /*0x4ca180*/
            *v65 = v9; /*0x4ca188*/
            v47[4] = sub_2A8358(); /*0x4ca198*/
            sub_2A81D8((double)*(int *)*v65); /*0x4ca1b0*/
            sub_2A7FEC(); /*0x4ca1c8*/
            sub_2A81D8((double)*(__int64 *)(*v65 + 8)); /*0x4ca1e8*/
            sub_2A7FEC(); /*0x4ca204*/
            v10 = (char *)sub_141054(*v65 + 16); /*0x4ca220*/
            sub_2A829C(v10); /*0x4ca228*/
            sub_2A7FEC(); /*0x4ca244*/
            sub_4DAE04(v87); /*0x4ca254*/
            sub_2A7FEC(); /*0x4ca260*/
            ((void (__fastcall *)(__int64 *))loc_4D8768)(v67); /*0x4ca278*/
            v3 = v89; /*0x4ca27c*/
          }
          *(_DWORD *)v83 = 4; /*0x4ca158*/
          v7 = v85; /*0x4ca15c*/
          v8 = (__int64)v84; /*0x4ca160*/
          ((void (__fastcall *)(_QWORD *))loc_4D03D4)(v85); /*0x4ca2a0*/
          v11 = sub_4DB0C4((unsigned __int64 *)v87); /*0x4ca2a8*/
          ((void (__fastcall *)(_QWORD *, __int64, unsigned __int64))loc_5959C8)(v7, 48, v11); /*0x4ca2b8*/
          sub_596028(v7); /*0x4ca2cc*/
          v12 = sub_CB11C(v8); /*0x4ca2d8*/
          if ( (v12 & 1) != 0 ) /*0x4ca2dc*/
          {
            sub_56B83C(v80, v82 + 136); /*0x4ca2ec*/
            v13 = v72; /*0x4ca2f4*/
            *v72 = (__int64)v3; /*0x4ca2f8*/
            v14 = ((__int64 (__fastcall *)(__int64))loc_4D76E4)(*v13); /*0x4ca300*/
            *v79 = v14; /*0x4ca308*/
            v15 = ((__int64 (__fastcall *)(__int64))loc_4D7B90)(*v13); /*0x4ca310*/
            *v77 = v15; /*0x4ca318*/
            while ( 1 ) /*0x4ca320*/
            {
              v16 = v79; /*0x4ca320*/
              if ( (((__int64 (__fastcall *)(__int64 *, __int64 *))loc_4D7F40)(v79, v77) & 1) == 0 ) /*0x4ca330*/
                break; /*0x4ca330*/
              v17 = ((__int64 (__fastcall *)(__int64 *))loc_4D83C8)(v16); /*0x4ca384*/
              v18 = v75; /*0x4ca388*/
              *v75 = v17; /*0x4ca38c*/
              sub_56B840(v82 + 176, *v18); /*0x4ca39c*/
              sub_56B844(v79); /*0x4ca3ac*/
            }
            *(_DWORD *)v83 = 6; /*0x4ca33c*/
            *(_DWORD *)v83 = 1; /*0x4ca3d8*/
            ((void (__fastcall *)(__int64 *))loc_415B1C)(v80); /*0x4ca3e0*/
          }
          else if ( (sub_591B70((__int64)&unk_7C06AC, 5u, v8) & 1) != 0 ) /*0x4ca414*/
          {
            v35 = v89; /*0x4ca540*/
            v24 = sub_56B854(v89); /*0x4ca548*/
            *v73 = v24; /*0x4ca550*/
            v25 = ((__int64 (__fastcall *)(__int64 *))loc_4D7B90)(v35); /*0x4ca558*/
            *v71 = v25; /*0x4ca560*/
            while ( (((__int64 (__fastcall *)(__int64 *, __int64 *))loc_4D7F40)(v73, v71) & 1) != 0 ) /*0x4ca578*/
            {
              v26 = ((__int64 (__fastcall *)(__int64 *))loc_4D83C8)(v73); /*0x4ca594*/
              v27 = v70; /*0x4ca598*/
              *v70 = v26; /*0x4ca59c*/
              v28 = sub_56B858(v82 + 200, *v27); /*0x4ca5ac*/
              v29 = v68; /*0x4ca5b4*/
              *v68 = v28; /*0x4ca5b8*/
              v29[1] = v30; /*0x4ca5bc*/
              sub_56B85C(v73); /*0x4ca5c8*/
            }
            *(_DWORD *)v83 = 10; /*0x4ca588*/
            *(_DWORD *)v83 = 0; /*0x4ca5f8*/
          }
          else
          {
            ((void (__fastcall *)(__int64 *, __int64))loc_4113FC)(v81, v82 + 136); /*0x4ca428*/
            v19 = v69; /*0x4ca434*/
            *v69 = (__int64)v89; /*0x4ca438*/
            v20 = ((__int64 (__fastcall *)(__int64))loc_4D76E4)(*v19); /*0x4ca440*/
            *v78 = v20; /*0x4ca448*/
            v21 = ((__int64 (__fastcall *)(__int64))loc_4D7B90)(*v19); /*0x4ca450*/
            *v76 = v21; /*0x4ca458*/
            while ( (sub_56B848(v78, v76) & 1) != 0 ) /*0x4ca470*/
            {
              v22 = ((__int64 (__fastcall *)(__int64 *))loc_4D83C8)(v78); /*0x4ca4b8*/
              v23 = v74; /*0x4ca4bc*/
              *v74 = v22; /*0x4ca4c0*/
              ((void (__fastcall *)(__int64, __int64))loc_4D8B24)(v82 + 176, *v23); /*0x4ca4d0*/
              sub_56B84C(v78); /*0x4ca4e8*/
            }
            *(_DWORD *)v83 = 8; /*0x4ca484*/
            *(_DWORD *)v83 = 1; /*0x4ca518*/
            sub_56B850(v81); /*0x4ca520*/
          }
          sub_74539C(v84); /*0x4ca608*/
          ((void (__fastcall *)(_QWORD *))loc_4D0934)(v85); /*0x4ca610*/
          sub_2D94E4(v87); /*0x4ca618*/
          v3 = v89; /*0x4ca61c*/
        }
        sub_2CB290(v3); /*0x4ca62c*/
      }
      result = sub_2CB290(v90); /*0x4ca638*/
    }
  }
  _ReadStatusReg(TPIDR_EL0); /*0x4ca644*/
  return result; /*0x4ca674*/
}