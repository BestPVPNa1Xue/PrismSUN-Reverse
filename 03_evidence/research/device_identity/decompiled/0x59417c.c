__int64 __fastcall sub_59417C(__int64 a1)
{
  int v1; // w14
  __int64 v2; // x23
  int v3; // w8
  __int64 result; // x0
  int v5; // w8
  int v6; // w8
  bool v7; // [xsp+26h] [xbp-Ah]
  char v8; // [xsp+27h] [xbp-9h]
  __int64 v9; // [xsp+28h] [xbp-8h]
  __int64 savedregs; // [xsp+30h] [xbp+0h]
  __int64 savedregs_8; // [xsp+38h] [xbp+8h]

  savedregs_8 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x594190*/
  savedregs = 0x4A38A2FC00000000LL; /*0x594194*/
  while ( 1 ) /*0x594234*/
  {
    while ( 1 ) /*0x594220*/
    {
      while ( 1 ) /*0x59420c*/
      {
        while ( 1 ) /*0x5941e4*/
        {
          while ( 1 ) /*0x5941d0*/
          {
            while ( HIDWORD(savedregs) == -1699953854 ) /*0x5941d0*/
            {
              v7 = loc_594180 >> 10 == 3508160 || loc_594184 >> 10 == 3508160; /*0x5944c4*/
              HIDWORD(savedregs) = -477483271; /*0x5944d4*/
            }
            if ( HIDWORD(savedregs) != -1206029703 ) /*0x5941e4*/
              break; /*0x5941e4*/
            if ( (v8 & 1) != 0 ) /*0x594458*/
              v5 = 2050609444; /*0x594458*/
            else
              v5 = 1060112261; /*0x594458*/
            HIDWORD(savedregs) = v5; /*0x594460*/
          }
          if ( HIDWORD(savedregs) != -477483271 ) /*0x59420c*/
            break; /*0x59420c*/
          if ( v7 ) /*0x5944e0*/
            v6 = 2050609444; /*0x5944f8*/
          else
            v6 = 1391972007; /*0x5944f8*/
          HIDWORD(savedregs) = v6; /*0x594500*/
        }
        if ( HIDWORD(savedregs) != -358256298 ) /*0x594220*/
          break; /*0x594220*/
        HIDWORD(savedregs) = 834654795; /*0x594344*/
      }
      if ( HIDWORD(savedregs) != 834654795 ) /*0x594234*/
        break; /*0x594234*/
      HIDWORD(savedregs) = 1494756723; /*0x594358*/
    }
    if ( HIDWORD(savedregs) == 850401712 ) /*0x594248*/
    {
      if ( (v1 & 0x10000000) != 0 ) /*0x594508*/
      {
        atomic_load_explicit((atomic_uint *volatile)(v2 - 3), memory_order_acquire); /*0x59450c*/
        JUMPOUT(0x594510); /*0x594510*/
      }
      JUMPOUT(0x58F8B0); /*0x58f8b0*/
    }
    if ( HIDWORD(savedregs) == 984649039 ) /*0x59425c*/
      break; /*0x59425c*/
    switch ( HIDWORD(savedregs) ) /*0x594270*/
    {
      case 0x3F300785: /*0x594270*/
        HIDWORD(savedregs) = -1699953854; /*0x594474*/
        break;
      case 0x4A38A2FC: /*0x594270*/
        if ( (unsigned int)savedregs < 0xCB7EFC2D ) /*0x594328*/
          v3 = -358256298; /*0x594328*/
        else
          v3 = 850401712; /*0x594328*/
        HIDWORD(savedregs) = v3; /*0x594330*/
        break;
      case 0x52F7CEA7: /*0x594270*/
        HIDWORD(savedregs) = 1690556574; /*0x59436c*/
        break;
      case 0x566D7347: /*0x594270*/
        v8 = (*(_DWORD *)sub_59417C >> 26 == 5 && *(_DWORD *)sub_59417C >> 21 == 1697) /*0x594424*/
           | (*(_DWORD *)sub_59417C >> 26 == 5) ^ (*(_DWORD *)sub_59417C >> 21 == 1697);
        HIDWORD(savedregs) = -1206029703; /*0x594434*/
        break;
      case 0x59182D73: /*0x594270*/
        HIDWORD(savedregs) = 1450013511; /*0x5943e8*/
        break;
      case 0x64C3D89E: /*0x594270*/
        savedregs = (unsigned int)a1 | 0x3AB08D4F00000000LL; /*0x59437c*/
        v9 = a1 + 568; /*0x594388*/
        break;
      default:
        _ReadStatusReg(TPIDR_EL0); /*0x5943c4*/
        sub_5A7998(); /*0x5943d8*/
    }
  }
  result = v9; /*0x5943a0*/
  _ReadStatusReg(TPIDR_EL0); /*0x5943a4*/
  return result; /*0x5943c0*/
}