#include "apch.h"
#include "Maths.h"
	//#include <Eigen/Core>
	//#include <Eigen/Geometry>
	//#include <Eigen/Dense>

namespace A {

	Eigen::Affine3f CreateOrthographicProjection(float left, float right, float bottom, float top, float z_near, float z_far)
	{
		AP_PROFILE_FN();
		Eigen::Affine3f proj = Eigen::Affine3f::Identity();
		proj(0, 0) = 2 / (right - left);
		proj(1, 1) = 2 / (top - bottom);
		proj(2, 2) = 2 / (z_near - z_far);
		proj(0, 3) = (right + left) / (left - right);
		proj(1, 3) = (top + bottom) / (bottom - top);
		proj(2, 3) = (z_far + z_near) / (z_near - z_far);
		proj(3, 3) = 1;
		return proj;
	}

}