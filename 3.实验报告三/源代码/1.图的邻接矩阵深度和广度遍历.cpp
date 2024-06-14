//算法6.5　采用邻接矩阵表示图的深度优先搜索遍历

#include <iostream>
using namespace std;
#define MVNum 100							//最大顶点数
typedef char VerTexType;					//假设顶点的数据类型为字符型 
typedef int ArcType;                 		//假设边的权值类型为整型 
                    
#define MAXQSIZE 100						//最大队列长度
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
						
                  		
bool visited[MVNum]; 	//访问标志数组，其初值为"false"
//------------图的邻接矩阵------------------
typedef struct{ 
	VerTexType vexs[MVNum];            		//顶点表 
	ArcType arcs[MVNum][MVNum];      		//邻接矩阵 
	int vexnum,arcnum;                		//图的当前点数和边数 
}AMGraph;

          			 
int FirstAdjVex(AMGraph G , int v);			//返回v的第一个邻接点
int NextAdjVex(AMGraph G , int v , int w);	//返回v相对于w的下一个邻接点

int LocateVex(AMGraph G , VerTexType v){
	//确定点v在G中的位置
	for(int i = 0; i < G.vexnum; ++i)
		if(G.vexs[i] == v)
			return i;
		return -1;
}//LocateVex

void CreateUDN(AMGraph &G){ 
    //采用邻接矩阵表示法，创建无向网G 
	int i , j , k;
	cout <<"请输入总顶点数，总边数，以空格隔开:";
    cin >> G.vexnum >> G.arcnum;							//输入总顶点数，总边数
	cout << endl;
	
	cout << "输入点的名称，如a" <<endl;

    for(i = 0; i < G.vexnum; ++i){   
		cout << "请输入第" << (i+1) << "个点的名称:";
		cin >> G.vexs[i];                        			//依次输入点的信息 
	}	
	cout << endl;

    for(i = 0; i < G.vexnum; ++i)                			//初始化邻接矩阵，边的权值均置为极大值MaxInt 
		for(j = 0; j < G.vexnum; ++j)   
			G.arcs[i][j] = 0;  
	cout << "输入边依附的顶点，如a b" << endl;
	for(k = 0; k < G.arcnum;++k){							//构造邻接矩阵 
		VerTexType v1 , v2;
		cout << "请输入第" << (k + 1) << "条边依附的顶点:";
		cin >> v1 >> v2;									//输入一条边依附的顶点及权值
		i = LocateVex(G, v1);  j = LocateVex(G, v2);		//确定v1和v2在G中的位置，即顶点数组的下标 
		G.arcs[j][i] = G.arcs[i][j] = 1;					//置<v1, v2>的对称边<v2, v1>的权值为w 
	}//for
}//CreateUDN 

void DFS(AMGraph G, int v){        		
	//图G为邻接矩阵类型 
	int w;
	cout << G.vexs[v] << "  ";  visited[v] = true;  		//访问第v个顶点，并置访问标志数组相应分量值为true 
	for(w = 0; w < G.vexnum; w++)  							//依次检查邻接矩阵v所在的行  
		if((G.arcs[v][w] != 0)&& (!visited[w]))  DFS(G, w); //G.arcs[v][w]!=0表示w是v的邻接点，如果w未访问，则递归调用DFS 
}//DFS


void show(AMGraph G){
	for(int i=0;i<G.vexnum;i++){
		for(int j=0;j<G.vexnum;j++)
			cout<<G.arcs[i][j]<<"\t";
		cout<<endl;
	}	
}

//----队列的定义及操作--------
typedef struct{
	ArcType *base;							//初始化的动态分配存储空间
	int front;								//头指针，若队列不空，指向队头元素
	int rear;								//尾指针，若队列不空，指向队尾元素的下一个位置
}sqQueue;

Status InitQueue(sqQueue &Q){
	//构造一个空队列Q
	Q.base = new ArcType[MAXQSIZE];
	if(!Q.base)     return ERROR;				//存储分配失败
	Q.front = Q.rear = 0;
	return OK;
}//InitQueue

void EnQueue(sqQueue &Q, ArcType e){
	//插入元素e为Q的新的队尾元素
	if((Q.rear + 1) % MAXQSIZE == Q.front)
		return;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
}//EnQueue

bool QueueEmpty(sqQueue Q){
	//判断是否为空队
	if(Q.rear == Q.front)
		return true;
	return false;
}//QueueEmpty

void DeQueue(sqQueue &Q, ArcType &u){
	//队头元素出队并置为u 
	u = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
}//DeQueue   								
//--------------------------------------------------
/*
a   b  c  d  e  
1  0  0  1  0   a
1  1  0  0  1   b
..........
*/

int FirstAdjVex(AMGraph G , int v){
	//返回v的第一个邻接点
	int i;
	for(i = 0 ; i < G.vexnum ; ++i){
		if(G.arcs[v][i] == 1 && visited[i] == false)
			return i;
	}
	return -1;
}//FirstAdjVex

int NextAdjVex(AMGraph G , int u , int w){//   0 1 1 0  1
	//返回v相对于w的下一个邻接点
	int i;
	for(i = w ; i < G.vexnum ; ++i){
		if(G.arcs[u][i] == 1 && visited[i] == false)
			return i;
	}
	return -1;
}//NextAdjVex

void BFS (AMGraph G, int v){ 
    //按广度优先非递归遍历连通图G 
	sqQueue Q;
	ArcType u;
	ArcType w;
    cout << G.vexs[v] << "  ";    visited[v] = true;     						//访问第v个顶点，并置访问标志数组相应分量值为true 
    InitQueue(Q);              													//辅助队列Q初始化，置空         
    EnQueue(Q, v);            													//v进队 
    while(!QueueEmpty(Q)){   													//队列非空 
		DeQueue(Q, u);       													//队头元素出队并置为u
		for(w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w)){
			//依次检查u的所有邻接点w ，FirstAdjVex(G, u)表示u的第一个邻接点 
			//NextAdjVex(G, u, w)表示u相对于w的下一个邻接点，w≥0表示存在邻接点 
			if(!visited[w]){	           										//w为u的尚未访问的邻接顶点 
				cout << G.vexs[w] << "  ";   visited[w] = true;					//访问w，并置访问标志数组相应分量值为true 
				EnQueue(Q, w);													//w进队 
			}//if 
		}//for
    }//while 
}//BFS 


int main(){
	cout << "************算法6.5　采用邻接矩阵表示图的深度优先搜索遍历**************" << endl << endl;
	AMGraph G;
	CreateUDN(G);
	cout << endl;
	cout << "无向图G创建完成！" << endl << endl;
	show(G);
	int i;
	VerTexType c;
	cout << "请输入深度遍历无向图G的起始点：";
    cin >> c;
	cout << "深度优先搜索遍历无向图G结果：" << endl;
	DFS(G , LocateVex(G,c));
	cout <<endl;
	
	cout << "请输入广度遍历无向图G的起始点：";
	cin >> c;
    for(int t=0;t<MVNum;t++)  
	  visited[t]=false; 	//访问标志数组，其初值为"false"
	
	cout << "广度优先搜索遍历连通图结果：" << endl;
	BFS(G , LocateVex(G,c));
	cout <<endl;
	return 0;
}//main
