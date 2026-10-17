__int64 __fastcall sub_2E4448(
        __int64 a1,
        __int64 a2,
        __int64 a3,
        __int64 a4,
        __int64 a5,
        __int64 a6,
        __int64 a7,
        __int64 a8,
        __int64 a9,
        __int64 a10,
        __int64 a11,
        __int64 a12,
        __int64 a13,
        __int64 a14,
        __int64 a15)
{
  __int128 v15; // q8
  __int128 v16; // q15
  __int64 (__fastcall *v17)(__int64, __int64 *, __int64 *); // x12
  __int64 v18; // x19
  __int64 v19; // x20
  __int64 v20; // x21
  __int64 v21; // x0
  __int64 v22; // x8
  __int64 result; // x0
  int v24; // w8
  int v25; // w8
  _QWORD savedregs[6]; // [xsp+D0h] [xbp+0h] BYREF

  savedregs[0] = a8; /*0x2e447c*/
  savedregs[5] = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x2e4498*/
  HIDWORD(savedregs[4]) = -1888053050; /*0x2e44a4*/
  savedregs[3] = (char *)&savedregs[4] + 4; /*0x2e44ac*/
  while ( 1 ) /*0x2e44c0*/
  {
    while ( HIDWORD(savedregs[4]) == -1888053050 ) /*0x2e44c0*/
      *(_DWORD *)savedregs[3] = 489683803; /*0x2e4604*/
    if ( HIDWORD(savedregs[4]) == -1142222200 ) /*0x2e44d4*/
      break; /*0x2e44d4*/
    switch ( HIDWORD(savedregs[4]) ) /*0x2e44e8*/
    {
      case 0xCCE238A6: /*0x2e44e8*/
        if ( (savedregs[1] & 0x100000000000000LL) != 0 ) /*0x2e47d8*/
          v24 = -854330809; /*0x2e47d8*/
        else
          v24 = 293222628; /*0x2e47d8*/
        *(_DWORD *)savedregs[3] = v24; /*0x2e47e0*/
        break;
      case 0xCD13F247: /*0x2e44e8*/
        *(_DWORD *)savedregs[3] = -136317177; /*0x2e4730*/
        break;
      case 0xF55C4710: /*0x2e44e8*/
        MEMORY[0xFFFFFFFFFF4DFBF8](); /*0x2e4888*/
        JUMPOUT(0x2E488C); /*0x2e488c*/
      case 0xF7DFF707: /*0x2e44e8*/
        _ReadStatusReg(TPIDR_EL0); /*0x2e4738*/
        abort(); /*0x2e474c*/
      case 0x117A38E4: /*0x2e44e8*/
        *(_DWORD *)savedregs[3] = 2091192711; /*0x2e47f4*/
        break;
      case 0x1D2FFB5B: /*0x2e44e8*/
        v17 = *(__int64 (__fastcall **)(__int64, __int64 *, __int64 *))(*(_QWORD *)a3 + 280LL); /*0x2e4680*/
        savedregs[3] = &savedregs[1]; /*0x2e4698*/
        savedregs[5] = 0xFFFFFF80FFFFFFD8LL; /*0x2e46a8*/
        v18 = a1; /*0x2e46ac*/
        v19 = a2; /*0x2e46b4*/
        v20 = a3; /*0x2e46bc*/
        v21 = v17(a3, &a15, &a15); /*0x2e46c4*/
        a2 = v19; /*0x2e46c8*/
        a3 = v20; /*0x2e46cc*/
        v22 = v21; /*0x2e46d0*/
        a1 = v18; /*0x2e46d4*/
        savedregs[4] = v22; /*0x2e46d8*/
        savedregs[2] = v22; /*0x2e46e0*/
        *(_DWORD *)savedregs[3] = -1142222200; /*0x2e46f0*/
        break;
      case 0x1F16C44D: /*0x2e44e8*/
        *(_DWORD *)savedregs[3] = 980827917; /*0x2e4770*/
        break;
      case 0x278EC761: /*0x2e44e8*/
        *(_OWORD *)(a8 + 352) = v15; /*0x2e499c*/
        *(_OWORD *)(a8 + 368) = v16; /*0x2e499c*/
        JUMPOUT(0x2E49A0); /*0x2e49a0*/
      case 0x3A763F0D: /*0x2e44e8*/
        HIBYTE(savedregs[1]) = *(_DWORD *)sub_2E4448 >> 26 == 5 || *(_DWORD *)sub_2E4448 >> 21 == 1697; /*0x2e47a4*/
        *(_DWORD *)savedregs[3] = -857589594; /*0x2e47b4*/
        break;
      case 0x5D8C9B8B: /*0x2e44e8*/
        JUMPOUT(0x2E49B8); /*0x2e49b8*/
      case 0x5DAFC482: /*0x2e44e8*/
        if ( (savedregs[1] & 0x1000000000000LL) != 0 ) /*0x2e4878*/
          v25 = -854330809; /*0x2e4878*/
        else
          v25 = -1888053050; /*0x2e4878*/
        *(_DWORD *)savedregs[3] = v25; /*0x2e4880*/
        break;
      case 0x695BE653: /*0x2e44e8*/
        *(_DWORD *)savedregs[3] = -1888053050; /*0x2e475c*/
        break;
      case 0x7CA51187: /*0x2e44e8*/
        BYTE6(savedregs[1]) = loc_2E444C >> 10 == 3508160 || loc_2E4450 >> 10 == 3508160; /*0x2e4844*/
        *(_DWORD *)savedregs[3] = 1571800194; /*0x2e4854*/
        break;
      case 0x7ED82D5F: /*0x2e44e8*/
        JUMPOUT(0x2E4978); /*0x2e4978*/
    }
  }
  result = savedregs[2]; /*0x2e46f8*/
  _ReadStatusReg(TPIDR_EL0); /*0x2e46fc*/
  return result; /*0x2e4720*/
}