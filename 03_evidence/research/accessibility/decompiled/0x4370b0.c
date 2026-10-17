__int64 __fastcall sub_4370B0(__int64 a1, int a2)
{
  int v2; // w8
  int v3; // w8
  int v4; // w8
  unsigned __int8 v5; // w8
  unsigned __int8 v6; // w8
  char v8; // [xsp+13h] [xbp-1Dh]
  int v9; // [xsp+14h] [xbp-1Ch]
  unsigned __int8 *v10; // [xsp+18h] [xbp-18h]
  unsigned __int8 *v11; // [xsp+20h] [xbp-10h]
  _QWORD savedregs[2]; // [xsp+30h] [xbp+0h] BYREF

  savedregs[1] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x4370c4*/
  HIDWORD(savedregs[0]) = 452549591; /*0x4370d0*/
  while ( 1 ) /*0x437240*/
  {
    while ( 1 ) /*0x43722c*/
    {
      while ( 1 ) /*0x4371f0*/
      {
        while ( 1 ) /*0x4371dc*/
        {
          while ( 1 ) /*0x4371c8*/
          {
            while ( 1 ) /*0x4371b4*/
            {
              while ( 1 ) /*0x4371a0*/
              {
                while ( 1 ) /*0x437164*/
                {
                  while ( 1 ) /*0x437150*/
                  {
                    while ( 1 ) /*0x437128*/
                    {
                      while ( 1 ) /*0x4370ec*/
                      {
                        while ( HIDWORD(savedregs[0]) == -2139415139 ) /*0x4370ec*/
                        {
                          v6 = atomic_load(v10); /*0x437500*/
                          *v11 = v6; /*0x437508*/
                          HIDWORD(savedregs[0]) = -395954494; /*0x437518*/
                        }
                        if ( HIDWORD(savedregs[0]) != -2000260738 ) /*0x437128*/
                          break; /*0x437128*/
                        if ( (unsigned int)(v9 - 1) > 1 ) /*0x437440*/
                          v4 = 279073412; /*0x437440*/
                        else
                          v4 = 271602109; /*0x437440*/
                        HIDWORD(savedregs[0]) = v4; /*0x437448*/
                      }
                      if ( HIDWORD(savedregs[0]) != -1664351331 ) /*0x437150*/
                        break; /*0x437150*/
                      v8 = *v11 & 1; /*0x437554*/
                      HIDWORD(savedregs[0]) = 431975056; /*0x437564*/
                    }
                    if ( HIDWORD(savedregs[0]) != -1433670016 ) /*0x437164*/
                      break; /*0x437164*/
                    *v11 = *v10; /*0x437470*/
                    HIDWORD(savedregs[0]) = -754944101; /*0x437480*/
                  }
                  if ( HIDWORD(savedregs[0]) != -760333176 ) /*0x4371a0*/
                    break; /*0x4371a0*/
                  v5 = atomic_load(v10); /*0x4374b4*/
                  *v11 = v5; /*0x4374bc*/
                  HIDWORD(savedregs[0]) = 1927365106; /*0x4374cc*/
                }
                if ( HIDWORD(savedregs[0]) != -754944101 ) /*0x4371b4*/
                  break; /*0x4371b4*/
                HIDWORD(savedregs[0]) = 2059050472; /*0x437494*/
              }
              if ( HIDWORD(savedregs[0]) != -671032368 ) /*0x4371c8*/
                break; /*0x4371c8*/
              v11 = (unsigned __int8 *)savedregs; /*0x437390*/
              v10 = (unsigned __int8 *)__PAIR64__(HIDWORD(a1), a2); /*0x4373a0*/
              v9 = a2; /*0x4373a8*/
              HIDWORD(savedregs[0]) = -506845592; /*0x4373b8*/
            }
            if ( HIDWORD(savedregs[0]) != -506845592 ) /*0x4371dc*/
              break; /*0x4371dc*/
            HIDWORD(savedregs[0]) = 1519152572; /*0x4373cc*/
          }
          if ( HIDWORD(savedregs[0]) != -395954494 ) /*0x4371f0*/
            break; /*0x4371f0*/
          HIDWORD(savedregs[0]) = 2059050472; /*0x43752c*/
        }
        if ( HIDWORD(savedregs[0]) != 271602109 ) /*0x43722c*/
          break; /*0x43722c*/
        HIDWORD(savedregs[0]) = -760333176; /*0x4374a8*/
      }
      if ( HIDWORD(savedregs[0]) != 279073412 ) /*0x437240*/
        break; /*0x437240*/
      HIDWORD(savedregs[0]) = -1433670016; /*0x43745c*/
    }
    if ( HIDWORD(savedregs[0]) == 431975056 ) /*0x437268*/
      break; /*0x437268*/
    switch ( HIDWORD(savedregs[0]) ) /*0x43727c*/
    {
      case 0x1AF95BD7: /*0x43727c*/
        HIDWORD(savedregs[0]) = -671032368; /*0x437370*/
        break;
      case 0x1F3B2CC2: /*0x43727c*/
        HIDWORD(savedregs[0]) = -2139415139; /*0x4374f4*/
        break;
      case 0x2A46EFF7: /*0x43727c*/
        if ( v9 == 5 ) /*0x437414*/
          v3 = 523971778; /*0x437414*/
        else
          v3 = 279073412; /*0x437414*/
        HIDWORD(savedregs[0]) = v3; /*0x43741c*/
        break;
      case 0x5A8C6DBC: /*0x43727c*/
        if ( v9 >= 5 ) /*0x4373ec*/
          v2 = 709292023; /*0x4373ec*/
        else
          v2 = -2000260738; /*0x4373ec*/
        HIDWORD(savedregs[0]) = v2; /*0x4373f4*/
        break;
      case 0x72E141F2: /*0x43727c*/
        HIDWORD(savedregs[0]) = 2059050472; /*0x4374e0*/
        break;
      default:
        HIDWORD(savedregs[0]) = -1664351331; /*0x437540*/
        break;
    }
  }
  _ReadStatusReg(TPIDR_EL0); /*0x437574*/
  return v8 & 1; /*0x437594*/
}