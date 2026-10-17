__int64 __usercall sub_6D49A8@<X0>(_DWORD *a1@<X8>)
{
  __int64 result; // x0
  int v3; // w8
  int v4; // w8
  int v5; // w8
  _QWORD savedregs[4]; // [xsp+20h] [xbp+0h] BYREF

  savedregs[3] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x6d49c4*/
  savedregs[2] = 0x34387BC8E84FF0B4LL; /*0x6d49d0*/
  savedregs[0] = (char *)&savedregs[2] + 4; /*0x6d49e4*/
  while ( 1 ) /*0x6d4b9c*/
  {
    while ( 1 ) /*0x6d4b74*/
    {
      while ( 1 ) /*0x6d4b60*/
      {
        while ( 1 ) /*0x6d4b4c*/
        {
          while ( 1 ) /*0x6d4b38*/
          {
            while ( 1 ) /*0x6d4b24*/
            {
              while ( 1 ) /*0x6d4b10*/
              {
                while ( 1 ) /*0x6d4ad4*/
                {
                  while ( 1 ) /*0x6d4ac0*/
                  {
                    while ( 1 ) /*0x6d4a98*/
                    {
                      while ( 1 ) /*0x6d4a70*/
                      {
                        while ( 1 ) /*0x6d4a5c*/
                        {
                          while ( 1 ) /*0x6d4a34*/
                          {
                            while ( 1 ) /*0x6d4a20*/
                            {
                              while ( 1 ) /*0x6d4a0c*/
                              {
                                while ( 1 ) /*0x6d49f8*/
                                {
                                  while ( HIDWORD(savedregs[2]) == -2037584930 ) /*0x6d49f8*/
                                    HIDWORD(savedregs[2]) = 2066064017; /*0x6d4d38*/
                                  if ( HIDWORD(savedregs[2]) != -1875965114 ) /*0x6d4a0c*/
                                    break; /*0x6d4a0c*/
                                  if ( (savedregs[1] & 0x10000000000LL) != 0 ) /*0x6d4e90*/
                                    v5 = 142780370; /*0x6d4e90*/
                                  else
                                    v5 = -391895735; /*0x6d4e90*/
                                  HIDWORD(savedregs[2]) = v5; /*0x6d4e98*/
                                }
                                if ( HIDWORD(savedregs[2]) != -1845716283 ) /*0x6d4a20*/
                                  break; /*0x6d4a20*/
                                HIDWORD(savedregs[2]) = 1415506539; /*0x6d4c20*/
                              }
                              if ( HIDWORD(savedregs[2]) != -1640525926 ) /*0x6d4a34*/
                                break; /*0x6d4a34*/
                              BYTE5(savedregs[1]) = loc_6D49AC >> 10 == 3508160 || loc_6D49B0 >> 10 == 3508160; /*0x6d4e5c*/
                              HIDWORD(savedregs[2]) = -1875965114; /*0x6d4e6c*/
                            }
                            if ( HIDWORD(savedregs[2]) != -1216617300 ) /*0x6d4a5c*/
                              break; /*0x6d4a5c*/
                            HIDWORD(savedregs[2]) = 803678935; /*0x6d4d10*/
                          }
                          if ( HIDWORD(savedregs[2]) != -954251431 ) /*0x6d4a70*/
                            break; /*0x6d4a70*/
                          if ( (savedregs[1] & 0x100000000000000LL) != 0 ) /*0x6d4cc4*/
                            v3 = 803678935; /*0x6d4cc4*/
                          else
                            v3 = 1890205824; /*0x6d4cc4*/
                          HIDWORD(savedregs[2]) = v3; /*0x6d4ccc*/
                        }
                        if ( HIDWORD(savedregs[2]) != -391895735 ) /*0x6d4a98*/
                          break; /*0x6d4a98*/
                        HIDWORD(savedregs[2]) = 793825815; /*0x6d4c48*/
                      }
                      if ( HIDWORD(savedregs[2]) != 32172518 ) /*0x6d4ac0*/
                        break; /*0x6d4ac0*/
                      result = sub_2D9160((__int64)a1); /*0x6d4cec*/
                      HIDWORD(savedregs[2]) = -1216617300; /*0x6d4cfc*/
                    }
                    if ( HIDWORD(savedregs[2]) != 41997047 ) /*0x6d4ad4*/
                      break; /*0x6d4ad4*/
                    if ( (savedregs[1] & 0x1000000000000LL) != 0 ) /*0x6d4df0*/
                      v4 = 142780370; /*0x6d4df0*/
                    else
                      v4 = 462732316; /*0x6d4df0*/
                    HIDWORD(savedregs[2]) = v4; /*0x6d4df8*/
                  }
                  if ( HIDWORD(savedregs[2]) == 142780370 ) /*0x6d4ae8*/
                  {
                    _ReadStatusReg(TPIDR_EL0); /*0x6d4d64*/
                    abort(); /*0x6d4d78*/
                  }
                  if ( HIDWORD(savedregs[2]) != 462732316 ) /*0x6d4b10*/
                    break; /*0x6d4b10*/
                  HIDWORD(savedregs[2]) = -1640525926; /*0x6d4e0c*/
                }
                if ( HIDWORD(savedregs[2]) != 524769196 ) /*0x6d4b24*/
                  break; /*0x6d4b24*/
                BYTE6(savedregs[1]) = *(_DWORD *)sub_6D49A8 >> 26 == 5 || *(_DWORD *)sub_6D49A8 >> 21 == 1697; /*0x6d4dbc*/
                HIDWORD(savedregs[2]) = 41997047; /*0x6d4dcc*/
              }
              if ( HIDWORD(savedregs[2]) != 793825815 ) /*0x6d4b38*/
                break; /*0x6d4b38*/
              result = sub_6DD92C((__int64)a1); /*0x6d4c6c*/
              *a1 = 1; /*0x6d4c74*/
              LOBYTE(savedregs[2]) = 1; /*0x6d4c80*/
              HIBYTE(savedregs[1]) = 1; /*0x6d4c90*/
              HIDWORD(savedregs[2]) = -954251431; /*0x6d4ca0*/
            }
            if ( HIDWORD(savedregs[2]) != 803678935 ) /*0x6d4b4c*/
              break; /*0x6d4b4c*/
            HIDWORD(savedregs[2]) = -2037584930; /*0x6d4d24*/
          }
          if ( HIDWORD(savedregs[2]) != 876116936 ) /*0x6d4b60*/
            break; /*0x6d4b60*/
          HIDWORD(savedregs[2]) = -1845716283; /*0x6d4c0c*/
        }
        if ( HIDWORD(savedregs[2]) != 1415506539 ) /*0x6d4b74*/
          break; /*0x6d4b74*/
        HIDWORD(savedregs[2]) = 1965939032; /*0x6d4c34*/
      }
      if ( HIDWORD(savedregs[2]) != 1890205824 ) /*0x6d4b9c*/
        break; /*0x6d4b9c*/
      HIDWORD(savedregs[2]) = 32172518; /*0x6d4ce0*/
    }
    if ( HIDWORD(savedregs[2]) != 1965939032 ) /*0x6d4bb0*/
      break; /*0x6d4bb0*/
    HIDWORD(savedregs[2]) = 524769196; /*0x6d4d88*/
  }
  _ReadStatusReg(TPIDR_EL0); /*0x6d4d40*/
  return result; /*0x6d4d60*/
}