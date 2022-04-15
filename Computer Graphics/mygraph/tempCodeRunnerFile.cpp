std::vector <V3d> v;
	v.push_back((V3d){-100, -100, -100});
	v.push_back((V3d){-100, 100, -100});
	v.push_back((V3d){100, 100, -100});
	v.push_back((V3d){100, -100, -100});
	v.push_back((V3d){-100, -100, 100});
	v.push_back((V3d){-100, 100, 100});
	v.push_back((V3d){100, 100, 100});
	v.push_back((V3d){100, -100, 100});
	std::vector <L3d> line;
	makeTube(v, line);
	drawPolyhedron(line, RED);
	rotateDX(v, 30);
	scale(v, 2);
	makeTube(v, line);
	drawPolyhedron(line, YELLOW);