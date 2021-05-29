#include<bits/stdc++.h>
using namespace std;

#define OPCODE(it) make_tuple(it->second.type, stoi(it->second.opcode))
#define NULL_TUPLE make_tuple("-", -1)

string registers[] = {"AREG", "BREG", "CREG", "DREG"};
string branchCodes[] = {"LT", "LE", "GT", "GE", "NE", "EQ", "ANY"};

struct MOT {
	string type, opcode, size, operand;
};

struct symtab {
	int LC, value, size;
	string symbol;
};
vector<symtab>sym;

struct littab {
	int LC;
	string literal;
};
vector<littab>ltt;

unordered_map<string, MOT> hashTable;

struct intermediateCode {
	int LC;
	tuple <string, int> opcode, op1_opcode,  op2_opcode;
};
vector<intermediateCode>imc;

struct TargetCode {
	int LC, opcode, op1_opcode,  op2_opcode;
};
vector<TargetCode>tc;

int LC = 0;
bool flag = false;
vector<int>poolTable;

//store the MOT table using hashing technique
void hashing() {
    fstream fp;
	string lineOfFile, word;
	vector <string> tokens;

    //openeing the file mot_table.txt
	fp.open("mot_table1.txt", ios::in);

	if(fp) {
		while(getline(fp, lineOfFile)) {
			tokens.clear();
			stringstream line(lineOfFile);
			while(getline(line, word, ' ')) 
        		tokens.push_back(word);
        	hashTable[tokens[0]] = {tokens[3], tokens[1], tokens[2], tokens[4]}; 
		}
	}
	else {
		cout<<"Error in opening the file";
		exit(1);
	}
}

//to display MOT table
void displayHashTable() {
	for (auto x : hashTable) 
      cout << x.first << " " << x.second.opcode << " " << x.second.type
      << " " << x.second.operand << " " << x.second.size << endl; 
}

void initSymbolTable(string s, int value, int size, string type, int lineNo) {
	for(int i = 0; i < sym.size(); i++) {
		if(sym[i].symbol == s) {
			if(sym[i].LC == -1) {
				sym[i].LC = LC, sym[i].size = size, sym[i].value = value;
				return;
			}
			else {
				cout << "Redeclaration of "<< s << " at line " << lineNo << endl;
				exit(1);
			}
		}
	}
	cout << s << " declared at line " << lineNo << " but not used " << endl;
	exit(1);
}

int addToSymbolTable(string s, int value, int size, string type) {
	//index, lc, value, size, symbol
	for(int i = 0; i < sym.size(); i++) {
		if(sym[i].symbol == s) {
			if(type == "LABEL" && sym[i].LC == -1)
				sym[i].LC = LC;
			return i+1;
		}
	}
	if(type == "SYMBOL")
		sym.push_back({-1, -1, 1, s});
	else
		sym.push_back({LC, -1, 1, s});
	return sym.size();
}

int addToLiteralTable(string l) {
	ltt.push_back({-1, l}); //LC, literal
	return ltt.size();
}

tuple <string, int> searchOp1(string key) {
	for(int i = 0 ; i < 4; i++) {
		if(registers[i] == key)
			return make_tuple("R", i+1);
	}
	for(int i = 0 ; i < 7; i++) {
		if(branchCodes[i] == key)
			return make_tuple("CC", i+1);
	}
	return make_tuple("", -1);
}

void handleEQU(string label1, string label2, int lineNo) {
	bool check = false;
	int x, y, c = 0;
	for(int i = 0; i < label2.length(); i++) {
		if(label2[i] == '+') {
			c = stoi(label2.substr(i+1, label2.length()));
			label2 = label2.substr(0, i-1);
			break;
		}
	}
	for(int i = 0; i < sym.size(); i++) {
		if(sym[i].symbol == label2) 
			x = i;
		if(sym[i].symbol == label1)
			y = i;	
	}
	sym[y].LC = sym[x].LC + c;		
}

tuple <string, int> handleOrigin(string label) {
	if(all_of(label.begin(), label.end(), ::isdigit)) {
		LC = stoi(label);
		return make_tuple("C", stoi(label));
	}
	int c = 0, i;
	for(i = 0; i < label.length(); i++) {
		if(label[i] == '+') {
			c = stoi(label.substr(i+1, label.length()));
			label = label.substr(0, i);
			break;
		}
	}
	for(i = 0; i < sym.size(); i++) {
		if(sym[i].symbol == label) 
			break;		
	}
	LC = sym[i].LC + c;	
	return make_tuple("S", addToSymbolTable(label, 0, 0, "SYMBOL"));
}

void handleLiterals() {
	for(int i = 0; i < ltt.size(); i++) {
		if(ltt[i].LC == -1) 
			ltt[i].LC = LC ++;
	}
}

void displayTables() {
	cout << "\n----------------- INTERMEDIATE CODE ------------------\n" ;
	cout << "LC\tOPCODE\t\tOPERAND 1\tOPERAND 2" << endl;
	for(int i = 0; i < imc.size(); i++) {
		if(imc[i].LC == -1) cout<< "-" << "\t";
		else cout << imc[i].LC << "\t";

		cout << "(" << get<0>(imc[i].opcode) << " , " << get<1>(imc[i].opcode) << ")" << "\t";

		if(get<1>(imc[i].op1_opcode) == -1) cout << "-\t\t";
		else if(get<0>(imc[i].op1_opcode) == "R") cout << "( " << get<1>(imc[i].op1_opcode) << " )\t\t";
		else cout << "(" << get<0>(imc[i].op1_opcode) << ", " << get<1>(imc[i].op1_opcode) << ")\t\t";

		if(get<1>(imc[i].op2_opcode) == -1) cout << "-" << endl;
		else cout << "(" << get<0>(imc[i].op2_opcode) << " , " << get<1>(imc[i].op2_opcode) << ")" << endl;
	}

	cout << "\n----------------- SYMBOL TABLE ------------------\n" ;
	cout << "LC\tSYMBOL\tVALUE\tSIZE" << endl;
	for(int i = 0; i < sym.size(); i++) 
		cout << sym[i].LC << "\t" << sym[i].symbol << "\t" <<sym[i].value << "\t" << sym[i].size << endl;

	cout << "\n----------------- LITERAL TABLE ------------------\n" ;
	cout << "LC\tLITERAL" <<endl;
	for(int i = 0; i < ltt.size(); i++) 
		cout << ltt[i].LC << "\t" << ltt[i].literal << endl;

	cout << "\n----------------- POOL TABLE ------------------\n" ;
	cout << "LITERAL NUMBER" <<endl;
	for(int i = 0; i < poolTable.size(); i++)
		cout << "#" << poolTable[i] << endl;

	cout << "\n----------------- TARGET CODE ------------------\n" ;
	cout << "LC\tOPCODE\t\tOPERAND 1\tOPERAND 2" << endl;
	for(int i = 0; i < tc.size(); i++)
		cout << tc[i].LC << "\t" << tc[i].opcode << "\t\t" << tc[i].op1_opcode << "\t\t" << tc[i].op2_opcode << endl;
}

//function to generate intermediate code
void generateIntermediateCode(vector<string>tokens, int lineNo) {
	//intermediateCode temp;

	//every program must begin with START
	if(lineNo == 1) {
		auto it = hashTable.find(tokens[0]);
	    if(it != hashTable.end() && tokens[0] == "START") {
	      	if(tokens.size() > 1) {
		       	imc.push_back({-1, OPCODE(it), NULL_TUPLE, make_tuple("C", stoi(tokens[1]))});
		        LC = stoi(tokens[1]);
	      	}
	      	else
	      		imc.push_back({-1, OPCODE(it), NULL_TUPLE, NULL_TUPLE});
	    }
	    else {
	        cout<<"START missing.."<<endl;
	        exit(1);
	    }
	    return;
	}
	if(tokens[0] == "START") {
		cout << "Redeclaration of START at line " << lineNo << endl;
		exit(1);
	}

	switch(tokens.size()) {
		case 1: //END, LTORG, STOP
		{	
			auto it = hashTable.find(tokens[0]);
			if(it != hashTable.end()) {
				imc.push_back({LC, OPCODE(it), NULL_TUPLE, NULL_TUPLE});
				if(tokens[0] == "LTORG") {
					handleLiterals();
					return;
				}
				else if(tokens[0] == "END") {
					flag = true;
					handleLiterals();
				}
				LC += stoi(it->second.size);
			}
			else{
				cout<<"Invalid Instruction at line " << lineNo <<endl;
				exit(1);
			}
		}
			break;

		case 2: //ORIGIN, READ, PRINT
		{	
			auto it = hashTable.find(tokens[0]);
			if(it != hashTable.end()) {
				if(tokens[0] == "ORIGIN") {
					imc.push_back({LC, OPCODE(it), NULL_TUPLE, handleOrigin(tokens[1])});
					return;
				}
				else if(all_of(tokens[1].begin(), tokens[1].end(), ::isdigit))
					imc.push_back({LC, OPCODE(it), NULL_TUPLE, make_tuple("C", stoi(tokens[1]))});
				else if(tokens[1].find('=') != string::npos) 
					imc.push_back({LC, OPCODE(it), NULL_TUPLE, make_tuple("L", addToLiteralTable(tokens[1]))});
				else 
					imc.push_back({LC, OPCODE(it), NULL_TUPLE, make_tuple("S", addToSymbolTable(tokens[1], 0, 0, "SYMBOL"))});
				
				LC += stoi(it->second.size);
			}
			else{
				cout<<"Invalid Instruction at line " << lineNo <<endl;
				exit(1);
			}
		}
			break;

		case 3:
		{	
			auto it = hashTable.find(tokens[0]);
			auto it1 = hashTable.find(tokens[1]);
			if(it != hashTable.end()) { 
				//ADD, SUB, MULT, DIV, BC, MOVEM, MOVER
				if(get<1>(searchOp1(tokens[1])) == -1) {
					cout << "Invalid register or branch code usage at line " << lineNo << endl;
					exit(1);
				}
				else if(all_of(tokens[2].begin(), tokens[2].end(), ::isdigit))
					imc.push_back({LC, OPCODE(it), searchOp1(tokens[1]), make_tuple("C", stoi(tokens[2]))});
				else if(tokens[2].find('=') != string::npos) 
					imc.push_back({LC, OPCODE(it), searchOp1(tokens[1]), make_tuple("L", addToLiteralTable(tokens[2]))});
				else 
					imc.push_back({LC, OPCODE(it), searchOp1(tokens[1]), make_tuple("S", addToSymbolTable(tokens[2], 0, 0, "SYMBOL"))});
				LC += stoi(it->second.size);
			}
			else if(it1 != hashTable.end()) { 
				//DS, DC, EQU
				if(tokens[1] == "EQU") {
						handleEQU(tokens[0], tokens[2], lineNo);
						imc.push_back({LC, OPCODE(it1), NULL_TUPLE, make_tuple("S", addToSymbolTable(tokens[2], 0, 0, "LABEL"))});
						LC += stoi(it1->second.size);
						return;
				}
				tokens[2].erase(remove(tokens[2].begin(), tokens[2].end(), '\''), tokens[2].end());
				imc.push_back({LC, OPCODE(it1), NULL_TUPLE, make_tuple("C", stoi(tokens[2]))});
				if(tokens[1] == "DC") {
    				initSymbolTable(tokens[0], stoi(tokens[2]), 1, "SYMBOL", lineNo);
    				LC += stoi(it1->second.size);
    			}
    			else {
    				initSymbolTable(tokens[0], stoi(tokens[2]), stoi(tokens[2]), "SYMBOL", lineNo);
    				LC += stoi(tokens[2]);
    			}
			}
			else{
				cout<<"Invalid Instruction at line " << lineNo <<endl;
				exit(1);
			}
		}
			break;
		case 4:
		{	
			addToSymbolTable(tokens[0], 0, 0, "LABEL");
			auto it = hashTable.find(tokens[1]);
			if(it != hashTable.end()) {
				if(get<1>(searchOp1(tokens[2])) == -1) {
					cout << "Invalid register or branch code usage at line " << lineNo << endl;
					exit(1);
				}
				else if(all_of(tokens[3].begin(), tokens[3].end(), ::isdigit))
					imc.push_back({LC, OPCODE(it), searchOp1(tokens[2]), make_tuple("C", stoi(tokens[3]))});
				else if(tokens[3].find('=') != string::npos) 
					imc.push_back({LC, OPCODE(it), searchOp1(tokens[2]), make_tuple("L", addToLiteralTable(tokens[3]))});
				else 
					imc.push_back({LC, OPCODE(it), searchOp1(tokens[2]), make_tuple("S", addToSymbolTable(tokens[3], 0, 0, "SYMBOL"))});
				LC += stoi(it->second.size);
			}
			else{
				cout<<"Invalid Instruction at line " << lineNo <<endl;
				exit(1);
			}
		}
			break;
		default:
			cout<<"Invalid Instruction at line " << lineNo <<endl;
    		exit(1);
    }
}

void checkSymbolTable() {
	for(int i = 0; i < sym.size(); i++) {
		if(sym[i].LC == -1) {
			cout << sym[i].symbol << " not declared" <<endl;
			exit(1);
		}
	}
}

void generatePoolTable() {
	poolTable.push_back(1);
	for(int i = 0; i < ltt.size() - 1; i++) {
		if(abs(ltt[i].LC - ltt[i+1].LC) != 1) 
			poolTable.push_back(i+2);
	}
}

void generateTargetCode() {
	TargetCode temp;
	int pt = 1, y;
	vector<bool>visited(ltt.size(), false);
	for(int i = 0; i < imc.size(); i++) {
		if(get<0>(imc[i].opcode) == "DL" || (get<0>(imc[i].opcode) == "AD" && get<1>(imc[i].opcode) == 1)
			|| (get<0>(imc[i].opcode) == "AD" && get<1>(imc[i].opcode) == 4) ||
			(get<0>(imc[i].opcode) == "AD" && get<1>(imc[i].opcode) == 5) ||
			(get<0>(imc[i].opcode) == "AD" && get<1>(imc[i].opcode) == 2))
			continue;

		temp.LC = imc[i].LC;
		if(get<0>(imc[i].opcode) == "AD" && get<1>(imc[i].opcode) == 3) {
			int lc = imc[i].LC;
			if(pt == poolTable.size()) y = ltt.size();
			else y = poolTable[pt] - 1;
			for(int j = poolTable[pt-1] - 1; j < y; j++, lc++) {
				string x = ltt[j].literal;
				x.erase(remove(x.begin(), x.end(), '\''), x.end());
				x.erase(remove(x.begin(), x.end(), '='), x.end());
				visited[j] = true;
				tc.push_back({lc, 0, 0, stoi(x)});
			}
			pt++;
			continue;
		}

		if(get<0>(imc[i].opcode) == "IS") temp.opcode = get<1>(imc[i].opcode);
		else temp.opcode = 0;

		if(get<1>(imc[i].op1_opcode) == -1) temp.op1_opcode = 0;
		else temp.op1_opcode = get<1>(imc[i].op1_opcode);

		if(get<1>(imc[i].op2_opcode) == -1) temp.op2_opcode = 0;
		else if(get<0>(imc[i].op2_opcode) == "C") temp.op2_opcode = get<1>(imc[i].op2_opcode);
		else if(get<0>(imc[i].op2_opcode) == "S") temp.op2_opcode = sym[get<1>(imc[i].op2_opcode) - 1].LC;
		else if(get<0>(imc[i].op2_opcode) == "L") temp.op2_opcode = ltt[get<1>(imc[i].op2_opcode) - 1].LC;

		tc.push_back(temp);
	}
	int lc = imc[imc.size()-1].LC;
	for(int i = 0; i < ltt.size(); i++) {	
		if(visited[i] == false) {
			string x = ltt[i].literal;
			x.erase(remove(x.begin(), x.end(), '\''), x.end());
			x.erase(remove(x.begin(), x.end(), '='), x.end());
			tc.push_back({lc++, 0, 0, stoi(x)});
		}
	}
}

int main() {
	//store the MOT table in hashTable	
	hashing();

    fstream fp;
	string lineOfFile, word;
	vector <string> tokens;
	int lineNo = 1;

	//reading the input file which contains source code
	fp.open("input_file.txt", ios::in);

	if(fp) {
		while(getline(fp, lineOfFile) && flag == false) {
			tokens.clear();
			//ignore any blank lines in source code
			if(lineOfFile.size() == 0)
				continue;

			stringstream line(lineOfFile);
			while(getline(line, word, ' ')) 
        		tokens.push_back(word);
        	
        	generateIntermediateCode(tokens, lineNo);
        	lineNo++;
		}

		//check if any LC value is not initialized. If such an entry is found then variable is not declared
		checkSymbolTable();
		generatePoolTable();
		generateTargetCode();
		//display the IC table, symbol table, literal table, pool table, TC table
		displayTables();
	}
	else {
		cout<<"Error in opening the file";
		exit(1);
	}

	return 0;
}
