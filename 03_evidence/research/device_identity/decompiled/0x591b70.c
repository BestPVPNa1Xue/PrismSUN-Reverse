__int64 __fastcall sub_591B70(__int64 a1, __int64 a2, __int64 a3)
{
  char v3; // w0
  int v5; // w8
  int v6; // w8
  _QWORD savedregs[6]; // [xsp+20h] [xbp+0h] BYREF

  savedregs[5] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x591b8c*/
  savedregs[4] = 0x5B65D5768E61098FLL; /*0x591b98*/
  savedregs[3] = (char *)&savedregs[4] + 4; /*0x591bac*/
  while ( 1 ) /*0x591bfc*/
  {
    while ( 1 ) /*0x591be8*/
    {
      while ( 1 ) /*0x591bd4*/
      {
        while ( 1 ) /*0x591bb0*/
        {
          if ( HIDWORD(savedregs[4]) == -1466504749 ) /*0x591bc0*/
          {
            _ReadStatusReg(TPIDR_EL0); /*0x591d30*/
            sub_593834(a1, a2, a3); /*0x591d44*/
          }
          if ( HIDWORD(savedregs[4]) != -1235911524 ) /*0x591bd4*/
            break; /*0x591bd4*/
          if ( (loc_591B74 >> 10 == 3508160 && loc_591B78 >> 10 == 3508160) /*0x591df0*/
             | (loc_591B74 >> 10 == 3508160) ^ (loc_591B78 >> 10 == 3508160) )
          {
            v6 = -1466504749; /*0x591df4*/
          }
          else
          {
            v6 = -399292333; /*0x591df4*/
          }
          HIDWORD(savedregs[4]) = v6; /*0x591dfc*/
        }
        if ( HIDWORD(savedregs[4]) != -1090088898 ) /*0x591be8*/
          break; /*0x591be8*/
        HIDWORD(savedregs[4]) = -963730425; /*0x591c94*/
      }
      if ( HIDWORD(savedregs[4]) != -963730425 ) /*0x591bfc*/
        break; /*0x591bfc*/
      HIDWORD(savedregs[4]) = 1864965886; /*0x591ca8*/
    }
    if ( HIDWORD(savedregs[4]) == -399292333 ) /*0x591c10*/
      break; /*0x591c10*/
    if ( HIDWORD(savedregs[4]) == 1533400438 ) /*0x591c38*/
    {
      HIDWORD(savedregs[4]) = -1090088898; /*0x591c80*/
    }
    else
    {
      if ( *(_DWORD *)sub_591B70 >> 26 == 5 || *(_DWORD *)sub_591B70 >> 21 == 1697 ) /*0x591d80*/
        v5 = -1466504749; /*0x591d84*/
      else
        v5 = -1235911524; /*0x591d84*/
      HIDWORD(savedregs[4]) = v5; /*0x591d8c*/
    }
  }
  savedregs[4] = a3; /*0x591cd0*/
  sub_19C47C(a3); /*0x591ce0*/
  sub_D038C(savedregs[4]); /*0x591cec*/
  sub_593830(); /*0x591d00*/
  _ReadStatusReg(TPIDR_EL0); /*0x591d04*/
  return v3 & 1; /*0x591d2c*/
}