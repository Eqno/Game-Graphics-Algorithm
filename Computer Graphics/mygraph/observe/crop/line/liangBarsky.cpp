bool clip(double p, double q, double &tl, double &tu)
{
	bool flag = true;
	double r = q / p;
	if (p < 0)
	{
		if (r > tu) flag = false;
		else if (r > tl) tl = r;
	}
	else if (p > 0) 
	{
		if (r < tl) flag = false;
		else if (r < tu) tu = r;
	}
	else if (q < 0) flag = false;
	return flag;
}
void cropLine(int l, int r, int b, int t,
	int &x1, int &y1, int &x2, int &y2)
{
	double dx = x2-x1, dy = y2-y1, tl = 0, tu = 1;
	if (clip(-dx, x1-l, tl, tu)
		&& clip(dx, r-x1, tl, tu)
		&& clip(-dy, y1-b, tl, tu)
		&& clip(dy, t-y1, tl, tu))
	{
		if (tu < 1) x2 = x1+tu*dx+0.5, y2 = y1+tu*dy+0.5;
		if (tl > 0) x1 = x1+tl*dx+0.5, y1 = y1+tl*dy+0.5;
	}
	else x1 = x2 = l, y1 = y2 = b;
}
