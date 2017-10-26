#ifndef DIP_MESHPROC_H
#define DIP_MESHPROC_H

#include <Eigen/Dense>

namespace dip {
// Coordinate conversions in 3D space
// Given a triangle with vertices r0, r1, r2 (in Cartesian Coordinate System)
// and a point r (in Cartesian CS), calcualte the barycentric/areal coordinates
// [w, v, u] of the point
// tri matrix has a vertex position in 3d as a row vector.
    Eigen::Vector3f cart2bary(
        const Eigen::Matrix3f &tri,
        const Eigen::Vector3f &point);


    Eigen::Vector3f bary2cart(
        const Eigen::Matrix3f &tri,
        const Eigen::Vector3f &point_bary);
}

#endif //DIP_MESHPROC_H
