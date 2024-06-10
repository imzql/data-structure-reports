#include <iostream>
using namespace std;

#define MaxInt 32767 // ��ʾ����ֵ������
#define MVNum 100     // ��󶥵���

// �������������Ϊ�ַ���
typedef char VerTexType;
// �ߵ�Ȩֵ����Ϊ����
typedef int ArcType;

// ����ͼ���ڽӾ���ṹ
typedef struct {
	VerTexType vexs[MVNum];        // �����
	ArcType arcs[MVNum][MVNum];    // �ڽӾ���
	int vexnum, arcnum;            // ͼ�ĵ�ǰ�����ͱ���
} AMGraph;

// ����״̬
typedef enum {ERROR, OK} Status;

// ȷ��������G�е�λ�ã�������趥��ֵ���ظ�
int LocateVex(AMGraph &G, VerTexType v) {
	for (int i = 0; i < G.vexnum; ++i) {
		if (G.vexs[i] == v)
			return i;
	}
	return -1; // δ�ҵ�����-1
}

// �ݹ�ʵ�������������
void DFS(AMGraph &G, int v, bool visited[]) {
	visited[v] = true;
	cout << G.vexs[v] << " "; // �������
	for (int i = 0; i < G.vexnum; ++i) {
		if (G.arcs[v][i] != MaxInt && !visited[i]) {
			DFS(G, i, visited);
		}
	}
}

// ���ڽӾ����ʾ��������������G
Status CreateUDN(AMGraph &G) {
	cout << "�������ܶ��������ܱ�����" << endl;
	cin >> G.vexnum >> G.arcnum; // �����ܶ��������ܱ���
	cout << "�����붥����Ϣ��" << endl;
	for (int i = 0; i < G.vexnum; ++i)
		cin >> G.vexs[i]; // ������������Ϣ
	for (int i = 0; i < G.vexnum; ++i) // ��ʼ���ڽӾ��󣬱ߵ�Ȩֵ����Ϊ����ֵ
		for (int j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = MaxInt;
	cout << "������ߵ���Ϣ����� �յ� Ȩֵ����" << endl;
	for (int k = 0; k < G.arcnum; ++k) { // �����ڽӾ���
		VerTexType v1, v2;
		ArcType w;
		cin >> v1 >> v2 >> w; // ����һ���������Ķ��㼰Ȩֵ
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		G.arcs[i][j] = w; // ��<v1, v2>��Ȩֵ��Ϊw
		G.arcs[j][i] = G.arcs[i][j]; // ��<v1, v2>�ĶԳƱ�<v2, v1>��ȨֵΪw
	}
	return OK;
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

// ��ͼ����������ȱ���
void DFSTraverse(AMGraph &G) {
	bool visited[MVNum] = {false}; // ����Ƿ񱻷��ʹ�
	cout << "������ȱ��������" << endl;
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


