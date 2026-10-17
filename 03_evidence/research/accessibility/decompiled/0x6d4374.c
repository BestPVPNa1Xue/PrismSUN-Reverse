// bad sp value at call has been detected, the output may be wrong!
void __fastcall sub_6D4374(__int64 a1)
{
  __int64 v2; // x0
  __int64 v3; // x0
  __int64 v4; // x0
  __int64 v5; // x20
  __int64 v6; // x25
  __int64 v7; // x0
  __int64 v8; // x0
  __int64 v9; // x1
  char v10; // w8
  bool v11; // w9
  int v12; // w10
  _QWORD savedregs[12]; // [xsp+50h] [xbp+0h] BYREF

  savedregs[11] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x6d439c*/
  if ( *(_DWORD *)sub_6D4374 >> 26 == 5 /*0x6d4990*/
    || *(_DWORD *)sub_6D4374 >> 21 == 1697
    || loc_6D4378 >> 10 == 3508160
    || loc_6D437C >> 10 == 3508160 )
  {
    _ReadStatusReg(TPIDR_EL0); /*0x6d48ec*/
    abort(); /*0x6d4900*/
  }
  savedregs[6] = &savedregs[10]; /*0x6d442c*/
  savedregs[8] = &savedregs[10]; /*0x6d4438*/
  savedregs[7] = &savedregs[10]; /*0x6d4444*/
  savedregs[9] = &savedregs[10]; /*0x6d4468*/
  sub_6DD914(a1); /*0x6d447c*/
  v2 = sub_189D50(a1); /*0x6d4488*/
  sub_6DD918(v2, v2); /*0x6d4498*/
  v3 = ((__int64 (__fastcall *)(_QWORD *))loc_6D680C)(&savedregs[10]); /*0x6d44a0*/
  savedregs[10] = sub_6DD91C(v3); /*0x6d44a8*/
  sub_B6704(&savedregs[10], (char *)savedregs[10]); /*0x6d44b4*/
  sub_B6704(&savedregs[10], &byte_34073); /*0x6d44c4*/
  sub_109F10(savedregs[10], savedregs[11], savedregs[10], savedregs[11], (__int64)&savedregs[10]); /*0x6d44e0*/
  v4 = sub_6DD920(a1); /*0x6d44ec*/
  savedregs[10] = sub_189D50(v4); /*0x6d44fc*/
  v5 = savedregs[10]; /*0x6d4500*/
  while ( (sub_191270(&savedregs[10], &savedregs[10]) & 1) != 0 ) /*0x6d4520*/
  {
    savedregs[10] = sub_191368((__int64)&savedregs[10]); /*0x6d453c*/
    v6 = sub_10A12C((__int64)&savedregs[10]); /*0x6d4548*/
    sub_19C47C(savedregs[10]); /*0x6d4550*/
    sub_D038C(savedregs[10]); /*0x6d455c*/
    sub_10A218(v6); /*0x6d456c*/
    LOBYTE(savedregs[10]) = 0; /*0x6d4574*/
    v7 = sub_6DD924((__int64)&savedregs[10]); /*0x6d457c*/
    sub_10A218(v7); /*0x6d4588*/
    sub_1913C8(&savedregs[10]); /*0x6d4598*/
  }
  v8 = sub_10A12C((__int64)&savedregs[10]); /*0x6d45c8*/
  sub_11A3BC(v8, v5); /*0x6d45d0*/
  v9 = sub_D456C(v5); /*0x6d45e0*/
  v12 = -874224922; /*0x6d45e4*/
  while ( 1 ) /*0x6d4610*/
  {
    while ( 1 ) /*0x6d45fc*/
    {
      while ( v12 == -1894599676 ) /*0x6d45fc*/
        v12 = -142280193; /*0x6d4720*/
      if ( v12 != -1846149849 ) /*0x6d4610*/
        break; /*0x6d4610*/
      v10 = ((loc_6D73E4 & 0xFC000000) != 335544320) ^ ((loc_6D73E4 & 0xFFE00000) != -736100352); /*0x6d4768*/
      v12 = 618024184; /*0x6d476c*/
    }
    if ( v12 == -1325592268 ) /*0x6d4638*/
      break; /*0x6d4638*/
    switch ( v12 ) /*0x6d4660*/
    {
      case -874224922: /*0x6d4660*/
        v12 = 338372572; /*0x6d4708*/
        break;
      case -142280193: /*0x6d4660*/
        v12 = -1846149849; /*0x6d4730*/
        break;
      case 338372572: /*0x6d4660*/
        v12 = -1894599676; /*0x6d4714*/
        break;
      case 618024184: /*0x6d4660*/
        if ( (v10 & 1) != 0 ) /*0x6d478c*/
          v12 = 1449341100; /*0x6d478c*/
        else
          v12 = 1002650834; /*0x6d478c*/
        break;
      case 634465085: /*0x6d4660*/
        v11 = (loc_6D73E8 & 0xFFFFFC00) == -702611456 || (loc_6D73EC & 0xFFFFFC00) == -702611456; /*0x6d47d8*/
        v12 = 814385766; /*0x6d47dc*/
        break;
      case 814385766: /*0x6d4660*/
        if ( v11 ) /*0x6d47f8*/
          v12 = 1449341100; /*0x6d47fc*/
        else
          v12 = -1325592268; /*0x6d47fc*/
        break;
      case 1002650834: /*0x6d4660*/
        v12 = 634465085; /*0x6d4794*/
        break;
      default:
        abort(); /*0x6d472c*/
    }
  }
  __memcpy_chk(&savedregs[10], v9, 4, 4); /*0x6d4854*/
  sub_D2AC4(v5); /*0x6d4868*/
  sub_6DD928((__int64)&savedregs[10]); /*0x6d4870*/
  _ReadStatusReg(TPIDR_EL0); /*0x6d4874*/
}