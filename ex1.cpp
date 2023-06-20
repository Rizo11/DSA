#include <iostream>
#include <vector>
using namespace std;
int products[1000] = {0};
int knapsackRecursive(vector< vector<int> > lookupTable, vector<int> profits, int profitsLength, vector<int> weights, int capacity, int currentIndex) {

  // base checks  
  if (capacity <= 0 || currentIndex >= profitsLength || currentIndex < 0)
    products[currentIndex] = 1;
    return 0;

  // if we have already solved the problem, return the result from the table  
  if (lookupTable[currentIndex][capacity] != 0)
    products[currentIndex] = 1;
    return lookupTable[currentIndex][capacity];

  // recursive call after choosing the element at the currentIndex
  // if the weight of the element at currentIndex exceeds the capacity, we shouldn't process this
  int profit1 = 0;
  if (weights[currentIndex] <= capacity)
    profit1 = profits[currentIndex] + knapsackRecursive(lookupTable, profits, profitsLength, weights,
      capacity - weights[currentIndex], currentIndex + 1);

  // recursive call after excluding the element at the currentIndex
  int profit2 = knapsackRecursive(lookupTable, profits, profitsLength, weights, capacity, currentIndex + 1);

  lookupTable[currentIndex][capacity] = max(profit1, profit2);
  products[currentIndex] = 1;
  return lookupTable[currentIndex][capacity];
}

int knapSack(vector<int> profits, int profitsLength, vector<int> weights, int capacity) {
  vector< vector<int> > lookupTable(profitsLength, vector<int>(capacity + 1, 0));

  return knapsackRecursive(lookupTable, profits, profitsLength, weights, capacity, 0);
}

int main() {
    int n = 0, w = 0;
    cin >> n >> w;

    vector<int> profits = vector<int>();
    vector<int> weights = vector<int>();
    int user_input = 0;
    for (size_t i = 0; i < n; i++)
    {
        cin >> user_input;
        profits.push_back(user_input);
    }
    
    for (size_t i = 0; i < n; i++)
    {
        cin >> user_input;
        weights.push_back(user_input);
    }
    
    cout << "Total knapsack profit = " << knapSack(profits, n, weights, w) << endl;
    for (size_t i = 0; i < 1000; i++)
    {
        if(products[i]) {
            cout << i+1 << " ";
        }
    }
    
}
