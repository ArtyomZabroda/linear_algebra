#ifndef _ZABRODA_VECTOR_H_
#define _ZABRODA_VECTOR_H_

#include <array>
#include <type_traits>
#include <numeric>
#include "utility.h"

namespace zabroda::math {

	// Base for all vector-like classes. Uses CRTP to manifest pseudo-polymorphic behavior
	template <template <size_t, typename> class Child, size_t Sz, typename T>
	class Tuple {
	public:
		using iterator = std::array<T, Sz>::iterator;
		using const_iterator = std::array<T, Sz>::const_iterator;
		using reverse_iterator = std::array<T, Sz>::reverse_iterator;
		using const_reverse_iterator = std::array<T, Sz>::const_reverse_iterator;

		Tuple();
		template<std::convertible_to<T> U>
		Tuple(std::initializer_list<U> init);

		explicit Tuple(T default_val);
		template<std::forward_iterator Iter>
		explicit Tuple(Iter begin); // Initialize from container

		Tuple(const Tuple&) = default;
		Tuple(Tuple&&) = default;
		Tuple& operator=(const Tuple&) = default;
		Tuple& operator=(Tuple&&) = default;

		template<std::convertible_to<T> U>
		Child<Sz, T>& operator=(std::initializer_list<U> init);

		T& operator()(size_t i);
		T operator() (size_t i) const;

		bool operator==(const Child<Sz, T>& other) const;
		bool operator!=(const Child<Sz, T>& other) const;

		Child<Sz, T>& operator+=(const Child<Sz, T>& other);
		Child<Sz, T> operator+(const Child<Sz, T>& other);

		Child<Sz, T>& operator-=(const Child<Sz, T>& other);
		Child<Sz, T> operator-(const Child<Sz, T>& other);

		Child<Sz, T>& operator*=(T f);
		Child<Sz, T> operator*(T f);

		Child<Sz, T>& operator/=(T f);
		Child<Sz, T> operator/(T f);

		Child<Sz, T> operator-();

		size_t size() { return Sz; }
		iterator begin() { return elems_.begin(); }
		iterator end() { return elems_.end(); }
		const_iterator begin() const { return elems_.begin(); }
		const_iterator end() const { return elems_.end(); }
	private:
		std::array<T, Sz> elems_;
	};

	template <template <size_t, typename> class Child, size_t Sz, typename T>
	Child<Sz, T> zabroda::math::Tuple<Child, Sz, T>::operator-()
	{
		Child<Sz, T> result;
		iterator b1 = begin();
		iterator e = end();
		for (auto b = result.begin(); b1 != e; ++b1, ++b)
			*b = -(*b1);
		return result;
	}

	template <template <size_t, typename> class Child, size_t Sz, typename T>
	Child<Sz, T> zabroda::math::Tuple<Child, Sz, T>::operator/(T f)
	{
		Child<Sz, T> result;
		iterator b1 = begin();
		iterator e = end();
		for (auto b = result.begin(); b1 != e; ++b1, ++b)
			*b = (*b1) / f;
		return result;
	}

	template <template <size_t, typename> class Child, size_t Sz, typename T>
	Child<Sz, T>& zabroda::math::Tuple<Child, Sz, T>::operator/=(T f)
	{
		iterator b1 = begin();
		iterator e = end();
		for (; b1 != e; ++b1)
			*b1 /= f;
		return static_cast<Child<Sz, T>&>(*this);
	}

	template <template <size_t, typename> class Child, size_t Sz, typename T>
	Child<Sz, T> zabroda::math::Tuple<Child, Sz, T>::operator*(T f)
	{
		Child<Sz, T> result;
		iterator b1 = begin();
		iterator e = end();
		for (auto b = result.begin(); b1 != e; ++b1, ++b)
			*b = (*b1) * f;
		return result;
	}

	template <template <size_t, typename> class Child, size_t Sz, typename T>
	Child<Sz, T>& zabroda::math::Tuple<Child, Sz, T>::operator*=(T f)
	{
		iterator b1 = begin();
		iterator e = end();
		for (; b1 != e; ++b1)
			*b1 *= f;
		return static_cast<Child<Sz, T>&>(*this);
	}

	template <template <size_t, typename> class Child, size_t Sz, typename T>
	Child<Sz, T> zabroda::math::Tuple<Child, Sz, T>::operator-(const Child<Sz, T>& other)
	{
		Child<Sz, T> result;
		iterator b1 = begin();
		const_iterator b2 = other.begin();
		iterator e = end();
		for (auto b = result.begin(); b1 != e; ++b1, ++b2, ++b)
			*b = (*b1) - (*b2);
		return result;
	}

	template <template <size_t, typename> class Child, size_t Sz, typename T>
	Child<Sz, T>& zabroda::math::Tuple<Child, Sz, T>::operator-=(const Child<Sz, T>& other)
	{
		iterator b1 = begin();
		const_iterator b2 = other.begin();
		iterator e = end();
		for (; b1 != e; ++b1, ++b2)
			*b1 -= *b2;
		return static_cast<Child<Sz, T>&>(*this);
	}

	template <template <size_t, typename> class Child, size_t Sz, typename T>
	Child<Sz, T> zabroda::math::Tuple<Child, Sz, T>::operator+(const Child<Sz, T>& other)
	{
		Child<Sz, T> result;
		iterator b1 = begin();
		const_iterator b2 = other.begin();
		iterator e = end();
		for (auto b = result.begin(); b1 != e; ++b1, ++b2, ++b)
			*b = (*b1) + (*b2);
		return result;
	}

	template <template <size_t, typename> class Child, size_t Sz, typename T>
	Child<Sz, T>& zabroda::math::Tuple<Child, Sz, T>::operator+=(const Child<Sz, T>& other)
	{
		iterator b1 = begin();
		const_iterator b2 = other.begin();
		iterator e = end();
		for (; b1 != e; ++b1, ++b2)
			*b1 += *b2;
		return static_cast<Child<Sz, T>&>(*this);
	}

	template <template <size_t, typename> class Child, size_t Sz, typename T>
	bool zabroda::math::Tuple<Child, Sz, T>::operator!=(const Child<Sz, T>& other) const
	{
		return !(*this == other);
	}

	template <template <size_t, typename> class C, size_t Sz, typename T /*= float*/>
	bool zabroda::math::Tuple<C, Sz, T>::operator==(const C<Sz, T>& other) const
	{
		for (int i{}; i < Sz; ++i) {
			if (!compare_floats((*this)(i), other(i))) return false;
		}
		return true;
	}

	template <template <size_t, typename> class C, size_t sz, typename T /*= float*/>
	template<std::convertible_to<T> U>
	C<sz, T>& zabroda::math::Tuple<C ,sz, T>::operator=(std::initializer_list<U> init)
	{
		assert(init.size() == size());
		std::copy(init.begin(), init.end(), elems_.begin());
		return static_cast<C<T>&>(*this);
	}

	template <template <size_t, typename> class C, size_t sz, typename T /*= float*/>
	template<std::forward_iterator Iter>
	zabroda::math::Tuple<C, sz, T>::Tuple(Iter begin)
	{
		auto s = size();
		for (int i{}; i < s; ++i) {
			(*this)(i) = *begin;
			++begin;
		}

	}

	template <template <size_t, typename> class C, size_t sz, typename T /*= float*/>
	zabroda::math::Tuple<C, sz, T>::Tuple(T default_val)
	{
		for (auto& el : elems_)
			el = default_val;
	}

	template <template <size_t, typename> class C, size_t sz, typename T /*= float*/>
	T zabroda::math::Tuple<C, sz, T>::operator() (size_t i) const
	{
		return elems_[i];
	}

	template <template <size_t, typename> class C, size_t sz, typename T /*= float*/>
	T& zabroda::math::Tuple<C, sz, T>::operator()(size_t i)
	{
		return elems_[i];
	}

	template <template <size_t, typename> class C, size_t sz, typename T /*= float*/>
	template<std::convertible_to<T> U>
	zabroda::math::Tuple<C, sz, T>::Tuple(std::initializer_list<U> init)
	{
		assert(init.size() == size());
		std::copy(init.begin(), init.end(), elems_.begin());
	}

	template <template <size_t, typename> class C, size_t sz, typename T /*= float*/>
	zabroda::math::Tuple<C, sz, T>::Tuple()
		: elems_{}
	{
	}



	template<size_t Sz, typename T = float>
	class Vector : public Tuple<Vector, Sz, T> {
		using Tuple<Vector, Sz, T>::Tuple;
	};

	template<typename T>
	class Vector<2, T> : public Tuple<Vector, 2, T> {
	public:
		using Tuple<Vector, 2, T>::Tuple;
		T& x() { return (*this)(0); }
		T x() const { return (*this)(0); }
		T& y() { return (*this)(1); }
		T y() const { return (*this)(1); }
	};

	template<typename T>
	class Vector<3, T> : public Tuple<Vector, 3, T> {
	public:
		using Tuple<Vector, 3, T>::Tuple;
		T& x() { return (*this)(0); }
		T x() const { return (*this)(0); }
		T& y() { return (*this)(1); }
		T y() const { return (*this)(1); }
		T& z() { return (*this)(2); }
		T z() const { return (*this)(2); }
	};



	template <size_t Sz, typename T /*= float*/>
	T length(const Vector<Sz, T>& t)
	{
		T result{};
		for (auto a : t)
			result += a * a;
		return sqrt(result);
	}

	template <size_t Sz, typename T /*= float*/>
	Vector<Sz, T> normalize(Vector<Sz, T> t)
	{
		T l = length(t);
		return t / l;
	}

	template <size_t Sz, typename T /*= float*/>
	T dot(const Vector<Sz, T>& t1, const Vector<Sz, T>& t2)
	{
		return std::inner_product(t1.begin(), t1.end(), t2.begin(), T{});
	}

	template <size_t Sz, typename T /*= float*/>
	Vector<3, T> cross(const Vector<Sz, T>& t1, const Vector<Sz, T>& t2) // function is defined only for 3d vector
	{
		return { t1.y() * t2.z() - t1.z() * t2.y(),
				 t1.z() * t2.x() - t1.x() * t2.z(),
				 t1.x() * t2.y() - t1.y() * t2.x()
		       };
	}
}

#endif