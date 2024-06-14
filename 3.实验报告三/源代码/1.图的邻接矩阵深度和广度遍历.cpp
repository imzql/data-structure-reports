//�㷨6.5�������ڽӾ����ʾͼ�����������������

#include <iostream>
using namespace std;
#define MVNum 100							//��󶥵���
typedef char VerTexType;					//���趥�����������Ϊ�ַ��� 
typedef int ArcType;                 		//����ߵ�Ȩֵ����Ϊ���� 
                    
#define MAXQSIZE 100						//�����г���
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
						
                  		
bool visited[MVNum]; 	//���ʱ�־���飬���ֵΪ"false"
//------------ͼ���ڽӾ���------------------
typedef struct{ 
	VerTexType vexs[MVNum];            		//����� 
	ArcType arcs[MVNum][MVNum];      		//�ڽӾ��� 
	int vexnum,arcnum;                		//ͼ�ĵ�ǰ�����ͱ��� 
}AMGraph;

          			 
int FirstAdjVex(AMGraph G , int v);			//����v�ĵ�һ���ڽӵ�
int NextAdjVex(AMGraph G , int v , int w);	//����v�����w����һ���ڽӵ�

int LocateVex(AMGraph G , VerTexType v){
	//ȷ����v��G�е�λ��
	for(int i = 0; i < G.vexnum; ++i)
		if(G.vexs[i] == v)
			return i;
		return -1;
}//LocateVex

void CreateUDN(AMGraph &G){ 
    //�����ڽӾ����ʾ��������������G 
	int i , j , k;
	cout <<"�������ܶ��������ܱ������Կո����:";
    cin >> G.vexnum >> G.arcnum;							//�����ܶ��������ܱ���
	cout << endl;
	
	cout << "���������ƣ���a" <<endl;

    for(i = 0; i < G.vexnum; ++i){   
		cout << "�������" << (i+1) << "���������:";
		cin >> G.vexs[i];                        			//������������Ϣ 
	}	
	cout << endl;

    for(i = 0; i < G.vexnum; ++i)                			//��ʼ���ڽӾ��󣬱ߵ�Ȩֵ����Ϊ����ֵMaxInt 
		for(j = 0; j < G.vexnum; ++j)   
			G.arcs[i][j] = 0;  
	cout << "����������Ķ��㣬��a b" << endl;
	for(k = 0; k < G.arcnum;++k){							//�����ڽӾ��� 
		VerTexType v1 , v2;
		cout << "�������" << (k + 1) << "���������Ķ���:";
		cin >> v1 >> v2;									//����һ���������Ķ��㼰Ȩֵ
		i = LocateVex(G, v1);  j = LocateVex(G, v2);		//ȷ��v1��v2��G�е�λ�ã�������������±� 
		G.arcs[j][i] = G.arcs[i][j] = 1;					//��<v1, v2>�ĶԳƱ�<v2, v1>��ȨֵΪw 
	}//for
}//CreateUDN 

void DFS(AMGraph G, int v){        		
	//ͼGΪ�ڽӾ������� 
	int w;
	cout << G.vexs[v] << "  ";  visited[v] = true;  		//���ʵ�v�����㣬���÷��ʱ�־������Ӧ����ֵΪtrue 
	for(w = 0; w < G.vexnum; w++)  							//���μ���ڽӾ���v���ڵ���  
		if((G.arcs[v][w] != 0)&& (!visited[w]))  DFS(G, w); //G.arcs[v][w]!=0��ʾw��v���ڽӵ㣬���wδ���ʣ���ݹ����DFS 
}//DFS


void show(AMGraph G){
	for(int i=0;i<G.vexnum;i++){
		for(int j=0;j<G.vexnum;j++)
			cout<<G.arcs[i][j]<<"\t";
		cout<<endl;
	}	
}

//----���еĶ��弰����--------
typedef struct{
	ArcType *base;							//��ʼ���Ķ�̬����洢�ռ�
	int front;								//ͷָ�룬�����в��գ�ָ���ͷԪ��
	int rear;								//βָ�룬�����в��գ�ָ���βԪ�ص���һ��λ��
}sqQueue;

Status InitQueue(sqQueue &Q){
	//����һ���ն���Q
	Q.base = new ArcType[MAXQSIZE];
	if(!Q.base)     return ERROR;				//�洢����ʧ��
	Q.front = Q.rear = 0;
	return OK;
}//InitQueue

void EnQueue(sqQueue &Q, ArcType e){
	//����Ԫ��eΪQ���µĶ�βԪ��
	if((Q.rear + 1) % MAXQSIZE == Q.front)
		return;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
}//EnQueue

bool QueueEmpty(sqQueue Q){
	//�ж��Ƿ�Ϊ�ն�
	if(Q.rear == Q.front)
		return true;
	return false;
}//QueueEmpty

void DeQueue(sqQueue &Q, ArcType &u){
	//��ͷԪ�س��Ӳ���Ϊu 
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
	//����v�ĵ�һ���ڽӵ�
	int i;
	for(i = 0 ; i < G.vexnum ; ++i){
		if(G.arcs[v][i] == 1 && visited[i] == false)
			return i;
	}
	return -1;
}//FirstAdjVex

int NextAdjVex(AMGraph G , int u , int w){//   0 1 1 0  1
	//����v�����w����һ���ڽӵ�
	int i;
	for(i = w ; i < G.vexnum ; ++i){
		if(G.arcs[u][i] == 1 && visited[i] == false)
			return i;
	}
	return -1;
}//NextAdjVex

void BFS (AMGraph G, int v){ 
    //��������ȷǵݹ������ͨͼG 
	sqQueue Q;
	ArcType u;
	ArcType w;
    cout << G.vexs[v] << "  ";    visited[v] = true;     						//���ʵ�v�����㣬���÷��ʱ�־������Ӧ����ֵΪtrue 
    InitQueue(Q);              													//��������Q��ʼ�����ÿ�         
    EnQueue(Q, v);            													//v���� 
    while(!QueueEmpty(Q)){   													//���зǿ� 
		DeQueue(Q, u);       													//��ͷԪ�س��Ӳ���Ϊu
		for(w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w)){
			//���μ��u�������ڽӵ�w ��FirstAdjVex(G, u)��ʾu�ĵ�һ���ڽӵ� 
			//NextAdjVex(G, u, w)��ʾu�����w����һ���ڽӵ㣬w��0��ʾ�����ڽӵ� 
			if(!visited[w]){	           										//wΪu����δ���ʵ��ڽӶ��� 
				cout << G.vexs[w] << "  ";   visited[w] = true;					//����w�����÷��ʱ�־������Ӧ����ֵΪtrue 
				EnQueue(Q, w);													//w���� 
			}//if 
		}//for
    }//while 
}//BFS 


int main(){
	cout << "************�㷨6.5�������ڽӾ����ʾͼ�����������������**************" << endl << endl;
	AMGraph G;
	CreateUDN(G);
	cout << endl;
	cout << "����ͼG������ɣ�" << endl << endl;
	show(G);
	int i;
	VerTexType c;
	cout << "��������ȱ�������ͼG����ʼ�㣺";
    cin >> c;
	cout << "�������������������ͼG�����" << endl;
	DFS(G , LocateVex(G,c));
	cout <<endl;
	
	cout << "�������ȱ�������ͼG����ʼ�㣺";
	cin >> c;
    for(int t=0;t<MVNum;t++)  
	  visited[t]=false; 	//���ʱ�־���飬���ֵΪ"false"
	
	cout << "�����������������ͨͼ�����" << endl;
	BFS(G , LocateVex(G,c));
	cout <<endl;
	return 0;
}//main
