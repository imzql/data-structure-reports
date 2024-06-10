#include <iostream>
using namespace std;

#define MAXTSIZE 100
#define OK 1

typedef char TElemType;
typedef int Status;

// 二叉树的二叉链表存储表示
typedef struct BiTNode {
	TElemType data;                 // 结点数据域
	struct BiTNode* lchild, * rchild; // 左右孩子指针
} BiTNode, * BiTree;

// 初始化二叉树
BiTree CreateBiTree(char* str, int& i) {
	if (str[i] == '#' || str[i] == '\0') {
		i++;
		return NULL;
	}
	
	// 创建新节点
	BiTree T = new BiTNode;
	T->data = str[i++];
	T->lchild = CreateBiTree(str, i); // 递归构建左子树
	T->rchild = CreateBiTree(str, i); // 递归构建右子树
	
	return T;
}

// 先序遍历
Status PreOrderTraverse(BiTree T) {
	if (T == NULL) return OK;
	else {
		cout << T->data; // 访问根结点
		PreOrderTraverse(T->lchild); // 递归遍历左子树
		PreOrderTraverse(T->rchild); // 递归遍历右子树
	}
}

// 中序遍历
Status InOrderTraverse(BiTree T) {
	if (T == NULL) return OK; // 空二叉树
	else {
		InOrderTraverse(T->lchild); // 递归遍历左子树
		cout << T->data; // 访问根结点
		InOrderTraverse(T->rchild); // 递归遍历右子树
	}
}

// 后序遍历
Status PostOrderTraverse(BiTree T) {
	if (T == NULL) return OK; // 空二叉树
	else {
		PostOrderTraverse(T->lchild); // 递归遍历左子树
		PostOrderTraverse(T->rchild); // 递归遍历右子树
		cout << T->data; // 访问根结点
	}
}

// 统计二叉树中结点的个数
int CountNodes(BiTree T) {
	if (T == NULL) return 0;
	return 1 + CountNodes(T->lchild) + CountNodes(T->rchild);
}

// 统计二叉树中叶子结点的个数
int CountLeafNodes(BiTree T) {
	if (T == NULL) return 0;
	if (T->lchild == NULL && T->rchild == NULL) return 1;
	return CountLeafNodes(T->lchild) + CountLeafNodes(T->rchild);
}

// 计算二叉树的深度
int TreeDepth(BiTree T) {
	if (T == NULL) return 0;
	int leftDepth = TreeDepth(T->lchild);
	int rightDepth = TreeDepth(T->rchild);
	return 1 + max(leftDepth, rightDepth);
}

int main() {
	char str[] = "ABC##DE#G##F###";
	int i = 0;
	
	// 创建二叉树
	BiTree T = CreateBiTree(str, i);
	
	// 遍历二叉树
	cout << "先序遍历为: ";
	PreOrderTraverse(T);
	cout << endl;
	
	cout << "中序遍历为: ";
	InOrderTraverse(T);
	cout << endl;
	
	cout << "后序遍历为: ";
	PostOrderTraverse(T);
	cout << endl;
	
	// 统计结点个数
	cout << "结点总数: " << CountNodes(T) << endl;
	
	// 统计叶子结点个数
	cout << "叶子结点数: " << CountLeafNodes(T) << endl;
	
	// 计算二叉树深度
	cout << "二叉树深度: " << TreeDepth(T) << endl;
	
	return 0;
}

