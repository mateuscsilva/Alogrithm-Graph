void read_instance(char *filename, bool directed_graph, bool weighted_graph, vector<vertex> &allVertex){
	cout<<"Begin - read\n";
	ifstream file;
	file.open(filename);

	if(!file){
        cout<<"file not found \n";
        return;
    }
    int vertex1, vertex2, weight = 0;
    edge e1, e2;

	while(!file.eof()){
		int size = allVertex.size() - 1;
		file>>vertex1>>vertex2;

		if(weighted_graph){
			file>>weight;
		}		
		if(size < vertex1){
			vertex v;
			v.id = vertex1;
			allVertex.push_back(v);
		}
		size = allVertex.size() - 1;
		if(size < vertex2){
			vertex v;
			v.id = vertex2;
			allVertex.push_back(v);
		}

		e1.weight = weight;
		e2.weight = weight;
		e1.adj_vertex = make_pair(vertex1, vertex2);
		e2.adj_vertex = make_pair(vertex2, vertex1);
		allVertex[vertex1].adj.push_back(e1);
		if(!directed_graph){
			allVertex[vertex2].adj.push_back(e2);
		}

	}
   	cout<<"End - read\n";
}
