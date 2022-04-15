void drawCircle(int x, int y, int r, int n, int color)
{
	for (int k=0; k<=n; k++)
	{
		int i = x+r*cos(2*pi*k/n), j = y+r*sin(2*pi*k/n);
		putpixel(i+0.5, j+0.5, color);
	}
}
