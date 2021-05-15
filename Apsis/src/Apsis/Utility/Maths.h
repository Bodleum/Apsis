#pragma once
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/Dense>

namespace A {

	Eigen::Affine3f CreateOrthographicProjection(float left, float right, float bottom, float top, float z_near, float z_far);

}
