__int64 __usercall sub_58C5B0@<X0>(__int64 result@<X0>, __int64 a2@<X2>, _QWORD *a3@<X3>, __int64 a4@<X8>, __int64 a5)
{
  __int64 v5; // x19
  int v7; // w8
  unsigned int v8; // w21
  __int64 v9; // x0
  int v10; // w8
  int v11; // w8
  int v12; // w8
  char v13; // [xsp+56h] [xbp+16h]
  char v14; // [xsp+57h] [xbp+17h]
  unsigned __int8 *v15; // [xsp+58h] [xbp+18h]
  _QWORD savedregs[4]; // [xsp+60h] [xbp+20h] BYREF

  v5 = result; /*0x58c5c8*/
  savedregs[3] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x58c5d8*/
  savedregs[2] = 0xE6C5AD7506A5016ALL; /*0x58c5e4*/
  while ( 1 ) /*0x58c7c4*/
  {
    while ( 1 ) /*0x58c79c*/
    {
      while ( 1 ) /*0x58c788*/
      {
        while ( 1 ) /*0x58c774*/
        {
          while ( 1 ) /*0x58c760*/
          {
            while ( 1 ) /*0x58c738*/
            {
              while ( 1 ) /*0x58c724*/
              {
                while ( 1 ) /*0x58c710*/
                {
                  while ( 1 ) /*0x58c6e8*/
                  {
                    while ( 1 ) /*0x58c6d4*/
                    {
                      while ( 1 ) /*0x58c6c0*/
                      {
                        while ( 1 ) /*0x58c6ac*/
                        {
                          while ( 1 ) /*0x58c684*/
                          {
                            while ( 1 ) /*0x58c670*/
                            {
                              while ( 1 ) /*0x58c65c*/
                              {
                                while ( 1 ) /*0x58c648*/
                                {
                                  while ( 1 ) /*0x58c60c*/
                                  {
                                    while ( HIDWORD(savedregs[2]) == -2107929299 ) /*0x58c60c*/
                                      HIDWORD(savedregs[2]) = 1614826856; /*0x58c898*/
                                    if ( HIDWORD(savedregs[2]) == -2081885584 ) /*0x58c620*/
                                    {
                                      _ReadStatusReg(TPIDR_EL0); /*0x58ca84*/
                                      abort(); /*0x58ca98*/
                                    }
                                    if ( HIDWORD(savedregs[2]) != -1894466829 ) /*0x58c648*/
                                      break; /*0x58c648*/
                                    if ( (v13 & 1) != 0 ) /*0x58cb44*/
                                      v11 = 889066663; /*0x58cb44*/
                                    else
                                      v11 = 1985596001; /*0x58cb44*/
                                    HIDWORD(savedregs[2]) = v11; /*0x58cb4c*/
                                  }
                                  if ( HIDWORD(savedregs[2]) != -1845673766 ) /*0x58c65c*/
                                    break; /*0x58c65c*/
                                  HIDWORD(savedregs[2]) = 1009800053; /*0x58c970*/
                                }
                                if ( HIDWORD(savedregs[2]) != -1827904051 ) /*0x58c670*/
                                  break; /*0x58c670*/
                                savedregs[1] = &a5; /*0x58c8cc*/
                                savedregs[0] = &a5; /*0x58c8d8*/
                                v15 = (unsigned __int8 *)&savedregs[2]; /*0x58c8e4*/
                                a5 = v5; /*0x58c8ec*/
                                v8 = ((__int64 (__fastcall *)(__int64))loc_596E90)(v5); /*0x58c8f8*/
                                v9 = ((__int64 (__fastcall *)(__int64))loc_597284)(a5); /*0x58c900*/
                                sub_58CD1C(v8, v9); /*0x58c910*/
                                result = ((__int64 (__fastcall *)(__int64 *))loc_4CB214)(&a5); /*0x58c918*/
                                v14 = result & 1; /*0x58c920*/
                                HIDWORD(savedregs[2]) = -908007584; /*0x58c930*/
                              }
                              if ( HIDWORD(savedregs[2]) != -1336128247 ) /*0x58c684*/
                                break; /*0x58c684*/
                              HIDWORD(savedregs[2]) = -657717802; /*0x58c9b0*/
                            }
                            if ( HIDWORD(savedregs[2]) != -908007584 ) /*0x58c6ac*/
                              break; /*0x58c6ac*/
                            if ( (v14 & 1) != 0 ) /*0x58c954*/
                              v10 = -1845673766; /*0x58c954*/
                            else
                              v10 = 910854899; /*0x58c954*/
                            HIDWORD(savedregs[2]) = v10; /*0x58c95c*/
                          }
                          if ( HIDWORD(savedregs[2]) != -657717802 ) /*0x58c6c0*/
                            break; /*0x58c6c0*/
                          HIDWORD(savedregs[2]) = 198185783; /*0x58ca20*/
                        }
                        if ( HIDWORD(savedregs[2]) != -423252619 ) /*0x58c6d4*/
                          break; /*0x58c6d4*/
                        if ( LODWORD(savedregs[2]) <= 0x76D4422A ) /*0x58c868*/
                          v7 = 1373229485; /*0x58c868*/
                        else
                          v7 = 2100152160; /*0x58c868*/
                        HIDWORD(savedregs[2]) = v7; /*0x58c870*/
                      }
                      if ( HIDWORD(savedregs[2]) != -191786739 ) /*0x58c6e8*/
                        break; /*0x58c6e8*/
                      v13 = (((((*(_DWORD *)sub_58C5B0 >> 26 == 5) << 31 >> 31) /*0x58cb10*/
                             + (((*(_DWORD *)sub_58C5B0 >> 26 == 5) ^ (*(_DWORD *)sub_58C5B0 >> 21 == 1697)) << 31 >> 31)) << 31 >> 31)
                           - (((*(_DWORD *)sub_58C5B0 >> 26 == 5)
                             & (unsigned __int8)(*(_DWORD *)sub_58C5B0 >> 21 != 1697)) << 31 >> 31))
                          & 1;
                      HIDWORD(savedregs[2]) = -1894466829; /*0x58cb20*/
                    }
                    if ( HIDWORD(savedregs[2]) != 98953998 ) /*0x58c710*/
                      break; /*0x58c710*/
                    HIDWORD(savedregs[2]) = -1827904051; /*0x58c8ac*/
                  }
                  if ( HIDWORD(savedregs[2]) != 129248049 ) /*0x58c724*/
                    break; /*0x58c724*/
                  HIDWORD(savedregs[2]) = -657717802; /*0x58ca0c*/
                }
                if ( HIDWORD(savedregs[2]) != 198185783 ) /*0x58c738*/
                  break; /*0x58c738*/
                result = ((__int64 (__fastcall *)(_QWORD))loc_4CC5D4)(savedregs[1]); /*0x58ca2c*/
                HIDWORD(savedregs[2]) = 1389366180; /*0x58ca3c*/
              }
              if ( HIDWORD(savedregs[2]) != 717011824 ) /*0x58c760*/
                break; /*0x58c760*/
              result = sub_58F768(a4, *v15, a2, a3); /*0x58c9dc*/
              *(_DWORD *)savedregs[0] = 1; /*0x58c9e8*/
              HIDWORD(savedregs[2]) = 129248049; /*0x58c9f8*/
            }
            if ( HIDWORD(savedregs[2]) != 889066663 ) /*0x58c774*/
              break; /*0x58c774*/
            HIDWORD(savedregs[2]) = -2081885584; /*0x58ca7c*/
          }
          if ( HIDWORD(savedregs[2]) != 910854899 ) /*0x58c788*/
            break; /*0x58c788*/
          HIDWORD(savedregs[2]) = 717011824; /*0x58c9c4*/
        }
        if ( HIDWORD(savedregs[2]) != 1009800053 ) /*0x58c79c*/
          break; /*0x58c79c*/
        result = ((__int64 (__fastcall *)(__int64, _QWORD))loc_58D010)(a4, savedregs[1]); /*0x58c980*/
        *(_DWORD *)savedregs[0] = 1; /*0x58c98c*/
        HIDWORD(savedregs[2]) = -1336128247; /*0x58c99c*/
      }
      if ( HIDWORD(savedregs[2]) != 1373229485 ) /*0x58c7c4*/
        break; /*0x58c7c4*/
      HIDWORD(savedregs[2]) = -2107929299; /*0x58c884*/
    }
    if ( HIDWORD(savedregs[2]) == 1389366180 ) /*0x58c7d8*/
      break; /*0x58c7d8*/
    if ( HIDWORD(savedregs[2]) == 1614826856 ) /*0x58c814*/
    {
      HIDWORD(savedregs[2]) = -191786739; /*0x58cabc*/
    }
    else
    {
      if ( HIDWORD(savedregs[2]) != 1985596001 ) /*0x58c828*/
        JUMPOUT(0x58CBC0); /*0x58cbc0*/
      if ( loc_58C5B4 >> 10 == 3508160 || loc_58C5B8 >> 10 == 3508160 ) /*0x58cba8*/
        v12 = 889066663; /*0x58cbac*/
      else
        v12 = 98953998; /*0x58cbac*/
      HIDWORD(savedregs[2]) = v12; /*0x58cbb4*/
    }
  }
  _ReadStatusReg(TPIDR_EL0); /*0x58ca44*/
  return result; /*0x58ca6c*/
}