bool __fastcall sub_331F98(__int64 a1)
{
  int v1; // w8
  int v3; // w8
  int v4; // w8
  bool v5; // [xsp+1Eh] [xbp-2h]
  bool v6; // [xsp+1Fh] [xbp-1h]
  __int64 savedregs; // [xsp+20h] [xbp+0h]
  __int64 savedregs_8; // [xsp+28h] [xbp+8h]

  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x331fac*/
  savedregs = 0xED858725544A5BC4LL; /*0x331fb8*/
  while ( 1 ) /*0x332080*/
  {
    while ( 1 ) /*0x33206c*/
    {
      while ( 1 ) /*0x332058*/
      {
        while ( 1 ) /*0x332044*/
        {
          while ( 1 ) /*0x332008*/
          {
            while ( 1 ) /*0x331ff4*/
            {
              while ( 1 ) /*0x331fe0*/
              {
                while ( HIDWORD(savedregs) == -2000590559 ) /*0x331fe0*/
                  HIDWORD(savedregs) = 1219405415; /*0x332154*/
                if ( HIDWORD(savedregs) != -1386248582 ) /*0x331ff4*/
                  break; /*0x331ff4*/
                v5 = *(_DWORD *)sub_331F98 >> 26 == 5 || *(_DWORD *)sub_331F98 >> 21 == 1697; /*0x332218*/
                HIDWORD(savedregs) = -1259242743; /*0x332228*/
              }
              if ( HIDWORD(savedregs) != -1259242743 ) /*0x332008*/
                break; /*0x332008*/
              if ( v5 ) /*0x332234*/
                v3 = 1642087172; /*0x33224c*/
              else
                v3 = 1622877232; /*0x33224c*/
              HIDWORD(savedregs) = v3; /*0x332254*/
            }
            if ( HIDWORD(savedregs) != -353047460 ) /*0x332044*/
              break; /*0x332044*/
            HIDWORD(savedregs) = -1386248582; /*0x3321e4*/
          }
          if ( HIDWORD(savedregs) != -310016219 ) /*0x332058*/
            break; /*0x332058*/
          if ( (unsigned int)savedregs < 0xAADFA394 ) /*0x332110*/
            v1 = 1685051401; /*0x332110*/
          else
            v1 = 1726482805; /*0x332110*/
          HIDWORD(savedregs) = v1; /*0x332118*/
        }
        if ( HIDWORD(savedregs) != -180611199 ) /*0x33206c*/
          break; /*0x33206c*/
        HIDWORD(savedregs) = -353047460; /*0x332140*/
      }
      if ( HIDWORD(savedregs) != 1219405415 ) /*0x332080*/
        break; /*0x332080*/
      savedregs = (unsigned int)a1 | 0x4D99FC2D00000000LL; /*0x332164*/
      v6 = *(_QWORD *)(a1 + 8) != 0; /*0x33217c*/
    }
    if ( HIDWORD(savedregs) == 1301937197 ) /*0x332094*/
      break; /*0x332094*/
    switch ( HIDWORD(savedregs) ) /*0x3320a8*/
    {
      case 0x60BB2430: /*0x3320a8*/
        if ( (loc_331F9C >> 10 != 3508160) ^ (loc_331FA0 >> 10 != 3508160) /*0x3322d8*/
           | (loc_331F9C >> 10 == 3508160 && loc_331FA0 >> 10 == 3508160) )
        {
          v4 = 1642087172; /*0x3322dc*/
        }
        else
        {
          v4 = -2000590559; /*0x3322dc*/
        }
        HIDWORD(savedregs) = v4; /*0x3322e4*/
        break;
      case 0x61E04304: /*0x3320a8*/
        _ReadStatusReg(TPIDR_EL0); /*0x3321c0*/
        abort(); /*0x3321d4*/
      case 0x646FD809: /*0x3320a8*/
        HIDWORD(savedregs) = -180611199; /*0x33212c*/
        break;
      default:
        JUMPOUT(0x3322F0); /*0x3322f0*/
    }
  }
  _ReadStatusReg(TPIDR_EL0); /*0x33219c*/
  return v6; /*0x3321bc*/
}