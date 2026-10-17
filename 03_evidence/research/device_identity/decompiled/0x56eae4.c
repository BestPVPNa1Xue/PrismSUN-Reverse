void __usercall sub_56EAE4(__int64 a1@<X0>, __int64 a2@<X8>)
{
  __int64 v3; // x20
  __int64 v4; // x0
  char *v5; // x27
  __int64 v6; // x21
  __int64 v7; // x0
  int v8; // w9
  bool v9; // w8
  __int64 v10; // [xsp-490h] [xbp-5C0h] BYREF
  __int64 v11; // [xsp-470h] [xbp-5A0h] BYREF
  __int64 v12; // [xsp-460h] [xbp-590h] BYREF
  __int64 v13; // [xsp-440h] [xbp-570h] BYREF
  __int64 v14; // [xsp-430h] [xbp-560h] BYREF
  __int64 v15; // [xsp-3E0h] [xbp-510h] BYREF
  __int64 v16; // [xsp-390h] [xbp-4C0h] BYREF
  __int64 v17; // [xsp-370h] [xbp-4A0h] BYREF
  __int64 v18; // [xsp-360h] [xbp-490h] BYREF
  __int64 v19; // [xsp-350h] [xbp-480h] BYREF
  __int64 v20; // [xsp-340h] [xbp-470h] BYREF
  __int64 v21; // [xsp-320h] [xbp-450h] BYREF
  __int64 v22; // [xsp-300h] [xbp-430h] BYREF
  __int64 v23; // [xsp-2F0h] [xbp-420h] BYREF
  __int64 v24; // [xsp-2E0h] [xbp-410h] BYREF
  __int64 v25; // [xsp-2C0h] [xbp-3F0h] BYREF
  __int64 v26; // [xsp-2B0h] [xbp-3E0h] BYREF
  __int64 v27; // [xsp-2A0h] [xbp-3D0h] BYREF
  __int64 v28; // [xsp-290h] [xbp-3C0h] BYREF
  __int64 v29; // [xsp-270h] [xbp-3A0h] BYREF
  __int64 v30; // [xsp-250h] [xbp-380h] BYREF
  __int64 v31; // [xsp-240h] [xbp-370h] BYREF
  __int64 v32; // [xsp-230h] [xbp-360h] BYREF
  __int64 v33; // [xsp-1F0h] [xbp-320h] BYREF
  __int64 v34; // [xsp-1C0h] [xbp-2F0h] BYREF
  __int64 v35; // [xsp-1A0h] [xbp-2D0h] BYREF
  __int64 v36; // [xsp-180h] [xbp-2B0h] BYREF
  __int64 v37; // [xsp-160h] [xbp-290h] BYREF
  __int64 v38; // [xsp-120h] [xbp-250h] BYREF
  __int64 v39; // [xsp-110h] [xbp-240h] BYREF
  __int64 v40; // [xsp-E0h] [xbp-210h] BYREF
  _QWORD v41[2]; // [xsp-C0h] [xbp-1F0h] BYREF
  _QWORD v42[2]; // [xsp-B0h] [xbp-1E0h] BYREF
  __int64 v43; // [xsp-A0h] [xbp-1D0h] BYREF
  __int64 v44; // [xsp-80h] [xbp-1B0h] BYREF
  __int64 v45; // [xsp-60h] [xbp-190h] BYREF
  __int64 v46; // [xsp-50h] [xbp-180h] BYREF
  _QWORD v47[4]; // [xsp-40h] [xbp-170h] BYREF
  __int64 v48; // [xsp-20h] [xbp-150h]
  __int64 v49; // [xsp-10h] [xbp-140h]
  __int64 *v50; // [xsp+0h] [xbp-130h]
  __int64 *v51; // [xsp+8h] [xbp-128h]
  __int64 *v52; // [xsp+10h] [xbp-120h]
  __int64 *v53; // [xsp+18h] [xbp-118h]
  __int64 *v54; // [xsp+20h] [xbp-110h]
  __int64 *v55; // [xsp+28h] [xbp-108h]
  __int64 *v56; // [xsp+30h] [xbp-100h]
  __int64 *v57; // [xsp+38h] [xbp-F8h]
  __int64 *v58; // [xsp+40h] [xbp-F0h]
  __int64 *v59; // [xsp+48h] [xbp-E8h]
  __int64 *v60; // [xsp+50h] [xbp-E0h]
  __int64 *v61; // [xsp+58h] [xbp-D8h]
  __int64 *v62; // [xsp+60h] [xbp-D0h]
  __int64 *v63; // [xsp+68h] [xbp-C8h]
  __int64 *v64; // [xsp+70h] [xbp-C0h]
  __int64 *v65; // [xsp+78h] [xbp-B8h]
  __int64 *v66; // [xsp+80h] [xbp-B0h]
  __int64 *v67; // [xsp+88h] [xbp-A8h]
  __int64 *v68; // [xsp+90h] [xbp-A0h]
  __int64 *v69; // [xsp+98h] [xbp-98h]
  __int64 *v70; // [xsp+A0h] [xbp-90h]
  __int64 *v71; // [xsp+A8h] [xbp-88h]
  __int64 *v72; // [xsp+B0h] [xbp-80h]
  __int64 *v73; // [xsp+B8h] [xbp-78h]
  __int64 *v74; // [xsp+C0h] [xbp-70h]
  __int64 *v75; // [xsp+C8h] [xbp-68h]
  __int64 *v76; // [xsp+D0h] [xbp-60h]
  __int64 *v77; // [xsp+D8h] [xbp-58h]
  __int64 *v78; // [xsp+E0h] [xbp-50h]
  __int64 *v79; // [xsp+E8h] [xbp-48h]
  __int64 *v80; // [xsp+F0h] [xbp-40h]
  __int64 *v81; // [xsp+F8h] [xbp-38h]
  __int64 *v82; // [xsp+100h] [xbp-30h]
  __int64 *v83; // [xsp+108h] [xbp-28h]
  __int64 *v84; // [xsp+110h] [xbp-20h]
  __int64 v85; // [xsp+118h] [xbp-18h]
  __int64 v86; // [xsp+120h] [xbp-10h]

  v85 = a2; /*0x56eb04*/
  v86 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL0) + 40); /*0x56eb10*/
  if ( !atomic_load(dword_7D092C) ) /*0x56eb1c*/
  {
    byte_7AF000 = byte_7AEFF8 ^ 0x8B; /*0x56eb48*/
    byte_7AF001 = byte_7AEFF9 ^ 0x6A; /*0x56eb6c*/
    byte_7AF002 = ~byte_7AEFFA & 0x2E | byte_7AEFFA & 0xD1; /*0x56ebac*/
    byte_7AF003 = ~byte_7AEFFB & 0x56 | byte_7AEFFB & 0xA9; /*0x56ebec*/
    byte_7AF004 = byte_7AEFFC + 7 - 2 * (byte_7AEFFC & 7); /*0x56ec1c*/
  }
  atomic_store(1u, dword_7D092C); /*0x56ec30*/
  if ( *(_DWORD *)sub_56EAE4 >> 26 != 5 /*0x5704e4*/
    && *(_DWORD *)sub_56EAE4 >> 21 != 1697
    && loc_56EAE8 >> 10 != 3508160
    && loc_56EAEC >> 10 != 3508160 )
  {
    v80 = &v46; /*0x56ec54*/
    v77 = &v45; /*0x56ec60*/
    v83 = &v44; /*0x56ec6c*/
    v82 = &v43; /*0x56ec78*/
    v81 = &v40; /*0x56ec94*/
    v84 = &v39; /*0x56eca8*/
    v79 = &v38; /*0x56ecb4*/
    v78 = &v37; /*0x56ecc0*/
    v76 = &v36; /*0x56eccc*/
    v75 = &v35; /*0x56ecd8*/
    v50 = &v34; /*0x56ece8*/
    v74 = &v33; /*0x56ed04*/
    v73 = &v32; /*0x56ed20*/
    v52 = &v31; /*0x56ed30*/
    v51 = &v30; /*0x56ed40*/
    v72 = &v29; /*0x56ed4c*/
    v70 = &v28; /*0x56ed58*/
    v55 = &v27; /*0x56ed68*/
    v54 = &v26; /*0x56ed78*/
    v53 = &v25; /*0x56ed88*/
    v58 = &v24; /*0x56ed94*/
    v57 = &v23; /*0x56eda0*/
    v56 = &v22; /*0x56edac*/
    v66 = &v21; /*0x56edb8*/
    v65 = &v20; /*0x56edc4*/
    v61 = &v19; /*0x56edd0*/
    v60 = &v18; /*0x56eddc*/
    v59 = &v17; /*0x56ede8*/
    v62 = &v16; /*0x56edf4*/
    v64 = &v15; /*0x56ee00*/
    v63 = &v14; /*0x56ee0c*/
    v68 = &v13; /*0x56ee18*/
    v67 = &v11; /*0x56ee2c*/
    v69 = &v10; /*0x56ee38*/
    v49 = v85; /*0x56ee44*/
    v48 = a1; /*0x56ee48*/
    ((void (__fastcall *)(_QWORD *__return_ptr))loc_570514)(v47); /*0x56ee50*/
    v71 = &v12; /*0x56ee54*/
    v3 = sub_58BF88(v47); /*0x56ee60*/
    v4 = sub_20C7E8(v47); /*0x56ee68*/
    sub_11328C(v83, v3, v4); /*0x56ee78*/
    v5 = (char *)v83 + *(_QWORD *)(*v83 - 176); /*0x56ee8c*/
    sub_B6704(v42, &byte_7AF000); /*0x56ee9c*/
    sub_B6704(v41, &byte_34073); /*0x56eeac*/
    sub_145800(v82, v5, v42[0], v42[1], 0, v41[0], v41[1]); /*0x56eed4*/
    sub_F7474(v81, 48); /*0x56eee8*/
    v6 = sub_CE5AC(v81); /*0x56eefc*/
    v7 = ((__int64 (__fastcall *)(__int64))loc_572344)(v48); /*0x56ef04*/
    v8 = 1513971592; /*0x56ef0c*/
    while ( v8 != -2112022474 ) /*0x56ef24*/
    {
      switch ( v8 ) /*0x56ef38*/
      {
        case -2066626733: /*0x56ef38*/
          sub_58BF78(v7, v7); /*0x56f060*/
        case -1993925495: /*0x56ef38*/
          v8 = -2066626733; /*0x56f054*/
          break;
        case -1462948831: /*0x56ef38*/
          v8 = -560766175; /*0x56f070*/
          break;
        case -1168329632: /*0x56ef38*/
          if ( v9 ) /*0x56f0c8*/
            v8 = -1993925495; /*0x56f0cc*/
          else
            v8 = 1912740979; /*0x56f0cc*/
          break;
        case -560766175: /*0x56ef38*/
          v9 = (*(_DWORD *)sub_56E4B4 & 0xFC000000) == 335544320 || (*(_DWORD *)sub_56E4B4 & 0xFFE00000) == -736100352; /*0x56f0a8*/
          v8 = -1168329632; /*0x56f0ac*/
          break;
        case 1147398356: /*0x56ef38*/
          v8 = -1462948831; /*0x56f048*/
          break;
        case 1225293591: /*0x56ef38*/
          v8 = 1147398356; /*0x56f03c*/
          break;
        case 1513971592: /*0x56ef38*/
          v8 = 1225293591; /*0x56f030*/
          break;
        default:
          if ( (loc_56E4B8 & 0xFFFFFC00) == -702611456 || (loc_56E4BC & 0xFFFFFC00) == -702611456 ) /*0x56f120*/
            v8 = -1993925495; /*0x56f124*/
          else
            v8 = -2112022474; /*0x56f124*/
          break;
      }
    }
    __memcpy_chk(v6, v7, 32, -1); /*0x56f170*/
    sub_CE5AC(v81); /*0x56f17c*/
    sub_2195C4(v48 + 32); /*0x56f18c*/
    JUMPOUT(0x56F3E8); /*0x56f3e8*/
  }
  _ReadStatusReg(TPIDR_EL0); /*0x570458*/
  abort(); /*0x57046c*/
}