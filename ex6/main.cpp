// Mukhammadrizo Maribjonov DS-AI 4


#include <iostream>
#include <vector>

using namespace std;

// data type to store bid data for a given item
struct entry {

    //constructor of entry
    entry(size_t initialIndex, int minBid, int maxBid) : initial_index(initialIndex), min_bid(minBid),
                                                         max_bid(maxBid) {}

    // default constructor
    entry() {}

    // store the initial index of bid entry
    size_t initial_index;

    // min bid for given item
    int min_bid;

    // max_bid for given item
    int max_bid;
};

int main() {

    int input_length = 0;
    cin >> input_length;

    int min_bid, max_bid;

    // use count sort to sort bid entries by max bid
    vector<vector<entry>> List_for_sorting_by_max_bid(100001, vector<entry>());
    int count_of_entries = input_length;
    for (size_t i = 0; i < input_length; ++i) {
        cin >> min_bid >> max_bid;
        List_for_sorting_by_max_bid[max_bid].push_back(entry(i+1, min_bid, max_bid));
    }


    // use count sort to sort bid entries by min
    vector<vector<entry>> List_for_sorting_by_min_bid(101, vector<entry>());
    for (int i = 0; i < 100001 && count_of_entries; ++i) {
        if (!List_for_sorting_by_max_bid[i].empty()) {
            for (auto e : List_for_sorting_by_max_bid[i]) {
                List_for_sorting_by_min_bid[e.min_bid].push_back(e);
            }
            --count_of_entries;
        }
    }


    // output the result
    for (int i = List_for_sorting_by_min_bid.size()-1; i >= 0; --i) {
        for (auto e1 : List_for_sorting_by_min_bid[i]) {
            cout << e1.initial_index << " ";
        }
    }

    return 0;
}