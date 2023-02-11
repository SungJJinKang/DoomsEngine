//==================================================================================
// Copyright (c) 2016 , Advanced Micro Devices, Inc.  All rights reserved.
//
/// \author AMD Developer Tools Team
/// \file AMDTPowerProfileDataTypes.h
///
//==================================================================================

#pragma once

/** \file AMDTPowerProfileDataTypes.h
\brief Data types and structure definitions used by AMD uProf Power Profiler APIs.
*/

#include <AMDTDefinitions.h>

/** HW Components for which power counters are supported are called devices.
Following are such components:
    - AMD APUs and its subcomponents like CPU Compute-units, CPU Cores, integrated GPUs
    - AMD discrete GPUs
This macro denotes all the devices that are relevant to power profiling.
*/
#define AMDT_PWR_ALL_DEVICES 0xFFFFFFFFUL

/**
This macro denotes all the counters that are relevant to power profiling.
*/
#define AMDT_PWR_ALL_COUNTERS 0xFFFFFFFFUL

/** Process name length
*/
#define AMDT_PWR_EXE_NAME_LENGTH 64

/** Process name length
*/
#define AMDT_PWR_EXE_PATH_LENGTH 256

/** Maximum number of available APU P-States
*/
#define AMDT_MAX_PSTATES 8

/** Process marker buffer length
*/
#define AMDT_PWR_MARKER_BUFFER_LENGTH 32

/** Hisotgram maximum bin size
*/
#define AMDT_PWR_HISTOGRAM_MAX_BIN_COUNT 32

/** Maximum values for a counter
*/
#define AMDT_PWR_MAX_COUNTER_VALUE_COUNT 8

/** Device Id
*/
typedef AMDTUInt32 AMDTPwrDeviceId;

/** All the PIDs are set
*/
#define AMD_PWR_ALL_PIDS 0xFFFFFFFFU

#define AMD_PWR_CORE_MASK_SIZE 4

#define FREQ_BIN_CNT 25

#define AMD_PWT_HISTOGRAM_STEPS 200

/** Following power profile counters are supported for AMDTPwrGetCounterId.
\ingroup profiling
*/
typedef enum
{
    AMD_PWR_SOCKET_POWER = 1,
    AMD_PWR_SOCKET_TEMPERATURE,
    AMD_PWR_SOCKET_STAPM_LIMIT,
    AMD_PWR_SOCKET_PPT_FAST_LIMIT,
    AMD_PWR_SOCKET_PPT_SLOW_LIMIT,
    AMD_PWR_SOCKET_PPT_LIMIT,
    AMD_PWR_SOCKET_COUNTER_CNT = AMD_PWR_SOCKET_PPT_LIMIT,
} AMDTCounter;

/** Following power profile modes are supported.
\ingroup profiling
*/
typedef enum
{
    AMDT_PWR_MODE_TIMELINE_ONLINE,          // Enable live profile mode, collect and decode counters simultaneously
    AMDT_PWR_MODE_TIMELINE_OFFLINE,         // Enable offline mode, collect timeline counters and dump counter data in raw file
    AMDT_PWR_MODE_APP_ANALYSIS,             // Enable application analysis mode, collect context data and dump the data into raw files
    AMDT_PWR_MODE_TRANSLATE,                // Decode the data collected in raw file and generate report
    AMDT_PWR_MODE_INSTANT_COUNTER,          // Enable instantenious data reading mode
    AMDT_PWR_MODE_CNT                       // Total supported profile modes
} AMDTPwrProfileMode;

/** Each package (processor node) and its sub-components and dGPUs are considered as devices here.
Following are the various types of devices supported by power profiler.
\ingroup profiling
*/
typedef enum
{
    AMDT_PWR_DEVICE_SYSTEM,                 /**< Dummy root node. All the top-level devices like CPU,APU,dGPU are its children */
    AMDT_PWR_DEVICE_PACKAGE,                /**< In a multi-node, socket system, each node will be a separate package */
    AMDT_PWR_DEVICE_CPU_COMPUTE_UNIT,       /**< Each CPU Compute-Unit within a package */
    AMDT_PWR_DEVICE_CPU_CORE,               /**< Each CPU core within a CPU Compute-Unit */
    AMDT_PWR_DEVICE_DIE,                    /**< Each Die in a socket */
    AMDT_PWR_DEVICE_PHYSICAL_CORE,          /**< Each Physical core in a die of a socket */
    AMDT_PWR_DEVICE_THREAD,                 /**< Each Thread in a physical core */
    AMDT_PWR_DEVICE_INTERNAL_GPU,           /**< Integrated GPU within a AMD APU */
    AMDT_PWR_DEVICE_EXTERNAL_GPU,           /**< Each AMD dGPU connected in the system */
    AMDT_PWR_DEVICE_SVI2,                   /**< Serial Voltage Interface 2 */
    AMDT_PWR_DEVICE_CNT                     /**< Total device count */
} AMDTDeviceType;

/** Following is the list of counter category supported by power profiler.
\ingroup profiling
*/
typedef enum
{
    AMDT_PWR_CATEGORY_POWER,              /**< Instantaneous power */
    AMDT_PWR_CATEGORY_FREQUENCY,          /**< Frequency  */
    AMDT_PWR_CATEGORY_TEMPERATURE,        /**< Temperature in centigrade */
    AMDT_PWR_CATEGORY_VOLTAGE,            /**< Voltage */
    AMDT_PWR_CATEGORY_CURRENT,            /**< Current */
    AMDT_PWR_CATEGORY_PSTATE,             /**< P-State */
    AMDT_PWR_CATEGORY_CSTATES_RESIDENCY,  /**< C-State */
    AMDT_PWR_CATEGORY_TIME,               /**< Time */
    AMDT_PWR_CATEGORY_ENERGY,             /**< Energy consumed */
    AMDT_PWR_CATEGORY_CORRELATED_POWER,   /**< Energy consumed */
    AMDT_PWR_CATEGORY_CAC,                /**< CAC values  */
    AMDT_PWR_CATEGORY_CONTROLLER,         /**< Controller Limit and values */
    AMDT_PWR_CATEGORY_DPM,                /**< DPM State residency */
    AMDT_PWR_CATEGORY_CNT,                /**< Total category count */
} AMDTPwrCategory;

/** Following is the list of aggregation types supported by power profiler.
\ingroup profiling
*/
typedef enum
{
    AMDT_PWR_VALUE_SINGLE,                  /**< Single instantaneous value */
    AMDT_PWR_VALUE_CUMULATIVE,              /**< Cumulative value */
    AMDT_PWR_VALUE_HISTOGRAM,               /**< Histogram value */
    AMDT_PWR_VALUE_CNT                      /**< Total power value */
} AMDTPwrAggregation;

/** Various unit types for the output values for the counter types.
\ingroup profiling
*/
typedef enum
{
    AMDT_PWR_UNIT_TYPE_COUNT,             /**< Count index */
    AMDT_PWR_UNIT_TYPE_NUMBER,            /**< Count index */
    AMDT_PWR_UNIT_TYPE_PERCENT,           /**< Percentage */
    AMDT_PWR_UNIT_TYPE_RATIO,             /**< Ratio */
    AMDT_PWR_UNIT_TYPE_MILLI_SECOND,      /**< Time in milli seconds*/
    AMDT_PWR_UNIT_TYPE_JOULE,             /**< Energy consumption */
    AMDT_PWR_UNIT_TYPE_WATT,              /**< Power consumption */
    AMDT_PWR_UNIT_TYPE_VOLT,              /**< Voltage */
    AMDT_PWR_UNIT_TYPE_MILLI_AMPERE,      /**< Current */
    AMDT_PWR_UNIT_TYPE_MEGA_HERTZ,        /**< Frequency type unit */
    AMDT_PWR_UNIT_TYPE_CENTIGRADE,        /**< Temperature type unit */
    AMDT_PWR_UNIT_TYPE_CNT                /**< Total power unit */
} AMDTPwrUnit;

/** States of Power profiler.
\ingroup profiling
*/
typedef enum
{
    AMDT_PWR_PROFILE_STATE_UNINITIALIZED,          /**< Profiler is not initialized */
    AMDT_PWR_PROFILE_STATE_IDLE,                   /**< Profiler is initialized */
    AMDT_PWR_PROFILE_STATE_RUNNING,                /**< Profiler is running */
    AMDT_PWR_PROFILE_STATE_PAUSED,                 /**< Profiler is paused */
    AMDT_PWR_PROFILE_STATE_STOPPED,                /**< Profiler is Stopped */
    AMDT_PWR_PROFILE_STATE_ABORTED,                /**< Profiler is aborted */
    AMDT_PWR_PROFILE_STATE_CNT                     /**< Total number of profiler states */
} AMDTPwrProfileState;

/** Options to retrieve the profiled counter data using AMDTPwrReadAllEnabledCounters function
\ingroup profiling
*/
typedef enum
{
    AMDT_PWR_SAMPLE_VALUE_INSTANTANEOUS,     /**< Default. The latest/instantaneous */
    AMDT_PWR_SAMPLE_VALUE_LIST,              /**< List of sampled counter values */
    AMDT_PWR_SAMPLE_VALUE_AVERAGE,           /**< Average of the sampled counter */
    AMDT_PWR_SAMPLE_VALUE_CNT                /**< Maximum Sample value count */
} AMDTSampleValueOption;

/** P-States can be either hardware or software P-States. Hardware P-States are also known as
Boosted P-States. These are defined as AMDT_PWR_PSTATES_PBx. The Software P-States are defined
as AMDT_PWR_PSTATES_Px, where x is the P-State number. Hardware(Boosted) P-States are not
software visible.
\ingroup profiling
*/
typedef enum
{
    AMDT_PWR_PSTATE_PB0,  /**< Boosted P-State 0 */
    AMDT_PWR_PSTATE_PB1,  /**< Boosted P-State 1*/
    AMDT_PWR_PSTATE_PB2,  /**< Boosted P-State 2*/
    AMDT_PWR_PSTATE_PB3,  /**< Boosted P-State 3*/
    AMDT_PWR_PSTATE_PB4,  /**< Boosted P-State 4*/
    AMDT_PWR_PSTATE_PB5,  /**< Boosted P-State 5*/
    AMDT_PWR_PSTATE_PB6,  /**< Boosted P-State 6*/
    AMDT_PWR_PSTATE_P0,   /**< Software P-State 0 */
    AMDT_PWR_PSTATE_P1,   /**< Software P-State 1 */
    AMDT_PWR_PSTATE_P2,   /**< Software P-State 2 */
    AMDT_PWR_PSTATE_P3,   /**< Software P-State 3 */
    AMDT_PWR_PSTATE_P4,   /**< Software P-State 4 */
    AMDT_PWR_PSTATE_P5,   /**< Software P-State 5 */
    AMDT_PWR_PSTATE_P6,   /**< Software P-State 6 */
    AMDT_PWR_PSTATE_P7,   /**< Software P-State 7 */
} AMDTApuPStates;

/**  Following structure represents the device tree of the target system. Nodes will be
available for components for which power counters are supported. Following are such components -
AMD APUs and its subcomponents like CPU Compute-units, CPU Cores, integrated GPUs & AMD discrete GPUs.
\ingroup profiling
*/
typedef struct AMDTPwrDevice
{
    AMDTDeviceType      m_type;           /**< Device type- compute unit/Core/ package/ dGPU */
    AMDTPwrDeviceId     m_deviceID;       /**< Node id within the topology tree */
    char*               m_pName;          /**< Name of the device */
    char*               m_pDescription;   /**< Description about the device */
    bool                m_isAccessible;   /**< If counters are accessible */
    AMDTUInt32          m_categoryMask;   /**< Supported counter category by the device */
    AMDTPwrDevice*      m_pFirstChild;    /**< Points to the sub-devices of this device */
    AMDTPwrDevice*      m_pNextDevice;    /**< Points to the next device at the same hierarchy */
} AMDTPwrDevice;

/** Details of a supported power counter and its associated device.
Following counter types are supported:
    - Simple Counters has m_aggregation type as AMDT_PWR_VALUE_SINGLE.
    - Histogram Counters has m_aggregation type as AMDT_PWR_VALUE_HISTOGRAM.
    - Cumulative Counters has m_aggregation type as AMDT_PWR_VALUE_CUMULATIVE.
\ingroup profiling
*/
typedef struct AMDTPwrCounterDesc
{
    AMDTUInt32           m_counterID;       /**< Counter index */
    AMDTUInt32           m_deviceId;        /**< Device Id */
    AMDTDeviceType       m_devType;         /**< Device type- compute unit/Core/ package/ dGPU */
    AMDTUInt32           m_devInstanceId;   /**< Device instance id within the device type */
    char*                m_name;            /**< Name of the counter */
    char*                m_description;     /**< Description of the counter */
    AMDTPwrCategory      m_category;        /**< Power/Freq/Temperature */
    AMDTPwrAggregation   m_aggregation;     /**< Single/Histogram/Cumulative */
    AMDTFloat64          m_minValue;        /**< Minimum possible counter value */
    AMDTFloat64          m_maxValue;        /**< Maximum possible counter value */
    AMDTPwrUnit          m_units;           /**< Seconds/MHz/Joules/Watts/Volt/Ampere */
    bool                 m_isParentCounter; /**< If the counter has some child counters*/
} AMDTPwrCounterDesc;

/** Structure represents a counter ID and its value
\ingroup profiling
*/
typedef struct
{
    AMDTUInt32      m_counterID;       /**< Counter index */
    AMDTUInt32      m_valueCnt;        /**< Number of value for this counter */
    union
    {
        AMDTFloat32     m_data;        /**< Counter value */
        AMDTFloat32*    m_pData;       /**< Pointer to the multi value array */
    };
} AMDTPwrCounterValue;

/** This structure represents the system time in second and milliseconds
\ingroup profiling
*/
typedef struct
{
    AMDTUInt64   m_second;           /**< Seconds */
    AMDTUInt64   m_microSecond;      /**< Milliseconds */
} AMDTPwrSystemTime;

/** Output sample with timestamp and the counter values for all the enabled counters.
\ingroup profiling
*/
typedef struct AMDTPwrSample
{
    AMDTPwrSystemTime      m_systemTime;          /**< Start time of Profiling */
    AMDTUInt64             m_elapsedTimeMs;       /**< Elapsed time in milliseconds - relative to the start time of the profile */
    AMDTUInt64             m_recordId;            /**< Record id */
    AMDTUInt32             m_numOfCounter;         /**< Number of counter values available */
    AMDTPwrCounterValue*   m_counterValues;       /**< list of counter values */
} AMDTPwrSample;

/** Provides various P-States and their corresponding frequencies.
\ingroup profiling
*/
typedef struct AMDTPwrApuPstate
{
    AMDTApuPStates  m_state;            /**< P-State number */
    bool            m_isBoosted;        /**< Boosted P-State flag */
    AMDTUInt32      m_frequency;        /**< P-State frequency */
} AMDTPwrApuPstate;

/** List of the supported APU P-States details
\ingroup profiling
*/
typedef struct AMDTPwrApuPstateList
{
    AMDTUInt32        m_cnt;                             /**< Number of P-States */
    AMDTPwrApuPstate  m_stateInfo[AMDT_MAX_PSTATES];     /**< P-States list */
} AMDTPwrApuPstateList;

/** Provides hierarchical relationship details of a power counter. Both the parent and children
counter details will be provided.
\ingroup profiling
*/
typedef struct AMDTPwrCounterHierarchy
{
    AMDTUInt32  m_counter;           /**< Counter Id */
    AMDTUInt32  m_parent;            /**< Parent counter Id */
    AMDTUInt32  m_childCnt;          /**< Number of child counters */
    AMDTUInt32* m_pChildList;        /**< List of child counters */
} AMDTPwrCounterHierarchy;

/** Represents a generic histogram.
\ingroup profiling
*/
typedef struct
{
    AMDTUInt32      m_counterId;                                /**< Counter being aggregated */
    AMDTFloat32     m_bins[AMDT_PWR_HISTOGRAM_MAX_BIN_COUNT];       /**< The counts for each bin are stored in an array of n elements pointed to by bin */
} AMDTPwrHistogram;

/** Represents process power info.
\ingroup profiling
*/
typedef struct AMDTPwrProcessInfo
{
    AMDTUInt32  m_pid;                                  /**< Process id */
    AMDTUInt64  m_sampleCnt;                            /**< Number of PID samples */
    AMDTFloat32 m_power;                                /**< PID power indicator */
    AMDTFloat32 m_ipc;                                  /**< Agreegated IPC value */
    char        m_name[AMDT_PWR_EXE_NAME_LENGTH];       /**< Executable name */
    char        m_path[AMDT_PWR_EXE_PATH_LENGTH];       /**< Path */
} AMDTPwrProcessInfo;

// ContextPowerData: Power with context information
typedef struct  ContextPowerData
{
    AMDTUInt64    m_ip;             /**< Sample address */
    AMDTUInt32    m_processId;      /**< Process id */
    AMDTUInt32    m_threadId;       /**< Thread id */
    AMDTUInt64    m_timeStamp;      /**< Sample time stamp */
    AMDTUInt32    m_coreId;         /**< Cpu core id */
    AMDTFloat32   m_ipcLoad;        /**< Agreegated IPC value */
    AMDTFloat32   m_power;          /**< Power consumed */
    AMDTUInt64    m_sampleCnt;      /**< Number of samples */
} ContextPowerData;

// AMDTPwrModuleData: Power with module information
typedef struct AMDTPwrModuleData
{
    AMDTUInt32    m_processId;                               /**< Process id */
    char          m_processName[AMDT_PWR_EXE_NAME_LENGTH];   /**< Executable name */
    char          m_processPath[AMDT_PWR_EXE_PATH_LENGTH];   /**< Path */
    AMDTFloat32   m_power;                                   /**< Power consumed */
    AMDTFloat32   m_ipcLoad;                                 /**< Agreegated IPC value */
    AMDTUInt64    m_sampleCnt;                               /**< Number of PID samples */
    bool          m_isKernel;                                /**< Kernel/User module */
    char          m_moduleName[AMDT_PWR_EXE_NAME_LENGTH];    /**< Executable name */
    char          m_modulePath[AMDT_PWR_EXE_PATH_LENGTH];    /**< Path */
    AMDTUInt64    m_loadAddr;                                /**< Module load address */
    AMDTUInt64    m_size;                                    /**< Module size */
} AMDTPwrModuleData;

/** Represents the instrumented power data.
\ingroup profiling
*/

typedef struct AMDTPwrInstrumentedPowerData
{
    AMDTUInt8           m_name[AMDT_PWR_MARKER_BUFFER_LENGTH];        /**< Name of the user marker */
    AMDTUInt8           m_userBuffer[AMDT_PWR_MARKER_BUFFER_LENGTH];  /**< User supplied buffer */
    AMDTPwrSystemTime   m_systemStartTime;                            /**< Profile start time */
    AMDTUInt64          m_startTs;                                    /**< Marker start elapsed time */
    AMDTUInt64          m_endTs;                                      /**< Marker end elapsed time */
    AMDTPwrProcessInfo  m_pidInfo;                                    /**< Process information */
} AMDTPwrInstrumentedPowerData;

/** Represents the counter category information.
\ingroup profiling
*/

typedef struct AMDTPwrCategoryInfo
{
    AMDTUInt8           m_name[AMDT_PWR_EXE_NAME_LENGTH];             /**< Name of the category */
    AMDTPwrCategory     m_category;                                   /**< Power/Freq/Temperature */
} AMDTPwrCategoryInfo;

/** Represents the counter unit information.
\ingroup profiling
*/

typedef struct AMDTPwrUnitInfo
{
    AMDTUInt8           m_name[AMDT_PWR_EXE_NAME_LENGTH];             /**< Name string of the unit*/
    AMDTPwrUnit         m_unitId;                                     /**< Unit id defined in AMDTPwrUnit*/
} AMDTPwrUnitInfo;

typedef struct AMDTPwrOfflineSessionInfo
{
    AMDTUInt16 m_family;
    AMDTUInt16 m_model;
    AMDTUInt64 m_samplingInterval;
    AMDTUInt64 m_sessionStartTime;
    AMDTUInt64 m_sessionEndTime;
    AMDTUInt64 m_sessionDuration;
    AMDTUInt32 m_profileType;
    AMDTUInt64 m_targetCoreMask[AMD_PWR_CORE_MASK_SIZE];
} AMDTPwrOfflineSessionInfo;
