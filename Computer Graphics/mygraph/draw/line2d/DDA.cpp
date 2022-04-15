void drawLine(double x1, double y1, double x2, double y2, int color)
{
	double dx = x2-x1, dy = y2-y1, step = _max(_abs(dx), _abs(dy)),
		xi = dx / step, yi = dy / step;
	for (; step --; x1+=xi, y1+=yi) putpixel(x1+0.5, y1+0.5, color);
}
void drawLine(const V2d &a, const V2d &b, int color)
{ drawLine(a.x, a.y, b.x, b.y, color); }
void drawLine(const L2d &p, int color)
{ drawLine(p.a, p.b, color); }


