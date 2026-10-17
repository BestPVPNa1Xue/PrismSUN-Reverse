__int64 __fastcall sub_596E90(unsigned __int8 *a1)
{
  __int64 result; // x0
  unsigned __int8 v2; // [xsp+14h] [xbp-Ch]
  int savedregs; // [xsp+20h] [xbp+0h]
  int savedregs_4; // [xsp+24h] [xbp+4h]
  __int64 savedregs_8; // [xsp+28h] [xbp+8h]

  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x596ea4*/
  savedregs_4 = -702208379; /*0x596eb0*/
  while ( savedregs_4 != -1773450272 ) /*0x596ecc*/
  {
    if ( savedregs_4 == -1505691076 ) /*0x596ee0*/
    {
      savedregs = (int)a1; /*0x597020*/
      v2 = *a1; /*0x59702c*/
      savedregs_4 = -1773450272; /*0x59703c*/
    }
    else
    {
      savedregs_4 = -1505691076; /*0x597010*/
    }
  }
  result = v2; /*0x597044*/
  _ReadStatusReg(TPIDR_EL0); /*0x597048*/
  return result; /*0x597064*/
}