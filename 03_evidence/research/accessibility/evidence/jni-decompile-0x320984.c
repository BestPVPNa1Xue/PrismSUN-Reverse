__int64 __fastcall sub_320984(__int64 a1, __int64 a2, __int64 a3, __int64 a4)
{
  __int64 result; // x0
  __int64 savedregs_8; // [xsp+28h] [xbp+8h]

  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x320998*/
  result = (*(__int64 (__fastcall **)(__int64, __int64, __int64, __int64))(*(_QWORD *)a3 + 1152LL))(a3, a3, a3, a4); /*0x320b04*/
  _ReadStatusReg(TPIDR_EL0); /*0x320b08*/
  return result; /*0x320b24*/
}