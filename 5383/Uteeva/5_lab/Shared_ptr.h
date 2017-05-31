#pragma once
#ifndef SHAREDPTR_H
#define SHAREDPTR_H
#include <algorithm>
#include <cstddef>
namespace stepik
{
	template <typename T>
	class shared_ptr
	{
		template <typename T2>
		friend class shared_ptr;

	public:

		explicit shared_ptr(T *ptr = nullptr) {
			ptr_ = ptr;
			if (ptr_) {
				reference_ = new size_t(1);
			}
			else {
				reference_ = 0;
			}
		}
		~shared_ptr()
		{
			decrement_r();
		}

		template <typename T2>
		shared_ptr(const shared_ptr<T2> & other)
		{
			ptr_ = other.ptr_;
			reference_ = other.reference_;
			if (ptr_) {
				++(*reference_);
			}
		}
		template <typename T2>
		shared_ptr& operator=(const shared_ptr<T2> & other)
		{
			shared_ptr tmp(other);
			swap(tmp);
			return *this;
		}

		void decrement_r() {
			if (reference_ && ptr_ && !--(*reference_)) {
				delete ptr_;
				delete reference_;
				reference_ = 0;
			}
		}
		explicit operator bool() const
		{
			return (ptr_ != nullptr);
		}

		T* get() const
		{
			return ptr_;
		}

		long use_count() const
		{
			return (reference_ ? *reference_ : 0);
		}

		T& operator*() const
		{
			return *ptr_;
		}

		T* operator->() const
		{
			return ptr_;
		}
		template <typename T2>
		bool operator==(const shared_ptr<T2> &other) const
		{
			return (ptr_ == other.ptr_);
		}

		void swap(shared_ptr& x) noexcept
		{
			std::swap(ptr_, x.ptr_);
			std::swap(reference_, x.reference_);
		}

		void reset(T *ptr = 0)
		{
			shared_ptr tmp(ptr);
			this->swap(tmp);
		}

	private:
		T* ptr_;
		size_t* reference_;

	};
} // namespace stepik

#endif // SHAREDPTR_H