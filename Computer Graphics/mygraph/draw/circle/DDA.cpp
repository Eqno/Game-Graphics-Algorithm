void drawCircle(int x, int y, int r, int color)
{
	const double del = 1./r;
	double tx = r, ty = 0;
	for (double i=0; i<=2*pi; i+=del)
	{
		putpixel(x+tx+0.5, y+ty+0.5, color);
		tx -= ty*del, ty += tx*del;
	}
}
