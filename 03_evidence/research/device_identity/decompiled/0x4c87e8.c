__int64 __fastcall sub_4C87E8(__int64 result)
{
  __int64 v1; // x23
  _BYTE v2[32]; // [xsp-40h] [xbp-50h] BYREF
  _QWORD v3[6]; // [xsp-20h] [xbp-30h] BYREF

  v3[5] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x4c8808*/
  if ( *(_DWORD *)sub_4C87E8 >> 26 == 5 /*0x4c89b8*/
    || *(_DWORD *)sub_4C87E8 >> 21 == 1697
    || loc_4C87EC >> 10 == 3508160
    || loc_4C87F0 >> 10 == 3508160 )
  {
    _ReadStatusReg(TPIDR_EL0); /*0x4c8934*/
    sub_56B7E4(); /*0x4c8948*/
  }
  v3[2] = result; /*0x4c883c*/
  v1 = result; /*0x4c8840*/
  if ( *(_DWORD *)(result + 60) ) /*0x4c8844*/
  {
    sub_56B7D8(v3, 4, result + 60, 4); /*0x4c8874*/
    sub_56B7DC(v2, v3, 4); /*0x4c8884*/
    if ( (sub_56B7E0((__int64)&unk_7C06AC, 6u, (__int64)v2) & 1) != 0 ) /*0x4c88a8*/
      *(_DWORD *)(v1 + 60) = 0; /*0x4c88b4*/
    result = sub_74539C(v2); /*0x4c88d8*/
  }
  _ReadStatusReg(TPIDR_EL0); /*0x4c88e8*/
  return result; /*0x4c8910*/
}