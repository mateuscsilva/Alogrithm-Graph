// breadth-first search
void bfs(vector<vertex> &allVertex){
	for(int i = 0; i < allVertex.size(); i++){
		allVertex[i].visit = 0;
		allVertex[i].color = -1;
		allVertex[i].father = -1;
		allVertex[i].distance = INT_MAX;
	}
	queue <int> next;
	next.push(allVertex[0].id);
	allVertex[0].visit = 1;
	allVertex[0].distance = 0;
	while(!next.empty()){
		int firstVertex = next.front();
		next.pop();
		for(int i = 0; i < allVertex[firstVertex].adj.size(); i++){
			int secondVertex = allVertex[firstVertex].adj[i].adj_vertex.second;
			if(allVertex[secondVertex].visit == 0){
				next.push(secondVertex);
				allVertex[secondVertex].visit = 1;
				allVertex[secondVertex].distance = allVertex[firstVertex].distance + 1;
				allVertex[secondVertex].father = allVertex[firstVertex].id;
			}	
		}
	}	
}

// depth-first search recursion
void dfs(vector<vertex> &allVertex, int firstVertex, int *time){
	(*time) = (*time) + 1;
	allVertex[firstVertex].visit = 1;
	allVertex[firstVertex].distance = (*time);
	for(int i = 0; i < allVertex[firstVertex].adj.size(); i++){
		int secondVertex = allVertex[firstVertex].adj[i].adj_vertex.second;
		if(allVertex[secondVertex].visit == 0){
			allVertex[secondVertex].father = firstVertex;
			dfs(allVertex, secondVertex, time);
		}
	}
	allVertex[firstVertex].visit = 2;
	(*time) = (*time) + 1;
	allVertex[firstVertex].time = (*time);
}

// depth-first search loop
void dfsLoop(vector<vertex> &allVertex){
	for(int i = 0; i < allVertex.size(); i++){
		allVertex[i].father = -1;
		allVertex[i].visit = 0;
		allVertex[i].father = -1;
	}
	int time = 0;
	for(int i = 0; i < allVertex.size(); i++){
		if(allVertex[i].visit == 0){
			dfs(allVertex, allVertex[i].id, &time);
		}
	}
}

//test if a graph as connect
void connectGraph(vector<vertex> &allVertex){
	dfs(allVertex, allVertex[0].id, 0);
	bool connect = true;
	for(int i = 0; i < allVertex.size(); i++){
		if(!allVertex[i].visit){
			connect = false;
		}
	}
	if(connect){
		cout<<"Connect Acyclic Graph\n";
	}else{
		cout<<"Desconnect Acyclic Graph\n";
	}
}

//test if the graph has at least on cycle
void acyclicGraphLoop(vector<vertex> &allVertex){
	bool checkAcyclic = true;
	queue <int> next;
	next.push(allVertex[0].id);
	allVertex[0].visit = 1;
	while(!next.empty()){
		int firstVertex = next.front();
		next.pop();
		for(int i = 0; i < allVertex[firstVertex].adj.size(); i++){
			int secondVertex = allVertex[firstVertex].adj[i].adj_vertex.second;
			if(allVertex[secondVertex].visit == 0){
				next.push(secondVertex);
				allVertex[secondVertex].visit = 1;
				allVertex[secondVertex].father = firstVertex;
			}else if(allVertex[secondVertex].visit > 0 && allVertex[firstVertex].father != secondVertex){
				checkAcyclic = false;
			}	
		}
	}
	if(checkAcyclic){
		cout<<"Acyclic Graph\n";
	}else{
		cout<<"Grpah has cycle\n";
	}	
}

// auxiliar depth-first search recursion for topological sort
void topologicalDfs(vector<vertex> &allVertex, list<vertex> &topology, int firstVertex, int *time){
	(*time) = (*time) + 1;
	allVertex[firstVertex].visit = 1;
	allVertex[firstVertex].distance = (*time);
	for(int i = 0; i < allVertex[firstVertex].adj.size(); i++){
		int secondVertex = allVertex[firstVertex].adj[i].adj_vertex.second;
		if(allVertex[secondVertex].visit == 0){
			allVertex[secondVertex].father = firstVertex;
			topologicalDfs(allVertex, topology, secondVertex, time);
		}
	}
	allVertex[firstVertex].visit = 2;
	(*time) = (*time) + 1;
	allVertex[firstVertex].time = (*time);
	topology.push_front(allVertex[firstVertex]);
}

// auxiliar depth-first search loop for topological sort
void topologicalDfsLoop(vector<vertex> &allVertex, list<vertex> &topology){
	for(int i = 0; i < allVertex.size(); i++){
		allVertex[i].father = -1;
		allVertex[i].visit = 0;
		allVertex[i].father = -1;
	}
	int time = 0;
	for(int i = 0; i < allVertex.size(); i++){
		if(allVertex[i].visit == 0){
			topologicalDfs(allVertex, topology, allVertex[i].id, &time);
		}
	}
}

void topologicalSort(vector<vertex> &allVertex){
	list<vertex> topology;
	topologicalDfsLoop(allVertex, topology);
	cout<<"topologicalSort: ";
	for(list<vertex>::iterator it = topology.begin(); it != topology.end(); it++){
		cout<<(*it).id<<" ";
	}
	cout<<endl;
}

bool compare_edge(edge a, edge b){
	return a.weight < b.weight;
}

vertex Makeset(vertex v){
	v.height = 0;
	v.father = v.id;
	return v;
}

vertex Findset(vertex v, vector<vertex> &allVertex){
	if(v.father != v.id){
		v = Findset(allVertex[v.father], allVertex);
	}
	return v;
}

void Link(vertex x, vertex y, vector<vertex> &allVertex){
	if(allVertex[x.id].height > allVertex[y.id].height){
		allVertex[y.id].father = allVertex[x.id].father;
	}else {
		allVertex[x.id].father=allVertex[y.id].father;
		if(allVertex[y.id].height==allVertex[x.id].height){
			allVertex[y.id].height++;	
		}
	}
}

void Union(vertex x, vertex y, vector<vertex> &allVertex){
	Link(Findset(allVertex[x.id], allVertex), Findset(allVertex[y.id], allVertex), allVertex);
} 

void minimumSpanningTreeKruskal(vector<vertex> &allVertex){
	int totalSum = 0;
	vector<edge> adj;
	vertex vTemp1, vTemp2;
	for(int i = 0; i < allVertex.size(); i++){
		vertex v;
		v.id = i;
		v = Makeset(v);
		allVertex[i] = v;
		for(int j = 0; j < allVertex[i].adj.size(); j++){
			adj.push_back(allVertex[i].adj[j]);	
		}
	}

	sort(adj.begin(), adj.end(), compare_edge);
	
	for(int i = 0; i < adj.size(); i++){
		edge e = adj[i];
		vTemp1 = Findset(allVertex[e.adj_vertex.first], allVertex);
		allVertex[e.adj_vertex.first].father = vTemp1.father;
		vTemp2 = Findset(allVertex[e.adj_vertex.second], allVertex);
		allVertex[e.adj_vertex.second].father = vTemp2.father;

		if(allVertex[e.adj_vertex.first].father != allVertex[e.adj_vertex.second].father){
			Union(allVertex[e.adj_vertex.first], allVertex[e.adj_vertex.second], allVertex);
			totalSum += e.weight;
		}
	}
	cout<<"Tree weight = "<<totalSum<<endl;
}

void chooseAlgorithm(char *code, vector<vertex> &allVertex){
	cout<<"Begin - "<<code<<endl;
	if(strcmp(code, "dfs") == 0){
		dfsLoop(allVertex);
	}else if(strcmp(code, "bfs") == 0){
		bfs(allVertex);
	}else if(strcmp(code, "acyclic") == 0){
		acyclicGraphLoop(allVertex);
	}else if(strcmp(code, "connectGraph") == 0){
		connectGraph(allVertex);
	}else if(strcmp(code, "topological-sort") == 0){
		topologicalSort(allVertex); //Graph should be directed
	}else if(strcmp(code, "kruskal") == 0){
		minimumSpanningTreeKruskal(allVertex);
	}
	cout<<"End - "<<code<<endl;
}