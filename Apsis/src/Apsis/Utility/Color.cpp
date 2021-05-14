#include "apch.h"
#include "Color.h"
	//#include <Eigen/Core>

namespace A {

	static const float HSVToRGBHelper(float n, const Eigen::Vector4f& hsva)
	{
		AP_PROFILE_FN();
		float k = fmod(n + (hsva.x() * 360.0f), 6);
		return hsva.z() - hsva.z() * hsva.y() * std::max(std::min(std::min(k, 4 - k), 1.0f), 0.0f);
	}

	const Eigen::Vector4f HSVToRGB(const Eigen::Vector4f& hsva) noexcept
	{
		AP_PROFILE_FN();
		return Eigen::Vector4f(HSVToRGBHelper(5, hsva), HSVToRGBHelper(3, hsva), HSVToRGBHelper(1, hsva), hsva.w());
	}

	const Eigen::Vector4f RGBToHSV(const Eigen::Vector4f& rgba) noexcept
	{
		float V = std::max(std::max(rgba.x(), rgba.y()), rgba.z());
		float C = V - std::min(std::min(rgba.x(), rgba.y()), rgba.z());

		float h = 0;
		if (V == rgba.x())
			h = (rgba.y() - rgba.z()) / C;
		else if (V == rgba.y())
			h = 2 + (rgba.z() - rgba.x()) / C;
		else if (V == rgba.z())
			h = 4 + (rgba.x() - rgba.y()) / C;

		return Eigen::Vector4f(h, V == 0 ? 0 : C / V, V, rgba.w());
	}

}