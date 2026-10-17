__int64 __usercall sub_2E5024@<X0>(__int64 a1@<X0>, __int64 a2@<X1>, __int64 a3@<X8>)
{
  __int64 v5; // [xsp-40h] [xbp-40h]

  if ( *(_DWORD *)sub_2E5024 >> 26 == 5 /*0x2e524c*/
    || *(_DWORD *)sub_2E5024 >> 21 == 1697
    || ((((((loc_2E5028 >> 10 == 3508160) << 31 >> 31)
         + (((loc_2E5028 >> 10 == 3508160) ^ (loc_2E502C >> 10 == 3508160)) << 31 >> 31)) << 31 >> 31)
       - (((loc_2E5028 >> 10 == 3508160) & (unsigned __int8)(loc_2E502C >> 10 != 3508160)) << 31 >> 31))
      & 1) != 0 )
  {
    sub_30550C(); /*0x2e51b0*/
  }
  if ( !a2 ) /*0x2e50a4*/
    return sub_F7768(a3); /*0x2e50b4*/
  v5 = sub_3054A4(a1, a2, 0); /*0x2e50d0*/
  if ( !v5 ) /*0x2e50e4*/
    return sub_F7768(a3); /*0x2e50f0*/
  sub_3054A8(a3, v5); /*0x2e510c*/
  return ((__int64 (__fastcall *)(__int64, __int64, __int64))loc_2E579C)(a1, a2, v5); /*0x2e51a0*/
}