#pragma once
#include <Eigen/Core>

namespace A {

	class Cam
	{
	public:
		inline Cam() : m_Proj(Eigen::Matrix4f::Zero()) {}
		Cam(Eigen::Matrix4f proj);
		virtual ~Cam() = default;

	protected:
		Eigen::Matrix4f m_Proj;
	};


	class OrthoCam : public Cam
	{
	public:
		OrthoCam(float left, float right, float top, float bottom, float z_near, float z_far);
		virtual ~OrthoCam() = default;
	};
}
