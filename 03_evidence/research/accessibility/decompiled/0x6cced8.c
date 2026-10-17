__int64 __fastcall sub_6CCED8(_QWORD *a1)
{
  __int64 result; // x0
  int v3; // w8
  int v4; // w8
  bool v5; // [xsp+2Fh] [xbp+Fh]
  int i; // [xsp+34h] [xbp+14h]

  _ReadStatusReg(TPIDR_EL0); /*0x6ccee8*/
  for ( i = -316822184; ; i = -1686821343 ) /*0x6ccf08*/
  {
    while ( 1 ) /*0x6ccfc4*/
    {
      while ( 1 ) /*0x6ccfb0*/
      {
        while ( 1 ) /*0x6ccf9c*/
        {
          while ( 1 ) /*0x6ccf60*/
          {
            while ( 1 ) /*0x6ccf4c*/
            {
              while ( 1 ) /*0x6ccf38*/
              {
                while ( 1 ) /*0x6ccf14*/
                {
                  if ( i == -1686821343 ) /*0x6ccf24*/
                  {
                    _ReadStatusReg(TPIDR_EL0); /*0x6cd0f0*/
                    abort(); /*0x6cd104*/
                  }
                  if ( i != -1367455102 ) /*0x6ccf38*/
                    break; /*0x6ccf38*/
                  v5 = loc_6CCEDC >> 10 == 3508160 || loc_6CCEE0 >> 10 == 3508160; /*0x6cd1c4*/
                  i = -209147672; /*0x6cd1d4*/
                }
                if ( i != -1170364904 ) /*0x6ccf4c*/
                  break; /*0x6ccf4c*/
                i = -1367455102; /*0x6cd174*/
              }
              if ( i != -1049796097 ) /*0x6ccf60*/
                break; /*0x6ccf60*/
              i = 843223095; /*0x6cd084*/
            }
            if ( i != -452375418 ) /*0x6ccf9c*/
              break; /*0x6ccf9c*/
            i = -1049796097; /*0x6cd070*/
          }
          if ( i != -316822184 ) /*0x6ccfb0*/
            break; /*0x6ccfb0*/
          i = -452375418; /*0x6cd05c*/
        }
        if ( i != -209147672 ) /*0x6ccfc4*/
          break; /*0x6ccfc4*/
        if ( v5 ) /*0x6cd1e0*/
          v4 = 1153607117; /*0x6cd1f8*/
        else
          v4 = 1236086502; /*0x6cd1f8*/
        i = v4; /*0x6cd200*/
      }
      if ( i != 843223095 ) /*0x6cd000*/
        break; /*0x6cd000*/
      if ( *(_DWORD *)sub_6CCED8 >> 26 == 5 || *(_DWORD *)sub_6CCED8 >> 21 == 1697 ) /*0x6cd154*/
        v3 = 1153607117; /*0x6cd158*/
      else
        v3 = -1170364904; /*0x6cd158*/
      i = v3; /*0x6cd160*/
    }
    if ( i != 1153607117 ) /*0x6cd014*/
      break; /*0x6cd014*/
  }
  result = ((__int64 (__fastcall *)(_QWORD *))loc_6CD3CC)(a1); /*0x6cd0a0*/
  *a1 = &off_793DE8; /*0x6cd0b4*/
  _ReadStatusReg(TPIDR_EL0); /*0x6cd0b8*/
  return result; /*0x6cd0d8*/
}