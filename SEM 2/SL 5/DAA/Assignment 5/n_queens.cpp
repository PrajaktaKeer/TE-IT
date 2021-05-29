/* Roll No - 33231
Batch - L10
Problem Statement : Write a recursive program to find the solution of placing n queens on chessboard 
so that no two queens attack each other using Backtracking.*/

#include<bits/stdc++.h>
using namespace std;

//this function prints all the available solution
void display(vector<vector<int>>positions) 
{ 
  static int count = 1;
  cout<<"\nSOLUTION "<<count++<<endl;
    for (int i = 0; i < positions.size(); i++) { 
        for (int j = 0; j < positions.size(); j++) 
            printf(" %d ", positions[i][j]); 
        printf("\n"); 
    } 
} 
  
//this function checks whether the queen is safely placed or not
bool isSafe(vector<vector<int>>positions, int row, int col) 
{ 
    int i, j; 
  
    //checks all rows on left side
    for (i = 0; i < col; i++) 
        if (positions[row][i]) 
            return false; 
  
    //checks upper diagonal on left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) 
        if (positions[i][j]) 
            return false; 
  
    //checks lower diagonal on left side
    for (i = row, j = col; j >= 0 && i < positions.size(); i++, j--) 
        if (positions[i][j]) 
            return false; 
  
    return true; 
} 
  
//recursive function for placing N queens
bool place(vector<vector<int>>&positions, int col) 
{ 
    //base condition, if all queens are placed then return true
    if (col == positions.size()) { 
        display(positions);
        return true; 
    }

    bool flag = false;
  
    //iterate over all the columns
    for (int i = 0; i < positions.size(); i++) { 
        
        if (isSafe(positions, i, col)) { 
            positions[i][col] = 1; 
	    flag = place(positions, col + 1) || flag;  
	    positions[i][col] = 0; // BACKTRACK
        } 
    } 
    //if queen cannot be placed in any row then return false
    return flag; 
} 

void SolveNQ(int queens) {
	vector<vector<int>>positions(queens, vector<int>(queens, 0));

	if (place(positions, 0) == false) 
	    cout << "Solution does not exist"; 

}

int main() {
	int queens;
	cout<<"How many queens do you want to place? ";
	cin>>queens;

	if(queens > 3) 
	    SolveNQ(queens);
	else
	    cout<<"\nSolution does not exist\n";
	return 0;
}

/*OUTPUT :
jing@jing-Latitude-E5440:~/prajakta/TE IT/SEM 2/SL 5/DAA$ ./a.out
How many queens do you want to place? 4

SOLUTION 1
 0  0  1  0 
 1  0  0  0 
 0  0  0  1 
 0  1  0  0 

SOLUTION 2
 0  1  0  0 
 0  0  0  1 
 1  0  0  0 
 0  0  1  0 
jing@jing-Latitude-E5440:~/prajakta/TE IT/SEM 2/SL 5/DAA$ ./a.out
How many queens do you want to place? 5

SOLUTION 1
 1  0  0  0  0 
 0  0  0  1  0 
 0  1  0  0  0 
 0  0  0  0  1 
 0  0  1  0  0 

SOLUTION 2
 1  0  0  0  0 
 0  0  1  0  0 
 0  0  0  0  1 
 0  1  0  0  0 
 0  0  0  1  0 

SOLUTION 3
 0  0  1  0  0 
 1  0  0  0  0 
 0  0  0  1  0 
 0  1  0  0  0 
 0  0  0  0  1 

SOLUTION 4
 0  0  0  1  0 
 1  0  0  0  0 
 0  0  1  0  0 
 0  0  0  0  1 
 0  1  0  0  0 

SOLUTION 5
 0  1  0  0  0 
 0  0  0  1  0 
 1  0  0  0  0 
 0  0  1  0  0 
 0  0  0  0  1 

SOLUTION 6
 0  0  0  0  1 
 0  0  1  0  0 
 1  0  0  0  0 
 0  0  0  1  0 
 0  1  0  0  0 

SOLUTION 7
 0  1  0  0  0 
 0  0  0  0  1 
 0  0  1  0  0 
 1  0  0  0  0 
 0  0  0  1  0 

SOLUTION 8
 0  0  0  0  1 
 0  1  0  0  0 
 0  0  0  1  0 
 1  0  0  0  0 
 0  0  1  0  0 

SOLUTION 9
 0  0  0  1  0 
 0  1  0  0  0 
 0  0  0  0  1 
 0  0  1  0  0 
 1  0  0  0  0 

SOLUTION 10
 0  0  1  0  0 
 0  0  0  0  1 
 0  1  0  0  0 
 0  0  0  1  0 
 1  0  0  0  0 
 */
