/*Roll No : 33231
Batch : L10
Title : Lexical Analyzer */

#include<bits/stdc++.h>
using namespace std;

vector<string>terminals, keywords;

struct UST {
	string lexeme, type, token;
	int index;
};
vector<UST>ust;

typedef struct KWT {
	string name;
	int index;
	string token;
}KWT;
vector<KWT>KT = {{"break",1,"K1"} , {"case",2,"K2"} , {"char",3,"K3"} , {"const",4,"k4"} , {"continue",5,"K5"} , 
	{"default",6,"K6"} , {"do",7,"K7"}, {"double",8,"k8"} ,{"else",9,"k9"}, {"float",10,"k10"}, {"for",11,"k11"}, 
	{"if",12,"k12"} , {"int",13,"k13"} , {"long",14,"k14"}, {"return",15,"k15"} , {"static",16,"k16"}, 
	{"struct",17,"k17"}, {"switch",18,"k18"}, {"typedef",19,"k19"} , {"void",20,"k20"}, {"while",21,"k21"}
};

typedef struct LT {
	string literal, token, attr;
	int index;
}LT;
vector<LT>lt;

typedef struct ST {
	string symbol, token;
	int index;
}ST;
vector<ST>st;

vector<char>ter = {',',';','+','-','*','/','(',')','{','}','=','&'};

void handle_symbol(string w) {
	// symbol adding to symbol table and ust table
	for(int i = 0; i < st.size(); i++) {
		if(w == st[i].symbol) {// is symbol is already present in the symbol table
			ust.push_back({w, "SYM", st[i].token, st[i].index});
			return;
		}
	}
    // copy word to symbol table
	st.push_back({w, "ID" + to_string(st.size()+1), st.size()+1});
	
	// copy symbol to ust table
	ust.push_back({w, "SYM", st[st.size()-1].token, st[st.size()-1].index});	
	return;			
}

void handle_kw(string w) {
	//cout << w << endl;
	for(int i = 0; i < KT.size(); i++) {
		if(w == KT[i].name) {// if it is a keyword
			if(find(keywords.begin(), keywords.end(), w) == keywords.end())
				keywords.push_back(w);
			ust.push_back({w, "KEY", KT[i].token, i+1});
			return;
		}
    }// if it is not a keyword it can be symbol
    handle_symbol(w);// handle symbol
}

int isterminal(char a) { // function to chek given charachter is terminal or not
	string key;
	key += a;
	for(int i = 0; i < 12; i++) {
		if(ter[i] == a) {
			if(find(terminals.begin(), terminals.end(), key) == terminals.end())
				terminals.push_back(key);
			return i+1; // if it is an terminal
		}
	}
	return 0;// not an terminal
}

void handle_terminal(int a, char c) {// function to add terminal to the ust table
	string s;
	s += c;
	ust.push_back({s, "TER", s, a});
}

void handle_lit(string L, string attr) {
	lt.push_back({L, "LT" + to_string(lt.size()+1), attr, lt.size()+1});
	// copying keyword and its index and token to the ust table
	ust.push_back({L, "LIT", lt[lt.size()-1].token, lt[lt.size()-1].index});
}

void output() {
	// function to print ust table
	fstream fp;
	fp.open("ust.txt", ios::out);

	cout << "\n\t*****TERMINALS*****\n";
	for(int i = 0; i < terminals.size(); i++)
		cout << i+1 << "\t" << terminals[i] << endl;

	cout << "\n\t*****KEYWORDS*****\n";
	for(int i = 0; i < keywords.size(); i++)
		cout << i+1 << "\t" << keywords[i] << endl;

	cout << "\n\t*****UST table*****\n\nLexeme\tTYPE\tINDEX\tTOKEN\n";

	if(fp) {
		fp << "Lexeme\tTYPE\tINDEX\tTOKEN\n";
		for(int i = 0; i < ust.size(); i++) {
			cout << setw(6) << ust[i].lexeme << "\t" << setw(3) << ust[i].type << "\t" << setw(5) << 
				ust[i].index << "\t" << ust[i].token << endl;
			fp << setw(6) << ust[i].lexeme << "\t" << setw(3) << ust[i].type << "\t" << setw(5) << 
				ust[i].index << "\t" << ust[i].token << endl;
		}
		fp.close();// closing ust table file
	}
	
	fp.open("idt_table.txt", ios::out);// opening symbol table file
	// print symbol table
	cout << "\n\n\t*****IDENTIFIER table*****\n\nIndex\tIDENTIFIER\tTOKEN\n";
	if(fp) {
		fp << "Index\tIDENTIFIER\tTOKEN\n";
		for(int i = 0; i < st.size(); i++) {
			cout << setw(-5) << st[i].index << "\t" << setw(10) << st[i].symbol << "\t" << st[i].token << endl;
			fp << setw(-5) << st[i].index << "\t" << setw(10) << st[i].symbol << "\t" << st[i].token << endl;
		}
		fp.close();// closing symbol table file
	}
	
	fp.open("literal_table.txt", ios::out);// opening literal table file 
	cout << "\n\n\t*****LITERAl table*****\n\nIndex\t\t\tLiteral\t\tTOKEN\tAttribute\n";
	if(fp) {
		//	copying literal table to file
		fp << "Index\t\t\tLiteral\t\tTOKEN\tAttribute\n";
		for(int i = 0; i < lt.size(); i++) {
			cout << setw(-5) << lt[i].index << "\t" << setw(25) << lt[i].literal << "\t" << setw(5) << 
				lt[i].token << "\t" << lt[i].attr << endl;
			fp << setw(-5) << lt[i].index << "\t" << setw(25) << lt[i].literal << "\t" << setw(5) << 
				lt[i].token << "\t" << lt[i].attr << endl;
// writing ine by line entries of literal table to file
		}
		fp.close();// closing literal table file
	}
}

int main() {
	fstream fp;
	string str, num;
	fp.open("INPUT.c", ios::in);
	if(fp) {
		while(getline(fp, str)) {
			if(str[0] == '#') continue; //preprocessor
			for(int i = 0, j = 0; i < str.length(); ) {
				if(isalpha(str[i])) {// if as keyword or identifier always begin with aplhabet
					num = "";
				  	while(isalnum(str[i])) // until we continously get alphabets or digits
				  	    num += str[i++]; // copy string upto space or terminal
					handle_kw(num);	// handle keyword
					continue;
				}
				else {
					j = isterminal(str[i]);
					if(j != 0) {
						if(j == 6 && str[i+1] == '/') { //to ignore comments
				   	    	i = str.length();
						    break;
						}
						handle_terminal(j, str[i]);
					   	i++;
					   	continue;	
					}
				    else {
				    	if(str[i] == '"') { // literal handling
					    	num = "";
					    	i++;
					    	while(str[i] != '"') {
					    		num += str[i++];
					    		if(i == str.length()) {
					    			printf("\nError in literals");
					    			return 0;
								}
							}
							handle_lit(num, "String constant");
						    i++;
							continue;
						}
					}
				}
				if(isdigit(str[i])) {
					num = "";
				  	while(isalnum(str[i])) // until we continously get alphabets or digits
				  	    num += str[i++]; // copy string upto space or terminal
					handle_lit(num, "Numeric Constant");	// handle keyword
					continue;
				}
				//if(str[i] != '0') {
					if(isdigit(str[i]) || str[i]=='#' || str[i]=='$' || str[i]=='@') {
						// error when we have incorrect identifier
						cout << "Error in code incorrect identifier " << str[i];
						return 0;
					}
				//}
				i++;
			} 
		}
		output();//to print and write output to the file
    }
    else {
		cout<<"Error in opening the file";
		exit(1);
	} 
}

/*OUTPUT:

	*****TERMINALS*****
1	/
2	(
3	)
4	{
5	,
6	;
7	&
8	=
9	}

	*****KEYWORDS*****
1	int
2	float
3	do
4	if
5	while
6	return

	*****UST table*****

Lexeme	TYPE  INDEX	TOKEN
   int	KEY	   13	k13
  main	SYM	    1	ID1
     (	TER	    7	(
     )	TER	    8	)
     {	TER	    9	{
   int	KEY	   13	k13
   num	SYM	    2	ID2
     ,	TER	    1	,
   den	SYM	    3	ID3
     ;	TER	    2	;
 float	KEY	   10	k10
result	SYM	    4	ID4
     ;	TER	    2	;
    do	KEY	    7	K7
     {	TER	    9	{
printf	SYM	    5	ID5
     (	TER	    7	(
Enter numerator : 	LIT	    1	LT1
     )	TER	    8	)
     ;	TER	    2	;
 scanf	SYM	    6	ID6
     (	TER	    7	(
    %d	LIT	    2	LT2
     ,	TER	    1	,
     &	TER	   12	&
   num	SYM	    2	ID2
     )	TER	    8	)
     ;	TER	    2	;
printf	SYM	    5	ID5
     (	TER	    7	(
Enter Denominator : 	LIT	    3	LT3
     )	TER	    8	)
     ;	TER	    2	;
 scanf	SYM	    6	ID6
     (	TER	    7	(
    %d	LIT	    4	LT4
     ,	TER	    1	,
     &	TER	   12	&
   den	SYM	    3	ID3
     )	TER	    8	)
     ;	TER	    2	;
    if	KEY	   12	k12
     (	TER	    7	(
   den	SYM	    3	ID3
     =	TER	   11	=
     0	LIT	    5	LT5
     )	TER	    8	)
     {	TER	    9	{
result	SYM	    4	ID4
     =	TER	   11	=
   num	SYM	    2	ID2
     /	TER	    6	/
   den	SYM	    3	ID3
     ;	TER	    2	;
printf	SYM	    5	ID5
     (	TER	    7	(
result = %f\n	LIT	    6	LT6
     ,	TER	    1	,
result	SYM	    4	ID4
     )	TER	    8	)
     ;	TER	    2	;
     }	TER	   10	}
     }	TER	   10	}
 while	KEY	   21	k21
     (	TER	    7	(
   den	SYM	    3	ID3
     =	TER	   11	=
     0	LIT	    7	LT7
     )	TER	    8	)
     ;	TER	    2	;
printf	SYM	    5	ID5
     (	TER	    7	(
Exception divide by zero	LIT	    8	LT8
     )	TER	    8	)
     ;	TER	    2	;
return	KEY	   15	k15
     0	LIT	    9	LT9
     ;	TER	    2	;
     }	TER	   10	}


	*****IDENTIFIER table*****

Index	IDENTIFIER	TOKEN
1	      main		ID1
2	       num		ID2
3	       den		ID3
4	    result		ID4
5	    printf		ID5
6	     scanf		ID6


	*****LITERAl table*****

Index			Literal			TOKEN	Attribute
1	       Enter numerator : 	  LT1	String constant
2	                       %d	  LT2	String constant
3	     Enter Denominator : 	  LT3	String constant
4	                       %d	  LT4	String constant
5	                        0	  LT5	Numeric Constant
6	            result = %f\n	  LT6	String constant
7	                        0	  LT7	Numeric Constant
8	 Exception divide by zero	  LT8	String constant
9	                        0	  LT9	Numeric Constant
*/