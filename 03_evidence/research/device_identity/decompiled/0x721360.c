__int64 __fastcall sub_721360(__int64 a1)
{
  __int64 result; // x0
  __int64 v2; // [xsp+20h] [xbp-10h]
  int savedregs; // [xsp+30h] [xbp+0h]
  int i; // [xsp+34h] [xbp+4h]
  __int64 savedregs_8; // [xsp+38h] [xbp+8h]

  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x721374*/
  for ( i = -1714695687; ; i = -1968779230 ) /*0x721380*/
  {
    while ( i == -1968779230 ) /*0x7213b0*/
    {
      savedregs = a1; /*0x721478*/
      v2 = a1 + 24; /*0x721484*/
      i = -1221443054; /*0x721494*/
    }
    if ( i != -1714695687 ) /*0x7213c4*/
      break; /*0x7213c4*/
  }
  result = v2; /*0x72149c*/
  _ReadStatusReg(TPIDR_EL0); /*0x7214a0*/
  return result; /*0x7214bc*/
}