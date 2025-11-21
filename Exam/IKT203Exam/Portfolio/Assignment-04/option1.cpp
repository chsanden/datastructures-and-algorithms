#include "option1.h"
#include <iostream>
#include "SharedLib.h"
#include <algorithm>

constexpr float INF = 1e9f;

// Global graph storage and lookup table used by the ReadGraph callbacks.
// These are populated automatically when readGraphFromFile(...) is executed.
Graph g;
std::unordered_map<std::string, int> nameToIndex;
std::string filename = "DATA/network_graph.txt"; // Remember to set working directory for this path to work

//////////////////////////////// Callbacks ////////////////////////////////
// Callback: called once for each node read from network_graph.txt.
// Responsible for registering the vertex in the graph and recording its index.

bool onNodeRead(const int aIndex, const int aTotalCount, const std::string& aNode)
{
    const int idx = g.AddVertex(aNode);
    nameToIndex[aNode] = idx;
    return true;
}

// Callback: called for each edge (connection) read from the file.
// Translates node names into vertex indices and adds an undirected weighted edge.
bool onEdgeRead(const int aIndex, const int aTotalCount, const std::string& aFromNode, const std::string& aToNode, const float aWeight)
{
    const int fromIdx = nameToIndex[aFromNode];
    const int toIdx = nameToIndex[aToNode];

    g.AddUndirectedEdge(fromIdx, toIdx, aWeight);
    return true;
}

//////////////////////////////// Dijkstra algorithm ////////////////////////////////
// Computes the shortest path between src and dst using Dijkstra's algorithm.
// Uses the custom MinHeap class as the priority queue.
// Output: 'outPath' contains vertex indices from src -> dst in order.
// Returns INF if no path exists.
float Dijkstra(const Graph& graph, int src, int dst, std::vector<int>& outPath)
{
    const int n = graph.GetVertexCount();

    std::vector<float> dist(n, INF);
    std::vector<int> prev(n, -1);
    std::vector<bool> visited(n, false);

    dist[src] = 0.0f;

    MinHeap heap;
    heap.Push(src, 0.0f);

    // Pop the next closest unvisited vertex. Old entries with outdated distances
    // are skipped via the 'visited' array (lazy deletion).
    while (!heap.isEmpty()) {
        HeapNode* node = heap.Pop();
        const int u = node->vertex;
        // float d = node->distance;    not needed
        delete node;

        if (visited[u])
            continue;
        visited[u] = true;
        if (u == dst)
            break;

        for (const TEdge* e : graph.GetEdges(u)) {
            int v = e->toIndex;
            float w = e->weight;

            if (visited[v])
                continue;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                heap.Push(v, dist[v]);
            }
        }
    }

    outPath.clear();
    if (dist[dst] == INF)
        return INF;
    for (int v = dst; v != -1; v = prev[v])
        outPath.push_back(v);
    std::reverse(outPath.begin(), outPath.end());
    return dist[dst];
}

//////////////////////////////// Class logic ////////////////////////////////
// Graph
// Clean up all dynamically allocated vertices and edges.
// Graph owns all TVertex* and TEdge*.
Graph::~Graph()
{
    for (TVertex* v : vertices) {
        for (TEdge* e : v->edges) {
            delete e;
        }
        delete v;
    }
}

int Graph::AddVertex(const std::string& name)
{
    auto* v = new TVertex;
    v->name = name;
    vertices.push_back(v);
    return static_cast<int>(vertices.size()) - 1;
}

void Graph::AddUndirectedEdge(int fromIndex, int toIndex, float weight)
{
    TEdge* e1 = new TEdge;
    e1->toIndex = toIndex;
    e1->weight = weight;

    TEdge* e2 = new TEdge;
    e2->toIndex = fromIndex;
    e2->weight = weight;

    vertices[fromIndex]->edges.push_back(e1);
    vertices[toIndex]->edges.push_back(e2);
}

int Graph::GetVertexCount() const
{
    return static_cast<int>(vertices.size());
}

const TVertex *Graph::GetVertex(int index) const
{
    return vertices[index];
}

const std::vector<TEdge*>& Graph::GetEdges(const int index) const
{
    return vertices[index]->edges;
}

// Heap
// Min-heap storing (vertex, distance) pairs.
// Used by Dijkstra as a priority queue.
MinHeap::~MinHeap()
{
    for (HeapNode* n : data)
        delete n;
}

bool MinHeap::isEmpty() const
{
    return data.empty();
}

void MinHeap::Push(int vertex, float dist)
{
    auto* n = new HeapNode{vertex, dist};
    data.push_back(n);
    HeapUp(static_cast<int>(data.size()) - 1);
}

HeapNode* MinHeap::Pop()
{
    if (data.empty())
        return nullptr;

    HeapNode* root = data[0];
    data[0] = data.back();
    data.pop_back();
    if (!data.empty())
        HeapDown(0);
    return root;
}

void MinHeap::HeapUp(int idx)
{
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (data[parent]->distance <= data[idx]->distance)
            break;
        std::swap(data[idx], data[parent]);
        idx = parent;
    }
}

void MinHeap::HeapDown(int idx)
{
    int n = static_cast<int>(data.size());

    while (true) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = idx;

        if (left < n && data[left]->distance < data[smallest]->distance)
            smallest = left;
        if (right < n && data[right]->distance < data[smallest]->distance)
            smallest = right;

        if (smallest == idx)
            break;
        std::swap(data[idx], data[smallest]);
        idx = smallest;
    }
}


// Entry point for Assignment 04 Option 1.
// Loads the network graph from file, prints node list,
// prompts the user for source and destination,
// and runs Dijkstra to find the lowest-latency path.
int RunApp() {

    readGraphFromFile(filename, onNodeRead, onEdgeRead);

    // Debug: Print all nodes and vertices
    /*
    pack("Graph");
    for (int i = 0; i < g.GetVertexCount(); i++) {
        const TVertex* v = g.GetVertex(i);
        std::cout << i << ": " << v->name << std::endl;
        for (const TEdge* e : g.GetEdges(i)) {
            std::cout << "  -> " << e->toIndex << " (weight = " << e->weight << ")" << std::endl;
        }
    }
    */
    /* Debug heap test
    pack("Heap");
    MinHeap test;
    test.Push(1, 5.0f);
    test.Push(2, 3.0f);
    test.Push(3, 10.0f);
    while (!test.isEmpty())
    {
        const HeapNode* n = test.Pop();
        std::cout << "(" << n->vertex << ", " << n->distance << ")" << "\n";
        delete n;
    }
    printline();
    */

    std::cout << "\nGraph:" << std::endl;
    for (int i = 0; i < g.GetVertexCount(); ++i)
        std::cout << i << ": " << g.GetVertex(i)->name << std::endl;

    int src, dst;
    std::cout << "\nEnter source index: ";
    std::cin >> src;
    std::cout << "\nEnter destination index: ";
    std::cin >> dst;
    if (src < 0 || src >= g.GetVertexCount() ||
    dst < 0 || dst >= g.GetVertexCount()) {
        std::cout << "Invalid indices.\n";
        return 0;
    }

    std::vector<int> path;
    float total = Dijkstra(g, src, dst, path);

    if (total >= INF) {
        std::cout << "\nNo path between those nodes.\n";
    } else {
        std::cout << "\nLowest latency path: ";
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << g.GetVertex(path[i])->name;
            if (i + 1 < path.size()) std::cout << " -> ";
        }
        std::cout << " \n(Total: " << total << " ms)\n";
    }
    printline();

	return 0;
}