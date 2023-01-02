#ifndef DELAUNAYTRIANGULATION_H
#define DELAUNAYTRIANGULATION_H

#include "dungeon/map/room/Room.h"
#include "../AlgorithmsHelper.h"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/Graphics/ConvexShape.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <poly2tri/poly2tri.h>
#include <set>

class DelaunayTriangulation
{
public:
    DelaunayTriangulation() = default;

    std::set<Edge>& triangulation(std::list<Room>& rooms);

    void draw(sf::RenderWindow& window);

private:
    void sortRoomsCoordinatesClockwiseOrder(std::list<Room>&);

    void populateLinesVertexArray();

    void populateTrianglesVertexArray(const std::vector<p2t::Triangle*>&);

    sf::Vector2f getAveragedRoomCenter(std::list<Room>&);

    bool isValid(sf::Vector2i point);

    bool cartesianToPolarCoordinates(const Room&, const Room&) const;

    bool areEdgesValid(Edge& first, Edge& second, Edge& third);

    void ifNoEdgesTryAgain(std::list<Room>& rooms);

private:
    /** Triangles (consisting of vertexes) building the current figure. */
    sf::VertexArray delaunayEdges;
    sf::VertexArray triangleLines;
    std::vector<p2t::Point*> polyline;
    std::set<Edge> mTriangleEdges;
};

#endif// DELAUNAYTRIANGULATION_H
