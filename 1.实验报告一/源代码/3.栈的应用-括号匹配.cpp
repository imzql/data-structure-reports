#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stack>
#include <cstring>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

using namespace std;
typedef int Status;
typedef char  SElemType;

#define  MAXSIZE  100
typedef struct {
	SElemType   *base;
	SElemType   *top;
	int stacksize;
} SqStack;

Status InitStack(SqStack &S) {
	S.base = new SElemType[MAXSIZE];
	S.top = S.base;
	S.stacksize = MAXSIZE;
	return OK;
}

Status Push( SqStack &S, SElemType e) {
	if ( S.top - S.base == S.stacksize ) // ջ��
		return ERROR;
	*S.top++ = e;
	return OK;
}

Status Pop( SqStack &S, SElemType &e) {
	if ( S.top == S.base ) // ջ��
		return ERROR;
	e = *--S.top;
	return OK;
}

//���ض�ջԪ��
SElemType GetTop(SqStack s) {
	if (s.top != s.base) {
		return *(s.top - 1);
	}
}

//�ж�ջ�Ƿ�Ϊ��
int StackEmpty(SqStack s) {
	return s.top == s.base;
}

bool IsBracket(char *exp) {
	SqStack s;
	SElemType e;
	int flag = 1;
	InitStack(s); // ��ʼ��ջ

	for (int i = 0; exp[i] != '\0' && flag; i++) {
		char ch = exp[i];
		switch (ch) {
			case '(':
			case '[':
			case '{':
				Push(s, ch); 
				break;
			case ')':
				if (!StackEmpty(s) && GetTop(s) == '(') {
					Pop(s, e); 
				} else {
					flag = 0; 
				}
				break;
			case ']':
				if (!StackEmpty(s) && GetTop(s) == '[') {
					Pop(s, e); 
				} else {
					flag = 0; 
				}
				break;
			case '}':
				if (!StackEmpty(s) && GetTop(s) == '{') {
					Pop(s, e); 
				} else {
					flag = 0; 
				}
				break;
			default:
				break;
		}
	}
	return StackEmpty(s) && flag;
}

int main() {
	char a[30];
	cout << "������һ���������ŵ��ַ���: ";

	cin >> a;

	int result = IsBracket(a) ? 1 : 0;
	
	cout<< result;

	return 0;

}
