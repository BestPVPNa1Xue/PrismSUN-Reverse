__int64 sub_3B8C40()
{
  unsigned __int8 v0; // w8
  __int64 v1; // x19
  unsigned __int8 v3; // [xsp-30h] [xbp-30h]

  if ( *(_DWORD *)sub_3B8C40 >> 26 == 5 /*0x3b8e18*/
    || *(_DWORD *)sub_3B8C40 >> 21 == 1697
    || loc_3B8C44 >> 10 == 3508160
    || loc_3B8C48 >> 10 == 3508160 )
  {
    abort(); /*0x3b8d8c*/
  }
  v0 = atomic_load((unsigned __int8 *)&MEMORY[0x7D0810]); /*0x3b8c78*/
  if ( ((v0 ^ 0xFE) & v0) == 0 && (unsigned int)sub_7699C4(&MEMORY[0x7D0810]) ) /*0x3b8cac*/
  {
    v1 = sub_783C68(632); /*0x3b8cd0*/
    sub_40593C(v1, v3); /*0x3b8ce0*/
    sub_3D7DD0(&MEMORY[0x7D0808], v1); /*0x3b8cf8*/
    __cxa_atexit((void (*)(void *))&loc_3D7F10, &MEMORY[0x7D0808], &off_78EC70); /*0x3b8d14*/
    sub_405940(&MEMORY[0x7D0810]); /*0x3b8d20*/
  }
  return ((__int64 (__fastcall *)(void *))sub_3D832C)(&MEMORY[0x7D0808]); /*0x3b8d48*/
}