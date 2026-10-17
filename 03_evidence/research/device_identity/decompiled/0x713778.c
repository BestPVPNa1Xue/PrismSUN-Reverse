__int64 __usercall sub_713778@<X0>(__int64 a1@<X8>)
{
  void *v2; // x20
  __int64 result; // x0
  int v4; // w9
  int v5; // w9
  _QWORD savedregs[4]; // [xsp+20h] [xbp+0h] BYREF

  savedregs[3] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x713790*/
  savedregs[2] = 0x116AC80F22A98BFDLL; /*0x71379c*/
  savedregs[0] = (char *)&savedregs[2] + 4; /*0x7137b0*/
  while ( 1 ) /*0x7137ec*/
  {
    while ( 1 ) /*0x7137d8*/
    {
      while ( HIDWORD(savedregs[2]) == -1743443909 ) /*0x7137d8*/
      {
        HIBYTE(savedregs[1]) = (*(_DWORD *)sub_713778 >> 26 == 5 && *(_DWORD *)sub_713778 >> 21 == 1697) /*0x713a54*/
                             | (*(_DWORD *)sub_713778 >> 26 == 5) ^ (*(_DWORD *)sub_713778 >> 21 == 1697);
        HIDWORD(savedregs[2]) = -646343732; /*0x713a64*/
      }
      if ( HIDWORD(savedregs[2]) != -1642494046 ) /*0x7137ec*/
        break; /*0x7137ec*/
      BYTE6(savedregs[1]) = loc_71377C >> 10 == 3508160 || loc_713780 >> 10 == 3508160; /*0x713b14*/
      HIDWORD(savedregs[2]) = 1295592645; /*0x713b24*/
    }
    if ( HIDWORD(savedregs[2]) == -1535070849 ) /*0x713800*/
    {
      _ReadStatusReg(TPIDR_EL0); /*0x7139e0*/
      abort(); /*0x7139f4*/
    }
    if ( HIDWORD(savedregs[2]) == -1424169549 ) /*0x713814*/
      break; /*0x713814*/
    switch ( HIDWORD(savedregs[2]) ) /*0x71383c*/
    {
      case 0xD852EB0E: /*0x71383c*/
        HIDWORD(savedregs[2]) = -1743443909; /*0x713a18*/
        break;
      case 0xD97993CC: /*0x71383c*/
        if ( (savedregs[1] & 0x100000000000000LL) != 0 ) /*0x713a88*/
          v4 = 1009306573; /*0x713a88*/
        else
          v4 = 2045110027; /*0x713a88*/
        HIDWORD(savedregs[2]) = v4; /*0x713a90*/
        break;
      case 0xE70EEBB1: /*0x71383c*/
        HIDWORD(savedregs[2]) = -665654514; /*0x713960*/
        break;
      case 0x116AC80F: /*0x71383c*/
        HIDWORD(savedregs[2]) = 898517146; /*0x713938*/
        break;
      case 0x358E489A: /*0x71383c*/
        HIDWORD(savedregs[2]) = -418452559; /*0x71394c*/
        break;
      case 0x3C28CBCD: /*0x71383c*/
        HIDWORD(savedregs[2]) = -1535070849; /*0x7139d8*/
        break;
      case 0x4D392CC5: /*0x71383c*/
        if ( (savedregs[1] & 0x1000000000000LL) != 0 ) /*0x713b48*/
          v5 = 1009306573; /*0x713b48*/
        else
          v5 = -1424169549; /*0x713b48*/
        HIDWORD(savedregs[2]) = v5; /*0x713b50*/
        break;
      default:
        HIDWORD(savedregs[2]) = -1642494046; /*0x713aa4*/
        break;
    }
  }
  savedregs[2] = a1; /*0x713970*/
  v2 = (void *)sub_783C68(8); /*0x713980*/
  memset(v2, 0, 8u); /*0x713990*/
  sub_713BD8((__int64)v2); /*0x713998*/
  result = sub_71403C(a1, v2); /*0x7139a4*/
  _ReadStatusReg(TPIDR_EL0); /*0x7139a8*/
  return result; /*0x7139c8*/
}