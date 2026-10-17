_QWORD *__fastcall sub_F6A1C(_QWORD *result, _QWORD *a2)
{
  bool v2; // zf

  v2 = *(_DWORD *)sub_F6A1C >> 26 == 5 || (*(_DWORD *)sub_F6A1C & 0xFFE00000) == -736100352; /*0xf6a40*/
  if ( v2 /*0xf6af4*/
    || loc_F6A20 >> 10 == 3508160
    || (loc_F6A24 & 0xFFFFFC00) == 0xD61F0000
    || *(_DWORD *)sub_1DA358 >> 26 == 5
    || (*(_DWORD *)sub_1DA358 & 0xFFE00000) == 0xD4200000
    || (loc_1DA35C & 0xFFFFFC00) == 0xD61F0000
    || (loc_1DA360 & 0xFFFFFC00) == 0xD61F0000
    || *(_DWORD *)sub_1DA40C >> 26 == 5
    || (*(_DWORD *)sub_1DA40C & 0xFFE00000) == 0xD4200000
    || (loc_1DA410 & 0xFFFFFC00) == 0xD61F0000
    || (loc_1DA414 & 0xFFFFFC00) == 0xD61F0000 )
  {
    abort(); /*0xf6b10*/
  }
  if ( *a2 < *result ) /*0xf6b04*/
    return a2; /*0xf6b04*/
  return result; /*0xf6b0c*/
}