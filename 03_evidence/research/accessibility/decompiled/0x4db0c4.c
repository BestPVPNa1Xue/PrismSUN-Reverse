unsigned __int64 __fastcall sub_4DB0C4(unsigned __int64 *a1)
{
  int v1; // w8
  unsigned __int64 result; // x0
  int v3; // w8
  int v4; // w8
  char v5; // [xsp+27h] [xbp-9h]
  unsigned __int64 v6; // [xsp+28h] [xbp-8h]
  unsigned __int64 savedregs; // [xsp+30h] [xbp+0h]
  __int64 savedregs_8; // [xsp+38h] [xbp+8h]

  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x4db0d8*/
  savedregs = 0xE4F0B280F1D9F17CLL; /*0x4db0e4*/
  while ( 1 ) /*0x4db15c*/
  {
    while ( 1 ) /*0x4db148*/
    {
      while ( 1 ) /*0x4db134*/
      {
        while ( 1 ) /*0x4db114*/
        {
          if ( HIDWORD(savedregs) == -798416038 ) /*0x4db120*/
            JUMPOUT(0x4DB3F8); /*0x4db3f8*/
          if ( HIDWORD(savedregs) != -793148885 ) /*0x4db134*/
            break; /*0x4db134*/
          HIDWORD(savedregs) = 1765237016; /*0x4db310*/
        }
        if ( HIDWORD(savedregs) != -453987712 ) /*0x4db148*/
          break; /*0x4db148*/
        if ( (unsigned int)savedregs >= 0xF665B9CF ) /*0x4db23c*/
          v1 = -798416038; /*0x4db23c*/
        else
          v1 = 1759205822; /*0x4db23c*/
        HIDWORD(savedregs) = v1; /*0x4db244*/
      }
      if ( HIDWORD(savedregs) != -300029638 ) /*0x4db15c*/
        break; /*0x4db15c*/
      savedregs = *a1; /*0x4db2a4*/
      *a1 = 0; /*0x4db2a8*/
      v6 = savedregs; /*0x4db2b0*/
      HIDWORD(savedregs) = 79083392; /*0x4db2c0*/
    }
    if ( HIDWORD(savedregs) == 79083392 ) /*0x4db170*/
      break; /*0x4db170*/
    switch ( HIDWORD(savedregs) ) /*0x4db184*/
    {
      case 0xD3460EA: /*0x4db184*/
        if ( loc_4DB0C8 >> 10 == 3508160 || loc_4DB0CC >> 10 == 3508160 ) /*0x4db3e4*/
          v4 = 1551965874; /*0x4db3e8*/
        else
          v4 = 659251048; /*0x4db3e8*/
        HIDWORD(savedregs) = v4; /*0x4db3f0*/
        break;
      case 0x274B5F68: /*0x4db184*/
        HIDWORD(savedregs) = -300029638; /*0x4db280*/
        break;
      case 0x5B1B89A4: /*0x4db184*/
        HIDWORD(savedregs) = -793148885; /*0x4db26c*/
        break;
      case 0x5C811EB2: /*0x4db184*/
        _ReadStatusReg(TPIDR_EL0); /*0x4db2ec*/
        abort(); /*0x4db300*/
      case 0x60802E6F: /*0x4db184*/
        if ( (v5 & 1) != 0 ) /*0x4db380*/
          v3 = 1551965874; /*0x4db380*/
        else
          v3 = 221536490; /*0x4db380*/
        HIDWORD(savedregs) = v3; /*0x4db388*/
        break;
      case 0x68DB59BE: /*0x4db184*/
        HIDWORD(savedregs) = 1528531364; /*0x4db258*/
        break;
      default:
        v5 = (*(_DWORD *)sub_4DB0C4 >> 26 == 5 && *(_DWORD *)sub_4DB0C4 >> 21 == 1697) /*0x4db34c*/
           | (*(_DWORD *)sub_4DB0C4 >> 26 == 5) ^ (*(_DWORD *)sub_4DB0C4 >> 21 == 1697);
        HIDWORD(savedregs) = 1619013231; /*0x4db35c*/
        break;
    }
  }
  result = v6; /*0x4db2c8*/
  _ReadStatusReg(TPIDR_EL0); /*0x4db2cc*/
  return result; /*0x4db2e8*/
}