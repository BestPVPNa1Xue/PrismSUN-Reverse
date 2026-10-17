__int64 __fastcall sub_4C4AE0(__int64 a1)
{
  unsigned int v2; // w20
  __int64 v3; // x0
  __int64 *v4; // x19
  __int64 v5; // x19
  __int64 v6; // x0
  __int64 *v7; // x19
  __int64 *v8; // x1
  __int64 *v9; // x19
  __int64 result; // x0
  __int64 v11; // [xsp-120h] [xbp-160h] BYREF
  __int64 v12; // [xsp-110h] [xbp-150h] BYREF
  __int64 v13; // [xsp-100h] [xbp-140h] BYREF
  __int64 v14; // [xsp-F0h] [xbp-130h] BYREF
  __int64 v15; // [xsp-E0h] [xbp-120h] BYREF
  _BYTE v16[32]; // [xsp-D0h] [xbp-110h] BYREF
  _BYTE v17[32]; // [xsp-B0h] [xbp-F0h] BYREF
  _BYTE v18[16]; // [xsp-90h] [xbp-D0h] BYREF
  __int64 v19; // [xsp-80h] [xbp-C0h]
  __int64 v20; // [xsp-70h] [xbp-B0h] BYREF
  __int64 v21; // [xsp-60h] [xbp-A0h] BYREF
  _QWORD v22[4]; // [xsp-50h] [xbp-90h] BYREF
  unsigned int v23; // [xsp-30h] [xbp-70h] BYREF
  __int64 v24; // [xsp-20h] [xbp-60h]
  __int64 v25; // [xsp-10h] [xbp-50h] BYREF
  __int64 *v26; // [xsp+0h] [xbp-40h]
  __int64 *v27; // [xsp+8h] [xbp-38h]
  __int64 *v28; // [xsp+10h] [xbp-30h]
  __int64 *v29; // [xsp+18h] [xbp-28h]
  __int64 *v30; // [xsp+20h] [xbp-20h]
  __int64 *v31; // [xsp+28h] [xbp-18h]
  __int64 *v32; // [xsp+30h] [xbp-10h]
  __int64 v33; // [xsp+38h] [xbp-8h]

  v33 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x4c4b08*/
  if ( *(_DWORD *)sub_4C4AE0 >> 26 == 5 /*0x4c4f7c*/
    || *(_DWORD *)sub_4C4AE0 >> 21 == 1697
    || ((((((((loc_4C4AE4 >> 10 == 3508160) << 31 >> 31) + ((loc_4C4AE8 >> 10 == 3508160) << 31 >> 31)) << 31 >> 31) - 1) << 31 >> 31)
       + ((loc_4C4AE8 >> 10 != 3508160 || loc_4C4AE4 >> 10 != 3508160) << 31 >> 31))
      & 1) != 0 )
  {
    _ReadStatusReg(TPIDR_EL0); /*0x4c4ec4*/
    sub_56B34C(); /*0x4c4ed8*/
  }
  v31 = &v25; /*0x4c4b14*/
  v32 = &v21; /*0x4c4b38*/
  v30 = &v20; /*0x4c4b44*/
  v28 = &v15; /*0x4c4b80*/
  v26 = &v13; /*0x4c4b94*/
  v29 = &v12; /*0x4c4ba0*/
  v27 = &v11; /*0x4c4bac*/
  v24 = a1; /*0x4c4bb4*/
  if ( (((__int64 (__fastcall *)(__int64))sub_4C4F88)(a1) & 1) != 0 ) /*0x4c4bc4*/
  {
    v23 = sub_4C5298(a1); /*0x4c4bd0*/
    v2 = v23; /*0x4c4bd4*/
    ((void (__fastcall *)(_QWORD *__return_ptr, unsigned int *))sub_2B3110)(v22, &v23); /*0x4c4be0*/
    v3 = ((__int64 (__fastcall *)(_QWORD, _QWORD *))sub_4C546C)(v2, v22); /*0x4c4bec*/
    v4 = v31; /*0x4c4bf0*/
    *v31 = v3; /*0x4c4bfc*/
    sub_74539C(v22); /*0x4c4c04*/
  }
  else
  {
    v19 = sub_3B8C40(); /*0x4c4c2c*/
    if ( (*(_BYTE *)(a1 + 8) & 1) == 0 ) /*0x4c4c34*/
    {
      sub_56B328(v18, v19 + 28); /*0x4c4c48*/
      ((void (__fastcall *)(__int64, _BYTE *, _QWORD))loc_4C5878)(v19 + 68, v18, v17[16]); /*0x4c4c5c*/
      sub_41D0C4(v18); /*0x4c4c68*/
      ((void (__fastcall *)(_BYTE *, __int64))loc_411028)(v17, v19 + 120); /*0x4c4c7c*/
      ((void (__fastcall *)(__int64, _BYTE *, _QWORD))loc_4C5E8C)(v19 + 160, v17, v16[16]); /*0x4c4c98*/
      sub_41D0C4(v17); /*0x4c4ca4*/
      *(_BYTE *)(a1 + 8) = 1; /*0x4c4cb4*/
      ((void (__fastcall *)(_BYTE *))loc_41D9C8)(v17); /*0x4c4cbc*/
      ((void (__fastcall *)(_BYTE *))loc_41D9C8)(v18); /*0x4c4cc4*/
    }
    v5 = v19; /*0x4c4d24*/
    v6 = ((__int64 (*)(void))loc_5B7CE0)(); /*0x4c4d28*/
    sub_56B330(v5, v6, 5); /*0x4c4d38*/
    v16[0] = 0; /*0x4c4d3c*/
    if ( (((__int64 (__fastcall *)(__int64, _BYTE *, __int64, __int64))loc_410AEC)(a1 + 56, v16, 1, 5) & 1) != 0 ) /*0x4c4d58*/
    {
      sub_56B334(&unk_7B06A4); /*0x4c4d68*/
      ((void (__fastcall *)(void *))sub_59240C)(&unk_7C06AC); /*0x4c4d78*/
      v14 = a1; /*0x4c4d7c*/
      v7 = v28; /*0x4c4d80*/
      sub_4C6934(v28, &v14); /*0x4c4d8c*/
      sub_74797C(v7); /*0x4c4d94*/
      sub_74795C(v7); /*0x4c4da4*/
      v8 = v26; /*0x4c4da8*/
      *(_BYTE *)v26 = 0; /*0x4c4dac*/
      if ( (((__int64 (__fastcall *)(__int64, __int64 *, __int64, __int64))loc_410AEC)(a1 + 64, v8, 1, 5) & 1) != 0 ) /*0x4c4dc4*/
      {
        *v27 = a1; /*0x4c4dd0*/
        v9 = v29; /*0x4c4dd4*/
        sub_56B338(v29); /*0x4c4ddc*/
        sub_56B33C(v9); /*0x4c4de4*/
        sub_56B340(v9); /*0x4c4df0*/
      }
      v4 = v31; /*0x4c4e30*/
    }
    else
    {
      v4 = v31; /*0x4c4e3c*/
    }
    *v4 = sub_56B348(); /*0x4c4e4c*/
  }
  result = *v4; /*0x4c4e64*/
  _ReadStatusReg(TPIDR_EL0); /*0x4c4e68*/
  return result; /*0x4c4e98*/
}