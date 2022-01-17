#include <iostream>
#include <fstream>
#include <sstream>
#include "MinHeap.h"
#include "MinHeap_2.h"

using namespace std;


vector<vector<tuple<int,int,int>>> buildGraph2 ();

// Build the graph as a vector of MinHeaps
tuple<vector<MinHeap>, int> buildGraph ();

vector<tuple<int,int,int>> init_shortest_paths (int graph_size);

vector<int> Dijkstra_Algo (vector<MinHeap> & graph, int num_edges, ofstream & debugFile);


int main() 
{

    ofstream debugFile;
    debugFile.open("main.dbg", ios_base::in);

    // A vector that contains each vertex and its shortest path from the staring point
    vector<tuple<int,int,int>> shortest_paths_vector;

    auto [graph, num_edges] = buildGraph();

    // Initialize the shortest_paths vector to have the same size as the graph
    shortest_paths_vector = init_shortest_paths(graph.size());

    // Turn the shortest_paths_vector into a minimum heap
    MinHeap paths_heap (shortest_paths_vector, 1, num_edges);

    // auto A = Dijkstra_Algo(graph, paths_heap, debugFile);
    auto A = Dijkstra_Algo(graph, num_edges, debugFile);

    debugFile.close();

    // 7,37,59,82,99,115,133,165,188,197
    cout << A[7] << "," << A[37] << "," << A[59] << "," << A[82] << "," << A[99] << "," <<  A[115] << "," <<  A[133] << "," <<  A[165] << "," <<  A[188] << "," <<  A[197] << endl;

    
    return 0;
    
}

tuple<vector<MinHeap>, int> buildGraph ()
{
    fstream data;
    data.open("Data.txt", ios_base::in);

    string line;
    vector<MinHeap> graph;
    double max_heap_size = 0;

    while(getline(data, line))
    {
        stringstream ss(line);

        int vertex;
        int neighbor;
        char comma;
        int length;

        vector<tuple<int,int,int>> heap;

        ss >> vertex;

        while( ss >> neighbor >> comma >> length)
        {
            auto tuple = make_tuple(vertex, neighbor, length);
            heap.push_back(tuple);
            max_heap_size++;
        }
        MinHeap minHeap(heap, heap.size(), heap.size());
        graph.push_back(minHeap);
    }

    data.close();
    return make_tuple(graph, max_heap_size);
}


vector<tuple<int,int,int>> init_shortest_paths (int graph_size)
{
    vector<tuple<int,int,int>> shortest_paths;

    // Push a placecholder a index zero for easier indexing later
    // shortest_paths.push_back( make_tuple(0, 0) );

    // The starting vertex is 1 and has the length 0
    // shortest_paths.push_back( make_tuple(1, 0));

    // Each element is initialize to -1 to represent positive infinity.
    // Since Dijkstra's algorithm does not work on negative edge lengths & all input edge are positive, it's safe to use -1 here.
    // for (int i = 1; i < graph_size; i++)
    // {   
    //     shortest_paths.push_back( make_tuple(i, -1) );
    // }

    // shortest_paths.push_back(make_tuple(1, 0));
    
    shortest_paths.resize(graph_size);

    // shortest_paths[0] = make_tuple(1, 1, 0);

    shortest_paths[0] = make_tuple(0, 1, 0);

    return shortest_paths;
}


vector<int> Dijkstra_Algo (vector<MinHeap> & graph, int num_edges, ofstream & debugFile)
{

    MinHeap2 heap(num_edges);
    vector<int> A;
    A.resize(graph.size() + 1, -1);
    A[0] = 0;
    A[1] = 0;

    heap.insert(make_tuple(0, 0));
    heap.insert(make_tuple(1, 0));

    vector<bool> processed;
    processed.resize(graph.size(), false);

    int i = 0; 

    while(i < num_edges)
    {
        auto [v, v_len] = heap.getMin();

        if (!processed[v])
        {
            processed[v] = true;

            vector<tuple<int,int,int>> v_neighbors = graph[v - 1].getHeap();

            for (auto each : v_neighbors)
            {
                int w = get<1>(each);
                int w_len = get<2>(each);



                if (((v_len + w_len) < A[w]) || (A[w] == -1) )
                {
                    A[w] = v_len + w_len;
                }

                if (!processed[w])
                {
                    heap.insert(make_tuple(w, A[w]));
                }
            }
        }

        heap.removemin();

        i++;
    }

    return A;
}
