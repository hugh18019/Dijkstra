#include <iostream>
#include <fstream>
#include <sstream>
#include "MinHeap.h"

using namespace std;

vector<vector<tuple<int, int>>> readFile();
vector<tuple<int, int>> Dijkstra_Algo(vector<MinHeap> graph);

int main() 
{

    vector<MinHeap> graph;

    vector<vector<tuple<int, int>>> graph2;
    graph2 = readFile();

    // fstream data;
    // data.open("miniData.txt", ios_base::in);

    // string line;

    // while(getline(data, line))
    // {
    //     stringstream ss(line);
        
    //     int vertex;
    //     int neighbor;
    //     char comma;
    //     int length;

    //     vector<tuple<int, int>> heap;

    //     ss >> vertex;

    //     while( ss >> neighbor >> comma >> length)
    //     {
    //         auto tuple = make_tuple(neighbor, length);
    //         heap.push_back(tuple);
    //     }
    //     MinHeap minHeap(heap, heap.size(), heap.size());
    //     graph.push_back(minHeap);
    // }

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
    vector<tuple<int, int>> temp;
    // Since the input file uses 1 based indexing, push a placeholder tuple at index 0 for easier indexing later
    temp.push_back(make_tuple(0, 0));
    graph.push_back(temp);

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
        graph.push_back(temp);
    }

    return graph;
}

// vector<tuple<int, int>> Dijkstra_Algo (vector<MinHeap> graph) 
// {
//     vector<MinHeap> processed;
    
//     vector<MinHeap> toProcess;
    
//     vector<tuple<int, int>> shortest_paths;

//     toProcess.push_back(graph[0]);
//     shortest_paths.push_back(make_tuple(0, 0));



//     // iterator
//     int i = 0;
//     int j = 1;

//     while (i < graph.size())
//     {
//         while (!toProcess[j - 1].empty())
//         {
//         // v is the next vertex to be processed
//         // j_to_v is the length from processed[j] to v
//         auto [v, j_to_v] = toProcess[j - 1].getMin();

//         // Resize the arrays for array indexing    
//         if (v > toProcess.size())
//         {
//             toProcess.resize(v);
//         }
//         if (v > shortest_paths.size())
//         {
//             shortest_paths.resize(v);
//         }
//         // computed_v_len is the shortest length from the first vertex to v
//         int computed_v_len = get<1>(shortest_paths[j - 1]) + j_to_v;

//             // shortest_paths now has the shortest length from the first vertex to v
//         shortest_paths[v - 1] = make_tuple(v, computed_v_len);
        
//         toProcess[j - 1].removemin();
//        }

//        j = v;
//        i++;

//     }

//     return shortest_paths;
    
// }