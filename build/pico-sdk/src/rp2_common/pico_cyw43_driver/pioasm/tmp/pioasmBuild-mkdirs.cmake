# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/mac/Documents/PicoWorkspace/Pico/tools/pioasm"
  "/Users/mac/Documents/PicoWorkspace/MoonlitCalc/build/pioasm"
  "/Users/mac/Documents/PicoWorkspace/MoonlitCalc/build/pioasm-install"
  "/Users/mac/Documents/PicoWorkspace/MoonlitCalc/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/tmp"
  "/Users/mac/Documents/PicoWorkspace/MoonlitCalc/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp"
  "/Users/mac/Documents/PicoWorkspace/MoonlitCalc/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src"
  "/Users/mac/Documents/PicoWorkspace/MoonlitCalc/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/mac/Documents/PicoWorkspace/MoonlitCalc/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp/${subDir}")
endforeach()
