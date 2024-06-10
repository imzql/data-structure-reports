#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status; //Status �Ǻ�������ֵ���ͣ���ֵ�Ǻ������״̬���롣
typedef int ElemType; //ElemType Ϊ�ɶ�����������ͣ�����Ϊint����


typedef struct LNode {
	ElemType data; //����������
	struct LNode *next; //����ָ����
} LNode, *LinkList; //LinkListΪָ��ṹ��LNode��ָ������



Status InitList(LinkList &L) { //�㷨2.6 ������ĳ�ʼ��
	//����һ���յĵ�����L
	L = new LNode; //�����½����Ϊͷ��㣬��ͷָ��Lָ��ͷ���
	L->next = NULL; //ͷ����ָ�����ÿ�
	return OK;
}

Status GetElem(LinkList L, int i, ElemType &e) { //�㷨2.7 �������ȡֵ
	//�ڴ�ͷ���ĵ�����L�в��ҵ�i��Ԫ��
	//��e����L�е�i������Ԫ�ص�ֵ
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

LNode *LocateElem(LinkList L,  ElemType e) { //�㷨2.8 ��ֵ����
	//�ڴ�ͷ���ĵ�����L�в���ֵΪe��Ԫ��
	LinkList p;
	p = L->next;
	while (p && p ->data != e) {
		p = p->next;
	}
	return p;
} //LocateElem

Status ListInsert(LinkList &L, int i, ElemType e) { //�㷨2.9 ������Ĳ���
	//�ڴ�ͷ���ĵ�����L�е�i��λ�ò���ֵΪe���½��
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

Status ListDelete(LinkList &L, int i) { //�㷨2.9 �������ɾ��
	//�ڴ�ͷ���ĵ�����L�У�ɾ����i��λ��
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

void CreateList_H(LinkList &L, int n) { //�㷨2.11 ǰ�巨����������
	//��λ������n��Ԫ�ص�ֵ��������ͷ���ĵ�����L
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

void CreateList_R(LinkList &L, int n) { //�㷨2.12 ��巨����������
	//��λ������n��Ԫ�ص�ֵ����������ͷ���ĵ�����L
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
	//���õ����������Ԫ����ʾ����
	LinkList p;
	p = L->next;
	while (p) {
		cout << p->data;
		p = p->next;
	}
}

int ListLength(LinkList L) {
	//ʵ�ֵ�������������
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

//�����ֵ
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
        //	1) ��������������һ������ͷ����4�����ģ�5��4��2��1���ĵ�����ʵ�ֵ��������Ļ���������
		LinkList L;
	
		InitList(L);	
	    
	    cout << "��������ֵ��5��4��2��1���ĵ�����" ;
	
		// ����������5��4��2��1��
		CreateList_H(L, 4);
		
		//	2) ���õ����������Ԫ����ʾ������
		cout << "����������Ԫ��Ϊ��"<<endl;
	
		ShowList(L);
	
	    cout << endl;
		
		//	3)ȡֵ�����ѽ��õĵ������еĵ�3��λ�ã�i=3��ȡ��Ԫ�ص�ֵ�������
		ElemType e;
		GetElem(L, 3, e);
		cout << "��3��λ�õ�Ԫ��ֵΪ��" << e << endl;
		
		//	4)���ҡ����������ҵ���2�͵���100��Ԫ�أ�����ʾ�����Ϣ��
		cout << "����ֵΪ2��Ԫ�أ�" << (LocateElem(L, 2) != NULL ? "����" : "������") << endl;
		cout << "����ֵΪ100��Ԫ�أ�" << (LocateElem(L, 100) != NULL ? "����" : "������") << endl;
		
		//	5) ����Ԫ�ء����ѽ��õĵ������е�ָ��λ�ã�i=3������һ�����3��ʵ�ֵ��������Ļ��������������õ����������Ԫ����ʾ������
		ListInsert(L, 3, 3);
		cout << "�ڵ�3��λ�ò���Ԫ��3�󣬵���������Ԫ��Ϊ��" << endl;
		ShowList(L);
		
		//	6) ɾ��Ԫ�ء���һ������ͷ���ĵ������ָ��λ�ã���i=2��ɾ��һ����㣬ʵ�ֵ�����ɾ���Ļ��������������õ����������Ԫ����ʾ������
		ListDelete(L, 2);
		cout << "ɾ����2��λ�õ�Ԫ�غ󣬵���������Ԫ��Ϊ��" << endl;
		ShowList(L);
		
		//	7)����õ�����ı���
		cout << "������ı�Ϊ��" << ListLength(L) << endl;
		
		//	8)ȡ���ֵ�����һ���㷨��ͨ��һ�˱���ȷ������Ϊn�ĵ�������ֵ���Ľ�㡣
		cout << "��������ֵ����Ԫ��Ϊ��" << getMaxElement(L) << endl;
		
		return 0;
}
