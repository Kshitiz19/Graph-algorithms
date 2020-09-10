#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sys/types.h>
#include <set>
#include <time.h>
#include <queue>

using namespace std;

void cluster(char *graphFile)
{
	int V, E, a, b, c;
	set <int> X;
	fstream infile;
	infile.open(graphFile);

	infile >> V >> E;
	vector< set<int> > Adj;

	for(int i=0; i<=V; i++) Adj.push_back(X);

	for(int i=1; i<=E; i++)
	{
		infile >> a >> b;
		Adj[a].insert(b);
		Adj[b].insert(a);
	}

/*	for(int i=1; i<=V; i++)
	{
		printf("%d-->\t", i);
		for(set<int>:: iterator j=Adj[i].begin(); j!=Adj[i].end(); j++) printf("%d   ", *j);
		printf("\n");
	}
*/
	int cluster[V+1], counter=0;
	set<int> list;
	int sample = V*0.1;
	srand(time(0));

	for(int i=1, element; i<=sample; i++)
		{
			element = (rand()%V + 1);
			//printf("%d\t", element);
			list.insert(element);
		}
	//printf("\n\n");
	queue<int> Q;

	bool visited[V+1];
	for(int i=1; i<=V; i++) visited[i] = false;

	for(set<int>:: iterator j=list.begin(); j!=list.end(); j++)
		{
			Q.push(*j);
			cluster[*j] = ++counter;
			visited[*j] = true;
		}

	int currentNode, currentCluster;

	while(!Q.empty())
	{
		currentNode = Q.front();
		Q.pop();
		visited[currentNode] = true;
		currentCluster = cluster[currentNode];
		//printf("\n Starting with node %d\n", currentNode);
		for(set<int>:: iterator j=Adj[currentNode].begin(); j!=Adj[currentNode].end(); j++)
			{
				if(visited[*j] == false)
					{
						Q.push(*j);
						cluster[*j] = currentCluster;
						//printf("\nAssigned cluster %d to node %d", currentCluster, *j);
						visited[*j] = true;
					}
			}
	}
	for(int i=1; i<=V; i++) printf("%d\n", cluster[i]);
}

int main(int argc, char** argv)
{
	cluster(argv[1]);
	return 0;
}
