__int64 __fastcall sub_7149D8(__int64 a1)
{
  int v2; // w8
  int v3; // w8
  bool v4; // [xsp+1Eh] [xbp-2h]
  char v5; // [xsp+1Fh] [xbp-1h]
  unsigned __int64 i; // [xsp+20h] [xbp+0h]
  __int64 savedregs_8; // [xsp+28h] [xbp+8h]

  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x7149ec*/
  for ( i = 0xCE9ED87958E10B2BLL; ; HIDWORD(i) = -1947775717 ) /*0x7149f8*/
  {
    while ( 1 ) /*0x714ad4*/
    {
      while ( 1 ) /*0x714ac0*/
      {
        while ( 1 ) /*0x714a84*/
        {
          while ( 1 ) /*0x714a70*/
          {
            while ( 1 ) /*0x714a5c*/
            {
              while ( 1 ) /*0x714a34*/
              {
                while ( 1 ) /*0x714a20*/
                {
                  while ( HIDWORD(i) == -2074889799 ) /*0x714a20*/
                    HIDWORD(i) = 1786012014; /*0x714b6c*/
                  if ( HIDWORD(i) != -1947775717 ) /*0x714a34*/
                    break; /*0x714a34*/
                  HIDWORD(i) = -1459739199; /*0x714bdc*/
                }
                if ( HIDWORD(i) != -1459739199 ) /*0x714a5c*/
                  break; /*0x714a5c*/
                v5 = (*(_DWORD *)sub_7149D8 >> 26 == 5 && *(_DWORD *)sub_7149D8 >> 21 == 1697) /*0x714c18*/
                   | (*(_DWORD *)sub_7149D8 >> 26 == 5) ^ (*(_DWORD *)sub_7149D8 >> 21 == 1697);
                HIDWORD(i) = 706117936; /*0x714c28*/
              }
              if ( HIDWORD(i) != -828450695 ) /*0x714a70*/
                break; /*0x714a70*/
              HIDWORD(i) = -2074889799; /*0x714b58*/
            }
            if ( HIDWORD(i) != -807201955 ) /*0x714a84*/
              break; /*0x714a84*/
            v4 = loc_7149DC >> 10 == 3508160 || loc_7149E0 >> 10 == 3508160; /*0x714cb8*/
            HIDWORD(i) = 1233037877; /*0x714cc8*/
          }
          if ( HIDWORD(i) != 706117936 ) /*0x714ac0*/
            break; /*0x714ac0*/
          if ( (v5 & 1) != 0 ) /*0x714c4c*/
            v2 = 1815054115; /*0x714c4c*/
          else
            v2 = 1492941900; /*0x714c4c*/
          HIDWORD(i) = v2; /*0x714c54*/
        }
        if ( HIDWORD(i) != 1233037877 ) /*0x714ad4*/
          break; /*0x714ad4*/
        if ( v4 ) /*0x714cd4*/
          v3 = 1815054115; /*0x714cec*/
        else
          v3 = 1951910158; /*0x714cec*/
        HIDWORD(i) = v3; /*0x714cf4*/
      }
      if ( HIDWORD(i) != 1492941900 ) /*0x714ae8*/
        break; /*0x714ae8*/
      HIDWORD(i) = -807201955; /*0x714c68*/
    }
    if ( HIDWORD(i) != 1786012014 ) /*0x714afc*/
      break; /*0x714afc*/
  }
  if ( HIDWORD(i) == 1815054115 ) /*0x714b10*/
  {
    _ReadStatusReg(TPIDR_EL0); /*0x714bb8*/
    abort(); /*0x714bcc*/
  }
  _ReadStatusReg(TPIDR_EL0); /*0x714b94*/
  return 17; /*0x714bb4*/
}