__int64 __fastcall sub_5DA398(__int64 a1)
{
  int v2; // w8
  __int64 result; // x0
  int v4; // w8
  int v5; // w8
  bool savedregs_7; // [xsp+37h] [xbp+7h]
  __int64 savedregs_8; // [xsp+38h] [xbp+8h]
  unsigned __int64 savedregs_16; // [xsp+40h] [xbp+10h]
  __int64 savedregs_24; // [xsp+48h] [xbp+18h]

  savedregs_24 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x5da3b4*/
  savedregs_16 = 0xD6640D5EA23F1F2BLL; /*0x5da3c0*/
  while ( 1 ) /*0x5da460*/
  {
    while ( 1 ) /*0x5da44c*/
    {
      while ( 1 ) /*0x5da424*/
      {
        while ( 1 ) /*0x5da410*/
        {
          while ( 1 ) /*0x5da3e8*/
          {
            while ( HIDWORD(savedregs_16) == -1257444924 ) /*0x5da3e8*/
            {
              savedregs_7 = loc_5DA39C >> 10 == 3508160 || loc_5DA3A0 >> 10 == 3508160; /*0x5da700*/
              HIDWORD(savedregs_16) = 223304884; /*0x5da710*/
            }
            if ( HIDWORD(savedregs_16) != -976945811 ) /*0x5da410*/
              break; /*0x5da410*/
            savedregs_16 = (unsigned int)a1 | 0xE8AC12BC00000000LL; /*0x5da5a8*/
            ((void (__fastcall *)(__int64))loc_5F8D44)(a1); /*0x5da5b4*/
            savedregs_8 = a1; /*0x5da5b8*/
          }
          if ( HIDWORD(savedregs_16) != -867171594 ) /*0x5da424*/
            break; /*0x5da424*/
          if ( ((((((*(_DWORD *)sub_5DA398 >> 26 == 5) << 31 >> 31) /*0x5da694*/
                 + (((*(_DWORD *)sub_5DA398 >> 26 == 5) ^ (*(_DWORD *)sub_5DA398 >> 21 == 1697)) << 31 >> 31)) << 31 >> 31)
               - (((*(_DWORD *)sub_5DA398 >> 26 == 5) & (unsigned __int8)(*(_DWORD *)sub_5DA398 >> 21 != 1697)) << 31 >> 31))
              & 1) != 0 )
            v4 = 901391280; /*0x5da694*/
          else
            v4 = -666659314; /*0x5da694*/
          HIDWORD(savedregs_16) = v4; /*0x5da69c*/
        }
        if ( HIDWORD(savedregs_16) == -789430404 ) /*0x5da438*/
          JUMPOUT(0x5DA748); /*0x5da748*/
        if ( HIDWORD(savedregs_16) != -698086050 ) /*0x5da44c*/
          break; /*0x5da44c*/
        if ( (_DWORD)savedregs_16 == 1635996050 ) /*0x5da554*/
          v2 = -789430404; /*0x5da554*/
        else
          v2 = 1175297462; /*0x5da554*/
        HIDWORD(savedregs_16) = v2; /*0x5da55c*/
      }
      if ( HIDWORD(savedregs_16) != -666659314 ) /*0x5da460*/
        break; /*0x5da460*/
      HIDWORD(savedregs_16) = -1257444924; /*0x5da6b0*/
    }
    if ( HIDWORD(savedregs_16) == -391376196 ) /*0x5da474*/
      break; /*0x5da474*/
    switch ( HIDWORD(savedregs_16) ) /*0x5da488*/
    {
      case 0xEB248716: /*0x5da488*/
        _ReadStatusReg(TPIDR_EL0); /*0x5da60c*/
        abort(); /*0x5da620*/
      case 0xD4F5CB4: /*0x5da488*/
        if ( savedregs_7 ) /*0x5da71c*/
          v5 = 901391280; /*0x5da734*/
        else
          v5 = 989248209; /*0x5da734*/
        HIDWORD(savedregs_16) = v5; /*0x5da73c*/
        break;
      case 0xF7708BE: /*0x5da488*/
        HIDWORD(savedregs_16) = -867171594; /*0x5da584*/
        break;
      case 0x35BA23B0: /*0x5da488*/
        HIDWORD(savedregs_16) = -349927658; /*0x5da604*/
        break;
      case 0x3AF6BAD1: /*0x5da488*/
        HIDWORD(savedregs_16) = -976945811; /*0x5da598*/
        break;
      default:
        HIDWORD(savedregs_16) = 259459262; /*0x5da570*/
        break;
    }
  }
  result = savedregs_8; /*0x5da5d0*/
  _ReadStatusReg(TPIDR_EL0); /*0x5da5d4*/
  return result; /*0x5da5f4*/
}