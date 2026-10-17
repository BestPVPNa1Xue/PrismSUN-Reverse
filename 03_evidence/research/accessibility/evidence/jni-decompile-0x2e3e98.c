__int64 __fastcall sub_2E3E98(__int64 a1, __int64 a2, __int64 a3, __int64 a4)
{
  int v4; // w8
  __int64 v5; // x19
  __int64 v6; // x20
  __int64 v7; // x21
  __int64 v8; // x22
  __int64 v9; // x0
  __int64 v10; // x8
  __int64 result; // x0
  int v12; // w8
  int v13; // w8
  _QWORD savedregs[6]; // [xsp+30h] [xbp+0h] BYREF

  savedregs[5] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x2e3eb4*/
  savedregs[4] = 0x6EA2EDA97FFEF9FFLL; /*0x2e3ec0*/
  savedregs[1] = (char *)&savedregs[4] + 4; /*0x2e3ed4*/
  while ( 1 ) /*0x2e3f88*/
  {
    while ( 1 ) /*0x2e3f38*/
    {
      while ( 1 ) /*0x2e3f10*/
      {
        while ( 1 ) /*0x2e3efc*/
        {
          while ( 1 ) /*0x2e3ee8*/
          {
            while ( HIDWORD(savedregs[4]) == -1864225944 ) /*0x2e3ee8*/
            {
              BYTE6(savedregs[2]) = (((((((loc_2E3E9C >> 10 == 3508160) << 31 >> 31) /*0x2e42e4*/
                                       + ((loc_2E3EA0 >> 10 == 3508160) << 31 >> 31)) << 31 >> 31)
                                     - 1) << 31 >> 31)
                                   + ((loc_2E3EA0 >> 10 != 3508160 || loc_2E3E9C >> 10 != 3508160) << 31 >> 31))
                                  & 1;
              HIDWORD(savedregs[4]) = -263390907; /*0x2e42f4*/
            }
            if ( HIDWORD(savedregs[4]) != -1450271296 ) /*0x2e3efc*/
              break; /*0x2e3efc*/
            HIDWORD(savedregs[4]) = -1864225944; /*0x2e4270*/
          }
          if ( HIDWORD(savedregs[4]) != -1446647105 ) /*0x2e3f10*/
            break; /*0x2e3f10*/
          HIBYTE(savedregs[2]) = *(_DWORD *)sub_2E3E98 >> 26 == 5 || *(_DWORD *)sub_2E3E98 >> 21 == 1697; /*0x2e4220*/
          HIDWORD(savedregs[4]) = 692526728; /*0x2e4230*/
        }
        if ( HIDWORD(savedregs[4]) != -1346213134 ) /*0x2e3f38*/
          break; /*0x2e3f38*/
        HIDWORD(savedregs[4]) = 1672984869; /*0x2e40c0*/
      }
      if ( HIDWORD(savedregs[4]) == -743672015 ) /*0x2e3f4c*/
      {
        _ReadStatusReg(TPIDR_EL0); /*0x2e41b4*/
        abort(); /*0x2e41c8*/
      }
      if ( HIDWORD(savedregs[4]) == -702217507 ) /*0x2e3f60*/
        JUMPOUT(0x2E432C); /*0x2e432c*/
      if ( HIDWORD(savedregs[4]) != -263390907 ) /*0x2e3f88*/
        break; /*0x2e3f88*/
      if ( (savedregs[2] & 0x1000000000000LL) != 0 ) /*0x2e4318*/
        v13 = 1405888877; /*0x2e4318*/
      else
        v13 = -59702638; /*0x2e4318*/
      HIDWORD(savedregs[4]) = v13; /*0x2e4320*/
    }
    if ( HIDWORD(savedregs[4]) == -260701015 ) /*0x2e3f9c*/
      break; /*0x2e3f9c*/
    switch ( HIDWORD(savedregs[4]) ) /*0x2e3fb0*/
    {
      case 0xFC710292: /*0x2e3fb0*/
        HIDWORD(savedregs[4]) = 545407299; /*0x2e40d4*/
        break;
      case 0x19EC6A3F: /*0x2e3fb0*/
        HIDWORD(savedregs[4]) = -1346213134; /*0x2e40ac*/
        break;
      case 0x20824143: /*0x2e3fb0*/
        savedregs[4] = a4; /*0x2e4108*/
        v5 = a1; /*0x2e4124*/
        v6 = a2; /*0x2e412c*/
        v7 = a3; /*0x2e4134*/
        v8 = a4; /*0x2e413c*/
        v9 = (*(__int64 (__fastcall **)(__int64, __int64, __int64, __int64))(*(_QWORD *)a3 + 264LL))(a3, a3, a3, a4); /*0x2e4144*/
        a2 = v6; /*0x2e4148*/
        a3 = v7; /*0x2e414c*/
        a4 = v8; /*0x2e4150*/
        v10 = v9; /*0x2e4154*/
        a1 = v5; /*0x2e4158*/
        savedregs[3] = v10; /*0x2e415c*/
        HIDWORD(savedregs[4]) = -260701015; /*0x2e416c*/
        break;
      case 0x29471E88: /*0x2e3fb0*/
        if ( (savedregs[2] & 0x100000000000000LL) != 0 ) /*0x2e4254*/
          v12 = 1405888877; /*0x2e4254*/
        else
          v12 = -1450271296; /*0x2e4254*/
        HIDWORD(savedregs[4]) = v12; /*0x2e425c*/
        break;
      case 0x53CC296D: /*0x2e3fb0*/
        HIDWORD(savedregs[4]) = -743672015; /*0x2e41ac*/
        break;
      case 0x63B7B925: /*0x2e3fb0*/
        HIDWORD(savedregs[4]) = -1446647105; /*0x2e41ec*/
        break;
      default:
        if ( LODWORD(savedregs[4]) < 0xB4E43132 ) /*0x2e4090*/
          v4 = 434924095; /*0x2e4090*/
        else
          v4 = -702217507; /*0x2e4090*/
        HIDWORD(savedregs[4]) = v4; /*0x2e4098*/
        break;
    }
  }
  result = savedregs[3]; /*0x2e4174*/
  _ReadStatusReg(TPIDR_EL0); /*0x2e4178*/
  return result; /*0x2e419c*/
}