#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <list>
#include <sstream>
#include <utility>
#include <climits>
#include <string.h>
#include "../str/structs.h"
#include "../str/utils.h"

using namespace std;

int main(int argc, char* argv[]){
	vector<vertex> allVertex;
	// string default_filename_code = "dfs"; 
	// string default_filename_instance = "../instance/instance_example.txt";
	char *filename_code;
	char *filename_instance;
	bool directed_graph = false;
	bool weigheted_graph = false;
	for(int i=0; i<argc; i++){
		if(strcmp(argv[i],"--code") == 0){
			filename_code = argv[i+1];
			i++;
		}else if(strcmp(argv[i],"--instance") == 0){
			filename_instance = argv[i+1];
			i++;
		}else if(strcmp(argv[i],"--directed") == 0){
			directed_graph = atoi(argv[i+1]); //0->false | 1->true
			i++;
		}else if(strcmp(argv[i],"--weight") == 0){
			weigheted_graph = atoi(argv[i+1]); //0->false | 1->true
			i++;
		}
	}
	read_instance(filename_instance, directed_graph, weigheted_graph, allVertex);
	chooseAlgorithm(filename_code, allVertex);
}