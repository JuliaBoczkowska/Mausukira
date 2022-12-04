#ifndef DELAUNAYTRIANGULATION_H
#define DELAUNAYTRIANGULATION_H
#include "../../map/Room.h"
#include "../AlgorithmsHelper.h"
#include "SFML/Graphics/VertexArray.hpp"
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
    float calculateArcTan(const Room&) const;
    void cartesianToPolarCoordinates(const Room&, const Room&, double&, double&) const;

private:
    /** Triangles (consisting of vertexes) building the current figure. */
    sf::VertexArray delaunayEdges;
    sf::VertexArray triangleLines;
    std::vector<p2t::Point*> polyline;
    std::set<Edge> mTriangleEdges;
    ;
};
#endif// DELAUNAYTRIANGULATION_H
