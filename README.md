# Intercept

## Overview

Intercept is a C/C++ binding interface to the Arma 3 SQF engine (internally refered to as the Real Virtuality or RV engine). It's goal is to provide easy to use library for addon makers to develop addons in a native language, or to develope language extensions for the Arma 3 engine.

Intercept works on a host/client based system, in which the host, Intercept itself, hosts client DLLs that implement the Intercept library. The Intercept host handles access to the RV engine by clients through a layer that provides thread concurrency, memory handling, and event dispatching. Client DLLs are then able to be written in a way that can safely ignore most internal nuances of handling data in the RV engine and work with standard C++ STD/STL data types, and only a few specialized objects (all of which are wrapped in `std::shared_ptr` to properly handle memory releasing).

The intercept library also provides raw C bindings to SQF functionality, so it is entirely possible to use Intercept as the basis for writing in additional scripting languages to the RV engine, such as Python or Lua.

## Technical Details

Intercept works by making direct calls to the SQF functions in the RV engine. To provide concurrency with the game engine, these calls wait until the RV engine is specifically unlocked to Intercept client code, allowing an access window where commands can execute and return results. The only time that these commands are blocked is right before execution, and they unblock very quickly after, providing extremely high throughput in terms of code execution. 

Intercept clients are able to invoke through the host these commands by provided wrapper functions that replicate and emulate the SQF command namespace (minus some unneeded functionality, like arrays or control structures). These wrapper functions take standard inputs, such as simple primitives like `float` or `bool`, and standard `std::string` arguments and convert them into the proper SQF command variables, providing a seamless layer to the clients.

An example of a very simple client that invokes `nular`, `unary`, and `binary` SQF functions (aka functions that take no arguments, a right side argument only, and both a left and right side argument respectively) is demonstrated below and a [fuller example can be found here](src/client).

```c++
#include <Windows.h>
#include <stdio.h>
#include <cstdint>
#include <sstream>

// the Intercept library, only one include required.
#include "intercept.hpp"

// required exported function to return API version
int __cdecl intercept::api_version() {
    return 1;
}

// This function is exported and is called by the host each frame.
void __cdecl intercept::on_frame() {
    // call the SQF random implementation
    float rand_val = intercept::sqf::random(100.0f);
    
    // build a string...
    std::stringstream side_chat_msg;
    side_chat_msg << "Hello Arma World, here is some randomness: " << rand_val;
    
    // send it to the binary SQF sideChat command, using the nular function player as the
    // first argument
    intercept::sqf::side_chat(intercept::sqf::player(), side_chat_msg.str());
}

// Normal Windows DLL junk...
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
    )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
```

## Completion Status

As of now (12/2/15) Intercept is _not_ language feature complete. It still requires that hundreds of wrapper functions be written to facilitate smooth interaction with the RV engine. Most of these will come in the form of simple macros for repititous simple functions (for example any SQF functions that returns nothing, and takes a standard set of simple arguments like `OBJECT` and `SCALAR`), but others will require more hand tuning to take and return relevant results. Also event handling is not completed in any significant fashion, and a structure for handling engine events needs to be implemented.

## Contributions

Feel free to contribute as much as you want to this project in terms of time and code. The goal of this project is to be a tool for the community to provide better performing and more complex addons for the Arma 3 platform.

## License

Intercept is licensed under the GNU/GPL v2 license. You can find the full license in the LICENSE file.
