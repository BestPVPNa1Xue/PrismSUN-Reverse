__int64 sub_785B94()
{
  __int64 result; // x0
  char s1[92]; // [xsp+4h] [xbp-6Ch] BYREF

  result = getauxval(0x10u); /*0x785ba4*/
  if ( (result & 0x100) != 0 ) /*0x785ba8*/
  {
    result = __system_property_get("ro.arch", s1); /*0x785bd0*/
    if ( (int)result <= 0 ) /*0x785bd8*/
    {
      unk_7D1BB0 = 1; /*0x785c1c*/
    }
    else
    {
      result = strncmp(s1, "exynos9810", 0xAu); /*0x785bec*/
      unk_7D1BB0 = (_DWORD)result != 0; /*0x785c00*/
    }
  }
  else
  {
    unk_7D1BB0 = 0; /*0x785bb4*/
  }
  return result; /*0x785bc0*/
}