// Mukhammadrizo Maribjonov DS-AI 4

#include <iostream>
#include  <bits/stdc++.h>

using namespace std;

using namespace std;

template<typename T>

class Node {
public:
    T value;
    Node* next;

    Node(T data) {
        this->value = data;
        this->next = nullptr;
    }
};

template<typename T>

class STACK {
private:
    Node<T> *top;
    int size;

public:
    STACK(){
        size = 0;
    }

    void push(T value){
        Node<T> *newNode = new Node(value);
        newNode->value = value;
        newNode->next = top;
        top = newNode;
        ++size;
    }

    T pop(){

        if (isEmpty()) {
            throw out_of_range("STACK IS EMPTY");
        }
        Node<T>* temp = top;
        top = top->next;
        T popValue = temp->value;
        free(temp);
        return popValue;
    }

    T peek() {
        if (isEmpty()) {
            throw out_of_range("STACK IS EMPTY");
        }
        return top->value;
    }

    int stackSize() {
        return size;
    }

    /* returns true if empty */
    bool isEmpty() {
        return top == nullptr;
    }
};

template <typename N>
struct L_Node {
    N value;
    L_Node* next;

    L_Node(N value) {
        this->value = value;
        next = nullptr;
    }
};

template <typename N>
class Linked_List {
public:

    L_Node<N>* head;
    Linked_List() {
        head = nullptr;
    }

    // Function to insert a
    // node at the end of the
    // linked list.
    void insertNode(N data) {
        // Create the new Node.
        L_Node<N> *newNode = new L_Node<N>(data);

        // Assign to head
        if (head == nullptr) {
            head = newNode;
            return;
        }

        // Traverse till end of list
        L_Node<N> *temp = head;
        while (temp->next != nullptr) {

            // Update temp
            temp = temp->next;
        }

        // Insert at the last.
        temp->next = newNode;
    }

    // Function to print the
    // linked list.
    void printList();

    // Function to delete the
    // node at given position
    void deleteNode(int nodeOffset)
    {
        L_Node<N> temp1 = head, *temp2 = nullptr;
        int ListLen = 0;

        if (head == nullptr) {
            cout << "List empty." << endl;
            return;
        }

        // Find length of the linked-list.
        while (temp1 != nullptr) {
            temp1 = temp1->next;
            ListLen++;
        }

        // Check if the position to be
        // deleted is greater than the length
        // of the linked list.
        if (ListLen < nodeOffset) {
            cout << "Index out of range"
                 << endl;
            return;
        }

        // Declare temp1
        temp1 = head;

        // Deleting the head.
        if (nodeOffset == 1) {

            // Update head
            head = head->next;
            delete temp1;
            return;
        }

        // Traverse the list to
        // find the node to be deleted.
        while (nodeOffset-- > 1) {

            // Update temp2
            temp2 = temp1;

            // Update temp1
            temp1 = temp1->next;
        }

        // Change the next pointer
        // of the previous node.
        temp2->next = temp1->next;

        // Delete the node
        delete temp1;
    }
};

void strSplit(Linked_List<string>* result, string str) {
    size_t pos = 0;
    std::string token;
    string delimiter = " ";
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        result->insertNode(token);
        str.erase(0, pos + delimiter.length());
    }
    result->insertNode(str);
}

/* returns true if str is delimiter */
bool isDelimiter(string* all_delimiters, int size, string str, bool& isDelimiter, size_t& index, bool& isClosing) {
    for (int i = 0; i < size; ++i) {
        if (all_delimiters[i] == str) {
            index = i;
            isDelimiter = true;
            if (i % 2 == 1) {
                isClosing = true;
            }
            return true;
        }
    }

    return false;
}

string findPair(string* all_delimiters, int size, string delimiter) {
    for (int i = 0; i < size; ++i) {
        if (all_delimiters[i] == delimiter) {
            if (i % 2 == 0) {
                return all_delimiters[++i];
            }

            return all_delimiters[--i];
        }
    }
}

int main() {
    int nOfDelimeters = 0, kOfLines = 0;
    cin >> nOfDelimeters >> kOfLines;

    if (nOfDelimeters == 0) {
        cout << "The input is properly balanced." << endl;
        return 0;
    }

    string delimeters[100];
    Linked_List<string>* lines[100];
    string line;
    getline(cin, line);

    for (int i = 0; i < 2*nOfDelimeters; ++i) {
        string delimeter1, delimeter2;
        cin >> delimeter1 >> delimeter2;
        delimeters[i] = delimeter1;
        delimeters[++i] = delimeter2;
    }

    getline(cin, line);
    STACK<string>* current_delims = new STACK<string>();
    for (int i = 0; i < kOfLines; ++i) {
        getline(cin, line);
        Linked_List<string>* split_line = new Linked_List<string>();
        strSplit(split_line, line);
        lines[i] = split_line;

    }

    for (int i = 0; i < kOfLines; ++i) {
        L_Node<string>* word = lines[i]->head;
        size_t symbolCount = 0;
        while (word != nullptr) {

            symbolCount += word->value.size();


            bool isDelim = false;
            bool closing = false;
            size_t delimIndex = 0;

            // check for current word is delimiter
            isDelimiter(delimeters, 2*nOfDelimeters, word->value, isDelim, delimIndex, closing);

            if (isDelim) {

                if (current_delims->isEmpty()) {
                    // } hello
                    if (closing) {
                        cout << "Error in line " << i + 1 << ", column: " << symbolCount << " unexpected closing token " << word->value << "." << endl;
                        return 0;
                    }

                    // { hello
                    current_delims->push(word->value);
                } else if (closing) {
                    if (current_delims->peek() != delimeters[delimIndex-1]) {
                        string expected = findPair(delimeters, 2*nOfDelimeters, current_delims->peek());
                        cout << "Error in line " << i + 1 << ", column " << symbolCount << ": expected " << expected << " but got " << delimeters[delimIndex] << "." << endl;
                        return 0;
                    }

                    current_delims->pop();
                } else if (!closing) {
                    current_delims->push(word->value);
                }
            }

            if (word->next != nullptr) {
                ++symbolCount;
            } else {
                if (i == kOfLines-1 && !current_delims->isEmpty()) {
                    string expected = findPair(delimeters, 2*nOfDelimeters, current_delims->peek());
                    cout << "Error in line " << i + 1 << ", column " << symbolCount+2 << ": expected " << expected << " but got end of input." << endl;
                    return 0;
                }
            }

            word = word->next;
        }


    }
    cout << "The input is properly balanced." << endl;
    return 0;
}