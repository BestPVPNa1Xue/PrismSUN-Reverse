__int64 __fastcall sub_714D58(__int64 a1)
{
  int v2; // w8
  int v3; // w8
  __int64 i; // [xsp+20h] [xbp+0h]
  __int64 savedregs_8; // [xsp+28h] [xbp+8h]

  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x714d6c*/
  for ( i = 0x3646EBB2EC95156ALL; ; HIDWORD(i) = -442391946 ) /*0x714d78*/
  {
    while ( 1 ) /*0x714e18*/
    {
      while ( 1 ) /*0x714e04*/
      {
        while ( 1 ) /*0x714df0*/
        {
          while ( 1 ) /*0x714ddc*/
          {
            while ( HIDWORD(i) == -493497421 ) /*0x714ddc*/
            {
              if ( *(_DWORD *)sub_714D58 >> 26 == 5 || *(_DWORD *)sub_714D58 >> 21 == 1697 ) /*0x714f74*/
                v2 = -183804223; /*0x714f78*/
              else
                v2 = 8155282; /*0x714f78*/
              HIDWORD(i) = v2; /*0x714f80*/
            }
            if ( HIDWORD(i) != -442391946 ) /*0x714df0*/
              break; /*0x714df0*/
            HIDWORD(i) = 263312552; /*0x714eb0*/
          }
          if ( HIDWORD(i) != -183804223 ) /*0x714e04*/
            break; /*0x714e04*/
          HIDWORD(i) = 1435764931; /*0x714f08*/
        }
        if ( HIDWORD(i) != 8155282 ) /*0x714e18*/
          break; /*0x714e18*/
        if ( loc_714D5C >> 10 == 3508160 || loc_714D60 >> 10 == 3508160 ) /*0x714fdc*/
          v3 = -183804223; /*0x714fe0*/
        else
          v3 = 567549026; /*0x714fe0*/
        HIDWORD(i) = v3; /*0x714fe8*/
      }
      if ( HIDWORD(i) != 263312552 ) /*0x714e2c*/
        break; /*0x714e2c*/
      HIDWORD(i) = -493497421; /*0x714ec4*/
    }
    if ( HIDWORD(i) == 567549026 ) /*0x714e40*/
      break; /*0x714e40*/
    if ( HIDWORD(i) != 910617522 ) /*0x714e54*/
    {
      _ReadStatusReg(TPIDR_EL0); /*0x714f10*/
      abort(); /*0x714f24*/
    }
  }
  _ReadStatusReg(TPIDR_EL0); /*0x714ed8*/
  return 1; /*0x714ef8*/
}