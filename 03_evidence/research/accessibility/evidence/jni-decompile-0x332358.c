__int64 __fastcall sub_332358(
        __int64 a1,
        __int64 a2,
        __int64 a3,
        __int64 a4,
        __int64 a5,
        __int64 a6,
        __int64 a7,
        __int64 a8,
        __int64 a9,
        __int64 a10,
        __int64 a11,
        __int64 a12,
        __int64 a13)
{
  __int64 result; // x0

  _ReadStatusReg(TPIDR_EL0); /*0x33239c*/
  result = (*(unsigned int (__fastcall **)(__int64, __int64 *, __int64 *))(*(_QWORD *)a3 + 400LL))(a3, &a13, &a13); /*0x332534*/
  _ReadStatusReg(TPIDR_EL0); /*0x332538*/
  return result; /*0x332558*/
}