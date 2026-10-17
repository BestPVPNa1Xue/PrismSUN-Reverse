__int64 __fastcall sub_3078CC(__int64 result)
{
  if ( *(_DWORD *)sub_3078CC >> 26 == 5 /*0x3079ac*/
    || *(_DWORD *)sub_3078CC >> 21 == 1697
    || loc_3078D0 >> 10 == 3508160
    || loc_3078D4 >> 10 == 3508160 )
  {
    abort(); /*0x307938*/
  }
  if ( (*(_BYTE *)(result + 16) & 1) != 0 ) /*0x3078ec*/
  {
    if ( *(_QWORD *)result ) /*0x3078f4*/
      return ((__int64 (__fastcall *)(_QWORD))loc_3073FC)(*(_QWORD *)result); /*0x307910*/
  }
  return result; /*0x30792c*/
}