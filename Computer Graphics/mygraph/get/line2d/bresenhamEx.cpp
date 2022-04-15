void getX(int i, int x1, int y1, int x2, int y2, std::vector<V2d> &res)
{
	int dx = i*(x1-x2), dy = y2-y1;
	for (int f=dx; x1!=x2; x1+=i)
	{
		res.push_back((V2d){ x1, y1 });
		f += dy + dy;
		if (f > 0)
		{
			y1 ++;
			f += dx + dx;
		}
	}
}
void getY(int i, int x1, int y1, int x2, int y2, std::vector<V2d> &res)
{
	int dx = x2-x1, dy = i*(y1-y2);
	for (int f=dy; y1!=y2; y1+=i)
	{
		res.push_back((V2d){ x1, y1 });
		f += dx + dx;
		if (f > 0)
		{
			x1 ++;
			f += dy + dy;
		}
	}
}
void getLine(int x1, int y1, int x2, int y2, std::vector<V2d> &res)
{
	if (_abs(x2-x1) > _abs(y2-y1))
	{
		if (y1 > y2) _swap(x1, x2), _swap(y1, y2);
		if (x2 > x1) getX(1, x1, y1, x2, y2, res);
		else getX(-1, x1, y1, x2, y2, res);
	}
	else
	{
		if (x1 > x2) _swap(x1, x2), _swap(y1, y2);
		if (y2 > y1) getY(1, x1, y1, x2, y2, res);
		else getY(-1, x1, y1, x2, y2, res);
	}
}
void getLine(const V2d &a, const V2d &b, std::vector<V2d> &res)
{ getLine(a.x, a.y, b.x, b.y, res); }
void getLine(const L2d &p, std::vector<V2d> &res)
{ getLine(p.a, p.b, res); }
void getLines(const std::vector<V2d> &v, std::vector<V2d> &res)
{
	for (int i=1; i<v.size(); i++)
		getLine(v[i], v[i-1], res);
}