__int64 __fastcall sub_417DD0(__int64 result, char a2, unsigned int a3)
{
  __int64 v5; // x21
  unsigned int savedregs; // [xsp+40h] [xbp+20h]
  int savedregs_4; // [xsp+44h] [xbp+24h]
  __int64 savedregs_8; // [xsp+48h] [xbp+28h]
  __int64 v9; // [xsp+50h] [xbp+30h]

  v5 = result; /*0x417dec*/
  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x417df8*/
  savedregs_4 = 403875192; /*0x417e04*/
  while ( savedregs_4 != -2044044019 ) /*0x417e20*/
  {
    if ( savedregs_4 == 403875192 ) /*0x417e84*/
    {
      savedregs_4 = 1300841473; /*0x417f28*/
    }
    else
    {
      v9 = v5; /*0x417f48*/
      LOBYTE(v9) = a2 & 1; /*0x417f50*/
      savedregs = a3; /*0x417f54*/
      result = sub_4498CC(v9, a2 & 1, a3); /*0x417f68*/
      savedregs_4 = -2044044019; /*0x417f78*/
    }
  }
  _ReadStatusReg(TPIDR_EL0); /*0x417f80*/
  return result; /*0x417fa4*/
}