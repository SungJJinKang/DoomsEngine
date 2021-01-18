#pragma once

#include <future>
#include <chrono>


template <typename T>
class SharedFutureWrapper
{
private:

public:
	SharedFutureWrapper() noexcept{}
	SharedFutureWrapper(const SharedFutureWrapper& other) {}
	SharedFutureWrapper(const SharedFutureWrapper& other) noexcept {}
	SharedFutureWrapper(FutureWrapper<T>&& other) noexcept {}
	SharedFutureWrapper(SharedFutureWrapper&& other) noexcept {}

	virtual ~SharedFutureWrapper(){}

	SharedFutureWrapper& operator=(const SharedFutureWrapper& other) {}
	SharedFutureWrapper& operator=(const SharedFutureWrapper& other) noexcept {}
	SharedFutureWrapper& operator=(SharedFutureWrapper&& other) noexcept {}



	virtual T get() = 0;
	virtual T& get() = 0;

	virtual bool valid() const noexcept = 0;
	virtual void wait() const = 0;

	template< class Rep, class Period >
	std::future_status wait_for(const std::chrono::duration<Rep, Period>& timeout_duration) const = 0;
	template< class Clock, class Duration >
	std::future_status wait_until(const std::chrono::time_point<Clock, Duration>& timeout_time) const = 0;
};

