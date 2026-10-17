__int64 __fastcall sub_591164(__int64 a1, unsigned int a2)
{
  int v2; // w8
  __int64 v3; // x19
  unsigned int v4; // w20
  int v5; // w0
  int v6; // w8
  __int64 result; // x0
  int v8; // w8
  int v9; // w8
  _QWORD savedregs[4]; // [xsp+20h] [xbp+0h] BYREF

  savedregs[3] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x59117c*/
  savedregs[2] = 0x6B7BA182F3E887DBLL; /*0x591188*/
  savedregs[0] = (char *)&savedregs[2] + 4; /*0x59119c*/
  while ( 1 ) /*0x5911c4*/
  {
    while ( 1 ) /*0x5911a0*/
    {
      if ( HIDWORD(savedregs[2]) == -1806044597 ) /*0x5911b0*/
      {
        _ReadStatusReg(TPIDR_EL0); /*0x5913e8*/
        abort(); /*0x5913fc*/
      }
      if ( HIDWORD(savedregs[2]) != -1656054128 ) /*0x5911c4*/
        break; /*0x5911c4*/
      HIDWORD(savedregs[2]) = 1722573505; /*0x59140c*/
    }
    if ( HIDWORD(savedregs[2]) == -936917907 ) /*0x5911ec*/
      break; /*0x5911ec*/
    switch ( HIDWORD(savedregs[2]) ) /*0x591214*/
    {
      case 0xD8DB974B: /*0x591214*/
        HIDWORD(savedregs[2]) = -1656054128; /*0x59134c*/
        break;
      case 0x2064CE44: /*0x591214*/
        LODWORD(savedregs[2]) = a2; /*0x59137c*/
        v3 = a1; /*0x591388*/
        v4 = a2; /*0x591390*/
        v5 = sub_59381C(a1, a2); /*0x591398*/
        a2 = v4; /*0x59139c*/
        v6 = v5; /*0x5913a0*/
        a1 = v3; /*0x5913a4*/
        HIDWORD(savedregs[1]) = v6; /*0x5913a8*/
        HIDWORD(savedregs[2]) = -936917907; /*0x5913b8*/
        break;
      case 0x330CC433: /*0x591214*/
        HIDWORD(savedregs[2]) = 1807775613; /*0x591568*/
        break;
      case 0x3B3AAB7B: /*0x591214*/
        if ( (savedregs[1] & 0x1000000LL) != 0 ) /*0x59147c*/
          v8 = -1806044597; /*0x59147c*/
        else
          v8 = 1331942837; /*0x59147c*/
        HIDWORD(savedregs[2]) = v8; /*0x591484*/
        break;
      case 0x404FFD50: /*0x591214*/
        if ( (savedregs[1] & 0x10000LL) != 0 ) /*0x591544*/
          v9 = -1806044597; /*0x591544*/
        else
          v9 = 2023400915; /*0x591544*/
        HIDWORD(savedregs[2]) = v9; /*0x59154c*/
        break;
      case 0x4F63D5B5: /*0x591214*/
        HIDWORD(savedregs[2]) = 1767822483; /*0x591498*/
        break;
      case 0x66AC62C1: /*0x591214*/
        BYTE3(savedregs[1]) = (*(_DWORD *)sub_591164 >> 26 == 5 && *(_DWORD *)sub_591164 >> 21 == 1697) /*0x591448*/
                            | (*(_DWORD *)sub_591164 >> 26 == 5) ^ (*(_DWORD *)sub_591164 >> 21 == 1697);
        HIDWORD(savedregs[2]) = 993700731; /*0x591458*/
        break;
      case 0x695ED493: /*0x591214*/
        BYTE2(savedregs[1]) = (loc_591168 >> 10 != 3508160) ^ (loc_59116C >> 10 != 3508160) /*0x591510*/
                            | (loc_591168 >> 10 == 3508160 && loc_59116C >> 10 == 3508160);
        HIDWORD(savedregs[2]) = 1078984016; /*0x591520*/
        break;
      case 0x6B7BA182: /*0x591214*/
        if ( LODWORD(savedregs[2]) > 0xCD4F837F ) /*0x59131c*/
          v2 = 1807775613; /*0x59131c*/
        else
          v2 = 856474675; /*0x59131c*/
        HIDWORD(savedregs[2]) = v2; /*0x591324*/
        break;
      case 0x6BC0777D: /*0x591214*/
        HIDWORD(savedregs[2]) = -656697525; /*0x591338*/
        break;
      default:
        HIDWORD(savedregs[2]) = 543477316; /*0x591360*/
        break;
    }
  }
  result = HIDWORD(savedregs[1]); /*0x5913c0*/
  _ReadStatusReg(TPIDR_EL0); /*0x5913c4*/
  return result; /*0x5913e4*/
}