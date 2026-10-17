void sub_7861C8()
{
  __int64 v0; // x30
  unsigned __int64 v1; // x19
  _QWORD v2[14]; // [xsp+0h] [xbp-70h] BYREF

  if ( !unk_7D1BB8 ) /*0x7861d4*/
  {
    v2[12] = v0; /*0x7861e4*/
    if ( (int)__system_property_get("ro.arch", v2) <= 0 || strncmp((const char *)v2, "exynos9810", 0xAu) ) /*0x786210*/
    {
      v1 = getauxval(0x10u); /*0x786220*/
      v2[2] = getauxval(0x1Au); /*0x786230*/
      v2[0] = 24; /*0x78623c*/
      v2[1] = v1; /*0x78623c*/
      sub_785C2C(v1 | 0x4000000000000000LL, v2); /*0x786240*/
    }
  }
}