__int64 __fastcall sub_591620(__int64 result, __int64 a2, __int64 a3)
{
  int v3; // w8
  __int64 v4; // x19
  unsigned int v5; // w20
  unsigned int v6; // w21
  int v7; // w8
  int v8; // w8
  char v9; // [xsp+3Eh] [xbp+1Eh]
  char v10; // [xsp+3Fh] [xbp+1Fh]
  __int64 savedregs; // [xsp+40h] [xbp+20h]
  __int64 savedregs_8; // [xsp+48h] [xbp+28h]

  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x59163c*/
  savedregs = 0x47EDE48C6C6580C6LL; /*0x591648*/
  while ( 1 ) /*0x591710*/
  {
    while ( 1 ) /*0x5916fc*/
    {
      while ( 1 ) /*0x5916e8*/
      {
        while ( 1 ) /*0x591698*/
        {
          while ( 1 ) /*0x591684*/
          {
            while ( 1 ) /*0x591670*/
            {
              while ( HIDWORD(savedregs) == -2141036827 ) /*0x591670*/
              {
                v9 = (((((((loc_591624 >> 10 == 3508160) << 31 >> 31) + ((loc_591628 >> 10 == 3508160) << 31 >> 31)) << 31 >> 31) /*0x591a38*/
                      - 1) << 31 >> 31)
                    + ((loc_591628 >> 10 != 3508160 || loc_591624 >> 10 != 3508160) << 31 >> 31))
                   & 1;
                HIDWORD(savedregs) = 986813839; /*0x591a48*/
              }
              if ( HIDWORD(savedregs) != -2140638004 ) /*0x591684*/
                break; /*0x591684*/
              HIDWORD(savedregs) = 1288331380; /*0x591938*/
            }
            if ( HIDWORD(savedregs) != -1670711016 ) /*0x591698*/
              break; /*0x591698*/
            HIDWORD(savedregs) = 720319449; /*0x5918f8*/
          }
          if ( HIDWORD(savedregs) == -679357138 ) /*0x5916ac*/
            JUMPOUT(0x591A7C); /*0x591a7c*/
          if ( HIDWORD(savedregs) != -84059891 ) /*0x5916e8*/
            break; /*0x5916e8*/
          if ( (v10 & 1) != 0 ) /*0x5919a8*/
            v7 = -1670711016; /*0x5919a8*/
          else
            v7 = 483542911; /*0x5919a8*/
          HIDWORD(savedregs) = v7; /*0x5919b0*/
        }
        if ( HIDWORD(savedregs) != 240361218 ) /*0x5916fc*/
          break; /*0x5916fc*/
        HIDWORD(savedregs) = 2140427707; /*0x59185c*/
      }
      if ( HIDWORD(savedregs) != 414254084 ) /*0x591710*/
        break; /*0x591710*/
      HIDWORD(savedregs) = -2140638004; /*0x591848*/
    }
    if ( HIDWORD(savedregs) == 426501548 ) /*0x591724*/
      break; /*0x591724*/
    switch ( HIDWORD(savedregs) ) /*0x591738*/
    {
      case 0x1CD2477F: /*0x591738*/
        HIDWORD(savedregs) = -2141036827; /*0x5919c4*/
        break;
      case 0x2554B1FD: /*0x591738*/
        HIDWORD(savedregs) = 414254084; /*0x591834*/
        break;
      case 0x2AEF33D9: /*0x591738*/
        _ReadStatusReg(TPIDR_EL0); /*0x591900*/
        sub_593828(result, a2, a3); /*0x591914*/
      case 0x3AD1958F: /*0x591738*/
        if ( (v9 & 1) != 0 ) /*0x591a6c*/
          v8 = -1670711016; /*0x591a6c*/
        else
          v8 = 240361218; /*0x591a6c*/
        HIDWORD(savedregs) = v8; /*0x591a74*/
        break;
      case 0x47EDE48C: /*0x591738*/
        if ( (_DWORD)savedregs == 833101707 ) /*0x591818*/
          v3 = -679357138; /*0x591818*/
        else
          v3 = 626307581; /*0x591818*/
        HIDWORD(savedregs) = v3; /*0x591820*/
        break;
      case 0x4CCA6074: /*0x591738*/
        v10 = (*(_DWORD *)sub_591620 >> 26 == 5 && *(_DWORD *)sub_591620 >> 21 == 1697) /*0x591974*/
            | (*(_DWORD *)sub_591620 >> 26 == 5) ^ (*(_DWORD *)sub_591620 >> 21 == 1697);
        HIDWORD(savedregs) = -84059891; /*0x591984*/
        break;
      default:
        v4 = result; /*0x59187c*/
        v5 = a2; /*0x591884*/
        v6 = a3; /*0x59188c*/
        savedregs = (unsigned int)a3 | 0x196BE5AC00000000LL; /*0x591890*/
        sub_592F20(__PAIR64__(HIDWORD(result), a2), (unsigned int)a2, (unsigned int)a3); /*0x5918a0*/
        result = v4; /*0x5918a4*/
        a2 = v5; /*0x5918a8*/
        a3 = v6; /*0x5918ac*/
        break;
    }
  }
  _ReadStatusReg(TPIDR_EL0); /*0x5918c4*/
  return result; /*0x5918e8*/
}