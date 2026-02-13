# AsyncDNSServer_Teensy41


[![arduino-library-badge](https://www.ardu-badge.com/badge/AsyncDNSServer_Teensy41.svg?)](https://www.ardu-badge.com/AsyncDNSServer_Teensy41)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/AsyncDNSServer_Teensy41.svg)](https://github.com/khoih-prog/AsyncDNSServer_Teensy41/releases)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/AsyncDNSServer_Teensy41.svg)](http://github.com/khoih-prog/AsyncDNSServer_Teensy41/issues)

<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>

---
---

## Table of Contents


* [Why do we need this AsyncDNSServer_Teensy41 library](#why-do-we-need-this-AsyncDNSServer_Teensy41-library)
  * [Features](#features)
  * [Why Async is better](#why-async-is-better)
  * [Currently Supported Boards](#currently-supported-boards)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Teensy boards](#1-for-teensy-boards)
* [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)
* [HOWTO Setting up the Async DNS Server](#howto-setting-up-the-async-dns-server)
* [Examples](#examples)
	* [ 1. AsyncCaptivePortal](examples/AsyncCaptivePortal)
  * [ 2. AsyncCaptivePortalAdvanced](examples/AsyncCaptivePortalAdvanced) 
  * [ 3. AsyncDNServerFull](examples/AsyncDNServerFull)
  * [ 4. AsyncDNSServer](examples/AsyncDNSServer)
  * [ 5. multiFileProject](examples/multiFileProject)
* [Example AsyncDNSServer](#example-AsyncDNSServer)
  * [1. File AsyncDNSServer.ino](#1-file-AsyncDNSServerino)
  * [2. File defines.h](#2-file-definesh) 
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Why do we need this [AsyncDNSServer_Teensy41 library](https://github.com/khoih-prog/AsyncDNSServer_Teensy41)

#### Features

This [AsyncDNSServer_Teensy41 library](https://github.com/khoih-prog/AsyncDNSServer_Teensy41) is a fully asynchronous DNSServer library, designed for a trouble-free, multi-connection network environment, for **Teensy 4.1 using QNEthernet Library**.

This library is based on, modified from:

1. [Develo's ESPAsyncDNSServer](https://github.com/devyte/ESPAsyncDNSServer)
2. [AsyncDNSServer_STM32](https://github.com/khoih-prog/AsyncDNSServer_STM32)

to apply the better and faster **asynchronous** feature into **Teensy 4.1 using QNEthernet Library**.


#### Why Async is better

- Using asynchronous network means that you can handle **more than one connection at the same time**
- You are called once the packet is ready
- After a DNS Client connected to this Async DNS server, you are **immediately ready** to handle other connections while the Server is taking care of receiving and responding to the UDP packets in the background.
- You are not required to check in a tight loop() the arrival of the DNS requesting packets to process them.
- **Speed is OMG**


### Currently Supported Boards

1. **Teensy 4.1 using QNEthernet Library**


---
---

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`Teensy core v1.56+`](https://www.pjrc.com/teensy/td_download.html)
 3. [`QNEthernet Library version v0.14.0+`](https://github.com/ssilverman/QNEthernet) for Teensy 4.1 built-in Ethernet.
 4. [`AsyncUDP_Teensy41 library v1.2.1+`](https://github.com/khoih-prog/AsyncUDP_Teensy41). To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/AsyncUDP_Teensy41.svg?)](https://www.ardu-badge.com/AsyncUDP_Teensy41).
 
---

### Installation

The suggested way to install is to:

#### Use Arduino Library Manager

The best way is to use `Arduino Library Manager`. Search for `AsyncDNSServer_Teensy41`, then select / install the latest version. You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/AsyncDNSServer_Teensy41.svg?)](https://www.ardu-badge.com/AsyncDNSServer_Teensy41) for more detailed instructions.

### Manual Install

1. Navigate to [AsyncDNSServer_Teensy41](https://github.com/khoih-prog/AsyncDNSServer_Teensy41) page.
2. Download the latest release `AsyncDNSServer_Teensy41-main.zip`.
3. Extract the zip file to `AsyncDNSServer_Teensy41-main` directory 
4. Copy the whole `AsyncDNSServer_Teensy41-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**AsyncDNSServer_Teensy41** library](https://registry.platformio.org/libraries/khoih-prog/AsyncDNSServer_Teensy41) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/AsyncDNSServer_Teensy41/installation). Search for AsyncDNSServer_Teensy41 in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---
---

### Packages' Patches

#### 1. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the files in [**Packages_Patches for Teensy directory**](Packages_Patches/hardware/teensy/avr) into Teensy hardware directory (./arduino-1.8.19/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.19. These files must be copied into the directory:

- `./arduino-1.8.19/hardware/teensy/avr/boards.txt`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy4/Stream.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy4/Stream.h`

---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using `xyz-Impl.h` instead of standard `xyz.cpp`, possibly creates certain `Multiple Definitions` Linker error in certain use cases.

You can include this `.hpp` file

```
// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "AsyncDNSServer_Teensy41.hpp"         //https://github.com/khoih-prog/AsyncDNSServer_Teensy41
```

in many files. But be sure to use the following `.h` file **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "AsyncDNSServer_Teensy41.h"           //https://github.com/khoih-prog/AsyncDNSServer_Teensy41
```

Check the new [**multiFileProject** example](examples/multiFileProject) for a `HOWTO` demo.

Have a look at the discussion in [Different behaviour using the src_cpp or src_h lib #80](https://github.com/khoih-prog/ESPAsync_WiFiManager/discussions/80)


---
---

## HOWTO Setting up the Async DNS Server


```cpp

#include "QNEthernet.h"       // https://github.com/ssilverman/QNEthernet
using namespace qindesign::network;

#include <AsyncDNSServer_Teensy41.h>

const byte DNS_PORT = 53;

IPAddress apIP;

AsyncDNSServer dnsServer;


void setup()
{
  ...
  
  // modify TTL associated  with the domain name (in seconds)
  // default is 60 seconds
  dnsServer.setTTL(300);
  // set which return code will be used for all other domains 
  // (e.g. sending ServerFailure instead of NonExistentDomain will reduce number of queries
  // sent by clients). Default is AsyncDNSReplyCode::NonExistentDomain
  dnsServer.setErrorReplyCode(AsyncDNSReplyCode::ServerFailure);

  // start DNS server for a specific domain name
  dnsServer.start(DNS_PORT, "*", Ethernet.localIP());

  ...
}

void loop() 
{
}

```

---
---


### Examples


 1. [AsyncCaptivePortal](examples/AsyncCaptivePortal)
 2. [AsyncCaptivePortalAdvanced](examples/AsyncCaptivePortalAdvanced)
 3. [AsyncDNServerFull](examples/AsyncDNServerFull) 
 4. [AsyncDNSServer](examples/AsyncDNSServer)
 5. [multiFileProject](examples/multiFileProject)

---

### Example [AsyncDNSServer](examples/AsyncDNSServer)

#### 1. File [AsyncDNSServer.ino](examples/AsyncDNSServer/AsyncDNSServer.ino)


https://github.com/khoih-prog/AsyncDNSServer_Teensy41/blob/2ca8c4f8d45ff01f939ed210f02c60d6e94321fb/examples/AsyncDNSServer/AsyncDNSServer.ino#L12-L115


#### 2. File [defines.h](examples/AsyncDNSServer/defines.h)

https://github.com/khoih-prog/AsyncDNSServer_Teensy41/blob/2ca8c4f8d45ff01f939ed210f02c60d6e94321fb/examples/AsyncDNSServer/defines.h#L12-L45


---
---

### Debug

Debug is enabled by default on Serial. To disable, use level 0

```cpp
#define ASYNC_DNS_TEENSY41_DEBUG_PORT      Serial

// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _ASYNC_DNS_TEENSY41_LOGLEVEL_      0
```

You can also change the debugging level from 0 to 4

```cpp
#define ASYNC_DNS_TEENSY41_DEBUG_PORT      Serial


// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _ASYNC_DNS_TEENSY41_LOGLEVEL_    4
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of Arduino IDE, the Arduino `STM32` core or depending libraries.

Sometimes, the library will only work if you update the `STM32` core to the latest version because I am always using the latest cores /libraries.


---
---


### Issues

Submit issues to: [AsyncDNSServer_Teensy41 issues](https://github.com/khoih-prog/AsyncDNSServer_Teensy41/issues)

---

## TO DO

 1. Fix bug. Add enhancement


## DONE

 1. Initial porting and coding for **Teensy 4.1 using built-in QNEthernet**
 2. Add more examples.
 3. Add debugging features.
 
---
---

### Contributions and Thanks

1. Based on and modified from [Develo's ESPAsyncDNSServer Library](https://github.com/devyte/ESPAsyncDNSServer).


<table>
  <tr>
    <td align="center"><a href="https://github.com/devyte"><img src="https://github.com/devyte.png" width="100px;" alt="devyte"/><br/><sub><b>⭐️ Develo</b></sub></a><br/></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [GPLv3](https://github.com/khoih-prog/AsyncDNSServer_Teensy41/blob/main/LICENSE)

---

## Copyright

- Copyright 2016- Develo
- Copyright 2022- Khoi Hoang

