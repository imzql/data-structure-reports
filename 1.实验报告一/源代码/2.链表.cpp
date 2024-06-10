#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status; //Status 是函数返回值类型，其值是函数结果状态代码。
typedef int ElemType; //ElemType 为可定义的数据类型，此设为int类型


typedef struct LNode {
	ElemType data; //结点的数据域
	struct LNode *next; //结点的指针域
} LNode, *LinkList; //LinkList为指向结构体LNode的指针类型



Status InitList(LinkList &L) { //算法2.6 单链表的初始化
	//构造一个空的单链表L
	L = new LNode; //生成新结点作为头结点，用头指针L指向头结点
	L->next = NULL; //头结点的指针域置空
	return OK;
}

Status GetElem(LinkList L, int i, ElemType &e) { //算法2.7 单链表的取值
	//在带头结点的单链表L中查找第i个元素
	//用e返回L中第i个数据元素的值
	int j;
	LinkList p;
	p = L->next;
	j = 1;
	while (p && j < i) {
		p = p->next;
		++j;
	}
	if (!p || j > i) return ERROR;
	e = p->data;
	return OK;
} //GetElem

LNode *LocateElem(LinkList L,  ElemType e) { //算法2.8 按值查找
	//在带头结点的单链表L中查找值为e的元素
	LinkList p;
	p = L->next;
	while (p && p ->data != e) {
		p = p->next;
	}
	return p;
} //LocateElem

Status ListInsert(LinkList &L, int i, ElemType e) { //算法2.9 单链表的插入
	//在带头结点的单链表L中第i个位置插入值为e的新结点
	int j;
	LinkList p, s;
	p = L;
	j = 0;
	while (p && (j < i - 1)) {
		p = p->next;
		++j;
	}
	if (!p || j > i - 1)return ERROR;
	s = new LNode;
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
} //ListInsert

Status ListDelete(LinkList &L, int i) { //算法2.9 单链表的删除
	//在带头结点的单链表L中，删除第i个位置
	LinkList p, q;
	int j;
	p = L;
	j = 0;
	while ((p->next) && (j < i - 1)) {
		p = p->next;
		++j;
	}
	if (!(p->next) || (j > i - 1)) return ERROR;
	q = p->next;
	p->next = q->next;
	delete q;
	return OK;
} //ListDelete

void CreateList_H(LinkList &L, int n) { //算法2.11 前插法创建单链表
	//逆位序输入n个元素的值，建立到头结点的单链表L
	LinkList p;
	int i;
	L = new LNode;
	L->next = NULL;
	for (i = 0; i < n; ++i) {
		p = new LNode;
		cin >> p->data;
		p->next = L->next;
		L->next = p;
	}
} //CreateList_H

void CreateList_R(LinkList &L, int n) { //算法2.12 后插法创建单链表
	//正位序输入n个元素的值，建立带表头结点的单链表L
	LinkList p, r;
	int i;
	L = new LNode;
	L->next = NULL;
	r = L;
	for (i = 0; i < n; ++i) {
		p = new LNode;
		cin >> p->data;
		p->next = NULL;
		r->next = p;
		r = p;
	}
} //CreateList_R

void ShowList(LinkList L) {
	//将该单链表的所有元素显示出来
	LinkList p;
	p = L->next;
	while (p) {
		cout << p->data;
		p = p->next;
	}
}

int ListLength(LinkList L) {
	//实现单链表的求表长操作
	LinkList p;
	int j;
	p = L->next;
	if (p == NULL) return 0;
	while (p) {
		++j;
		p = p->next;
	}
	return j;
}

//求最大值
ElemType getMaxElement(LinkList L) {
	LinkList p = L->next;
	ElemType max_val = p->data; 
	while (p) {
		if (p->data > max_val) {
			max_val = p->data;
		}
		p = p->next;
	}
	return max_val;
}

int main() {
        //	1) 建立单链表。建立一个包括头结点和4个结点的（5，4，2，1）的单链表，实现单链表建立的基本操作。
		LinkList L;
	
		InitList(L);	
	    
	    cout << "请输入数值（5，4，2，1）的单链表" ;
	
		// 建立单链表（5，4，2，1）
		CreateList_H(L, 4);
		
		//	2) 将该单链表的所有元素显示出来。
		cout << "单链表所有元素为："<<endl;
	
		ShowList(L);
	
	    cout << endl;
		
		//	3)取值。在已建好的单链表中的第3个位置（i=3）取出元素的值并输出。
		ElemType e;
		GetElem(L, 3, e);
		cout << "第3个位置的元素值为：" << e << endl;
		
		//	4)查找。在链表中找等于2和等于100的元素，并显示相关信息。
		cout << "查找值为2的元素：" << (LocateElem(L, 2) != NULL ? "存在" : "不存在") << endl;
		cout << "查找值为100的元素：" << (LocateElem(L, 100) != NULL ? "存在" : "不存在") << endl;
		
		//	5) 插入元素。在已建好的单链表中的指定位置（i=3）插入一个结点3，实现单链表插入的基本操作，并将该单链表的所有元素显示出来。
		ListInsert(L, 3, 3);
		cout << "在第3个位置插入元素3后，单链表所有元素为：" << endl;
		ShowList(L);
		
		//	6) 删除元素。在一个包括头结点的单链表的指定位置（如i=2）删除一个结点，实现单链表删除的基本操作，并将该单链表的所有元素显示出来。
		ListDelete(L, 2);
		cout << "删除第2个位置的元素后，单链表所有元素为：" << endl;
		ShowList(L);
		
		//	7)输出该单链表的表长。
		cout << "单链表的表长为：" << ListLength(L) << endl;
		
		//	8)取最大值。设计一个算法，通过一趟遍历确定长度为n的单链表中值最大的结点。
		cout << "单链表中值最大的元素为：" << getMaxElement(L) << endl;
		
		return 0;
}
