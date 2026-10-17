__int64 __fastcall sub_2BFD70(__int64 a1, char a2)
{
  __int64 result; // x0
  int v3; // w8
  int v4; // w8
  bool v5; // [xsp+1Eh] [xbp-2h]
  char v6; // [xsp+1Fh] [xbp-1h]
  __int64 savedregs; // [xsp+20h] [xbp+0h]
  char savedregsa; // [xsp+20h] [xbp+0h]
  __int64 savedregs_8; // [xsp+28h] [xbp+8h]

  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x2bfd84*/
  savedregs = 0x703BDC1377A169F4LL; /*0x2bfd90*/
  while ( 1 ) /*0x2bfe58*/
  {
    while ( 1 ) /*0x2bfe1c*/
    {
      while ( 1 ) /*0x2bfe08*/
      {
        while ( 1 ) /*0x2bfde0*/
        {
          while ( 1 ) /*0x2bfdcc*/
          {
            while ( HIDWORD(savedregs) == -1650795090 ) /*0x2bfdcc*/
              HIDWORD(savedregs) = -1430831018; /*0x2c0080*/
            if ( HIDWORD(savedregs) != -1430831018 ) /*0x2bfde0*/
              break; /*0x2bfde0*/
            v5 = loc_2BFD74 >> 10 == 3508160 || loc_2BFD78 >> 10 == 3508160; /*0x2c00e4*/
            HIDWORD(savedregs) = 1765765483; /*0x2c00f4*/
          }
          if ( HIDWORD(savedregs) != -744112126 ) /*0x2bfe08*/
            break; /*0x2bfe08*/
          HIDWORD(savedregs) = 202390135; /*0x2bfff4*/
        }
        if ( HIDWORD(savedregs) != -723432779 ) /*0x2bfe1c*/
          break; /*0x2bfe1c*/
        HIDWORD(savedregs) = -744112126; /*0x2bff54*/
      }
      if ( HIDWORD(savedregs) == -429098577 ) /*0x2bfe30*/
      {
        _ReadStatusReg(TPIDR_EL0); /*0x2bffbc*/
        abort(); /*0x2bffd0*/
      }
      if ( HIDWORD(savedregs) != 27646508 ) /*0x2bfe58*/
        break; /*0x2bfe58*/
      HIDWORD(savedregs) = -723432779; /*0x2bff40*/
    }
    if ( HIDWORD(savedregs) == 124027358 ) /*0x2bfe6c*/
      break; /*0x2bfe6c*/
    switch ( HIDWORD(savedregs) ) /*0x2bfe80*/
    {
      case 0xC103A77: /*0x2bfe80*/
        v6 = (*(_DWORD *)sub_2BFD70 >> 26 == 5 && *(_DWORD *)sub_2BFD70 >> 21 == 1697) /*0x2c0030*/
           | (*(_DWORD *)sub_2BFD70 >> 26 == 5) ^ (*(_DWORD *)sub_2BFD70 >> 21 == 1697);
        HIDWORD(savedregs) = 822446068; /*0x2c0040*/
        break;
      case 0x2E445C20: /*0x2bfe80*/
        HIDWORD(savedregs) = -429098577; /*0x2bffb4*/
        break;
      case 0x310587F4: /*0x2bfe80*/
        if ( (v6 & 1) != 0 ) /*0x2c0064*/
          v3 = 776231968; /*0x2c0064*/
        else
          v3 = -1650795090; /*0x2c0064*/
        HIDWORD(savedregs) = v3; /*0x2c006c*/
        break;
      case 0x693F716B: /*0x2bfe80*/
        if ( v5 ) /*0x2c0100*/
          v4 = 776231968; /*0x2c0118*/
        else
          v4 = 124027358; /*0x2c0118*/
        HIDWORD(savedregs) = v4; /*0x2c0120*/
        break;
      default:
        HIDWORD(savedregs) = 27646508; /*0x2bff2c*/
        break;
    }
  }
  savedregsa = a2 & 1; /*0x2bff74*/
  result = sub_2DB684(a1, a2 & 1); /*0x2bff84*/
  _ReadStatusReg(TPIDR_EL0); /*0x2bff88*/
  return result; /*0x2bffa4*/
}