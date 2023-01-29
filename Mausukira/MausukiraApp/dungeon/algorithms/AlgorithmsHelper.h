#ifndef ALGORITHMSHELPER_H
#define ALGORITHMSHELPER_H

#include "SFML/System/Vector2.hpp"
#include <cmath>

struct Vertex
{
    Vertex(sf::Vector2i coord)
        : x(coord.x)
        , y(coord.y)
    {
    }

    bool operator==(const Vertex& other) const
    {
        return (x == other.x) && (y == other.y);
    }

    bool operator<(const Vertex& other) const
    {
        return (this->x < other.x) || ((this->x == other.x) && (this->y < other.y));
    }

    int x;
    int y;
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
    float measureDistance(const sf::Vector2i& vertexA, const sf::Vector2i& vertexB)
    {
        return sqrt(pow(vertexB.x - vertexA.x, 2) + pow(vertexB.y - vertexA.y, 2) * 1.0);
    }

    Edge(const sf::Vector2i& vertexA, const sf::Vector2i& vertexB)
        : mVertexA(vertexA)
        , mVertexB(vertexB)
    {
        mDistance = measureDistance(vertexA, vertexB);
    }

    Edge() = default;

    bool operator()(Edge first, Edge second)
    {
        return (first.mVertexA == second.mVertexA);
    }

    Edge& operator=(const Edge& other) const
    {
        return const_cast<Edge&>(*this);
    }

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

    sf::Vector2i mVertexA;
    sf::Vector2i mVertexB;
    float mDistance{0};
};
#endif// ALGORITHMSHELPER_H
