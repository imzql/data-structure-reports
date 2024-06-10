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
	if ( S.top - S.base == S.stacksize ) // Õ»Âú
		return ERROR;
	*S.top++ = e;
	return OK;
}

Status Pop( SqStack &S, SElemType &e) {
	if ( S.top == S.base ) // Õ»¿Õ
		return ERROR;
	e = *--S.top;
	return OK;
}

//·µ»Ø¶¥Õ»ÔªËØ
SElemType GetTop(SqStack s) {
	if (s.top != s.base) {
		return *(s.top - 1);
	}
}

//ÅÐ¶ÏÕ»ÊÇ·ñÎª¿Õ
int StackEmpty(SqStack s) {
	return s.top == s.base;
}

bool IsBracket(char *exp) {
	SqStack s;
	SElemType e;
	int flag = 1;
	InitStack(s); // ³õÊ¼»¯Õ»

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
	cout << "ÇëÊäÈëÒ»¸ö°üº¬À¨ºÅµÄ×Ö·û´®: ";

	cin >> a;

	int result = IsBracket(a) ? 1 : 0;
	
	cout<< result;

	return 0;

}
