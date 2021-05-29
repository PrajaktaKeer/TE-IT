/*Roll No : 33231
Batch : L10
Problem Statement : Write a program to solve optimal storage on tapes problem using Greedy approach.*/

#include<bits/stdc++.h>
using namespace std;

#define sizeOfTape 100

//function for merge sort
void merge(vector<int>&v, int beg, int end, int mid) {
	int i = beg, j = mid + 1, res[100], k = 0;

	while(i <= mid && j <= end) {
		if(v[i] < v[j]) 
			res[k++] = v[i++];

		else 
			res[k++] = v[j++];
	}
	while(i <= mid) 
		res[k++] = v[i++];

	while(j <= end) 
		res[k++] = v[j++];

	for(i = beg, j = 0; i <= end; i++, j++)
		v[i] = res[j];
}

void mergeSort(vector<int>&v, int beg, int end) {
	int mid;
	if(beg < end) {
		mid = (beg + end) / 2;
		mergeSort(v, beg, mid);
		mergeSort(v, mid+1, end);
		merge(v, beg, end, mid);
	}
}

//function to find MRT for each tape
float findMRT(vector<vector<int>>tapes, int j) {
	if(tapes[j].size() == 1)
		return tapes[j][0];
	int MRT = 0;
	for(int i = 0; i < tapes[j].size(); i++) 
		MRT += tapes[j][i] * (tapes[i].size() - i);
	return MRT / tapes[j].size();
}

void fillTapes(vector<int>&programs, int noOfTapes) {
	//sorting the programs vector 
	mergeSort(programs, 0, programs.size() - 1);
	int i, j;
	float totalMRT = 0, MRT;

	//printing the sorted array
	cout << "\nSorted Array : ";
	for(i = 0; i < programs.size(); i++) {
		if(i == programs.size() - 1)
				cout << programs[i];
		else
			cout << programs[i] << " , ";
	}

	//inserting the programs into the tapes
	vector<vector<int>>tapes(noOfTapes);
	for(i = 0, j = 0; i < programs.size(); i++, j = (j+1)%noOfTapes) {
		if(sizeOfTape - accumulate(tapes[j].begin(), tapes[j].end(), 0) >= programs[i]) 
			tapes[j].push_back(programs[i]);
		else
			break;
	}

	//printing the programs that cannot be stored onto the tapes due to lack of available space
	if(i < programs.size()) {
		cout << "\n\nThese programs cannot be stored : ";
		for(j = i; j < programs.size(); j++)
			cout << programs[j] << " ";
	}

	//printing the contents of each tape
	for(i = 0; i < noOfTapes; i++) {
		cout << "\n\nTape " << i + 1 << " : [";
		for(j = 0; j < tapes[i].size(); j++) {
			if(j == tapes[i].size() - 1)
				cout << tapes[i][j];
			else
				cout << tapes[i][j] << " , ";
		}
		cout << "]";

		(tapes[i].size() != 0) ? MRT = findMRT(tapes, i) : MRT = 0;
		totalMRT += MRT;
		//printing the MRT value of each tape
		cout << "\t\t**MRT " << i + 1 << " = " << MRT;
	}

	//printing the average MRT
	cout << "\n\nAverage MRT = " << (float)(totalMRT / noOfTapes) << endl;
}

int main() {
	int noOfPrograms, noOfTapes, x;
	vector<int>programs;

	//accepting the noOfPrograms, ProgramArray and noOfTapes
	do {
		cout << "\nEnter the number of programs : ";
		cin >> noOfPrograms;
		if(noOfPrograms <= 0)
			cout << "\nPlease enter a nonzero positive integer.\n";
	}while(noOfPrograms <= 0);

	cout << "\nEnter the sizes for " << noOfPrograms << " programs : ";
	for(int i = 0; i < noOfPrograms; i++) {
		do {
			cin >> x;
			if(x <= 0)
				cout << "\nPlease enter a nonzero positive integer.\n";
		}while(x <= 0); 
		programs.push_back(x);
	}

	do {
		cout << "\nEnter the number of available tapes : ";
		cin >> noOfTapes;
		if(noOfTapes <= 0)
			cout << "\nPlease enter a nonzero positive integer.\n";
	}while(noOfTapes <= 0);
	
	fillTapes(programs, noOfTapes);

	return 0;
}

/*OUTPUT :

Enter the number of programs : 10

Enter the sizes for 10 programs : 50 10 40 80 90 70 20 30 60 100

Enter the number of available tapes : 5

Sorted Array : 10 , 20 , 30 , 40 , 50 , 60 , 70 , 80 , 90 , 100

These programs cannot be stored : 80 90 100 

Tape 1 : [10 , 60]		**MRT 1 = 40

Tape 2 : [20 , 70]		**MRT 2 = 55

Tape 3 : [30]		    **MRT 3 = 30

Tape 4 : [40]		    **MRT 4 = 40

Tape 5 : [50]		    **MRT 5 = 50

Average MRT = 43
*/

