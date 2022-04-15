void transform(std::vector <V2d> &v, 
	double a, double b, double c, double d,
	int l, int m, double p, double q, double s)
{
	for (int i=0; i<v.size(); i++)
	{
		double x = v[i].x*a+v[i].y*c+l;
		double y = v[i].x*b+v[i].y*d+m;
		double e = v[i].x*p+v[i].y*q+s;
		x /= e, y /= e;
		v[i].x = x, v[i].y = y;
	}
}
void translateX(std::vector <V2d> &v, int l)
{ transform(v, 1, 0, 0, 1, l, 0, 0, 0, 1); }
void translateY(std::vector <V2d> &v, int m)
{ transform(v, 1, 0, 0, 1, 0, m, 0, 0, 1); }
void translate(std::vector <V2d> &v, int l, int m)
{ transform(v, 1, 0, 0, 1, l, m, 0, 0, 1); }

void scale(std::vector <V2d> &v, double s)
{ transform(v, 1, 0, 0, 1, 0, 0, 0, 0, 1/s); }
void scaleX(std::vector <V2d> &v, double a)
{ transform(v, a, 0, 0, 1, 0, 0, 0, 0, 1); }
void scaleY(std::vector <V2d> &v, double d)
{ transform(v, 1, 0, 0, d, 0, 0, 0, 0, 1); }
void scale(std::vector <V2d> &v, double a, double d)
{ transform(v, a, 0, 0, d, 0, 0, 0, 0, 1); }

void rotateR(std::vector <V2d> &v, double angle)
{
	double c = cos(angle), s = sin(angle);
	transform(v, c, s, -s, c, 0, 0, 0, 0, 1);
}
void rotateD(std::vector <V2d> &v, double angle)
{
	angle = angle/45*atan(1);
	double c = cos(angle), s = sin(angle);
	transform(v, c, s, -s, c, 0, 0, 0, 0, 1);
}

void symX(std::vector <V2d> &v)
{ transform(v, -1, 0, 0, 1, 0, 0, 0, 0, 1); }
void symY(std::vector <V2d> &v)
{ transform(v, 1, 0, 0, -1, 0, 0, 0, 0, 1); }
void symO(std::vector <V2d> &v)
{ transform(v, -1, 0, 0, -1, 0, 0, 0, 0, 1); }
void symYX(std::vector <V2d> &v)
{ transform(v, 0, 1, 1, 0, 0, 0, 0, 0, 1); }
void symYOX(std::vector <V2d> &v)
{ transform(v, 0, -1, -1, 0, 0, 0, 0, 0, 1); }

void shearX(std::vector <V2d> &v, double c)
{ transform(v, 1, 0, c, 1, 0, 0, 0, 0, 1); }
void shearY(std::vector <V2d> &v, double b)
{ transform(v, 1, b, 0, 1, 0, 0, 0, 0, 1); }
void shear(std::vector <V2d> &v, double c, double b)
{ transform(v, 1, b, c, 1, 0, 0, 0, 0, 1); }