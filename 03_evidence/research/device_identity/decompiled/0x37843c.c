__int64 __usercall sub_37843C@<X0>(__int64 a1@<X0>, __int64 a2@<X8>)
{
  __int64 v2; // x0
  _QWORD *v3; // x19
  __int64 v4; // x0
  __int64 v5; // x0
  __int64 v6; // x0
  unsigned int v7; // w0
  unsigned int *v8; // x22
  __int64 v9; // x0
  __int64 v10; // x0
  __int64 *v11; // x8
  __int64 v12; // x0
  __int64 v13; // x0
  __int64 v14; // x0
  __int64 *v15; // x8
  __int64 v16; // x0
  __int64 v17; // x0
  __int64 *v18; // x8
  __int64 v19; // x21
  __int64 v20; // x0
  __int64 v21; // x0
  __int64 *v22; // x8
  __int64 *v23; // x10
  __int64 result; // x0
  __int64 v25; // [xsp-220h] [xbp-290h] BYREF
  __int64 v26; // [xsp-210h] [xbp-280h] BYREF
  __int64 v27; // [xsp-200h] [xbp-270h] BYREF
  __int64 v28; // [xsp-1F0h] [xbp-260h] BYREF
  __int64 v29; // [xsp-1D0h] [xbp-240h] BYREF
  __int64 v30; // [xsp-1C0h] [xbp-230h] BYREF
  __int64 v31; // [xsp-1B0h] [xbp-220h] BYREF
  __int64 v32; // [xsp-1A0h] [xbp-210h] BYREF
  _QWORD v33[16]; // [xsp-190h] [xbp-200h] BYREF
  __int64 v34; // [xsp-110h] [xbp-180h] BYREF
  __int64 v35; // [xsp-100h] [xbp-170h] BYREF
  __int64 v36; // [xsp-F0h] [xbp-160h] BYREF
  __int64 v37; // [xsp-E0h] [xbp-150h] BYREF
  __int64 v38; // [xsp-D0h] [xbp-140h]
  __int64 v39; // [xsp-C0h] [xbp-130h] BYREF
  __int64 v40; // [xsp-B0h] [xbp-120h]
  __int64 v41; // [xsp-A0h] [xbp-110h] BYREF
  __int64 v42; // [xsp-90h] [xbp-100h] BYREF
  __int64 v43; // [xsp-80h] [xbp-F0h] BYREF
  __int64 v44; // [xsp-70h] [xbp-E0h] BYREF
  __int64 v45; // [xsp-60h] [xbp-D0h]
  _QWORD v46[10]; // [xsp-50h] [xbp-C0h] BYREF
  __int64 *v47; // [xsp+0h] [xbp-70h]
  __int64 *v48; // [xsp+8h] [xbp-68h]
  __int64 *v49; // [xsp+10h] [xbp-60h]
  __int64 *v50; // [xsp+18h] [xbp-58h]
  __int64 *v51; // [xsp+20h] [xbp-50h]
  __int64 *v52; // [xsp+28h] [xbp-48h]
  unsigned int *v53; // [xsp+30h] [xbp-40h]
  __int64 *v54; // [xsp+38h] [xbp-38h]
  __int64 *v55; // [xsp+40h] [xbp-30h]
  __int64 v56; // [xsp+48h] [xbp-28h]
  __int64 *v57; // [xsp+50h] [xbp-20h]
  __int64 *v58; // [xsp+58h] [xbp-18h]
  _QWORD *v59; // [xsp+60h] [xbp-10h]
  __int64 v60; // [xsp+68h] [xbp-8h]

  v60 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x378468*/
  if ( (*(_DWORD *)sub_37843C >> 26 == 5) ^ (*(_DWORD *)sub_37843C >> 21 == 1697) /*0x378b48*/
     | (*(_DWORD *)sub_37843C >> 26 == 5 && *(_DWORD *)sub_37843C >> 21 == 1697)
    || loc_378440 >> 10 == 3508160
    || loc_378444 >> 10 == 3508160 )
  {
    _ReadStatusReg(TPIDR_EL0); /*0x378a94*/
    sub_3B33EC(); /*0x378aa8*/
  }
  v58 = &v43; /*0x3784b4*/
  v57 = &v42; /*0x3784c0*/
  v55 = &v41; /*0x3784cc*/
  v53 = (unsigned int *)&v36; /*0x3784f8*/
  v47 = &v35; /*0x378504*/
  v50 = &v32; /*0x378520*/
  v51 = &v30; /*0x378534*/
  v54 = &v28; /*0x378548*/
  v52 = &v27; /*0x378554*/
  v48 = &v26; /*0x378560*/
  v49 = &v25; /*0x37856c*/
  v56 = a2; /*0x378574*/
  v46[8] = a2; /*0x378578*/
  v46[6] = a1; /*0x37857c*/
  v46[4] = 0x40000000; /*0x378584*/
  v59 = v46; /*0x37858c*/
  sub_2E8E80(a1); /*0x378590*/
  v2 = sub_3B33CC(&v44); /*0x378598*/
  v45 = sub_3B33D0(v2); /*0x3785a8*/
  v3 = v59; /*0x3785ac*/
  if ( (sub_CB11C(v59) & 1) != 0 ) /*0x3785b8*/
  {
    sub_C7BE8(v56, v45); /*0x3785cc*/
    *(_DWORD *)v55 = 1; /*0x3785e0*/
  }
  else
  {
    v4 = ((__int64 (__fastcall *)(__int64 *))loc_379920)(&v39); /*0x37861c*/
    v40 = sub_3B33D4(v4); /*0x378634*/
    if ( (sub_23F1AC(v3, v40) & 1) != 0 ) /*0x378644*/
    {
      v6 = sub_141054(v3); /*0x3786c8*/
      v7 = sub_37B87C(4294967196LL, v6, 0x80000, 416); /*0x3786dc*/
      v8 = v53; /*0x3786e0*/
      *v53 = v7; /*0x3786e8*/
      if ( (*v8 & 0x80000000) == 0 ) /*0x3786f8*/
      {
        memset(v33, 0, sizeof(v33)); /*0x378774*/
        v12 = sub_141054(v3); /*0x37877c*/
        if ( (unsigned int)((__int64 (__fastcall *)(__int64, _QWORD *))loc_37C8EC)(v12, v33) ) /*0x378784*/
        {
          sub_37CDF8(*v8); /*0x3787a4*/
          v13 = sub_3B33DC(&v31); /*0x3787ac*/
          v14 = ((__int64 (__fastcall *)(__int64))loc_37D7F4)(v13); /*0x3787b4*/
          v15 = v50; /*0x3787bc*/
          *v50 = v14; /*0x3787c0*/
          sub_C7BE8(v56, *v15); /*0x3787cc*/
          *(_DWORD *)v55 = 1; /*0x3787dc*/
        }
        else if ( v33[6] >= 0x40000000LL ) /*0x37882c*/
        {
          v19 = (__int64)v54; /*0x3788b4*/
          sub_4C0718(*v8, (__int64)v54); /*0x3788bc*/
          sub_37CDF8(*v8); /*0x3788cc*/
          if ( (sub_CB11C(v19) & 1) != 0 ) /*0x3788dc*/
          {
            v20 = sub_3B33E0(v48); /*0x3788ec*/
            v21 = sub_3B33E4(v20); /*0x3788f4*/
            v22 = v52; /*0x3788fc*/
            *v52 = v21; /*0x378900*/
            sub_3B33E8(v56, *v22); /*0x37890c*/
            *(_DWORD *)v55 = 1; /*0x378920*/
          }
          else
          {
            *(_BYTE *)v49 = 0; /*0x37897c*/
            sub_3780EC(v19); /*0x378988*/
            v23 = v49; /*0x378998*/
            *(_BYTE *)v49 = 1; /*0x37899c*/
            *(_DWORD *)v55 = 1; /*0x3789a8*/
            if ( (*(_BYTE *)v23 & 1) == 0 ) /*0x3789b4*/
              sub_74539C(v56); /*0x3789c0*/
          }
          sub_74539C(v54); /*0x3789d8*/
          v3 = v59; /*0x3789dc*/
        }
        else
        {
          sub_37CDF8(*v8); /*0x378838*/
          v16 = ((__int64 (__fastcall *)(__int64 *))loc_37DB14)(&v29); /*0x378844*/
          v17 = ((__int64 (__fastcall *)(__int64))loc_37E7B8)(v16); /*0x37884c*/
          v18 = v51; /*0x378854*/
          *v51 = v17; /*0x378858*/
          sub_C7BE8(v56, *v18); /*0x378864*/
          *(_DWORD *)v55 = 1; /*0x378878*/
          v3 = v59; /*0x37887c*/
        }
      }
      else
      {
        v9 = sub_3B33D8(&v34); /*0x378704*/
        v10 = ((__int64 (__fastcall *)(__int64))loc_37C42C)(v9); /*0x378714*/
        v11 = v47; /*0x37871c*/
        *v47 = v10; /*0x378720*/
        sub_C7BE8(v56, *v11); /*0x37872c*/
        *(_DWORD *)v55 = 1; /*0x37873c*/
      }
    }
    else
    {
      v5 = ((__int64 (__fastcall *)(__int64 *))loc_37AB08)(&v37); /*0x378650*/
      v38 = ((__int64 (__fastcall *)(__int64))loc_37B510)(v5); /*0x378668*/
      sub_C7BE8(v56, v38); /*0x378674*/
      *(_DWORD *)v55 = 1; /*0x378688*/
    }
  }
  result = sub_74539C(v3); /*0x378a34*/
  _ReadStatusReg(TPIDR_EL0); /*0x378a38*/
  return result; /*0x378a68*/
}