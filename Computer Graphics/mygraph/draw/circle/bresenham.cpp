void drawCircle(int x, int y, int r, int color)
{
	int d = 1-r, tx = 0, ty = r;
	while (tx <= ty)
	{
		putpixel(x+tx, y+ty, color);
		putpixel(x-tx, y+ty, color);
		putpixel(x+tx, y-ty, color);
		putpixel(x-tx, y-ty, color);
		putpixel(y+ty, x+tx, color);
		putpixel(y-ty, x+tx, color);
		putpixel(y+ty, x-tx, color);
		putpixel(y-ty, x-tx, color);
		if (d <= 0) d += 2*tx+3, tx ++;
		else d += 2*(tx-ty)+5, tx ++, ty--;
	}
}
