double C(int n, int k)
{
    if (k<0 || k>n) return 0;
    double a = 1;
    for (int i=n; i>n-k; i--) a *= i;
    double b = 1;
    for (int i=k; i>0; i--) b *= i;
    return a / b;
}
void drawBezier(const std::vector<V2d> &v, int acc, int color)
{
    int n = v.size() - 1;
    std::vector<double> c;
    for (int k=0; k<=n; k++)
        c.push_back(C(n, k));
    for (double t=0; t<=1; t+=1.0/acc)
    {
        double x = 0, y = 0;
        for (int k=0; k<=n; k++)
        {
            double b = c[k]*pow(t, k)*pow(1-t, n-k);
            x += v[k].x * b;
            y += v[k].y * b;
        }
        putpixel(x+0.5, y+0.5, color);   
    }
}