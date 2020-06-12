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
	}
	cout<<"End - "<<code<<endl;
}