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
	bool visit = false;
	vector<edge> adj;
};