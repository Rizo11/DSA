// Mukhammadrizo Maribjonov DS-AI 4

#include <iostream>
#include  <bits/stdc++.h>

using namespace std;

template<typename T>

class Node {
    public:
        T value;
        Node* next;

        Node(T data) {
            this->value = data;
            this->next = NULL;
        }
};

template<typename T>
class QUEUE {

    private:
        Node<T> * front;
        Node<T> * rear;
        int volume;
    public:
        QUEUE() {
            volume = 0;
            front = nullptr;
            rear = nullptr;
        }

        void offer(T value) {
            Node<T>* newNodePrt = new Node(value);

            if (rear == nullptr) {
                front = rear = newNodePrt;
                return;
            }

            rear->next = newNodePrt;
            rear = newNodePrt;
            ++volume;
        }

        T pool() {

            if (front == nullptr) {
                throw out_of_range("QUEUE IS EMPTY");
            }

            Node<T>* tmpNode = front;
            front = front->next;
            --volume;

            if (front == nullptr) {
                rear = nullptr;
            }

            T returnValue = tmpNode->value;
            delete(tmpNode);
            return returnValue;
        }

        T peek() {
            if (front == nullptr) {
                return nullptr;
            }

            return front;
        }

        int size() {
            return volume;
        }

        bool isEmpty() {
            return volume == 0;
        }
};

template<typename T>

class STACK {
    private:
        Node<T> *top;
        Node<T> *bottom;
        int size;

    public:
        STACK(){
            size = 0;
        }

        void push(T value){
            Node<T> *newNode = new Node(value);
            newNode->next = top->next;
            top->next = newNode;
            ++size;
        }

        T pop(){

			if (isEmpty()) {
                throw out_of_range("STACK IS EMPTY");
			}
            Node<T> *popNode = top->next;
            T popValue = popNode->value;
            top->next = popNode->next;
            --size;
            delete(popNode);
            return popValue;
        }

        T peek() {
            if (isEmpty()) {
                throw out_of_range("STACK IS EMPTY");
            }
            return top->next->value;
        }

        int stackSize() {
            return size;
        }

        bool isEmpty() {
            return size == 0;
        }
};

QUEUE<string> splitstr(string str, string deli = " ")
{
    int start = 0;
    int end = str.find(deli);
    QUEUE<string> strings;
    while (end != -1) {
        strings.offer(str.substr(start, end - start));
        start = end + deli.size();
        end = str.find(deli, start);
    }

    strings.offer(str.substr(start, end - start));

    return strings;
}

int main() {
    char line[1000];
    cin.getline(line, 1000);
    splitstr(line, " ");

    return 0;
}