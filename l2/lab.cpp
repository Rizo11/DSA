#include <iostream>

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


int main()
{
	STACK<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	s.push(5);

	cout << "Stack size: " << s.stackSize() << endl;

	cout << s.pop() << endl;

	cout << s.peek() << endl;

    cout << s.pop() << endl;
    cout << s.pop() << endl;
    cout << s.pop() << endl;
    cout << s.pop() << endl;

	cout << "finish" << endl;

    QUEUE<int> q;
    QUEUE<string> qs;
    q.offer(1);
    q.offer(2);
    q.offer(3);
    q.offer(4);
    int a = q.pool();
    qs.offer("Yehia");
    cout << qs.pool() << endl;
    qs.offer("Osama");
    cout << qs.pool() << endl;



    return 0;
}