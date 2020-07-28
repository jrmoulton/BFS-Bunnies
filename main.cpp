
#include "headers.h"
using namespace std;

class SimplePoint {
   public:
    int x, y, val;

    SimplePoint() { return; }

    SimplePoint(int ax, int ay, int aval) {
        x = ax;
        y = ay;
        val = aval;
    }
};

class Point : public SimplePoint {
   public:
    vector<Point *> neighbors;
    vector<SimplePoint *> history;

    Point() { return; }

    Point(int ax, int ay, int aval) {
        x = ax;
        y = ay;
        val = aval;
    }
};

template <typename T>
class Node {
   public:
    Node *pPrev, *pNext;
    T value;

    Node(T aValue) {
        pPrev = this;
        pNext = this;
        value = aValue;
    }
};

template <typename T>
class Queue {
   public:
    Node<T> *pHead, *pTail;
    int count;

    Queue() {
        pHead = nullptr;
        pTail = nullptr;
        count = 0;
    }
    Queue(T aHead) {
        Node<T> temp = Node<T>(aHead);
        pHead = &temp;
        pTail = &temp;
        count = 1;
    }

    T *pop() {
        if (count == 0) {
            return nullptr;
        }
        count -= 1;
        Node<T> *temp = pHead;
        pHead = temp->pNext;
        T *data = &temp->value;
        delete temp;
        return data;
    }

    void append(T aTail) {
        Node<T> *temp = new Node<T>(aTail);
        if (pTail == nullptr) {
            temp->pPrev = temp;
            temp->pNext = temp;
            pHead = temp;
        } else {
            temp->pPrev = pTail;
            pTail->pNext = temp;
        }
        pTail = temp;
        count += 1;
    }

    bool isEmpty() {
        if (count == 0) {
            return true;
        } else {
            return false;
        }
    }
};

const int maze1[6][6] = {
    {0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 0}, {1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0},
};

int answer(int maze[]) {
    Queue<Point> queue(Point(0, 0, 0));

    while (!queue.isEmpty()) {
        Point activePoint = *queue.pop();
        if (activePoint.x == 0 && activePoint.y == 0) {
            return 5;
            // return activePoint.history.size();
        }
    }
    return 3;
}

int main() {}
