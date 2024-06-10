#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

#define MaxInt 32767 // 表示极大值，即∞
#define MVNum 100     // 最大顶点数

// 定义图的邻接矩阵结构
typedef struct {
	vector<char> vexs;        // 顶点表
	vector<vector<int> > arcs; // 邻接矩阵
	int vexnum, arcnum;       // 图的当前点数和边数
} AMGraph;

// 创建有向图
void CreateDG(AMGraph &G, const vector<pair<char, char> > &edges) {
	str::unordered_map<char, int> vertex_index;
	int count = 0;
	
	for (const auto &edge : edges) {
		if (vertex_index.find(edge.first) == vertex_index.end()) {
			vertex_index[edge.first] = count++;
			G.vexs.push_back(edge.first);
		}
		if (vertex_index.find(edge.second) == vertex_index.end()) {
			vertex_index[edge.second] = count++;
			G.vexs.push_back(edge.second);
		}
	}
	
	G.vexnum = count;
	G.arcnum = edges.size();
	
	G.arcs.resize(count, vector<int>(count, MaxInt));
	
	for (const auto &edge : edges) {
		int from = vertex_index[edge.first];
		int to = vertex_index[edge.second];
		G.arcs[from][to] = 1; // 有向图，边存在即置为1
	}
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

int main() {
	vector<pair<char, char>> edges = {
		{'v1', 'v2'},
		{'v1', 'v3'},
		{'v4', 'v1'},
		{'v3', 'v4'}
	};
	AMGraph G;
	CreateDG(G, edges);
	PrintGraph(G);
	return 0;
}

