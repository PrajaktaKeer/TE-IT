/*Roll No : 33231
Batch : L10
Problem Statement : Write a program to implement a Recursive Descent Parser  */

#include<bits/stdc++.h>
using namespace std;

/*GRAMMAR:
A -> aAa | bBb
B -> bBb | epsilon */

//added a '$' sign in middle of the input string to avoid infinite looping 

int c = 0;

void B(string str) {
	if(str[c] == '$') {
		c++;
		return;
	}
	if(str[c] == 'b') {
		c++;
		B(str);
		if(str[c] == 'b') c++;
		else {
			cout << str << " is syntatically incorrect\n";
			exit(1);
		}

	}
	else return;
}

void A(string str) {
	if(str[c] == '$') {
		cout << str << " is syntatically incorrect\n";
		exit(1);
	}
	if(str[c] == 'a') {
		c++;
		A(str);
		if(str[c] == 'a') c++;
		else {
			cout << str << " is syntatically incorrect\n";
			exit(1);
		}
	}
	else if(str[c] == 'b'){
		c++;
		B(str);
		if(str[c] == 'b') c++;
		else {
			cout << str << " is syntatically incorrect\n";
			exit(1);
		}
	}
	else {
			cout << str << " is syntatically incorrect\n";
			exit(1);
	}
}

int main() {
	string str;
	cout << "\nEnter input string : ";
	cin >> str;
	if (str.length() & 1){
        cout << "Given string is synactically not correct";
        exit(1);
    }
    str.insert(str.length() / 2, "$");
	A(str);
	cout << str << " is syntatically correct.\n";
	return 0;
}

/*OUTPUT :
jing@jing-Latitude-E5440:~/prajakta/TE IT/SEM 2/SL 5/SP$ ./a.out

Enter input string : aaabbaaa
aaab$baaa is syntatically correct.

jing@jing-Latitude-E5440:~/prajakta/TE IT/SEM 2/SL 5/SP$ ./a.out

Enter input string : baab
ba$ab is syntatically incorrect

jing@jing-Latitude-E5440:~/prajakta/TE IT/SEM 2/SL 5/SP$ ./a.out

Enter input string : abbba
Given string is synactically not correct */