#pragma once

#include <future>
#include <chrono>

#include "shared_future/SharedFutureWrapper.h"

template <typename T>
class FutureWrapper
{
private:

public:
	FutureWrapper() noexcept {}

	FutureWrapper(const FutureWrapper& other) = delete;

	/// <summary>
	/// Move contructor
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	FutureWrapper(FutureWrapper&& other) noexcept {}

	virtual ~FutureWrapper(){}

	virtual FutureWrapper& operator=(FutureWrapper&& other) noexcept = 0;
	virtual FutureWrapper& operator=(const FutureWrapper& other) = delete;

	virtual SharedFutureWrapper<T> share() = 0;

	virtual T get() = 0; 
	virtual T& get() = 0;
	
	virtual bool valid() const noexcept = 0;
	virtual void wait() const = 0;

	template< class Rep, class Period >
	std::future_status wait_for(const std::chrono::duration<Rep, Period>& timeout_duration) const = 0;
	template< class Clock, class Duration >
	std::future_status wait_until(const std::chrono::time_point<Clock, Duration>& timeout_time) const = 0;
};

