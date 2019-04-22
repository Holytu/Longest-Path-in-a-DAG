#include <iostream>
#include <list>
#include <stack>

using namespace std;

#define NINF INT_MIN
///
class AdjListNode
{
	int v;
	int weight;
public:
	AdjListNode(int _v, int _w);
	int getV();
	int getWeight();
};

AdjListNode::AdjListNode(int _v, int _w)
{
	this->v = _v;
	this->weight = _w;
}

int AdjListNode::getV()
{
	return this->v;
}

int AdjListNode::getWeight()
{
	return this->weight;
}
///
class Graph
{
	int V; 
	list<AdjListNode> *adj;
	void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);

public:
	Graph(int V);
	void addEdge(int u, int v, int weight);
	void longestPath(int s);
	
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<AdjListNode>[V];
}

void Graph::addEdge(int u, int v, int weight)
{
	AdjListNode node(v, weight);
	adj[u].push_back(node); 
}

void Graph::topologicalSortUtil(int v, bool visited[], stack<int> &Stack)
{
	visited[v] = true;

	list<AdjListNode>::iterator i;

	for (i = adj[v].begin(); i != adj[v].end(); i++)
	{
		AdjListNode node = *i;
		if(visited[node.getV()] == false)
		{
			topologicalSortUtil(node.getV(), visited, Stack);
		}

	}

	Stack.push(v);
}

void Graph::longestPath(int s)
{
	int dist[V];
	bool *visited = new bool[V];
	stack<int> Stack;

	for (int i = 0; i < V; i++)
	{
		visited[i] = false;
	}

	for (int i = 0; i < V; i++)
	{
		if(visited[i] == false)
		{
			topologicalSortUtil(i, visited, Stack);
		}
	}

	for (int i = 0; i < V; i++)
	{
		dist[i] = NINF;
	}
	dist[s] = 0;

	while(Stack.empty() == false)
	{
		int u = Stack.top();
		Stack.pop();

		list<AdjListNode>::iterator i;
		if(dist[u] != NINF)
		{
			for (i = adj[u].begin(); i != adj[u].end(); i++)
			{
				if(dist[i->getV()] < dist[u] + i->getWeight() )
				{
					dist[i->getV()] = dist[u] + i->getWeight();
				}
			}
		}
	}

	for (int i = 0; i < V; i++)
	{
		if(dist[i] == NINF)
		{
			cout<<"NINF ";
		}
		else
		{
			cout<<dist[i]<<" ";
		}
	}
}

int main(void)
{
	Graph g(6);
	g.addEdge(0, 1, 5);
	g.addEdge(0, 2, 3);
	g.addEdge(1, 3, 6);
	g.addEdge(1, 2, 2);
	g.addEdge(2, 3, 7);
	g.addEdge(2, 4, 4);
	g.addEdge(2, 5, 2);
	g.addEdge(3, 4, -1);
	g.addEdge(3, 5, 1);
	g.addEdge(4, 5, -2);

	g.longestPath(1);

	return 0; 
}