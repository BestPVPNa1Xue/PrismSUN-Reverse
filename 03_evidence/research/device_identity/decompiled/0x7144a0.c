__int64 __usercall sub_7144A0@<X0>(__int64 a1@<X8>)
{
  int v2; // w8
  __int64 v3; // x0
  __int64 result; // x0
  int v5; // w8
  int v6; // w8
  bool v7; // [xsp+3Eh] [xbp+1Eh]
  char v8; // [xsp+3Fh] [xbp+1Fh]
  __int64 savedregs; // [xsp+40h] [xbp+20h]
  __int64 savedregs_8; // [xsp+48h] [xbp+28h]

  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x7144c4*/
  savedregs = 0x2714481C96E8F798LL; /*0x7144d0*/
  while ( 1 ) /*0x7144f8*/
  {
    while ( HIDWORD(savedregs) == -2029398564 ) /*0x7144f8*/
      HIDWORD(savedregs) = 1952204304; /*0x714860*/
    if ( HIDWORD(savedregs) == -1749857430 ) /*0x714534*/
      break; /*0x714534*/
    switch ( HIDWORD(savedregs) ) /*0x714548*/
    {
      case 0x9A6D8471: /*0x714548*/
        v8 = (*(_DWORD *)sub_7144A0 >> 26 == 5) ^ (*(_DWORD *)sub_7144A0 >> 21 == 1697) /*0x714810*/
           | (*(_DWORD *)sub_7144A0 >> 26 == 5 && *(_DWORD *)sub_7144A0 >> 21 == 1697);
        HIDWORD(savedregs) = 2109498120; /*0x714820*/
        break;
      case 0xA7263527: /*0x714548*/
        HIDWORD(savedregs) = 2038950913; /*0x7146bc*/
        break;
      case 0xB943BBC4: /*0x714548*/
        HIDWORD(savedregs) = 1034946041; /*0x7146e4*/
        break;
      case 0xC2805CCB: /*0x714548*/
        if ( v7 ) /*0x7148cc*/
          v6 = -280764954; /*0x7148e4*/
        else
          v6 = -1186743356; /*0x7148e4*/
        HIDWORD(savedregs) = v6; /*0x7148ec*/
        break;
      case 0xD42B5573: /*0x714548*/
        JUMPOUT(0x7148F4); /*0x7148f4*/
      case 0xE23E82FA: /*0x714548*/
        _ReadStatusReg(TPIDR_EL0); /*0x71477c*/
        abort(); /*0x714790*/
      case 0xEF43DDE6: /*0x714548*/
        HIDWORD(savedregs) = -499219718; /*0x714774*/
        break;
      case 0x2714481C: /*0x714548*/
        if ( (_DWORD)savedregs == 1201728355 ) /*0x7146a0*/
          v2 = -735357581; /*0x7146a0*/
        else
          v2 = -1490668249; /*0x7146a0*/
        HIDWORD(savedregs) = v2; /*0x7146a8*/
        break;
      case 0x3DB005F9: /*0x714548*/
        v3 = ((__int64 (*)(void))loc_716070)(); /*0x714714*/
        savedregs = ((__int64 (__fastcall *)(__int64))loc_716A70)(v3); /*0x71471c*/
        result = sub_C7BE8(a1, savedregs); /*0x714728*/
        HIDWORD(savedregs) = -1749857430; /*0x714738*/
        break;
      case 0x471F5402: /*0x714548*/
        HIDWORD(savedregs) = -1704098703; /*0x7147b4*/
        break;
      case 0x745C4610: /*0x714548*/
        v7 = loc_7144A4 >> 10 == 3508160 || loc_7144A8 >> 10 == 3508160; /*0x7148b0*/
        HIDWORD(savedregs) = -1031775029; /*0x7148c0*/
        break;
      case 0x7987EC01: /*0x714548*/
        HIDWORD(savedregs) = 1193235458; /*0x7146d0*/
        break;
      default:
        if ( (v8 & 1) != 0 ) /*0x714844*/
          v5 = -280764954; /*0x714844*/
        else
          v5 = -2029398564; /*0x714844*/
        HIDWORD(savedregs) = v5; /*0x71484c*/
        break;
    }
  }
  _ReadStatusReg(TPIDR_EL0); /*0x714740*/
  return result; /*0x714764*/
}