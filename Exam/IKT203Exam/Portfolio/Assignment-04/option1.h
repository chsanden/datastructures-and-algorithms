#pragma once

#ifndef OPTION1_H
#define OPTION1_H
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// Structs and classes
struct TEdge {
    int toIndex;
    float weight;
};

struct TVertex {
    std::string name;
    std::vector<TEdge*> edges;
};

struct HeapNode {
    int vertex;
    float distance;
};

class MinHeap {
private:
    std::vector<HeapNode*> data;

    void HeapUp(int idx);
    void HeapDown(int idx);

public:
    ~MinHeap();

    [[nodiscard]] bool isEmpty() const;
    void Push(int vertex, float dist);
    HeapNode* Pop();

};

class Graph {
private:
    std::vector<TVertex*> vertices;     // Owns all TVertex*

public:
    ~Graph();

    int AddVertex(const std::string& name);
    void AddUndirectedEdge(int fromIndex, int toIndex, float weight);

    [[nodiscard]] int GetVertexCount() const;
    [[nodiscard]] const TVertex* GetVertex(int index) const;
    [[nodiscard]] const std::vector<TEdge*>& GetEdges(int index) const;
};

// Callbacks & funcs
bool onNodeRead(int aIndex, int aTotalCount, const std::string& aNode);
bool onEdgeRead(int aIndex, int aTotalCount, std::string& aFromNode, std::string& aToNode, float aWeight);

float Dijkstra(const Graph& graph, int src, int dst, std::vector<int>& outPath);

// Terminal tidying
inline void printline()
{
    std::cout << "----------------------------------------" << std::endl;
}

inline void pack(const std::string& line)
{
    std::cout << "\n\n\n" << std::endl;
    printline();
    std::cout << line << std::endl;
    printline();
}





int RunApp();


#endif // OPTION1_H
