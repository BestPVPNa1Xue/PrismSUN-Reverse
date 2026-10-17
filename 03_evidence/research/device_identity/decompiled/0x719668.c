__int64 __fastcall sub_719668(__int64 a1)
{
  int v1; // w8
  __int64 v2; // x20
  __int64 v3; // x19
  __int64 result; // x0
  int v5; // w8
  int v6; // w8
  bool savedregs_7; // [xsp+37h] [xbp+7h]
  __int64 savedregs_8; // [xsp+38h] [xbp+8h]
  unsigned __int64 savedregs_16; // [xsp+40h] [xbp+10h]
  __int64 savedregs_24; // [xsp+48h] [xbp+18h]

  savedregs_24 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x719680*/
  savedregs_16 = 0xFE060258E8571C85LL; /*0x71968c*/
  while ( 1 ) /*0x7196bc*/
  {
    if ( HIDWORD(savedregs_16) == -1925299292 ) /*0x7196c8*/
    {
      _ReadStatusReg(TPIDR_EL0); /*0x7198e0*/
      abort(); /*0x7198f4*/
    }
    if ( HIDWORD(savedregs_16) == -1892735365 ) /*0x7196dc*/
      break; /*0x7196dc*/
    switch ( HIDWORD(savedregs_16) ) /*0x719704*/
    {
      case 0xC7174FA6: /*0x719704*/
        JUMPOUT(0x7199F8); /*0x7199f8*/
      case 0xEEB52573: /*0x719704*/
        HIDWORD(savedregs_16) = 1001512286; /*0x719850*/
        break;
      case 0xF78334D9: /*0x719704*/
        if ( savedregs_7 ) /*0x719968*/
          v5 = 1025898586; /*0x719980*/
        else
          v5 = 33825817; /*0x719980*/
        HIDWORD(savedregs_16) = v5; /*0x719988*/
        break;
      case 0xFE060258: /*0x719704*/
        if ( (unsigned int)savedregs_16 < 0xC82CB05A ) /*0x719820*/
          v1 = -954773594; /*0x719820*/
        else
          v1 = 155648340; /*0x719820*/
        HIDWORD(savedregs_16) = v1; /*0x719828*/
        break;
      case 0x2042419: /*0x719704*/
        if ( loc_71966C >> 10 == 3508160 || loc_719670 >> 10 == 3508160 ) /*0x7199e4*/
          v6 = 1025898586; /*0x7199e8*/
        else
          v6 = 1261691705; /*0x7199e8*/
        HIDWORD(savedregs_16) = v6; /*0x7199f0*/
        break;
      case 0x9470154: /*0x719704*/
        HIDWORD(savedregs_16) = -290118285; /*0x71983c*/
        break;
      case 0x1CFC22DC: /*0x719704*/
        savedregs_7 = *(_DWORD *)sub_719668 >> 26 == 5 || *(_DWORD *)sub_719668 >> 21 == 1697; /*0x71994c*/
        HIDWORD(savedregs_16) = -142396199; /*0x71995c*/
        break;
      case 0x3BB1DD5E: /*0x719704*/
        HIDWORD(savedregs_16) = 486286044; /*0x719918*/
        break;
      case 0x3D25F85A: /*0x719704*/
        HIDWORD(savedregs_16) = -1925299292; /*0x7198d8*/
        break;
      case 0x4B33E339: /*0x719704*/
        HIDWORD(savedregs_16) = 1537791744; /*0x719864*/
        break;
      default:
        v2 = a1; /*0x719874*/
        savedregs_16 = (unsigned int)a1 | 0x8F2F267B00000000LL; /*0x719878*/
        v3 = a1; /*0x71987c*/
        sub_725B28(a1); /*0x719884*/
        a1 = v2; /*0x719888*/
        savedregs_8 = v3; /*0x71988c*/
        break;
    }
  }
  result = savedregs_8; /*0x7198a4*/
  _ReadStatusReg(TPIDR_EL0); /*0x7198a8*/
  return result; /*0x7198c8*/
}