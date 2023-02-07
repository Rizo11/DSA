//
// Created by rizo on 2/6/23.
//

#include "task2.h"
// DS-AI 4
// Mukhammadrizo Maribjonov

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Value {
    int index;
    string str;
    size_t frequency;
    Value* next;
    Value* end;

    Value(string str, int index) {
        this->str = str;
        this->frequency = 1;
        next = end = NULL;
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
            while (current != NULL) {
                if (current->str == key) {
                    ++current->frequency;
                    return;
                }
                current = current->next;
            }


            // collision
            // if there is hash code, but no this kind of node, create and add to sorted linked list
            current = table[hash_key];
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new Value(key, hash_key);
            keys.push_back(key);
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
        }
        else {
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
        for ( auto key : keys) {
            Value* current = table[hashFunc(key)];
            while (current->str != key) {
                current = current->next;
            }

            cout << current->str << endl;
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

void task2() {
    int n = 0;
    cin >> n;
    LinkedHash* db1 = new LinkedHash(n);
    for (int i = 0; i < n; ++i) {
        string input;
        cin >> input;
        db1->put(input);
    }

    cin >> n;
    LinkedHash* db2 = new LinkedHash(n);
    for (int i = 0; i < n; ++i) {
        string input;
        cin >> input;
        if ( !db1->contains(input) ) {
            db2->put(input);
        }
    }
    if (db2->size() == 0) {
        return;
    }
    cout << db2->size() << endl;
    db2->print();
}
