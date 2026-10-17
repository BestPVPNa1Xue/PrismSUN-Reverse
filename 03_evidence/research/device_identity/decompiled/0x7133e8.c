__int64 __usercall sub_7133E8@<X0>(__int64 result@<X0>, __int64 a2@<X8>)
{
  __int64 v2; // x19
  __int64 v3; // x20
  _QWORD savedregs[4]; // [xsp+20h] [xbp+0h] BYREF

  savedregs[3] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x713400*/
  HIDWORD(savedregs[2]) = -560029350; /*0x71340c*/
  savedregs[1] = (char *)&savedregs[2] + 4; /*0x713414*/
  while ( HIDWORD(savedregs[2]) != -2010581162 ) /*0x71343c*/
  {
    if ( HIDWORD(savedregs[2]) == -929810920 ) /*0x71348c*/
    {
      LODWORD(savedregs[2]) = result; /*0x71354c*/
      v2 = a2; /*0x713550*/
      v3 = result; /*0x713558*/
      sub_713778(a2); /*0x71355c*/
      a2 = v2; /*0x713560*/
      result = v3; /*0x713564*/
      HIDWORD(savedregs[2]) = -2010581162; /*0x713574*/
    }
    else
    {
      HIDWORD(savedregs[2]) = -929810920; /*0x713530*/
    }
  }
  _ReadStatusReg(TPIDR_EL0); /*0x71357c*/
  return result; /*0x71359c*/
}