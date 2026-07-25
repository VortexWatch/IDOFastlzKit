========================================================================
                             IDOFastlzKit SDK
========================================================================

IDOFastlzKit is an open-source high-speed compression dynamic library
tailored for embedded assets, VeryFit watch faces (.iwf), and stream transfer pipelines.

This package contains the precompiled binary release for Windows 
integration (C/C++).

------------------------------------------------------------------------
1. PACKAGE CONTENTS
------------------------------------------------------------------------

IDOFastlzKit_SDK/
│    IDOFastlzKit.h      # Public API Header
│    IDOFastlzKit.lib    # MSVC Import Library
│    IDOFastlzKit.dll    # Dynamic Link Library
└── README.txt


------------------------------------------------------------------------
2. INTEGRATION
------------------------------------------------------------------------

--- MSVC / Visual Studio Project Setup ---

1. Add the `include/` directory to your project's Additional Include Directories:
   Properties -> C/C++ -> General -> Additional Include Directories

2. Add the `lib/` directory to your project's Additional Library Directories:
   Properties -> Linker -> General -> Additional Library Directories

3. Add `IDOFastlzKit.lib` to Additional Dependencies:
   Properties -> Linker -> Input -> Additional Dependencies

4. Copy `IDOFastlzKit.dll` into your application's output directory 
   (where your `.exe` runs) or system PATH.


--- CMake Integration ---

If your project uses CMake, configure it to consume the precompiled binaries:

    cmake_minimum_required(VERSION 3.18)
    project(MyProject LANGUAGES C CXX)

    set(SDK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/path/to/IDOFastlzKit_SDK")

    # Include paths
    include_directories("${SDK_DIR}/include")

    # Import the precompiled DLL
    add_library(IDOFastlzKit SHARED IMPORTED)
    set_target_properties(IDOFastlzKit PROPERTIES
        IMPORTED_IMPLIB "${SDK_DIR}/lib/IDOFastlzKit.lib"
        IMPORTED_LOCATION "${SDK_DIR}/bin/IDOFastlzKit.dll"
    )

    add_executable(MyTarget main.cpp)
    target_link_libraries(MyTarget PRIVATE IDOFastlzKit)

    # Post-build step to copy DLL alongside executable
    add_custom_command(TARGET MyTarget POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDK_DIR}/bin/IDOFastlzKit.dll"
        $<TARGET_FILE_DIR:MyTarget>
    )


------------------------------------------------------------------------
3. CODE EXAMPLES
------------------------------------------------------------------------

--- Example 1: Buffer Block Compression ---

    #include <IDOFastlzKit.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    void compress_buffer_demo(void) {
        const char *raw_data = "Data block to compress...";
        int raw_size = (int)strlen(raw_data) + 1;
        uint32_t block_size = 1024; // 1 KB block size

        // Allocate buffer with required padding
        int max_out = raw_size + FASTLZ_BUFFER_PADDING(raw_size);
        void *compressed_buf = malloc(max_out);

        int compressed_size = fastlz_util_compress_buff(
            raw_data, 
            compressed_buf, 
            raw_size, 
            block_size
        );

        if (compressed_size > 0) {
            printf("Compressed %d bytes -> %d bytes\n", raw_size, compressed_size);
        } else {
            printf("Compression failed.\n");
        }

        free(compressed_buf);
    }


--- Example 2: File Block Compression & Decompression ---

    #include <IDOFastlzKit.h>
    #include <stdio.h>

    void compress_file_demo(void) {
        FILE *in = fopen("watchface.iwf", "rb");
        FILE *out = fopen("watchface.iwf.lz", "wb");

        if (in && out) {
            // Block size usually matching device packet limits (e.g., 4096)
            int ret = fastlz_util_compress_file(in, out, 4096);
            if (ret == 0) {
                printf("File compression complete.\n");
            }
        }

        if (in) fclose(in);
        if (out) fclose(out);
    }

    void decompress_file_demo(void) {
        FILE *in = fopen("watchface.iwf.lz", "rb");
        FILE *out = fopen("watchface_decomp.iwf", "wb");

        if (in && out) {
            int ret = fastlz_util_decompress_file(in, out, 4096);
            if (ret == 0) {
                printf("File decompression complete.\n");
            }
        }

        if (in) fclose(in);
        if (out) fclose(out);
    }


------------------------------------------------------------------------
4. LOGGING SETUP
------------------------------------------------------------------------

To enable internal console output during development:

    #include <IDOFastlzKit.h>

    int main(void) {
        // Enable console output, disable file log writing
        debug_log_init(true, false, NULL);
        cur_debug_level = DEBUG_LEVEL_INFO;

        // Your code here...

        return 0;
    }


------------------------------------------------------------------------
5. LICENSE
------------------------------------------------------------------------

This SDK wraps FastLZ and IDO Code technology (GNU General Public License v3.0).

========================================================================