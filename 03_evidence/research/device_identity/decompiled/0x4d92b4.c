bool __fastcall sub_4D92B4(__int64 a1)
{
  int v1; // w8
  int v3; // w8
  int v4; // w8
  bool v5; // [xsp+1Dh] [xbp-3h]
  bool v6; // [xsp+1Eh] [xbp-2h]
  bool v7; // [xsp+1Fh] [xbp-1h]
  __int64 savedregs; // [xsp+20h] [xbp+0h]
  __int64 savedregs_8; // [xsp+28h] [xbp+8h]

  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x4d92c8*/
  savedregs = 0x72C91F222C8FB80ELL; /*0x4d92d4*/
  while ( 1 ) /*0x4d93c4*/
  {
    while ( 1 ) /*0x4d93b0*/
    {
      while ( 1 ) /*0x4d939c*/
      {
        while ( 1 ) /*0x4d9388*/
        {
          while ( 1 ) /*0x4d9374*/
          {
            while ( 1 ) /*0x4d9338*/
            {
              while ( 1 ) /*0x4d9324*/
              {
                while ( 1 ) /*0x4d9310*/
                {
                  while ( HIDWORD(savedregs) == -1413920724 ) /*0x4d9310*/
                    HIDWORD(savedregs) = -1356747042; /*0x4d953c*/
                  if ( HIDWORD(savedregs) != -1356747042 ) /*0x4d9324*/
                    break; /*0x4d9324*/
                  v6 = *(_DWORD *)sub_4D92B4 >> 26 == 5 || *(_DWORD *)sub_4D92B4 >> 21 == 1697; /*0x4d9588*/
                  HIDWORD(savedregs) = -565438299; /*0x4d9598*/
                }
                if ( HIDWORD(savedregs) != -1248529437 ) /*0x4d9338*/
                  break; /*0x4d9338*/
                savedregs = (unsigned int)a1 | 0x408567AD00000000LL; /*0x4d94bc*/
                v7 = *(_WORD *)(a1 + 616) != 0; /*0x4d94d4*/
              }
              if ( HIDWORD(savedregs) != -830659339 ) /*0x4d9374*/
                break; /*0x4d9374*/
              HIDWORD(savedregs) = -1248529437; /*0x4d94ac*/
            }
            if ( HIDWORD(savedregs) != -572904727 ) /*0x4d9388*/
              break; /*0x4d9388*/
            HIDWORD(savedregs) = -563851786; /*0x4d9484*/
          }
          if ( HIDWORD(savedregs) != -565438299 ) /*0x4d939c*/
            break; /*0x4d939c*/
          if ( v6 ) /*0x4d95a4*/
            v3 = 860674788; /*0x4d95bc*/
          else
            v3 = 2079585617; /*0x4d95bc*/
          HIDWORD(savedregs) = v3; /*0x4d95c4*/
        }
        if ( HIDWORD(savedregs) != -563851786 ) /*0x4d93b0*/
          break; /*0x4d93b0*/
        HIDWORD(savedregs) = -1413920724; /*0x4d9498*/
      }
      if ( HIDWORD(savedregs) != -537698099 ) /*0x4d93c4*/
        break; /*0x4d93c4*/
      if ( v5 ) /*0x4d9644*/
        v4 = 860674788; /*0x4d965c*/
      else
        v4 = -830659339; /*0x4d965c*/
      HIDWORD(savedregs) = v4; /*0x4d9664*/
    }
    if ( HIDWORD(savedregs) == 860674788 ) /*0x4d93d8*/
    {
      _ReadStatusReg(TPIDR_EL0); /*0x4d9518*/
      abort(); /*0x4d952c*/
    }
    if ( HIDWORD(savedregs) == 1082484653 ) /*0x4d93ec*/
      break; /*0x4d93ec*/
    switch ( HIDWORD(savedregs) ) /*0x4d9400*/
    {
      case 0x52A90A7D: /*0x4d9400*/
        JUMPOUT(0x4D9670); /*0x4d9670*/
      case 0x62C21186: /*0x4d9400*/
        v5 = loc_4D92B8 >> 10 == 3508160 || loc_4D92BC >> 10 == 3508160; /*0x4d9628*/
        HIDWORD(savedregs) = -537698099; /*0x4d9638*/
        break;
      case 0x72C91F22: /*0x4d9400*/
        if ( (_DWORD)savedregs == 46318552 ) /*0x4d9468*/
          v1 = 1386809981; /*0x4d9468*/
        else
          v1 = -572904727; /*0x4d9468*/
        HIDWORD(savedregs) = v1; /*0x4d9470*/
        break;
      default:
        HIDWORD(savedregs) = 1656885638; /*0x4d95d8*/
        break;
    }
  }
  _ReadStatusReg(TPIDR_EL0); /*0x4d94f4*/
  return v7; /*0x4d9514*/
}