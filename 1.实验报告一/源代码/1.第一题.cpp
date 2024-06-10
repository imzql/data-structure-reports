#include <iostream>
using namespace std;

const int MAX_SIZE = 50; // 定义顺序表的最大长度

struct SeqList {
	int data[MAX_SIZE]; // 顺序表的元素数组
	int length;         // 顺序表的当前长度
};

// 初始化顺序表
void initList(SeqList &list) {
	list.length = 0; // 初始长度为0
}

// 输出顺序表中的所有元素
void printList(SeqList list) {
	cout << "顺序表中的元素为：";
	for (int i = 0; i < list.length; ++i) {
		cout << list.data[i] << " ";
	}
	cout << endl;
}

// 在顺序表中查找元素值为key的元素，返回其位置，若不存在返回-1
int search(SeqList list, int key) {
	for (int i = 0; i < list.length; ++i) {
		if (list.data[i] == key) {
			return i; // 找到了，返回位置
		}
	}
	return -1; // 没找到，返回-1
}

// 在顺序表的指定位置插入元素value
bool insert(SeqList &list, int pos, int value) {
	if (pos < 1 || pos > list.length + 1 || list.length == MAX_SIZE) {
		return false; // 插入位置不合法或顺序表已满，插入失败
	}
	for (int i = list.length; i >= pos; --i) {
		list.data[i] = list.data[i - 1]; // 依次向后移动元素，腾出位置
	}
	list.data[pos - 1] = value; // 在腾出的位置插入新元素
	++list.length; // 长度加1
	return true; // 插入成功
}

// 在顺序表中删除指定位置的元素
bool remove(SeqList &list, int pos) {
	if (pos < 1 || pos > list.length) {
		return false; // 删除位置不合法，删除失败
	}
	for (int i = pos; i < list.length; ++i) {
		list.data[i - 1] = list.data[i]; // 依次向前移动元素，覆盖被删除的元素
	}
	--list.length; // 长度减1
	return true; // 删除成功
}

// 获取顺序表中指定位置的元素值
int getElement(SeqList list, int pos) {
	if (pos < 1 || pos > list.length) {
		return -1; // 位置不合法，返回-1表示错误
	}
	return list.data[pos - 1];
}

// 获取顺序表的长度
int length(SeqList list) {
	return list.length;
}

// 获取顺序表中的最大值
int getMax(SeqList list) {
	if (list.length == 0) {
		return -1; // 顺序表为空，返回-1表示错误
	}
	int max = list.data[0]; // 假设第一个元素最大
	for (int i = 1; i < list.length; ++i) {
		if (list.data[i] > max) {
			max = list.data[i]; // 更新最大值
		}
	}
	return max; // 返回最大值
}

int main() {
	SeqList list;
	initList(list);
	
	// 1、从键盘输入元素值
	cout << "请输入顺序表中的元素值：" << endl;
	for (int i = 0; i < 8; ++i) {
		cin >> list.data[i];
		++list.length;
	}
	
	// 2、输出顺序表中所有元素
	printList(list);
	
	// 3、查找元素28和25
	int pos28 = search(list, 28);
	int pos25 = search(list, 25);
	if (pos28 != -1) {
		cout << "顺序表中存在元素28，位置为：" << pos28 + 1 << endl;
	} else {
		cout << "顺序表中不存在元素28" << endl;
	}
	if (pos25 != -1) {
		cout << "顺序表中存在元素25，位置为：" << pos25 + 1 << endl;
	} else {
		cout << "顺序表中不存在元素25" << endl;
	}
	
	// 4、在顺序表中第五个位置插入元素9
	insert(list, 5, 9);
	cout << "在顺序表中第五个位置插入元素9后的顺序表：" << endl;
	printList(list);
	
	// 5、删除顺序表中第五个位置的元素
	remove(list, 5);
	cout << "删除顺序表中第五个位置的元素后的顺序表：" << endl;
	printList(list);
	
	// 6、取出第三个位置的值并输出
	int element = getElement(list, 3);
	cout << "顺序表中第三个位置的元素值为：" << element << endl;
	
	// 7、输出顺序表的长度
	cout << "顺序表的长度为：" << length(list) << endl;
	
	// 8、取最大值
	int max = getMax(list);
	if (max != -1) {
		cout << "顺序表中的最大值为：" << max << endl;
	} else {
		cout << "顺序表为空，无最大值" << endl;
	}
	
	return 0;
}

