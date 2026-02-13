/****************************************************************************************************************************
  AsyncDNSServer_Teensy41.h
   
  AsyncDNSServer_Teensy41 is a Async UDP library for the Teensy41 using built-in Ethernet and QNEThernet
  
  Based on and modified from ESPAsyncUDP Library (https://github.com/me-no-dev/ESPAsyncUDP)
  Built by Khoi Hoang https://github.com/khoih-prog/AsyncDNSServer_Teensy41
  
  Version: 1.1.1
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.1.1   K Hoang      19/03/2022 Initial coding for Teensy 4.1 using built-in QNEthernet.
                                  Bump up version to v1.1.1 to sync with AsyncDNSServer_STM32 v1.1.1  
  ***************************************************************************************************************************/

#pragma once
  
#ifndef ASYNC_DNS_SERVER_TEENSY41_H
#define ASYNC_DNS_SERVER_TEENSY41_H

#if ( defined(CORE_TEENSY) && defined(__IMXRT1062__) && defined(ARDUINO_TEENSY41) )
  // For Teensy 4.1
  #if !defined(BOARD_NAME)
    #define BOARD_NAME              "TEENSY 4.1"
  #endif
  
  // Use true for NativeEthernet Library, false if using other Ethernet libraries
  #define USE_NATIVE_ETHERNET     false
  #define USE_QN_ETHERNET         true
#else
  //#error Only Teensy 4.1 supported
#endif

#define ASYNC_DNS_SERVER_TEENSY41_VERSION            "AsyncDNSServer_Teensy41 v1.1.1"

#define ASYNC_DNS_SERVER_TEENSY41_VERSION_MAJOR      1
#define ASYNC_DNS_SERVER_TEENSY41_VERSION_MINOR      1
#define ASYNC_DNS_SERVER_TEENSY41_VERSION_PATCH      1

#define ASYNC_DNS_SERVER_TEENSY41_VERSION_INT        1001001

#include <AsyncUDP_Teensy41.h>

#include "AsyncDNSServer_Teensy41_Debug.h"

#include "AsyncDNSServer_Teensy41.hpp"
#include "AsyncDNSServer_Teensy41_Impl.h"

#endif    // ASYNC_DNS_SERVER_TEENSY41_H
