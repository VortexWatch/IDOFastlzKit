# IDOFastlzKit SDK

[![License: GPL v3](https://shields.io)](https://gnu.org)
[![Target Platform](https://shields.io)]()
[![Ecosystem](https://shields.io)]()

An open-source, high-speed chunk-compression dynamic library tailored for embedded binary assets, proprietary firmware streaming pipelines, and **VeryFit `.iwf / .iwf.lz` watch face container packaging**. 

`IDOFastlzKit` decouples IDO's custom block-based compression algorithms—originally locked inside native compiler asset tools—into a universal, modular SDK for standalone C/C++ desktop integration.
---

## 🛠️ Integration Architecture

### CMake Build Definition
To consume the precompiled shared library binaries seamlessly inside modern C/C++ cross-platform compiler environments, inject this configuration block directly into your `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.18)
project(IwfToolchain LANGUAGES C CXX)

# Define SDK Root Mapping
set(SDK_DIR "\${CMAKE_CURRENT_SOURCE_DIR}/path/to/IDOFastlzKit_SDK")
include_directories("\${SDK_DIR}/include")

# Register Imported Shared Binary Target
add_library(IDOFastlzKit SHARED IMPORTED)
set_target_properties(IDOFastlzKit PROPERTIES
    IMPORTED_IMPLIB "\${SDK_DIR}/lib/IDOFastlzKit.lib"
    IMPORTED_LOCATION "\${SDK_DIR}/bin/IDOFastlzKit.dll"
)

# Bind Target Executable
add_executable(IwfPacker main.cpp)
target_link_libraries(IwfPacker PRIVATE IDOFastlzKit)

# Automate Runtime Post-Build DLL Relocation
add_custom_command(TARGET IwfPacker POST_BUILD
    COMMAND \${CMAKE_COMMAND} -E copy_if_different
    "\${SDK_DIR}/bin/IDOFastlzKit.dll"
    \$<TARGET_FILE_DIR:IwfPacker>
)
```

---

## 💻 API Code Implementations

### Real-Time File Stream Extraction (`.iwf.lz` ➡️ `.iwf`)
Extract layout structures from official server-side compressed dial face bundles fetched directly over active transport channels:

```c
#include <IDOFastlzKit.h>
#include <stdio.h>

void unpack_device_dial(const char* packed_source, const char* extracted_out) {
    FILE *in = fopen(packed_source, "rb");
    FILE *out = fopen(extracted_out, "wb");

    if (in && out) {
        // IDO standard system block size limits default to 4096 bytes
        int result = fastlz_util_decompress_file(in, out, 4096);
        if (result == 0) {
            printf("[+] Success: Extracted native layout matrix container.\n");
        } else {
            printf("[-] Error: Chunk decompression validation failed.\n");
        }
    }

    if (in) fclose(in);
    if (out) fclose(out);
}
```

---

## ⚖️ Legal Framework & License

`IDOFastlzKit` is open-source software licensed strictly under the terms of the **GNU General Public License v3.0 (GPL-3.0)**. 

* **The Copyleft Firewall:** Any downstream tools, modification branches, or commercial utilities that link into `IDOFastlzKit` are legally bound to completely release their source changes under the same license terms.
* **Liability Disclaimer:** This software is provided **"AS IS" without warranty of any kind**. VortexWatch Studio carries no liability for system crashes, battery loops, or firmware panel faults induced on target hardware.

***
Developed & Maintained by **VortexWatch Studio** | Contact Hub: `vortexwatch@proton.me`
