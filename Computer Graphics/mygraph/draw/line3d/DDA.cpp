void drawLine(double x1, double y1, double z1, double x2, double y2, double z2, int color)
{
	double dx = x2-x1, dy = y2-y1, dz = z2-z1, step = _max(_abs(dx), _abs(dy), _abs(dz)), 
		   xi = dx / step, yi = dy / step, zi = dz / step;
	for (; step --; x1+=xi, y1+=yi, z1+=zi) putpixel(x1+0.5, y1+0.5, z1+0.5, color);
}
void drawLine(const V3d &a, const V3d &b, int color)
{ drawLine(a.x, a.y, a.z, b.x, b.y, b.z, color); }
void drawLine(const L3d &p, int color)
{ drawLine(p.a, p.b, color); }
