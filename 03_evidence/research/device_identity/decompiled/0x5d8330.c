__int64 __usercall sub_5D8330@<X0>(bool a1@<W2>, _QWORD *a2@<X3>, _QWORD *a3@<X8>, _QWORD *a4)
{
  bool v4; // w12
  bool v5; // w13
  _DWORD *v6; // x15
  _QWORD *v7; // x17
  char v8; // w19
  _BYTE *v9; // x20
  char v10; // w13
  _BYTE *v11; // x19
  char v12; // w12
  _BYTE *v13; // x19
  int v14; // w19
  _QWORD *v15; // x9
  _QWORD *v16; // x16
  _QWORD *v17; // x6
  _QWORD *v18; // x7
  char v19; // w19
  _BYTE *v20; // x20
  __int64 v21; // x0
  __int64 result; // x0
  bool v23; // w8
  _QWORD savedregs[6]; // [xsp+50h] [xbp+0h] BYREF

  savedregs[5] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x5d834c*/
  if ( *(_DWORD *)sub_5D8330 >> 26 == 5 /*0x5d8e38*/
    || *(_DWORD *)sub_5D8330 >> 21 == 1697
    || ((((((((loc_5D8334 >> 10 == 3508160) << 31 >> 31) + ((loc_5D8338 >> 10 == 3508160) << 31 >> 31)) << 31 >> 31) - 1) << 31 >> 31)
       + ((loc_5D8338 >> 10 != 3508160 || loc_5D8334 >> 10 != 3508160) << 31 >> 31))
      & 1) != 0 )
  {
    _ReadStatusReg(TPIDR_EL0); /*0x5d8d80*/
    abort(); /*0x5d8d94*/
  }
  v15 = savedregs; /*0x5d8364*/
  v16 = &savedregs[4]; /*0x5d8384*/
  v17 = &savedregs[4]; /*0x5d839c*/
  v18 = &savedregs[4]; /*0x5d83a4*/
  a4 = a3; /*0x5d83ac*/
  v14 = -1347166115; /*0x5d83b4*/
  while ( 1 ) /*0x5d86e4*/
  {
    while ( 1 ) /*0x5d8698*/
    {
      while ( 1 ) /*0x5d8684*/
      {
        while ( 1 ) /*0x5d8670*/
        {
          while ( 1 ) /*0x5d865c*/
          {
            while ( 1 ) /*0x5d8648*/
            {
              while ( 1 ) /*0x5d8634*/
              {
                while ( 1 ) /*0x5d8620*/
                {
                  while ( 1 ) /*0x5d85f8*/
                  {
                    while ( 1 ) /*0x5d85e4*/
                    {
                      while ( 1 ) /*0x5d85d0*/
                      {
                        while ( 1 ) /*0x5d8580*/
                        {
                          while ( 1 ) /*0x5d856c*/
                          {
                            while ( 1 ) /*0x5d8558*/
                            {
                              while ( 1 ) /*0x5d8530*/
                              {
                                while ( 1 ) /*0x5d851c*/
                                {
                                  while ( 1 ) /*0x5d84f4*/
                                  {
                                    while ( 1 ) /*0x5d84cc*/
                                    {
                                      while ( 1 ) /*0x5d84a4*/
                                      {
                                        while ( 1 ) /*0x5d8490*/
                                        {
                                          while ( 1 ) /*0x5d8468*/
                                          {
                                            while ( 1 ) /*0x5d8454*/
                                            {
                                              while ( 1 ) /*0x5d8440*/
                                              {
                                                while ( 1 ) /*0x5d842c*/
                                                {
                                                  while ( 1 ) /*0x5d8418*/
                                                  {
                                                    while ( 1 ) /*0x5d8404*/
                                                    {
                                                      while ( 1 ) /*0x5d83f0*/
                                                      {
                                                        while ( 1 ) /*0x5d83dc*/
                                                        {
                                                          while ( 1 ) /*0x5d83c8*/
                                                          {
                                                            while ( v14 == -1901127648 ) /*0x5d83c8*/
                                                              v14 = 1428609360; /*0x5d883c*/
                                                            if ( v14 != -1890712082 ) /*0x5d83dc*/
                                                              break; /*0x5d83dc*/
                                                            if ( *v7 >= *a2 ) /*0x5d87cc*/
                                                              v14 = -500805607; /*0x5d87cc*/
                                                            else
                                                              v14 = 1069373250; /*0x5d87cc*/
                                                          }
                                                          if ( v14 != -1765945612 ) /*0x5d83f0*/
                                                            break; /*0x5d83f0*/
                                                          v14 = 899254513; /*0x5d88b8*/
                                                        }
                                                        if ( v14 != -1637896283 ) /*0x5d8404*/
                                                          break; /*0x5d8404*/
                                                        v14 = 1806126664; /*0x5d88ac*/
                                                      }
                                                      if ( v14 != -1626733760 ) /*0x5d8418*/
                                                        break; /*0x5d8418*/
                                                      v14 = -765633737; /*0x5d8818*/
                                                    }
                                                    if ( v14 != -1443510470 ) /*0x5d842c*/
                                                      break; /*0x5d842c*/
                                                    v14 = 461349005; /*0x5d8894*/
                                                  }
                                                  if ( v14 != -1347166115 ) /*0x5d8440*/
                                                    break; /*0x5d8440*/
                                                  v14 = -412046884; /*0x5d874c*/
                                                }
                                                if ( v14 != -1192678630 ) /*0x5d8454*/
                                                  break; /*0x5d8454*/
                                                v14 = -1168785959; /*0x5d8940*/
                                              }
                                              if ( v14 != -1168785959 ) /*0x5d8468*/
                                                break; /*0x5d8468*/
                                              v14 = 1806126664; /*0x5d894c*/
                                            }
                                            if ( v14 != -955853752 ) /*0x5d8490*/
                                              break; /*0x5d8490*/
                                            if ( a1 ) /*0x5d8a80*/
                                              v14 = -736658688; /*0x5d8a84*/
                                            else
                                              v14 = 67611723; /*0x5d8a84*/
                                          }
                                          if ( v14 != -845504193 ) /*0x5d84a4*/
                                            break; /*0x5d84a4*/
                                          v19 = *v6; /*0x5d8964*/
                                          v20 = (_BYTE *)(*v7)++; /*0x5d8968*/
                                          *v20 = v19; /*0x5d8974*/
                                          v14 = 680362766; /*0x5d8978*/
                                        }
                                        if ( v14 != -765633737 ) /*0x5d84cc*/
                                          break; /*0x5d84cc*/
                                        v14 = -223699997; /*0x5d8824*/
                                      }
                                      if ( v14 != -736658688 ) /*0x5d84f4*/
                                        break; /*0x5d84f4*/
                                      v14 = 436921256; /*0x5d8990*/
                                    }
                                    if ( v14 != -500805607 ) /*0x5d851c*/
                                      break; /*0x5d851c*/
                                    v14 = 1806126664; /*0x5d87d4*/
                                  }
                                  if ( v14 != -412046884 ) /*0x5d8530*/
                                    break; /*0x5d8530*/
                                  v14 = 444687841; /*0x5d8758*/
                                }
                                if ( v14 != -223699997 ) /*0x5d8558*/
                                  break; /*0x5d8558*/
                                v14 = 1806126664; /*0x5d8830*/
                              }
                              if ( v14 != 67611723 ) /*0x5d856c*/
                                break; /*0x5d856c*/
                              v6 = &a4; /*0x5d8778*/
                              v7 = &savedregs[4]; /*0x5d8780*/
                              a2 = &savedregs[4]; /*0x5d8788*/
                              a4 = v15; /*0x5d8798*/
                              savedregs[4] = v15 + 6; /*0x5d87a0*/
                              v14 = -1890712082; /*0x5d87a4*/
                            }
                            if ( v14 != 225648192 ) /*0x5d8580*/
                              break; /*0x5d8580*/
                            if ( v5 ) /*0x5d8888*/
                              v14 = -1443510470; /*0x5d888c*/
                            else
                              v14 = -1765945612; /*0x5d888c*/
                          }
                          if ( v14 == 436921256 ) /*0x5d85bc*/
                            abort(); /*0x5d899c*/
                          if ( v14 != 444687841 ) /*0x5d85d0*/
                            break; /*0x5d85d0*/
                          v14 = 1555867990; /*0x5d8764*/
                        }
                        if ( v14 != 461349005 ) /*0x5d85e4*/
                          break; /*0x5d85e4*/
                        v14 = -1637896283; /*0x5d88a0*/
                      }
                      if ( v14 != 484625814 ) /*0x5d85f8*/
                        break; /*0x5d85f8*/
                      v14 = -845504193; /*0x5d8958*/
                    }
                    if ( v14 != 680362766 ) /*0x5d8620*/
                      break; /*0x5d8620*/
                    v14 = -1890712082; /*0x5d8984*/
                  }
                  if ( v14 != 805996437 ) /*0x5d8634*/
                    break; /*0x5d8634*/
                  a1 = (loc_5D6D94 & 0xFFFFFC00) == -702611456 || (loc_5D6D98 & 0xFFFFFC00) == -702611456; /*0x5d8a60*/
                  v14 = -955853752; /*0x5d8a64*/
                }
                if ( v14 != 899254513 ) /*0x5d8648*/
                  break; /*0x5d8648*/
                v12 = *v6; /*0x5d88c4*/
                v13 = (_BYTE *)(*v7)++; /*0x5d88c8*/
                *v13 = v12; /*0x5d88d4*/
                v4 = *v7 >= *a2; /*0x5d88e4*/
                v14 = 1562688842; /*0x5d88e8*/
              }
              if ( v14 != 1069373250 ) /*0x5d865c*/
                break; /*0x5d865c*/
              v8 = *v6; /*0x5d87e0*/
              v9 = (_BYTE *)(*v7)++; /*0x5d87e4*/
              *v9 = v8; /*0x5d87f0*/
              if ( *v7 >= *a2 ) /*0x5d8810*/
                v14 = -1626733760; /*0x5d8810*/
              else
                v14 = -1901127648; /*0x5d8810*/
            }
            if ( v14 != 1428609360 ) /*0x5d8670*/
              break; /*0x5d8670*/
            v10 = *v6; /*0x5d8848*/
            v11 = (_BYTE *)(*v7)++; /*0x5d884c*/
            *v11 = v10; /*0x5d8858*/
            v5 = *v7 >= *a2; /*0x5d8868*/
            v14 = 225648192; /*0x5d886c*/
          }
          if ( v14 != 1555867990 ) /*0x5d8684*/
            break; /*0x5d8684*/
          if ( (loc_5D6D90 & 0xFC000000) == 335544320 || (loc_5D6D90 & 0xFFE00000) == -736100352 ) /*0x5d89ec*/
            v14 = -736658688; /*0x5d89f0*/
          else
            v14 = 1671227737; /*0x5d89f0*/
        }
        if ( v14 != 1562688842 ) /*0x5d8698*/
          break; /*0x5d8698*/
        if ( v4 ) /*0x5d8904*/
          v14 = 1818581172; /*0x5d8908*/
        else
          v14 = 484625814; /*0x5d8908*/
      }
      savedregs[0] = v18; /*0x5d86c0*/
      savedregs[1] = v17; /*0x5d86c8*/
      savedregs[2] = v16; /*0x5d86cc*/
      savedregs[3] = v15; /*0x5d86d0*/
      savedregs[4] = a3; /*0x5d86d4*/
      if ( v14 != 1671227737 ) /*0x5d86e4*/
        break; /*0x5d86e4*/
      v14 = 805996437; /*0x5d89f8*/
      a3 = (_QWORD *)savedregs[4]; /*0x5d8a00*/
      v15 = (_QWORD *)savedregs[3]; /*0x5d8a04*/
      v16 = (_QWORD *)savedregs[2]; /*0x5d8a08*/
      v17 = (_QWORD *)savedregs[1]; /*0x5d8a0c*/
      v18 = (_QWORD *)savedregs[0]; /*0x5d8a14*/
    }
    if ( v14 == 1806126664 ) /*0x5d86f8*/
      break; /*0x5d86f8*/
    v14 = -1192678630; /*0x5d8910*/
    a3 = (_QWORD *)savedregs[4]; /*0x5d8918*/
    v15 = (_QWORD *)savedregs[3]; /*0x5d891c*/
    v16 = (_QWORD *)savedregs[2]; /*0x5d8920*/
    v17 = (_QWORD *)savedregs[1]; /*0x5d8924*/
    v18 = (_QWORD *)savedregs[0]; /*0x5d892c*/
  }
  v21 = sub_5FE42C(); /*0x5d8b88*/
  savedregs[4] = sub_5FE430(v21); /*0x5d8b94*/
  LODWORD(savedregs[4]) = ((__int64 (__fastcall *)(_QWORD, _QWORD, _QWORD))loc_5CEE84)(savedregs[4], 0, 0); /*0x5d8bac*/
  if ( SLODWORD(savedregs[4]) >= 0 ) /*0x5d8bbc*/
  {
    savedregs[4] = sub_5D8194(LODWORD(savedregs[4]), savedregs[3], 47); /*0x5d8bf4*/
    sub_5D5A04(LODWORD(savedregs[4])); /*0x5d8bfc*/
    if ( savedregs[4] > 0LL && *(_BYTE *)savedregs[3] ) /*0x5d8c18*/
    {
      LOBYTE(savedregs[4]) = 0; /*0x5d8c44*/
      sub_C7BE8(savedregs[4], savedregs[3]); /*0x5d8c50*/
      while ( 1 ) /*0x5d8c60*/
      {
        result = sub_CB11C(savedregs[4]); /*0x5d8c60*/
        v23 = 0; /*0x5d8c64*/
        if ( (result & 1) == 0 ) /*0x5d8c68*/
        {
          result = ((__int64 (__fastcall *)(_QWORD))loc_5DA7D8)(savedregs[4]); /*0x5d8c74*/
          v23 = 1; /*0x5d8c7c*/
          if ( *(_BYTE *)result != 10 ) /*0x5d8c84*/
          {
            result = ((__int64 (__fastcall *)(_QWORD))loc_5DA7D8)(savedregs[4]); /*0x5d8c90*/
            v23 = *(_BYTE *)result == 13; /*0x5d8c9c*/
          }
        }
        if ( !v23 ) /*0x5d8cb0*/
          break; /*0x5d8cb0*/
        ((void (__fastcall *)(_QWORD))loc_5DAC6C)(savedregs[4]); /*0x5d8cbc*/
      }
      LOBYTE(savedregs[4]) = 1; /*0x5d8cfc*/
      *(_DWORD *)savedregs[2] = 1; /*0x5d8d08*/
      if ( (savedregs[4] & 1) == 0 ) /*0x5d8d14*/
        result = sub_74539C(savedregs[4]); /*0x5d8d24*/
    }
    else
    {
      result = sub_5FE434(savedregs[4]); /*0x5d8c28*/
      *(_DWORD *)savedregs[2] = 1; /*0x5d8c34*/
    }
  }
  else
  {
    result = sub_F7768(savedregs[4]); /*0x5d8bc8*/
    *(_DWORD *)savedregs[2] = 1; /*0x5d8bd4*/
  }
  _ReadStatusReg(TPIDR_EL0); /*0x5d8d30*/
  return result; /*0x5d8d54*/
}