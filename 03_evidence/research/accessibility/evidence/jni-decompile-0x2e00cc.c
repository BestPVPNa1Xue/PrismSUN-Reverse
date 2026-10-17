__int64 __fastcall sub_2E00CC(__int64 a1, __int64 a2, __int64 a3, __int64 a4)
{
  int v4; // w8
  __int64 v5; // x19
  __int64 v6; // x20
  __int64 v7; // x21
  __int64 v8; // x22
  __int64 v9; // x0
  __int64 v10; // x8
  __int64 result; // x0
  int v12; // w8
  int v13; // w8
  _QWORD savedregs[6]; // [xsp+30h] [xbp+0h] BYREF

  savedregs[5] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x2e00e8*/
  savedregs[4] = 0x9C1AB430FB406384LL; /*0x2e00f4*/
  savedregs[1] = (char *)&savedregs[4] + 4; /*0x2e0108*/
  while ( 1 ) /*0x2e016c*/
  {
    while ( 1 ) /*0x2e0158*/
    {
      while ( 1 ) /*0x2e010c*/
      {
        if ( HIDWORD(savedregs[4]) == -1864267215 ) /*0x2e011c*/
        {
          _ReadStatusReg(TPIDR_EL0); /*0x2e0388*/
          abort(); /*0x2e039c*/
        }
        if ( HIDWORD(savedregs[4]) != -1734279768 ) /*0x2e0158*/
          break; /*0x2e0158*/
        HIDWORD(savedregs[4]) = -164291536; /*0x2e02a4*/
      }
      if ( HIDWORD(savedregs[4]) != -1675971536 ) /*0x2e016c*/
        break; /*0x2e016c*/
      if ( LODWORD(savedregs[4]) == 523073458 ) /*0x2e0288*/
        v4 = 1275946712; /*0x2e0288*/
      else
        v4 = -1734279768; /*0x2e0288*/
      HIDWORD(savedregs[4]) = v4; /*0x2e0290*/
    }
    if ( HIDWORD(savedregs[4]) == -1597294109 ) /*0x2e0180*/
      break; /*0x2e0180*/
    switch ( HIDWORD(savedregs[4]) ) /*0x2e01a8*/
    {
      case 0xD2CF0AA3: /*0x2e01a8*/
        BYTE6(savedregs[2]) = loc_2E00D0 >> 10 == 3508160 || loc_2E00D4 >> 10 == 3508160; /*0x2e04a4*/
        HIDWORD(savedregs[4]) = -505115701; /*0x2e04b4*/
        break;
      case 0xD582B699: /*0x2e01a8*/
        HIDWORD(savedregs[4]) = 1405801939; /*0x2e02cc*/
        break;
      case 0xE1E48BCB: /*0x2e01a8*/
        if ( (savedregs[2] & 0x1000000000000LL) != 0 ) /*0x2e04d8*/
          v13 = -1864267215; /*0x2e04d8*/
        else
          v13 = -712853863; /*0x2e04d8*/
        HIDWORD(savedregs[4]) = v13; /*0x2e04e0*/
        break;
      case 0xE43B40F2: /*0x2e01a8*/
        HIDWORD(savedregs[4]) = -758183261; /*0x2e0454*/
        break;
      case 0xF6351C30: /*0x2e01a8*/
        HIDWORD(savedregs[4]) = 700916445; /*0x2e02b8*/
        break;
      case 0x1C77B758: /*0x2e01a8*/
        if ( (savedregs[2] & 0x100000000000000LL) != 0 ) /*0x2e0438*/
          v12 = -1864267215; /*0x2e0438*/
        else
          v12 = -465878798; /*0x2e0438*/
        HIDWORD(savedregs[4]) = v12; /*0x2e0440*/
        break;
      case 0x25D38FF7: /*0x2e01a8*/
        HIBYTE(savedregs[2]) = (((((((*(_DWORD *)sub_2E00CC >> 26 == 5) << 31 >> 31) /*0x2e0404*/
                                  + ((*(_DWORD *)sub_2E00CC >> 21 == 1697) << 31 >> 31)) << 31 >> 31)
                                - 1) << 31 >> 31)
                              + ((*(_DWORD *)sub_2E00CC >> 21 != 1697 || *(_DWORD *)sub_2E00CC >> 26 != 5) << 31 >> 31))
                             & 1;
        HIDWORD(savedregs[4]) = 477607768; /*0x2e0414*/
        break;
      case 0x29C722DD: /*0x2e01a8*/
        HIDWORD(savedregs[4]) = 634621943; /*0x2e03ac*/
        break;
      case 0x4C0D66D8: /*0x2e01a8*/
        JUMPOUT(0x2E04E8); /*0x2e04e8*/
      default:
        v5 = a1; /*0x2e02f4*/
        v6 = a2; /*0x2e02fc*/
        v7 = a3; /*0x2e0304*/
        v8 = a4; /*0x2e030c*/
        savedregs[4] = a4; /*0x2e0310*/
        v9 = (*(__int64 (__fastcall **)(__int64, __int64, __int64, __int64))(*(_QWORD *)a3 + 904LL))(a3, a3, a3, a4); /*0x2e032c*/
        a2 = v6; /*0x2e0330*/
        a3 = v7; /*0x2e0334*/
        a4 = v8; /*0x2e0338*/
        v10 = v9; /*0x2e033c*/
        a1 = v5; /*0x2e0340*/
        savedregs[3] = v10; /*0x2e0344*/
        HIDWORD(savedregs[4]) = -1597294109; /*0x2e0354*/
        break;
    }
  }
  result = savedregs[3]; /*0x2e035c*/
  _ReadStatusReg(TPIDR_EL0); /*0x2e0360*/
  return result; /*0x2e0384*/
}