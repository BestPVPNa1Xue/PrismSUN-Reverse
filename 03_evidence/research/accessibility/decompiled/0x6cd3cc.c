__int64 __fastcall sub_6CD3CC(__int64 result)
{
  _QWORD *v1; // x19
  _QWORD savedregs[4]; // [xsp+20h] [xbp+0h] BYREF

  v1 = (_QWORD *)result; /*0x6cd3dc*/
  savedregs[3] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x6cd3e8*/
  HIDWORD(savedregs[2]) = 264864329; /*0x6cd3f4*/
  savedregs[1] = (char *)&savedregs[2] + 4; /*0x6cd3fc*/
  while ( 1 ) /*0x6cd410*/
  {
    while ( HIDWORD(savedregs[2]) == -1931393818 ) /*0x6cd410*/
    {
      LODWORD(savedregs[2]) = (_DWORD)v1; /*0x6cd528*/
      result = ((__int64 (__fastcall *)(_QWORD *))loc_62FC98)(v1); /*0x6cd534*/
      *v1 = &off_793E50; /*0x6cd548*/
      HIDWORD(savedregs[2]) = -506541834; /*0x6cd558*/
    }
    if ( HIDWORD(savedregs[2]) == -506541834 ) /*0x6cd474*/
      break; /*0x6cd474*/
    HIDWORD(savedregs[2]) = -1931393818; /*0x6cd518*/
  }
  _ReadStatusReg(TPIDR_EL0); /*0x6cd560*/
  return result; /*0x6cd580*/
}