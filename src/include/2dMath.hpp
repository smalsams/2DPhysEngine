#pragma once
#ifndef MATH2D_HPP
#define MATH2D_HPP
#include <algorithm>
#include <cmath>
#include <type_traits>

namespace seng {

	/*
	 * @brief A 2D vector class with x and y components
	 * @tparam T the type of the components
	 */
	template <typename T>
	class vector2 {
		T x_, y_;
	public:
		vector2() = default;
		vector2(const T x, const T y) : x_(x), y_(y) {}

		/*
		 * @brief Gets the x component of the vector
		 */
		[[nodiscard]] T x() const { return x_; }

		/*
		 * @brief Gets the y component of the vector
		 */
		[[nodiscard]] T y() const { return y_; }

		/*
		 * @brief Gets the squared magnitude of the vector
		 *
		 */
		[[nodiscard]] T magnitude_squared() const { return x_ * x_ + y_ * y_; }

		/*
		 * @brief Sets the x component of the vector
		 */
		void set_x(const T x) { x_ = x; }

		/*
		 * @brief Sets the y component of the vector
		 */
		void set_y(const T y) { y_ = y; }

		/*
		 * @brief Sets the x and y components of the vector
		 */
		void set(const T x, const float y) { x_ = x; y_ = y; }
		vector2 operator+(const vector2& other) const { return { x_ + other.x_, y_ + other.y_ }; }
		vector2 operator-(const vector2& other) const { return { x_ - other.x_, y_ - other.y_ }; }
		vector2 operator*(const T scalar) const { return { x_ * scalar, y_ * scalar }; }
		void operator+=(const vector2& other) { x_ += other.x_; y_ += other.y_; }
		void operator-=(const vector2& other) { x_ -= other.x_; y_ -= other.y_; }
		void operator*=(const T scalar) { x_ *= scalar; y_ *= scalar; }
		vector2 operator-() { return { -x_, -y_ }; }
		vector2 operator+() { return { x_, y_}; }
		vector2 operator/(const T scalar) const { return { x_ / scalar, y_ / scalar }; }

		/*
		 * @brief Calculates the dot product of this vector and another
		 */
		[[nodiscard]] T dot(const vector2& other) const { return x_ * other.x_ + y_ * other.y_; }

		/*
		 * @brief Static method to calculate the dot product of two vectors
		 */
		static T dot(const vector2& a, const vector2& b) { return a.x() * b.x() + a.y()* b.y(); }

		/*
		 * @brief Calculates the dot product of this vector and another, but with the y component negated
		 */
		[[nodiscard]] T y_neg_dot(const vector2& other) const { return x_ * other.x_ - y_ * other.y_; }

		/*
		 * @brief Static method to calculate the dot product of two vectors, but with the y component negated
		 */
		static T y_neg_dot(const vector2& a, const vector2& b) { return a.x() * b.x() - a.y() * b.y(); }

		/*
		 * @brief Calculates the cross product of this vector and another
		 */
		[[nodiscard]] T cross(const vector2& other) const { return x_ * other.y_ - y_ * other.x_; }


		/*
		 * @brief Static method to calculate the cross product of two vectors
		 */
		[[nodiscard]] vector2 normalized() const {
			if (x_ == 0 && y_ == 0) return { 0, 0 };
			const T mag = sqrt(magnitude_squared());
			return { x_ / mag, y_ / mag };
		}

		/*
		 * @brief Calculates the magnitude of the vector
		 */
		[[nodiscard]] float magnitude() const
		{
			return std::sqrt(magnitude_squared());
		}

		/*
		 * @brief calculates the floor for both components of the vector
		 * @tparam U the type of the components
		 * @return a vector2 with the floor of the components
		 * @note this function is only available for floating point types
		 */
		template <typename U = T,
			typename = std::enable_if_t<std::is_floating_point_v<U>>>
		vector2<int> floor()
		{
			return { static_cast<int>(std::floor(x())), static_cast<int>(std::floor(y())) };
		}

		/*
		 * @brief calculates the absolute value for both components of the vector
		 * @tparam U the type of the components
		 * @return a vector2 with the absolute value of the components
		 * @note this function is only available for floating point types
		 */
		template <typename U = T,
			typename = std::enable_if_t<std::is_floating_point_v<U>>>
		vector2<U> fabs() const
		{
			return { std::fabs(x()), std::fabs(y()) };
		}

		[[nodiscard]] vector2 to_normal()
		{
			return { -this.y(), this.x() };
		}

		bool operator==(const vector2& other) const { return x_ == other.x_ && y_ == other.y_; }
		bool operator!=(const vector2& other) const { return x_ != other.x_ || y_ != other.y_; }

		friend vector2 operator*(const T scalar, const vector2& vec) { return vec * scalar; }
	};

	template <typename T>
	class matrix22 {
	private:
		T m00_, m01_, m10_, m11_;
	public:
		matrix22(const T m00, const T m01, const T m10, const T m11) : m00_(m00), m01_(m01), m10_(m10), m11_(m11) {}
		matrix22(const matrix22& other) : m00_(other.m00()), m01_(other.m01()), m10_(other.m10()), m11_(other.m11()) {}
		matrix22& operator=(const matrix22& other) = default;
		[[nodiscard]] T m00() const { return m00_; }
		[[nodiscard]] T m01() const { return m01_; }
		[[nodiscard]] T m10() const { return m10_; }
		[[nodiscard]] T m11() const { return m11_; }
		~matrix22() = default;


		vector2<T> operator*(const vector2<T>& vec) const
		{
			return { m00_ * vec.x() + m01_ * vec.y(), m10_ * vec.x() + m11_ * vec.y() };
		}
		matrix22 operator*(const matrix22& other) const
		{
			return { m00 * other.m00() + m01 * other.m10(), m00 * other.m01() + m01 * other.m11(),
					m10 * other.m00() + m11 * other.m10(), m10 * other.m01() + m11 * other.m11() };
		}
		matrix22 operator*(const T scalar) const {
			return { m00_ * scalar, m01_ * scalar, m10_ * scalar, m11_ * scalar };
		}
		void operator*=(T scalar)
		{
			m00_ *= scalar;
			m01_ *= scalar;
			m10_ *= scalar;
			m11_ *= scalar;
		}
		matrix22 operator+(const matrix22& other) const {
			return { m00_ + other.m00_, m01_ + other.m01_, m10_ + other.m10_, m11_ + other.m11_ };
		}
		matrix22 operator-(const matrix22& other) const {
			return { m00_ - other.m00_, m01_ - other.m01_, m10_ - other.m10_, m11_ - other.m11_ };
		}
		void operator+=(const matrix22& other)
		{
			m00_ += other.m00();
			m01_ += other.m01();
			m10_ += other.m10();
			m11_ += other.m11();
		}
		void operator-=(const matrix22& other)
		{
			m00_ -= other.m00();
			m01_ -= other.m01();
			m10_ -= other.m10();
			m11_ -= other.m11();
		}


		[[nodiscard]] T determinant() const { return m00_ * m11_ - m01_ * m10_; }
		[[nodiscard]] matrix22 inverse() const
		{
			T det = determinant();
			if (det == 0) return *this;
			T inv_det = 1 / det;
			return { m11_ * inv_det, -m01_ * inv_det, -m10_ * inv_det, m00_ * inv_det };
		}
		[[nodiscard]] matrix22 transpose() const
		{
			return { m00_, m10_, m01_, m11_ };
		}

		static matrix22 rotation(const T angle) {
			T c = cos(angle);
			T s = sin(angle);
			return { c, -s, s, c };
		}
		static matrix22 scale(float x, float y) {
			return { x, 0, 0, y };
		}
		static matrix22 scale(float s) {
			return { s, 0, 0, s };
		}
		static matrix22 identity() {
			return { 1, 0, 0, 1 };
		}
	};

	/*
	 * @brief A structure that represents a 2D transform with a position and an angle
	 */
	struct transform
	{
		vector2<float> position{};
		float angle{};
		vector2<float> scale {1, 1};
	};

	/*
	 * @brief calculates the minimum of x and y components of a vector
	 * @tparam U the type of the components
	 * @param vector the vector to calculate the minimum of
	 * @return the minimum of the x and y components
	 * @note this function is only available for floating point types
	 */
	template <typename U, typename = std::enable_if_t<std::is_floating_point_v<U>>>
	[[nodiscard]] static float single_min(const vector2<U>& vector)
	{
		return std::min(vector.x(), vector.y());
	}

	/*
	 * @brief calculates the minimum of x and y components of an unlimited number of vectors
	 * @tparam U the type of the components
	 * @param vector the first vector to calculate the minimum of
	 * @param vectors the rest of the vectors to calculate the minimum of
	 * @return the minimum of the x and y components
	 * @note this function is only available for floating point types
	 */
	template <typename U, typename ... Vectors>
	[[nodiscard]] static float single_min(const vector2<U>& vector, const Vectors& ... vectors)
	{
		//other vectors are passed to the function recursively and have to be of the same type
		return std::min(vector.x(), single_min<U>(vectors...));
	}

	/*
	 * @brief Checks if two floating point numbers are almost equal
	 * @tparam T the type of the numbers
	 * @param a the first number
	 * @param b the second number
	 * @param epsilon the epsilon value to check against
	 * @return true if the numbers are almost equal, false otherwise
	 * @note this function is only available for floating point types
	 */
	template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
	bool almost_equal(T a, T b, T epsilon = std::numeric_limits<T>::epsilon()) {
		return std::fabs(a - b) <= epsilon;
	}

	/*
	 * @brief Checks if two floating point vectors are almost equal
	 * @tparam T the type of the vectors
	 * @param a the first vector
	 * @param b the second vector
	 * @param epsilon the epsilon value to check against
	 * @return true if the vectors are almost equal, false otherwise
	 */
	template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
	bool almost_equal(const vector2<T>& a, const vector2<T>& b, T epsilon = std::numeric_limits<T>::epsilon())
	{
		return almost_equal(a.x(), b.x(), epsilon) && almost_equal(a.y(), b.y(), epsilon);
	}

}
#endif