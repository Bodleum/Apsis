#pragma once
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/Dense>

namespace A {

	class Cam
	{
	public:
		Cam();
		Cam(const Eigen::Matrix4f& proj);
		virtual ~Cam() = default;

		inline const Eigen::Affine3f GetProj() const { return m_Proj; }
		inline const Eigen::Affine3f GetView() const { return m_View; }
		inline const Eigen::Affine3f GetVP() const { return m_VP; }
		inline const Eigen::Affine3f GetTransform() const { return m_Transform; }

		inline const Eigen::Matrix4f GetProjMatrix() const { return m_Proj.matrix(); }
		inline const Eigen::Matrix4f GetViewMatrix() const { return m_View.matrix(); }
		inline const Eigen::Matrix4f GetVPMatrix() const { return m_VP.matrix(); }
		inline const Eigen::Matrix4f GetTransformMatrix() const { return m_Transform.matrix(); }
		inline const Eigen::Vector3f GetPositionMatrix() const { return m_Position; }

		inline void SetScale(float scale) { m_Scale = scale; Refresh(); }
		inline void SetRotation(float angle) { m_Rotation = Eigen::AngleAxisf(3.1415f * angle / 180.0f, Eigen::Vector3f::UnitZ()); Refresh(); }
		inline void Rotate(float angle) { m_Rotation *= Eigen::Quaternionf(Eigen::AngleAxisf(3.1415f * angle / 180.0f, Eigen::Vector3f::UnitZ())); Refresh(); }
		inline void SetPosition(const Eigen::Vector3f& position) { m_Position = position; Refresh(); }

	protected:
		void Refresh();

		Eigen::Affine3f m_Proj = Eigen::Affine3f::Identity();
		Eigen::Affine3f m_View = Eigen::Affine3f::Identity();
		Eigen::Affine3f m_VP = Eigen::Affine3f::Identity();
		Eigen::Affine3f m_Transform = Eigen::Affine3f::Identity();

		float m_Scale = 1.0f;
		Eigen::Quaternionf m_Rotation = Eigen::Quaternionf::Identity();
		Eigen::Vector3f m_Position = Eigen::Vector3f::Zero();
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
