__int64 __fastcall sub_2A6598(__int64 result)
{
  bool v1; // zf

  v1 = *(_DWORD *)sub_2A6598 >> 26 == 5 || (*(_DWORD *)sub_2A6598 & 0xFFE00000) == -736100352; /*0x2a65bc*/
  if ( v1 /*0x2a662c*/
    || loc_2A659C >> 10 == 3508160
    || (loc_2A65A0 & 0xFFFFFC00) == 0xD61F0000
    || *(_DWORD *)sub_2A665C >> 26 == 5
    || (*(_DWORD *)sub_2A665C & 0xFFE00000) == 0xD4200000
    || (loc_2A6660 & 0xFFFFFC00) == 0xD61F0000
    || (loc_2A6664 & 0xFFFFFC00) == 0xD61F0000 )
  {
    abort(); /*0x2a6658*/
  }
  if ( result ) /*0x2a6630*/
  {
    if ( *(_BYTE *)(result + 24) == 16 ) /*0x2a663c*/
      return *(_QWORD *)(result + 32); /*0x2a6640*/
    else
      return 0; /*0x2a664c*/
  }
  return result; /*0x2a6648*/
}