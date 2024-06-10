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
  
    // 检查队列是否为空  
    bool isEmpty() {  
        return tag == 0 && front == rear;  
    }  
  
    // 检查队列是否已满  
    bool isFull() {  
        return tag == 1 && front == rear;  
    }  
  
    // 入队操作  
    bool enqueue(int x) {  
        if (isFull()) {  
            cout << "队列是满的" << endl;  
            return false;  
        }  
  
        Q[rear] = x;  
        rear = (rear + 1) % m;  
  
        if (front == rear) {  
            tag = 1; // 
        }  
        return true;  
    }  
  
    // 出队操作  
    bool dequeue(int& x) {  
        if (isEmpty()) {  
            cout << "队列是空的" << endl;  
            return false;  
        }  
  
        x = Q[front];  
        front = (front + 1) % m;  
  
        if (front == rear) {  
            tag = 0; // 队列空  
        }  
        return true;  
    }  
  
    // 打印队列元素  
    void printQueue() {  
        if (isEmpty()) {  
            cout << "队列是空的" << endl;  
            return;  
        }  
  
        cout << "队列元素 ";  
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
  
    // 入队操作  
    q.enqueue(1);  
    q.enqueue(2);  
    q.enqueue(3);  
    q.printQueue(); 
  
    // 出队操作  
    q.dequeue(data);  
    cout << "出队 " << data << endl; 
    q.printQueue();
  
    // 再次入队直到队列满  
    for (int i = 4; i <= MAXSIZE; ++i) {  
        if (!q.enqueue(i)) {  
            break;  
        }  
    }  
    q.printQueue(); 
  
    // 再次尝试入队，应失败  
    if (!q.enqueue(MAXSIZE + 1)) {  
        cout << "队列满的" << endl;  
    }  
  
    // 出队直到队列空  
    while (!q.isEmpty()) {  
        q.dequeue(data);  
        cout << "队列元素 " << data << endl;  
    }  
  
    q.printQueue();   
  
    return 0;  
}
