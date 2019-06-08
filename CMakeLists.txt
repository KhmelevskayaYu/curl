cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include("cmake/HunterGate.cmake")
huntergate(
  URL "https://github.com/ruslo/hunter/archive/v0.23.83.tar.gz"
  SHA1 "12dec078717539eb7b03e6d2a17797cba9be9ba9"
)

project(download)
hunter_add_package(CURL)
find_package(CURL CONFIG REQUIRED)


add_executable(download sources/download.cpp)

target_link_libraries(download CURL::libcurl)













