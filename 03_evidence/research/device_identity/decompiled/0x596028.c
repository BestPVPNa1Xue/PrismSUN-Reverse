__int64 __usercall sub_596028@<X0>(__int64 *a1@<X0>, __int64 a2@<X8>)
{
  __int64 result; // x0
  __int64 v4; // x0
  __int64 v5; // x0
  __int64 v6; // x0
  __int64 *v7; // x22
  __int64 v8; // x24
  double v9; // d0
  double v10; // d1
  double v11; // d2
  double v12; // d3
  long double v13; // q4
  unsigned int v14; // w25
  __int64 v15; // x3
  __int64 *v16; // x20
  __int64 v17; // x0
  __int64 *v18; // x22
  __int64 v19; // [xsp-120h] [xbp-160h]
  __int64 v20; // [xsp-110h] [xbp-150h] BYREF
  __int64 v21; // [xsp-100h] [xbp-140h] BYREF
  __int64 v22; // [xsp-E0h] [xbp-120h]
  __int64 v23; // [xsp-D0h] [xbp-110h]
  __int64 v24; // [xsp-C0h] [xbp-100h] BYREF
  __int64 v25; // [xsp-A0h] [xbp-E0h]
  __int64 v26; // [xsp-90h] [xbp-D0h] BYREF
  int v27; // [xsp-70h] [xbp-B0h]
  __int64 v28; // [xsp-60h] [xbp-A0h]
  __int64 v29; // [xsp-40h] [xbp-80h] BYREF
  __int64 v30[7]; // [xsp-30h] [xbp-70h] BYREF
  __int64 *v31; // [xsp+8h] [xbp-38h]
  __int64 *v32; // [xsp+10h] [xbp-30h]
  __int64 *v33; // [xsp+18h] [xbp-28h]
  __int64 *v34; // [xsp+20h] [xbp-20h]
  __int64 *v35; // [xsp+28h] [xbp-18h]
  __int64 v36; // [xsp+30h] [xbp-10h]
  __int64 v37; // [xsp+38h] [xbp-8h]

  v37 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x596050*/
  if ( (*(_DWORD *)sub_596028 >> 26 == 5 && *(_DWORD *)sub_596028 >> 21 == 1697) /*0x5964f0*/
     | (*(_DWORD *)sub_596028 >> 26 == 5) ^ (*(_DWORD *)sub_596028 >> 21 == 1697)
    || (loc_59602C >> 10 != 3508160) ^ (loc_596030 >> 10 != 3508160)
     | (loc_59602C >> 10 == 3508160 && loc_596030 >> 10 == 3508160) )
  {
    _ReadStatusReg(TPIDR_EL0); /*0x596438*/
    sub_5A79F8(); /*0x59644c*/
  }
  v34 = &v26; /*0x596098*/
  v30[4] = a2; /*0x5960d8*/
  v30[2] = (__int64)a1; /*0x5960dc*/
  if ( (a1[2] & 1) != 0 ) /*0x5960e8*/
  {
    v31 = &v20; /*0x596100*/
    v32 = &v21; /*0x596104*/
    v33 = &v24; /*0x596108*/
    v35 = &v29; /*0x59610c*/
    v36 = a2; /*0x596110*/
    v4 = sub_2A8358(); /*0x596114*/
    sub_4DAA54(v30, v4); /*0x596120*/
    sub_5A79C8(v30); /*0x596128*/
    sub_5A79CC((double)*(unsigned __int8 *)a1); /*0x59613c*/
    sub_2A7FEC(); /*0x59614c*/
    sub_5A79D0(v30); /*0x59615c*/
    v5 = sub_5A79D4(a1 + 1); /*0x596168*/
    sub_5A79D8(v5, 1); /*0x596170*/
    sub_2A7FEC(); /*0x596188*/
    v6 = sub_4DAE04(v30); /*0x596194*/
    v28 = sub_2A7958(v6); /*0x5961a0*/
    if ( v28 ) /*0x5961a8*/
    {
      sub_C7BE8(v34, v28); /*0x5961e8*/
      sub_5A79DC(v28); /*0x5961f4*/
      v25 = sub_5A79E0(); /*0x59620c*/
      if ( sub_4D92B4(v25) ) /*0x596214*/
      {
        v7 = v34; /*0x596274*/
        v23 = sub_18A5BC(v34); /*0x596280*/
        v22 = sub_18A814(v7); /*0x59628c*/
        ((void (__fastcall *)(__int64 *, __int64, __int64))loc_5964FC)(v33, v23, v22); /*0x59629c*/
        v8 = sub_5A79E4(v25); /*0x5962b0*/
        v14 = sub_4D1F14(v25, v9, v10, v11, v12, v13); /*0x5962c0*/
        v15 = ((__int64 (__fastcall *)(__int64))loc_596B58)(v25); /*0x5962d0*/
        sub_5BCDD8(v33, v8, v14, v15); /*0x5962ec*/
        v16 = v32; /*0x5962f8*/
        v17 = sub_D7E30(v32); /*0x596300*/
        v18 = v31; /*0x596304*/
        *v31 = v17; /*0x596308*/
        v19 = sub_D7F1C(v16); /*0x596314*/
        ((void (__fastcall *)(__int64, __int64, __int64))loc_594FB0)(v36, *v18, v19); /*0x596324*/
        v27 = 1; /*0x596334*/
        sub_5A79E8(v32); /*0x59633c*/
        sub_D2AC4((__int64)v33); /*0x596344*/
      }
      else
      {
        sub_F7768(v36); /*0x596234*/
        v27 = 1; /*0x59623c*/
      }
      sub_74539C(v34); /*0x596398*/
    }
    else
    {
      sub_F7768(v36); /*0x5961b0*/
      v27 = 1; /*0x5961b8*/
    }
    result = sub_5A79F0(v30); /*0x5963b8*/
  }
  else
  {
    result = sub_F7768(a2); /*0x5960f8*/
  }
  _ReadStatusReg(TPIDR_EL0); /*0x5963e4*/
  return result; /*0x596414*/
}