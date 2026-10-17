__int64 __fastcall sub_596B58(__int64 a1)
{
  __int64 result; // x0
  int v2; // w8
  int v3; // w8
  char v4; // [xsp+1Fh] [xbp-1h]
  unsigned __int64 savedregs; // [xsp+20h] [xbp+0h]
  __int64 savedregs_8; // [xsp+28h] [xbp+8h]

  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x596b6c*/
  savedregs = 0xECF78D5E0ABF9F7ALL; /*0x596b78*/
  while ( 1 ) /*0x596ba0*/
  {
    while ( HIDWORD(savedregs) == -1878882261 ) /*0x596ba0*/
    {
      if ( (v4 & 1) != 0 ) /*0x596db4*/
        v2 = 1072993036; /*0x596db4*/
      else
        v2 = -1345274016; /*0x596db4*/
      HIDWORD(savedregs) = v2; /*0x596dbc*/
    }
    if ( HIDWORD(savedregs) == -1534367074 ) /*0x596bb4*/
      break; /*0x596bb4*/
    switch ( HIDWORD(savedregs) ) /*0x596bc8*/
    {
      case 0xAF0EF5FC: /*0x596bc8*/
        HIDWORD(savedregs) = -1005274128; /*0x596cb0*/
        break;
      case 0xAFD0BF60: /*0x596bc8*/
        if ( ((((((((loc_596B5C >> 10 == 3508160) << 31 >> 31) + ((loc_596B60 >> 10 == 3508160) << 31 >> 31)) << 31 >> 31) /*0x596e40*/
               - 1) << 31 >> 31)
             + ((loc_596B60 >> 10 != 3508160 || loc_596B5C >> 10 != 3508160) << 31 >> 31))
            & 1) != 0 )
          v3 = 1072993036; /*0x596e40*/
        else
          v3 = -1534367074; /*0x596e40*/
        HIDWORD(savedregs) = v3; /*0x596e48*/
        break;
      case 0xC414BBF0: /*0x596bc8*/
        HIDWORD(savedregs) = 1875373136; /*0x596cc4*/
        break;
      case 0xECF78D5E: /*0x596bc8*/
        HIDWORD(savedregs) = -1357974020; /*0x596c9c*/
        break;
      case 0x1BBE0297: /*0x596bc8*/
        v4 = (((((*(_DWORD *)sub_596B58 >> 26 == 5) << 31 >> 31) /*0x596d80*/
              + (((*(_DWORD *)sub_596B58 >> 26 == 5) ^ (*(_DWORD *)sub_596B58 >> 21 == 1697)) << 31 >> 31)) << 31 >> 31)
            - (((*(_DWORD *)sub_596B58 >> 26 == 5) & (unsigned __int8)(*(_DWORD *)sub_596B58 >> 21 != 1697)) << 31 >> 31))
           & 1;
        HIDWORD(savedregs) = -1878882261; /*0x596d90*/
        break;
      case 0x3FF4930C: /*0x596bc8*/
        _ReadStatusReg(TPIDR_EL0); /*0x596d08*/
        sub_5A7A10(); /*0x596d1c*/
      default:
        HIDWORD(savedregs) = 465437335; /*0x596d2c*/
        break;
    }
  }
  result = *(_QWORD *)(a1 + 624); /*0x596cdc*/
  *(_QWORD *)(a1 + 624) = result + 1; /*0x596ce4*/
  _ReadStatusReg(TPIDR_EL0); /*0x596ce8*/
  return result; /*0x596d04*/
}