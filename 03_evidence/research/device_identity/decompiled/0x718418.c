void sub_718418()
{
  _QWORD savedregs[2]; // [xsp+70h] [xbp+20h]

  savedregs[1] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x718438*/
  for ( savedregs[0] = 0xD863AE6E2A3B30C9LL; HIDWORD(savedregs[0]) == -664555922; HIDWORD(savedregs[0]) = -268087441 ) /*0x718444*/
    ; /*0x7186e4*/
  JUMPOUT(0x7186EC); /*0x7186ec*/
}