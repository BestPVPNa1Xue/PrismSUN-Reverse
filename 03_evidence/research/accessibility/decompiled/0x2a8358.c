__int64 sub_2A8358()
{
  bool v0; // zf
  __int64 result; // x0

  v0 = *(_DWORD *)sub_2A8358 >> 26 == 5 || (*(_DWORD *)sub_2A8358 & 0xFFE00000) == -736100352; /*0x2a837c*/
  if ( v0 || loc_2A835C >> 10 == 3508160 || (loc_2A8360 & 0xFFFFFC00) == 0xD61F0000 ) /*0x2a83a8*/
    abort(); /*0x2a83cc*/
  result = sub_2A708C(&off_7ABAE8); /*0x2a83b4*/
  if ( result ) /*0x2a83b8*/
    *(_DWORD *)(result + 24) = 32; /*0x2a83c0*/
  return result; /*0x2a83c8*/
}