#include "apch.h"
#include "Cam.h"
	//#include <Eigen/Core>
	//#include <Eigen/Geometry>
	//#include <Eigen/Dense>

namespace A {

	Cam::Cam()
	{
		AP_PROFILE_FN();
		Refresh();
	}

	Cam::Cam(const Eigen::Matrix4f& proj)
		: m_Proj(proj)
	{
		AP_PROFILE_FN();
		Refresh();
	}

	void Cam::Refresh()
	{
		m_Transform = Eigen::Affine3f::Identity();
		m_Transform.scale(m_Scale);
		m_Transform.rotate(m_Orientation);
		m_Transform.translate(m_Position);

		m_View = m_Transform.inverse();
		m_VP = m_Proj * m_View;
	}

	OrthoCam::OrthoCam(float left, float right, float bottom, float top, float z_near, float z_far)
	{
		AP_PROFILE_FN();

		Eigen::Matrix4f proj = Eigen::Matrix4f::Zero();
		proj(0, 0) = 2 / (right - left);
		proj(1, 1) = 2 / (top - bottom);
		proj(2, 2) = 2 / (z_near - z_far);
		proj(0, 3) = (right + left) / (left - right);
		proj(1, 3) = (top + bottom) / (bottom - top);
		proj(2, 3) = (z_far + z_near) / (z_near - z_far);
		proj(3, 3) = 1;
		m_Proj = proj;

		Refresh();
	}

}