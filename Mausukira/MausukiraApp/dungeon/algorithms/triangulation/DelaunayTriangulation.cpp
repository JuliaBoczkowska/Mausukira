#include "DelaunayTriangulation.h"
#include "../../Debug.h"
#include "SFML/Graphics/ConvexShape.hpp"

static constexpr auto PI = 3.141592653589793238463;


std::set<Edge>& DelaunayTriangulation::triangulation(std::list<Room>& rooms)
{
    delaunayEdges.setPrimitiveType(sf::Triangles);
    triangleLines.setPrimitiveType(sf::Lines);

    sortRoomsCoordinatesClockwiseOrder(rooms);

    shape.setFillColor(sf::Color{ 20, 0, 0, 90 });


    int counter = 0;
    shape.setPointCount(rooms.size());
    for (auto it = rooms.begin(); it != rooms.end(); ++it)
    {
        shape.setPoint(counter, sf::Vector2f{ it->mCenter.x, it->mCenter.y });
        counter++;
        std::cout << it->mCenter.x << "," << it->mCenter.y << std::endl;
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
    sf::Vector2f center{ 0, 0 };
    center.x = x / rooms.size();
    center.y = y / rooms.size();
    return center;
}

void DelaunayTriangulation::sortRoomsCoordinatesClockwiseOrder(std::list<Room>& rooms)
{
    Room::setCenter(getAveragedRoomCenter(rooms));
    rooms.sort(
        [this](Room first, Room second)
        {

            return cartesianToPolarCoordinates(first, second);
        });
}

bool DelaunayTriangulation::cartesianToPolarCoordinates(const Room& a, const Room& b) const
{
//    auto a1 = (static_cast<int>(calculateArcTan(first) * (180.0 / PI)) + 360) % 360;
//    auto a2 = (static_cast<int>(calculateArcTan(second) * (180.0 / PI)) + 360) % 360;
//    return a1 < a2;
    auto center = Room::centerOfAllPoints;

    if (a.mCenter.x >= 0 and b.mCenter.x < 0)
    {
        return true;
    }
    else if (a.mCenter.x == 0 and b.mCenter.x == 0)
    {
        return a.mCenter.y > b.mCenter.y;
    }

    auto det =
        (a.mCenter.x - center.x) * (b.mCenter.y - center.y) - (b.mCenter.x - center.x) * (a.mCenter.y - center.y);
    if (det < 0)
    {
        return true;
    }
    else if (det > 0)
    {
        return false;
    }

    auto d1 = (a.mCenter.x - center.x) * (a.mCenter.x - center.x) + (a.mCenter.y - center.y) * (a.mCenter.y - center.y);
    auto d2 = (b.mCenter.x - center.x) * (b.mCenter.x - center.x) + (b.mCenter.y - center.y) * (b.mCenter.y - center.y);
    return d1 > d2;
}

float DelaunayTriangulation::calculateArcTan(const Room& second) const
{
    return atan2(second.mCenter.x - Room::centerOfAllPoints.x,
        second.mCenter.y - Room::centerOfAllPoints.y);
}

bool DelaunayTriangulation::isValid(sf::Vector2i point)
{
    if (point.x < 0 or point.y < 0)
    {
        return false;
    }
    return true;
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
        if (isValid(sf::Vector2i(triangulatedTriangle->GetPoint(0)->x,
            triangulatedTriangle->GetPoint(0)->y)) and isValid(sf::Vector2i(triangulatedTriangle->GetPoint(1)->x,
            triangulatedTriangle->GetPoint(1)->y)))
        {
            mTriangleEdges.emplace(Edge(sf::Vector2i(triangulatedTriangle->GetPoint(0)->x,
                    triangulatedTriangle->GetPoint(0)->y),
                sf::Vector2i(triangulatedTriangle->GetPoint(1)->x,
                    triangulatedTriangle->GetPoint(1)->y)));
        }
        if (isValid(sf::Vector2i(triangulatedTriangle->GetPoint(1)->x,
            triangulatedTriangle->GetPoint(1)->y)) and
            isValid(sf::Vector2i(triangulatedTriangle->GetPoint(2)->x,
                triangulatedTriangle->GetPoint(2)->y)))
        {

            mTriangleEdges.emplace(Edge(sf::Vector2i(triangulatedTriangle->GetPoint(1)->x,
                    triangulatedTriangle->GetPoint(1)->y),
                sf::Vector2i(triangulatedTriangle->GetPoint(2)->x,
                    triangulatedTriangle->GetPoint(2)->y)));
        }
        if (isValid(sf::Vector2i(triangulatedTriangle->GetPoint(0)->x,
            triangulatedTriangle->GetPoint(0)->y)) and isValid(sf::Vector2i(triangulatedTriangle->GetPoint(2)->x,
            triangulatedTriangle->GetPoint(2)->y)))
        {

            mTriangleEdges.emplace(Edge(sf::Vector2i(triangulatedTriangle->GetPoint(0)->x,
                    triangulatedTriangle->GetPoint(0)->y),
                sf::Vector2i(triangulatedTriangle->GetPoint(2)->x,
                    triangulatedTriangle->GetPoint(2)->y)));
        }


    }

    for (auto& edge: mTriangleEdges)
    {
        if (edge.mVertexA.x < 0 || edge.mVertexA.y < 0 || edge.mVertexB.y < 0, edge.mVertexB.x < 0)
        {
            std::cout << "bad news";
        }
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

void DelaunayTriangulation::draw(sf::RenderWindow& window)
{
#if DEBUG_ROOM_GENERATION
    window.draw(shape);
    window.draw(triangleLines);
#endif
}