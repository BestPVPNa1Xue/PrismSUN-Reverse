__int64 __fastcall sub_F7FAC(__int64 a1)
{
  bool v1; // zf

  v1 = *(_DWORD *)sub_F7FAC >> 26 == 5 || (*(_DWORD *)sub_F7FAC & 0xFFE00000) == -736100352; /*0xf7fd4*/
  if ( v1 || loc_F7FB0 >> 10 == 3508160 || (loc_F7FB4 & 0xFFFFFC00) == 0xD61F0000 ) /*0xf8000*/
    abort(); /*0xf801c*/
  sub_1DB670(); /*0xf8008*/
  return a1; /*0xf8018*/
}