/* Batch : L 10
Roll No : 33231
Problem Statement : Write a program to find Maximum and Minimum element in an array using Divide and Conquer strategy
and verify the time complexity. */

#include<bits/stdc++.h>
using namespace std;

tuple<int, int> findMinMax(vector<int>v, int beg, int end) {
	tuple<int, int> leftMinMax, rightMinMax, MinMax;  
	MinMax = make_tuple(0, 0);   
    int mid;
    cout << "\n\nBEG = " << beg << "\tEND = " << end ;
     
    // If there is only one element 
    if (beg == end) {
        cout << "\tMIN = " << v[beg] << "\tMAX = " << v[beg] ;
    	return make_tuple(v[beg], v[beg]);
    }
     
    // If there are two elements 
    if (end == beg + 1) {
        (v[0] > v[1]) ? cout << "\tMIN = " << v[end] << "\tMAX = " << v[beg] : cout << "\tMIN = " << v[beg] << "\tMAX = " << v[end];
    	return (v[beg] > v[end]) ? make_tuple(v[beg], v[end]) : make_tuple(v[end], v[beg]);
    }
     
    // If there are more than 2 elements 
    mid = (beg + end) / 2; 
    leftMinMax = findMinMax(v, beg, mid);
    rightMinMax = findMinMax(v, mid + 1, end); 
     
    // Compare minimums of two parts
    (get<1>(leftMinMax) < get<1>(rightMinMax)) ? get<1>(MinMax) = get<1>(leftMinMax) : get<1>(MinMax) = get<1>(rightMinMax);   
     
    // Compare maximums of two parts
    (get<0>(leftMinMax) > get<0>(rightMinMax)) ? get<0>(MinMax) = get<0>(leftMinMax) : get<0>(MinMax) = get<0>(rightMinMax);
    cout << "\n\nBEG = " << beg << "\tEND = " << end ;
    cout << "\tMIN = " << get<1>(MinMax) << "\tMAX = " << get<0>(MinMax);
    return MinMax;
}

int main() {
	tuple<int, int>MinMax;
	vector<int>arr;
	int n, x;
	cout << "\nEnter the number of elements : ";
	cin >> n;
	while(n--) {
		cin >> x;
		arr.push_back(x);
	}

	MinMax = findMinMax(arr, 0, arr.size()-1);
    cout << "\n------------------------------------------------\n" ;
	cout << "The maximum element is = " << get<0>(MinMax) << endl;
	cout << "The minimum element is = " << get<1>(MinMax) << endl;
	return 0;
}

/*
Output:
    Enter the number of elements : 5
    7 65 23 1 45


    BEG = 0 END = 4

    BEG = 0 END = 2

    BEG = 0 END = 1 MIN = 7 MAX = 65

    BEG = 2 END = 2 MIN = 23    MAX = 23

    BEG = 0 END = 2 MIN = 7 MAX = 65

    BEG = 3 END = 4 MIN = 1 MAX = 45

    BEG = 0 END = 4 MIN = 1 MAX = 65
    ------------------------------------------------
    The maximum element is = 65
    The minimum element is = 1*/
