void drawPolyhedron(const std::vector<V3d> &vertex, int color)
{
	int len = vertex.size();
	for (int i=0; i<vertex.size(); i++)
		drawLine(vertex[i].x, vertex[i].y, vertex[i].z, 
			vertex[(i+1+len)%len].x, vertex[(i+1+len)%len].y, vertex[(i+1+len)%len].z, color);
}
void drawPolyhedron(const std::vector<L3d> &line, int color)
{ for (auto i: line) drawLine(i, color); }
