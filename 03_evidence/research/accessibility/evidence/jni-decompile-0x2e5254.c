__int64 __fastcall sub_2E5254(__int64 a1, __int64 a2, __int64 a3)
{
  int v3; // w8
  __int64 v4; // x19
  __int64 v5; // x20
  __int64 v6; // x21
  __int64 v7; // x0
  __int64 v8; // x8
  __int64 result; // x0
  int v10; // w8
  int v11; // w8
  bool v12; // [xsp+46h] [xbp+16h]
  bool v13; // [xsp+47h] [xbp+17h]
  __int64 v14; // [xsp+48h] [xbp+18h]
  __int64 savedregs; // [xsp+50h] [xbp+20h]
  __int64 savedregs_8; // [xsp+58h] [xbp+28h]

  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x2e5270*/
  savedregs = 0xAC47351A15298258LL; /*0x2e527c*/
  while ( 1 ) /*0x2e53d0*/
  {
    while ( 1 ) /*0x2e53bc*/
    {
      while ( 1 ) /*0x2e53a8*/
      {
        while ( 1 ) /*0x2e5394*/
        {
          while ( 1 ) /*0x2e536c*/
          {
            while ( 1 ) /*0x2e5344*/
            {
              while ( 1 ) /*0x2e5330*/
              {
                while ( 1 ) /*0x2e5308*/
                {
                  while ( 1 ) /*0x2e52e0*/
                  {
                    while ( 1 ) /*0x2e52c0*/
                    {
                      if ( HIDWORD(savedregs) == -1889117694 ) /*0x2e52cc*/
                      {
                        _ReadStatusReg(TPIDR_EL0); /*0x2e5554*/
                        abort(); /*0x2e5568*/
                      }
                      if ( HIDWORD(savedregs) != -1738792065 ) /*0x2e52e0*/
                        break; /*0x2e52e0*/
                      HIDWORD(savedregs) = 929325255; /*0x2e558c*/
                    }
                    if ( HIDWORD(savedregs) != -1404619494 ) /*0x2e5308*/
                      break; /*0x2e5308*/
                    if ( (unsigned int)savedregs < 0xA8FB6C28 ) /*0x2e544c*/
                      v3 = 1751300371; /*0x2e544c*/
                    else
                      v3 = -759640945; /*0x2e544c*/
                    HIDWORD(savedregs) = v3; /*0x2e5454*/
                  }
                  if ( HIDWORD(savedregs) != -1144742029 ) /*0x2e5330*/
                    break; /*0x2e5330*/
                  HIDWORD(savedregs) = -1889117694; /*0x2e554c*/
                }
                if ( HIDWORD(savedregs) != -806423315 ) /*0x2e5344*/
                  break; /*0x2e5344*/
                v12 = loc_2E5258 >> 10 == 3508160 || loc_2E525C >> 10 == 3508160; /*0x2e5660*/
                HIDWORD(savedregs) = 1436645232; /*0x2e5670*/
              }
              if ( HIDWORD(savedregs) == -759640945 ) /*0x2e5358*/
                JUMPOUT(0x2E56A4); /*0x2e56a4*/
              if ( HIDWORD(savedregs) != -534350449 ) /*0x2e536c*/
                break; /*0x2e536c*/
              HIDWORD(savedregs) = -806423315; /*0x2e5610*/
            }
            if ( HIDWORD(savedregs) != -62566458 ) /*0x2e5394*/
              break; /*0x2e5394*/
            savedregs = (unsigned int)a3 | 0x4682DCD600000000LL; /*0x2e54b8*/
            v4 = a1; /*0x2e54d0*/
            v5 = a2; /*0x2e54d8*/
            v6 = a3; /*0x2e54e0*/
            v7 = (*(__int64 (__fastcall **)(__int64, __int64, __int64))(*(_QWORD *)a2 + 1352LL))(a2, a2, a3); /*0x2e54e8*/
            a2 = v5; /*0x2e54ec*/
            a3 = v6; /*0x2e54f0*/
            v8 = v7; /*0x2e54f4*/
            a1 = v4; /*0x2e54f8*/
            v14 = v8; /*0x2e54fc*/
          }
          if ( HIDWORD(savedregs) != 97236944 ) /*0x2e53a8*/
            break; /*0x2e53a8*/
          HIDWORD(savedregs) = -62566458; /*0x2e5490*/
        }
        if ( HIDWORD(savedregs) != 929325255 ) /*0x2e53bc*/
          break; /*0x2e53bc*/
        v13 = *(_DWORD *)sub_2E5254 >> 26 == 5 || *(_DWORD *)sub_2E5254 >> 21 == 1697; /*0x2e55c0*/
        HIDWORD(savedregs) = 1534585913; /*0x2e55d0*/
      }
      if ( HIDWORD(savedregs) != 1036734911 ) /*0x2e53d0*/
        break; /*0x2e53d0*/
      HIDWORD(savedregs) = -1738792065; /*0x2e547c*/
    }
    if ( HIDWORD(savedregs) == 1182981334 ) /*0x2e53e4*/
      break; /*0x2e53e4*/
    if ( HIDWORD(savedregs) == 1436645232 ) /*0x2e53f8*/
    {
      if ( v12 ) /*0x2e567c*/
        v11 = -1144742029; /*0x2e5694*/
      else
        v11 = 97236944; /*0x2e5694*/
      HIDWORD(savedregs) = v11; /*0x2e569c*/
    }
    else if ( HIDWORD(savedregs) == 1534585913 ) /*0x2e540c*/
    {
      if ( v13 ) /*0x2e55dc*/
        v10 = -1144742029; /*0x2e55f4*/
      else
        v10 = -534350449; /*0x2e55f4*/
      HIDWORD(savedregs) = v10; /*0x2e55fc*/
    }
    else
    {
      HIDWORD(savedregs) = 1036734911; /*0x2e5468*/
    }
  }
  result = v14; /*0x2e5514*/
  _ReadStatusReg(TPIDR_EL0); /*0x2e5518*/
  return result; /*0x2e553c*/
}