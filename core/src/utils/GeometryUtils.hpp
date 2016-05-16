#ifndef UTILS_GEOMETRYUTILS_HPP_DEFINED
#define UTILS_GEOMETRYUTILS_HPP_DEFINED

#include "GeoCoordinate.hpp"
#include "meshing/MeshTypes.hpp"

#include <algorithm>
#include <vector>

namespace utymap { namespace utils {

    // Checks whether geocoordinates are in clockwise oreder
    inline bool isClockwise(const std::vector<utymap::GeoCoordinate>& coordinates)
    {
        auto size = coordinates.size();
        double area = 0.0;
        for (std::size_t p = size - 1, q = 0; q < size; p = q++)
            area += coordinates[p].longitude*coordinates[q].latitude - coordinates[q].longitude*coordinates[p].latitude;
        return area < 0;
    }

    // Gets circle parameters from geocoordinates
    inline void getCircle(const std::vector<utymap::GeoCoordinate>& coordinates, utymap::GeoCoordinate& center, double& radius) 
    {
        auto minMaxLong = std::minmax_element(coordinates.begin(), coordinates.end(),
            [](const utymap::GeoCoordinate& left, const utymap::GeoCoordinate& right) {
                return left.longitude < right.longitude;
        });

        auto minMaxLat = std::minmax_element(coordinates.begin(), coordinates.end(),
            [](const utymap::GeoCoordinate& left, const utymap::GeoCoordinate& right) {
                return left.latitude < right.latitude;
        });

        double centerLon = (minMaxLong.first->longitude + (minMaxLong.second->longitude - minMaxLong.first->longitude) / 2);
        double centerLat = (minMaxLat.first->latitude + (minMaxLat.second->latitude - minMaxLat.first->latitude) / 2);

        radius = (minMaxLat.second->latitude - minMaxLat.first->latitude) / 2;
        center = utymap::GeoCoordinate(centerLat, centerLon);
    }

    // Gets circle parameters from rectangle.
    inline void getCircle(const utymap::meshing::Rectangle& rectangle, utymap::meshing::Vector2& center, double& radius)
    {
        double radiusX = (rectangle.xMax - rectangle.xMin) / 2;
        double radiusY = (rectangle.yMax - rectangle.yMin) / 2;

        double centerX = rectangle.xMin + radiusX;
        double centerY = rectangle.yMin + radiusY;

        radius = radiusY;
        center = utymap::meshing::Vector2(centerX, centerY);
    }

}}

#endif // UTILS_GEOMETRYUTILS_HPP_DEFINED
