__int64 __fastcall sub_320D04(__int64 a1, __int64 a2, __int64 a3)
{
  int v5; // w8
  __int64 result; // x0
  int v7; // w8
  int v8; // w8
  char v9; // [xsp+46h] [xbp+16h]
  char v10; // [xsp+47h] [xbp+17h]
  __int64 v11; // [xsp+48h] [xbp+18h]
  __int64 i; // [xsp+50h] [xbp+20h]
  __int64 savedregs_8; // [xsp+58h] [xbp+28h]

  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x320d2c*/
  for ( i = 0x832A0F2E61A790FLL; ; HIDWORD(i) = 428047171 ) /*0x320d38*/
  {
    while ( 1 ) /*0x320e78*/
    {
      while ( 1 ) /*0x320e50*/
      {
        while ( 1 ) /*0x320e3c*/
        {
          while ( 1 ) /*0x320e28*/
          {
            while ( 1 ) /*0x320e14*/
            {
              while ( 1 ) /*0x320dec*/
              {
                while ( 1 ) /*0x320dd8*/
                {
                  while ( 1 ) /*0x320dc4*/
                  {
                    while ( 1 ) /*0x320d74*/
                    {
                      while ( 1 ) /*0x320d60*/
                      {
                        while ( HIDWORD(i) == -1964284404 ) /*0x320d60*/
                        {
                          i = (unsigned int)a3 | 0x6394AB1800000000LL; /*0x320f74*/
                          v11 = (*(__int64 (__fastcall **)(__int64, __int64, __int64))(*(_QWORD *)a2 + 1160LL))( /*0x320f90*/
                                  a2,
                                  a2,
                                  a3);
                        }
                        if ( HIDWORD(i) != -1433706959 ) /*0x320d74*/
                          break; /*0x320d74*/
                        HIDWORD(i) = -1964284404; /*0x320f4c*/
                      }
                      if ( HIDWORD(i) != -1189533076 ) /*0x320dc4*/
                        break; /*0x320dc4*/
                      if ( (v10 & 1) != 0 ) /*0x3210ac*/
                        v7 = 568018978; /*0x3210ac*/
                      else
                        v7 = -202928134; /*0x3210ac*/
                      HIDWORD(i) = v7; /*0x3210b4*/
                    }
                    if ( HIDWORD(i) != -1079396542 ) /*0x320dd8*/
                      break; /*0x320dd8*/
                    v9 = (((((((loc_320D08 >> 10 == 3508160) << 31 >> 31) + ((loc_320D0C >> 10 == 3508160) << 31 >> 31)) << 31 >> 31) /*0x32113c*/
                          - 1) << 31 >> 31)
                        + ((loc_320D0C >> 10 != 3508160 || loc_320D08 >> 10 != 3508160) << 31 >> 31))
                       & 1;
                    HIDWORD(i) = 205340924; /*0x32114c*/
                  }
                  if ( HIDWORD(i) != -927856883 ) /*0x320dec*/
                    break; /*0x320dec*/
                  HIDWORD(i) = 2134757149; /*0x320f38*/
                }
                if ( HIDWORD(i) != -202928134 ) /*0x320e14*/
                  break; /*0x320e14*/
                HIDWORD(i) = -1079396542; /*0x3210c8*/
              }
              if ( HIDWORD(i) != 137535730 ) /*0x320e28*/
                break; /*0x320e28*/
              if ( (unsigned int)i <= 0xE658CD42 ) /*0x320f08*/
                v5 = 975745063; /*0x320f08*/
              else
                v5 = 937890151; /*0x320f08*/
              HIDWORD(i) = v5; /*0x320f10*/
            }
            if ( HIDWORD(i) != 205340924 ) /*0x320e3c*/
              break; /*0x320e3c*/
            if ( (v9 & 1) != 0 ) /*0x321170*/
              v8 = 568018978; /*0x321170*/
            else
              v8 = -1433706959; /*0x321170*/
            HIDWORD(i) = v8; /*0x321178*/
          }
          if ( HIDWORD(i) != 428047171 ) /*0x320e50*/
            break; /*0x320e50*/
          v10 = (((((((*(_DWORD *)sub_320D04 >> 26 == 5) << 31 >> 31) /*0x321078*/
                   + ((*(_DWORD *)sub_320D04 >> 21 == 1697) << 31 >> 31)) << 31 >> 31)
                 - 1) << 31 >> 31)
               + ((*(_DWORD *)sub_320D04 >> 21 != 1697 || *(_DWORD *)sub_320D04 >> 26 != 5) << 31 >> 31))
              & 1;
          HIDWORD(i) = -1189533076; /*0x321088*/
        }
        if ( HIDWORD(i) == 501849243 ) /*0x320e64*/
        {
          _ReadStatusReg(TPIDR_EL0); /*0x320fe8*/
          sub_34ABC0(); /*0x320ffc*/
        }
        if ( HIDWORD(i) != 568018978 ) /*0x320e78*/
          break; /*0x320e78*/
        HIDWORD(i) = 501849243; /*0x320fe0*/
      }
      if ( HIDWORD(i) == 937890151 ) /*0x320e8c*/
        JUMPOUT(0x321180); /*0x321180*/
      if ( HIDWORD(i) != 975745063 ) /*0x320ea0*/
        break; /*0x320ea0*/
      HIDWORD(i) = -927856883; /*0x320f24*/
    }
    if ( HIDWORD(i) == 1670687512 ) /*0x320eb4*/
      break; /*0x320eb4*/
  }
  result = v11; /*0x320fa8*/
  _ReadStatusReg(TPIDR_EL0); /*0x320fac*/
  return result; /*0x320fd0*/
}