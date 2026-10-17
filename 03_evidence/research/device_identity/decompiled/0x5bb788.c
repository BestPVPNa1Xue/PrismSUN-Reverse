void __usercall sub_5BB788(__int64 a1@<X8>)
{
  int v2; // w8
  __int64 v3; // x0
  int v4; // w8
  int v5; // w8
  _QWORD savedregs[4]; // [xsp+20h] [xbp+0h] BYREF

  savedregs[3] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x5bb7a4*/
  savedregs[2] = 0xCD96594B00000000LL; /*0x5bb7a8*/
  savedregs[0] = (char *)&savedregs[2] + 4; /*0x5bb7bc*/
  while ( 1 ) /*0x5bb884*/
  {
    while ( 1 ) /*0x5bb85c*/
    {
      while ( 1 ) /*0x5bb848*/
      {
        while ( 1 ) /*0x5bb834*/
        {
          while ( 1 ) /*0x5bb820*/
          {
            while ( 1 ) /*0x5bb7f8*/
            {
              while ( 1 ) /*0x5bb7e4*/
              {
                while ( 1 ) /*0x5bb7d0*/
                {
                  while ( HIDWORD(savedregs[2]) == -2082070721 ) /*0x5bb7d0*/
                    HIDWORD(savedregs[2]) = -2072876934; /*0x5bb91c*/
                  if ( HIDWORD(savedregs[2]) != -2072876934 ) /*0x5bb7e4*/
                    break; /*0x5bb7e4*/
                  HIDWORD(savedregs[2]) = 1370684587; /*0x5bb930*/
                }
                if ( HIDWORD(savedregs[2]) != -1715780855 ) /*0x5bb7f8*/
                  break; /*0x5bb7f8*/
                if ( (savedregs[1] & 0x100000000000000LL) != 0 ) /*0x5bba44*/
                  v4 = 1225525419; /*0x5bba44*/
                else
                  v4 = -683586505; /*0x5bba44*/
                HIDWORD(savedregs[2]) = v4; /*0x5bba4c*/
              }
              if ( HIDWORD(savedregs[2]) != -1328161966 ) /*0x5bb820*/
                break; /*0x5bb820*/
              HIBYTE(savedregs[1]) = *(_DWORD *)sub_5BB788 >> 26 == 5 || *(_DWORD *)sub_5BB788 >> 21 == 1697; /*0x5bba10*/
              HIDWORD(savedregs[2]) = -1715780855; /*0x5bba20*/
            }
            if ( HIDWORD(savedregs[2]) != -1258831733 ) /*0x5bb834*/
              break; /*0x5bb834*/
            v3 = ((__int64 (*)(void))loc_5BBB54)(); /*0x5bb968*/
            savedregs[2] = ((__int64 (__fastcall *)(__int64))loc_5BC98C)(v3); /*0x5bb970*/
            sub_C7BE8(a1, savedregs[2]); /*0x5bb97c*/
            HIDWORD(savedregs[2]) = 223721733; /*0x5bb98c*/
          }
          if ( HIDWORD(savedregs[2]) != -845784757 ) /*0x5bb848*/
            break; /*0x5bb848*/
          if ( LODWORD(savedregs[2]) == -915159588 ) /*0x5bb900*/
            v2 = -528624337; /*0x5bb900*/
          else
            v2 = -2082070721; /*0x5bb900*/
          HIDWORD(savedregs[2]) = v2; /*0x5bb908*/
        }
        if ( HIDWORD(savedregs[2]) != -683586505 ) /*0x5bb85c*/
          break; /*0x5bb85c*/
        if ( loc_5BB78C >> 10 == 3508160 || loc_5BB790 >> 10 == 3508160 ) /*0x5bbaa8*/
          v5 = 1225525419; /*0x5bbaac*/
        else
          v5 = -489876148; /*0x5bbaac*/
        HIDWORD(savedregs[2]) = v5; /*0x5bbab4*/
      }
      if ( HIDWORD(savedregs[2]) == -528624337 ) /*0x5bb870*/
      {
        MEMORY[0x235D90C](); /*0x5bbabc*/
        JUMPOUT(0x5BBAC0); /*0x5bbac0*/
      }
      if ( HIDWORD(savedregs[2]) != -489876148 ) /*0x5bb884*/
        break; /*0x5bb884*/
      HIDWORD(savedregs[2]) = -1258831733; /*0x5bb944*/
    }
    if ( HIDWORD(savedregs[2]) == 223721733 ) /*0x5bb898*/
      break; /*0x5bb898*/
    if ( HIDWORD(savedregs[2]) == 1225525419 ) /*0x5bb8c0*/
    {
      _ReadStatusReg(TPIDR_EL0); /*0x5bb9b8*/
      abort(); /*0x5bb9cc*/
    }
    HIDWORD(savedregs[2]) = -1328161966; /*0x5bb9dc*/
  }
  _ReadStatusReg(TPIDR_EL0); /*0x5bb994*/
}