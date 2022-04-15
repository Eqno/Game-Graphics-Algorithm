void drawX(int i, int x1, int y1, int x2, int y2, int color)
{
	int dx = x2-x1, dy = y2-y1;
	int f = dx + (i?-2:2)*dy;
	while (x1 != x2)
	{
		putpixel(x1, y1, color);
		if (f < 0)
		{
			y1 += !i;
			f += i ? (2*dy) : (2*dx-2*dy);
		}
		else
		{
			y1 += i;
			f += i ? (2*dx+2*dy) : (-2*dy);
		}
		x1 += i ? -1 : 1;
	}
}
void drawY(int i, int x1, int y1, int x2, int y2, int color)
{
	int dx = x2-x1, dy = y2-y1;
	int f = (i?-2:2)*dx -dy;
	while (y1 != y2)
	{
		putpixel(x1, y1, color);
		if (f < 0)
		{
			x1 += i;
			f += i ? (-2*dx-2*dy) : (2*dx);
		}
		else
		{
			x1 += !i;
			f += i ? (-2*dx) : (2*dx-2*dy);
		}
		y1 += i ? -1 : 1;
	}
}
void drawLine(int x1, int y1, int x2, int y2, int color)
{
	if (_abs(x2-x1) > _abs(y2-y1))
	{
		if (y1 > y2) _swap(x1, x2), _swap(y1, y2);
		if (x2 > x1) drawX(0, x1, y1, x2, y2, color);
		else drawX(1, x1, y1, x2, y2, color);
	}
	else
	{
		if (x1 > x2) _swap(x1, x2), _swap(y1, y2);
		if (y2 > y1) drawY(0, x1, y1, x2, y2, color);
		else drawY(1, x1, y1, x2, y2, color);
	}
}
void drawLine(const V2d &a, const V2d &b, int color)
{ drawLine(a.x, a.y, b.x, b.y, color); }
void drawLine(const L2d &p, int color)
{ drawLine(p.a, p.b, color); }
