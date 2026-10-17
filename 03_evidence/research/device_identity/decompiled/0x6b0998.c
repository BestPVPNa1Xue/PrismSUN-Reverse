__int64 __fastcall sub_6B0998(__int64 *a1)
{
  __int64 result; // x0
  int v2; // w8
  int v3; // w8
  bool v4; // [xsp+16h] [xbp-1Ah]
  char v5; // [xsp+17h] [xbp-19h]
  __int64 v6; // [xsp+18h] [xbp-18h]
  int v7; // [xsp+24h] [xbp-Ch]

  _ReadStatusReg(TPIDR_EL0); /*0x6b09a4*/
  v7 = 74647834; /*0x6b09bc*/
  while ( 1 ) /*0x6b0a8c*/
  {
    while ( 1 ) /*0x6b0a64*/
    {
      while ( 1 ) /*0x6b0a14*/
      {
        while ( 1 ) /*0x6b0a00*/
        {
          while ( 1 ) /*0x6b09ec*/
          {
            while ( 1 ) /*0x6b09d8*/
            {
              while ( v7 == -2144490011 ) /*0x6b09d8*/
              {
                if ( (v5 & 1) != 0 ) /*0x6b0cf8*/
                  v2 = 377619587; /*0x6b0cf8*/
                else
                  v2 = 334682320; /*0x6b0cf8*/
                v7 = v2; /*0x6b0d00*/
              }
              if ( v7 != -1884103899 ) /*0x6b09ec*/
                break; /*0x6b09ec*/
              v7 = 1730657316; /*0x6b0b9c*/
            }
            if ( v7 != -1761401433 ) /*0x6b0a00*/
              break; /*0x6b0a00*/
            if ( v4 ) /*0x6b0d80*/
              v3 = 377619587; /*0x6b0d98*/
            else
              v3 = -831059950; /*0x6b0d98*/
            v7 = v3; /*0x6b0da0*/
          }
          if ( v7 != -1745157339 ) /*0x6b0a14*/
            break; /*0x6b0a14*/
          v6 = *a1; /*0x6b0be0*/
          v7 = 240228648; /*0x6b0bf0*/
        }
        if ( v7 == -1728953467 ) /*0x6b0a28*/
        {
          _ReadStatusReg(TPIDR_EL0); /*0x6b0c30*/
          sub_6B69BC(a1); /*0x6b0c44*/
        }
        if ( v7 != -831059950 ) /*0x6b0a64*/
          break; /*0x6b0a64*/
        v7 = -1745157339; /*0x6b0bc4*/
      }
      if ( v7 != 74647834 ) /*0x6b0a8c*/
        break; /*0x6b0a8c*/
      v7 = -1884103899; /*0x6b0b88*/
    }
    if ( v7 == 240228648 ) /*0x6b0ab4*/
      break; /*0x6b0ab4*/
    switch ( v7 ) /*0x6b0ac8*/
    {
      case 334682320: /*0x6b0ac8*/
        v7 = 622014637; /*0x6b0d14*/
        break;
      case 377619587: /*0x6b0ac8*/
        v7 = -1728953467; /*0x6b0c28*/
        break;
      case 622014637: /*0x6b0ac8*/
        v4 = loc_6B099C >> 10 == 3508160 || loc_6B09A0 >> 10 == 3508160; /*0x6b0d64*/
        v7 = -1761401433; /*0x6b0d74*/
        break;
      case 935721084: /*0x6b0ac8*/
        v5 = (*(_DWORD *)sub_6B0998 >> 26 != 5) ^ (*(_DWORD *)sub_6B0998 >> 21 != 1697) /*0x6b0cc4*/
           | (*(_DWORD *)sub_6B0998 >> 26 == 5 && *(_DWORD *)sub_6B0998 >> 21 == 1697);
        v7 = -2144490011; /*0x6b0cd4*/
        break;
      case 1730657316: /*0x6b0ac8*/
        v7 = 1860349465; /*0x6b0bb0*/
        break;
      default:
        v7 = 935721084; /*0x6b0c68*/
        break;
    }
  }
  result = v6; /*0x6b0bf8*/
  _ReadStatusReg(TPIDR_EL0); /*0x6b0bfc*/
  return result; /*0x6b0c18*/
}