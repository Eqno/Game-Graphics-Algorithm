void transform(std::vector <V3d> &v, 
	double a, double b, double c, double d, double e, double f,
	double g, double h, double i, int l, int m, int n, 
	double p, double q, double r, double s)
{
	for (int j=0; j<v.size(); j++)
	{
		double x = v[j].x*a+v[j].y*d+v[j].z*g+l;
		double y = v[j].x*b+v[j].y*e+v[j].z*h+m;
		double z = v[j].x*c+v[j].y*f+v[j].z*i+n;
		double e = v[j].x*p+v[j].y*q+v[j].z*r+s;
		x /= e, y /= e, z /= e;
		v[j].x = x, v[j].y = y, v[j].z = z;
	}
}
void translateX(std::vector <V3d> &v, int l)
{ transform(v, 1, 0, 0, 0, 1, 0, 0, 0, 1, l, 0, 0, 0, 0, 0, 1); }
void translateY(std::vector <V3d> &v, int m)
{ transform(v, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, m, 0, 0, 0, 0, 1); }
void translateZ(std::vector <V3d> &v, int n)
{ transform(v, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, n, 0, 0, 0, 1); }
void translate(std::vector <V3d> &v, int l, int m, int n)
{ transform(v, 1, 0, 0, 0, 1, 0, 0, 0, 1, l, m, n, 0, 0, 0, 1); }

void scale(std::vector <V3d> &v, double s)
{ transform(v, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1/s); }
void scaleX(std::vector <V3d> &v, double a)
{ transform(v, a, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1); }
void scaleY(std::vector <V3d> &v, double e)
{ transform(v, 1, 0, 0, 0, e, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1); }
void scaleZ(std::vector <V3d> &v, double i)
{ transform(v, 1, 0, 0, 0, 1, 0, 0, 0, i, 0, 0, 0, 0, 0, 0, 1); }
void scale(std::vector <V3d> &v, double a, double e, double i)
{ transform(v, a, 0, 0, 0, e, 0, 0, 0, i, 0, 0, 0, 0, 0, 0, 1); }

void rotateRX(std::vector <V3d> &v, double angle)
{
	double c = cos(angle), s = sin(angle);
	transform(v, 1, 0, 0, 0, c, s, 0, -s, c, 0, 0, 0, 0, 0, 0, 1);
}
void rotateX(std::vector <V3d> &v, double angle)
{ rotateRX(v, angle); }
void rotateRY(std::vector <V3d> &v, double angle)
{
	double c = cos(angle), s = sin(angle);
	transform(v, c, 0, -s, 0, 1, 0, s, 0, c, 0, 0, 0, 0, 0, 0, 1);
}
void rotateY(std::vector <V3d> &v, double angle)
{ rotateRY(v, angle); }
void rotateRZ(std::vector <V3d> &v, double angle)
{
	double c = cos(angle), s = sin(angle);
	transform(v, c, s, 0, -s, c, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1);
}
void rotateZ(std::vector <V3d> &v, double angle)
{ rotateRZ(v, angle); }
void rotateDX(std::vector <V3d> &v, double angle)
{ rotateX(v, angle*atan(1)/45); }
void rotateDY(std::vector <V3d> &v, double angle)
{ rotateY(v, angle*atan(1)/45); }
void rotateDZ(std::vector <V3d> &v, double angle)
{ rotateZ(v, angle*atan(1)/45); }

void symX(std::vector <V3d> &v)
{ transform(v, 1, 0, 0, 0, -1, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 1); }
void symY(std::vector <V3d> &v)
{ transform(v, -1, 0, 0, 0, 1, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 1); }
void symZ(std::vector <V3d> &v)
{ transform(v, -1, 0, 0, 0, -1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1); }
void symXOY(std::vector <V3d> &v)
{ transform(v, 1, 0, 0, 0, 1, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 1); }
void symYOZ(std::vector <V3d> &v)
{ transform(v, -1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1); }
void symZOX(std::vector <V3d> &v)
{ transform(v, 1, 0, 0, 0, -1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1); }
void symO(std::vector <V3d> &v)
{ transform(v, -1, 0, 0, 0, -1, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 1); }

void shearX(std::vector <V3d> &v, double d, double g)
{ transform(v, 1, 0, 0, d, 1, 0, g, 0, 1, 0, 0, 0, 0, 0, 0, 1); }
void shearY(std::vector <V3d> &v, double b, double h)
{ transform(v, 1, b, 0, 0, 1, 0, 0, h, 1, 0, 0, 0, 0, 0, 0, 1); }
void shearZ(std::vector <V3d> &v, double c, double f)
{ transform(v, 1, 0, c, 0, 1, f, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1); }
void shear(std::vector <V3d> &v, double d, double g, double b, double h, double c, double f)
{ transform(v, 1, b, c, d, 1, f, g, h, 1, 0, 0, 0, 0, 0, 0, 1); }
