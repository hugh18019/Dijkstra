#include <iostream>
#include <fstream>
#include <sstream>
#include "MinHeap.h"

using namespace std;

vector<vector<tuple<int, int>>> readFile ();
vector<tuple<int, int>> init_shortest_paths (int graph_size);
vector<tuple<int, int>> Dijkstra_Algo (vector<vector<tuple<int, int>>> graph);

int main() 
{
    // A vector represents the graph
    // Each index of the vector is a vertex in the graph
    vector<vector<tuple<int, int>>> graph;
    // A vector that contains each vertex and its shortest path from the staring point
    vector<tuple<int, int>> shortest_paths_vector;

    graph = readFile();

    // Initialize the shortest_paths vector to have the same size as the graph
    shortest_paths_vector = init_shortest_paths(graph.size());

    // Turn the shortest_paths_vector into a minimum heap
    MinHeap shortest_paths(shortest_paths_vector, shortest_paths_vector.size(), shortest_paths_vector.size());

    // Dijkstra_Algo(graph);

    return 0;
    
}

vector<vector<tuple<int, int>>> readFile ()
{
    fstream data;
    data.open("miniData.txt", ios_base::in);
    string line;

    // A vector represents the graph
    // Each index of the vector is a vertex in the graph
    vector<vector<tuple<int, int>>> graph;

    while (getline(data, line))
    {
        stringstream ss(line);
        int vertex;
        char comma;
        int length;

        // Consume the vertex at the start of each line in input file
        ss >> vertex;
        // Temperary vector for storing the neighbors of each vertex and their respective lengths
        vector<tuple<int, int>> temp;
        
        while (ss >> vertex >> comma >> length)
        {
            // Push each pair of vertex and length on each line onto the graph as a tuple
            temp.push_back(make_tuple(vertex, length));
        }

        
        if (!temp.empty())
            graph.push_back(temp);
        // If a line in the input file only has a vertex, then push a tuple of 0 as its neighbor
        else
        {
            vector<tuple<int, int>> temp2;
            temp2.push_back(make_tuple(0, 0));
            graph.push_back(temp2);
        }
    }
    return graph;
}


vector<tuple<int, int>> init_shortest_paths (int graph_size)
{
    vector<tuple<int, int>> shortest_paths;

    // The starting vertex is 1 and has the length 0
    shortest_paths.push_back( make_tuple(1, 0));

    // Each element is initialize to -1 to represent positive infinity.
    // Since Dijkstra's algorithm does not work on negative edge lengths & all input edge are positive, it's safe to use -1 here.
    for (int i = 1; i < graph_size; i++)
    {   
        shortest_paths.push_back( make_tuple(i, -1) );
    }
    
    return shortest_paths;
}

vector<tuple<int, int>> Dijkstra_Algo (vector<vector<tuple<int, int>>> graph) 
{
    
}