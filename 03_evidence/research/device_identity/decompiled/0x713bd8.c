__int64 __fastcall sub_713BD8(__int64 result)
{
  _QWORD *v1; // x19
  int v2; // w8
  int v3; // w8
  int v4; // w8
  _QWORD savedregs[4]; // [xsp+20h] [xbp+0h] BYREF

  v1 = (_QWORD *)result; /*0x713be8*/
  savedregs[3] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x713bf4*/
  savedregs[2] = 0xE146A9FF02818586LL; /*0x713c00*/
  savedregs[0] = (char *)&savedregs[2] + 4; /*0x713c14*/
  while ( 1 ) /*0x713d04*/
  {
    while ( 1 ) /*0x713cf0*/
    {
      while ( 1 ) /*0x713cdc*/
      {
        while ( 1 ) /*0x713cc8*/
        {
          while ( 1 ) /*0x713ca0*/
          {
            while ( 1 ) /*0x713c8c*/
            {
              while ( 1 ) /*0x713c50*/
              {
                while ( 1 ) /*0x713c3c*/
                {
                  while ( 1 ) /*0x713c28*/
                  {
                    while ( HIDWORD(savedregs[2]) == -1648244324 ) /*0x713c28*/
                    {
                      LODWORD(savedregs[2]) = (_DWORD)v1; /*0x713de8*/
                      result = sub_725814(v1); /*0x713df4*/
                      *v1 = &off_793FB0; /*0x713e08*/
                      HIDWORD(savedregs[2]) = 1116742736; /*0x713e18*/
                    }
                    if ( HIDWORD(savedregs[2]) != -1547936832 ) /*0x713c3c*/
                      break; /*0x713c3c*/
                    HIDWORD(savedregs[2]) = 1128067688; /*0x713e50*/
                  }
                  if ( HIDWORD(savedregs[2]) != -1353324635 ) /*0x713c50*/
                    break; /*0x713c50*/
                  if ( (savedregs[1] & 0x100000000000000LL) != 0 ) /*0x713f80*/
                    v4 = -1547936832; /*0x713f80*/
                  else
                    v4 = -450221357; /*0x713f80*/
                  HIDWORD(savedregs[2]) = v4; /*0x713f88*/
                }
                if ( HIDWORD(savedregs[2]) != -1039765194 ) /*0x713c8c*/
                  break; /*0x713c8c*/
                HIDWORD(savedregs[2]) = -420124961; /*0x713efc*/
              }
              if ( HIDWORD(savedregs[2]) != -515462657 ) /*0x713ca0*/
                break; /*0x713ca0*/
              if ( LODWORD(savedregs[2]) == 828820823 ) /*0x713d94*/
                v2 = 1891422097; /*0x713d94*/
              else
                v2 = -248227470; /*0x713d94*/
              HIDWORD(savedregs[2]) = v2; /*0x713d9c*/
            }
            if ( HIDWORD(savedregs[2]) != -450221357 ) /*0x713cc8*/
              break; /*0x713cc8*/
            HIDWORD(savedregs[2]) = -1648244324; /*0x713dd8*/
          }
          if ( HIDWORD(savedregs[2]) != -420124961 ) /*0x713cdc*/
            break; /*0x713cdc*/
          HIBYTE(savedregs[1]) = loc_713BDC >> 10 == 3508160 || loc_713BE0 >> 10 == 3508160; /*0x713f4c*/
          HIDWORD(savedregs[2]) = -1353324635; /*0x713f5c*/
        }
        if ( HIDWORD(savedregs[2]) != -248227470 ) /*0x713cf0*/
          break; /*0x713cf0*/
        HIDWORD(savedregs[2]) = 699979513; /*0x713db0*/
      }
      if ( HIDWORD(savedregs[2]) != 699979513 ) /*0x713d04*/
        break; /*0x713d04*/
      HIDWORD(savedregs[2]) = 786260500; /*0x713dc4*/
    }
    if ( HIDWORD(savedregs[2]) != 786260500 ) /*0x713d18*/
      break; /*0x713d18*/
    if ( ((((((*(_DWORD *)sub_713BD8 >> 26 == 5) << 31 >> 31) /*0x713ee0*/
           + (((*(_DWORD *)sub_713BD8 >> 26 == 5) ^ (*(_DWORD *)sub_713BD8 >> 21 == 1697)) << 31 >> 31)) << 31 >> 31)
         - (((*(_DWORD *)sub_713BD8 >> 26 == 5) & (unsigned __int8)(*(_DWORD *)sub_713BD8 >> 21 != 1697)) << 31 >> 31))
        & 1) != 0 )
      v3 = -1547936832; /*0x713ee0*/
    else
      v3 = -1039765194; /*0x713ee0*/
    HIDWORD(savedregs[2]) = v3; /*0x713ee8*/
  }
  if ( HIDWORD(savedregs[2]) != 1116742736 ) /*0x713d40*/
  {
    if ( HIDWORD(savedregs[2]) != 1128067688 ) /*0x713d54*/
      JUMPOUT(0x713F94); /*0x713f94*/
    _ReadStatusReg(TPIDR_EL0); /*0x713e58*/
    abort(); /*0x713e6c*/
  }
  _ReadStatusReg(TPIDR_EL0); /*0x713e20*/
  return result; /*0x713e40*/
}