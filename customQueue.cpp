#include <optional>
#include <vector>

template <typename T>
class Node {
   public:
    Node *pPrev, *pNext;
    T value;

    Node(T aValue) : value(aValue) {}
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

    std::optional<T> pop() {
        if (count == 0) {
            return std::nullopt;
        }
        count -= 1;
        Node<T> *temp = pHead;
        pHead = temp->pNext;
        T data = temp->value;
        delete temp;
        return data;
    }

    void append(T aTail) {
        Node<T> *temp = new Node<T>(aTail);
        if (count == 0) {
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

    bool empty() {
        if (count == 0) {
            return true;
        } else {
            return false;
        }
    }
};