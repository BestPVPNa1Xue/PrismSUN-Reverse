__int64 __fastcall sub_301194(__int64 a1, __int64 a2)
{
  __int64 result; // x0
  int v3; // w8
  int v4; // w8
  bool v5; // [xsp+1Eh] [xbp-2h]
  char v6; // [xsp+1Fh] [xbp-1h]
  unsigned __int64 savedregs; // [xsp+20h] [xbp+0h]
  __int64 savedregs_8; // [xsp+28h] [xbp+8h]

  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x3011a8*/
  savedregs = 0xD82619F013509610LL; /*0x3011b4*/
  while ( 1 ) /*0x30127c*/
  {
    while ( 1 ) /*0x301254*/
    {
      while ( 1 ) /*0x301240*/
      {
        while ( 1 ) /*0x30122c*/
        {
          while ( 1 ) /*0x301218*/
          {
            while ( 1 ) /*0x3011f0*/
            {
              while ( 1 ) /*0x3011dc*/
              {
                while ( HIDWORD(savedregs) == -1454429961 ) /*0x3011dc*/
                  HIDWORD(savedregs) = -581120223; /*0x301378*/
                if ( HIDWORD(savedregs) != -1344280099 ) /*0x3011f0*/
                  break; /*0x3011f0*/
                HIDWORD(savedregs) = -1245446845; /*0x3013d8*/
              }
              if ( HIDWORD(savedregs) == -1245446845 ) /*0x301204*/
              {
                _ReadStatusReg(TPIDR_EL0); /*0x3013e0*/
                abort(); /*0x3013f4*/
              }
              if ( HIDWORD(savedregs) != -668591632 ) /*0x301218*/
                break; /*0x301218*/
              HIDWORD(savedregs) = 2033326135; /*0x301350*/
            }
            if ( HIDWORD(savedregs) != -581120223 ) /*0x30122c*/
              break; /*0x30122c*/
            HIDWORD(savedregs) = 124778342; /*0x301418*/
          }
          if ( HIDWORD(savedregs) != -171043003 ) /*0x301240*/
            break; /*0x301240*/
          if ( (v6 & 1) != 0 ) /*0x3014a8*/
            v3 = -1344280099; /*0x3014a8*/
          else
            v3 = 1115469709; /*0x3014a8*/
          HIDWORD(savedregs) = v3; /*0x3014b0*/
        }
        if ( HIDWORD(savedregs) != -5475992 ) /*0x301254*/
          break; /*0x301254*/
        if ( v5 ) /*0x301530*/
          v4 = -1344280099; /*0x301548*/
        else
          v4 = 687160324; /*0x301548*/
        HIDWORD(savedregs) = v4; /*0x301550*/
      }
      if ( HIDWORD(savedregs) != 124778342 ) /*0x30127c*/
        break; /*0x30127c*/
      v6 = (*(_DWORD *)sub_301194 >> 26 == 5) ^ (*(_DWORD *)sub_301194 >> 21 == 1697) /*0x301474*/
         | (*(_DWORD *)sub_301194 >> 26 == 5 && *(_DWORD *)sub_301194 >> 21 == 1697);
      HIDWORD(savedregs) = -171043003; /*0x301484*/
    }
    if ( HIDWORD(savedregs) == 687160324 ) /*0x3012a4*/
      break; /*0x3012a4*/
    if ( HIDWORD(savedregs) == 1115469709 ) /*0x3012b8*/
    {
      HIDWORD(savedregs) = 1456581018; /*0x3014c4*/
    }
    else if ( HIDWORD(savedregs) == 1456581018 ) /*0x3012cc*/
    {
      v5 = loc_301198 >> 10 == 3508160 || loc_30119C >> 10 == 3508160; /*0x301514*/
      HIDWORD(savedregs) = -5475992; /*0x301524*/
    }
    else
    {
      HIDWORD(savedregs) = -1454429961; /*0x301364*/
    }
  }
  result = (*(__int64 (__fastcall **)(__int64, __int64))(*(_QWORD *)a1 + 184LL))(a1, a2); /*0x3013a8*/
  _ReadStatusReg(TPIDR_EL0); /*0x3013ac*/
  return result; /*0x3013c8*/
}