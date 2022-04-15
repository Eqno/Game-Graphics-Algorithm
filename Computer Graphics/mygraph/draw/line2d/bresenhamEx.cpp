void drawX(int i, int x1, int y1, int x2, int y2, int color)
{
	int dx = i*(x1-x2), dy = y2-y1;
	for (int f=dx; x1!=x2; x1+=i)
	{
		putpixel(x1, y1, color);
		f += dy + dy;
		if (f > 0) y1 ++, f += dx + dx;
	}
}
void drawY(int i, int x1, int y1, int x2, int y2, int color)
{
	int dx = x2-x1, dy = i*(y1-y2);
	for (int f=dy; y1!=y2; y1+=i)
	{
		putpixel(x1, y1, color);
		f += dx + dx;
		if (f > 0) x1 ++, f += dy + dy;
	}
}
void drawLine(int x1, int y1, int x2, int y2, int color)
{
	if (_abs(x2-x1) > _abs(y2-y1))
	{
		if (y1 > y2) _swap(x1, x2), _swap(y1, y2);
		if (x2 > x1) drawX(1, x1, y1, x2, y2, color);
		else drawX(-1, x1, y1, x2, y2, color);
	}
	else
	{
		if (x1 > x2) _swap(x1, x2), _swap(y1, y2);
		if (y2 > y1) drawY(1, x1, y1, x2, y2, color);
		else drawY(-1, x1, y1, x2, y2, color);
	}
}
void drawLine(const V2d &a, const V2d &b, int color)
{ drawLine(a.x, a.y, b.x, b.y, color); }
void drawLine(const L2d &p, int color)
{ drawLine(p.a, p.b, color); }
void drawLines(const std::vector<V2d> &v, int color)
{
	for (int i=1; i<v.size(); i++)
		drawLine(v[i], v[i-1], color);
}