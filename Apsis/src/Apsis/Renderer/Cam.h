#pragma once
#include <Eigen/Core>

namespace A {

	class Cam
	{
	public:
		Cam();
		Cam(const Eigen::Matrix4f& proj);
		virtual ~Cam() = default;

		inline const Eigen::Matrix4f GetProj() const { return m_Proj; }
		inline const Eigen::Matrix4f GetView() const { return m_View; }
		inline const Eigen::Matrix4f GetVP() const { return m_VP; }
		inline const Eigen::Matrix4f GetTransform() const { return m_Transform; }
		inline const Eigen::Vector3f GetPosition() const { return m_Position; }

		inline void SetPosition(const Eigen::Vector3f& position) { m_Position = position; Refresh(); }

	protected:
		void Refresh();

		Eigen::Matrix4f m_Proj;
		Eigen::Matrix4f m_View;
		Eigen::Matrix4f m_VP;
		Eigen::Matrix4f m_Transform;

		Eigen::Vector3f m_Position;
		// TODO: Add rotations -> Quaternions?
	};


	class OrthoCam : public Cam
	{
	public:
		OrthoCam(float left, float right, float bottom, float top, float z_near, float z_far);
		virtual ~OrthoCam() = default;
	};

	typedef enum class CamType : unsigned short
	{
		Ortho
	};
}
