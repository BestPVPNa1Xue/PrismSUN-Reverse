__int64 __fastcall sub_5A7BE4(__int64 a1)
{
  __int64 v1; // x0
  __int64 *v2; // x20
  __int64 v3; // x0
  unsigned int v4; // w20
  __int64 v5; // x0
  __int64 v6; // x0
  __int64 v7; // x0
  __int64 *v8; // x19
  unsigned int v9; // w19
  __int64 v10; // x22
  __int64 v11; // x0
  __int64 v12; // x0
  __int64 *v13; // x22
  unsigned int v14; // w19
  __int64 v15; // x22
  __int64 v16; // x0
  __int64 v17; // x0
  __int64 *v18; // x9
  unsigned int v19; // w19
  __int64 v20; // x22
  __int64 v21; // x0
  __int64 v22; // x0
  __int64 result; // x0
  __int64 v24; // [xsp-190h] [xbp-1F0h] BYREF
  __int64 v25; // [xsp-170h] [xbp-1D0h] BYREF
  _QWORD v26[4]; // [xsp-160h] [xbp-1C0h] BYREF
  __int64 v27; // [xsp-140h] [xbp-1A0h] BYREF
  __int64 v28; // [xsp-120h] [xbp-180h] BYREF
  _QWORD v29[4]; // [xsp-110h] [xbp-170h] BYREF
  __int64 v30; // [xsp-F0h] [xbp-150h] BYREF
  __int64 v31; // [xsp-D0h] [xbp-130h] BYREF
  _QWORD v32[4]; // [xsp-C0h] [xbp-120h] BYREF
  __int64 v33; // [xsp-A0h] [xbp-100h] BYREF
  __int64 v34; // [xsp-90h] [xbp-F0h] BYREF
  __int64 v35; // [xsp-80h] [xbp-E0h] BYREF
  _BYTE v36[32]; // [xsp-70h] [xbp-D0h] BYREF
  __int64 v37; // [xsp-50h] [xbp-B0h]
  __int64 v38; // [xsp-40h] [xbp-A0h] BYREF
  __int64 v39; // [xsp-30h] [xbp-90h]
  __int64 v40; // [xsp-20h] [xbp-80h]
  __int64 v41; // [xsp-10h] [xbp-70h] BYREF
  __int64 v42; // [xsp+0h] [xbp-60h]
  __int64 *v43; // [xsp+8h] [xbp-58h]
  __int64 *v44; // [xsp+10h] [xbp-50h]
  __int64 *v45; // [xsp+18h] [xbp-48h]
  __int64 *v46; // [xsp+20h] [xbp-40h]
  __int64 *v47; // [xsp+28h] [xbp-38h]
  __int64 *v48; // [xsp+30h] [xbp-30h]
  __int64 *v49; // [xsp+38h] [xbp-28h]
  __int64 *v50; // [xsp+40h] [xbp-20h]
  __int64 *v51; // [xsp+48h] [xbp-18h]
  __int64 *v52; // [xsp+50h] [xbp-10h]
  __int64 v53; // [xsp+58h] [xbp-8h]

  v53 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x5a7c0c*/
  if ( ((((((((*(_DWORD *)sub_5A7BE4 >> 26 == 5) << 31 >> 31) + ((*(_DWORD *)sub_5A7BE4 >> 21 == 1697) << 31 >> 31)) << 31 >> 31) /*0x5a8134*/
         - 1) << 31 >> 31)
       + ((*(_DWORD *)sub_5A7BE4 >> 21 != 1697 || *(_DWORD *)sub_5A7BE4 >> 26 != 5) << 31 >> 31))
      & 1) != 0
    || loc_5A7BE8 >> 10 == 3508160
    || loc_5A7BEC >> 10 == 3508160 )
  {
    _ReadStatusReg(TPIDR_EL0); /*0x5a8084*/
    abort(); /*0x5a8098*/
  }
  v52 = &v41; /*0x5a7c1c*/
  v51 = &v35; /*0x5a7c50*/
  v49 = &v34; /*0x5a7c5c*/
  v50 = &v33; /*0x5a7c68*/
  v48 = &v31; /*0x5a7c84*/
  v44 = &v30; /*0x5a7c90*/
  v45 = &v28; /*0x5a7cac*/
  v46 = &v27; /*0x5a7cb8*/
  v43 = &v25; /*0x5a7cd4*/
  v47 = &v24; /*0x5a7ce0*/
  v40 = a1; /*0x5a7ce8*/
  v42 = a1; /*0x5a7cf0*/
  if ( (((__int64 (*)(void))sub_5A8148)() & 1) != 0 ) /*0x5a7cf8*/
  {
    v1 = ((__int64 (*)(void))loc_4C7A14)(); /*0x5a7d04*/
    v2 = v52; /*0x5a7d08*/
    *v52 = v1; /*0x5a7d0c*/
  }
  else
  {
    v3 = ((__int64 (__fastcall *)(__int64 *))loc_5A858C)(&v38); /*0x5a7d18*/
    v39 = ((__int64 (__fastcall *)(__int64))loc_5A938C)(v3); /*0x5a7d20*/
    v37 = sub_2A06DC(v39, 0); /*0x5a7d30*/
    if ( v37 ) /*0x5a7d38*/
    {
      v6 = ((__int64 (__fastcall *)(_QWORD *))loc_5A984C)(v32); /*0x5a7dac*/
      v32[2] = ((__int64 (__fastcall *)(__int64))loc_5AABA0)(v6); /*0x5a7db4*/
      v7 = sub_2A0DE8(v37); /*0x5a7dc4*/
      v8 = v48; /*0x5a7dc8*/
      *v48 = v7; /*0x5a7dcc*/
      if ( *v8 ) /*0x5a7dd0*/
      {
        v11 = sub_5B6F10(v29); /*0x5a7e5c*/
        v29[2] = ((__int64 (__fastcall *)(__int64))loc_5AC544)(v11); /*0x5a7e64*/
        v12 = sub_2A0DE8(v37); /*0x5a7e74*/
        v13 = v45; /*0x5a7e78*/
        *v45 = v12; /*0x5a7e7c*/
        if ( *v13 ) /*0x5a7e80*/
        {
          v16 = ((__int64 (__fastcall *)(_QWORD *))loc_5AC920)(v26); /*0x5a7f0c*/
          v26[2] = ((__int64 (__fastcall *)(__int64))loc_5ADA44)(v16); /*0x5a7f14*/
          v17 = sub_5B6F18(v37); /*0x5a7f24*/
          v18 = v43; /*0x5a7f28*/
          *v43 = v17; /*0x5a7f2c*/
          v2 = v52; /*0x5a7f3c*/
          if ( *v18 ) /*0x5a7f30*/
          {
            v21 = v42; /*0x5a7fb8*/
            *(_QWORD *)(v42 + 8) = *v8; /*0x5a7fbc*/
            *(_QWORD *)(v21 + 16) = *v13; /*0x5a7fc4*/
            *(_QWORD *)(v21 + 24) = *v18; /*0x5a7fcc*/
            v22 = ((__int64 (*)(void))loc_5ADE24)(); /*0x5a7fd8*/
            *v2 = sub_5B6F84(v22); /*0x5a7fe0*/
          }
          else
          {
            v19 = sub_5B6F1C(0xFA7u); /*0x5a7f50*/
            v20 = (__int64)v47; /*0x5a7f5c*/
            sub_5B6F20(v47, &byte_34073); /*0x5a7f64*/
            *v2 = sub_4C546C(v19, v20); /*0x5a7f7c*/
            sub_74539C(v20); /*0x5a7f84*/
          }
          *(_DWORD *)v50 = 1; /*0x5a7f90*/
        }
        else
        {
          v14 = sub_5B6F14(0xFA7u); /*0x5a7ea4*/
          v15 = (__int64)v46; /*0x5a7eb0*/
          sub_C7BE8(v46, &byte_34073); /*0x5a7eb8*/
          v2 = v52; /*0x5a7ebc*/
          *v2 = sub_4C546C(v14, v15); /*0x5a7ed4*/
          sub_74539C(v15); /*0x5a7edc*/
          *(_DWORD *)v50 = 1; /*0x5a7ee8*/
        }
      }
      else
      {
        v9 = sub_2B2208(0xFA7u); /*0x5a7df0*/
        v10 = (__int64)v44; /*0x5a7dfc*/
        sub_5B6F0C(v44, &byte_34073); /*0x5a7e04*/
        v2 = v52; /*0x5a7e08*/
        *v2 = sub_4C546C(v9, v10); /*0x5a7e24*/
        sub_74539C(v10); /*0x5a7e2c*/
        *(_DWORD *)v50 = 1; /*0x5a7e38*/
      }
    }
    else
    {
      v4 = sub_2B2208(0xFA6u); /*0x5a7d44*/
      sub_5B6EA4(v36, &byte_34073); /*0x5a7d54*/
      v5 = sub_5B6EA8(v4, (__int64)v36); /*0x5a7d60*/
      v2 = v52; /*0x5a7d6c*/
      *v52 = v5; /*0x5a7d70*/
      sub_74539C(v36); /*0x5a7d78*/
      *(_DWORD *)v50 = 1; /*0x5a7d84*/
    }
  }
  result = *v2; /*0x5a802c*/
  _ReadStatusReg(TPIDR_EL0); /*0x5a8030*/
  return result; /*0x5a8060*/
}