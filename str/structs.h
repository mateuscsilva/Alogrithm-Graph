#ifndef STRUCTS_H
#define STRUCTS_H

#endif

using namespace std;

struct edge{
	pair<int, int> adj_vertex;
	int weight = 0;
};

struct vertex{
	int id;
	int father = -1;
	int color = -1;
	int time = -1;
	int distance = -1;
	int visit = 0;
	vector<edge> adj;
};