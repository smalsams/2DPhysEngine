#pragma once

#include "2dMath.hpp"

namespace seng {
	class rectangle_capsule {
	public:
		rectangle_capsule() {
			topleft_ = vector2<float>(static_cast<float>(0), static_cast<float>(0));
			bottomright_ = vector2<float>(static_cast<float>(0), static_cast<float>(0));
		}

		rectangle_capsule(float x1, float y1, float x2, float y2) {
			topleft_ = vector2(x1, y1);
			bottomright_ = vector2(x2, y2);
		}

		rectangle_capsule(const vector2<float>& first, const vector2<float>& second) {
			topleft_ = first;
			bottomright_ = second;
		}

		/*
		 * @brief Checks if a point is inside the rectangle
		 * @param point The point to check
		 * @return bool
		 */
		bool contains(const vector2<float>& point) const {
			return point.x() >= topleft_.x() && point.x() <= bottomright_.x() && point.y() >= topleft_.y() && point.y() <= bottomright_.y();
		}

		/*
		 * @brief Checks if two rectangles are overlapping
		 * @param first The first rectangle
		 * @param second The second rectangle
		 */
		static bool are_overlapping(const rectangle_capsule& first, const rectangle_capsule& second) {
			return first.get_topleft().x() <= second.get_bottomright().x()
				&& first.get_bottomright().x() >= second.get_topleft().x()
				&& first.get_topleft().y() <= second.get_bottomright().y()
				&& first.get_bottomright().y() >= second.get_topleft().y();
		}

		/*
		 * @brief Gets the size of the rectangle
		 */
		[[nodiscard]] vector2<float> get_size() const
		{
			return bottomright_ - topleft_;
		}

		[[nodiscard]] vector2<float> get_topleft() const { return topleft_; }
		[[nodiscard]] vector2<float> get_bottomright() const { return bottomright_; }
	private:
		vector2<float> topleft_;
		vector2<float> bottomright_;

	};
}
