#include "apch.h"
#include "Cam.h"

#include <Eigen/Geometry>

namespace A {

	Cam::Cam()
		: m_Proj(Eigen::Matrix4f::Identity()), m_View(Eigen::Matrix4f::Identity()), m_VP(Eigen::Matrix4f::Identity()), m_Transform(Eigen::Matrix4f::Identity()), m_Position(Eigen::Vector3f::Zero())
	{
		AP_PROFILE_FN();
		Refresh();
	}

	Cam::Cam(const Eigen::Matrix4f& proj)
		: m_Proj(proj), m_View(Eigen::Matrix4f::Identity()), m_VP(Eigen::Matrix4f::Identity()), m_Transform(Eigen::Matrix4f::Identity()), m_Position(Eigen::Vector3f::Zero())
	{
		AP_PROFILE_FN();
		Refresh();
	}

	void Cam::Refresh()
	{
		Eigen::Affine3f transform = Eigen::Affine3f::Identity();
		// Scale
		// Rotate
		transform.translate(m_Position);
		m_Transform = transform.matrix();

		m_View = m_Transform.inverse();
		m_VP = m_Proj * m_View;
	}

	OrthoCam::OrthoCam(float left, float right, float bottom, float top, float z_near, float z_far)
	{
		AP_PROFILE_FN();

		m_Proj = Eigen::Matrix4f::Zero();
		m_Proj(0, 0) = 2 / (right - left);
		m_Proj(1, 1) = 2 / (top - bottom);
		m_Proj(2, 2) = 2 / (z_near - z_far);
		m_Proj(0, 3) = (right + left) / (left - right);
		m_Proj(1, 3) = (top + bottom) / (bottom - top);
		m_Proj(2, 3) = (z_far + z_near) / (z_near - z_far);
		m_Proj(3, 3) = 1;

		Refresh();
	}

}