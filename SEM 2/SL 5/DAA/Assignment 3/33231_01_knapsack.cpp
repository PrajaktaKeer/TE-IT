/* Given weight and value array and weight of knapsack, compute the max profit that can be obtained*/
/*Roll No : 33231
Batch : L10 */

#include<bits/stdc++.h>
using namespace std;

int knapsack(vector<int>wt, vector<int>val, int W, int N) {
	vector<vector<int>>t(N+1, vector<int> (W+1, 0));

	for(int i = 1; i < N+1; i++) {
		for(int j = 1; j < W+1; j++) {
			if(wt[i-1] <= j)
				t[i][j] = max(val[i-1] + t[i-1][j-wt[i-1]], t[i-1][j]);
			else
				t[i][j] = t[i-1][j];
		}
	}
	return t[N][W];
}

int main() {
	int noOfItems, weightOfKnapsack;
	cout << "\nEnter number of items : ";
	cin >> noOfItems;

	vector<int>wt(noOfItems), val(noOfItems);

	cout << "\nEnter weight of knapsack : ";
	cin >> weightOfKnapsack;

	for(int i = 0; i < noOfItems; i++) {
		cout << "\nEnter weight and value of Item " << i+1 << " : ";
		cin >> wt[i] >> val[i];
	}

	cout << "Max Profit = " << knapsack(wt, val, weightOfKnapsack, noOfItems) << endl;
}

/*OUTPUT :
Enter number of items : 3

Enter weight of knapsack : 50

Enter weight and value of Item 1 : 10 60

Enter weight and value of Item 2 : 20 100

Enter weight and value of Item 3 : 30 120
Max Profit = 220
*/
