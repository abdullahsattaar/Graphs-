#include<iostream>
#include<fstream>
#include<list>
using namespace std;

class Node
{
	int destination;
	Node* next;
public:
	Node()
	{
		destination = 0;
		next = nullptr;
	}
	Node(int dest)
	{
		destination = dest;
		next = nullptr;
	}
	Node(int dest, Node* n)
	{
		destination = dest;
		next = n;
	}
	int returndestination() // getter of destination
	{
		return destination;
	}
};


class Graph
{
	int v;
	list<Node>* adj;
public:
	Graph(int v)
	{
		this->v = v;
		adj = new list<Node>[v];
	}

	Node* newAdjListNode(int dest)
	{
		return new Node(dest);
	}

	void addEdge(int src, int dest)
	{

		adj[src].push_back(*newAdjListNode(dest));
	}

	void TakeInput(string file)
	{
		ifstream f;

		f.open(file);

		if (!f.is_open())
		{
			cout << " error" << endl;
		}
		else
		{
			int i = 0;

			while (!f.eof())
			{
				char input[50], input2[50];

				f.getline(input, 50, '\n');

				int index = 0;
				for (int j = 0; j < strlen(input); j++)
				{

					if (input[j] - 48 >= 0 && input[j] - 48 <= 9)
					{
						input2[index] = input[j];

						index++;
					}
				}
				input2[index] = '\0';
				for (int j = 0; j < strlen(input); j++)
				{
				cout << input[j] << " ";
				}
				int size = strlen(input2);
				for (int j = 0; j < strlen(input2); j++)
				{
					cout << input2[j] << " ";
				}
				cout << endl;

				if (i >= 1)
				{
					for (int j = 1; j < strlen(input2); j++)
					{
						if (input2[j] - 48 == 1)
						{
							addEdge(input2[0] - 48, j - 1);
						}
					}
				}
				i++;
			}

		}
	}

	void ExploreFunction(int start, bool visited[])
	{
		visited[start] = true;
		cout << start << " ";
		list<Node>::iterator i;
		for (i = adj[start].begin(); i != adj[start].end(); ++i)
		{
			if (!visited[i.operator*().returndestination()])
			{
				ExploreFunction(i.operator*().returndestination(), visited);
			}
		}

	}
	void ExploreFunction(int start)    // Wrapper function
	{
		bool* visit = new bool[v];
		for (int i = 0; i < v; i++)
		{
			visit[i] = false;
		}
		ExploreFunction(start, visit);
	}

};

int main()
{
	Graph g(9); // Total 9 vertices in graph 
	g.TakeInput("AdjacencyList.txt");
	cout << "Following is Depth First Traversal\n";
	g.ExploreFunction(0);
	/* sample output
	nextNode = 0
	nextNode = 1
	nextNode = 7
	nextNode = 2
	nextNode = 3
	nextNode = 4
	nextNode = 8
	nextNode = 5
	nextNode = 6	*/

	//if (g.hasCycle())  //in our case it should return true as there are cycles in the graph
	//	cout << "Graph contains cycle";
	//else
	//	cout << "Graph doesn't contain cycle";
	return 0;
}