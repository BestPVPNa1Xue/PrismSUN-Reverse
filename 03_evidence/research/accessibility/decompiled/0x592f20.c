__int64 __fastcall sub_592F20(__int64 result, __int64 a2, unsigned int a3)
{
  int v3; // w8
  int v4; // w8
  int v5; // w8
  int v6; // w8
  int v7; // w8
  int v8; // w8
  char v9; // [xsp+1Ah] [xbp-16h]
  bool v10; // [xsp+1Bh] [xbp-15h]
  int v11; // [xsp+1Ch] [xbp-14h]
  unsigned int *v12; // [xsp+20h] [xbp-10h]
  unsigned int *v13; // [xsp+28h] [xbp-8h]
  _QWORD savedregs[2]; // [xsp+30h] [xbp+0h] BYREF

  savedregs[1] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x592f34*/
  savedregs[0] = 0x177409EEF7E2A1C1LL; /*0x592f40*/
  while ( 1 ) /*0x593058*/
  {
    while ( 1 ) /*0x593044*/
    {
      while ( 1 ) /*0x59301c*/
      {
        while ( 1 ) /*0x593008*/
        {
          while ( 1 ) /*0x592ff4*/
          {
            while ( 1 ) /*0x592fe0*/
            {
              while ( 1 ) /*0x592fcc*/
              {
                while ( 1 ) /*0x592fb8*/
                {
                  while ( 1 ) /*0x592fa4*/
                  {
                    while ( 1 ) /*0x592f90*/
                    {
                      while ( 1 ) /*0x592f68*/
                      {
                        while ( HIDWORD(savedregs[0]) == -2143086268 ) /*0x592f68*/
                        {
                          v9 = (loc_592F24 >> 10 != 3508160) ^ (loc_592F28 >> 10 != 3508160) /*0x593638*/
                             | (loc_592F24 >> 10 == 3508160 && loc_592F28 >> 10 == 3508160);
                          HIDWORD(savedregs[0]) = 1010633584; /*0x593648*/
                        }
                        if ( HIDWORD(savedregs[0]) == -2098806298 ) /*0x592f7c*/
                        {
                          _ReadStatusReg(TPIDR_EL0); /*0x593504*/
                          abort(); /*0x593518*/
                        }
                        if ( HIDWORD(savedregs[0]) != -2017589339 ) /*0x592f90*/
                          break; /*0x592f90*/
                        HIDWORD(savedregs[0]) = 803505659; /*0x5934b4*/
                      }
                      if ( HIDWORD(savedregs[0]) != -2006772489 ) /*0x592fa4*/
                        break; /*0x592fa4*/
                      HIDWORD(savedregs[0]) = -2017589339; /*0x593408*/
                    }
                    if ( HIDWORD(savedregs[0]) != -1893255656 ) /*0x592fb8*/
                      break; /*0x592fb8*/
                    if ( v11 >= 5 ) /*0x593364*/
                      v4 = 481591556; /*0x593364*/
                    else
                      v4 = 634552879; /*0x593364*/
                    HIDWORD(savedregs[0]) = v4; /*0x59336c*/
                  }
                  if ( HIDWORD(savedregs[0]) != -1866515357 ) /*0x592fcc*/
                    break; /*0x592fcc*/
                  HIDWORD(savedregs[0]) = -1893255656; /*0x593344*/
                }
                if ( HIDWORD(savedregs[0]) != -1853203250 ) /*0x592fe0*/
                  break; /*0x592fe0*/
                *v12 = *v13; /*0x5933e4*/
                HIDWORD(savedregs[0]) = -2006772489; /*0x5933f4*/
              }
              if ( HIDWORD(savedregs[0]) != -1704789222 ) /*0x592ff4*/
                break; /*0x592ff4*/
              HIDWORD(savedregs[0]) = 1848648796; /*0x5932bc*/
            }
            if ( HIDWORD(savedregs[0]) != -1323710814 ) /*0x593008*/
              break; /*0x593008*/
            HIDWORD(savedregs[0]) = -2017589339; /*0x5934a0*/
          }
          if ( HIDWORD(savedregs[0]) != -1196565817 ) /*0x59301c*/
            break; /*0x59301c*/
          HIDWORD(savedregs[0]) = -153984742; /*0x5932d0*/
        }
        if ( HIDWORD(savedregs[0]) == -1047382706 ) /*0x593030*/
          JUMPOUT(0x593680); /*0x593680*/
        if ( HIDWORD(savedregs[0]) != -917219379 ) /*0x593044*/
          break; /*0x593044*/
        atomic_store(*v13, v12); /*0x593430*/
        HIDWORD(savedregs[0]) = 1900800236; /*0x593440*/
      }
      if ( HIDWORD(savedregs[0]) != -887687068 ) /*0x593058*/
        break; /*0x593058*/
      HIDWORD(savedregs[0]) = 1128984660; /*0x593468*/
    }
    if ( HIDWORD(savedregs[0]) == -609265046 ) /*0x593080*/
      break; /*0x593080*/
    switch ( HIDWORD(savedregs[0]) ) /*0x593094*/
    {
      case 0xE89EFAAA: /*0x593094*/
        v10 = *(_DWORD *)sub_592F20 >> 26 == 5 || *(_DWORD *)sub_592F20 >> 21 == 1697; /*0x593570*/
        HIDWORD(savedregs[0]) = -189034791; /*0x593580*/
        break;
      case 0xF4BB8ED9: /*0x593094*/
        if ( v10 ) /*0x59358c*/
          v7 = 1034683589; /*0x5935a4*/
        else
          v7 = 887822560; /*0x5935a4*/
        HIDWORD(savedregs[0]) = v7; /*0x5935ac*/
        break;
      case 0xF6D2611A: /*0x593094*/
        v13 = (unsigned int *)savedregs; /*0x5932f8*/
        v12 = (unsigned int *)__PAIR64__(HIDWORD(result), a3); /*0x59330c*/
        v11 = a3; /*0x593314*/
        savedregs[0] = a3 | 0x90BF3C6300000000LL; /*0x593320*/
        break;
      case 0xF7C81795: /*0x593094*/
        HIDWORD(savedregs[0]) = -1853203250; /*0x5933d0*/
        break;
      case 0x1672AB48: /*0x593094*/
        HIDWORD(savedregs[0]) = -1704789222; /*0x5932a8*/
        break;
      case 0x177409EE: /*0x593094*/
        if ( LODWORD(savedregs[0]) < 0x250C96C7 ) /*0x59328c*/
          v3 = -1047382706; /*0x59328c*/
        else
          v3 = 376613704; /*0x59328c*/
        HIDWORD(savedregs[0]) = v3; /*0x593294*/
        break;
      case 0x1CB48104: /*0x593094*/
        if ( v11 == 5 ) /*0x59338c*/
          v5 = -887687068; /*0x59338c*/
        else
          v5 = -137881707; /*0x59338c*/
        HIDWORD(savedregs[0]) = v5; /*0x593394*/
        break;
      case 0x25D2822F: /*0x593094*/
        if ( v11 == 3 ) /*0x5933b4*/
          v6 = 1890327524; /*0x5933b4*/
        else
          v6 = -137881707; /*0x5933b4*/
        HIDWORD(savedregs[0]) = v6; /*0x5933bc*/
        break;
      case 0x2FE485FB: /*0x593094*/
        HIDWORD(savedregs[0]) = -609265046; /*0x5934c8*/
        break;
      case 0x34EB18E0: /*0x593094*/
        HIDWORD(savedregs[0]) = -2143086268; /*0x5935c0*/
        break;
      case 0x3C3D0B70: /*0x593094*/
        if ( (v9 & 1) != 0 ) /*0x59366c*/
          v8 = 1034683589; /*0x59366c*/
        else
          v8 = -1196565817; /*0x59366c*/
        HIDWORD(savedregs[0]) = v8; /*0x593674*/
        break;
      case 0x3DAC04C5: /*0x593094*/
        HIDWORD(savedregs[0]) = -2098806298; /*0x5934fc*/
        break;
      case 0x434AF054: /*0x593094*/
        atomic_store(*v13, v12); /*0x59347c*/
        HIDWORD(savedregs[0]) = -1323710814; /*0x59348c*/
        break;
      case 0x6E30245C: /*0x593094*/
        HIDWORD(savedregs[0]) = -392234326; /*0x59353c*/
        break;
      case 0x70AC1BE4: /*0x593094*/
        HIDWORD(savedregs[0]) = -917219379; /*0x59341c*/
        break;
      default:
        HIDWORD(savedregs[0]) = -2017589339; /*0x593454*/
        break;
    }
  }
  _ReadStatusReg(TPIDR_EL0); /*0x5934d0*/
  return result; /*0x5934ec*/
}