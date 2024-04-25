#include <iostream>
#include <cassert>

using namespace std;

template<class T>
class Node {
private:
    Node* prev_;
    Node* next_;
    T data_;

public:
    Node(Node* prev, Node* next, T data) : prev_(prev), next_(next), data_(data) {}

    Node* getPrev() const {
        return prev_;
    }

    Node* getNext() const {
        return next_;
    }

    T getData() const {
        return data_;
    }

    void setPrev(Node* newPrev) {
        prev_ = newPrev;
    }

    void setNext(Node* newNext) {
        next_ = newNext;
    }

    void setData(T newData) {
        data_ = newData;
    }

    void display() {
        cout << data_;
    }
};

template<class T>
class DoublyLinkedList {
private:
    Node<T>* head_ = nullptr;
    Node<T>* tail_ = nullptr;
    int size_ = 0;

public:
    virtual ~DoublyLinkedList() {
        while (head_ != nullptr) {
            Node<T>* temp = head_;
            head_ = head_->getNext();
            delete temp;
        }
        tail_ = nullptr;
    }

    void prepend(Node<T>* nodeToPrepend) {
        if (head_ == nullptr) {
            head_ = nodeToPrepend;
            tail_ = head_;
        }
        else {
            head_->setPrev(nodeToPrepend);
            nodeToPrepend->setNext(head_);
            head_ = nodeToPrepend;
        }
        size_++;
    }

    void appendToTail(Node<T>* nodeToAppend) {
        if (head_ == nullptr) {
            head_ = nodeToAppend;
            tail_ = head_;
        }
        else {
            tail_->setNext(nodeToAppend);
            nodeToAppend->setPrev(tail_);
            tail_ = nodeToAppend;
        }
        size_++;
    }

    void insert(int index, Node<T>* nodeToInsert) {
        if (index == size_) {
            appendToTail(nodeToInsert);
            return;
        }

        Node<T>* findNode = findByIndex(index);
        if (findNode == head_ || findNode == nullptr) {
            prepend(nodeToInsert);
        }
        else {
            Node<T>* findPrev = findNode->getPrev();
            findPrev->setNext(nodeToInsert);
            nodeToInsert->setPrev(findPrev);
            nodeToInsert->setNext(findNode);
            findNode->setPrev(nodeToInsert);
        }
        size_++;
    }

    bool setValue(int index, T value) {
        Node<T>* node = findByIndex(index);
        if (node) {
            node->setData(value);
            return true;
        }
        else {
            return false;
        }
    }

    int getSize() const {
        return size_;
    }

    Node<T>* findByIndex(int index) {
        if (head_ == nullptr) {
            return nullptr;
        }
        int currIndex = 0;
        Node<T>* currNode = head_;
        while (true) {
            if (currNode == nullptr) {
                return nullptr;
            }
            if (currIndex == index) {
                return currNode;
            }
            if (currIndex > index) {
                return nullptr;
            }
            currNode = currNode->getNext();
            currIndex++;
        }
    }

    bool removeFirst() {
        if (head_ == nullptr) {
            return false;
        }
        else if (size_ == 1) {
            delete head_;
            head_ = tail_ = nullptr;
        }
        else {
            Node<T>* next = head_->getNext();
            next->setPrev(nullptr);
            delete head_;
            head_ = next;
        }
        size_--;
        return true;
    }

    bool removeLast() {
        if (head_ == nullptr) {
            return false;
        }
        else if (size_ == 1) {
            delete tail_;
            tail_ = head_ = nullptr;
        }
        else {
            Node<T>* prev = tail_->getPrev();
            prev->setNext(nullptr);
            delete tail_;
            tail_ = prev;
        }
        size_--;
        return true;
    }

    bool removeByIndex(int index) {
        if (head_ == nullptr) {
            return false;
        }
        if (head_->getNext() == nullptr && index == 0) {
            delete head_;
            head_ = tail_ = nullptr;
            size_--;
            return true;
        }
        else {
            Node<T>* node = findByIndex(index);
            if (node) {
                Node<T>* prev = node->getPrev();
                Node<T>* next = node->getNext();
                prev->setNext(next);
                next->setPrev(prev);
                delete node;
                size_--;
                return true;
            }
            else {
                return false;
            }
        }
    }

    Node<T>* getHead() const {
        return head_;
    }

    Node<T>* getTail() const {
        return tail_;
    }

    void display() {
        Node<T>* node = head_;
        cout << "[ ";
        while (node != nullptr) {
            node->display();
            node = node->getNext();
            cout << " ";
        }
        cout << "]";
    }
};

class DoublyLinkedListTester {
public:
    static void runTests() {
        testAppendToTail();
        testPrepend();
        testInsert();
        testFindByIndex();
        testRemoveFirst();
        testRemoveLast();
        testRemoveByIndex();
        testSetValue();
    }

private:
    static void testAppendToTail() {
        cout << "Test append to tail" << endl;
        DoublyLinkedList<int> linkedList;
        auto* listNode = new Node<int>(nullptr, nullptr, 30);
        linkedList.appendToTail(listNode);
        cout << "Result: ";
        linkedList.display();
        cout << "\n" << endl;
        assert(linkedList.getSize() == 1);
        assert(linkedList.getTail()->getData() == 30);
    }

    static void testPrepend() {
        cout << "Test prepend" << endl;
        DoublyLinkedList<int> linkedList;
        auto* listNode1 = new Node<int>(nullptr, nullptr, 10);
        auto* listNode2 = new Node<int>(nullptr, nullptr, 20);
        linkedList.prepend(listNode1);
        linkedList.prepend(listNode2);
        cout << "Result: ";
        linkedList.display();
        cout << "\n" << endl;
        assert(linkedList.getSize() == 2);
        assert(linkedList.getHead()->getData() == 20);
        assert(linkedList.getTail()->getData() == 10);
    }

    static void testInsert() {
        cout << "Test insert" << endl;
        DoublyLinkedList<int> linkedList;
        auto* listNode1 = new Node<int>(nullptr, nullptr, 10);
        auto* listNode2 = new Node<int>(nullptr, nullptr, 20);
        auto* listNode3 = new Node<int>(nullptr, nullptr, 30);
        linkedList.prepend(listNode1);
        linkedList.insert(1, listNode2);
        linkedList.insert(2, listNode3);
        cout << "Result: ";
        linkedList.display();
        cout << "\n" << endl;
        assert(linkedList.getSize() == 3);
        assert(linkedList.getTail()->getData() == 30);
        assert(linkedList.getHead()->getNext()->getData() == 20);
        assert(linkedList.getHead()->getNext()->getNext()->getData() == 30);
    }

    static void testFindByIndex() {
        cout << "Test find by index" << endl;
        DoublyLinkedList<int> linkedList;
        auto* listNode1 = new Node<int>(nullptr, nullptr, 10);
        auto* listNode2 = new Node<int>(nullptr, nullptr, 20);
        linkedList.prepend(listNode1);
        linkedList.prepend(listNode2);
        Node<int>* foundNode = linkedList.findByIndex(1);
        cout << "Found node: ";
        foundNode->display();
        cout << "\n" << endl;
        assert(foundNode->getData() == 10);
    }

    static void testRemoveFirst() {
        cout << "Test remove first" << endl;
        DoublyLinkedList<int> linkedList;
        auto* listNode1 = new Node<int>(nullptr, nullptr, 10);
        auto* listNode2 = new Node<int>(nullptr, nullptr, 20);
        linkedList.prepend(listNode1);
        linkedList.prepend(listNode2);
        linkedList.removeFirst();
        cout << "Result: ";
        linkedList.display();
        cout << "\n" << endl;
        assert(linkedList.getSize() == 1);
        assert(linkedList.getHead()->getData() == 10);
    }

    static void testRemoveLast() {
        cout << "Test remove last" << endl;
        DoublyLinkedList<int> linkedList;
        auto* listNode1 = new Node<int>(nullptr, nullptr, 10);
        auto* listNode2 = new Node<int>(nullptr, nullptr, 20);
        linkedList.prepend(listNode1);
        linkedList.prepend(listNode2);
        linkedList.removeLast();
        cout << "Result: ";
        linkedList.display();
        cout << "\n" << endl;
        assert(linkedList.getSize() == 1);
        assert(linkedList.getTail()->getData() == 20);
    }

    static void testRemoveByIndex() {
        cout << "Test remove by index" << endl;
        DoublyLinkedList<int> linkedList;
        auto* listNode1 = new Node<int>(nullptr, nullptr, 10);
        auto* listNode2 = new Node<int>(nullptr, nullptr, 20);
        auto* listNode3 = new Node<int>(nullptr, nullptr, 30);
        linkedList.prepend(listNode1);
        linkedList.prepend(listNode2);
        linkedList.prepend(listNode3);
        linkedList.removeByIndex(1);
        cout << "Result: ";
        linkedList.display();
        cout << "\n" << endl;
        assert(linkedList.getSize() == 2);
        assert(linkedList.getHead()->getData() == 30);
    }

    static void testSetValue() {
        cout << "Test set value" << endl;
        DoublyLinkedList<int> linkedList;
        auto* listNode1 = new Node<int>(nullptr, nullptr, 10);
        auto* listNode2 = new Node<int>(nullptr, nullptr, 20);
        linkedList.prepend(listNode1);
        linkedList.prepend(listNode2);

        bool result = linkedList.setValue(1, 30);
        cout << "Result: ";
        linkedList.display();
        cout << "\n" << endl;

        assert(result == true);
        assert(linkedList.findByIndex(1)->getData() == 30);

        result = linkedList.setValue(3, 40);

        assert(result == false);
    }
};

int main() {
    DoublyLinkedListTester::runTests();

    std::cout << "All tests passed successfully" << std::endl;

    return 0;
}