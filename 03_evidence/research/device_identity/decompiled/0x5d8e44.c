__int64 __fastcall sub_5D8E44(__int64 a1)
{
  __int64 v1; // x19
  int v2; // w8
  unsigned int v3; // w8
  int v4; // w8
  _BYTE *v5; // x8
  char v6; // w8
  int v7; // w8
  __int64 v8; // x20
  __int64 result; // x0
  int v10; // w8
  int v11; // w8
  bool v12; // [xsp+47h] [xbp-9h]
  __int64 v13; // [xsp+48h] [xbp-8h]
  bool v14; // [xsp+57h] [xbp+7h]
  __int128 *v15; // [xsp+58h] [xbp+8h]
  __int128 v16; // [xsp+60h] [xbp+10h] BYREF
  __int128 savedregs; // [xsp+70h] [xbp+20h]

  *((_QWORD *)&savedregs + 1) = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x5d8e60*/
  *(_QWORD *)&savedregs = 0x4615D7CE9F1CFF59LL; /*0x5d8e6c*/
  while ( DWORD1(savedregs) != -2100927183 ) /*0x5d8e94*/
  {
    switch ( DWORD1(savedregs) ) /*0x5d8ea8*/
    {
      case 0x835983CB: /*0x5d8ea8*/
        if ( v14 ) /*0x5d990c*/
          v7 = -798698595; /*0x5d9924*/
        else
          v7 = 1951232062; /*0x5d9924*/
        DWORD1(savedregs) = v7; /*0x5d992c*/
        break;
      case 0x8A9E93E5: /*0x5d8ea8*/
        DWORD1(savedregs) = 1884576300; /*0x5d97fc*/
        break;
      case 0x910F4ADB: /*0x5d8ea8*/
        _ReadStatusReg(TPIDR_EL0); /*0x5d9a30*/
        abort(); /*0x5d9a44*/
      case 0x956E1673: /*0x5d8ea8*/
        if ( (HIBYTE(v16) & 1) != 0 ) /*0x5d9170*/
          v4 = 797928020; /*0x5d9170*/
        else
          v4 = -1969318939; /*0x5d9170*/
        DWORD1(savedregs) = v4; /*0x5d9178*/
        break;
      case 0xC69E3D77: /*0x5d8ea8*/
        DWORD1(savedregs) = 534193696; /*0x5d984c*/
        break;
      case 0xCB577ABA: /*0x5d8ea8*/
        DWORD1(savedregs) = 66943637; /*0x5d9838*/
        break;
      case 0xD064D39D: /*0x5d8ea8*/
        DWORD1(savedregs) = 1528793244; /*0x5d9940*/
        break;
      case 0xDFF0792E: /*0x5d8ea8*/
        if ( v12 ) /*0x5d9ac0*/
          v10 = -1861268773; /*0x5d9ad8*/
        else
          v10 = 357820848; /*0x5d9ad8*/
        DWORD1(savedregs) = v10; /*0x5d9ae0*/
        break;
      case 0xF20F64D7: /*0x5d8ea8*/
        LOBYTE(xmmword_7AF5B0) = byte_7AF590 ^ 0x36; /*0x5d91b8*/
        BYTE1(xmmword_7AF5B0) = byte_7AF591 ^ 0xBC; /*0x5d91dc*/
        BYTE2(xmmword_7AF5B0) = ~(byte_7AF592 & 0x9E) & ~(~byte_7AF592 & 0x61); /*0x5d924c*/
        BYTE3(xmmword_7AF5B0) = (~byte_7AF593 & 0xF3 | byte_7AF593 & 0xC) ^ 9; /*0x5d9290*/
        BYTE4(xmmword_7AF5B0) = byte_7AF594 ^ 0xC2; /*0x5d92b4*/
        BYTE5(xmmword_7AF5B0) = byte_7AF595 ^ 0x68; /*0x5d92d8*/
        BYTE6(xmmword_7AF5B0) = byte_7AF596 ^ 0x15; /*0x5d92fc*/
        BYTE7(xmmword_7AF5B0) = byte_7AF597 ^ 0x13; /*0x5d9320*/
        BYTE8(xmmword_7AF5B0) = (~byte_7AF598 & 0x68 | byte_7AF598 & 0x97) ^ 0xA4; /*0x5d936c*/
        BYTE9(xmmword_7AF5B0) = byte_7AF599 ^ 0x5F; /*0x5d9390*/
        BYTE10(xmmword_7AF5B0) = byte_7AF59A ^ 0x32; /*0x5d93b4*/
        BYTE11(xmmword_7AF5B0) = (~byte_7AF59B & 0x55 | byte_7AF59B & 0xAA) ^ 0x81; /*0x5d9400*/
        BYTE12(xmmword_7AF5B0) = byte_7AF59C ^ 0x67; /*0x5d9424*/
        BYTE13(xmmword_7AF5B0) = byte_7AF59D ^ 0xE3; /*0x5d9448*/
        BYTE14(xmmword_7AF5B0) = byte_7AF59E + 24 - 2 * (byte_7AF59E & 0x18); /*0x5d9478*/
        HIBYTE(xmmword_7AF5B0) = byte_7AF59F ^ 0x9E; /*0x5d949c*/
        LOBYTE(xmmword_7AF5C0) = byte_7AF5A0 ^ 0x44; /*0x5d94c0*/
        BYTE1(xmmword_7AF5C0) = byte_7AF5A1 ^ 0xDD; /*0x5d94e4*/
        BYTE2(xmmword_7AF5C0) = byte_7AF5A2 ^ 0x51; /*0x5d9508*/
        BYTE3(xmmword_7AF5C0) = ~(~(~byte_7AF5A3 | 0xBC) | ~(byte_7AF5A3 | 0x43)); /*0x5d9568*/
        BYTE4(xmmword_7AF5C0) = byte_7AF5A4 ^ 0x6E; /*0x5d958c*/
        BYTE5(xmmword_7AF5C0) = byte_7AF5A5 ^ 0x9B; /*0x5d95b0*/
        BYTE6(xmmword_7AF5C0) = byte_7AF5A6 ^ 0xBC; /*0x5d95d4*/
        BYTE7(xmmword_7AF5C0) = byte_7AF5A7 ^ 0xFB; /*0x5d95f8*/
        BYTE8(xmmword_7AF5C0) = byte_7AF5A8 - (2 * (~(byte_7AF5A8 ^ 0x6D) & 0x6D) - 109); /*0x5d9644*/
        BYTE9(xmmword_7AF5C0) = byte_7AF5A9 ^ 0xBB; /*0x5d9668*/
        BYTE10(xmmword_7AF5C0) = ~(byte_7AF5AA | 0x35) | byte_7AF5AA & 0x35; /*0x5d96d0*/
        BYTE11(xmmword_7AF5C0) = byte_7AF5AB ^ 0x8F; /*0x5d96f4*/
        BYTE12(xmmword_7AF5C0) = byte_7AF5AC ^ 0xB2; /*0x5d9718*/
        BYTE13(xmmword_7AF5C0) = ~((byte_7AF5AD | 0x19) & ~(byte_7AF5AD & 0x19)); /*0x5d9780*/
        BYTE14(xmmword_7AF5C0) = byte_7AF5AE ^ 0x70; /*0x5d97a0*/
        HIBYTE(xmmword_7AF5C0) = byte_7AF5AF ^ 0xC7; /*0x5d97c4*/
        DWORD1(savedregs) = 2761199; /*0x5d97d4*/
        break;
      case 0x2A21EF: /*0x5d8ea8*/
        DWORD1(savedregs) = -1969318939; /*0x5d97e8*/
        break;
      case 0x3FD7A95: /*0x5d8ea8*/
        DWORD1(savedregs) = 1885689037; /*0x5d9a54*/
        break;
      default:
        v1 = a1; /*0x5d8fb4*/
        switch ( DWORD1(savedregs) ) /*0x5d8fd8*/
        {
          case 0x1553E9B0: /*0x5d8fd8*/
            if ( loc_5D8E48 >> 10 == 3508160 || loc_5D8E4C >> 10 == 3508160 ) /*0x5d9b58*/
              v11 = -1861268773; /*0x5d9b5c*/
            else
              v11 = -962708105; /*0x5d9b5c*/
            DWORD1(savedregs) = v11; /*0x5d9b64*/
            break;
          case 0x1D271EEE: /*0x5d8fd8*/
            DWORD1(savedregs) = 1951232062; /*0x5d99b8*/
            break;
          case 0x1FD72620: /*0x5d8fd8*/
            v15 = &v16; /*0x5d9874*/
            savedregs = xmmword_7AF5C0; /*0x5d989c*/
            v16 = xmmword_7AF5B0; /*0x5d98a0*/
            v5 = (_BYTE *)sub_785874(qword_7AF740); /*0x5d98b0*/
            a1 = v1; /*0x5d98b4*/
            if ( (*v5 & 1) != 0 ) /*0x5d98c8*/
              v6 = 21; /*0x5d98c8*/
            else
              v6 = 20; /*0x5d98c8*/
            v14 = (char)(v6 & 0xEB) == 0; /*0x5d98f0*/
            DWORD1(savedregs) = -2091285557; /*0x5d9900*/
            break;
          case 0x2F8F6A54: /*0x5d8fd8*/
            DWORD1(savedregs) = -233872169; /*0x5d918c*/
            break;
          case 0x31A876DC: /*0x5d8fd8*/
            v3 = atomic_load(dword_7D0978); /*0x5d9128*/
            HIBYTE(v16) = v3 == 0; /*0x5d9138*/
            DWORD1(savedregs) = -1787947405; /*0x5d9148*/
            break;
          case 0x376D42DF: /*0x5d8fd8*/
            JUMPOUT(0x5D9B70); /*0x5d9b70*/
          case 0x4615D7CE: /*0x5d8fd8*/
            if ( (unsigned int)savedregs >= 0xE144479 ) /*0x5d910c*/
              v2 = 833124060; /*0x5d910c*/
            else
              v2 = 929907423; /*0x5d910c*/
            DWORD1(savedregs) = v2; /*0x5d9114*/
            break;
          case 0x5B1F889C: /*0x5d8fd8*/
            v8 = sub_785874(qword_7AF720); /*0x5d9958*/
            ((void (__fastcall *)(__int64, __int128 *))loc_5F3774)(v8, v15); /*0x5d9964*/
            sub_5FE438(&loc_5F3EB4, v8, &off_78EC70); /*0x5d997c*/
            *(_BYTE *)sub_785874(qword_7AF740) = 1; /*0x5d9990*/
            DWORD1(savedregs) = 489103086; /*0x5d99a0*/
            a1 = v1; /*0x5d99a4*/
            break;
          case 0x66C51286: /*0x5d8fd8*/
            v13 = sub_785874(qword_7AF720); /*0x5d99e8*/
            DWORD1(savedregs) = -2100927183; /*0x5d99f8*/
            a1 = v1; /*0x5d99fc*/
            break;
          case 0x70545A2C: /*0x5d8fd8*/
            atomic_store(1u, dword_7D0978); /*0x5d9810*/
            DWORD1(savedregs) = -883459398; /*0x5d9820*/
            break;
          case 0x706554CD: /*0x5d8fd8*/
            v12 = (*(_DWORD *)sub_5D8E44 >> 26 == 5 || *(_DWORD *)sub_5D8E44 >> 21 == 1697) /*0x5d9aa0*/
               && (*(_DWORD *)sub_5D8E44 >> 26 == 5 || *(_DWORD *)sub_5D8E44 >> 21 == 1697);
            DWORD1(savedregs) = -537888466; /*0x5d9ab0*/
            break;
          default:
            DWORD1(savedregs) = 1724191366; /*0x5d99d0*/
            break;
        }
        break;
    }
  }
  result = v13; /*0x5d9a04*/
  _ReadStatusReg(TPIDR_EL0); /*0x5d9a08*/
  return result; /*0x5d9a2c*/
}