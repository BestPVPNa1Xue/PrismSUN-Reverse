__int64 __usercall sub_4C0718@<X0>(unsigned int a1@<W0>, __int64 a2@<X8>)
{
  __int64 result; // x0
  __int64 *v3; // x26
  __int64 v4; // x0
  __int64 *v5; // x22
  __int64 v6; // x19
  __int64 *v7; // x21
  unsigned int *v8; // x21
  unsigned int v9; // w24
  __int64 v10; // x0
  __int64 *v11; // x9
  __int64 v12; // [xsp-130h] [xbp-180h] BYREF
  __int64 v13; // [xsp-120h] [xbp-170h] BYREF
  __int64 v14; // [xsp-110h] [xbp-160h] BYREF
  __int64 v15; // [xsp-100h] [xbp-150h] BYREF
  __int64 v16; // [xsp-F0h] [xbp-140h] BYREF
  __int64 v17; // [xsp-E0h] [xbp-130h] BYREF
  const void *v18; // [xsp-D0h] [xbp-120h]
  _DWORD v19[8]; // [xsp-C0h] [xbp-110h] BYREF
  __int64 v20; // [xsp-A0h] [xbp-F0h]
  unsigned int v21; // [xsp-90h] [xbp-E0h] BYREF
  int v22; // [xsp-80h] [xbp-D0h]
  int v23; // [xsp-70h] [xbp-C0h] BYREF
  unsigned __int16 v24; // [xsp-60h] [xbp-B0h] BYREF
  int i; // [xsp-50h] [xbp-A0h]
  __int64 v26; // [xsp-40h] [xbp-90h] BYREF
  __int64 v27; // [xsp-30h] [xbp-80h] BYREF
  unsigned int v28; // [xsp-20h] [xbp-70h]
  __int64 v29; // [xsp-10h] [xbp-60h]
  __int64 *v30; // [xsp+0h] [xbp-50h]
  __int64 *v31; // [xsp+8h] [xbp-48h]
  __int64 *v32; // [xsp+10h] [xbp-40h]
  __int64 *v33; // [xsp+18h] [xbp-38h]
  __int64 *v34; // [xsp+20h] [xbp-30h]
  __int64 *v35; // [xsp+28h] [xbp-28h]
  __int64 *v36; // [xsp+30h] [xbp-20h]
  unsigned int *v37; // [xsp+38h] [xbp-18h]
  __int64 v38; // [xsp+40h] [xbp-10h]
  __int64 v39; // [xsp+48h] [xbp-8h]

  v39 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x4c0744*/
  if ( *(_DWORD *)sub_4C0718 >> 26 == 5 /*0x4c0d40*/
    || *(_DWORD *)sub_4C0718 >> 21 == 1697
    || loc_4C071C >> 10 == 3508160
    || loc_4C0720 >> 10 == 3508160 )
  {
    _ReadStatusReg(TPIDR_EL0); /*0x4c0c9c*/
    sub_4C373C(); /*0x4c0cb0*/
  }
  v38 = a2; /*0x4c0750*/
  v37 = (unsigned int *)&v27; /*0x4c076c*/
  v36 = &v26; /*0x4c0778*/
  v30 = &v17; /*0x4c07cc*/
  v35 = &v16; /*0x4c07d8*/
  v33 = &v15; /*0x4c07e4*/
  v32 = &v14; /*0x4c07f0*/
  v34 = &v13; /*0x4c07fc*/
  v31 = &v12; /*0x4c0808*/
  v29 = a2; /*0x4c0814*/
  v28 = a1; /*0x4c0818*/
  for ( i = 0; ; ++i )
  {
    v24 = 0; /*0x4c0824*/
    sub_4C0D54(v28, -2LL - i, 2); /*0x4c083c*/
    result = sub_4C0F3C(v28, &v24, 2); /*0x4c084c*/
    if ( v24 != i
      || ((sub_4C0D54(v28, -22, 1), v23 = 0, result = sub_4C0F3C(v28, &v23, 4), v23 != 101010256)
        ? (v22 = 0)
        : (v22 = 2),
          !v22) )
    {
      if ( i == 0xFFFF ) /*0x4c08ec*/
      {
        result = sub_4C365C(v38); /*0x4c08f8*/
        v22 = 1; /*0x4c0900*/
      }
      else
      {
        v22 = 0; /*0x4c090c*/
      }
    }
    if ( v22 ) /*0x4c091c*/
      break; /*0x4c091c*/
  }
  if ( v22 == 2 ) /*0x4c0944*/
  {
    v21 = 0; /*0x4c0948*/
    v20 = 12; /*0x4c0950*/
    sub_4C0D54(v28, 12, 1); /*0x4c0960*/
    sub_4C0F3C(v28, &v21, 4); /*0x4c0970*/
    v19[4] = 24; /*0x4c0978*/
    sub_4C0D54(v28, v21 - 24, 0); /*0x4c0990*/
    v3 = v36; /*0x4c0998*/
    sub_4C3660(v28, v36, 8); /*0x4c09a4*/
    memset(v19, 0, 0x10u); /*0x4c09b4*/
    sub_4C0F3C(v28, v19, 16); /*0x4c09c4*/
    v4 = ((__int64 (__fastcall *)(__int64 *))loc_4C1108)(v30); /*0x4c09cc*/
    v18 = (const void *)((__int64 (__fastcall *)(__int64))loc_4C1CEC)(v4); /*0x4c09d4*/
    if ( !memcmp(v19, v18, 0x10u) /*0x4c0a48*/
      && (v5 = v35, *v35 = 0, sub_4C0D54(v28, v21 - *v3 - 8, 0), sub_4C3664(v28, v5, 8), v6 = v38, *v5 == *v3) )
    {
      while ( 1 ) /*0x4c0a80*/
      {
        sub_4C3668(v28, v3, 8); /*0x4c0a80*/
        if ( *v3 == *v5 ) /*0x4c0a94*/
          break; /*0x4c0a94*/
        v7 = v33; /*0x4c0aa4*/
        sub_4C366C(v28, v33, 4); /*0x4c0ab0*/
        if ( *(_DWORD *)v7 == 1896449818 ) /*0x4c0ac8*/
        {
          v8 = v37; /*0x4c0ad4*/
          sub_4C0F3C(v28, v37, 4); /*0x4c0ae0*/
          sub_4C3670(v28, v8, 4); /*0x4c0af0*/
          sub_4C0F3C(v28, v8, 4); /*0x4c0b00*/
          sub_4C0F3C(v28, v8, 4); /*0x4c0b10*/
          sub_4C0D54(v28, *v8, 1); /*0x4c0b20*/
          sub_4C3674(v28, v8, 4); /*0x4c0b30*/
          sub_4C0F3C(v28, v8, 4); /*0x4c0b40*/
          *(_BYTE *)v32 = 0; /*0x4c0b48*/
          sub_F7768(v6); /*0x4c0b50*/
          sub_4C3678(v6, *v8); /*0x4c0b5c*/
          v9 = v28; /*0x4c0b68*/
          v10 = sub_24A758(v6); /*0x4c0b70*/
          result = sub_4C0F3C(v9, v10, *v37); /*0x4c0b84*/
          v11 = v32; /*0x4c0b90*/
          *(_BYTE *)v32 = 1; /*0x4c0b94*/
          v22 = 1; /*0x4c0b9c*/
          if ( (*(_BYTE *)v11 & 1) == 0 ) /*0x4c0ba8*/
            result = sub_4C36DC(v6); /*0x4c0bd4*/
        }
        else
        {
          result = sub_4C0D54(v28, *v3 - 4, 1); /*0x4c0bf0*/
          v22 = 0; /*0x4c0bf8*/
        }
        if ( v22 ) /*0x4c0c08*/
          goto LABEL_24; /*0x4c0c08*/
      }
      result = sub_F7768(v6); /*0x4c0c20*/
      v22 = 1; /*0x4c0c28*/
    }
    else
    {
      result = sub_F7768(v38); /*0x4c09f4*/
      v22 = 1; /*0x4c09fc*/
    }
  }
LABEL_24:
  _ReadStatusReg(TPIDR_EL0); /*0x4c0c48*/
  return result; /*0x4c0c78*/
}