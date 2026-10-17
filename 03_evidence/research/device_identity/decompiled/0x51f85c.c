// positive sp value has been detected, the output may be wrong!
__int64 __fastcall sub_51F85C(__int64 result, __int64 a2)
{
  __int64 v2; // x19
  __int64 v3; // x20
  int v4; // [xsp-4h] [xbp-2Ch]

  _ReadStatusReg(TPIDR_EL0); /*0x51f86c*/
  v4 = 1143282330; /*0x51f880*/
  while ( v4 != -914055923 ) /*0x51f8c4*/
  {
    if ( v4 == 1143282330 ) /*0x51f914*/
    {
      v4 = 1768497275; /*0x51f9a4*/
    }
    else
    {
      v2 = result; /*0x51f9d8*/
      v3 = a2; /*0x51f9e4*/
      sub_56C57C(); /*0x51f9ec*/
      result = v2; /*0x51f9f0*/
      a2 = v3; /*0x51f9f4*/
      v4 = -914055923; /*0x51fa04*/
    }
  }
  _ReadStatusReg(TPIDR_EL0); /*0x51fa0c*/
  return result; /*0x51fa2c*/
}