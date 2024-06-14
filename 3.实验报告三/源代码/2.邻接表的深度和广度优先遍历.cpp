
/*实验内容与步骤
*（一）分别以邻接矩阵和邻接表作为存储结构，分别采用深度、广度优先遍历，输出图的所有顶点的值。
*（二）分别以邻接矩阵和邻接表作为存储结构，实现以下图的基本操作：
*① 增加一个新顶点v，InsertVex(G, v)；
*② 删除顶点v及其相关的边，DeleteVex(G, v);
*③ 增加一条边<v，w>，InsertArc(G, v, w);
*④ 删除一条边<v，w>，DeleteArc(G, v, w)。
*（三）分别运用Prim算法和Kruskal算法编程，求教材P188图6.33的最小生成树。
*/

#include<iostream>     //v1
#include<cstring>
using namespace std;
const int MVNUM = 100;     //最大顶点数  #define MVNUM 100
const int MaxInt = 32767;  //极大值
bool visited[MVNUM]; 
//队列--------------------------------------------------
typedef struct{                
	int *base;
	int front;     //头指针
	int rear;	   //尾指针
}SqQueue;
//队列初始化
void initQueue(SqQueue &Q)
{
	Q.base = new int[MVNUM];
	Q.front = Q.rear = 0;
}
//队列的销毁
void DestroyQueue(SqQueue &Q)
{
	delete []Q.base;
}
//入队
void enQueue(SqQueue &Q,int e)            
{
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MVNUM;
}
//出队
void deQueue(SqQueue &Q,int &e)          
{
	e = Q.base [Q.front];
	Q.front = (Q.front + 1) % MVNUM;
}
//判队空
bool queueEmpty(SqQueue Q)
{
	if(Q.front == Q.rear)
	{
		return true;
	}
	return false;
}



//图的邻接表存储-------------------------------------------------------------------------------
typedef struct arcNode       //边结点
{
	int adjvex;
	struct arcNode *nextarc;
}ArcNode;
typedef struct vNode         //顶点信息
{
	string data;
	ArcNode *firstarc;		//指向第一条依附该顶点的边的指针
}VNode,AdjList[MVNUM];
struct ALGraph			     //邻接表
{
	AdjList vertices;
	int vexnum,arcnum;		 //当前顶点数和边数
};

//求顶点在图中的位置
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
//创建无向图
bool createUDG(ALGraph &G)
{int i;
	cout<<"输入总顶点和总边数:"<<endl;
	cin>>G.vexnum >>G.arcnum;
	cout<<"依次输入点的信息:"<<endl;
	for( i = 0;i < G.vexnum;i ++)      //初始化顶点信息
	{
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc  = NULL; 
	}
	ArcNode *p1,*p2;
	for( i = 0;i < G.arcnum ;i ++)
	{
		string v1,v2;
		int m,n;
		cout<<"请输入一条边依附的顶点:"<<endl;
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
//打印邻接表
void printAdjacencyList(ALGraph G)
{
	cout<<"图的邻接表:"<<endl;
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
//初始化访问标志数组
void initVisited(ALGraph G)
{
	for(int i = 0;i < G.vexnum ;i ++)
	{
		visited[i] = false;
	}
}
//深度优先搜索遍历
void DFS_AL(ALGraph G,int v)
{
	cout<<G.vertices[v].data<<"\t";
	visited[v] = true;         //第v个顶点已访问
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
//广度优先搜索遍历
void BFS_AL(ALGraph G,int v)
{
	cout<<G.vertices[v].data<<"\t";
	visited[v] = true;       //第v个顶点已访问
	SqQueue Q;
	initQueue(Q);
	enQueue(Q,v);
	int x;                  //出队元素
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


//邻接表的遍历和打印
void printAndDFS_AMAndBFS_AM(ALGraph G)
{   string v;
	initVisited(G);
	cout<<"请输入邻接表深度优先遍历的起点："; 
	cin>>v;
	cout<<"邻接表存储深度优先搜索遍历:"<<endl;
	DFS_AL(G,locateVex(G,v));
	cout<<endl;	
	initVisited(G);
	cout<<"请输入邻接表广度优先遍历的起点：";
	cin>>v;
	cout<<"邻接表存储广度优先搜索遍历:"<<endl;
	BFS_AL(G,locateVex(G,v));
	cout<<endl;
	printAdjacencyList(G);
}



int main()
{

	//邻接表的函数调用(图6.17(a))
	
	ALGraph G;
	createUDG(G);
	printAndDFS_AMAndBFS_AM(G);
	return 0;
}
