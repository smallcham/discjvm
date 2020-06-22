unsigned short  l2b_2(unsigned short x)
{
    return ((x & 0x00ffu) << 8u) | ((x & 0xff00u) >> 8u);
}

unsigned int l2b_4(unsigned int x)
{
    return ((x & 0x000000ffu) << 24u) |
           ((x & 0x0000ff00u) << 8u) |
           ((x & 0x00ff0000u) >> 8u) |
           ((x & 0xff000000u) >> 24u);
}
unsigned long long l2b_8(unsigned long long x)
{
    return ((x & 0x00000000000000ffu) << 56u) |
           ((x & 0x000000000000ff00u) << 40u) |
           ((x & 0x0000000000ff0000u) << 24u) |
           ((x & 0x00000000ff000000u) << 8u)|
           ((x & 0x000000ff00000000u) >> 8u)|
           ((x & 0x0000ff0000000000u) >> 24u)|
           ((x & 0x00ff000000000000u) >> 40u)|
           ((x & 0xff00000000000000u) >> 56u);
}
