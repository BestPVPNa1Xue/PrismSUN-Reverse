__int64 sub_5BA690()
{
  int v0; // w8
  unsigned int v1; // w8
  int v2; // w8
  char v3; // w8
  int v4; // w8
  __int64 v5; // x21
  __int64 result; // x0
  int v7; // w8
  int v8; // w8
  bool v9; // [xsp+46h] [xbp+6h]
  bool v10; // [xsp+47h] [xbp+7h]
  _QWORD *v11; // [xsp+48h] [xbp+8h]
  bool v12; // [xsp+5Fh] [xbp+1Fh]
  _QWORD savedregs[2]; // [xsp+60h] [xbp+20h] BYREF

  savedregs[1] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x5ba6b0*/
  savedregs[0] = 0x3A2B91B9FF8BE5FCLL; /*0x5ba6bc*/
  while ( 1 ) /*0x5ba6f8*/
  {
    while ( 1 ) /*0x5ba6e4*/
    {
      while ( HIDWORD(savedregs[0]) == -1872295163 ) /*0x5ba6e4*/
      {
        if ( v9 ) /*0x5bb00c*/
          v8 = 872624045; /*0x5bb024*/
        else
          v8 = -41380264; /*0x5bb024*/
        HIDWORD(savedregs[0]) = v8; /*0x5bb02c*/
      }
      if ( HIDWORD(savedregs[0]) != -1747860154 ) /*0x5ba6f8*/
        break; /*0x5ba6f8*/
      HIDWORD(savedregs[0]) = 1743212331; /*0x5ba9cc*/
    }
    if ( HIDWORD(savedregs[0]) == -1711536574 ) /*0x5ba70c*/
      break; /*0x5ba70c*/
    switch ( HIDWORD(savedregs[0]) ) /*0x5ba748*/
    {
      case 0xB8C9EC05: /*0x5ba748*/
        if ( v12 ) /*0x5ba998*/
          v2 = -1747860154; /*0x5ba9b0*/
        else
          v2 = -368143811; /*0x5ba9b0*/
        HIDWORD(savedregs[0]) = v2; /*0x5ba9b8*/
        break;
      case 0xC11B59C6: /*0x5ba748*/
        v5 = sub_785874(qword_7AF460); /*0x5bae24*/
        sub_5CC2DC(v5, v11); /*0x5bae30*/
        sub_5CC2E0(&loc_5C1244, v5, &off_78EC70); /*0x5bae48*/
        *(_BYTE *)sub_785874(qword_7AF480) = 1; /*0x5bae5c*/
        HIDWORD(savedregs[0]) = 1562609967; /*0x5bae6c*/
        break;
      case 0xCEFB4C4A: /*0x5ba748*/
        if ( v10 ) /*0x5baf6c*/
          v7 = 872624045; /*0x5baf84*/
        else
          v7 = 79077424; /*0x5baf84*/
        HIDWORD(savedregs[0]) = v7; /*0x5baf8c*/
        break;
      case 0xE1BFD385: /*0x5ba748*/
        HIDWORD(savedregs[0]) = 1901960410; /*0x5bad58*/
        break;
      case 0xEA0E923D: /*0x5ba748*/
        HIDWORD(savedregs[0]) = 434061399; /*0x5bad20*/
        break;
      case 0xFD889658: /*0x5ba748*/
        v11 = savedregs; /*0x5bad80*/
        *(_QWORD *)((char *)savedregs + 6) = *(__int64 *)((char *)&qword_7AF3F0 + 6); /*0x5bada8*/
        savedregs[0] = qword_7AF3F0; /*0x5badac*/
        if ( (*(_BYTE *)sub_785874(qword_7AF480) & 1) != 0 ) /*0x5badcc*/
          v3 = -43; /*0x5badcc*/
        else
          v3 = -44; /*0x5badcc*/
        if ( v3 == -44 ) /*0x5badf0*/
          v4 = 1261386462; /*0x5badf0*/
        else
          v4 = -1711536574; /*0x5badf0*/
        HIDWORD(savedregs[0]) = v4; /*0x5badf8*/
        break;
      case 0x4B6A030: /*0x5ba748*/
        HIDWORD(savedregs[0]) = 1682850629; /*0x5bafa0*/
        break;
      case 0x6D1C842: /*0x5ba748*/
        _ReadStatusReg(TPIDR_EL0); /*0x5baed0*/
        abort(); /*0x5baee4*/
      case 0x19DF4057: /*0x5ba748*/
        atomic_store(1u, dword_7D095C); /*0x5bad34*/
        HIDWORD(savedregs[0]) = -507522171; /*0x5bad44*/
        break;
      case 0x1E24D345: /*0x5ba748*/
        v1 = atomic_load(dword_7D095C); /*0x5ba96c*/
        v12 = v1 == 0; /*0x5ba97c*/
        HIDWORD(savedregs[0]) = -1194726395; /*0x5ba98c*/
        break;
      case 0x34032FAD: /*0x5ba748*/
        HIDWORD(savedregs[0]) = 114411586; /*0x5baec8*/
        break;
      case 0x3A2B91B9: /*0x5ba748*/
        if ( LODWORD(savedregs[0]) > 0x63B374F3 ) /*0x5ba954*/
          v0 = 505729861; /*0x5ba954*/
        else
          v0 = 1157832957; /*0x5ba954*/
        HIDWORD(savedregs[0]) = v0; /*0x5ba95c*/
        break;
      case 0x450320FD: /*0x5ba748*/
        JUMPOUT(0x5BB038); /*0x5bb038*/
      case 0x4B2F3ADE: /*0x5ba748*/
        HIDWORD(savedregs[0]) = -1055172154; /*0x5bae0c*/
        break;
      case 0x5CA0354B: /*0x5ba748*/
        HIDWORD(savedregs[0]) = -368143811; /*0x5bad0c*/
        break;
      case 0x5D23892F: /*0x5ba748*/
        HIDWORD(savedregs[0]) = -1711536574; /*0x5bae80*/
        break;
      case 0x62519037: /*0x5ba748*/
        v10 = *(_DWORD *)sub_5BA690 >> 26 == 5 || *(_DWORD *)sub_5BA690 >> 21 == 1697; /*0x5baf50*/
        HIDWORD(savedregs[0]) = -822391734; /*0x5baf60*/
        break;
      case 0x644E4345: /*0x5ba748*/
        v9 = loc_5BA694 >> 10 == 3508160 || loc_5BA698 >> 10 == 3508160; /*0x5baff0*/
        HIDWORD(savedregs[0]) = -1872295163; /*0x5bb000*/
        break;
      case 0x67E74F2B: /*0x5ba748*/
        LOBYTE(qword_7AF3F0) = byte_7AF3E0 ^ 0x20; /*0x5ba9f0*/
        BYTE1(qword_7AF3F0) = byte_7AF3E1 ^ 0x2B; /*0x5baa14*/
        BYTE2(qword_7AF3F0) = byte_7AF3E2 ^ 0x49; /*0x5baa38*/
        BYTE3(qword_7AF3F0) = ~byte_7AF3E3 & 0xDF | byte_7AF3E3 & 0x20; /*0x5baa70*/
        BYTE4(qword_7AF3F0) = byte_7AF3E4 ^ 0xF4; /*0x5baa94*/
        BYTE5(qword_7AF3F0) = ~byte_7AF3E5 & 0xB7 | byte_7AF3E5 & 0x48; /*0x5baad4*/
        BYTE6(qword_7AF3F0) = ~(byte_7AF3E6 | 0x70) | ~(~byte_7AF3E6 | 0x8F); /*0x5bab40*/
        HIBYTE(qword_7AF3F0) = (~byte_7AF3E7 & 0xFD | byte_7AF3E7 & 2) ^ 0x75; /*0x5bab84*/
        byte_7AF3F8 = byte_7AF3E8 ^ 0x2E; /*0x5baba8*/
        byte_7AF3F9 = byte_7AF3E9 ^ 0xE2; /*0x5babcc*/
        byte_7AF3FA = byte_7AF3EA - (2 * (~(byte_7AF3EA ^ 0x2C) & 0x2C) - 44); /*0x5bac18*/
        byte_7AF3FB = (~byte_7AF3EB & 0x42 | byte_7AF3EB & 0xBD) ^ 0x77; /*0x5bac64*/
        byte_7AF3FC = byte_7AF3EC ^ 0x42; /*0x5bac88*/
        byte_7AF3FD = ~(~(~byte_7AF3ED & 0xD4) & (~byte_7AF3ED | 0xD4)); /*0x5bace8*/
        HIDWORD(savedregs[0]) = 1554003275; /*0x5bacf8*/
        break;
      default:
        HIDWORD(savedregs[0]) = 1649512503; /*0x5baf08*/
        break;
    }
  }
  result = sub_785874(qword_7AF460); /*0x5bae90*/
  _ReadStatusReg(TPIDR_EL0); /*0x5bae94*/
  return result; /*0x5baeb8*/
}