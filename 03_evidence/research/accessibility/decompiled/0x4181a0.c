__int64 __fastcall sub_4181A0(
        __int64 a1,
        unsigned int a2,
        __int64 a3,
        __int64 a4,
        __int64 a5,
        __int64 a6,
        __int64 a7,
        __int64 a8,
        __int64 a9)
{
  char v9; // w0
  int v11; // w8
  int v12; // w8
  bool v13; // [xsp+1Fh] [xbp-1h]
  __int64 savedregs; // [xsp+20h] [xbp+0h]
  __int64 savedregs_8; // [xsp+28h] [xbp+8h]

  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x4181b4*/
  savedregs = 0x4383340563DFD054LL; /*0x4181c0*/
  while ( 1 ) /*0x418238*/
  {
    while ( 1 ) /*0x418210*/
    {
      while ( 1 ) /*0x4181fc*/
      {
        while ( 1 ) /*0x4181e8*/
        {
          while ( HIDWORD(savedregs) == -1580326077 ) /*0x4181e8*/
            HIDWORD(savedregs) = -751418259; /*0x41844c*/
          if ( HIDWORD(savedregs) != -1318046772 ) /*0x4181fc*/
            break; /*0x4181fc*/
          HIDWORD(savedregs) = 2143315356; /*0x418334*/
        }
        if ( HIDWORD(savedregs) != -1011383032 ) /*0x418210*/
          break; /*0x418210*/
        if ( (*(_DWORD *)sub_4181A0 >> 26 == 5 || *(_DWORD *)sub_4181A0 >> 21 == 1697) /*0x418408*/
          && (*(_DWORD *)sub_4181A0 >> 26 == 5 || *(_DWORD *)sub_4181A0 >> 21 == 1697) )
        {
          v11 = 1655387660; /*0x418430*/
        }
        else
        {
          v11 = -1580326077; /*0x418430*/
        }
        HIDWORD(savedregs) = v11; /*0x418438*/
      }
      if ( HIDWORD(savedregs) != -751418259 ) /*0x418238*/
        break; /*0x418238*/
      v13 = loc_4181A4 >> 10 == 3508160 || loc_4181A8 >> 10 == 3508160; /*0x41849c*/
      HIDWORD(savedregs) = 1957374876; /*0x4184ac*/
    }
    if ( HIDWORD(savedregs) == -288717195 ) /*0x418260*/
      break; /*0x418260*/
    switch ( HIDWORD(savedregs) ) /*0x418274*/
    {
      case 0x198DF019: /*0x418274*/
        _ReadStatusReg(TPIDR_EL0); /*0x4183ac*/
        abort(); /*0x4183c0*/
      case 0x43833405: /*0x418274*/
        HIDWORD(savedregs) = -1318046772; /*0x418320*/
        break;
      case 0x62AB360C: /*0x418274*/
        HIDWORD(savedregs) = 428732441; /*0x4183a4*/
        break;
      case 0x74AB2B9C: /*0x418274*/
        if ( v13 ) /*0x4184b8*/
          v12 = 1655387660; /*0x4184d0*/
        else
          v12 = -288717195; /*0x4184d0*/
        HIDWORD(savedregs) = v12; /*0x4184d8*/
        break;
      default:
        HIDWORD(savedregs) = -1011383032; /*0x418348*/
        break;
    }
  }
  a9 = a1; /*0x418360*/
  v9 = ((__int64 (__fastcall *)(__int64, _QWORD))loc_4370B0)(a1, a2); /*0x418370*/
  _ReadStatusReg(TPIDR_EL0); /*0x418374*/
  return v9 & 1; /*0x418394*/
}