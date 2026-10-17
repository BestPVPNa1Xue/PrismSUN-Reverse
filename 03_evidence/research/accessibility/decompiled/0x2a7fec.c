__int64 sub_2A7FEC()
{
  bool v0; // zf

  v0 = *(_DWORD *)sub_2A7FEC >> 26 == 5 || (*(_DWORD *)sub_2A7FEC & 0xFFE00000) == -736100352; /*0x2a8008*/
  if ( v0 || loc_2A7FF0 >> 10 == 3508160 || (loc_2A7FF4 & 0xFFFFFC00) == 0xD61F0000 ) /*0x2a8034*/
    abort(); /*0x2a8044*/
  return sub_2A8048();
}