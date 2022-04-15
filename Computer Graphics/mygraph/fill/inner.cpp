void fillPolygonByInnerPoint(const std::vector<V2d> point, int color)
{
    for (auto i: point)
        putpixel(i.x, i.y, color);
}