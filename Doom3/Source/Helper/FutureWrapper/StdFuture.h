#pragma once
#include "FutureWrapper.h"

#include <utility>

template <typename T>
class StdFuture : public FutureWrapper<T>
{
	friend class StdSharedFuture;
private:
	std::future<T> stdFuture;
public:

	inline StdFuture() noexcept : stdFuture{}
	{

	}

	inline StdFuture(StdFuture&& other) noexcept : stdFuture{std::move(other.stdFuture)}
	{
	
	}

	virtual ~StdFuture(){}

	StdFuture(const StdFuture& other) = delete;


	inline StdFuture& operator =(StdFuture&& other) noexcept final
	{
		stdFuture = std::move(other.stdFuture);
		return *this;
	}


	StdFuture& operator =(const StdFuture& other) = delete;


	inline SharedFutureWrapper<T> share() final
	{
		return this->stdFuture.share();
	}

	inline T get() final { return this->stdFuture.get(); }
	inline T& get() final { return this->stdFuture.get(); }


	inline bool valid() const noexcept final { return this->stdFuture.valid(); }
	inline void wait() const final { return this->stdFuture.wait(); }

	template< class Rep, class Period >
	inline std::future_status wait_for(const std::chrono::duration<Rep, Period>& timeout_duration) const final
	{
		return this->stdFuture.wait_for(timeotimeout_durationut_time);
	}

	template< class Clock, class Duration >
	inline std::future_status wait_until(const std::chrono::time_point<Clock, Duration>& timeout_time) const final
	{
		return this->stdFuture.wait_until(timeout_time);
	}

};

