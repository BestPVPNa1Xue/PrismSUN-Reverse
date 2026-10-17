__int64 __usercall sub_6CF0C8@<X0>(__int64 a1@<X0>, __int64 a2@<X1>, __int64 a3@<X8>)
{
  __int64 v3; // x2
  __int64 v4; // x3
  __int64 v5; // x4
  __int64 v6; // x5
  __int64 v7; // x6
  __int64 v8; // x7
  __int64 v9; // x0
  __int64 v10; // x0
  __int64 v11; // x0
  __int64 v12; // x0
  unsigned int v13; // w27
  __int64 *v14; // x22
  __int64 *v15; // x19
  __int64 *v16; // x22
  __int64 v17; // x0
  __int64 v18; // x0
  __int64 *v19; // x22
  __int64 v20; // x0
  __int64 *v21; // x22
  __int64 v22; // x23
  __int64 v23; // x0
  __int64 v24; // x1
  unsigned int v25; // w23
  unsigned int *v26; // x22
  _QWORD *v27; // x21
  unsigned __int64 v28; // x0
  __n128 v29; // q5
  unsigned int v30; // w20
  unsigned __int64 v31; // x0
  __n128 v32; // q5
  __int64 result; // x0
  __int64 v34; // [xsp-1B0h] [xbp-220h] BYREF
  __int64 v35; // [xsp-190h] [xbp-200h] BYREF
  __int64 v36; // [xsp-180h] [xbp-1F0h] BYREF
  __int64 v37; // [xsp-170h] [xbp-1E0h] BYREF
  __int64 v38; // [xsp-160h] [xbp-1D0h] BYREF
  __int64 v39; // [xsp-150h] [xbp-1C0h] BYREF
  _BYTE v40[32]; // [xsp-140h] [xbp-1B0h] BYREF
  __int64 v41; // [xsp-120h] [xbp-190h]
  __int64 v42; // [xsp-110h] [xbp-180h] BYREF
  __int64 v43; // [xsp-100h] [xbp-170h] BYREF
  __int64 v44; // [xsp-E0h] [xbp-150h] BYREF
  __int64 v45; // [xsp-D0h] [xbp-140h]
  __int64 v46; // [xsp-C0h] [xbp-130h] BYREF
  _QWORD v47[4]; // [xsp-A0h] [xbp-110h] BYREF
  _BYTE v48[32]; // [xsp-80h] [xbp-F0h] BYREF
  _QWORD v49[2]; // [xsp-60h] [xbp-D0h] BYREF
  char v50; // [xsp-50h] [xbp-C0h]
  _QWORD v51[9]; // [xsp-40h] [xbp-B0h] BYREF
  __int64 *v52; // [xsp+8h] [xbp-68h]
  __int64 *v53; // [xsp+10h] [xbp-60h]
  __int64 *v54; // [xsp+18h] [xbp-58h]
  __int64 *v55; // [xsp+20h] [xbp-50h]
  __int64 *v56; // [xsp+28h] [xbp-48h]
  __int64 *v57; // [xsp+30h] [xbp-40h]
  unsigned int *v58; // [xsp+38h] [xbp-38h]
  __int64 *v59; // [xsp+40h] [xbp-30h]
  _QWORD *v60; // [xsp+48h] [xbp-28h]
  __int64 *v61; // [xsp+50h] [xbp-20h]
  __int64 *v62; // [xsp+58h] [xbp-18h]
  __int64 v63; // [xsp+60h] [xbp-10h]
  __int64 v64; // [xsp+68h] [xbp-8h]

  v64 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x6cf0f0*/
  if ( ((((((((*(_DWORD *)sub_6CF0C8 >> 26 == 5) << 31 >> 31) + ((*(_DWORD *)sub_6CF0C8 >> 21 == 1697) << 31 >> 31)) << 31 >> 31) /*0x6cf6c0*/
         - 1) << 31 >> 31)
       + ((*(_DWORD *)sub_6CF0C8 >> 21 != 1697 || *(_DWORD *)sub_6CF0C8 >> 26 != 5) << 31 >> 31))
      & 1) != 0
    || loc_6CF0CC >> 10 == 3508160
    || loc_6CF0D0 >> 10 == 3508160 )
  {
    _ReadStatusReg(TPIDR_EL0); /*0x6cf610*/
    sub_6DD8D8(); /*0x6cf624*/
  }
  v59 = &v46; /*0x6cf150*/
  v52 = &v43; /*0x6cf16c*/
  v61 = &v42; /*0x6cf178*/
  v53 = &v39; /*0x6cf194*/
  v56 = &v38; /*0x6cf1a0*/
  v55 = &v37; /*0x6cf1ac*/
  v54 = &v36; /*0x6cf1b8*/
  v58 = (unsigned int *)&v35; /*0x6cf1c4*/
  v57 = &v34; /*0x6cf1d0*/
  v63 = a3; /*0x6cf1d8*/
  v51[6] = a3; /*0x6cf1dc*/
  v51[4] = a1; /*0x6cf1e0*/
  v51[2] = a2; /*0x6cf1e4*/
  v51[0] = sub_3B8C40(a1); /*0x6cf1ec*/
  v60 = v51; /*0x6cf1f0*/
  v9 = sub_6DD8B0(v51[0] + 556LL, 5u, v3, v4, v5, v6, v7, v8, v34); /*0x6cf200*/
  v50 = v9 & 1; /*0x6cf208*/
  v10 = sub_2A8358(v9); /*0x6cf20c*/
  v62 = v49; /*0x6cf214*/
  sub_6DD8B4(v49, v10); /*0x6cf220*/
  v11 = sub_10272C(v48); /*0x6cf228*/
  ((void (__fastcall *)(_QWORD *__return_ptr, __int64))sub_306DF0)(v47, v11); /*0x6cf230*/
  if ( (((__int64 (__fastcall *)(_QWORD *))loc_6AE7D0)(v47) & 1) != 0 ) /*0x6cf254*/
  {
    v41 = ((__int64 (__fastcall *)(_QWORD *))sub_6B0660)(v47); /*0x6cf314*/
    sub_31B73C(v41, (__int64)v40); /*0x6cf320*/
    v15 = v61; /*0x6cf324*/
    sub_189B94(v48, v40); /*0x6cf338*/
    sub_6DD8C0(v40); /*0x6cf340*/
    *(_DWORD *)v15 = 0; /*0x6cf344*/
  }
  else
  {
    v12 = ((__int64 (__fastcall *)(__int64 *))loc_6D30A4)(&v44); /*0x6cf264*/
    v45 = sub_6DD8B8(v12); /*0x6cf27c*/
    v13 = sub_2B2208(0xBBAu); /*0x6cf288*/
    v14 = v52; /*0x6cf290*/
    sub_6DD8BC(v52, v45); /*0x6cf298*/
    v15 = v61; /*0x6cf2a8*/
    ((void (__fastcall *)(_QWORD, __int64 *))loc_6B00FC)(v13, v14); /*0x6cf2b8*/
    sub_74539C(v14); /*0x6cf2c4*/
    *(_DWORD *)v15 = 1; /*0x6cf2cc*/
  }
  sub_3078CC(v47); /*0x6cf354*/
  if ( !*(_DWORD *)v15 ) /*0x6cf358*/
  {
    v16 = v53; /*0x6cf364*/
    *v53 = (__int64)v48; /*0x6cf368*/
    v17 = sub_189C64(*v16); /*0x6cf370*/
    *v56 = v17; /*0x6cf378*/
    v18 = sub_189D50(*v16); /*0x6cf380*/
    *v55 = v18; /*0x6cf388*/
    while ( (sub_191270(v56, v55) & 1) != 0 ) /*0x6cf39c*/
    {
      v20 = sub_191368(v56); /*0x6cf3d0*/
      v21 = v54; /*0x6cf3d4*/
      *v54 = v20; /*0x6cf3d8*/
      v22 = sub_4DAE04(v62); /*0x6cf3e4*/
      v23 = sub_141054(*v21); /*0x6cf3ec*/
      v24 = sub_6DD8C4(v23); /*0x6cf3f4*/
      sub_2A7FEC(v22, v24); /*0x6cf408*/
      sub_6DD8C8(v56); /*0x6cf420*/
    }
    *(_DWORD *)v15 = 2; /*0x6cf3a8*/
    v19 = v57; /*0x6cf3ac*/
    sub_191AD8(v57, v48); /*0x6cf440*/
    v25 = sub_6D4374(v19); /*0x6cf450*/
    sub_B8614(v57); /*0x6cf460*/
    v26 = v58; /*0x6cf464*/
    *v58 = v25; /*0x6cf468*/
    v27 = v60; /*0x6cf470*/
    if ( (v50 & 1) != 0 ) /*0x6cf474*/
    {
      v30 = *v26; /*0x6cf500*/
      if ( v30 == (unsigned int)((__int64 (__fastcall *)(__int64, __int64))sub_591164)(*v60 + 552LL, 5) ) /*0x6cf520*/
      {
        ((void (*)(void))loc_6D49A8)(); /*0x6cf570*/
      }
      else
      {
        sub_591620(*v27 + 552LL, *v26, 5u); /*0x6cf53c*/
        v31 = sub_6DD8D0((unsigned __int64 *)v62); /*0x6cf544*/
        sub_634E84(33, v31, v63, v32); /*0x6cf554*/
      }
      *(_DWORD *)v15 = 1; /*0x6cf560*/
    }
    else
    {
      sub_6DD8CC(*v60 + 556LL, 1, 5); /*0x6cf494*/
      sub_591620(*v27 + 552LL, *v26, 5u); /*0x6cf4a8*/
      v28 = sub_4DB0C4((unsigned __int64 *)v62); /*0x6cf4b0*/
      sub_634E84(25, v28, v63, v29); /*0x6cf4c0*/
      *(_DWORD *)v15 = 1; /*0x6cf4cc*/
    }
  }
  sub_B8614(v48); /*0x6cf598*/
  result = sub_2D94E4(v62); /*0x6cf5a0*/
  _ReadStatusReg(TPIDR_EL0); /*0x6cf5a4*/
  return result; /*0x6cf5d4*/
}