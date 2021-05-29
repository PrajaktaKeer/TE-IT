/*
Name: Prajakta Keer
Roll no.: 33231
Batch: L10
Assignment no.: 04
Problem Statement: Write a program to implement Bellman-Ford Algorithm using Dynamic Programming and verify the 
time complexity.
*/

#include<bits/stdc++.h>
using namespace std;

struct graph {
	int u, v, weight;
};

void printPath(vector<int>parent, int vertex)
{
    if(vertex < 0)
        return;
        
    printPath(parent, parent[vertex]);
    cout<<" -> "<<vertex;
}

// print the solution
void print(vector<int>dist, vector<int>parent)
{
    printf("\n\nVertex   Distance from Source\n");
    for (int i = 0; i < dist.size(); ++i) {
        cout << i << "\t\t" <<dist[i] << "\t\tPath : ";
        printPath(parent, i);
        cout << endl; 
    }
}

void bellmanFord(vector<struct graph> g, int srcVertex, int V, int E) {
    // Initialize distances from src to all other vertices as INFINITE
    vector<int> dist(V, INT_MAX), parent(V, -1);
    dist[srcVertex] = 0;
    bool change = true;
  
    //Relax all edges |V|-1 times. 
    for (int i = 1; i <= V - 1; i++) {
        change = false;
        for (int j = 0; j < E; j++) {
            int u = g[j].u;
            int v = g[j].v;
            int weight = g[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + weight;
                change = true;
            }
        }
    }
  
    // check for negative-weight cycles. 
    for (int i = 0; i < E && change; i++) {
        int u = g[i].u;
        int v = g[i].v;
        int weight = g[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "\nGraph contains negative weight cycle\n";
            return; // If negative cycle is detected, simply return
        }
    }
    print(dist, parent);
}

int checkEdge(vector<struct graph> &g, int s, int d, int w) {
    for(int i = 0; i < g.size(); i++) {
        if(g[i].u == s && g[i].v == d && g[i].weight == w)
            return 1;
    }
    return 0;
}

void createGraph(vector<struct graph> &g, int E, int V) {
    int src, dest, weight;
    
    for(int i = 0; i < E;) {
        cout << "\nEnter source, destination and weight of Edge " << i + 1 << " : ";
        cin >> src >> dest >> weight;

        if(src >=V || dest >= V) {
            cout << "\nThe source and destination must be in the range of 0-"<< V << endl;
            continue;
        }
        else if(src == dest) {
            cout << "Source and destination cannot be same\n";
            continue;
        }
        else if(checkEdge(g, src, dest, weight)) {
            cout << "Edge already exists\n";
            continue;
        } 
        else { 
            g.push_back({src, dest, weight});
            i++;
        }
    }
    cout << "\n***Graph is created***\n";
}

void displayGraph(vector<struct graph> &g, int E, int V) {
    cout << "\n***Adjacency Matrix***\n";

    int mat[V][V];
    memset(mat, 0, sizeof(mat));
    for(int i = 0; i < E; i++) 
        mat[g[i].u][g[i].v] = g[i].weight;
    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++)
            cout << mat[i][j] << "    ";
        cout << endl;
    }
}

int main() {
	vector<struct graph> g;
	int noOfEdges, noOfVertices, srcVertex;

	cout << "\nEnter number of vertices : ";
	cin >> noOfVertices;
	cout << "\nEnter number of edges : " ;
	cin >> noOfEdges;
    cout << "\nEnter the source vertex : ";
    cin >> srcVertex;

    createGraph(g, noOfEdges, noOfVertices);
    displayGraph(g, noOfEdges, noOfVertices);
	bellmanFord(g, srcVertex, noOfVertices, noOfEdges);
}

/*OUTPUT : 
Enter number of vertices : 5

Enter number of edges : 8

Enter the source vertex : 0

Enter source, destination and weight of Edge 1 : 0 1 -1

Enter source, destination and weight of Edge 2 : 0 2 4

Enter source, destination and weight of Edge 3 : 1 2 3

Enter source, destination and weight of Edge 4 : 1 3 2

Enter source, destination and weight of Edge 5 : 1 4 2

Enter source, destination and weight of Edge 6 : 3 2 5

Enter source, destination and weight of Edge 7 : 3 1 1

Enter source, destination and weight of Edge 8 : 4 3 -3

***Graph is created***

***Adjacency Matrix***
0    -1    4    0    0    
0    0    3    2    2    
0    0    0    0    0    
0    1    5    0    0    
0    0    0    -3    0   


Vertex   Distance from Source
0               0               Path :  -> 0
1               -1              Path :  -> 0 -> 1
2               2               Path :  -> 0 -> 1 -> 2
3               -2              Path :  -> 0 -> 1 -> 4 -> 3
4               1               Path :  -> 0 -> 1 -> 4

------------------------------------------------------------------------------

Enter number of vertices : 4

Enter number of edges : 4

Enter the source vertex : 0

Enter source, destination and weight of Edge 1 : 0 1 1

Enter source, destination and weight of Edge 2 : 1 2 -1

Enter source, destination and weight of Edge 3 : 2 3 -1

Enter source, destination and weight of Edge 4 : 3 0 -1

***Graph is created***

***Adjacency Matrix***
0    1    0    0    
0    0    -1    0    
0    0    0    -1    
-1    0    0    0  


Graph contains negative weight cycle

*/