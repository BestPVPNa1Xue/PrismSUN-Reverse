__int64 __fastcall sub_121FD0(__int64 *a1, _QWORD *a2)
{
  bool v2; // zf
  __int64 result; // x0

  v2 = *(_DWORD *)sub_121FD0 >> 26 == 5 || (*(_DWORD *)sub_121FD0 & 0xFFE00000) == -736100352; /*0x121ffc*/
  if ( v2 /*0x1220c8*/
    || loc_121FD4 >> 10 == 3508160
    || (loc_121FD8 & 0xFFFFFC00) == 0xD61F0000
    || (result = sub_215E64(&unk_3D77D), *a1 = result, *(_DWORD *)sub_215F50 >> 26 == 5)
    || (*(_DWORD *)sub_215F50 & 0xFFE00000) == 0xD4200000
    || (loc_215F54 & 0xFFFFFC00) == 0xD61F0000
    || (loc_215F58 & 0xFFFFFC00) == 0xD61F0000
    || *(_DWORD *)sub_D4614 >> 26 == 5
    || (*(_DWORD *)sub_D4614 & 0xFFE00000) == 0xD4200000
    || (loc_D4618 & 0xFFFFFC00) == 0xD61F0000
    || (loc_D461C & 0xFFFFFC00) == 0xD61F0000 )
  {
    abort(); /*0x1220e8*/
  }
  a1[1] = a2[1] - *a2; /*0x1220d8*/
  return result; /*0x1220e4*/
}