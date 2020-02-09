cmake_minimum_required(VERSION 3.10)
project(ray)

set(headers
  TKPrefix.h
  TKMath.h
  TKRay.h
  TKHitable.h
  TKSphere.h
  TKMaterial.h
  TKHitableList.h)

set(sources
  TKMath.cpp
  TKRay.cpp
  TKSphere.cpp
  TKHitableList.cpp
  TKMaterial.cpp
  rayTest.cpp
  )

include_directories("/usr/local/include/")

add_executable(rayTest ${headers} ${sources})

