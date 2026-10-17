__int64 __usercall sub_5AE1D4@<X0>(__int64 a1@<X0>, __int64 a2@<X8>)
{
  __int64 result; // x0
  __int64 v5; // x0
  __int64 *v6; // x10
  __int64 v7; // [xsp-100h] [xbp-130h] BYREF
  __int64 v8; // [xsp-F0h] [xbp-120h] BYREF
  _BYTE v9[32]; // [xsp-E0h] [xbp-110h] BYREF
  _QWORD v10[2]; // [xsp-C0h] [xbp-F0h] BYREF
  __int64 v11; // [xsp-B0h] [xbp-E0h] BYREF
  int v12; // [xsp-A0h] [xbp-D0h]
  __int64 v13; // [xsp-90h] [xbp-C0h] BYREF
  __int64 v14; // [xsp-80h] [xbp-B0h]
  _QWORD v15[2]; // [xsp-70h] [xbp-A0h] BYREF
  __int64 v16; // [xsp-60h] [xbp-90h]
  _BYTE v17[16]; // [xsp-50h] [xbp-80h] BYREF
  __int64 v18; // [xsp-40h] [xbp-70h] BYREF
  __int64 v19; // [xsp-30h] [xbp-60h]
  __int64 v20; // [xsp-20h] [xbp-50h]
  __int64 v21; // [xsp-10h] [xbp-40h]
  __int64 *v22; // [xsp+0h] [xbp-30h]
  __int64 *v23; // [xsp+8h] [xbp-28h]
  __int64 *v24; // [xsp+10h] [xbp-20h]
  __int64 *v25; // [xsp+18h] [xbp-18h]
  __int64 v26; // [xsp+20h] [xbp-10h]
  __int64 v27; // [xsp+28h] [xbp-8h]

  v27 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x5ae1fc*/
  if ( !atomic_load((unsigned int *)&unk_7D0950) ) /*0x5ae208*/
  {
    byte_7AF254 = ~byte_7AF244 & 0xCF | byte_7AF244 & 0x30; /*0x5ae254*/
    byte_7AF255 = byte_7AF245 ^ 0xFA; /*0x5ae278*/
    byte_7AF256 = byte_7AF246 ^ 0xD4; /*0x5ae29c*/
    byte_7AF257 = byte_7AF247 + 16 - 2 * (byte_7AF247 & 0x10); /*0x5ae2cc*/
    byte_7AF258 = byte_7AF248 ^ 0x69; /*0x5ae2f0*/
    byte_7AF259 = byte_7AF249 ^ 0xFD; /*0x5ae314*/
    byte_7AF25A = byte_7AF24A ^ 0xE4; /*0x5ae338*/
    byte_7AF25B = byte_7AF24B ^ 0xBD; /*0x5ae35c*/
    byte_7AF25C = byte_7AF24C ^ 0xBC; /*0x5ae380*/
    byte_7AF25D = byte_7AF24D ^ 0x9C; /*0x5ae3a4*/
    byte_7AF25E = byte_7AF24E ^ 0x67; /*0x5ae3c8*/
    byte_7AF25F = byte_7AF24F ^ 0xCE; /*0x5ae3ec*/
    byte_7AF260 = (~byte_7AF250 & 0x20 | byte_7AF250 & 0xDF) ^ 0x95; /*0x5ae430*/
    byte_7AF261 = byte_7AF251 ^ 0xE6; /*0x5ae454*/
    byte_7AF262 = byte_7AF252 ^ 0x56; /*0x5ae478*/
    byte_7AF263 = ~byte_7AF253 & 0x36 | ~(~byte_7AF253 | 0x36); /*0x5ae4e0*/
  }
  atomic_store(1u, (unsigned int *)&unk_7D0950); /*0x5ae4f8*/
  if ( (*(_DWORD *)sub_5AE1D4 >> 26 == 5 && *(_DWORD *)sub_5AE1D4 >> 21 == 1697) /*0x5ae888*/
     | (*(_DWORD *)sub_5AE1D4 >> 26 == 5) ^ (*(_DWORD *)sub_5AE1D4 >> 21 == 1697)
    || (loc_5AE1D8 >> 10 != 3508160) ^ (loc_5AE1DC >> 10 != 3508160)
     | (loc_5AE1D8 >> 10 == 3508160 && loc_5AE1DC >> 10 == 3508160) )
  {
    _ReadStatusReg(TPIDR_EL0); /*0x5ae7c4*/
    abort(); /*0x5ae7d8*/
  }
  v25 = &v18; /*0x5ae520*/
  v23 = &v11; /*0x5ae55c*/
  v24 = &v8; /*0x5ae578*/
  v22 = &v7; /*0x5ae584*/
  v26 = a2; /*0x5ae58c*/
  v21 = a2; /*0x5ae590*/
  v20 = a1; /*0x5ae594*/
  if ( (((__int64 (__fastcall *)(__int64))loc_5A8148)(a1) & 1) != 0 ) /*0x5ae5a4*/
  {
    v19 = sub_5B6FF4(); /*0x5ae5c0*/
    if ( (((__int64 (__fastcall *)(__int64, __int64))sub_4181A0)(v19 + 217, 5) & 1) != 0 /*0x5ae650*/
      || (memcpy(v17, &byte_7AF254, sizeof(v17)),
          v16 = (*(__int64 (__fastcall **)(_BYTE *))(a1 + 8))(v17),
          v5 = ((__int64 (__fastcall *)(__int64 *))loc_5AE894)(&v13),
          v14 = ((__int64 (__fastcall *)(__int64))loc_5AF358)(v5),
          (v12 = (*(__int64 (__fastcall **)(__int64, __int64, _QWORD *))(a1 + 16))(v16, v14, v15)) != 0) )
    {
      result = sub_F7768(v26); /*0x5ae5e0*/
      *(_DWORD *)v25 = 1; /*0x5ae5ec*/
    }
    else
    {
      *(_BYTE *)v23 = 0; /*0x5ae674*/
      sub_5B6FF8(v9, v15[0], v15[0] + v15[1]); /*0x5ae68c*/
      sub_130B00(v10, v9); /*0x5ae698*/
      sub_CF83C(v10[0], v10[1], 1); /*0x5ae6b4*/
      sub_5B6FFC(v9); /*0x5ae6c4*/
      (*(void (__fastcall **)(__int64))(a1 + 24))(v16); /*0x5ae6d0*/
      v6 = v23; /*0x5ae6e4*/
      *(_BYTE *)v23 = 1; /*0x5ae6e8*/
      *(_DWORD *)v25 = 1; /*0x5ae6f4*/
      result = v26; /*0x5ae700*/
      if ( (*(_BYTE *)v6 & 1) == 0 ) /*0x5ae704*/
        result = sub_74539C(v26); /*0x5ae740*/
    }
  }
  else
  {
    result = sub_F7768(v26); /*0x5ae5b4*/
  }
  _ReadStatusReg(TPIDR_EL0); /*0x5ae76c*/
  return result; /*0x5ae79c*/
}