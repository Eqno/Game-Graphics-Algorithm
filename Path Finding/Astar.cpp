#include <queue>
#include <vector>
#include <iostream>
using namespace std;

// 正着走一格距离是 4，斜着走一格距离是 14
const int DIS_STRAIGHT = 4, DIS_DIAGONAL = 14;
const int HEIGHT = 30, WIDTH = 100, MAXDEP = 2000;
int depth, mapp[HEIGHT][WIDTH], close[HEIGHT+1][WIDTH+1];

// 八个方向
const int dir[8][2] = {
    {1,0}, {0,1}, {-1,0}, {0,-1},
    {1,1}, {-1,1}, {-1,-1}, {1,-1}
};

// 八个耗费
const int cost[8] = {
    DIS_STRAIGHT, DIS_STRAIGHT, DIS_STRAIGHT, DIS_STRAIGHT,
    DIS_DIAGONAL, DIS_DIAGONAL, DIS_DIAGONAL, DIS_DIAGONAL
};

// Node 类
struct Node
{
    int x, y;       // 点坐标
    int g, f;       // 优先级 = 耗费值 + 预测值
    int father;     // 父节点索引
    Node(int px, int py, int ex, int ey, int g, int father):
    x(px), y(py), g(g), father(father)
    {
        int disX = abs(ex - px), disY = abs(ey - py);   // 偏移量
        f = DIS_DIAGONAL * max(disX, disY)              // 优先级
            - DIS_STRAIGHT * abs(disX - disY) + g;
    }
};
vector<Node> node;

// cmp 类
struct Cmp
{
    bool operator()(int a, int b)                 // 优先级排序
    { return node[a].f > node[b].f; }
};
priority_queue<int, vector<int>, Cmp> open;

// 判断是否能走
inline bool judgeClose(int x, int y)
{ return x<0 || y<0 || x>=HEIGHT || y>=WIDTH || close[x][y]; }

// push 新点
void update(int p, int ex, int ey)
{
    int x = node[p].x, y = node[p].y;                   // 点坐标
    if (judgeClose(x, y)) return;                       // 不能走
    close[x][y] = 1;                                    // 能走
    for (int i=0; i<8; i++)                             // 继续查找
    {
        node.emplace_back(                              // 加入 node
            Node(
                x + dir[i][0], y + dir[i][1],
                ex, ey, node[p].g + cost[i], p
            )
        );
        open.push(node.size()-1);                       // 加入 open
    }
}

// bfs，不解释了
vector<int> findPath(int startX, int startY, int endX, int endY)
{
    node.emplace_back(Node(startX, startY, endX, endY, 0, -1));
    open.push(node.size()-1);
    while (open.size())
    {
        depth ++;
        if (depth >= MAXDEP) return {};
        int p = open.top(); open.pop();
        if (node[p].x == endX && node[p].y == endY)
        {
            vector<int> path;
            for (int i=p; i!=-1; i=node[i].father)
                path.push_back(i);
            return path;
        }
        update(p, endX, endY);
    }
    return {};
}

// 生成地图，对于每个点，五分之一概率出现障碍
void generateMap()
{
    for (int i=0; i<HEIGHT; i++)
        for (int j=0; j<WIDTH; j++)
        {
            if (rand()%5 == 0)
            {
                mapp[i][j] = '*';
                close[i][j] = 1;   
            }
            else mapp[i][j] = ' ';
        }
}

// 输出地图
void printMap()
{
    for (int i=0; i<HEIGHT; i++)
    {
        for (int j=0; j<WIDTH; j++)
            printf("%c", mapp[i][j]);
        putchar('\n');
    }
}

int main()
{
    generateMap();                                      // 生成地图
    int startX = 0, startY = 0, endX = 29, endY = 99;   // 起点终点
    mapp[startX][startY] = mapp[endX][endY] = ' ';      // 保证能走
    close[startX][startY] = close[endX][endY] = 0;
    vector<int> path = findPath(startX, startY, endX, endY);
    for (int i: path) mapp[node[i].x][node[i].y] = 'o'; // 标记路径
    printMap();
    return 0;
}