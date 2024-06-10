#include <iostream>  
using namespace std;  
  
#define MAXSIZE 5 
  
class CircularQueue {  

    int Q[MAXSIZE];  
    int front;  
    int rear;  
    int tag;  
    int m;  
  
public:  
    CircularQueue(int size) : m(size), front(0), rear(0), tag(0) {}  
  
    // �������Ƿ�Ϊ��  
    bool isEmpty() {  
        return tag == 0 && front == rear;  
    }  
  
    // �������Ƿ�����  
    bool isFull() {  
        return tag == 1 && front == rear;  
    }  
  
    // ��Ӳ���  
    bool enqueue(int x) {  
        if (isFull()) {  
            cout << "����������" << endl;  
            return false;  
        }  
  
        Q[rear] = x;  
        rear = (rear + 1) % m;  
  
        if (front == rear) {  
            tag = 1; // 
        }  
        return true;  
    }  
  
    // ���Ӳ���  
    bool dequeue(int& x) {  
        if (isEmpty()) {  
            cout << "�����ǿյ�" << endl;  
            return false;  
        }  
  
        x = Q[front];  
        front = (front + 1) % m;  
  
        if (front == rear) {  
            tag = 0; // ���п�  
        }  
        return true;  
    }  
  
    // ��ӡ����Ԫ��  
    void printQueue() {  
        if (isEmpty()) {  
            cout << "�����ǿյ�" << endl;  
            return;  
        }  
  
        cout << "����Ԫ�� ";  
        int i = front;  
        while (i != rear) {  
            cout << Q[i] << " ";  
            i = (i + 1) % m;  
        }  
        cout << endl;  
    }  
};  
  
int main() {  

	
    CircularQueue q(MAXSIZE);  
    int data;  
  
    // ��Ӳ���  
    q.enqueue(1);  
    q.enqueue(2);  
    q.enqueue(3);  
    q.printQueue(); 
  
    // ���Ӳ���  
    q.dequeue(data);  
    cout << "���� " << data << endl; 
    q.printQueue();
  
    // �ٴ����ֱ��������  
    for (int i = 4; i <= MAXSIZE; ++i) {  
        if (!q.enqueue(i)) {  
            break;  
        }  
    }  
    q.printQueue(); 
  
    // �ٴγ�����ӣ�Ӧʧ��  
    if (!q.enqueue(MAXSIZE + 1)) {  
        cout << "��������" << endl;  
    }  
  
    // ����ֱ�����п�  
    while (!q.isEmpty()) {  
        q.dequeue(data);  
        cout << "����Ԫ�� " << data << endl;  
    }  
  
    q.printQueue();   
  
    return 0;  
}
