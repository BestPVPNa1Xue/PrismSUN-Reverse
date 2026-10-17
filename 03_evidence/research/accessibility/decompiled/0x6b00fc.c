__int64 __usercall sub_6B00FC@<X0>(__int64 result@<X0>, __int64 a2@<X1>, __int64 a3@<X8>)
{
  unsigned int v3; // w19
  __int64 v4; // x20
  _DWORD *v5; // x21
  _QWORD savedregs[4]; // [xsp+50h] [xbp+20h] BYREF
  int v7; // [xsp+70h] [xbp+40h]

  savedregs[3] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x6b011c*/
  HIDWORD(savedregs[2]) = 851433620; /*0x6b0128*/
  savedregs[1] = (char *)&savedregs[2] + 4; /*0x6b0130*/
  while ( 1 ) /*0x6b01f8*/
  {
    while ( HIDWORD(savedregs[2]) == -347197698 ) /*0x6b01f8*/
      HIDWORD(savedregs[2]) = -278474408; /*0x6b0404*/
    if ( HIDWORD(savedregs[2]) == -278474408 ) /*0x6b0220*/
      break; /*0x6b0220*/
    if ( HIDWORD(savedregs[2]) == 818243131 ) /*0x6b0270*/
    {
      HIDWORD(savedregs[2]) = -347197698; /*0x6b03f0*/
    }
    else
    {
      v7 = a2; /*0x6b0318*/
      v3 = result; /*0x6b0320*/
      v4 = a2; /*0x6b0328*/
      v5 = (_DWORD *)a3; /*0x6b032c*/
      sub_635514(a3); /*0x6b0330*/
      a3 = (__int64)v5; /*0x6b0334*/
      result = v3; /*0x6b0338*/
      a2 = v4; /*0x6b033c*/
      *v5 = 2; /*0x6b0344*/
      v5[4] = v7; /*0x6b034c*/
      LOBYTE(savedregs[2]) = 1; /*0x6b0358*/
      HIDWORD(savedregs[2]) = 818243131; /*0x6b0380*/
    }
  }
  _ReadStatusReg(TPIDR_EL0); /*0x6b040c*/
  return result; /*0x6b0434*/
}