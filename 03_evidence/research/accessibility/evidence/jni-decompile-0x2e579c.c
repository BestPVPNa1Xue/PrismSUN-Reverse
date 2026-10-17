__int64 __fastcall sub_2E579C(__int64 a1, __int64 a2, __int64 a3)
{
  int v5; // w8
  __int64 result; // x0
  int v7; // w8
  int v8; // w8
  bool v9; // [xsp+3Eh] [xbp+1Eh]
  bool v10; // [xsp+3Fh] [xbp+1Fh]
  unsigned __int64 savedregs; // [xsp+40h] [xbp+20h]
  __int64 savedregs_8; // [xsp+48h] [xbp+28h]

  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x2e57c4*/
  savedregs = 0x37C16DE900000000LL; /*0x2e57c8*/
  while ( 1 ) /*0x2e582c*/
  {
    while ( 1 ) /*0x2e5818*/
    {
      while ( 1 ) /*0x2e57f0*/
      {
        while ( HIDWORD(savedregs) == -2117146032 ) /*0x2e57f0*/
        {
          v9 = loc_2E57A0 >> 10 == 3508160 || loc_2E57A4 >> 10 == 3508160; /*0x2e5b18*/
          HIDWORD(savedregs) = 1566498597; /*0x2e5b28*/
        }
        if ( HIDWORD(savedregs) == -1941690865 ) /*0x2e5804*/
          JUMPOUT(0x2E5B60); /*0x2e5b60*/
        if ( HIDWORD(savedregs) != -1542481201 ) /*0x2e5818*/
          break; /*0x2e5818*/
        savedregs = (unsigned int)a3 | 0xDB20973A00000000LL; /*0x2e59c8*/
        result = (*(__int64 (__fastcall **)(__int64, __int64, __int64))(*(_QWORD *)a2 + 1360LL))(a2, a2, a3); /*0x2e59e0*/
      }
      if ( HIDWORD(savedregs) != -1375908437 ) /*0x2e582c*/
        break; /*0x2e582c*/
      HIDWORD(savedregs) = 1114020101; /*0x2e5a44*/
    }
    if ( HIDWORD(savedregs) == -618621126 ) /*0x2e5854*/
      break; /*0x2e5854*/
    switch ( HIDWORD(savedregs) ) /*0x2e587c*/
    {
      case 0x158DAF0: /*0x2e587c*/
        HIDWORD(savedregs) = -1542481201; /*0x2e59a0*/
        break;
      case 0x1B821708: /*0x2e587c*/
        if ( v10 ) /*0x2e5a94*/
          v7 = 537253156; /*0x2e5aac*/
        else
          v7 = 1135912818; /*0x2e5aac*/
        HIDWORD(savedregs) = v7; /*0x2e5ab4*/
        break;
      case 0x2005D524: /*0x2e587c*/
        _ReadStatusReg(TPIDR_EL0); /*0x2e5a20*/
        sub_305514(); /*0x2e5a34*/
      case 0x37C16DE9: /*0x2e587c*/
        if ( (unsigned int)savedregs <= 0x6DBE765A ) /*0x2e595c*/
          v5 = 1635039701; /*0x2e595c*/
        else
          v5 = -1941690865; /*0x2e595c*/
        HIDWORD(savedregs) = v5; /*0x2e5964*/
        break;
      case 0x38ABC6BA: /*0x2e587c*/
        HIDWORD(savedregs) = -1375908437; /*0x2e598c*/
        break;
      case 0x42669905: /*0x2e587c*/
        v10 = *(_DWORD *)sub_2E579C >> 26 == 5 || *(_DWORD *)sub_2E579C >> 21 == 1697; /*0x2e5a78*/
        HIDWORD(savedregs) = 461510408; /*0x2e5a88*/
        break;
      case 0x43B4A772: /*0x2e587c*/
        HIDWORD(savedregs) = -2117146032; /*0x2e5ac8*/
        break;
      case 0x5D5EDF25: /*0x2e587c*/
        if ( v9 ) /*0x2e5b34*/
          v8 = 537253156; /*0x2e5b4c*/
        else
          v8 = 22600432; /*0x2e5b4c*/
        HIDWORD(savedregs) = v8; /*0x2e5b54*/
        break;
      default:
        HIDWORD(savedregs) = 950781626; /*0x2e5978*/
        break;
    }
  }
  _ReadStatusReg(TPIDR_EL0); /*0x2e59f8*/
  return result; /*0x2e5a1c*/
}