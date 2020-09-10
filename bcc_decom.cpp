<<<<<<< HEAD:bcc_decom.cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int timer = 0;
int *discover, *parent;
int *finish ;
int *color;
int *low;
char *articulation;
vector <pair <int,int> > dump;

void BCC(vector <vector <int> > &graph, int node)
{
	timer++;
	discover[node] = timer;
	color[node] = 'g';	
	low[node] = discover[node];

	for(auto v : graph[node])
	{
		if(color[v]=='w')
		{
			parent[v] = node;
			dump.push_back(make_pair(node, v));
			BCC(graph, v);
			low[node] = min(low[node], low[v]);
			if(low[v] >= discover[node])
			{
				printf("Following is a new component:\n");
				pair <int, int> p = make_pair(node, v);
				while(dump.back() != p)
				{
					printf("%d--%d\n", dump.back().first, dump.back().second);
					dump.pop_back();
				}
				printf("%d--%d\n", dump.back().first, dump.back().second);
				dump.pop_back();
			}
		}
		else if(v != parent[node] && discover[v] < discover[node])
		{
			dump.push_back(make_pair(node, v));
			low[node] = min(low[node], discover[v]);
		}
	}
	color[node] = 'b';
	timer++;
	finish[node] = timer;
}


int main() {

	int V, E, a, b;
	vector <vector <int> > graph;
	cin >> V >> E;
	graph.resize(V+1);
	printf("V=%d and E=%d\n",V, E);

	while(E--)
	{
		cin >> a >> b;
		if(a==b) continue;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	discover = new int[V+1];
	parent = new int[V+1];
	finish = new int[V+1];
	color = new int[V+1];
	low = new int[V+1];

	for(int i=0; i<=V; ++i) color[i] = 'w';
    BCC(graph, 1);
    
	return 0;
}
=======
#include <iostream>
#include <vector>
#include <stack>
// using namespace std;

int timer = 0;
int *discover, *parent;
int *finish ;
int *color;
int *low;
char *articulation;
std::vector <std::pair <int,int> > dump;

void BCC(std::vector <std::vector <int> > &graph, int node)
{
	timer++;
	discover[node] = timer;
	color[node] = 'g';	
	low[node] = discover[node];

	for(auto v : graph[node])
	{
		if(color[v]=='w')
		{
			parent[v] = node;
			dump.push_back(make_pair(node, v));
			BCC(graph, v);
			low[node] = min(low[node], low[v]);
			if(low[v] >= discover[node])
			{
				printf("Following is a new component:\n");
				pair <int, int> p = make_pair(node, v);
				while(dump.back() != p)
				{
					printf("%d--%d\n", dump.back().first, dump.back().second);
					dump.pop_back();
				}
				printf("%d--%d\n", dump.back().first, dump.back().second);
				dump.pop_back();
			}
		}
		else if(v != parent[node] && discover[v] < discover[node])
		{
			dump.push_back(make_pair(node, v));
			low[node] = min(low[node], discover[v]);
		}
	}
	color[node] = 'b';
	timer++;
	finish[node] = timer;
}


int main() {

	int V, E, a, b;
	std::vector <std::vector <int> > graph;
	cin >> V >> E;
	graph.resize(V+1);
	std::printf("V=%d and E=%d\n",V, E);

	while(E--)
	{
		std::cin >> a >> b;
		if(a==b) continue;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	discover = new int[V+1];
	parent = new int[V+1];
	finish = new int[V+1];
	color = new int[V+1];
	low = new int[V+1];

	for(int i=0; i<=V; ++i) color[i] = 'w';
    BCC(graph, 1);
    
	return 0;
}
>>>>>>> test_branch:BCC_Decomposition.cpp
