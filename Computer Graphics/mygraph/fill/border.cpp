void fillPolygon(const std::vector<L2d> poly, int color)
{
    std::vector<V2d> border;
    for (auto i: poly) getLine(i, border);
    
    std::unordered_set<int> set;
    for (auto i: border) set.insert(i.x*hashSeed+i.y);
    
    int x0 = INF, y0 = INF;
    for (int i=2; i<border.size(); i++)
    {
        int x = (border[i].x+border[i-2].x+1)/2;
        int y = (border[i].y+border[i-2].y+1)/2;
        if (set.find(x*hashSeed+y) == set.end())
        {
            x0 = x;
            y0 = y;
            break;
        }
    }

    if (x0 == INF || y0 == INF) return ;
    // std::cout << x0 << " " << y0 << std::endl;

    std::stack<V2d> stack;
    stack.push((V2d){ x0, y0 });
    while (! stack.empty())
    {
        V2d p = stack.top();
        stack.pop();
        // std::cout << p.x << " " << p.y << std::endl;
        putpixel(p.x, p.y, color);
        set.insert(p.x*hashSeed+p.y);
        if (set.find((p.x-1)*hashSeed+p.y) == set.end()) stack.push((V2d){ p.x-1, p.y });
        if (set.find((p.x+1)*hashSeed+p.y) == set.end()) stack.push((V2d){ p.x+1, p.y });
        if (set.find(p.x*hashSeed+p.y-1) == set.end()) stack.push((V2d){ p.x, p.y-1 });
        if (set.find(p.x*hashSeed+p.y+1) == set.end()) stack.push((V2d){ p.x, p.y+1 });
    }
}