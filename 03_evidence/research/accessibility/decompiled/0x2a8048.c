__int64 __fastcall sub_2A8048(_QWORD *a1, _QWORD *a2)
{
  bool v2; // zf
  unsigned int v3; // w8
  __int64 v4; // x11
  _QWORD *v5; // x8

  v2 = *(_DWORD *)sub_2A8048 >> 26 == 5 || (*(_DWORD *)sub_2A8048 & 0xFFE00000) == -736100352; /*0x2a806c*/
  if ( v2 || loc_2A804C >> 10 == 3508160 || (loc_2A8050 & 0xFFFFFC00) == 0xD61F0000 ) /*0x2a8098*/
    abort(); /*0x2a8148*/
  v3 = 0; /*0x2a80a0*/
  if ( a1 == a2 || !a1 || !a2 ) /*0x2a80ac*/
    return v3; /*0x2a80ac*/
  v4 = a1[2]; /*0x2a80b0*/
  if ( v4 ) /*0x2a80b4*/
  {
    v5 = *(_QWORD **)(v4 + 8); /*0x2a80b8*/
    if ( v5 ) /*0x2a80bc*/
    {
      *v5 = a2; /*0x2a8104*/
      a2[1] = v5; /*0x2a8108*/
      v3 = 1; /*0x2a810c*/
      *(_QWORD *)(v4 + 8) = a2; /*0x2a8110*/
      return v3; /*0x2a811c*/
    }
    return 1; /*0x2a813c*/
  }
  else
  {
    a1[2] = a2; /*0x2a8120*/
    *a2 = 0; /*0x2a8128*/
    a2[1] = a2; /*0x2a8128*/
    return 1; /*0x2a812c*/
  }
}