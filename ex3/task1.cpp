#include <iostream>
#include <vector>

using namespace std;

struct Value {
    int index;
    string str;
    size_t frequency;
    Value* next;

    Value(string str, int index) {
        this->str = str;
        this->frequency = 1;
        next = NULL;
        this->index = index;
    }
};


class LinkedHash{

public:
    vector<Value*> table = {};
    vector<string> keys = {};
    int capacity;
    int counter = 0;

    size_t hashFunc(string key) {
        size_t sum = 0;
        for (auto i : key) {
            sum += i;
        }
        return (sum % this->capacity);
    }

    LinkedHash(int capacity) {
        this->capacity = capacity;
        for (int i = 0; i < this->capacity; ++i) {
            //            table[i] = NULL;
            table.push_back(NULL);
        }
    }
    int size() {
        return counter;
    }

    bool isEmpty() {
        return table.empty();
    }

    void put(string key)  {

        int hash_key = hashFunc(key);

        // if hashcode is in table
        if (table[hash_key] != NULL) {

            // check linked list for presence of this str
            Value* current = table[hash_key];
            while (current != NULL) { // here might be error current->next != NULL
                if (current->str == key) {
                    ++current->frequency;
                    return;
                }
                current = current->next;
            }

            // if there is no this kind of node, create and add to sorted linked list
            current = table[hash_key];
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new Value(key, hash_key);
            ++counter;
        }
            // hashcode not in table
        else {
            table[hash_key] = new Value(key, hash_key);
            keys.push_back(key);
            ++counter;
        }
    }

    Value* get(string key) {
        int hash_key = hashFunc(key);

        // not this kind of entry
        if (table[hash_key] == NULL)
        {
            return NULL;
        } else if (!contains(key)) {
            return NULL;
        } else {
            Value* current = table[hash_key];
            while (current->str != key) {
                current = current->next;
            }
            return current;
        }
    }

    vector<string> keySet() {
        return keys;
    }

    void print() {
        Value* current;
        Value* max = table[hashFunc(keys[0])];
        vector<Value*> maxes = {};
        for (int j = 0; j < this->counter; ++j) {

            for (int i = 0; i < this->capacity; ++i) {
                current = table[i];
                while (current != NULL) {
                    if (current->frequency > max->frequency) {
                        max = current;
                    } else if (current->frequency == max->frequency) {
                        if (max->str > current->str) {
                            max = current;
                        }
                    }
                    current = current->next;
                }

            }
            maxes.push_back(max);
            cout << max->str << " " << max->frequency << endl;
            max->frequency = 0;
        }

    }

    bool contains(string key) {

        int hash_key = hashFunc(key);

        // if hashcode is in table
        if (table[hash_key] != NULL) {

            Value* current = table[hash_key];

            while (current != NULL) {
                if (current->str == key) {
                    return true;
                }
                current = current->next;
            }
        }
        return false;
    }

    ~LinkedHash() {
    }
};
