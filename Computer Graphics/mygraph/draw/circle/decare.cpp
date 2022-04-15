void drawCircle(int x, int y, int r, int color)
{
	for (int i=x; i<=x+r; i++)
	{
		int j = sqrt(r*r-(i-x)*(i-x))+y+0.5;
		putpixel(i, j, color);
		putpixel(j, i, color);
		putpixel(2*x-i, j, color);
		putpixel(j, 2*y-i, color);
		putpixel(i, 2*y-j, color);
		putpixel(2*y-j, i, color);
		putpixel(2*x-i, 2*y-j, color);
		putpixel(2*y-j, 2*x-i, color);
	}
}
