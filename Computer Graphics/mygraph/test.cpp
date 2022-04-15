#include "./mygraph.cpp" 
#include <cstring>
#include <vector>

const int WINSIZE = 1024;

void makeTube(const std::vector <V3d> &v, std::vector <L3d> &line)
{
	line.clear();

	line.push_back((L3d){v[0], v[1]});
	line.push_back((L3d){v[1], v[2]});
	line.push_back((L3d){v[2], v[3]});
	line.push_back((L3d){v[3], v[0]});
	
	line.push_back((L3d){v[4], v[5]});
	line.push_back((L3d){v[5], v[6]});
	line.push_back((L3d){v[6], v[7]});
	line.push_back((L3d){v[7], v[4]});

	line.push_back((L3d){v[0], v[4]});
	line.push_back((L3d){v[1], v[5]});
	line.push_back((L3d){v[2], v[6]});
	line.push_back((L3d){v[3], v[7]});
}

void draw()
{
	// // 坐标系
	// drawLine(-512, 0, 0, 512, 0, 0, WHITE);
	// drawLine(0, -512, 0, 0, 512, 0, WHITE);
    // drawLine(0, 0, -512, 0, 0, 512, WHITE);
	// // 立方体顶点
	// std::vector <V3d> v;
	// v.push_back((V3d){-100, -100, -100});
	// v.push_back((V3d){-100, 100, -100});
	// v.push_back((V3d){100, 100, -100});
	// v.push_back((V3d){100, -100, -100});
	// v.push_back((V3d){-100, -100, 100});
	// v.push_back((V3d){-100, 100, 100});
	// v.push_back((V3d){100, 100, 100});
	// v.push_back((V3d){100, -100, 100});
	// // 绘制立方体
	// std::vector <L3d> line;
	// makeTube(v, line);
	// drawPolyhedron(line, RED);
	// // 三维变换
	// rotateDY(v, 40);
	// translateX(v, 100);
	// rotateDY(v, -40);
	// // 绘制立方体
	// makeTube(v, line);
	// drawPolyhedron(line, YELLOW);

	// std::vector<V2d> lineA, lineB;
	// lineA.push_back((V2d){ 100, 300 });  // A
	// lineA.push_back((V2d){ 120, 200 });  // B
	// lineA.push_back((V2d){ 220, 200 });  // C
	// lineA.push_back((V2d){ 270, 100 });  // D
	// lineB.push_back((V2d){ 270, 100 });  // D

	// // lineB.push_back((V2d){ 370, 100 });  // OLD E
	// lineB.push_back((V2d){ 320, 0 });  // NEW E

	// // lineB.push_back((V2d){ 420, 200 });  // OLD F
	// lineB.push_back((V2d){ 320, -200 });  // NEW F

	// lineB.push_back((V2d){ 420, 300 });  // G
	// drawBezier(lineA, 500, WHITE);
	// drawBezier(lineB, 500, WHITE);
	// drawLines(lineA, YELLOW);
	// drawLines(lineB, YELLOW);

	// drawLine(120, 400, 420, -200, RED);  // E 点所在直线。
	// drawLine(20, 400, 420, -400, GREEN);  // F 点所在直线。

	// std::vector<V2d> poly1({{100, 100}, {100, 300}, {300, 300}, {300, 100}}); // 多边形1
	// std::vector<V2d> poly2({{120, 120}, {120, 280}, {280, 280}, {280, 120}}); // 多边形2
	// fillPolygon(poly1, RED); // 填充内部
	// fillPolygon(poly2, BLACK); // 填充内部
	// drawPolygon(poly1, YELLOW); // 绘制边界
	// drawPolygon(poly2, YELLOW); // 绘制边界

	

	// std::vector<L2d> poly({
	// 	{{100, 50}, {80, 330}},
	// 	{{80, 330}, {350, 280}},
	// 	{{350, 280}, {350, 80}},
	// 	{{350, 80}, {100, 50}}
	// });

	
	// drawLine(-500, 0, 500, 0, WHITE); // 坐标系 X 轴
	// drawLine(0, -500, 0, 500, WHITE); // 坐标系 Y 轴
	// std::vector<L2d> poly({
	// 	{{100, 100}, {100, 300}},
	// 	{{100, 300}, {300, 300}},
	// 	{{300, 300}, {300, 100}},
	// 	{{300, 100}, {100, 100}},
	// 	// {{100, 100}, {120, 120}},
	// 	{{120, 120}, {120, 280}},
	// 	{{120, 280}, {280, 280}},
	// 	{{280, 280}, {280, 120}},
	// 	{{280, 120}, {120, 120}},
	// 	// {{120, 120}, {100, 100}}
	// });
	// drawPolygon(poly, YELLOW);
	// fillPolygon(poly, RED);

	// drawLine((V2d) {0, 0}, (V2d) {0, 10}, YELLOW);

	// 坐标系
	drawLine(-500, 0, 500, 0, WHITE);
	drawLine(0, -500, 0, 500, WHITE);
	// 多边形
	std::vector <V2d> polygon({
		(V2d) {0, 0},
		(V2d) {250, 250},
		(V2d) {250, 0},
		(V2d) {0, 250},
		(V2d) {0, 0}
	});
	// 绘制多边形
	drawLines(polygon, YELLOW);
	// 二维变换
	shearX(polygon, 1.5);
	// 绘制多边形
	drawLines(polygon, WHITE);
}
int main(int argc, char **argv)
{
	char name[16];
	strncpy(name, "EqnoGL", strlen(name));
    // myinit3d(argc, argv, WINSIZE, WINSIZE, WINSIZE / 2, 0, 0, 0, 0, 0, draw, name);
    myinit2d(argc, argv, WINSIZE, WINSIZE, WINSIZE / 2, 0, 0, 0, 0, draw, name);
	return 0;
}

/*
void putpixel(int x, int y, int z) {}
void putpixel(int x, int y, int z, int c) {}
int _abs(int x) { return 0; }
int _max(int x, int y) { return 0; }
int _max(int x, int y, int z) { return 0; }
void _swap(int x, int y) {}
double sqrt(double x) { return x; }
const double pi = 1;
double sin(double x) { return x; }
double cos(double x) { return x; }
struct V2d { int x, y; };
struct L2d { V2d a, b; };
struct V3d { int x, y, z; };
struct L3d { V3d a, b; };
#include <vector>
#include <stack>
#include <unordered_set>
#include "../get/line2d/bresenhamEx.cpp"
const int hashSeed = 17;
const int INF = 0x3f3f3f3f;
*/