__int64 __fastcall sub_71BBB4(__int64 a1)
{
  int v3; // w8
  __int64 v4; // x8
  __int64 result; // x0
  int v6; // w8
  int v7; // w8
  __int64 v13; // [xsp+20h] [xbp-10h]
  bool v14; // [xsp+36h] [xbp+6h]
  bool v15; // [xsp+37h] [xbp+7h]
  __int64 v16; // [xsp+38h] [xbp+8h]
  unsigned int v17; // [xsp+40h] [xbp+10h]
  int i; // [xsp+44h] [xbp+14h]

  _ReadStatusReg(TPIDR_EL0); /*0x71bbc4*/
  v17 = -1872070051; /*0x71bbd8*/
  for ( i = 684013551; ; i = 1452409386 ) /*0x71bbe4*/
  {
    while ( 1 ) /*0x71bd2c*/
    {
      while ( 1 ) /*0x71bd18*/
      {
        while ( 1 ) /*0x71bcf0*/
        {
          while ( 1 ) /*0x71bcdc*/
          {
            while ( 1 ) /*0x71bcb4*/
            {
              while ( 1 ) /*0x71bca0*/
              {
                while ( 1 ) /*0x71bc8c*/
                {
                  while ( 1 ) /*0x71bc64*/
                  {
                    while ( 1 ) /*0x71bc50*/
                    {
                      while ( 1 ) /*0x71bc14*/
                      {
                        while ( 1 ) /*0x71bc00*/
                        {
                          while ( i == -1864230370 ) /*0x71bc00*/
                          {
                            __asm { BFMMLA V20.4S, V21.8H, V18.8H } /*0x71bfc0*/
                            i = 1948662258; /*0x71bfd4*/
                          }
                          if ( i != -1284000287 ) /*0x71bc14*/
                            break; /*0x71bc14*/
                          if ( v14 ) /*0x71bf94*/
                            v7 = -150360155; /*0x71bfac*/
                          else
                            v7 = 772985755; /*0x71bfac*/
                          i = v7; /*0x71bfb4*/
                        }
                        if ( i == -1162313770 ) /*0x71bc28*/
                        {
                          _ReadStatusReg(TPIDR_EL0); /*0x71be6c*/
                          sub_725B44(); /*0x71be80*/
                        }
                        if ( i != -821105566 ) /*0x71bc50*/
                          break; /*0x71bc50*/
                        i = 501090506; /*0x71bea4*/
                      }
                      if ( i != -320374876 ) /*0x71bc64*/
                        break; /*0x71bc64*/
                      v14 = loc_71BBB8 >> 10 == 3508160 || loc_71BBBC >> 10 == 3508160; /*0x71bf78*/
                      i = -1284000287; /*0x71bf88*/
                    }
                    if ( i != -150360155 ) /*0x71bc8c*/
                      break; /*0x71bc8c*/
                    i = -1162313770; /*0x71be64*/
                  }
                  if ( i != -140257541 ) /*0x71bca0*/
                    break; /*0x71bca0*/
                  i = -320374876; /*0x71bf28*/
                }
                if ( i != 501090506 ) /*0x71bcb4*/
                  break; /*0x71bcb4*/
                v15 = *(_DWORD *)sub_71BBB4 >> 26 == 5 || *(_DWORD *)sub_71BBB4 >> 21 == 1697; /*0x71bed8*/
                i = 1589405162; /*0x71bee8*/
              }
              if ( i != 684013551 ) /*0x71bcdc*/
                break; /*0x71bcdc*/
              if ( v17 >= 0x94F2B723 ) /*0x71bda8*/
                v3 = -1864230370; /*0x71bda8*/
              else
                v3 = 1948662258; /*0x71bda8*/
              i = v3; /*0x71bdb0*/
            }
            if ( i != 772985755 ) /*0x71bcf0*/
              break; /*0x71bcf0*/
            i = 1187867348; /*0x71bdec*/
          }
          if ( i != 1187867348 ) /*0x71bd18*/
            break; /*0x71bd18*/
          v17 = a1; /*0x71bdfc*/
          v13 = a1; /*0x71be04*/
          v4 = sub_725B40(a1); /*0x71be10*/
          a1 = v13; /*0x71be14*/
          v16 = v4; /*0x71be18*/
          i = 1644216526; /*0x71be28*/
        }
        if ( i != 1452409386 ) /*0x71bd2c*/
          break; /*0x71bd2c*/
        i = -821105566; /*0x71bdd8*/
      }
      if ( i != 1589405162 ) /*0x71bd40*/
        break; /*0x71bd40*/
      if ( v15 ) /*0x71bef4*/
        v6 = -150360155; /*0x71bf0c*/
      else
        v6 = -140257541; /*0x71bf0c*/
      i = v6; /*0x71bf14*/
    }
    if ( i == 1644216526 ) /*0x71bd54*/
      break; /*0x71bd54*/
  }
  result = v16; /*0x71be30*/
  _ReadStatusReg(TPIDR_EL0); /*0x71be34*/
  return result; /*0x71be54*/
}