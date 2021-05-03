#pragma once
#include <Eigen/Core>

namespace A {

	const Eigen::Vector4f HSVToRGB(const Eigen::Vector4f& hsla) noexcept;
	const Eigen::Vector4f RGBToHSV(const Eigen::Vector4f& rgba) noexcept;

}