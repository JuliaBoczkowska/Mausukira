#include "DelaunayTriangulation.h"

static constexpr auto PI = 3.141592653589793238463;


std::set<Edge>& DelaunayTriangulation::triangulation(std::list<Room>& rooms)
{
    delaunayEdges.setPrimitiveType(sf::Triangles);
    triangleLines.setPrimitiveType(sf::Lines);

    sortRoomsCoordinatesClockwiseOrder(rooms);

    std::list<Room>::iterator it;
    for (it = rooms.begin(); it != rooms.end(); ++it)
    {
        polyline.push_back(new p2t::Point(it->mCenter.x, it->mCenter.y));
    }

    p2t::CDT cdt(polyline);
    cdt.Triangulate();
    const auto triangulatedFigure = cdt.GetTriangles();

    delaunayEdges.resize(triangulatedFigure.size() * 3);
    triangleLines.resize(triangulatedFigure.size() * 3 * 3);

    populateTrianglesVertexArray(triangulatedFigure);
    populateLinesVertexArray();
    return mTriangleEdges;
}

sf::Vector2f DelaunayTriangulation::getAveragedRoomCenter(std::list<Room>& rooms)
{
    int x = 0;
    int y = 0;
    for (auto room: rooms)
    {
        x += room.mCenter.x;
        y += room.mCenter.y;
    }
    sf::Vector2f center{0, 0};
    center.x = x / rooms.size();
    center.y = y / rooms.size();
    return center;
}

void DelaunayTriangulation::sortRoomsCoordinatesClockwiseOrder(std::list<Room>& rooms)
{
    Room::setCenter(getAveragedRoomCenter(rooms));
    rooms.sort(
        [](Room first, Room second)
        {
            double a1 = (static_cast<int>(atan2(first.mCenter.x - Room::centerOfAllPoints.x,
                                                first.mCenter.y - Room::centerOfAllPoints.y) *
                                          (180.0 / PI)) +
                         360) %
                        360;
            double a2 = (static_cast<int>(atan2(second.mCenter.x - Room::centerOfAllPoints.x,
                                                second.mCenter.y - Room::centerOfAllPoints.y) *
                                          (180.0 / PI)) +
                         360) %
                        360;
            return a1 < a2;
        });
}

void DelaunayTriangulation::populateLinesVertexArray()
{
    for (int arrayIndex = 0, vertexIndex = 0; vertexIndex < delaunayEdges.getVertexCount();)
    {
        auto first = vertexIndex;
        auto second = vertexIndex + 1;
        auto third = vertexIndex + 2;
        vertexIndex = vertexIndex + 3;

        // 1 -> 2 triangle edge
        triangleLines[arrayIndex] = sf::Vertex(
            sf::Vector2f(delaunayEdges[first].position.x, delaunayEdges[first].position.y));
        triangleLines[++arrayIndex] = sf::Vertex(
            sf::Vector2f(delaunayEdges[second].position.x, delaunayEdges[second].position.y));

        // 1 -> 3 triangle edge
        triangleLines[++arrayIndex] = sf::Vertex(
            sf::Vector2f(delaunayEdges[first].position.x, delaunayEdges[first].position.y));
        triangleLines[++arrayIndex] = sf::Vertex(
            sf::Vector2f(delaunayEdges[third].position.x, delaunayEdges[third].position.y));

        // 2 -> 3 triangle edge
        triangleLines[++arrayIndex] = sf::Vertex(
            sf::Vector2f(delaunayEdges[second].position.x, delaunayEdges[second].position.y));
        triangleLines[++arrayIndex] = sf::Vertex(
            sf::Vector2f(delaunayEdges[third].position.x, delaunayEdges[third].position.y));
        ++arrayIndex;
    }

    for (int arrayIndex = 0; arrayIndex < triangleLines.getVertexCount(); ++arrayIndex)
    {
        triangleLines[arrayIndex].color = sf::Color::Green;
    }
}

void DelaunayTriangulation::populateTrianglesVertexArray(
    const std::vector<p2t::Triangle*>& triangulatedFigure)
{

    for (auto* triangulatedTriangle: triangulatedFigure)
    {
        mTriangleEdges.emplace(Edge(sf::Vector2i(triangulatedTriangle->GetPoint(0)->x,
                                                 triangulatedTriangle->GetPoint(0)->y),
                                    sf::Vector2i(triangulatedTriangle->GetPoint(1)->x,
                                                 triangulatedTriangle->GetPoint(1)->y)));

        mTriangleEdges.emplace(Edge(sf::Vector2i(triangulatedTriangle->GetPoint(1)->x,
                                                 triangulatedTriangle->GetPoint(1)->y),
                                    sf::Vector2i(triangulatedTriangle->GetPoint(2)->x,
                                                 triangulatedTriangle->GetPoint(2)->y)));

        mTriangleEdges.emplace(Edge(sf::Vector2i(triangulatedTriangle->GetPoint(0)->x,
                                                 triangulatedTriangle->GetPoint(0)->y),
                                    sf::Vector2i(triangulatedTriangle->GetPoint(2)->x,
                                                 triangulatedTriangle->GetPoint(2)->y)));
    }

    size_t arrayIndex = 0;
    for (auto* triangulatedTriangle: triangulatedFigure)
    {
        for (size_t vertexIndex = 0; vertexIndex < 3; ++vertexIndex)
        {
            delaunayEdges[arrayIndex] =
                sf::Vertex(sf::Vector2f(triangulatedTriangle->GetPoint(vertexIndex)->x,
                                        triangulatedTriangle->GetPoint(vertexIndex)->y));
            ++arrayIndex;
        }
    }
}

void DelaunayTriangulation::draw(sf::RenderWindow* window)
{
    window->draw(triangleLines);
}