//==================================================================================
// Copyright (c) 2016 - 2018 , Advanced Micro Devices, Inc.  All rights reserved.
//
/// \author AMD Developer Tools Team
/// \file AMDTPowerProfileApi.h
///
//==================================================================================

#pragma once

/**
\file AMDTPowerProfileApi.h
\brief AMD Power Profiler APIs to configure, control and collect the power profile counters.

\defgroup profiling Power Profiling
\brief AMDT Power Profiler APIs.

\mainpage AMD uProf Power Profiler API
The AMDTPwrProfileAPI is a powerful library to help analyze the energy efficiency of systems based on AMD CPUs, APUs and Discrete GPUs.

This API:
- Provides counters to read the power, thermal and frequency characteristics of APU/dGPU and their subcomponents.
- Supports AMD APUs (Kaveri, Temash, Mullins, Carrizo), Discrete GPUs (Tonga, Iceland, Bonaire, Hawaii and other newer graphics cards)
- Supports AMD FirePro discrete GPU cards (W9100, W8100, W7100, W5100 and other newer graphics cards).
- Supports Microsoft Windows as a dynamically loaded library or as a static library.
- Supports Linux as a shared library.
- Manages memory automatically - no allocation and free required.

Using this API, counter values can be read at regular sampling interval. Before any profiling done, the \ref AMDTPwrProfileInitialize()
API must be called. When all the profiling is finished, the \ref AMDTPwrProfileClose() API must be called. Upon successful completion all
the APIs will return AMDT_STATUS_OK, otherwise they return appropriate error codes.
*/

/** \example CollectAllCounters.cpp
Example program to collect all the available counters.
*/

#include <AMDTDefinitions.h>
#include <AMDTPowerProfileDataTypes.h>

/** This API loads and initializes the AMDT Power Profile drivers. This API should be the first one to be called.

    \ingroup profiling
    @param[in] profileMode: Client should select any one of the predefined profile modes that are defined in \ref AMDTPwrProfileMode.
    \return The status of initialization request
    \retval AMDT_STATUS_OK: Success
    \retval AMDT_ERROR_INVALIDARG: An invalid profileMode parameter was passed
    \retval AMDT_ERROR_DRIVER_UNAVAILABLE: Driver not available
    \retval AMDT_DRIVER_VERSION_MISMATCH: Mismatch between the expected and installed driver versions
    \retval AMDT_ERROR_PLATFORM_NOT_SUPPORTED: Platform not supported
    \retval AMDT_WARN_SMU_DISABLED: SMU is disabled and hence power and thermal values provided by SMU will not be available
    \retval AMDT_WARN_IGPU_DISABLED: Internal GPU is disabled
    \retval AMDT_ERROR_FAIL: An internal error occurred
    \retval AMDT_ERROR_PREVIOUS_SESSION_NOT_CLOSED: Previous session was not closed.
*/
extern AMDTResult AMDTPwrProfileInitialize(AMDTPwrProfileMode profileMode);

/** This API provides the list of all supported counters for the profile session.
The pointer returned will be valid till the client calls \ref AMDTPwrProfileClose() function.

    \ingroup profiling
    @param[out] pNumCounters: Number of counters supported by the device
    @param[out] ppCounterDescs: Description of each counter supported by the device
    \return The status of device counter details request
    \retval AMDT_STATUS_OK: On Success
    \retval AMDT_ERROR_INVALIDARG: NULL pointer was passed as ppCounterDescs or pNumCounters parameters
    \retval AMDT_ERROR_DRIVER_UNINITIALIZED: \ref AMDTPwrProfileInitialize() function was neither called nor successful
    \retval AMDT_ERROR_INVALID_DEVICEID: invalid deviceId parameter was passed
    \retval AMDT_ERROR_OUTOFMEMORY: Failed to allocate required memory
    \retval AMDT_ERROR_FAIL: An internal error occurred
*/
extern AMDTResult AMDTPwrGetSupportedCounters(AMDTUInt32* pNumCounters,
                                               AMDTPwrCounterDesc** ppCounterDescs);

/** This API provides the counter id for a basic counter.

    \ingroup profiling
    @param[in] counter: supported counter to get the counter is defined in in AMDTPowerProfileDataTypes.h
    @param[out] pCounterId: counter id of counter.
    \return The status of counter description request
    \retval AMDT_STATUS_OK: On Success
    \retval AMDT_ERROR_INVALIDARG:  NULL pointer was passed as pCounterDesc parameter
    \retval AMDT_ERROR_DRIVER_UNINITIALIZED: \ref AMDTPwrProfileInitialize() function was neither called nor successful
    \retval AMDT_ERROR_INVALID_COUNTERID: Invalid counterId parameter was passed
    \retval AMDT_ERROR_FAIL: An internal error occurred
*/
extern AMDTResult AMDTPwrGetCounterId(AMDTCounter counter, AMDTUInt32* pCounterId);

/** This API provides the description for the given counter Index.

    \ingroup profiling
    @param[in] counterId: Counter index
    @param[out] pCounterDesc: Description of the counter which index is counterId
    \return The status of counter description request
    \retval AMDT_STATUS_OK: On Success
    \retval AMDT_ERROR_INVALIDARG:  NULL pointer was passed as pCounterDesc parameter
    \retval AMDT_ERROR_DRIVER_UNINITIALIZED: \ref AMDTPwrProfileInitialize() function was neither called nor successful
    \retval AMDT_ERROR_INVALID_COUNTERID: Invalid counterId parameter was passed
    \retval AMDT_ERROR_FAIL: An internal error occurred
*/
extern AMDTResult AMDTPwrGetCounterDesc(AMDTUInt32 counterId,
                                        AMDTPwrCounterDesc* pCounterDesc);

/** This API will enable the counter to be sampled. This API cannot be used once profile is started.
    - If histogram/cumulative counters are enabled along with simple counters, then it is expected that the
    AMDTPwrReadAllEnabledCounters() API is regularly called to read the simple counters value. Only then
    the values for histogram/cumulative counters will be aggregated and the AMDTPwrReadCounterHistogram()
    API will return the correct values.
    - If only the histogram/cumulative counters are enabled, calling AMDTPwrReadCounterHistogram() is
    sufficient to get the values for the enabled histogram/cumulative counters.

    \ingroup profiling
    @param[in] counterId: Counter index
    \return The status of counter enable request
    \retval AMDT_STATUS_OK: On Success
    \retval AMDT_ERROR_DRIVER_UNINITIALIZED: \ref AMDTPwrProfileInitialize() function was neither called nor successful
    \retval AMDT_ERROR_INVALID_COUNTERID: Invalid counterId parameter was passed
    \retval AMDT_ERROR_COUNTER_ALREADY_ENABLED: Specified counter is already enabled
    \retval AMDT_ERROR_PROFILE_ALREADY_STARTED: Counters cannot be enabled on the fly when the profile is already started
    \retval AMDT_ERROR_PREVIOUS_SESSION_NOT_CLOSED: Previous session was not closed
    \retval AMDT_ERROR_COUNTER_NOT_ACCESSIBLE: Counter is not accessible
    \retval AMDT_ERROR_FAIL: An internal error occurred
*/
extern AMDTResult AMDTPwrEnableCounter(AMDTUInt32 counterId);

/** This API will set the driver to periodically sample the counter values and store them in a buffer.
    This cannot be called once the profile run is started. If sampling period is not set, profiler will
    set the default sampling period

    \ingroup profiling
    @param[in] interval: sampling period in millisecond
    \return The status of sampling time set request
    \retval AMDT_STATUS_OK: On Success
    \retval AMDT_ERROR_INVALIDARG: Invalid interval value was passed as IntervalMilliSec parameter
    \retval AMDT_ERROR_DRIVER_UNINITIALIZED: \ref AMDTPwrProfileInitialize() function was neither called nor successful
    \retval AMDT_ERROR_PROFILE_ALREADY_STARTED: Timer interval cannot be changed when the profile is already started
    \retval AMDT_ERROR_PREVIOUS_SESSION_NOT_CLOSED: Previous session was not closed
    \retval AMDT_ERROR_FAIL: An internal error occurred
*/
extern AMDTResult AMDTPwrSetTimerSamplingPeriod(AMDTUInt32 interval);

/** This API will start the profiling and the driver will collect the data at regular interval
    specified by \ref AMDTPwrSetTimerSamplingPeriod(). This has to be called after enabling the required counters
    by using \ref AMDTPwrEnableCounter() or \ref AMDTPwrEnableAllCounters().

    \ingroup profiling
    \return The status of starting the profile
    \retval AMDT_STATUS_OK: On Success
    \retval AMDT_ERROR_DRIVER_UNINITIALIZED: \ref AMDTPwrProfileInitialize function was neither called nor successful
    \retval AMDT_ERROR_TIMER_NOT_SET: Sampling timer was not set
    \retval AMDT_ERROR_COUNTERS_NOT_ENABLED: No counter enabled for collecting profile data
    \retval AMDT_ERROR_PROFILE_ALREADY_STARTED: Profile is already started
    \retval AMDT_ERROR_PREVIOUS_SESSION_NOT_CLOSED: Previous session was not closed
    \retval AMDT_ERROR_BIOS_VERSION_NOT_SUPPORTED: BIOS needs to be upgraded
    \retval AMDT_ERROR_FAIL: An internal error occurred
    \retval AMDT_ERROR_ACCESSDENIED: Profiler is busy, currently not accessible
*/
extern AMDTResult AMDTPwrStartProfiling();

/** This APIs will stop the profiling run which was started by \ref AMDTPwrStartProfiling() function call.

    \ingroup profiling
    \return The status of stopping the profile
    \retval AMDT_STATUS_OK: On Success
    \retval AMDT_ERROR_DRIVER_UNINITIALIZED: \ref AMDTPwrProfileInitialize() function was neither called nor successful
    \retval AMDT_ERROR_PROFILE_NOT_STARTED: Profile is not started
    \retval AMDT_ERROR_FAIL: An internal error occurred
*/
extern AMDTResult AMDTPwrStopProfiling();

/** This API will close the power profiler and unregister driver and cleanup all memory allocated
    during AMDTPwrProfileInitialize().

    \ingroup profiling
    \return The status of closing the profiler
    \retval AMDT_STATUS_OK: On Success
    \retval AMDT_ERROR_FAIL: An internal error occurred
    \retval AMDT_ERROR_DRIVER_UNINITIALIZED: \ref AMDTPwrProfileInitialize() function was neither called nor successful
*/
extern AMDTResult AMDTPwrProfileClose();

/** API to read all the counters that are enabled. This will NOT read the histogram counters.
    This can return an array of {CounterID, Float-Value}. If there are no new samples, this API will
    return AMDTResult NO_NEW_DATA and pNumOfSamples will point to value of zero. If there
    are new samples, this API will return AMDT_STATUS_OK and pNumOfSamples will point
    to value greater than zero.

    \ingroup profiling
    @param[out] ppData: Processed profile data. No need to allocate or free the memory data is valid till we call this API next time
    @param[out] pNumOfSamples: Number of sample based on the AMDTPwrSetSampleValueOption() set
    \return The status reading all enabled counters
    \retval AMDT_STATUS_OK: On Success
    \retval AMDT_ERROR_INVALIDARG: NULL pointer was passed as pNumSamples or ppData parameters
    \retval AMDT_ERROR_DRIVER_UNINITIALIZED: \ref AMDTPwrProfileInitialize() function was neither called nor successful
    \retval AMDT_ERROR_PROFILE_NOT_STARTED: Profile is not started
    \retval AMDT_ERROR_PROFILE_DATA_NOT_AVAILABLE: Profile data is not yet available
    \retval AMDT_ERROR_OUTOFMEMORY: Memory not available
    \retval AMDT_ERROR_SMU_ACCESS_FAILED: One of the configured SMU data access has problem it is advisable to stop the profiling session
    \retval AMDT_ERROR_FAIL: An internal error occurred
*/
extern AMDTResult AMDTPwrReadAllEnabledCounters(AMDTUInt32* pNumOfSamples,
                                                AMDTPwrSample** ppData);
