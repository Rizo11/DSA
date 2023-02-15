// Mukhammadrizo Maribjonov DS-AI 4

#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

/* Generic keyValuePair with key T, value S, next pointer to the next pair
 */
template <typename T, typename S>
struct keyValuePair {
private:
    T key;
    S value;
    keyValuePair<T, S>* next;

public:

    keyValuePair(T key, S value) {
        this->key = key;
        this->value = value;
        this->next = NULL;
    }

    /* returns key T */
    T getKey() const {
        return key;
    }

    /* returns pointer to the keyValuePair<T, S> */
    keyValuePair<T, S>* getNext() const {
        return next;
    }

    /* returns value S*/
    S getValue() const {
        return value;
    }

    /* sets the value */
    void setValue(S value) {
        this->value = value;
    }

    /* sets the pointer to the next */
    void setNext(keyValuePair<T, S>* next) {
        keyValuePair::next = next;
    }
};

/* generic hashTable with key T and value S
 * 1. S get(T key)
 * 2. void put(T key, S value)
 * 3. default capacity of hashTable is 1, doubles everytime when lead factor is 0.75 or bigger
 * 4. hash table is implemented with singly linked list
 */
template <typename T, typename S>
class HashTable {
private:

    /* array of pointers to linked list of key-value pairs */
    vector<keyValuePair<T, S>*> db = {};

    /* vector of keys */
    vector<T> keys = {};

    /* size of the indexing table */
    size_t capacity = 0;

    /* number of elements in hash table */
    size_t size = 0;

    /* list of all keyValuePairS */
    vector<keyValuePair<T, S>*> keyValuePairs = {};

    /* returns hashcode of given key */
    size_t getHash(T& key) {
        size_t hash = std::hash<T>()(key);
        return (hash % capacity);
    }

public:

    HashTable() {
        this->capacity = 1;
        for (int i = 0; i < capacity; ++i) {
            db.push_back(NULL);
        }
    }

    /* insert or update key-value pair */
    void put(T key, S value) {

        /* rehash if load factor is greater than 0.75 */
        if (75 < (int) 100*(size/capacity)) {
            rehash();
        }

        size_t hashCode = getHash(key);

        /* if hashcode is in the table */
        if (db[hashCode] != NULL) {

            /* check linked list for presence of given key */
            keyValuePair<T, S>* currentPair = db[hashCode];
            while (currentPair != NULL) {

                /* if key exists update the keyValuePair */
                if (currentPair->getKey() == key) {
                    currentPair->setValue(value);
                    return;
                }
                currentPair = currentPair->getNext();
            }


             /* collision */
             /* if there is hash code, but no this kind of node, create a new keyValuePair and add to linked list */
            keyValuePair<T, S>* newNode = new keyValuePair<T, S>(key, value);

            currentPair = db[hashCode];
            while (currentPair->getNext() != NULL) {
                currentPair = currentPair->getNext();
            }
            currentPair->setNext(newNode);
            keys.push_back(key);
            ++size;
        }
        /* hashcode is not in the table */
        else {
            keyValuePair<T, S>* newNode = new keyValuePair<T, S>(key, value);
            db[hashCode] = newNode;
            keys.push_back(key);
            keyValuePairs.push_back(newNode);
            ++size;
        }
    }

    /* returns value associated with given key */
    S get(T key) {

        int hashCode = getHash(key);

         /* given hashCode is not is the table */
        if (db[hashCode] == NULL)
            return S();

        /* hashCode is in the table */
        else {
            keyValuePair<T, S>* current = db[hashCode];
            while (current != NULL) {
                if (current->getKey() == key)
                    return current->getValue();
                current = current->getNext();
            }
            return S();
        }
    }

    /* remove key value pair with the given key */
    void remove(T key) {

    }

    /* returns the size of the hashTable = number of entries */
    size_t getSize() {
        return this->size;
    }

    /* returns true if hashTable is empty */
    bool isEmpty() {
        return db.empty();
    }

    /* returns set of keys */
    vector<T> keySet() {
        return keys;
    }

    /* doubles the size of the hashTable and rehashes all values */
    void rehash() {
        vector<keyValuePair<T, S>*> tmp = db;
        keys.clear();
        keyValuePairs.clear();
        db.resize(2 * capacity);

        for (int i = 0; i < 2 * capacity; ++i) {
            db[i] = NULL;
        }

        size = 0;
        capacity *= 2;

        for (int i = 0; i < tmp.size(); ++i) {
            keyValuePair<T, S>* head = tmp[i];

            while (head != NULL) {
                put(head->getKey(), head->getValue());
                head = head->getNext();
            }
        }
    }

    /* returns all keyValue pairs */
    vector<keyValuePair<T, S>*> getAll() {
        return keyValuePairs;
    }
};

/* day represents one actual day of the café. It contains order ids, date, total income of the day */
struct day {

    /* date of the day */
    string date = "";

    /* total income of the day */
    double total_income_of_day;

    /* day's orders */
    vector<string> orders;


    day(const string &date, double totalIncomeOfDay) : date(date), total_income_of_day(totalIncomeOfDay) {
        orders = {};
    }

    day() {

    }

    /* returns true if day contains given id, otherwise false */
    bool contains(string id) {
        for (auto ord_id : orders) {
            if (ord_id == id) {
                return true;
            }
        }
        return false;
    }

};


/* parses given string currency to double */
void strToDouble( string strNum, double& value)
{
    value = stod(strNum.substr(1, strNum.size()-1));
}

/* parses the given line into string date, string id, string cost */
void strSplit(double& cost, string& date, string& id, string str) {
    size_t pos = 0;
    std::string token;
    string delimiter = " ";
    vector<string> result = {};
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        result.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    result.push_back(str);

    strToDouble(result[3], cost);
    date = result[0];
    id = result[2];
}

int main() {
    int nOfInputs = 0;
    string nStr;
    getline(std::cin, nStr);
    nOfInputs = stoi(nStr);

    HashTable<string, day>* cafe = new HashTable<string, day>();

    for (int i = 0; i < nOfInputs; ++i) {

        string line;
        getline(std::cin, line);

        double cost;
        string date, id;
        strSplit(cost, date, id, line);


        day today = cafe->get(date);

        /* day doesn't exist in hashTable */
        if (today.date == day().date) {
            day newDay = day(date, cost);
            newDay.orders.push_back(id);
            cafe->put(date, newDay);
        }
        /* day exists in hashTable*/
        else {

            // id does not exist
            if (!today.contains(id)) {
                today.orders.push_back(id);
                today.total_income_of_day += cost;
            }
            // id exists
            else {
                today.total_income_of_day += cost;
            }

            cafe->put(today.date, today);
        }

    }

    /* for each day print date, total income, number of unique order ids */
    for (auto &d : cafe->getAll()) {
        while (d != NULL) {
            day dv = d->getValue();
            cout << d->getKey();
            printf(" $%.2f %d\n", dv.total_income_of_day, dv.orders.size());
            d = d->getNext();
        }
    }

    return 0;
}
