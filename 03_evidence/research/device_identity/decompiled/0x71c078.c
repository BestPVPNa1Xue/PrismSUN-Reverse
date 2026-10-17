void sub_71C078()
{
  _ReadStatusReg(TPIDR_EL0); /*0x71c088*/
  JUMPOUT(0x71C108); /*0x71c108*/
}