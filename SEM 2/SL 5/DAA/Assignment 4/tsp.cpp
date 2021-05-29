#include<bits/stdc++.h>
using namespace std;

int n, root = 0; //no of cities
vector<vector<int>>distMat(4, vector<int>(4, 0));
vector<vector<int>>path(16, vector<int>(4, -1));

int tsp(int mask, int pos) {
    vector<vector<int>>dp(16, vector<int>(4, -1));

    //if all cities are visited
    if(mask == (1<<n) -1)
        return distMat[pos][0];

    if(dp[mask][pos] != -1)
       return dp[mask][pos];

    //Now from current node, we will try to go to every other node and take the min ans
    int ans = INT_MAX;

    //Visit all the unvisited cities and take the best route
    for(int city = 0; city < n; city++){
        if((mask & (1<<city)) == 0){
            int newAns = distMat[pos][city] + tsp( mask | (1<<city), city);
            if(newAns < ans)
                path[mask][pos] = city;
            ans = min(ans, newAns);
        }
    }
    return dp[mask][pos] = ans;
}

void display_path() {
    vector<int>v(n, -1);
    int source = 0;
    cout << "\nThe travelled path is : 1 ";
    for(int count = 0; count < n-1; ) {
        for(int i = 0; i < (1<<n); i++)
        {
            if(path[i][source] != -1 && v[path[i][source]] == -1)
            {
                v[path[i][source]]++;
                source = path[i][source];
                cout << " -> " << source + 1;
                count++;
                break;
            }
        }
    }
    cout << " -> 1" << endl;
}

int main() { 
    cout << "\nEnter the number of cities : ";
    cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
          cout << "\nEnter the weight of Edge " << i << " - " << j << " : ";
          cin >> distMat[i][j];
        }
    }

    cout << "\nThe distance matrix is : \n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) 
          cout << distMat[i][j] << "\t";
        cout << "\n";
    }
    cout<<"Travelling Salesman Distance is : "<< tsp(1, 0) << endl;
    display_path();
}

/*OUTPUT : 
Enter the number of cities : 4

Enter the weight of Edge 0 - 0 : 0

Enter the weight of Edge 0 - 1 : 10

Enter the weight of Edge 0 - 2 : 15

Enter the weight of Edge 0 - 3 : 20

Enter the weight of Edge 1 - 0 : 5

Enter the weight of Edge 1 - 1 : 0

Enter the weight of Edge 1 - 2 : 9

Enter the weight of Edge 1 - 3 : 10

Enter the weight of Edge 2 - 0 : 6

Enter the weight of Edge 2 - 1 : 13

Enter the weight of Edge 2 - 2 : 0

Enter the weight of Edge 2 - 3 : 12

Enter the weight of Edge 3 - 0 : 8

Enter the weight of Edge 3 - 1 : 8

Enter the weight of Edge 3 - 2 : 9

Enter the weight of Edge 3 - 3 : 0

The distance matrix is : 
0   10  15  20  
5   0   9   10  
6   13  0   12  
8   8   9   0   

Travelling Salesman Distance is : 35

The travelled path is : 1  -> 2 -> 4 -> 3 -> 1
*/