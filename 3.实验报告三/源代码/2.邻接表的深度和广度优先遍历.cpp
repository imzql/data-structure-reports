
/*ʵ�������벽��
*��һ���ֱ����ڽӾ�����ڽӱ���Ϊ�洢�ṹ���ֱ������ȡ�������ȱ��������ͼ�����ж����ֵ��
*�������ֱ����ڽӾ�����ڽӱ���Ϊ�洢�ṹ��ʵ������ͼ�Ļ���������
*�� ����һ���¶���v��InsertVex(G, v)��
*�� ɾ������v������صıߣ�DeleteVex(G, v);
*�� ����һ����<v��w>��InsertArc(G, v, w);
*�� ɾ��һ����<v��w>��DeleteArc(G, v, w)��
*�������ֱ�����Prim�㷨��Kruskal�㷨��̣���̲�P188ͼ6.33����С��������
*/

#include<iostream>     //v1
#include<cstring>
using namespace std;
const int MVNUM = 100;     //��󶥵���  #define MVNUM 100
const int MaxInt = 32767;  //����ֵ
bool visited[MVNUM]; 
//����--------------------------------------------------
typedef struct{                
	int *base;
	int front;     //ͷָ��
	int rear;	   //βָ��
}SqQueue;
//���г�ʼ��
void initQueue(SqQueue &Q)
{
	Q.base = new int[MVNUM];
	Q.front = Q.rear = 0;
}
//���е�����
void DestroyQueue(SqQueue &Q)
{
	delete []Q.base;
}
//���
void enQueue(SqQueue &Q,int e)            
{
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MVNUM;
}
//����
void deQueue(SqQueue &Q,int &e)          
{
	e = Q.base [Q.front];
	Q.front = (Q.front + 1) % MVNUM;
}
//�жӿ�
bool queueEmpty(SqQueue Q)
{
	if(Q.front == Q.rear)
	{
		return true;
	}
	return false;
}



//ͼ���ڽӱ�洢-------------------------------------------------------------------------------
typedef struct arcNode       //�߽��
{
	int adjvex;
	struct arcNode *nextarc;
}ArcNode;
typedef struct vNode         //������Ϣ
{
	string data;
	ArcNode *firstarc;		//ָ���һ�������ö���ıߵ�ָ��
}VNode,AdjList[MVNUM];
struct ALGraph			     //�ڽӱ�
{
	AdjList vertices;
	int vexnum,arcnum;		 //��ǰ�������ͱ���
};

//�󶥵���ͼ�е�λ��
int locateVex(ALGraph G,string x)
{
	for(int i = 0;i < G.vexnum ;i ++)
	{
		if(G.vertices[i].data == x)
		{
			return i;
		}
	}
	return -1;
}
//��������ͼ
bool createUDG(ALGraph &G)
{int i;
	cout<<"�����ܶ�����ܱ���:"<<endl;
	cin>>G.vexnum >>G.arcnum;
	cout<<"������������Ϣ:"<<endl;
	for( i = 0;i < G.vexnum;i ++)      //��ʼ��������Ϣ
	{
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc  = NULL; 
	}
	ArcNode *p1,*p2;
	for( i = 0;i < G.arcnum ;i ++)
	{
		string v1,v2;
		int m,n;
		cout<<"������һ���������Ķ���:"<<endl;
		cin>>v1>>v2;
		m = locateVex(G,v1);n = locateVex(G,v2);
		p1 = new ArcNode;
		p1->adjvex = n;
		p1->nextarc = G.vertices[m].firstarc;
		G.vertices[m].firstarc = p1; 
		p2 = new ArcNode;
		p2->adjvex = m;
		p2->nextarc = G.vertices[n].firstarc;
		G.vertices[n].firstarc = p2; 
	}
	return true;
}
//��ӡ�ڽӱ�
void printAdjacencyList(ALGraph G)
{
	cout<<"ͼ���ڽӱ�:"<<endl;
	for(int i = 0;i < G.vexnum;i ++)
	{
		cout<<i<<" "<<G.vertices[i].data;
		if(G.vertices[i].firstarc != NULL)
		{
			cout<<"-->";
			if(G.vertices[i].firstarc->nextarc != NULL)
			{
				cout<<G.vertices[i].firstarc->adjvex<<"-->"; 
			}else
			{
				cout<<G.vertices[i].firstarc->adjvex<<endl;
			}	 
			while(G.vertices[i].firstarc->nextarc != NULL)
			{
				cout<<G.vertices[i].firstarc->nextarc->adjvex;
				if(G.vertices[i].firstarc->nextarc->nextarc != NULL)	
				{
					cout<<"-->";
				}else
				{
					cout<<endl;
				}
				G.vertices[i].firstarc->nextarc = G.vertices[i].firstarc->nextarc->nextarc;
			}	
		}else
		{
			cout<<endl;
		}
	}
}
//��ʼ�����ʱ�־����
void initVisited(ALGraph G)
{
	for(int i = 0;i < G.vexnum ;i ++)
	{
		visited[i] = false;
	}
}
//���������������
void DFS_AL(ALGraph G,int v)
{
	cout<<G.vertices[v].data<<"\t";
	visited[v] = true;         //��v�������ѷ���
	ArcNode *p = G.vertices[v].firstarc;	
	int w;
	while(p)
	{
		w = p->adjvex;
		if(!visited[w])
		{
			DFS_AL(G,w);
		}
		p = p->nextarc;
	}
}
//���������������
void BFS_AL(ALGraph G,int v)
{
	cout<<G.vertices[v].data<<"\t";
	visited[v] = true;       //��v�������ѷ���
	SqQueue Q;
	initQueue(Q);
	enQueue(Q,v);
	int x;                  //����Ԫ��
	while(!queueEmpty(Q))
	{
		deQueue(Q,x);
		ArcNode *p = G.vertices[x].firstarc;	
		while(p)
		{
			int w = p->adjvex; 
			if(!visited[w])
			{
				cout<<G.vertices[w].data<<"\t";
				visited[w] = true;
				enQueue(Q,w);
			}
			p = p->nextarc;
		}
	}
	DestroyQueue(Q);
}


//�ڽӱ�ı����ʹ�ӡ
void printAndDFS_AMAndBFS_AM(ALGraph G)
{   string v;
	initVisited(G);
	cout<<"�������ڽӱ�������ȱ�������㣺"; 
	cin>>v;
	cout<<"�ڽӱ�洢���������������:"<<endl;
	DFS_AL(G,locateVex(G,v));
	cout<<endl;	
	initVisited(G);
	cout<<"�������ڽӱ������ȱ�������㣺";
	cin>>v;
	cout<<"�ڽӱ�洢���������������:"<<endl;
	BFS_AL(G,locateVex(G,v));
	cout<<endl;
	printAdjacencyList(G);
}



int main()
{

	//�ڽӱ�ĺ�������(ͼ6.17(a))
	
	ALGraph G;
	createUDG(G);
	printAndDFS_AMAndBFS_AM(G);
	return 0;
}
