#ifndef MINSPANNINGTREE_H
#define MINSPANNINGTREE_H


#include "MinimumSpanningTreeHelper.h"
#include <vector>

class MinSpanningTree
{
public:
    MinSpanningTree() = default;

    static std::vector<Edge> processMST(std::vector<Edge> edges)
    {
        std::set<Vertex> openSet;
        std::set<Vertex> closedSet;

        closedSet.emplace(Vertex(edges.at(0).mVertexA));

        std::vector<Edge> result;
        float minimumDistance;

        for (auto edge: edges)
        {
            openSet.emplace(edge.mVertexA);
            openSet.emplace(edge.mVertexB);
        }

        while (openSet.size() > 0)
        {
            bool selected = 0;
            Edge selectedEdge;
            minimumDistance = 999;

            for (auto edge: edges)
            {
                int closedVertices = 0;

                if (!closedSet.contains(Vertex(edge.mVertexA)))
                {
                    ++closedVertices;
                }
                if (!closedSet.contains(Vertex(edge.mVertexB)))
                {
                    ++closedVertices;
                }
                if (closedVertices != 1)
                {
                    continue;
                }

                if (edge.mDistance < minimumDistance)
                {
                    selectedEdge = edge;
                    selected = true;
                    minimumDistance = edge.mDistance;
                }
            }
            if (!selected)
            {
                break;
            }
            result.push_back(selectedEdge);
            openSet.erase(Vertex(selectedEdge.mVertexA));
            openSet.erase(Vertex(selectedEdge.mVertexB));
            closedSet.emplace(Vertex(selectedEdge.mVertexA));
            closedSet.emplace(Vertex(selectedEdge.mVertexB));
        }
        return result;
    }
};

#endif //MINSPANNINGTREE_H
