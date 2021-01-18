#pragma once
#include "FutureWrapper.h"

#include <utility>

template <typename T>
class DummyFuture : public FutureWrapper<T>
{
public:

	DummyFuture() noexcept {}
	DummyFuture(DummyFuture&& other) noexcept {}
	DummyFuture(const DummyFuture& other) = delete;

	virtual ~DummyFuture(){}

	DummyFuture& operator =(DummyFuture&& other) noexcept final 
	{
		return *this;
	}
	DummyFuture& operator =(const DummyFuture& other) = delete;


	inline SharedFutureWrapper<T> share() final {}

	inline T get() final { return {}; }
	inline T& get() final { return {}; }


	inline bool valid() const noexcept final { return false; }
	inline void wait() const final {}

	inline std::future_status wait_for(const std::chrono::duration<Rep, Period>& timeout_duration) const final { return future_status::ready; }
	inline std::future_status wait_until(const std::chrono::time_point<Clock, Duration>& timeout_time) const final { return future_status::ready; }

};

