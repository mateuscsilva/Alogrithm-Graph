void bfs(vector<vertex> &allVertex){
	queue <int> next;
	next.push(allVertex[0].id);
	allVertex[0].visit = true;
	while(!next.empty()){
		int firstVertex = next.front();
		next.pop();
		for(int i = 0; i < allVertex[firstVertex].adj.size(); i++){
			int secondVertex = allVertex[firstVertex].adj[i].adj_vertex.second;
			if(!allVertex[secondVertex].visit){
				next.push(secondVertex);
				allVertex[secondVertex].visit = true;
			}	
		}
	}	
}

void dfs(vector<vertex> &allVertex, int firstVertex){
	allVertex[firstVertex].visit = true;
	for(int i = 0; i < allVertex[firstVertex].adj.size(); i++){
		int secondVertex = allVertex[firstVertex].adj[i].adj_vertex.second;
		if(!allVertex[secondVertex].visit){
			allVertex[secondVertex].father = firstVertex;
			dfs(allVertex, secondVertex);
		}
	}
}

void dfsLoop(vector<vertex> &allVertex){
	for(int i = 0; i < allVertex.size(); i++){
		allVertex[i].father = -1;
		allVertex[i].visit = false;
	}
	for(int i = 0; i < allVertex.size(); i++){
		if(!allVertex[i].visit){
			dfs(allVertex, allVertex[i].id);
		}
	}
}

void acyclicConnect(vector<vertex> &allVertex){
	dfs(allVertex, allVertex[0].id);
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


void acyclicGraphLoop(vector<vertex> &allVertex){
	checkAcyclic = true;
	queue <int> next;
	next.push(allVertex[0].id);
	allVertex[0].visit = true;
	while(!next.empty()){
		int firstVertex = next.front();
		next.pop();
		for(int i = 0; i < allVertex[firstVertex].adj.size(); i++){
			int secondVertex = allVertex[firstVertex].adj[i].adj_vertex.second;
			if(!allVertex[secondVertex].visit){
				next.push(secondVertex);
				allVertex[secondVertex].visit = true;
				allVertex[secondVertex].father = firstVertex;
			}else if(allVertex[secondVertex].visit && allVertex[firstVertex].father != secondVertex){
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

void chooseAlgorithm(char *code, vector<vertex> &allVertex){
	if(strcmp(code, "dfs") == 0){
		dfsLoop(allVertex);
	}else if(strcmp(code, "bfs") == 0){
		bfs(allVertex);
	}else if(strcmp(code, "acyclic") == 0){
		
	}else if(strcmp(code, "acyclic_connect") == 0){
		acyclicConnect(allVertex);
	}
}