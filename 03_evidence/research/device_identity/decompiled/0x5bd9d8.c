__int64 __fastcall sub_5BD9D8(
        __int64 a1,
        __int64 a2,
        __int64 a3,
        __int64 a4,
        int a5,
        __int64 a6,
        __int64 a7,
        __int64 a8,
        __int64 a9)
{
  __int64 v9; // x19
  __int64 v10; // x20
  __int64 v11; // x21
  __int64 v12; // x22
  int v13; // w23
  char v14; // w0
  char v15; // w8
  int v16; // w8
  __int64 result; // x0
  int v18; // [xsp+5Ch] [xbp-14h]
  __int64 v19; // [xsp+60h] [xbp-10h]
  __int64 v20; // [xsp+68h] [xbp-8h]
  __int64 v21; // [xsp+70h] [xbp+0h]
  __int64 v22; // [xsp+78h] [xbp+8h]
  __int64 v23; // [xsp+88h] [xbp+18h]
  _QWORD savedregs[6]; // [xsp+90h] [xbp+20h] BYREF

  savedregs[5] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x5bd9fc*/
  HIDWORD(savedregs[4]) = -1308847566; /*0x5bda08*/
  savedregs[3] = (char *)&savedregs[4] + 4; /*0x5bda10*/
  while ( 1 ) /*0x5bdac4*/
  {
    while ( 1 ) /*0x5bdab0*/
    {
      while ( 1 ) /*0x5bda88*/
      {
        while ( 1 ) /*0x5bda60*/
        {
          while ( 1 ) /*0x5bda38*/
          {
            while ( HIDWORD(savedregs[4]) == -1561044436 ) /*0x5bda38*/
            {
              if ( (savedregs[0] & 0x100000000000000LL) != 0 ) /*0x5bdd00*/
                v16 = -807965510; /*0x5bdd00*/
              else
                v16 = 1377801414; /*0x5bdd00*/
              HIDWORD(savedregs[4]) = v16; /*0x5bdd08*/
            }
            if ( HIDWORD(savedregs[4]) != -1363504837 ) /*0x5bda60*/
              break; /*0x5bda60*/
            savedregs[2] = &a9; /*0x5bdc1c*/
            savedregs[1] = &a9; /*0x5bdc34*/
            savedregs[5] = a2; /*0x5bdc44*/
            savedregs[4] = a3; /*0x5bdc4c*/
            a9 = a4; /*0x5bdc54*/
            LOBYTE(savedregs[4]) = a5; /*0x5bdc58*/
            v9 = a1; /*0x5bdc74*/
            v10 = a2; /*0x5bdc7c*/
            v11 = a3; /*0x5bdc84*/
            v12 = a4; /*0x5bdc8c*/
            v13 = a5; /*0x5bdc94*/
            a9 = ((__int64 (__fastcall *)(_QWORD, __int64, _QWORD, _QWORD))loc_5C2E14)( /*0x5bdca0*/
                   savedregs[4],
                   a2,
                   savedregs[4],
                   (unsigned __int8)a5);
            v14 = sub_241A20(a9); /*0x5bdcac*/
            a2 = v10; /*0x5bdcb0*/
            a3 = v11; /*0x5bdcb4*/
            a4 = v12; /*0x5bdcb8*/
            a5 = v13; /*0x5bdcbc*/
            v15 = v14; /*0x5bdcc0*/
            a1 = v9; /*0x5bdcc4*/
            HIBYTE(savedregs[0]) = v15 & 1; /*0x5bdccc*/
            HIDWORD(savedregs[4]) = -1561044436; /*0x5bdcdc*/
          }
          if ( HIDWORD(savedregs[4]) != -1308847566 ) /*0x5bda88*/
            break; /*0x5bda88*/
          HIDWORD(savedregs[4]) = -1363504837; /*0x5bdbf4*/
        }
        if ( HIDWORD(savedregs[4]) != -1017600328 ) /*0x5bdab0*/
          break; /*0x5bdab0*/
        v23 = *(_QWORD *)savedregs[1]; /*0x5bddc0*/
        HIDWORD(savedregs[4]) = 384154765; /*0x5bddd0*/
      }
      if ( HIDWORD(savedregs[4]) != -807965510 ) /*0x5bdac4*/
        break; /*0x5bdac4*/
      HIDWORD(savedregs[4]) = -1017600328; /*0x5bddb0*/
    }
    v22 = a1; /*0x5bdb30*/
    v20 = a2; /*0x5bdb34*/
    v21 = a3; /*0x5bdb38*/
    v19 = a4; /*0x5bdb3c*/
    v18 = a5; /*0x5bdb40*/
    if ( HIDWORD(savedregs[4]) == 384154765 ) /*0x5bdb50*/
      break; /*0x5bdb50*/
    if ( HIDWORD(savedregs[4]) == 623724701 ) /*0x5bdb64*/
    {
      (*(void (__fastcall **)(_QWORD, _QWORD))(**(_QWORD **)savedregs[1] + 72LL))( /*0x5bdd50*/
        *(_QWORD *)savedregs[1],
        *(_QWORD *)savedregs[2]);
      HIDWORD(savedregs[4]) = 1538496743; /*0x5bdd60*/
      a5 = v18; /*0x5bdd64*/
      a4 = v19; /*0x5bdd68*/
      a3 = v21; /*0x5bdd6c*/
      a2 = v20; /*0x5bdd70*/
      a1 = v22; /*0x5bdd74*/
    }
    else if ( HIDWORD(savedregs[4]) == 1377801414 ) /*0x5bdba0*/
    {
      HIDWORD(savedregs[4]) = 623724701; /*0x5bdd1c*/
    }
    else
    {
      HIDWORD(savedregs[4]) = -807965510; /*0x5bdd88*/
    }
  }
  result = v23; /*0x5bddd8*/
  _ReadStatusReg(TPIDR_EL0); /*0x5bdddc*/
  return result; /*0x5bde08*/
}