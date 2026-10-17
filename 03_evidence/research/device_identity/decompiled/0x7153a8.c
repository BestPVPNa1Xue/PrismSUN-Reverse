__int64 __usercall sub_7153A8@<X0>(__int64 a1@<X0>, __int64 a2@<X1>, __int64 a3@<X8>)
{
  __int64 result; // x0
  __int64 v4; // x0
  __int64 *v5; // x21
  __int64 v6; // x1
  __int64 v7; // x0
  __int64 v8; // x1
  __int64 v9; // x0
  __int64 v10; // x1
  __int64 v11; // x0
  __int64 v12; // x1
  __int64 v13; // x0
  __int64 v14; // x1
  __int64 v15; // x0
  __int64 v16; // x0
  char **v17; // x23
  __int64 v18; // x20
  __int64 v19; // x1
  __int64 v20; // x20
  __int64 v21; // x1
  __int64 v22; // x20
  __int64 v23; // x0
  __int64 v24; // x1
  __int64 v25; // x20
  __int64 v26; // x1
  __int64 v27; // x0
  __int64 v28; // x0
  __int64 *v29; // x8
  __int64 v30; // x0
  unsigned int v31; // w20
  __int64 v32; // x19
  __int64 v33; // x0
  __int64 v34; // x1
  __int64 v35; // x19
  __int64 v36; // x0
  __int64 v37; // x0
  __int64 v38; // x1
  __int64 v39; // x0
  __int64 v40; // x0
  __int64 v41; // x0
  unsigned int v42; // w19
  __int64 v43; // x0
  __int64 *v44; // x8
  __int64 *v45; // x19
  __int64 v46; // x0
  __int64 v47; // x0
  __int64 v48; // x19
  __int64 v49; // x0
  __int64 v50; // x1
  __int64 v51; // x19
  __int64 v52; // x0
  __int64 v53; // x1
  __int64 v54; // x19
  __int64 v55; // x0
  __int64 v56; // x1
  __int64 v57; // x19
  __int64 v58; // x1
  __int64 v59; // x19
  __int64 v60; // x0
  __int64 v61; // x19
  __int64 v62; // x0
  __int64 v63; // x19
  __int64 v64; // x0
  __int64 v65; // x19
  __int64 v66; // x0
  __int64 v67; // x0
  __int64 v68; // [xsp-2E0h] [xbp-3B0h] BYREF
  __int64 v69; // [xsp-2D0h] [xbp-3A0h] BYREF
  __int64 v70; // [xsp-2C0h] [xbp-390h] BYREF
  __int64 v71; // [xsp-2A0h] [xbp-370h] BYREF
  __int64 v72; // [xsp-280h] [xbp-350h] BYREF
  __int64 v73; // [xsp-260h] [xbp-330h] BYREF
  __int64 v74; // [xsp-250h] [xbp-320h] BYREF
  __int64 v75; // [xsp-230h] [xbp-300h] BYREF
  __int64 v76; // [xsp-220h] [xbp-2F0h] BYREF
  __int64 v77; // [xsp-210h] [xbp-2E0h] BYREF
  __int64 v78; // [xsp-1F0h] [xbp-2C0h] BYREF
  __int64 v79; // [xsp-1D0h] [xbp-2A0h] BYREF
  _BYTE v80[32]; // [xsp-1B0h] [xbp-280h] BYREF
  __int64 v81; // [xsp-190h] [xbp-260h] BYREF
  __int64 v82; // [xsp-180h] [xbp-250h]
  __int64 v83; // [xsp-170h] [xbp-240h] BYREF
  _QWORD v84[4]; // [xsp-160h] [xbp-230h] BYREF
  char v85; // [xsp-140h] [xbp-210h]
  __int64 v86; // [xsp-130h] [xbp-200h] BYREF
  __int64 v87; // [xsp-110h] [xbp-1E0h] BYREF
  __int64 v88; // [xsp-100h] [xbp-1D0h] BYREF
  __int64 v89; // [xsp-F0h] [xbp-1C0h] BYREF
  __int64 v90; // [xsp-E0h] [xbp-1B0h] BYREF
  __int64 v91; // [xsp-D0h] [xbp-1A0h] BYREF
  __int64 v92; // [xsp-C0h] [xbp-190h] BYREF
  __int64 v93; // [xsp-B0h] [xbp-180h] BYREF
  __int64 v94; // [xsp-A0h] [xbp-170h] BYREF
  __int64 v95; // [xsp-90h] [xbp-160h] BYREF
  __int64 v96; // [xsp-80h] [xbp-150h] BYREF
  __int64 v97; // [xsp-60h] [xbp-130h]
  __int64 v98; // [xsp-50h] [xbp-120h] BYREF
  __int64 v99; // [xsp-40h] [xbp-110h]
  __int64 v100; // [xsp-30h] [xbp-100h]
  __int64 v101; // [xsp-20h] [xbp-F0h]
  __int64 v102; // [xsp-10h] [xbp-E0h]
  char **v103; // [xsp+0h] [xbp-D0h]
  __int64 *v104; // [xsp+8h] [xbp-C8h]
  __int64 *v105; // [xsp+10h] [xbp-C0h]
  __int64 *v106; // [xsp+18h] [xbp-B8h]
  __int64 *v107; // [xsp+20h] [xbp-B0h]
  __int64 *v108; // [xsp+28h] [xbp-A8h]
  __int64 *v109; // [xsp+30h] [xbp-A0h]
  __int64 *v110; // [xsp+38h] [xbp-98h]
  __int64 *v111; // [xsp+40h] [xbp-90h]
  __int64 *v112; // [xsp+48h] [xbp-88h]
  __int64 *v113; // [xsp+50h] [xbp-80h]
  __int64 *v114; // [xsp+58h] [xbp-78h]
  __int64 *v115; // [xsp+60h] [xbp-70h]
  __int64 *v116; // [xsp+68h] [xbp-68h]
  __int64 *v117; // [xsp+70h] [xbp-60h]
  __int64 *v118; // [xsp+78h] [xbp-58h]
  __int64 *v119; // [xsp+80h] [xbp-50h]
  __int64 *v120; // [xsp+88h] [xbp-48h]
  __int64 *v121; // [xsp+90h] [xbp-40h]
  __int64 *v122; // [xsp+98h] [xbp-38h]
  __int64 *v123; // [xsp+A0h] [xbp-30h]
  __int64 *v124; // [xsp+A8h] [xbp-28h]
  __int64 *v125; // [xsp+B0h] [xbp-20h]
  __int64 *v126; // [xsp+B8h] [xbp-18h]
  __int64 v127; // [xsp+C0h] [xbp-10h]

  v127 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x7153d4*/
  if ( *(_DWORD *)sub_7153A8 >> 26 == 5 /*0x71605c*/
    || *(_DWORD *)sub_7153A8 >> 21 == 1697
    || loc_7153AC >> 10 == 3508160
    || loc_7153B0 >> 10 == 3508160 )
  {
    _ReadStatusReg(TPIDR_EL0); /*0x715fc4*/
    abort(); /*0x715fd8*/
  }
  v117 = &v98; /*0x715400*/
  v126 = &v96; /*0x715414*/
  v123 = &v95; /*0x715420*/
  v118 = &v94; /*0x71542c*/
  v125 = &v93; /*0x715438*/
  v124 = &v92; /*0x715444*/
  v122 = &v91; /*0x715450*/
  v121 = &v90; /*0x71545c*/
  v120 = &v89; /*0x715468*/
  v103 = (char **)&v88; /*0x715474*/
  v119 = &v86; /*0x715488*/
  v104 = &v83; /*0x7154a4*/
  v116 = &v79; /*0x7154c8*/
  v105 = &v78; /*0x7154d4*/
  v115 = &v77; /*0x7154e0*/
  v108 = &v76; /*0x7154ec*/
  v106 = &v75; /*0x7154f8*/
  v109 = &v74; /*0x715504*/
  v107 = &v73; /*0x715510*/
  v114 = &v72; /*0x71551c*/
  v113 = &v71; /*0x715528*/
  v112 = &v70; /*0x715534*/
  v110 = &v69; /*0x715540*/
  v111 = &v68; /*0x71554c*/
  v102 = a3; /*0x715554*/
  v101 = a1; /*0x715558*/
  v100 = a2; /*0x71555c*/
  if ( (sub_72583C(a2) & 1) != 0 ) /*0x715568*/
  {
    v99 = ((__int64 (__fastcall *)(__int64))sub_6B0998)(v100); /*0x715584*/
    if ( (unsigned int)sub_2A7E24(v99) == 1 && (v97 = sub_2A7E9C(v99, 0), (unsigned int)sub_725840(v97)) ) /*0x7155c4*/
    {
      v4 = sub_2A6598(v97); /*0x7155ec*/
      v5 = v126; /*0x7155f4*/
      sub_C7BE8(v126, v4); /*0x7155fc*/
      if ( (unsigned __int64)sub_725844(v5) >= 8 ) /*0x715610*/
      {
        v6 = ((__int64 (*)(void))sub_2A8358)(); /*0x715644*/
        v7 = ((__int64 (__fastcall *)(__int64 *, __int64))sub_4DAA54)(v125, v6); /*0x715650*/
        v8 = sub_2A8358(v7); /*0x715658*/
        v9 = sub_725848(v124, v8); /*0x715668*/
        v10 = sub_72584C(v9); /*0x715670*/
        v11 = sub_725850(v122, v10); /*0x71567c*/
        v12 = sub_2A8358(v11); /*0x715684*/
        v13 = ((__int64 (__fastcall *)(__int64 *, __int64))sub_4DAA54)(v121, v12); /*0x715694*/
        v14 = sub_2A8358(v13); /*0x71569c*/
        ((void (__fastcall *)(__int64 *, __int64))sub_4DAA54)(v120, v14); /*0x7156ac*/
        v15 = ((__int64 (__fastcall *)(__int64 *))loc_718418)(&v87); /*0x7156b4*/
        v16 = ((__int64 (__fastcall *)(__int64))loc_719668)(v15); /*0x7156c4*/
        v17 = v103; /*0x7156cc*/
        *v103 = (char *)v16; /*0x7156d0*/
        v18 = ((__int64 (__fastcall *)(__int64 *))sub_4DAE04)(v124); /*0x7156dc*/
        v19 = sub_2A829C(*v17); /*0x7156e8*/
        sub_2A7FEC(v18, v19); /*0x715700*/
        v20 = ((__int64 (__fastcall *)(__int64 *))sub_4DAE04)(v124); /*0x715714*/
        v21 = sub_2A81D8(1.0); /*0x715724*/
        sub_2A7FEC(v20, v21); /*0x71573c*/
        sub_4DF3C8((__int64)v119); /*0x71574c*/
        v85 = 1; /*0x715758*/
        if ( (sub_CB11C(v119) & 1) != 0 ) /*0x715764*/
        {
          v85 = 0; /*0x715768*/
          sub_4DFC3C(v84); /*0x715770*/
          sub_CFD4C(v119, v84); /*0x715780*/
          sub_74539C(v84); /*0x715788*/
        }
        v22 = ((__int64 (__fastcall *)(__int64 *))sub_4DAE04)(v122); /*0x715850*/
        v23 = sub_141054(v119); /*0x715858*/
        v24 = sub_725854(v23); /*0x715860*/
        sub_725858(v22, v24); /*0x715874*/
        v25 = sub_72585C(v122); /*0x715888*/
        v26 = sub_2A814C(v85 & 1); /*0x715898*/
        v27 = sub_725860(v25, v26); /*0x7158ac*/
        v28 = sub_3B8C40(v27); /*0x7158b8*/
        v29 = v104; /*0x7158c4*/
        *v104 = v28; /*0x7158c8*/
        if ( (((__int64 (__fastcall *)(__int64))sub_4D92B4)(*v29) & 1) != 0 ) /*0x7158dc*/
        {
          sub_F7768(v116); /*0x7159b4*/
          sub_1DB574(v116, v119); /*0x7159c0*/
          sub_1DB574(v116, v126); /*0x7159d0*/
          sub_746084((int)v116, *v103); /*0x7159e4*/
          v32 = ((__int64 (__fastcall *)(__int64 *))sub_4DAE04)(v121); /*0x7159f4*/
          v33 = sub_141054(v126); /*0x7159fc*/
          v34 = sub_2A829C(v33); /*0x715a04*/
          sub_725864(v32, v34); /*0x715a18*/
          v35 = ((__int64 (__fastcall *)(__int64 *))sub_4DAE04)(v121); /*0x715a2c*/
          v36 = sub_725868(*v104); /*0x715a38*/
          sub_5BA370(v36, v116); /*0x715a4c*/
          v37 = sub_141054(v105); /*0x715a58*/
          v38 = sub_2A829C(v37); /*0x715a60*/
          sub_72586C(v35, v38); /*0x715a74*/
          v39 = sub_74539C(v105); /*0x715a84*/
          ((void (__fastcall *)(__int64))sub_306DF0)(v39); /*0x715a8c*/
          if ( (((__int64 (__fastcall *)(__int64 *))loc_6AE7D0)(v115) & 1) != 0 ) /*0x715aac*/
          {
            v43 = sub_725934(v115); /*0x715bb8*/
            v44 = v107; /*0x715bc0*/
            *v107 = v43; /*0x715bc4*/
            sub_37843C(*v44, (__int64)v114); /*0x715bd0*/
            sub_2E5C18(*v107); /*0x715be4*/
            ((void (__fastcall *)(__int64))loc_37FB88)(*v107); /*0x715bf8*/
            v45 = v112; /*0x715c00*/
            v46 = ((__int64 (__fastcall *)(__int64 *))sub_71BBB4)(v112); /*0x715c08*/
            *v110 = v46; /*0x715c10*/
            v47 = ((__int64 (__fastcall *)(__int64 *))sub_71C078)(v45); /*0x715c18*/
            *v111 = v47; /*0x715c20*/
            v48 = ((__int64 (__fastcall *)(__int64 *))sub_4DAE04)(v120); /*0x715c2c*/
            v49 = sub_725938(v113); /*0x715c34*/
            v50 = sub_72593C(v49); /*0x715c3c*/
            sub_2A7FEC(v48, v50); /*0x715c50*/
            v51 = ((__int64 (__fastcall *)(__int64 *))sub_4DAE04)(v120); /*0x715c64*/
            v52 = sub_141054(v114); /*0x715c6c*/
            v53 = sub_725940(v52); /*0x715c74*/
            sub_725944(v51, v53); /*0x715c88*/
            v54 = ((__int64 (__fastcall *)(__int64 *))sub_4DAE04)(v120); /*0x715c9c*/
            v55 = sub_725948(*v110); /*0x715ca8*/
            v56 = sub_2A829C(v55); /*0x715cb0*/
            sub_72594C(v54, v56); /*0x715cc4*/
            v57 = ((__int64 (__fastcall *)(__int64 *))sub_4DAE04)(v120); /*0x715cd4*/
            v58 = sub_2A814C(*(unsigned __int8 *)*v111); /*0x715ce8*/
            sub_2A7FEC(v57, v58); /*0x715cfc*/
            sub_725950(v112); /*0x715d08*/
            sub_74539C(v113); /*0x715d10*/
            sub_74539C(v114); /*0x715d18*/
            *(_DWORD *)v117 = 0; /*0x715d20*/
          }
          else
          {
            v40 = ((__int64 (__fastcall *)(__int64 *))loc_71AF14)(v106); /*0x715ab8*/
            v41 = ((__int64 (__fastcall *)(__int64))loc_71B870)(v40); /*0x715ac8*/
            *v108 = v41; /*0x715ad4*/
            v42 = sub_725870(0xBBAu); /*0x715ae0*/
            sub_C7BE8(v109, *v108); /*0x715af4*/
            ((void (__fastcall *)(_QWORD, __int64 *))sub_6B00FC)(v42, v109); /*0x715b10*/
            sub_725874(v109); /*0x715b1c*/
            *(_DWORD *)v117 = 1; /*0x715b28*/
          }
          sub_3078CC(v115); /*0x715d30*/
          if ( !*(_DWORD *)v117 ) /*0x715d38*/
          {
            v59 = ((__int64 (__fastcall *)(__int64 *))sub_4DAE04)(v125); /*0x715d50*/
            v60 = ((__int64 (__fastcall *)(__int64 *))sub_4DB0C4)(v124); /*0x715d58*/
            sub_725954(v59, v60); /*0x715d64*/
            v61 = ((__int64 (__fastcall *)(__int64 *))sub_4DAE04)(v125); /*0x715d78*/
            v62 = sub_725958(v122); /*0x715d80*/
            sub_72595C(v61, v62); /*0x715d8c*/
            v63 = ((__int64 (__fastcall *)(__int64 *))sub_4DAE04)(v125); /*0x715da0*/
            v64 = ((__int64 (__fastcall *)(__int64 *))sub_4DB0C4)(v121); /*0x715da8*/
            sub_2A7FEC(v63, v64); /*0x715db4*/
            v65 = ((__int64 (__fastcall *)(__int64 *))sub_4DAE04)(v125); /*0x715dc8*/
            v66 = ((__int64 (__fastcall *)(__int64 *))sub_4DB0C4)(v120); /*0x715dd0*/
            sub_725960(v65, v66); /*0x715ddc*/
            v67 = ((__int64 (__fastcall *)(__int64 *))sub_4DB0C4)(v125); /*0x715de8*/
            ((void (__fastcall *)(__int64, __int64))sub_634E84)(19, v67); /*0x715df8*/
            *(_DWORD *)v117 = 1; /*0x715e08*/
          }
          sub_74539C(v116); /*0x715ea0*/
        }
        else
        {
          v30 = ((__int64 (__fastcall *)(__int64 *))loc_719A98)(&v81); /*0x7158ec*/
          v82 = ((__int64 (__fastcall *)(__int64))loc_71A890)(v30); /*0x715904*/
          v31 = sub_2B2208(0x1775u); /*0x715910*/
          sub_C7BE8(v80, v82); /*0x715920*/
          ((void (__fastcall *)(_QWORD, _BYTE *))sub_6B00FC)(v31, v80); /*0x71593c*/
          sub_74539C(v80); /*0x715948*/
          *(_DWORD *)v117 = 1; /*0x715954*/
        }
        sub_74539C(v119); /*0x715eb8*/
        sub_2D94E4(v120); /*0x715ec0*/
        sub_2D94E4(v121); /*0x715ec8*/
        sub_7259CC(v122); /*0x715ed0*/
        sub_2D94E4(v124); /*0x715ed8*/
        sub_2D94E4(v125); /*0x715ee0*/
        v5 = v126; /*0x715ee4*/
      }
      else
      {
        ((void (*)(void))sub_6D49A8)(); /*0x715624*/
        *(_DWORD *)v117 = 1; /*0x715634*/
      }
      result = sub_725A3C(v5); /*0x715f4c*/
    }
    else
    {
      result = ((__int64 (*)(void))sub_6D49A8)(); /*0x71559c*/
      *(_DWORD *)v117 = 1; /*0x7155a8*/
    }
  }
  else
  {
    result = ((__int64 (*)(void))sub_6D49A8)(); /*0x715574*/
  }
  _ReadStatusReg(TPIDR_EL0); /*0x715f6c*/
  return result; /*0x715f9c*/
}