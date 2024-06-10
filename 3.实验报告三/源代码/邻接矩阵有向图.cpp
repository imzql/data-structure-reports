#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

#define MaxInt 32767 // ��ʾ����ֵ������
#define MVNum 100     // ��󶥵���

// ����ͼ���ڽӾ���ṹ
typedef struct {
	vector<char> vexs;        // �����
	vector<vector<int> > arcs; // �ڽӾ���
	int vexnum, arcnum;       // ͼ�ĵ�ǰ�����ͱ���
} AMGraph;

// ��������ͼ
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
		G.arcs[from][to] = 1; // ����ͼ���ߴ��ڼ���Ϊ1
	}
}

// ����ڽӾ���
void PrintGraph(AMGraph &G) {
	cout << "������Ϣ��" << endl;
	for (int i = 0; i < G.vexnum; ++i)
		cout << G.vexs[i] << " ";
	cout << endl << "�ڽӾ���" << endl;
	for (int i = 0; i < G.vexnum; ++i) {
		for (int j = 0; j < G.vexnum; ++j) {
			if (G.arcs[i][j] == MaxInt)
				cout << "�� ";
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

