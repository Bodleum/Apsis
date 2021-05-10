#include "apch.h"
#include "Cam.h"

namespace A {

	Cam::Cam(const Eigen::Matrix4f& proj)
		: m_Proj(proj)
	{
	}

	OrthoCam::OrthoCam(float left, float right, float top, float bottom, float z_near, float z_far)
	{
		AP_PROFILE_FN();

		m_Proj = Eigen::Matrix4f::Zero();
		m_Proj(0, 0) = 2 / (right - left);
		m_Proj(1, 1) = 2 / (top - bottom);
		m_Proj(2, 2) = -1 * 2 / (z_far - z_near);
		m_Proj(0, 3) = -1 * (right + left) / (right - left);
		m_Proj(1, 3) = -1 * (top + bottom) / (top - bottom);
		m_Proj(2, 3) = -1 * (z_far + z_near) / (z_far - z_near);
		m_Proj(3, 3) = 1;
	}

}