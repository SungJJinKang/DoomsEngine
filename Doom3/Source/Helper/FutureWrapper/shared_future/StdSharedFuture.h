#pragma once
#include "SharedFutureWrapper.h"

template <typename T>
class StdSharedFuture : public SharedFutureWrapper<T>
{
private:
	std::shared_future<T> shared_future;
public:
	StdSharedFuture() noexcept : shared_future{} {}
	StdSharedFuture(const StdSharedFuture& other) : shared_future{ other.stdFuture } {}
	StdSharedFuture(const StdSharedFuture& other) noexcept : shared_future{ other.stdFuture }  {}
	StdSharedFuture(FutureWrapper<T>&& other) noexcept : shared_future{std::move(other.stdFuture)} {}
	StdSharedFuture(StdSharedFuture&& other) noexcept : shared_future{ std::move(other.shared_future) } {}

	virtual ~StdSharedFuture(){}

	inline StdSharedFuture& operator=(const StdSharedFuture& other)
	{ 
		shared_future = other.shared_future;
		return *this;
	}
	inline StdSharedFuture& operator=(const StdSharedFuture& other) noexcept
	{
		shared_future = other.shared_future;
		return *this;
	}
	inline StdSharedFuture& operator=(StdSharedFuture&& other) noexcept
	{
		shared_future = std::move(other.shared_future);
		return *this;
	}



	inline virtual T get() final { return shared_future.get(); }
	inline virtual T& get() final { return shared_future.get(); };

	inline virtual bool valid() const noexcept final { return shared_future.valid(); }
	inline virtual void wait() const final { return shared_future.wait(); }

	template< class Rep, class Period >
	inline std::future_status wait_for(const std::chrono::duration<Rep, Period>& timeout_duration) const final { return shared_future.wait_for(timeout_duration); }
	
	template< class Clock, class Duration >
	inline std::future_status wait_until(const std::chrono::time_point<Clock, Duration>& timeout_time) const final { return shared_future.wait_until(timeout_time); }
};

