project(sepia)
cmake_minimum_required(VERSION 2.8)
find_package(CUDA QUIET REQUIRED)
set(CMAKE_CXX_FLAGS "-std=c++11")
aux_source_directory(. SRC_LIST)
cuda_add_executable(${PROJECT_NAME} main.cpp sepia_cpu_impl.cpp sepia_gpu_impl.cu tgaimage.cpp)

