#include <iostream>
using namespace std;

#define MaxInt 32767 // 表示极大值，即∞
#define MVNum 100     // 最大顶点数

// 顶点的数据类型为字符型
typedef char VerTexType;
// 边的权值类型为整型
typedef int ArcType;

// 定义图的邻接矩阵结构
typedef struct {
	VerTexType vexs[MVNum];        // 顶点表
	ArcType arcs[MVNum][MVNum];    // 邻接矩阵
	int vexnum, arcnum;            // 图的当前点数和边数
} AMGraph;

// 定义状态
typedef enum {ERROR, OK} Status;

// 确定顶点在G中的位置，这里假设顶点值不重复
int LocateVex(AMGraph &G, VerTexType v) {
	for (int i = 0; i < G.vexnum; ++i) {
		if (G.vexs[i] == v)
			return i;
	}
	return -1; // 未找到返回-1
}

// 递归实现深度优先搜索
void DFS(AMGraph &G, int v, bool visited[]) {
	visited[v] = true;
	cout << G.vexs[v] << " "; // 输出顶点
	for (int i = 0; i < G.vexnum; ++i) {
		if (G.arcs[v][i] != MaxInt && !visited[i]) {
			DFS(G, i, visited);
		}
	}
}

// 以邻接矩阵表示法，创建无向网G
Status CreateUDN(AMGraph &G) {
	cout << "请输入总顶点数和总边数：" << endl;
	cin >> G.vexnum >> G.arcnum; // 输入总顶点数，总边数
	cout << "请输入顶点信息：" << endl;
	for (int i = 0; i < G.vexnum; ++i)
		cin >> G.vexs[i]; // 依次输入点的信息
	for (int i = 0; i < G.vexnum; ++i) // 初始化邻接矩阵，边的权值均置为极大值
		for (int j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = MaxInt;
	cout << "请输入边的信息（起点 终点 权值）：" << endl;
	for (int k = 0; k < G.arcnum; ++k) { // 构造邻接矩阵
		VerTexType v1, v2;
		ArcType w;
		cin >> v1 >> v2 >> w; // 输入一条边依附的顶点及权值
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		G.arcs[i][j] = w; // 边<v1, v2>的权值置为w
		G.arcs[j][i] = G.arcs[i][j]; // 置<v1, v2>的对称边<v2, v1>的权值为w
	}
	return OK;
}

// 输出邻接矩阵
void PrintGraph(AMGraph &G) {
	cout << "顶点信息：" << endl;
	for (int i = 0; i < G.vexnum; ++i)
		cout << G.vexs[i] << " ";
	cout << endl << "邻接矩阵：" << endl;
	for (int i = 0; i < G.vexnum; ++i) {
		for (int j = 0; j < G.vexnum; ++j) {
			if (G.arcs[i][j] == MaxInt)
				cout << "∞ ";
			else
				cout << G.arcs[i][j] << " ";
		}
		cout << endl;
	}
}

// 对图进行深度优先遍历
void DFSTraverse(AMGraph &G) {
	bool visited[MVNum] = {false}; // 标记是否被访问过
	cout << "深度优先遍历结果：" << endl;
	for (int i = 0; i < G.vexnum; ++i) {
		if (!visited[i]) {
			DFS(G, i, visited);
		}
	}
	cout << endl;
}

int main() {
	AMGraph G;
	CreateUDN(G);
	PrintGraph(G);
	DFSTraverse(G);
	return 0;
}


