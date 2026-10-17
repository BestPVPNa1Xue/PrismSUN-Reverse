__int64 __fastcall sub_42F1D8(__int64 result, __int64 a2, int a3)
{
  int v3; // w8
  int v4; // w8
  int v5; // w8
  int v6; // w8
  int v7; // w8
  int v8; // w8
  bool v9; // [xsp+1Bh] [xbp-15h]
  int v10; // [xsp+1Ch] [xbp-14h]
  unsigned __int8 *v11; // [xsp+20h] [xbp-10h]
  unsigned __int8 *v12; // [xsp+28h] [xbp-8h]
  _QWORD savedregs[2]; // [xsp+30h] [xbp+0h] BYREF

  savedregs[1] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x42f1ec*/
  savedregs[0] = 0x77C4EEB200000000LL; /*0x42f1f0*/
  while ( 1 ) /*0x42f3e4*/
  {
    while ( 1 ) /*0x42f3d0*/
    {
      while ( 1 ) /*0x42f3bc*/
      {
        while ( 1 ) /*0x42f3a8*/
        {
          while ( 1 ) /*0x42f36c*/
          {
            while ( 1 ) /*0x42f358*/
            {
              while ( 1 ) /*0x42f344*/
              {
                while ( 1 ) /*0x42f308*/
                {
                  while ( 1 ) /*0x42f2f4*/
                  {
                    while ( 1 ) /*0x42f2e0*/
                    {
                      while ( 1 ) /*0x42f2cc*/
                      {
                        while ( 1 ) /*0x42f2b8*/
                        {
                          while ( 1 ) /*0x42f2a4*/
                          {
                            while ( 1 ) /*0x42f290*/
                            {
                              while ( 1 ) /*0x42f27c*/
                              {
                                while ( 1 ) /*0x42f254*/
                                {
                                  while ( 1 ) /*0x42f22c*/
                                  {
                                    while ( 1 ) /*0x42f218*/
                                    {
                                      while ( HIDWORD(savedregs[0]) == -1912611793 ) /*0x42f218*/
                                      {
                                        if ( v10 == 5 ) /*0x42f568*/
                                          v5 = 737603923; /*0x42f568*/
                                        else
                                          v5 = 1771697488; /*0x42f568*/
                                        HIDWORD(savedregs[0]) = v5; /*0x42f570*/
                                      }
                                      if ( HIDWORD(savedregs[0]) != -1899792084 ) /*0x42f22c*/
                                        break; /*0x42f22c*/
                                      HIDWORD(savedregs[0]) = -604790378; /*0x42f5e4*/
                                    }
                                    if ( HIDWORD(savedregs[0]) == -1691820974 ) /*0x42f240*/
                                      JUMPOUT(0x42F87C); /*0x42f87c*/
                                    if ( HIDWORD(savedregs[0]) != -1573976204 ) /*0x42f254*/
                                      break; /*0x42f254*/
                                    v12 = (unsigned __int8 *)savedregs; /*0x42f4e0*/
                                    v11 = (unsigned __int8 *)__PAIR64__(HIDWORD(result), a3); /*0x42f4f8*/
                                    v10 = a3; /*0x42f500*/
                                    LOBYTE(savedregs[0]) = a3 & 1; /*0x42f510*/
                                    HIDWORD(savedregs[0]) = -167495574; /*0x42f520*/
                                  }
                                  if ( HIDWORD(savedregs[0]) == -1403542456 ) /*0x42f268*/
                                    JUMPOUT(0x42F84C); /*0x42f84c*/
                                  if ( HIDWORD(savedregs[0]) != -1291296841 ) /*0x42f27c*/
                                    break; /*0x42f27c*/
                                  HIDWORD(savedregs[0]) = -604790378; /*0x42f630*/
                                }
                                if ( HIDWORD(savedregs[0]) != -1158259947 ) /*0x42f290*/
                                  break; /*0x42f290*/
                                v9 = loc_42F1DC >> 10 == 3508160 || loc_42F1E0 >> 10 == 3508160; /*0x42f78c*/
                                HIDWORD(savedregs[0]) = 681381162; /*0x42f79c*/
                              }
                              if ( HIDWORD(savedregs[0]) != -998059342 ) /*0x42f2a4*/
                                break; /*0x42f2a4*/
                              *v11 = *v12; /*0x42f5c0*/
                              HIDWORD(savedregs[0]) = -1899792084; /*0x42f5d0*/
                            }
                            if ( HIDWORD(savedregs[0]) != -981614049 ) /*0x42f2b8*/
                              break; /*0x42f2b8*/
                            HIDWORD(savedregs[0]) = -1158259947; /*0x42f73c*/
                          }
                          if ( HIDWORD(savedregs[0]) != -880774196 ) /*0x42f2cc*/
                            break; /*0x42f2cc*/
                          HIDWORD(savedregs[0]) = 755518063; /*0x42f6a4*/
                        }
                        if ( HIDWORD(savedregs[0]) != -604790378 ) /*0x42f2e0*/
                          break; /*0x42f2e0*/
                        HIDWORD(savedregs[0]) = -880774196; /*0x42f690*/
                      }
                      if ( HIDWORD(savedregs[0]) != -406695632 ) /*0x42f2f4*/
                        break; /*0x42f2f4*/
                      atomic_store(*v12, v11); /*0x42f60c*/
                      HIDWORD(savedregs[0]) = -1291296841; /*0x42f61c*/
                    }
                    if ( HIDWORD(savedregs[0]) != -167495574 ) /*0x42f308*/
                      break; /*0x42f308*/
                    if ( v10 >= 5 ) /*0x42f540*/
                      v4 = -1912611793; /*0x42f540*/
                    else
                      v4 = -43195314; /*0x42f540*/
                    HIDWORD(savedregs[0]) = v4; /*0x42f548*/
                  }
                  if ( HIDWORD(savedregs[0]) == -130359500 ) /*0x42f31c*/
                    JUMPOUT(0x42F81C); /*0x42f81c*/
                  if ( HIDWORD(savedregs[0]) == -78426918 ) /*0x42f330*/
                    JUMPOUT(0x42F7F4); /*0x42f7f4*/
                  if ( HIDWORD(savedregs[0]) != -43195314 ) /*0x42f344*/
                    break; /*0x42f344*/
                  if ( v10 == 3 ) /*0x42f590*/
                    v6 = 1127330534; /*0x42f590*/
                  else
                    v6 = 1771697488; /*0x42f590*/
                  HIDWORD(savedregs[0]) = v6; /*0x42f598*/
                }
                if ( HIDWORD(savedregs[0]) != 25746884 ) /*0x42f358*/
                  break; /*0x42f358*/
                HIDWORD(savedregs[0]) = 245617674; /*0x42f4b8*/
              }
              if ( HIDWORD(savedregs[0]) != 245617674 ) /*0x42f36c*/
                break; /*0x42f36c*/
              if ( *(_DWORD *)sub_42F1D8 >> 26 == 5 || *(_DWORD *)sub_42F1D8 >> 21 == 1697 ) /*0x42f71c*/
                v7 = 1299130900; /*0x42f720*/
              else
                v7 = -981614049; /*0x42f720*/
              HIDWORD(savedregs[0]) = v7; /*0x42f728*/
            }
            if ( HIDWORD(savedregs[0]) == 433044986 ) /*0x42f380*/
              JUMPOUT(0x42F7D0); /*0x42f7d0*/
            if ( HIDWORD(savedregs[0]) == 495801104 ) /*0x42f394*/
              JUMPOUT(0x42F898); /*0x42f898*/
            if ( HIDWORD(savedregs[0]) != 567400540 ) /*0x42f3a8*/
              break; /*0x42f3a8*/
            HIDWORD(savedregs[0]) = -604790378; /*0x42f67c*/
          }
          if ( HIDWORD(savedregs[0]) != 634847530 ) /*0x42f3bc*/
            break; /*0x42f3bc*/
          atomic_store(*v12, v11); /*0x42f658*/
          HIDWORD(savedregs[0]) = 567400540; /*0x42f668*/
        }
        if ( HIDWORD(savedregs[0]) != 681381162 ) /*0x42f3d0*/
          break; /*0x42f3d0*/
        if ( v9 ) /*0x42f7a8*/
          v8 = 1299130900; /*0x42f7c0*/
        else
          v8 = -1573976204; /*0x42f7c0*/
        HIDWORD(savedregs[0]) = v8; /*0x42f7c8*/
      }
      if ( HIDWORD(savedregs[0]) != 737603923 ) /*0x42f3e4*/
        break; /*0x42f3e4*/
      HIDWORD(savedregs[0]) = 634847530; /*0x42f644*/
    }
    if ( HIDWORD(savedregs[0]) == 755518063 ) /*0x42f3f8*/
      break; /*0x42f3f8*/
    switch ( HIDWORD(savedregs[0]) ) /*0x42f40c*/
    {
      case 0x4331B2E6: /*0x42f40c*/
        HIDWORD(savedregs[0]) = -406695632; /*0x42f5f8*/
        break;
      case 0x4D6F2A14: /*0x42f40c*/
        _ReadStatusReg(TPIDR_EL0); /*0x42f6cc*/
        sub_449B5C(); /*0x42f6e0*/
      case 0x67C96D01: /*0x42f40c*/
        HIDWORD(savedregs[0]) = 25746884; /*0x42f4a4*/
        break;
      case 0x6999F550: /*0x42f40c*/
        HIDWORD(savedregs[0]) = -998059342; /*0x42f5ac*/
        break;
      case 0x77C4EEB2: /*0x42f40c*/
        if ( LODWORD(savedregs[0]) > 0xFDC4B052 ) /*0x42f488*/
          v3 = 433044986; /*0x42f488*/
        else
          v3 = 1741253889; /*0x42f488*/
        HIDWORD(savedregs[0]) = v3; /*0x42f490*/
        break;
    }
  }
  _ReadStatusReg(TPIDR_EL0); /*0x42f6ac*/
  return result; /*0x42f6c8*/
}