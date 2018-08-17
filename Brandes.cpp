// a.out Graph.txt source.txt Centrality.txt

// Graph.txt = File containing vertices and edges by specifying edge on each line
// source.txt = List of source vertices separated by \t
// Centrality.txt = File to write final Betweenness centrality values on


#include <typeinfo>
#include <bits/stdc++.h>
#include <limits.h>
#include <fstream>
#include <cstdio>
#include <utility>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
using namespace std;

typedef pair<int, int> iPair;

vector< vector<iPair> > Adj;
set < int > sources;
float *Centrality;
int V, E, W;
iPair **nodes; 
int *ref;

//Read and store source Vertices
void readSource(char *file)
{
	int s;
	fstream infile;
	infile.open(file);
	while(infile >> s) sources.insert(s); 
	infile.close();      							
}

void Buildgraph(char *file )
{
	int flag = 0;
	fstream infile;
	char ch;
	int a, b, c=1;
	float e;

	infile.open(file);
	infile >> V >> E;                   			//Read number of V and E
	Centrality = (float*)calloc(V+1 , sizeof(float));
	vector<iPair> X;
	for(int i=1 ; i<=V ; i++) 
	{
		Adj.push_back(X);
	}
	if(flag == 0)									//Graph is undirected
	{
		for(int i=1 ; i<=E ; i++)
		{           
			infile >> a >> b ;  
			//if(a==b) continue;           
			Adj[a].push_back(make_pair(1, b));		//Adding b to adj list of a for edge(a, b)
			Adj[b].push_back(make_pair(1, a));      //Adding a to adj list of b as graph is undirected
		}
	}
	else											//Graph is directed
	{
		for(int i=1 ; i<=E ; i++)
		{           
			infile >> a >> b >> c;             
			Adj[a].push_back(make_pair(c, b)); 		//Adding b to adj list of a for edge(a, b) with wt=c
		}
	}
	infile.close();	
}

struct comparer {

    bool operator() (iPair lhs , iPair rhs) const {
    	if(lhs.first == rhs.first) return (lhs.second < rhs.second);
    	else return lhs.first < rhs.first;
    }
};

struct comparChild {

    bool operator() (iPair lhs , iPair rhs) const {
        return lhs.second < rhs.second;
    }
};


void Brandes()
{
	int i, currentNode, *temp, min, mIndex, *numPaths, src;
	float *delta;
	int ver , dist , minDist;
	vector <int > discoveryList;
	multiset<iPair , comparer > Q;

	
	set <iPair, comparChild> SetChild; 
	
	ref = (int*)calloc(V+1 , sizeof(int));
	temp = (int*)calloc(V+1 , sizeof(int));
	numPaths = (int*)calloc(V+1, sizeof(int));
	delta = (float*)calloc(V+1, sizeof(float));
	nodes = (iPair**)malloc((V+1)*sizeof(iPair*));	

	
	//only |Src| pairs are needed to store but we cant access by their index so we're taking space for V+1
	for(i=1 ; i<=V ; i++) nodes[i] = (iPair*)malloc((V+1)*sizeof(iPair));
	
	//Running Dijkstra from every source
	for(set <int >::iterator ss = sources.begin() ; ss != sources.end() ; ss++)
	{		
		printf("Done for source %d\n", src);
		src = *ss;
		//Q.clear();
		discoveryList.clear();
		vector<int> parentDict[V+1]; 
		memset(numPaths , 0 , V+1 );
		for(int k=1; k<=V; k++) delta[k]=0.0;

		//Initializations of data structures	
		for(i=1 ; i<=V ; i++) 
		{
			for(set <int >::iterator si = sources.begin() ; si != sources.end() ; si++)
			{
				nodes[i][*si] = make_pair(INT_MAX, 0);
			} 
		} 
		multiset<iPair> ::iterator ms;
		//Initialize number of paths and distance as MAX 	
		numPaths[src] = 1;		
		for(i=1 ; i<=V ; i++) ref[i] = INT_MAX; 
		ref[src] = 0;
 
		i=0;
		while(++i <src)  Q.insert(make_pair(INT_MAX , i));
		Q.insert(make_pair(0 , src));
		while(++i <= V)  Q.insert(make_pair(INT_MAX , i));

		while(!Q.empty())
		{
			//for(ms=Q.begin(); ms!=Q.end(); ms++) printf(" %d: %d", ms->second, ms->first);
			//printf("\n");
			minDist = Q.begin()->first;	
			min = minDist;
			currentNode = Q.begin()->second;
			nodes[currentNode][src] = make_pair(minDist , numPaths[currentNode]); 
			discoveryList.push_back(currentNode);

			//Creating a set of child nodes of currentNode
			set<iPair , comparChild > P( Adj[currentNode].begin(), Adj[currentNode].end());

			//Updating distances of children in Dijkstra priority queue
			for(set <iPair>::iterator child=P.begin(); child!=P.end(); child++)
			{
				int ch = child->second;							//ch stores the index of child
				dist = child->first;							//dist stores distance of child from src
				if( (ref[ch] !=-1) && (dist+minDist < ref[ch]) )
				{   
					Q.erase(Q.find(make_pair(ref[ch] , ch)));
					Q.insert(make_pair(dist+minDist , ch));
					ref[ch] = dist+minDist;
					parentDict[ch].push_back( currentNode );
					numPaths[ch] = numPaths[currentNode]; 
				}  
				else if( (ref[ch] !=-1) && (dist+minDist == ref[ch]))
				{   
					if(ch == currentNode) continue;
					parentDict[ch].push_back(currentNode);
					numPaths[ch] += numPaths[currentNode];  
				} 
			}  
			P.clear();
			Q.erase(Q.begin());
			ref[currentNode] = -1;
		}    
		
		while(!discoveryList.empty())
		{

			int childNode = discoveryList.back();
			discoveryList.pop_back();
			if(childNode == src)
			{
				Centrality[src] += float(delta[src]/2.0);
				continue;
			}
			if(const bool is_in = sources.find(childNode) != sources.end()) delta[childNode] += 1.0;
	
			Centrality[childNode] += float(delta[childNode]/2.0);
			vector<int> ::iterator parentNode;
			for(parentNode=parentDict[childNode].begin() ; parentNode!=parentDict[childNode].end() ; parentNode++)
			{
				if(numPaths[childNode] > 0)
				{
					delta[*parentNode] += delta[childNode]*float(numPaths[*parentNode])/float(numPaths[childNode]);
				}
			}

		} 		
	} 
}


int main(int argc, char **argv)
{
	readSource(argv[2]);
	printf("Read source vertices\n\n");
	Buildgraph(argv[1]);
	printf("Read graph\n\n");
	clock_t tic = clock();
	Brandes();
	clock_t toc = clock();

	FILE* fp;
	fp = fopen(argv[3], "w");
	for(int i=1; i<=V; i++) fprintf(fp, "%d\t%f\n", i, Centrality[i]); 

	printf("Time taken for Betweenness Centrality: %f seconds \n", (double)(toc - tic) / ((CLOCKS_PER_SEC)));
	//for(int i=1; i<=V; i++) printf("%d = %f   ",i, Centrality[i]); 

	return 0;
}


