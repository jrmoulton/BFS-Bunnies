
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
    int saldo = 0;
    SimplePoint simple;
    vector<SimplePoint> neighbors;
    vector<SimplePoint> history;

    // Point() { return; }

    Point(int ax, int ay, int aval) {
        x = ax;
        y = ay;
        val = aval;
        simple = SimplePoint(ax, ay, aval);
    }
    Point(SimplePoint temp) {
        x = temp.x;
        y = temp.y;
        val = temp.val;
        simple = SimplePoint(temp.x, temp.y, temp.val);
    }
    vector<SimplePoint> getNeighbors(vector<vector<int>> *maze) {
        vector<SimplePoint> temp;
        if (x != 0) {
            temp.push_back(SimplePoint(x - 1, y, (*maze)[y][x - 1]));
        }
        if (x != (*maze)[0].size() - 1) {
            temp.push_back(SimplePoint(x + 1, y, (*maze)[y][x + 1]));
        }
        if (y != 0) {
            temp.push_back(SimplePoint(x, y - 1, (*maze)[y - 1][x]));
        }
        if (y != (*maze).size() - 1) {
            temp.push_back(SimplePoint(x, y + 1, (*maze)[y + 1][x]));
        }
        return temp;
    }
};

template <typename T>
class Node {
   public:
    Node *pPrev, *pNext;
    T value;

    Node(T aValue) : value(aValue) {
        pNext = this;
        // value = aValue;
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
        Node<T> *temp = new Node<T>(aHead);
        pHead = temp;
        pTail = temp;
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

const vector<vector<int>> maze1 = {
    {0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 0}, {1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0},
};

int answer(vector<vector<int>> maze) {
    Point startPoint = Point(0, 0, 0);
    startPoint.neighbors = startPoint.getNeighbors(&maze);
    Queue<Point> queue(startPoint);

    while (!queue.isEmpty()) {
        Point activePoint = *queue.pop();
        activePoint.history.push_back(activePoint.simple);
        if (activePoint.x == maze[0].size() - 1 &&
            activePoint.y == maze.size() - 1) {
            return activePoint.history.size();
        }
        for (const SimplePoint &neighbor : activePoint.neighbors) {
            Point temp = Point(neighbor);
            temp.history = activePoint.history;
            temp.neighbors = temp.getNeighbors(&maze);
            if (neighbor.val == 0) {
                temp.saldo = activePoint.saldo;
            } else {
                if (activePoint.saldo >= 1) {
                    temp.saldo += 1;
                }
            }
        }
    }
    return 100000;
}

int main() { std::cout << answer(maze1) << endl; }
