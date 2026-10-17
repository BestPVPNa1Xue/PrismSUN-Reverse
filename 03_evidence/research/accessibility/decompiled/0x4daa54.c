_QWORD *__fastcall sub_4DAA54(_QWORD *result, __int64 a2)
{
  int v2; // w8
  int v3; // w8
  int v4; // w8
  unsigned __int64 savedregs; // [xsp+20h] [xbp+0h]
  __int64 savedregs_8; // [xsp+28h] [xbp+8h]

  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x4daa68*/
  savedregs = 0xD6E4059679D8EA6ELL; /*0x4daa74*/
  while ( 1 ) /*0x4daad8*/
  {
    while ( 1 ) /*0x4daa8c*/
    {
      if ( HIDWORD(savedregs) == -1984266841 ) /*0x4daa9c*/
        JUMPOUT(0x4DAD80); /*0x4dad80*/
      if ( HIDWORD(savedregs) != -1141146219 ) /*0x4daad8*/
        break; /*0x4daad8*/
      HIDWORD(savedregs) = 100166346; /*0x4dabfc*/
    }
    if ( HIDWORD(savedregs) == -904863166 ) /*0x4daaec*/
      break; /*0x4daaec*/
    switch ( HIDWORD(savedregs) ) /*0x4dab00*/
    {
      case 0xD6E40596: /*0x4dab00*/
        if ( (_DWORD)savedregs == -1700345223 ) /*0x4dabcc*/
          v2 = -1984266841; /*0x4dabcc*/
        else
          v2 = 808520644; /*0x4dabcc*/
        HIDWORD(savedregs) = v2; /*0x4dabd4*/
        break;
      case 0xE3A08090: /*0x4dab00*/
        HIDWORD(savedregs) = 1483774657; /*0x4dac7c*/
        break;
      case 0x5F86ACA: /*0x4dab00*/
        if ( *(_DWORD *)sub_4DAA54 >> 26 != 5 && *(_DWORD *)sub_4DAA54 >> 21 != 1697 ) /*0x4dace4*/
          v3 = 1653580777; /*0x4dad04*/
        else
          v3 = -476020592; /*0x4dad04*/
        HIDWORD(savedregs) = v3; /*0x4dad0c*/
        break;
      case 0x2B3FC121: /*0x4dab00*/
        savedregs = (unsigned int)a2 | 0xCA10E24200000000LL; /*0x4dac2c*/
        *result = a2; /*0x4dac38*/
        break;
      case 0x30310BC4: /*0x4dab00*/
        HIDWORD(savedregs) = -1141146219; /*0x4dabe8*/
        break;
      case 0x58709AC1: /*0x4dab00*/
        _ReadStatusReg(TPIDR_EL0); /*0x4dac84*/
        abort(); /*0x4dac98*/
      case 0x628FA3E9: /*0x4dab00*/
        if ( loc_4DAA58 >> 10 == 3508160 || loc_4DAA5C >> 10 == 3508160 ) /*0x4dad68*/
          v4 = -476020592; /*0x4dad6c*/
        else
          v4 = 1816878541; /*0x4dad6c*/
        HIDWORD(savedregs) = v4; /*0x4dad74*/
        break;
      default:
        HIDWORD(savedregs) = 725598497; /*0x4dac10*/
        break;
    }
  }
  _ReadStatusReg(TPIDR_EL0); /*0x4dac50*/
  return result; /*0x4dac6c*/
}