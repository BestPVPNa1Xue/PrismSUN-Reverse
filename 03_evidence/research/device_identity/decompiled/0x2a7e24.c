__int64 __fastcall sub_2A7E24(__int64 result)
{
  bool v1; // zf
  _QWORD *v2; // x8

  v1 = *(_DWORD *)sub_2A7E24 >> 26 == 5 || (*(_DWORD *)sub_2A7E24 & 0xFFE00000) == -736100352; /*0x2a7e48*/
  if ( v1 || loc_2A7E28 >> 10 == 3508160 || (loc_2A7E2C & 0xFFFFFC00) == 0xD61F0000 ) /*0x2a7e74*/
    abort(); /*0x2a7e98*/
  if ( result ) /*0x2a7e78*/
  {
    v2 = (_QWORD *)(result + 16); /*0x2a7e7c*/
    LODWORD(result) = -1; /*0x2a7e80*/
    do /*0x2a7e8c*/
    {
      v2 = (_QWORD *)*v2; /*0x2a7e84*/
      result = (unsigned int)(result + 1); /*0x2a7e88*/
    }
    while ( v2 ); /*0x2a7e8c*/
  }
  return result; /*0x2a7e94*/
}