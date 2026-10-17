__int64 __fastcall sub_71C4D8(__int64 result)
{
  __int64 v1; // x19
  int v2; // w8
  int v3; // w8
  int v4; // w8
  bool v5; // [xsp+2Fh] [xbp+Fh]
  unsigned int v6; // [xsp+30h] [xbp+10h]
  int v7; // [xsp+34h] [xbp+14h]

  v1 = result; /*0x71c4e8*/
  _ReadStatusReg(TPIDR_EL0); /*0x71c4ec*/
  v6 = 1926439100; /*0x71c500*/
  v7 = 1010191734; /*0x71c50c*/
  while ( 1 ) /*0x71c5b4*/
  {
    while ( 1 ) /*0x71c5a0*/
    {
      while ( 1 ) /*0x71c58c*/
      {
        while ( 1 ) /*0x71c578*/
        {
          while ( 1 ) /*0x71c550*/
          {
            while ( 1 ) /*0x71c530*/
            {
              if ( v7 == -1514985429 ) /*0x71c53c*/
                JUMPOUT(0x71C858); /*0x71c858*/
              if ( v7 != -1424420178 ) /*0x71c550*/
                break; /*0x71c550*/
              v7 = -1163908168; /*0x71c778*/
            }
            if ( v7 != -1163908168 ) /*0x71c578*/
              break; /*0x71c578*/
            v5 = *(_DWORD *)sub_71C4D8 >> 26 == 5 || *(_DWORD *)sub_71C4D8 >> 21 == 1697; /*0x71c7ac*/
            v7 = 321563946; /*0x71c7bc*/
          }
          if ( v7 != -1134149872 ) /*0x71c58c*/
            break; /*0x71c58c*/
          if ( loc_71C4DC >> 10 == 3508160 || loc_71C4E0 >> 10 == 3508160 ) /*0x71c844*/
            v4 = 1863824774; /*0x71c848*/
          else
            v4 = -281680869; /*0x71c848*/
          v7 = v4; /*0x71c850*/
        }
        if ( v7 != -987131092 ) /*0x71c5a0*/
          break; /*0x71c5a0*/
        v6 = v1; /*0x71c6e8*/
        result = sub_74539C(v1); /*0x71c6f0*/
        v7 = -48353371; /*0x71c700*/
      }
      if ( v7 != -281680869 ) /*0x71c5b4*/
        break; /*0x71c5b4*/
      v7 = -987131092; /*0x71c6d8*/
    }
    if ( v7 == -48353371 ) /*0x71c5c8*/
      break; /*0x71c5c8*/
    switch ( v7 ) /*0x71c5f0*/
    {
      case 87019454: /*0x71c5f0*/
        v7 = 1178634598; /*0x71c6b0*/
        break;
      case 321563946: /*0x71c5f0*/
        if ( v5 ) /*0x71c7c8*/
          v3 = 1863824774; /*0x71c7e0*/
        else
          v3 = -1134149872; /*0x71c7e0*/
        v7 = v3; /*0x71c7e8*/
        break;
      case 1010191734: /*0x71c5f0*/
        if ( v6 >= 0xDA1162EE ) /*0x71c694*/
          v2 = -1514985429; /*0x71c694*/
        else
          v2 = 87019454; /*0x71c694*/
        v7 = v2; /*0x71c69c*/
        break;
      case 1178634598: /*0x71c5f0*/
        v7 = -1424420178; /*0x71c6c4*/
        break;
      case 1863824774: /*0x71c5f0*/
        v7 = 2007175255; /*0x71c738*/
        break;
      default:
        _ReadStatusReg(TPIDR_EL0); /*0x71c740*/
        sub_725B64(); /*0x71c754*/
    }
  }
  _ReadStatusReg(TPIDR_EL0); /*0x71c708*/
  return result; /*0x71c728*/
}