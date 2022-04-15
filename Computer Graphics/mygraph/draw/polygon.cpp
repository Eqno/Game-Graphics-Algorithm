void drawPolygon(const std::vector<V2d> &vertex, int color)
{
	int len = vertex.size();
	for (int i=0; i<vertex.size(); i++)
		drawLine(vertex[i].x, vertex[i].y, 
			vertex[(i+1+len)%len].x, vertex[(i+1+len)%len].y, color);
}
void drawPolygon(const std::vector<L2d> &line, int color)
{ for (auto i: line) drawLine(i, color); }
