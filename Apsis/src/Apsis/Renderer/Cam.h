#pragma once
#include "Apsis/Utility/Maths.h"
	//#include <Eigen/Core>
	//#include <Eigen/Geometry>
	//#include <Eigen/Dense>

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
		inline const float GetZoom() const { return m_Zoom; }
		inline const Eigen::Quaternionf GetOrientation() const { return m_Orientation; }
		inline const Eigen::Vector3f GetPosition() const { return m_Position; }

		inline void SetZoom(float zoom) { m_Zoom = zoom; RefreshProj(); }
		inline void SetMinZoom(float min_zoom) { m_MinZoom = min_zoom; }
		inline void SetMaxZoom(float max_zoom) { m_MaxZoom = max_zoom; }
		inline void Zoom(float zoom) { m_Zoom += zoom; RefreshProj(); }
		inline void SetOrientation(float angle) { m_Orientation = Eigen::AngleAxisf(3.1415f * angle / 180.0f, Eigen::Vector3f::UnitZ()); RefreshTransform(); }
		inline void Rotate(float angle) { m_Orientation *= Eigen::Quaternionf(Eigen::AngleAxisf(3.1415f * angle / 180.0f, Eigen::Vector3f::UnitZ())); RefreshTransform(); }
		inline void SetPosition(const Eigen::Vector3f& position) { m_Position = position; RefreshTransform(); }
		inline void Move(const Eigen::Vector3f& movement) { m_Position += movement; RefreshTransform(); }

		virtual void SetProj(float left, float right, float bottom, float top, float z_near, float z_far) = 0;

	protected:
		void RefreshTransform();
		void RefreshView();
		void RefreshProj();
		void RefreshVP();

		Eigen::Affine3f m_Proj = Eigen::Affine3f::Identity();
		Eigen::Affine3f m_View = Eigen::Affine3f::Identity();
		Eigen::Affine3f m_VP = Eigen::Affine3f::Identity();
		Eigen::Affine3f m_Transform = Eigen::Affine3f::Identity();

		float m_Zoom = 1.0f;
		float m_MinZoom = 0.1f;
		float m_MaxZoom = 10.0f;
		Eigen::Quaternionf m_Orientation = Eigen::Quaternionf::Identity();
		Eigen::Vector3f m_Position = Eigen::Vector3f::Zero();

		float m_Left = 1.0f;
		float m_Right = -1.0f;
		float m_Bottom = 1.0f;
		float m_Top = -1.0f;
		float m_Near = 1.0f;
		float m_Far = -1.0f;
	};


	class OrthoCam : public Cam
	{
	public:
		OrthoCam(float left, float right, float bottom, float top, float z_near, float z_far);
		virtual ~OrthoCam() = default;

		// Inherited via Cam
		virtual void SetProj(float left, float right, float bottom, float top, float z_near, float z_far) override;
	};

	enum class CamType : unsigned short
	{
		Ortho
	};
}
