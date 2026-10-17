__int64 __fastcall sub_2E0A2C(
        __int64 a1,
        __int64 a2,
        __int64 a3,
        __int64 a4,
        __int64 a5,
        __int64 a6,
        __int64 a7,
        __int64 a8,
        __int64 a9,
        __int64 a10,
        __int64 a11,
        __int64 a12,
        __int64 a13,
        __int64 a14,
        __int64 a15,
        __int64 a16,
        __int64 a17)
{
  int v17; // w8
  __int64 v18; // x19
  __int64 v19; // x20
  __int64 v20; // x0
  __int64 v21; // x8
  __int64 result; // x0
  int v23; // w8
  int v24; // w8
  __int64 v25; // [xsp+48h] [xbp-98h]
  __int64 *savedregs; // [xsp+100h] [xbp+20h]
  __int64 savedregs_8; // [xsp+108h] [xbp+28h]
  __int64 savedregs_16; // [xsp+110h] [xbp+30h]
  __int64 savedregs_24; // [xsp+118h] [xbp+38h]
  unsigned __int64 savedregs_24a; // [xsp+118h] [xbp+38h]

  savedregs_24 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x2e0a80*/
  savedregs_16 = 0x4D14A6C352F23309LL; /*0x2e0a8c*/
  while ( 1 ) /*0x2e0b90*/
  {
    while ( 1 ) /*0x2e0b68*/
    {
      while ( 1 ) /*0x2e0b54*/
      {
        while ( 1 ) /*0x2e0b40*/
        {
          while ( 1 ) /*0x2e0b04*/
          {
            while ( 1 ) /*0x2e0af0*/
            {
              while ( 1 ) /*0x2e0ac8*/
              {
                while ( 1 ) /*0x2e0ab4*/
                {
                  while ( HIDWORD(savedregs_16) == -1241783868 ) /*0x2e0ab4*/
                  {
                    if ( (HIBYTE(savedregs) & 1) != 0 ) /*0x2e0e30*/
                      v23 = -123139373; /*0x2e0e30*/
                    else
                      v23 = -117733862; /*0x2e0e30*/
                    HIDWORD(savedregs_16) = v23; /*0x2e0e38*/
                  }
                  if ( HIDWORD(savedregs_16) != -369454211 ) /*0x2e0ac8*/
                    break; /*0x2e0ac8*/
                  BYTE6(savedregs) = (((((loc_2E0A30 >> 10 == 3508160) << 31 >> 31) /*0x2e0ebc*/
                                      + (((loc_2E0A30 >> 10 == 3508160) ^ (loc_2E0A34 >> 10 == 3508160)) << 31 >> 31)) << 31 >> 31)
                                    - (((loc_2E0A30 >> 10 == 3508160) & (unsigned __int8)(loc_2E0A34 >> 10 != 3508160)) << 31 >> 31))
                                   & 1;
                  HIDWORD(savedregs_16) = 1605101572; /*0x2e0ecc*/
                }
                if ( HIDWORD(savedregs_16) == -123139373 ) /*0x2e0adc*/
                {
                  _ReadStatusReg(TPIDR_EL0); /*0x2e0d88*/
                  abort(); /*0x2e0d9c*/
                }
                if ( HIDWORD(savedregs_16) != -117733862 ) /*0x2e0af0*/
                  break; /*0x2e0af0*/
                HIDWORD(savedregs_16) = -369454211; /*0x2e0e4c*/
              }
              if ( HIDWORD(savedregs_16) != 95831537 ) /*0x2e0b04*/
                break; /*0x2e0b04*/
              HIDWORD(savedregs_16) = 868102992; /*0x2e0c3c*/
            }
            if ( HIDWORD(savedregs_16) == 479151687 ) /*0x2e0b2c*/
              JUMPOUT(0x2E0F00); /*0x2e0f00*/
            if ( HIDWORD(savedregs_16) != 648944498 ) /*0x2e0b40*/
              break; /*0x2e0b40*/
            HIBYTE(savedregs) = *(_DWORD *)sub_2E0A2C >> 26 == 5 || *(_DWORD *)sub_2E0A2C >> 21 == 1697; /*0x2e0dfc*/
            HIDWORD(savedregs_16) = -1241783868; /*0x2e0e0c*/
          }
          if ( HIDWORD(savedregs_16) != 868102992 ) /*0x2e0b54*/
            break; /*0x2e0b54*/
          HIDWORD(savedregs_16) = 996898790; /*0x2e0c50*/
        }
        if ( HIDWORD(savedregs_16) != 996898790 ) /*0x2e0b68*/
          break; /*0x2e0b68*/
        HIDWORD(savedregs_16) = 648944498; /*0x2e0dac*/
      }
      if ( HIDWORD(savedregs_16) != 1293199043 ) /*0x2e0b90*/
        break; /*0x2e0b90*/
      if ( (_DWORD)savedregs_16 == -704257376 ) /*0x2e0c20*/
        v17 = 479151687; /*0x2e0c20*/
      else
        v17 = 95831537; /*0x2e0c20*/
      HIDWORD(savedregs_16) = v17; /*0x2e0c28*/
    }
    if ( HIDWORD(savedregs_16) == 1440525631 ) /*0x2e0ba4*/
      break; /*0x2e0ba4*/
    if ( HIDWORD(savedregs_16) == 1526125174 ) /*0x2e0bb8*/
    {
      HIDWORD(savedregs_16) = 1943141628; /*0x2e0c64*/
    }
    else if ( HIDWORD(savedregs_16) == 1605101572 ) /*0x2e0bcc*/
    {
      if ( (BYTE6(savedregs) & 1) != 0 ) /*0x2e0ef0*/
        v24 = -123139373; /*0x2e0ef0*/
      else
        v24 = 1526125174; /*0x2e0ef0*/
      HIDWORD(savedregs_16) = v24; /*0x2e0ef8*/
    }
    else
    {
      savedregs = &a17; /*0x2e0cf0*/
      savedregs_24a = 0xFFFFFF80FFFFFFD8LL; /*0x2e0d08*/
      v25 = a1; /*0x2e0d0c*/
      v18 = a2; /*0x2e0d14*/
      v19 = a3; /*0x2e0d1c*/
      v20 = (*(__int64 (__fastcall **)(__int64, __int64 *, __int64 *))(*(_QWORD *)a3 + 920LL))(a3, &a17, &a17); /*0x2e0d24*/
      a2 = v18; /*0x2e0d28*/
      a3 = v19; /*0x2e0d2c*/
      v21 = v20; /*0x2e0d30*/
      a1 = v25; /*0x2e0d34*/
      savedregs_16 = (unsigned int)v21 | 0x55DCAD3F00000000LL; /*0x2e0d38*/
      savedregs_8 = v21; /*0x2e0d40*/
    }
  }
  result = savedregs_8; /*0x2e0d58*/
  _ReadStatusReg(TPIDR_EL0); /*0x2e0d5c*/
  return result; /*0x2e0d84*/
}