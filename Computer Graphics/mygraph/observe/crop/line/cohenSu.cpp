#define u8 unsigned char
int L, R, B, T;
u8 encode(int x, int y)
{
	u8 c = 0;
	if (x < L) c |= 1;
	if (x > R) c |= 2;
	if (y < B) c |= 4;
	if (y > T) c |= 8;
	return c;
}
#define process(c, x, y) \
do { \
	if (1&c) y=y1+(y2-y1)*(L-x1)/(x2-x1), x=L, c=encode(x, y); \
	if (2&c) y=y1+(y2-y1)*(R-x1)/(x2-x1), x=R, c=encode(x, y); \
    if (4&c) x=x1+(x2-x1)*(B-y1)/(y2-y1), y=B, c=encode(x, y); \
    if (8&c) x=x1+(x2-x1)*(T-y1)/(y2-y1), y=T, c=encode(x, y); \
} while (0)
void cropLine(int l, int r, int b, int t,
	int &x1, int &y1, int &x2, int &y2)
{
	L = l, R = r, B = b, T = t;
	u8 c1 = encode(x1, y1), c2 = encode(x2, y2);
    if (c1 & c2) return ;
    process(c1, x1, y1);
   	process(c2, x2, y2);
}
#undef process(c, x, y)
#undef uc
