void drawEllipse(int x, int y, int a, int b, int color)
{
	int d = b*b+a*a*(-b+0.25), tx = 0, ty = b;
	while (b*b*(tx+1) < a*a*(ty-0.5))
	{
		putpixel(x+tx+0.5, y+ty+0.5, color);
		putpixel(x-tx+0.5, y+ty+0.5, color);
		putpixel(x+tx+0.5, y-ty+0.5, color);
		putpixel(x-tx+0.5, y-ty+0.5, color);
		if (d <= 0) d += b*b*(2*tx+3), tx ++;
		else d += b*b*(2*tx+3)+a*a*(-2*ty+2), tx ++, ty--;
	}
	d = b*b*(tx+0.5)*(tx+0.5)+a*a*(ty-1)*(ty-1)-a*a*b*b;
	while (ty >= 0)
	{
		putpixel(x+tx+0.5, y+ty+0.5, color);
		putpixel(x-tx+0.5, y+ty+0.5, color);
		putpixel(x+tx+0.5, y-ty+0.5, color);
		putpixel(x-tx+0.5, y-ty+0.5, color);
		if (d > 0) d += a*a*(-2*ty+3), ty --;
		else d += b*b*(2*tx+2)+a*a*(-2*ty+3), tx ++, ty --;
	}
}
