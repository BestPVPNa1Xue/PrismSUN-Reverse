__int64 __fastcall sub_5B77D8(__int64 result, __int64 a2, __int64 a3, int a4)
{
  __int64 v4; // x24
  __int64 v5; // x21
  __int64 v6; // x19
  int v7; // w22
  __int64 v8; // x20
  _QWORD savedregs[8]; // [xsp+20h] [xbp+0h] BYREF

  savedregs[7] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x5b77f8*/
  HIDWORD(savedregs[6]) = 1448042090; /*0x5b7804*/
  savedregs[5] = (char *)&savedregs[6] + 4; /*0x5b780c*/
  while ( HIDWORD(savedregs[6]) != -1808217076 ) /*0x5b7820*/
  {
    if ( HIDWORD(savedregs[6]) == -216074490 ) /*0x5b78c0*/
    {
      LOWORD(savedregs[6]) = a4; /*0x5b7998*/
      v4 = a3; /*0x5b799c*/
      v5 = result; /*0x5b79a4*/
      v6 = a2; /*0x5b79ac*/
      v7 = a4; /*0x5b79b4*/
      v8 = a3; /*0x5b79b8*/
      sub_5B7CD0(a3 + 568, a2); /*0x5b79bc*/
      sub_5B7CD4(v4 + 592, v8); /*0x5b79c8*/
      a2 = v6; /*0x5b79cc*/
      a3 = v8; /*0x5b79d0*/
      a4 = v7; /*0x5b79d4*/
      result = v5; /*0x5b79d8*/
      *(_WORD *)(v4 + 616) = savedregs[6]; /*0x5b79e0*/
      *(_QWORD *)(v4 + 624) = 0; /*0x5b79e4*/
      HIDWORD(savedregs[6]) = -1808217076; /*0x5b79f4*/
    }
    else
    {
      HIDWORD(savedregs[6]) = -216074490; /*0x5b7964*/
    }
  }
  _ReadStatusReg(TPIDR_EL0); /*0x5b79fc*/
  return result; /*0x5b7a24*/
}