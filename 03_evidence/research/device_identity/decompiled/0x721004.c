__int64 __fastcall sub_721004(__int64 a1)
{
  __int64 result; // x0
  __int64 v2; // [xsp+20h] [xbp-10h]
  int savedregs; // [xsp+30h] [xbp+0h]
  int i; // [xsp+34h] [xbp+4h]
  __int64 savedregs_8; // [xsp+38h] [xbp+8h]

  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x721018*/
  for ( i = -330791944; ; i = -1874235550 ) /*0x721024*/
  {
    while ( i == -1874235550 ) /*0x721054*/
    {
      savedregs = a1; /*0x721158*/
      v2 = a1; /*0x721160*/
      i = -827447437; /*0x721170*/
    }
    if ( i == -827447437 ) /*0x7210b8*/
      break; /*0x7210b8*/
  }
  result = v2; /*0x721178*/
  _ReadStatusReg(TPIDR_EL0); /*0x72117c*/
  return result; /*0x721198*/
}