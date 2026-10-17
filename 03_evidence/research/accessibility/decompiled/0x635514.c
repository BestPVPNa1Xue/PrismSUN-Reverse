__int64 __fastcall sub_635514(__int64 result)
{
  int v1; // w8
  __int64 v2; // x20
  __int64 v3; // x19
  int v4; // w8
  int v5; // w8
  _QWORD savedregs[4]; // [xsp+20h] [xbp+0h] BYREF

  savedregs[3] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x63552c*/
  savedregs[2] = 0x18F10220A3AF0101LL; /*0x635538*/
  savedregs[0] = (char *)&savedregs[2] + 4; /*0x63554c*/
  while ( 1 ) /*0x63559c*/
  {
    while ( 1 ) /*0x635588*/
    {
      while ( 1 ) /*0x635574*/
      {
        while ( HIDWORD(savedregs[2]) == -1553194250 ) /*0x635574*/
          HIDWORD(savedregs[2]) = -614432840; /*0x63574c*/
        if ( HIDWORD(savedregs[2]) != -1451054013 ) /*0x635588*/
          break; /*0x635588*/
        HIDWORD(savedregs[2]) = 1899582288; /*0x635724*/
      }
      if ( HIDWORD(savedregs[2]) != -614432840 ) /*0x63559c*/
        break; /*0x63559c*/
      LODWORD(savedregs[2]) = result; /*0x63575c*/
      v2 = result; /*0x635760*/
      *(_DWORD *)result = 1; /*0x635768*/
      *(_BYTE *)(result + 4) = 0; /*0x63576c*/
      v3 = result; /*0x635774*/
      sub_4DAA54((_QWORD *)(result + 8), 0); /*0x635780*/
      result = v3; /*0x635784*/
      *(_DWORD *)(v2 + 16) = 0; /*0x635788*/
      HIDWORD(savedregs[2]) = -550102004; /*0x635798*/
    }
    if ( HIDWORD(savedregs[2]) == -550102004 ) /*0x6355b0*/
      break; /*0x6355b0*/
    switch ( HIDWORD(savedregs[2]) ) /*0x6355c4*/
    {
      case 0xE01FA054: /*0x6355c4*/
        HIDWORD(savedregs[2]) = 1288865686; /*0x635894*/
        break;
      case 0xF0A81B4F: /*0x6355c4*/
        JUMPOUT(0x635930); /*0x635930*/
      case 0xF4DC8A0A: /*0x6355c4*/
        HIDWORD(savedregs[2]) = 666987040; /*0x6357d0*/
        break;
      case 0x18F10220: /*0x6355c4*/
        if ( LODWORD(savedregs[2]) == -1708213579 ) /*0x635708*/
          v1 = -257418417; /*0x635708*/
        else
          v1 = -1451054013; /*0x635708*/
        HIDWORD(savedregs[2]) = v1; /*0x635710*/
        break;
      case 0x2472BFE5: /*0x6355c4*/
        HIBYTE(savedregs[1]) = *(_DWORD *)sub_635514 >> 26 == 5 || *(_DWORD *)sub_635514 >> 21 == 1697; /*0x635844*/
        HIDWORD(savedregs[2]) = 1822387990; /*0x635854*/
        break;
      case 0x27C16A20: /*0x6355c4*/
        _ReadStatusReg(TPIDR_EL0); /*0x6357d8*/
        sub_63A250(result); /*0x6357ec*/
      case 0x4210158F: /*0x6355c4*/
        if ( (savedregs[1] & 0x1000000000000LL) != 0 ) /*0x635920*/
          v5 = -186873334; /*0x635920*/
        else
          v5 = -1553194250; /*0x635920*/
        HIDWORD(savedregs[2]) = v5; /*0x635928*/
        break;
      case 0x4402FEAE: /*0x6355c4*/
        HIDWORD(savedregs[2]) = 611500005; /*0x635810*/
        break;
      case 0x4CD28796: /*0x6355c4*/
        BYTE6(savedregs[1]) = (loc_635518 >> 10 == 3508160 && loc_63551C >> 10 == 3508160) /*0x6358ec*/
                            | (loc_635518 >> 10 == 3508160) ^ (loc_63551C >> 10 == 3508160);
        HIDWORD(savedregs[2]) = 1108350351; /*0x6358fc*/
        break;
      case 0x6C9F6F16: /*0x6355c4*/
        if ( (savedregs[1] & 0x100000000000000LL) != 0 ) /*0x635878*/
          v4 = -186873334; /*0x635878*/
        else
          v4 = -534798252; /*0x635878*/
        HIDWORD(savedregs[2]) = v4; /*0x635880*/
        break;
      default:
        HIDWORD(savedregs[2]) = 1141046958; /*0x635738*/
        break;
    }
  }
  _ReadStatusReg(TPIDR_EL0); /*0x6357a0*/
  return result; /*0x6357c0*/
}