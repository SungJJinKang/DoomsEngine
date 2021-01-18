#pragma once
#include "SharedFutureWrapper.h"

template <typename T>
class DummySharedFuture : public SharedFutureWrapper<T>
{

public:

	DummySharedFuture() noexcept {}
	DummySharedFuture(const DummySharedFuture& other) {}
	DummySharedFuture(const DummySharedFuture& other) noexcept {}
	DummySharedFuture(FutureWrapper<T>&& other) noexcept {}
	DummySharedFuture(DummySharedFuture&& other) noexcept {}

	virtual ~DummySharedFuture(){}

	DummySharedFuture& operator=(const DummySharedFuture& other) {}
	DummySharedFuture& operator=(const DummySharedFuture& other) noexcept {}
	DummySharedFuture& operator=(DummySharedFuture&& other) noexcept {}



	virtual T get() final { return {}; }
	virtual T& get() final { return {}; };

	virtual bool valid() const noexcept final { return false; }
	virtual void wait() const final {}

	template< class Rep, class Period >
	std::future_status wait_for(const std::chrono::duration<Rep, Period>& timeout_duration) const final { return std::future_status::ready; }
	template< class Clock, class Duration >
	std::future_status wait_until(const std::chrono::time_point<Clock, Duration>& timeout_time) const final { return std::future_status::ready; }

};

