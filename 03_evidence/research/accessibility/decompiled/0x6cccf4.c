__int64 __usercall sub_6CCB14@<X0>(__int64 a1@<X8>)
{
  _QWORD *v2; // x20
  __int64 result; // x0
  int v4; // w9
  int v5; // w9
  _QWORD savedregs[4]; // [xsp+20h] [xbp+0h] BYREF

  savedregs[3] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x6ccb2c*/
  savedregs[2] = 0x623542300000001LL; /*0x6ccb34*/
  savedregs[0] = (char *)&savedregs[2] + 4; /*0x6ccb48*/
  while ( 1 ) /*0x6ccc10*/
  {
    while ( 1 ) /*0x6ccbe8*/
    {
      while ( 1 ) /*0x6ccbd4*/
      {
        while ( 1 ) /*0x6ccbc0*/
        {
          while ( 1 ) /*0x6ccbac*/
          {
            while ( 1 ) /*0x6ccb84*/
            {
              while ( 1 ) /*0x6ccb5c*/
              {
                while ( HIDWORD(savedregs[2]) == -1852494423 ) /*0x6ccb5c*/
                {
                  if ( (savedregs[1] & 0x100000000000000LL) != 0 ) /*0x6ccddc*/
                    v4 = -1433303286; /*0x6ccddc*/
                  else
                    v4 = 537591509; /*0x6ccddc*/
                  HIDWORD(savedregs[2]) = v4; /*0x6ccde4*/
                }
                if ( HIDWORD(savedregs[2]) != -1433303286 ) /*0x6ccb84*/
                  break; /*0x6ccb84*/
                HIDWORD(savedregs[2]) = 1457030163; /*0x6ccd34*/
              }
              if ( HIDWORD(savedregs[2]) != -335953658 ) /*0x6ccbac*/
                break; /*0x6ccbac*/
              HIDWORD(savedregs[2]) = 727169676; /*0x6ccd74*/
            }
            if ( HIDWORD(savedregs[2]) != 102978595 ) /*0x6ccbc0*/
              break; /*0x6ccbc0*/
            HIDWORD(savedregs[2]) = 416833724; /*0x6ccc94*/
          }
          if ( HIDWORD(savedregs[2]) != 416833724 ) /*0x6ccbd4*/
            break; /*0x6ccbd4*/
          HIDWORD(savedregs[2]) = 1715674523; /*0x6ccca8*/
        }
        if ( HIDWORD(savedregs[2]) != 537591509 ) /*0x6ccbe8*/
          break; /*0x6ccbe8*/
        if ( (loc_6CCB18 >> 10 == 3508160) ^ (loc_6CCB1C >> 10 == 3508160) /*0x6cce68*/
           | (loc_6CCB18 >> 10 == 3508160 && loc_6CCB1C >> 10 == 3508160) )
        {
          v5 = -1433303286; /*0x6cce6c*/
        }
        else
        {
          v5 = 1638949077; /*0x6cce6c*/
        }
        HIDWORD(savedregs[2]) = v5; /*0x6cce74*/
      }
      if ( HIDWORD(savedregs[2]) != 727169676 ) /*0x6ccc10*/
        break; /*0x6ccc10*/
      HIBYTE(savedregs[1]) = *(_DWORD *)sub_6CCB14 >> 26 == 5 || *(_DWORD *)sub_6CCB14 >> 21 == 1697; /*0x6ccda8*/
      HIDWORD(savedregs[2]) = -1852494423; /*0x6ccdb8*/
    }
    if ( HIDWORD(savedregs[2]) == 1457030163 ) /*0x6ccc38*/
    {
      _ReadStatusReg(TPIDR_EL0); /*0x6ccd3c*/
      abort(); /*0x6ccd50*/
    }
    if ( HIDWORD(savedregs[2]) == 1638949077 ) /*0x6ccc4c*/
      break; /*0x6ccc4c*/
    HIDWORD(savedregs[2]) = -335953658; /*0x6cccbc*/
  }
  savedregs[2] = a1; /*0x6ccccc*/
  v2 = (_QWORD *)sub_783C68(8); /*0x6cccdc*/
  memset(v2, 0, sizeof(_QWORD)); /*0x6cccec*/
  sub_6DD874(v2); /*0x6cccf4*/
  result = sub_6DD878(a1, v2); /*0x6ccd00*/
  _ReadStatusReg(TPIDR_EL0); /*0x6ccd04*/
  return result; /*0x6ccd24*/
}