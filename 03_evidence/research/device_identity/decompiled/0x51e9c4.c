// bad sp value at call has been detected, the output may be wrong!
__int64 __usercall sub_51E9C4@<X0>(__int64 a1@<X0>, __int64 a2@<X8>)
{
  _QWORD *v2; // x23
  _QWORD *v3; // x24
  __int64 v5; // x2
  _QWORD *v6; // x3
  int v7; // w8
  __int64 v8; // x0
  unsigned int v9; // w20
  __int64 v10; // x0
  __int64 v11; // x2
  __int64 result; // x0
  int v13; // w8
  _QWORD savedregs[12]; // [xsp+10h] [xbp+0h] BYREF

  savedregs[11] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x51e9ec*/
  if ( ((((((((*(_DWORD *)sub_51E9C4 >> 26 == 5) << 31 >> 31) + ((*(_DWORD *)sub_51E9C4 >> 21 == 1697) << 31 >> 31)) << 31 >> 31) /*0x51f03c*/
         - 1) << 31 >> 31)
       + ((*(_DWORD *)sub_51E9C4 >> 21 != 1697 || *(_DWORD *)sub_51E9C4 >> 26 != 5) << 31 >> 31))
      & 1) != 0
    || loc_51E9C8 >> 10 == 3508160
    || loc_51E9CC >> 10 == 3508160 )
  {
    _ReadStatusReg(TPIDR_EL0); /*0x51ef94*/
    sub_56C564(); /*0x51efa8*/
  }
  v2 = &savedregs[8]; /*0x51ea04*/
  savedregs[10] = &savedregs[10]; /*0x51ea18*/
  v3 = &savedregs[8]; /*0x51ea20*/
  v7 = ((__int64 (__fastcall *)(__int64))loc_4ECBF0)(a1); /*0x51ea64*/
  if ( v7 < 1 ) /*0x51ea6c*/
  {
    v8 = a2; /*0x51ea88*/
    if ( v7 ) /*0x51ea8c*/
    {
LABEL_41:
      result = sub_56C560(v8, LOBYTE(savedregs[10]), v5, v6); /*0x51ef30*/
      goto LABEL_42; /*0x51ef38*/
    }
    sub_56C550(&savedregs[8]); /*0x51ea94*/
    v9 = sub_56C554(a1); /*0x51eaa0*/
    v10 = ((__int64 (__fastcall *)(__int64))loc_51F454)(a1); /*0x51eaa8*/
    v11 = sub_2A86C4(v10, 1); /*0x51eabc*/
    ((void (__fastcall *)(_QWORD *, _QWORD, __int64))loc_5959C8)(&savedregs[8], v9, v11); /*0x51eacc*/
    LOBYTE(savedregs[8]) = 5; /*0x51eadc*/
    sub_596028(&savedregs[8]); /*0x51eae4*/
    sub_51F85C(a2, (__int64)&savedregs[8]); /*0x51eafc*/
    sub_4E0F04((__int64)&savedregs[8]); /*0x51eb0c*/
    result = sub_56C558(&savedregs[8]); /*0x51eb14*/
  }
  else
  {
    v8 = a2; /*0x51ea74*/
    if ( v7 < 2 ) /*0x51ea78*/
    {
      result = sub_51FC30(a2, LOBYTE(savedregs[10]), v5, v6); /*0x51eb74*/
    }
    else
    {
      if ( v7 != 2 ) /*0x51ea80*/
        goto LABEL_41; /*0x51ea80*/
      LODWORD(savedregs[10]) = sub_56C55C(a1); /*0x51eb84*/
      v13 = 1384805591; /*0x51eb88*/
      while ( 1 ) /*0x51ec3c*/
      {
        while ( 1 ) /*0x51ec14*/
        {
          while ( 1 ) /*0x51ec00*/
          {
            while ( 1 ) /*0x51ebec*/
            {
              while ( 1 ) /*0x51ebc4*/
              {
                while ( 1 ) /*0x51ebb0*/
                {
                  while ( 1 ) /*0x51eb9c*/
                  {
                    while ( v13 == -1622648339 ) /*0x51eb9c*/
                    {
                      if ( ((unsigned __int8)v2 & 1) != 0 ) /*0x51ede8*/
                        v13 = 1676428414; /*0x51ede8*/
                      else
                        v13 = 752237615; /*0x51ede8*/
                    }
                    if ( v13 != -1599234747 ) /*0x51ebb0*/
                      break; /*0x51ebb0*/
                    v13 = -90084416; /*0x51ed2c*/
                  }
                  if ( v13 != -1109993413 ) /*0x51ebc4*/
                    break; /*0x51ebc4*/
                  if ( ((unsigned __int8)v3 & 1) != 0 ) /*0x51ee58*/
                    v13 = 1676428414; /*0x51ee58*/
                  else
                    v13 = 843499874; /*0x51ee58*/
                }
                if ( v13 != -596344110 ) /*0x51ebec*/
                  break; /*0x51ebec*/
                LOBYTE(v2) = ((loc_4D2C50 & 0xFC000000) == 335544320) ^ ((loc_4D2C50 & 0xFFE00000) == -736100352); /*0x51edc4*/
                v13 = -1622648339; /*0x51edc8*/
              }
              if ( v13 != -451132720 ) /*0x51ec00*/
                break; /*0x51ec00*/
              LOBYTE(v3) = (loc_4D2C54 & 0xFFFFFC00) == -702611456 || (loc_4D2C58 & 0xFFFFFC00) == -702611456; /*0x51ee34*/
              v13 = -1109993413; /*0x51ee38*/
            }
            if ( v13 != -428964150 ) /*0x51ec14*/
              break; /*0x51ec14*/
            __memcpy_chk(&savedregs[10], &savedregs[10], 4, 4); /*0x51ed60*/
            v13 = 206761903; /*0x51ed64*/
          }
          if ( v13 != -90084416 ) /*0x51ec3c*/
            break; /*0x51ec3c*/
          v13 = 1632231929; /*0x51ed38*/
        }
        if ( v13 == 206761903 ) /*0x51ec64*/
          break; /*0x51ec64*/
        switch ( v13 ) /*0x51eca0*/
        {
          case 752237615: /*0x51eca0*/
            v13 = -451132720; /*0x51edf0*/
            break;
          case 843499874: /*0x51eca0*/
            v13 = -428964150; /*0x51ed44*/
            break;
          case 1104072194: /*0x51eca0*/
            abort(); /*0x51ed7c*/
          case 1384805591: /*0x51eca0*/
            v13 = -1599234747; /*0x51ed20*/
            break;
          case 1632231929: /*0x51eca0*/
            v13 = -596344110; /*0x51ed8c*/
            break;
          default:
            v13 = 1104072194; /*0x51ed70*/
            break;
        }
      }
      LOBYTE(savedregs[8]) = 6; /*0x51eee4*/
      sub_1B5FCC(&savedregs[9], &savedregs[10], 4); /*0x51eef4*/
      sub_51F85C(a2, (__int64)&savedregs[8]); /*0x51ef00*/
      result = sub_4E0F04((__int64)&savedregs[8]); /*0x51ef10*/
    }
  }
LABEL_42:
  _ReadStatusReg(TPIDR_EL0); /*0x51ef44*/
  return result; /*0x51ef74*/
}