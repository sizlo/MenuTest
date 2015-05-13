cmake_minimum_required (VERSION 3.2)

# Use c++11
set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

# Set up project
project (MenuTest)

# Set up vars
set(TIM_GAME_LIB_ROOT "$ENV{TIM_GAME_LIB_ROOT}")
if (NOT TIM_GAME_LIB_ROOT)
	message(FATAL_ERROR "TIM_GAME_LIB_ROOT not defined")
endif()
set(SFML_ROOT "$ENV{SFML_ROOT}")
if (NOT SFML_ROOT)
	message(FATAL_ERROR "SFML_ROOT not defined")
endif()

# CCMake modules
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake;${TIM_GAME_LIB_ROOT}/CMake")

# We want to use cotire for precompiled header
include(cotire)

# Find and include SFML
find_package(SFML 2.2 COMPONENTS graphics window system audio network)
include_directories(${SFML_INCLUDE_DIR})

# Include TimGameLib
include(TimGameLib)
include_directories(${TIM_GAME_LIB_ROOT}/Source)

# Include self
include_directories(Source)

# Locate all recourses
FILE(GLOB RESOURCE_FILES ${PROJECT_SOURCE_DIR}/Data/*)

# Mark resource files as resources
if (APPLE)
  set_source_files_properties(
    "${RESOURCE_FILES}"
    PROPERTIES
    MACOSX_PACKAGE_LOCATION Resources
  )
endif()

# MenuTest executable target
add_executable(MenuTest MACOSX_BUNDLE 
  Source/CMenuTest.cpp
  Source/CMenuTest.hpp
  Source/CPong.cpp
  Source/CPong.hpp
  Source/CFrontEnd.cpp
  Source/CFrontEnd.hpp
  Source/Main.cpp
  Source/MenuTest-Prefix.pch
  Source/CPauseMenu.cpp
  Source/CPauseMenu.hpp
  ${RESOURCE_FILES}
)

# TimGameLib library target depency
add_library(TimGameLib ${TIM_GAME_LIB_SOURCES})
add_dependencies(MenuTest TimGameLib)

if (WIN32)
	# Link Shlwapi.lib for finding exe path
	target_link_libraries(MenuTest Shlwapi.lib)

  # Copy resource files to exe folder
  foreach(RES ${RESOURCE_FILES})
    add_custom_command(
      TARGET MenuTest POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E
        copy_if_different ${RES} $<TARGET_FILE_DIR:MenuTest>
    )
  endforeach()
elseif(APPLE)
	# Link Foundation.framework for finding bundle path
	find_library(FOUNDATION_FRAMEWORK Foundation)
	target_link_libraries(MenuTest ${FOUNDATION_FRAMEWORK})

  # Add the resources to the bundle
  set_target_properties(MenuTest PROPERTIES RESOURCE "${RESOURCE_FILES}")
endif()

# Link SFML
target_link_libraries(MenuTest ${SFML_LIBRARIES})

# Link TimGameLib
target_link_libraries(MenuTest TimGameLib)

# Use cotire for precompiled header
set_target_properties(MenuTest PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "Source/MenuTest-Prefix.pch")
cotire(MenuTest)
set_target_properties(TimGameLib PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "${TIM_GAME_LIB_ROOT}/Source/TimGameLib_Prefix.pch")
cotire(TimGameLib)