__int64 __fastcall sub_2A829C(char *a1)
{
  bool v1; // zf
  __int64 result; // x0
  __int64 v4; // x20
  __int64 v5; // x8

  v1 = *(_DWORD *)sub_2A829C >> 26 == 5 || (*(_DWORD *)sub_2A829C & 0xFFE00000) == -736100352; /*0x2a82c4*/
  if ( v1 || loc_2A82A0 >> 10 == 3508160 || (loc_2A82A4 & 0xFFFFFC00) == 0xD61F0000 ) /*0x2a82f0*/
    abort(); /*0x2a8354*/
  result = sub_2A708C(&off_7ABAE8); /*0x2a8300*/
  if ( result ) /*0x2a8304*/
  {
    *(_DWORD *)(result + 24) = 16; /*0x2a8314*/
    v4 = result; /*0x2a8318*/
    v5 = sub_2A69E8(a1); /*0x2a8324*/
    result = v4; /*0x2a8328*/
    *(_QWORD *)(v4 + 32) = v5; /*0x2a832c*/
    if ( !v5 ) /*0x2a8330*/
    {
      sub_2A683C(v4); /*0x2a8340*/
      return 0; /*0x2a8344*/
    }
  }
  return result; /*0x2a833c*/
}