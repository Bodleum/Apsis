#include "apch.h"
#include "Cam.h"
	//#include "Apsis/Utility/Maths.h"
	//	#include <Eigen/Core>
	//	#include <Eigen/Geometry>
	//	#include <Eigen/Dense>

namespace A {

	Cam::Cam()
	{
		AP_PROFILE_FN();
	}

	Cam::Cam(const Eigen::Matrix4f& proj)
		: m_Proj(proj)
	{
		AP_PROFILE_FN();
		RefreshProj();
	}

	void Cam::RefreshTransform()
	{
		AP_PROFILE_FN();
		m_Transform = Eigen::Affine3f::Identity();
		//m_Transform.scale(m_Scale);
		m_Transform.rotate(m_Orientation);
		m_Transform.translate(m_Position);
		RefreshView();
	}

	void Cam::RefreshView()
	{
		AP_PROFILE_FN();
		m_View = m_Transform.inverse();
		RefreshVP();
	}

	void Cam::RefreshProj()
	{
		AP_PROFILE_FN();
		m_Zoom = std::max(m_Zoom, m_MinZoom);	// Clamp zoom
		m_Zoom = std::min(m_Zoom, m_MaxZoom);
		m_Proj = CreateOrthographicProjection(m_Left * 1.0f / m_Zoom, m_Right * 1.0f / m_Zoom, m_Bottom * 1.0f / m_Zoom, m_Top * 1.0f / m_Zoom, m_Near, m_Far);
		RefreshVP();
	}

	void Cam::RefreshVP()
	{
		AP_PROFILE_FN();
		m_VP = m_Proj * m_View;
	}

	OrthoCam::OrthoCam(float left, float right, float bottom, float top, float z_near, float z_far)
	{
		AP_PROFILE_FN();
		m_Left = left;
		m_Right = right;
		m_Bottom = bottom;
		m_Top = top;
		m_Near = z_near;
		m_Far = z_far;
		RefreshProj();
	}

	void OrthoCam::SetProj(float left, float right, float bottom, float top, float z_near, float z_far)
	{
		AP_PROFILE_FN();
		m_Left = left;
		m_Right = right;
		m_Bottom = bottom;
		m_Top = top;
		m_Near = z_near;
		m_Far = z_far;
		RefreshProj();
	}

}