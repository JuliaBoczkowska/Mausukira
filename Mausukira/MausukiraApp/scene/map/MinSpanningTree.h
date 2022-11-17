#ifndef MINSPANNINGTREE_H
#define MINSPANNINGTREE_H


#include "SFML/System/Vector2.hpp"
#include <vector>


class Vertex : public sf::Vector2f
{
public:
    Vertex(float x, float y)
        : sf::Vector2f(x, y)
    {

    }

    explicit Vertex(sf::Vector2f x)
        : sf::Vector2f(x)
    {

    }

    bool operator<(const Vertex& other) const
    {
        return (this->x < other.x) || ((this->x == other.x) && (this->y < other.y));
    }
};

class Edge
{
public:
    /**
     * @brief Measure distance between two vertices.
     * @param vertexA First vertex.
     * @param vertexB Second vertex.
     * @return measured Distance.
     */
    float measureDistance(const sf::Vector2f& vertexA, const sf::Vector2f& vertexB)
    {
        return sqrt(pow(vertexB.x - vertexA.x, 2) + pow(vertexB.y - vertexA.y, 2) * 1.0);
    }

    Edge(const sf::Vector2f& vertexA, const sf::Vector2f& vertexB)
        : mVertexA(vertexA)
        , mVertexB(vertexB)
    {
        mDistance = measureDistance(vertexA, vertexB);
    }

    Edge() = default;

    Edge& operator=(const Edge& other)
    {
        mVertexA = other.mVertexA;
        mVertexB = other.mVertexB;
        mDistance = other.mDistance;

        return *this;
    }

    Edge(const Edge& other)
    {
        mVertexA = other.mVertexA;
        mVertexB = other.mVertexB;
        mDistance = other.mDistance;
    }

    bool operator<(const Edge& other) const
    {
        return this->mDistance < other.mDistance;
    }

    sf::Vector2f mVertexA;
    sf::Vector2f mVertexB;
    float mDistance{ 0 };
};

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
