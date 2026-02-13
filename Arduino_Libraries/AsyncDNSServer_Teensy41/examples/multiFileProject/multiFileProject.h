/****************************************************************************************************************************
  multiFileProject.h
  For Teensy41 with QNEthernet
  
  AsyncDNSServer_Teensy41 is a Async UDP library for the Teensy41 using built-in Ethernet and QNEThernet
  
  Based on and modified from ESPAsyncUDP Library (https://github.com/me-no-dev/ESPAsyncUDP)
  Built by Khoi Hoang https://github.com/khoih-prog/AsyncDNSServer_Teensy41
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#pragma once

#define _ASYNC_DNS_TEENSY41_LOGLEVEL_       1

#define USING_DHCP            true
//#define USING_DHCP            false

#if !USING_DHCP
  // Set the static IP address to use if the DHCP fails to assign
  IPAddress myIP(192, 168, 2, 222);
  IPAddress myNetmask(255, 255, 255, 0);
  IPAddress myGW(192, 168, 2, 1);
  //IPAddress mydnsServer(192, 168, 2, 1);
  IPAddress mydnsServer(8, 8, 8, 8);
#endif

#include "QNEthernet.h"       // https://github.com/ssilverman/QNEthernet
using namespace qindesign::network;

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include <AsyncDNSServer_Teensy41.hpp>        // https://github.com/khoih-prog/AsyncDNSServer_Teensy41
