__int64 __fastcall sub_4CE0F4(__int64 result, int a2, __int64 a3)
{
  int v3; // w8
  __int64 v4; // x19
  int v5; // w20
  __int64 v6; // x21
  char v7; // w0
  char v8; // w8
  int v9; // w8
  int v10; // w8
  int v11; // w8
  bool v12; // [xsp+3Eh] [xbp+1Eh]
  char v13; // [xsp+3Fh] [xbp+1Fh]
  __int64 savedregs; // [xsp+40h] [xbp+20h]
  __int64 savedregs_8; // [xsp+48h] [xbp+28h]

  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x4ce110*/
  savedregs = 0xA02F7C60903359F6LL; /*0x4ce11c*/
  while ( 1 ) /*0x4ce20c*/
  {
    while ( 1 ) /*0x4ce1f8*/
    {
      while ( 1 ) /*0x4ce1e4*/
      {
        while ( 1 ) /*0x4ce1d0*/
        {
          while ( 1 ) /*0x4ce1a8*/
          {
            while ( 1 ) /*0x4ce194*/
            {
              while ( 1 ) /*0x4ce16c*/
              {
                while ( 1 ) /*0x4ce158*/
                {
                  while ( 1 ) /*0x4ce134*/
                  {
                    if ( HIDWORD(savedregs) == -1984963942 ) /*0x4ce144*/
                    {
                      _ReadStatusReg(TPIDR_EL0); /*0x4ce440*/
                      sub_56B9D8(); /*0x4ce454*/
                    }
                    if ( HIDWORD(savedregs) != -1781328320 ) /*0x4ce158*/
                      break; /*0x4ce158*/
                    HIDWORD(savedregs) = -623504296; /*0x4ce3e8*/
                  }
                  if ( HIDWORD(savedregs) != -1607500704 ) /*0x4ce16c*/
                    break; /*0x4ce16c*/
                  if ( (_DWORD)savedregs == -1226023953 ) /*0x4ce2d8*/
                    v3 = 227657762; /*0x4ce2d8*/
                  else
                    v3 = 1091912081; /*0x4ce2d8*/
                  HIDWORD(savedregs) = v3; /*0x4ce2e0*/
                }
                if ( HIDWORD(savedregs) != -1200637823 ) /*0x4ce194*/
                  break; /*0x4ce194*/
                HIDWORD(savedregs) = -684227701; /*0x4ce308*/
              }
              if ( HIDWORD(savedregs) != -861189262 ) /*0x4ce1a8*/
                break; /*0x4ce1a8*/
              savedregs = (unsigned int)a3 | 0x5E5B0B8B00000000LL; /*0x4ce344*/
              v4 = result; /*0x4ce364*/
              v5 = a2; /*0x4ce370*/
              v6 = a3; /*0x4ce378*/
              v7 = ((__int64 (__fastcall *)(void *, _QWORD, __int64))loc_591B70)(&unk_7C06AC, (unsigned __int8)a2, a3); /*0x4ce380*/
              a2 = v5; /*0x4ce384*/
              a3 = v6; /*0x4ce388*/
              v8 = v7; /*0x4ce38c*/
              result = v4; /*0x4ce390*/
              v13 = v8 & 1; /*0x4ce398*/
            }
            if ( HIDWORD(savedregs) != -684227701 ) /*0x4ce1d0*/
              break; /*0x4ce1d0*/
            HIDWORD(savedregs) = 1511165030; /*0x4ce464*/
          }
          if ( HIDWORD(savedregs) != -623504296 ) /*0x4ce1e4*/
            break; /*0x4ce1e4*/
          HIDWORD(savedregs) = -258764459; /*0x4ce3fc*/
        }
        if ( HIDWORD(savedregs) != -258764459 ) /*0x4ce1f8*/
          break; /*0x4ce1f8*/
        HIDWORD(savedregs) = 987938315; /*0x4ce410*/
      }
      if ( HIDWORD(savedregs) != -50443155 ) /*0x4ce20c*/
        break; /*0x4ce20c*/
      HIDWORD(savedregs) = -861189262; /*0x4ce31c*/
    }
    if ( HIDWORD(savedregs) == 227657762 ) /*0x4ce220*/
      JUMPOUT(0x4CE564); /*0x4ce564*/
    if ( HIDWORD(savedregs) == 987938315 ) /*0x4ce248*/
      break; /*0x4ce248*/
    switch ( HIDWORD(savedregs) ) /*0x4ce25c*/
    {
      case 0x41154191: /*0x4ce25c*/
        HIDWORD(savedregs) = -1200637823; /*0x4ce2f4*/
        break;
      case 0x41677AD6: /*0x4ce25c*/
        if ( v12 ) /*0x4ce4b4*/
          v10 = -1984963942; /*0x4ce4cc*/
        else
          v10 = 1199019529; /*0x4ce4cc*/
        HIDWORD(savedregs) = v10; /*0x4ce4d4*/
        break;
      case 0x47779609: /*0x4ce25c*/
        if ( ((((((loc_4CE0F8 >> 10 == 3508160) << 31 >> 31) /*0x4ce554*/
               + (((loc_4CE0F8 >> 10 == 3508160) ^ (loc_4CE0FC >> 10 == 3508160)) << 31 >> 31)) << 31 >> 31)
             - (((loc_4CE0F8 >> 10 == 3508160) & (unsigned __int8)(loc_4CE0FC >> 10 != 3508160)) << 31 >> 31))
            & 1) != 0 )
          v11 = -1984963942; /*0x4ce554*/
        else
          v11 = -50443155; /*0x4ce554*/
        HIDWORD(savedregs) = v11; /*0x4ce55c*/
        break;
      case 0x5A128C66: /*0x4ce25c*/
        v12 = *(_DWORD *)sub_4CE0F4 >> 26 == 5 || *(_DWORD *)sub_4CE0F4 >> 21 == 1697; /*0x4ce498*/
        HIDWORD(savedregs) = 1097300694; /*0x4ce4a8*/
        break;
      default:
        if ( (v13 & 1) != 0 ) /*0x4ce3cc*/
          v9 = -623504296; /*0x4ce3cc*/
        else
          v9 = -1781328320; /*0x4ce3cc*/
        HIDWORD(savedregs) = v9; /*0x4ce3d4*/
        break;
    }
  }
  _ReadStatusReg(TPIDR_EL0); /*0x4ce418*/
  return result; /*0x4ce43c*/
}