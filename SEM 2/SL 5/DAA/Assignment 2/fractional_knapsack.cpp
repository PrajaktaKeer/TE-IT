#include<bits/stdc++.h>
using namespace std;

struct Item {
	int idx, weight, value;
};

bool cmpPairs(struct Item p1, struct Item p2)
{
    double r1 = (double)p1.value / (double)p1.weight;
    double r2 = (double)p2.value / (double)p2.weight;
    return r1 > r2;
}

void fractionalKnapsack(vector<Item>itemsWeights, int capacity) {
	sort(itemsWeights.begin(), itemsWeights.end(), cmpPairs); //sort the items on basis of value/weight ratio in descending order

    cout << "\n--------VALUE/WEIGHT RATIO OF EACH ITEM--------\n";
    for (int i = 0; i < itemsWeights.size(); i++)
        cout << "ITEM " << itemsWeights[i].idx << " Value = " << itemsWeights[i].value
    << " Weight = " << itemsWeights[i].weight
     << " Ratio = " << itemsWeights[i].value / itemsWeights[i].weight << endl;

    double maxValue = 0.0; // Result (value in Knapsack)
 
    cout << "\n-------PORTION OF EACH ITEM USED-------\n";
    // Looping through all Items
    for (int i = 0; i < itemsWeights.size(); i++) {
        // If adding Item won't overflow, add it completely
        if (itemsWeights[i].weight <= capacity) {
            cout << "ITEM " << itemsWeights[i].idx << " Portion = 1" << endl; 
            maxValue += itemsWeights[i].value;
            capacity -= itemsWeights[i].weight;
        }
        // If we can't add current Item, add fractional part of it
        else {
            cout << "ITEM " << itemsWeights[i].idx << " Portion = " 
            << (double)capacity / (double)itemsWeights[i].weight << endl; 
            maxValue += itemsWeights[i].value * ((double)capacity / (double)itemsWeights[i].weight);
            break;
        }
    }
 	
 	cout << "\nMaximum value we can obtain = " << maxValue << endl;
}

int main() {
	Item item;
	int noOfItems, capacity;
	cout << "\nEnter the number of items : ";
	cin >> noOfItems;
	cout << "\nEnter the capacity of knapsack : ";
	cin >> capacity;
	vector<Item>itemsWeights(noOfItems);

	for(int i = 0; i < noOfItems; i++) {
		cout << "Enter the value and weight of item " << i+1 << " : ";
		itemsWeights[i].idx = i + 1;
		cin >> itemsWeights[i].value >> itemsWeights[i].weight;
	}

	fractionalKnapsack(itemsWeights, capacity);
}

/*OUTPUT : 

Enter the number of items : 3

Enter the capacity of knapsack : 50
Enter the value and weight of item 1 : 100 20
Enter the value and weight of item 2 : 60 10
Enter the value and weight of item 3 : 120 30

--------VALUE/WEIGHT RATIO OF EACH ITEM--------
ITEM 2 Value = 60 Weight = 10 Ratio = 6
ITEM 1 Value = 100 Weight = 20 Ratio = 5
ITEM 3 Value = 120 Weight = 30 Ratio = 4

-------PORTION OF EACH ITEM USED-------
ITEM 2 Portion = 1
ITEM 1 Portion = 1
ITEM 3 Portion = 0.666667

Maximum value we can obtain = 240*/
