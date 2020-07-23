
#include <iostream>
using namespace std;

class SimplePoint {
   public:
    int x;
    int y;
    int val;

    SimplePoint() { return; }

    SimplePoint(int ax, int ay, int aval) {
        x = ax;
        y = ay;
        val = aval;
    }
};

class Point : public SimplePoint {
   public:
    Point *neighbors[];

    Point() { return; }

    Point(int ax, int ay, int aval) {
        x = ax;
        y = ay;
        val = aval;
    }
};

class Node {
   public:
    Node *pPrev;
    Node *pNext;
    Point value;

    Node(Point aValue) {
        pPrev = this;
        pNext = this;
        value = aValue;
    }
    // Node()
};

class Queue {
   public:
    Node *pHead;
    Node *pTail;

    Queue() {
        pHead = nullptr;
        pTail = nullptr;
    }
    Queue(Node aHead) {
        pHead = &aHead;
        pTail = &aHead;
    }

    Point pop() {
        Node temp = *pHead;
        pHead = temp.pNext;
        return temp.value;
    }

    void append(Point aTail) { temp = Node(aTail); }
};

int main() {
    Queue temp(Node(Point(2, 0, 0)));
    cout << temp.pHead->value.x << endl;
}