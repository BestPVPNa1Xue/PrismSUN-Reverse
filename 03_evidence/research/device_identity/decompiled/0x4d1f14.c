__int64 __fastcall sub_4D1F14(__int64 a1, double a2, double a3, double a4, double a5, long double a6)
{
  __int64 v6; // x21
  __int128 v7; // q23
  int v8; // w8
  __int64 result; // x0
  int v10; // w8
  int v11; // w8
  bool v12; // [xsp+1Bh] [xbp-5h]
  unsigned __int16 v13; // [xsp+1Ch] [xbp-4h]
  __int64 savedregs; // [xsp+20h] [xbp+0h]
  __int64 savedregs_8; // [xsp+28h] [xbp+8h]

  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x4d1f28*/
  savedregs = 0x651E2E4A999E286FLL; /*0x4d1f34*/
  while ( 1 ) /*0x4d2038*/
  {
    while ( 1 ) /*0x4d2024*/
    {
      while ( 1 ) /*0x4d2010*/
      {
        while ( 1 ) /*0x4d1fe8*/
        {
          while ( 1 ) /*0x4d1fc0*/
          {
            while ( 1 ) /*0x4d1f84*/
            {
              while ( 1 ) /*0x4d1f70*/
              {
                while ( 1 ) /*0x4d1f5c*/
                {
                  while ( HIDWORD(savedregs) == -1945594203 ) /*0x4d1f5c*/
                  {
                    savedregs = (unsigned int)a1 | 0x52F29DC200000000LL; /*0x4d211c*/
                    v13 = *(_WORD *)(a1 + 616); /*0x4d2128*/
                  }
                  if ( HIDWORD(savedregs) != -1427319394 ) /*0x4d1f70*/
                    break; /*0x4d1f70*/
                  HIDWORD(savedregs) = 277169829; /*0x4d2170*/
                }
                if ( HIDWORD(savedregs) != -1150457750 ) /*0x4d1f84*/
                  break; /*0x4d1f84*/
                if ( v12 ) /*0x4d2200*/
                  v10 = -1427319394; /*0x4d2218*/
                else
                  v10 = 1020608123; /*0x4d2218*/
                HIDWORD(savedregs) = v10; /*0x4d2220*/
              }
              if ( HIDWORD(savedregs) == -995985687 ) /*0x4d1fac*/
              {
                *(_OWORD *)v6 = v7; /*0x4d22ac*/
                *(long double *)(v6 + 16) = a6; /*0x4d22ac*/
                JUMPOUT(0x4D22B0); /*0x4d22b0*/
              }
              if ( HIDWORD(savedregs) != -967901866 ) /*0x4d1fc0*/
                break; /*0x4d1fc0*/
              HIDWORD(savedregs) = -1945594203; /*0x4d210c*/
            }
            if ( HIDWORD(savedregs) != -380690496 ) /*0x4d1fe8*/
              break; /*0x4d1fe8*/
            HIDWORD(savedregs) = 1059211633; /*0x4d20f8*/
          }
          if ( HIDWORD(savedregs) == 277169829 ) /*0x4d1ffc*/
          {
            _ReadStatusReg(TPIDR_EL0); /*0x4d2178*/
            sub_56BDF0(); /*0x4d218c*/
          }
          if ( HIDWORD(savedregs) != 1020608123 ) /*0x4d2010*/
            break; /*0x4d2010*/
          if ( loc_4D1F18 >> 10 == 3508160 || loc_4D1F1C >> 10 == 3508160 ) /*0x4d2298*/
            v11 = -1427319394; /*0x4d229c*/
          else
            v11 = -967901866; /*0x4d229c*/
          HIDWORD(savedregs) = v11; /*0x4d22a4*/
        }
        if ( HIDWORD(savedregs) != 1059211633 ) /*0x4d2024*/
          break; /*0x4d2024*/
        HIDWORD(savedregs) = 1221736640; /*0x4d21b0*/
      }
      if ( HIDWORD(savedregs) != 1221736640 ) /*0x4d2038*/
        break; /*0x4d2038*/
      v12 = *(_DWORD *)sub_4D1F14 >> 26 == 5 || *(_DWORD *)sub_4D1F14 >> 21 == 1697; /*0x4d21e4*/
      HIDWORD(savedregs) = -1150457750; /*0x4d21f4*/
    }
    if ( HIDWORD(savedregs) == 1391631810 ) /*0x4d204c*/
      break; /*0x4d204c*/
    if ( HIDWORD(savedregs) == 1696476746 ) /*0x4d2074*/
    {
      if ( (_DWORD)savedregs == 338677106 ) /*0x4d20c8*/
        v8 = -995985687; /*0x4d20c8*/
      else
        v8 = 1969696241; /*0x4d20c8*/
      HIDWORD(savedregs) = v8; /*0x4d20d0*/
    }
    else
    {
      HIDWORD(savedregs) = -380690496; /*0x4d20e4*/
    }
  }
  result = v13; /*0x4d2140*/
  _ReadStatusReg(TPIDR_EL0); /*0x4d2144*/
  return result; /*0x4d2160*/
}