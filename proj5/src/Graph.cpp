#include "Graph.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include "exceptions.h"
#include "Utils.h"

using namespace std;
Graph::Graph(string filename){
	filename; //Filter file.
	ifstream infile(filename.c_str());
	if(infile.is_open()){
		printDebug("Reading in file was a success" ,2);
	}else{
		cout << "INPUT ERROR" << endl;
		exit(EXIT_FAILURE);
	}
	//do program

	string line;
	int i = 0;
	//grab each number

	//add input to graph
	while(getline(infile, line)){
		int startVertex;
		int targetVertex;
		int cost;
		vector<string> lineVector = split(line);
		//test the split function for accuracy
		for(int x = 0; x < lineVector.size(); x++){
			printDebug(lineVector[x], 5);
		}
		//first line different from rest
		if (i == 0){
			vertexes = num<int>(lineVector.at(0));
			edges = num<int>(lineVector.at(1));
			graph.resize(vertexes);
			for (int x = 0; x < vertexes; x++){
				graph[x].resize(vertexes);
				for(int y = 0; y < graph[x].size(); y++){
					graph[x][y] = -1; //assign default -1
				}
			}
			i++;
		}else{
			startVertex  = num<int>(lineVector[0])-1;
			targetVertex = num<int>(lineVector[1])-1;
			cost = num<int>(lineVector[2]);
			graph[startVertex][targetVertex] = cost;
			graph[targetVertex][startVertex] = cost;
		}
	}

	//test proper graph
	if(DEBUG){
		printDebug("   01, 02, 03, 04, 05, 06, 07", 5);
		for(int x = 0; x < graph.size(); x++ ){
			string printString = ""+str<int>(x+1);
			for(int y = 0; y < graph[x].size(); y++){
				printString += ", "+str<int>(graph[x][y]);
			}
			printDebug(printString, 5);
		}
	}
}

int Graph::trips(int start, int stop, int people){
	vector <int> edgesSeen(edges);
	int current = start;
	int target = stop;
	vector<int> vertexesVisited(vertexes);
	int smallestEdge = tripsRecurse(current, target, edgesSeen, vertexesVisited);
	/*NOT ACTUALLY DONE YET*/
	return totalTrips;
}

int tripsRecurse(int current, int target, vector<int> edgesSeen, vector<int> vertexesVisited){
	//loop through list of current and grab highest edge
	//but add other edges to not-visited list
	vector<int> foundEdges(edges);
	int largestEdge = -1;
	int edgeFoundAt = -1;
	int anEdge = -1;
	for(int x = 0; x < graph[current].size(); x++){
		anEdge = graph[current][x];
		if(anEdge > largestEdge){
			largestEdge = anEdge;
			edgeFoundAt = x;
		}else{
			foundEdges[x] = anEdge;
		}
	}
	// if it's smaller than an edge we've seen before
	// return with -1
	for(int x = 0; x < edgesSeen.size(); x++){
		if(edgesSeen[x] > largestEdge){
			return -1;
		}
	}
	// if it's NOT, recurse, giving position of the highest edge as current
	// and adding ALL edges of current to edgesSeen;
	//if it returns with negative one, try second highest edge,
	//if no other edge, return with -1.
	//finally, return with smallestedge found.

}
