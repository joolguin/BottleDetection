# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/jose/esp/idf/esp-idf/components/bootloader/subproject"
  "/Users/jose/esp/projects_tf/bottle_detection/build/bootloader"
  "/Users/jose/esp/projects_tf/bottle_detection/build/bootloader-prefix"
  "/Users/jose/esp/projects_tf/bottle_detection/build/bootloader-prefix/tmp"
  "/Users/jose/esp/projects_tf/bottle_detection/build/bootloader-prefix/src/bootloader-stamp"
  "/Users/jose/esp/projects_tf/bottle_detection/build/bootloader-prefix/src"
  "/Users/jose/esp/projects_tf/bottle_detection/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/jose/esp/projects_tf/bottle_detection/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/jose/esp/projects_tf/bottle_detection/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
