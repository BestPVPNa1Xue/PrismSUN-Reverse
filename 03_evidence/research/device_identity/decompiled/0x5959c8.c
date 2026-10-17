__int64 __fastcall sub_5959C8(
        __int64 a1,
        __int64 a2,
        _BYTE *a3,
        __int64 a4,
        __int64 a5,
        __int64 a6,
        __int64 a7,
        __int64 a8,
        _BYTE *a9)
{
  int v10; // w8
  char v12; // [xsp+3Eh] [xbp-12h]
  char v13; // [xsp+3Fh] [xbp-11h]
  _BYTE *v14; // [xsp+40h] [xbp-10h]
  _QWORD *v15; // [xsp+48h] [xbp-8h]
  __int64 *v16; // [xsp+50h] [xbp+0h]
  _BYTE *v17; // [xsp+58h] [xbp+8h]
  _BYTE *v18; // [xsp+60h] [xbp+10h]
  _QWORD savedregs[2]; // [xsp+70h] [xbp+20h] BYREF

  savedregs[1] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x5959f0*/
  HIDWORD(savedregs[0]) = 1063184410; /*0x5959fc*/
  while ( 1 ) /*0x595a90*/
  {
    while ( 1 ) /*0x595a54*/
    {
      while ( 1 ) /*0x595a40*/
      {
        while ( HIDWORD(savedregs[0]) == -1125165162 ) /*0x595a40*/
          HIDWORD(savedregs[0]) = 986233058; /*0x595d38*/
        if ( HIDWORD(savedregs[0]) != -914693728 ) /*0x595a54*/
          break; /*0x595a54*/
        if ( (v13 & 1) != 0 ) /*0x595c70*/
          v10 = 1245767364; /*0x595c70*/
        else
          v10 = -6435339; /*0x595c70*/
        HIDWORD(savedregs[0]) = v10; /*0x595c78*/
      }
      if ( HIDWORD(savedregs[0]) != -6435339 ) /*0x595a90*/
        break; /*0x595a90*/
      HIDWORD(savedregs[0]) = 1889705433; /*0x595ca8*/
    }
    if ( HIDWORD(savedregs[0]) == 286185151 ) /*0x595ab8*/
      break; /*0x595ab8*/
    switch ( HIDWORD(savedregs[0]) ) /*0x595af4*/
    {
      case 0x2DC318C0: /*0x595af4*/
        HIDWORD(savedregs[0]) = -1125165162; /*0x595d24*/
        break;
      case 0x3AC8B8E2: /*0x595af4*/
        v12 = *v18 & 1; /*0x595d50*/
        HIDWORD(savedregs[0]) = 286185151; /*0x595d60*/
        break;
      case 0x3CF4928C: /*0x595af4*/
        v18 = &a9; /*0x595be4*/
        v17 = &a9; /*0x595bf8*/
        v16 = (__int64 *)&a9; /*0x595c04*/
        v15 = savedregs; /*0x595c10*/
        a9 = a3; /*0x595c24*/
        v14 = a3; /*0x595c2c*/
        v13 = a3[16] & 1; /*0x595c3c*/
        HIDWORD(savedregs[0]) = -914693728; /*0x595c4c*/
        break;
      case 0x3F5EE81A: /*0x595af4*/
        HIDWORD(savedregs[0]) = 1022661260; /*0x595bd4*/
        break;
      case 0x4A40E6C4: /*0x595af4*/
        *v18 = 0; /*0x595c84*/
        HIDWORD(savedregs[0]) = -1125165162; /*0x595c94*/
        break;
      default:
        *v14 = *v17; /*0x595cbc*/
        sub_4DAA54(v15, *v16); /*0x595ccc*/
        sub_5954A8(v14 + 8, v15); /*0x595cdc*/
        sub_2D94E4(v15); /*0x595ce4*/
        v14[16] = 1; /*0x595cf0*/
        *v18 = 1; /*0x595d00*/
        HIDWORD(savedregs[0]) = 767760576; /*0x595d10*/
        break;
    }
  }
  _ReadStatusReg(TPIDR_EL0); /*0x595d70*/
  return v12 & 1; /*0x595d98*/
}