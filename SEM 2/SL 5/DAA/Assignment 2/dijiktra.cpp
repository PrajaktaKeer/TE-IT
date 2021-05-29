#include<bits/stdc++.h>
using namespace std;

#define MAX 100
#define INF INT32_MAX

vector<vector<int>>adj_mat(MAX, vector<int>(MAX, INF));

void printPath(vector<int> parent, int j, map <int, string> vertexNames) 
{ 	//cout << j << " ";
      
    // Base Case : If j is source 
    if (parent[j] == - 1) {
    	cout << vertexNames[j] << "->";
        return; 
    }
  
    printPath(parent, parent[j], vertexNames); 
  
    cout << vertexNames[j] << "->" ; 
} 

void dijiktra(map <int, string> vertexNames, string source, string destination, int vertices) {
	int src = -1, dest = -1;
	map<int, string>::iterator itr;
	for (itr = vertexNames.begin(); itr != vertexNames.end(); ++itr) { 
		if(itr->second == source)
			src = itr->first;
		else if (itr->second == destination)
			dest = itr->first;
	}

	if(src == -1) {
		cout << "Source not found" ;
		return;
	}
	if(dest == -1) {
		cout << "Destination not found" ;
		return;
	}

	int min = INT32_MAX, sel_ver, xs;
	vector<int>dist(vertices), path(vertices);
	vector<bool>visited(vertices, false);
	vector<int>::iterator it;

	for(int i = 0; i < vertices; i++) {
		dist[i] = adj_mat[src][i];
		if(adj_mat[src][i] == 0)
			visited[i] = true;
	}
	path[src] = -1;
	for(int i = 0; i < vertices-1; i++) {
		min = INT32_MAX;
		for(int j = 0; j < vertices; j++) {
			if(dist[j] < min && dist[j] != 0 && !visited[j]) {
				min = dist[j];
				sel_ver = j;
			}
		}
		visited[sel_ver] = true;
		for(int j = 0; j < vertices; j++) {
			if(dist[j] != 0 && !visited[j] && adj_mat[sel_ver][j] != INF && 
				dist[sel_ver]+adj_mat[sel_ver][j] < dist[j]) {
				path[j] = sel_ver;
				dist[j] = std::min(dist[j], adj_mat[sel_ver][j] + min);
			}
		}
	}

	cout << "The distance from " << source << " to " << destination << " = " << dist[dest] << endl;
	cout << "Path to be followed = ";

	for(int i = 0; i < path.size(); i++) {
		if(path[i] == 0) 
			path[i] = src;
		//cout << path[i] <<" ";
		
	}
	printPath(path, dest, vertexNames);
	cout << "\n";
}

void create(int vertices, map <int, string> &vertexNames)
{
	int weight;
	string name;
	cout << "Enter the names of vertices. ";
	for(int i = 0; i < vertices; i++) {
		cin >> name;
		vertexNames[i] = name;
	}
	
	for(int i = 0; i < vertices; i++) {
		adj_mat[i][i] = 0;
		for(int j = i + 1; j < vertices; j++) {
			cout << "\nEnter the weight of edge ("<<vertexNames[i] <<", "<<vertexNames[j] <<"). "; {
				cin >> weight;
				if(weight != 0)
					adj_mat[i][j] = weight;
				adj_mat[j][i] = adj_mat[i][j];
			}
		}
	}
}

void display(int vertices, map <int, string> vertexNames)
{
	int i, j;
	for(i = 0; i < vertices; i++) {
		for(j = 0; j < vertices; j++)
			(adj_mat[i][j] == INF) ? cout << "INF " : cout << adj_mat[i][j] << " ";
		cout<<endl;
	}
	/*map<int, string>::iterator itr;
	for (itr = vertexNames.begin(); itr != vertexNames.end(); ++itr) { 
        cout << '\t' << itr->first 
             << '\t' << itr->second << '\n'; 
    } */
}

int main()
{
	int choice, vertices;
	map <int, string> vertexNames;
	string source, destination;
	do
	{
		cout << "\nMENU :\n1. Create a graph\n2. Display the graph\n3. Find shotest path\n4. Exit\nEnter your choice : ";
		cin >> choice;
		switch(choice)
		{
			case 1:
				cout << "\nEnter number of vertices. ";
				cin >> vertices;
				create(vertices, vertexNames);
				break;
			case 2:
				cout<<"\nThe adjacency matrix of graph is :\n";
				display(vertices, vertexNames);
				break;
			case 3:
				cout << "Enter the source : " ;
				cin >> source;
				cout << "Enter the destination : " ;
				cin >> destination;
				dijiktra(vertexNames, source, destination, vertices);
				break;
			case 4:
				return 0;
		}
	}while(1);
	return 0;
}

/*OUTPUT:
MENU :
1. Create a graph
2. Display the graph
3. Find shotest path
4. Exit
Enter your choice : 1

Enter number of vertices. 6
Enter the names of vertices. Pune Mumbai Nashik Nagpur Jalgaon Aurangabad

Enter the weight of edge (Pune, Mumbai). 1

Enter the weight of edge (Pune, Nashik). 6

Enter the weight of edge (Pune, Nagpur). 7

Enter the weight of edge (Pune, Jalgaon). 0

Enter the weight of edge (Pune, Aurangabad). 0

Enter the weight of edge (Mumbai, Nashik). 4

Enter the weight of edge (Mumbai, Nagpur). 0

Enter the weight of edge (Mumbai, Jalgaon). 1

Enter the weight of edge (Mumbai, Aurangabad). 0

Enter the weight of edge (Nashik, Nagpur). 3

Enter the weight of edge (Nashik, Jalgaon). 2

Enter the weight of edge (Nashik, Aurangabad). 2

Enter the weight of edge (Nagpur, Jalgaon). 0

Enter the weight of edge (Nagpur, Aurangabad). 2

Enter the weight of edge (Jalgaon, Aurangabad). 1

MENU :
1. Create a graph
2. Display the graph
3. Find shotest path
4. Exit
Enter your choice : 2

The adjacency matrix of graph is :
0 1 6 7 INF INF 
1 0 4 INF 1 INF 
6 4 0 3 2 2 
7 INF 3 0 INF 2 
INF 1 2 INF 0 1 
INF INF 2 2 1 0 

MENU :
1. Create a graph
2. Display the graph
3. Find shotest path
4. Exit
Enter your choice : 3

Enter the source : Nashik
Enter the destination : Jalgaon

The distance from Nashik to Jalgaon = 2
Path to be followed = Nashik->Jalgaon

MENU :
1. Create a graph
2. Display the graph
3. Find shotest path
4. Exit
Enter your choice : 3

Enter the source : Pune 
Enter the destination : Aurangabad

The distance from Pune to Aurangabad = 3
Path to be followed = Pune->Mumbai->Jalgaon->Aurangabad

MENU :
1. Create a graph
2. Display the graph
3. Find shotest path
4. Exit
Enter your choice : 3

Enter the source : Nagpur
Enter the destination : Jalgaon

The distance from Nagpur to Jalgaon = 3
Path to be followed = Nagpur->Aurangabad->Jalgaon 

MENU :
1. Create a graph
2. Display the graph
3. Find shotest path
4. Exit
Enter your choice : 3

Enter the source : xxx
Enter the destination : Pune

Source not found

*/