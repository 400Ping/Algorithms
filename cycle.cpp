#include <iostream>
#include <limits.h>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

// Graph class represents a directed graph
// using adjacency list representation
class Graph {
public:
	map<int, bool> visited;
	map<int, list<int> > adj;
	map<int, list<int> > adj2;

	// function to add an edge to graph
	void addEdge(int v, int w);
	void addEdge2(int v, int w);

	// DFS traversal of the vertices
	// reachable from v
	void DFS(int v, int &count);

	void AllPathsUtil(int, int, bool[], int &count);
	void AllPaths(int s, int d, int &count, int V);

};

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v’s list.
    adj[w].push_back(v); 
}

void Graph::addEdge2(int v, int w)
{
	adj2[v].push_back(w); // Add w to v’s list.
    adj2[w].push_back(v); 
}

void Graph::DFS(int v, int &count)
{
	// Mark the current node as visited and
	// print it
	visited[v] = true;
	//cout << v << " ";
	count++;
	
	// Recur for all the vertices adjacent
	// to this vertex
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
		{
			addEdge2(*i, v);
			DFS(*i, count);			
		}
			
}

void Graph::AllPaths(int s, int d, int &count, int V)
{
	// Mark all the vertices as not visited
	bool* visited = new bool[V];

	// Initialize all vertices as not visited
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Call the recursive helper function to print all paths
	AllPathsUtil(s, d, visited, count);
}

void Graph::AllPathsUtil(int u, int d, bool visited[], int &count)
{
	// Mark the current node and store it in path[]
	visited[u] = true;


	// If current vertex is same as destination, then print
	// current path[]
	if (u == d) {
		count++;
	}
	else // If current vertex is not destination
	{
		// Recur for all the vertices adjacent to current
		// vertex
		list<int>::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
			if (!visited[*i])
				AllPathsUtil(*i, d, visited, count);
	}

	// Remove current vertex from path[] and mark it as
	// unvisited
	visited[u] = false;
}

// Driver's code
int main()
{
	bool y = true;
	bool AtLeastThreeCycle = false;
	Graph g;
	int vNum, eNum = 0;
	int a, b;
	cin >> vNum;
	while(true)
	{
		cin >> a;
		if(a == -1)
			break;
		cin >> b;
		g.addEdge(a, b);
		eNum++;
	}

	int DFSnode = 0;
	g.DFS(5, DFSnode);
	//cout << endl << DFSnode; // DFSnode == DFSedge+1
	if(vNum > DFSnode || eNum <= DFSnode)
		y = false;
	else if(eNum == DFSnode+1) // eNum == DFSedge+2
	{
		vector<int> vect;
		int count = 0;
		for(int v=1; v<=vNum; v++)
		{
			for (list<int>::iterator i = g.adj2[v].begin(); i != g.adj2[v].end(); ++i)
				vect.push_back(*i);

			for (list<int>::iterator j = g.adj[v].begin(); j != g.adj[v].end(); ++j)
			{
				vector<int>::iterator it = find(vect.begin(),vect.end(), *j);
				if(find(vect.begin(), vect.end(), *j)!=vect.end())
					;
				else
				{
					//cout << v << " " << *j << endl;
					g.AllPaths(v, *j, count, vNum);
					goto endLoop;
				}
			}
			vect.clear();
		}
		endLoop:
			if(count == 3)
				AtLeastThreeCycle = true;

	}
	else
		AtLeastThreeCycle = true;

	if(y)
		cout << "y" << endl;
	else
		cout << "n" << endl;
	
	if(AtLeastThreeCycle)
		cout << "There are at least three cycles." << endl;
	
	return 0;
}


// // C++ program to print all paths
// // from a source to destination.
// #include <iostream>
// #include <list>
// using namespace std;

// // A directed graph using
// // adjacency list representation
// class Graph {
// 	int V; // No. of vertices in graph
// 	list<int>* adj; // Pointer to an array containing
// 					// adjacency lists

// 	// A recursive function used by printAllPaths()
// 	void printAllPathsUtil(int, int, bool[], int &count);

// public:
// 	Graph(int V); // Constructor
// 	void addEdge(int u, int v);
// 	void printAllPaths(int s, int d, int &count);
// };

// Graph::Graph(int V)
// {
// 	this->V = V;
// 	adj = new list<int>[V];
// }

// void Graph::addEdge(int u, int v)
// {
// 	adj[u].push_back(v); // Add v to u’s list.
// 	adj[v].push_back(u);
// }

// // Prints all paths from 's' to 'd'
// void Graph::printAllPaths(int s, int d, int &count)
// {
// 	// Mark all the vertices as not visited
// 	bool* visited = new bool[V];

// 	// Initialize all vertices as not visited
// 	for (int i = 0; i < V; i++)
// 		visited[i] = false;

// 	// Call the recursive helper function to print all paths
// 	printAllPathsUtil(s, d, visited, count);
// }

// // A recursive function to print all paths from 'u' to 'd'.
// // visited[] keeps track of vertices in current path.
// // path[] stores actual vertices and path_index is current
// // index in path[]
// void Graph::printAllPathsUtil(int u, int d, bool visited[], int &count)
// {
// 	// Mark the current node and store it in path[]
// 	visited[u] = true;


// 	// If current vertex is same as destination, then print
// 	// current path[]
// 	if (u == d) {
// 		count++;
// 	}
// 	else // If current vertex is not destination
// 	{
// 		// Recur for all the vertices adjacent to current
// 		// vertex
// 		list<int>::iterator i;
// 		for (i = adj[u].begin(); i != adj[u].end(); ++i)
// 			if (!visited[*i])
// 				printAllPathsUtil(*i, d, visited, count);
// 	}

// 	// Remove current vertex from path[] and mark it as
// 	// unvisited
// 	visited[u] = false;
// }

// // Driver program
// int main()
// {
// 	// Create a graph given in the above diagram
// 	Graph g(6);
// 	g.addEdge(0, 1);
// 	g.addEdge(0, 2);
// 	g.addEdge(1, 3);
// 	g.addEdge(2, 3);
// 	g.addEdge(1, 4);
// 	g.addEdge(2, 4);
// 	g.addEdge(4, 5);

// 	int s = 0, d = 2, count = 0;
// 	cout << "Following are all different paths from " << s
// 		<< " to " << d << endl;
// 	g.printAllPaths(s, d, count);
// 	cout << count;

// 	return 0;
// }

// 	Graph g(6);
// 	g.add_edge(0, 1);
// 	g.add_edge(0, 2);
// 	g.add_edge(1, 3);
// 	g.add_edge(2, 3);
// 	g.add_edge(3, 4);
// 	g.add_edge(3, 5);
// 	g.add_edge(4, 5);