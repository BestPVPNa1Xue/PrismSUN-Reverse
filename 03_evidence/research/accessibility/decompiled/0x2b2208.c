__int64 __fastcall sub_2B2208(unsigned int a1)
{
  __int64 result; // x0
  int v2; // w8
  int v3; // w8
  bool v4; // [xsp+1Dh] [xbp-15h]
  unsigned int v5; // [xsp+1Eh] [xbp-14h]
  int v6; // [xsp+26h] [xbp-Ch]

  _ReadStatusReg(TPIDR_EL0); /*0x2b2214*/
  v6 = 1411777090; /*0x2b2234*/
  while ( 1 ) /*0x2b2250*/
  {
    while ( v6 == -1950832798 ) /*0x2b2250*/
    {
      v4 = loc_2B220C >> 10 == 3508160 || loc_2B2210 >> 10 == 3508160; /*0x2b255c*/
      v6 = -315610317; /*0x2b256c*/
    }
    if ( v6 == -1726425730 ) /*0x2b2264*/
      break; /*0x2b2264*/
    switch ( v6 ) /*0x2b228c*/
    {
      case -1040867082: /*0x2b228c*/
        _ReadStatusReg(TPIDR_EL0); /*0x2b2468*/
        sub_2DB4B8(); /*0x2b247c*/
      case -403195354: /*0x2b228c*/
        v6 = 960680196; /*0x2b23d8*/
        break;
      case -338524785: /*0x2b228c*/
        if ( ((((((*(_DWORD *)sub_2B2208 >> 26 == 5) << 31 >> 31) /*0x2b24f0*/
               + (((*(_DWORD *)sub_2B2208 >> 26 == 5) ^ (*(_DWORD *)sub_2B2208 >> 21 == 1697)) << 31 >> 31)) << 31 >> 31)
             - (((*(_DWORD *)sub_2B2208 >> 26 == 5) & (unsigned __int8)(*(_DWORD *)sub_2B2208 >> 21 != 1697)) << 31 >> 31))
            & 1) != 0 )
          v2 = 32254784; /*0x2b24f0*/
        else
          v2 = 385637750; /*0x2b24f0*/
        v6 = v2; /*0x2b24f8*/
        break;
      case -315610317: /*0x2b228c*/
        if ( v4 ) /*0x2b2578*/
          v3 = 32254784; /*0x2b2590*/
        else
          v3 = 1090317175; /*0x2b2590*/
        v6 = v3; /*0x2b2598*/
        break;
      case 32254784: /*0x2b228c*/
        v6 = -1040867082; /*0x2b2460*/
        break;
      case 385637750: /*0x2b228c*/
        v6 = -1950832798; /*0x2b250c*/
        break;
      case 960680196: /*0x2b228c*/
        v6 = -338524785; /*0x2b23ec*/
        break;
      case 1090317175: /*0x2b228c*/
        v6 = 1505041366; /*0x2b2400*/
        break;
      case 1411777090: /*0x2b228c*/
        v6 = -403195354; /*0x2b23c4*/
        break;
      default:
        v5 = a1; /*0x2b2418*/
        v6 = -1726425730; /*0x2b2428*/
        break;
    }
  }
  result = v5; /*0x2b2430*/
  _ReadStatusReg(TPIDR_EL0); /*0x2b2434*/
  return result; /*0x2b2450*/
}