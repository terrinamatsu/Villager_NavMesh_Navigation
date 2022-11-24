cmake_minimum_required(VERSION 3.12)
#-------------------------------------------------------------------------------------------
# I'm going to use vcpk in most cases for our install of 3rd party libs
# this is going to check the environment variable for CMAKE_TOOLCHAIN_FILE and this must point to where
# vcpkg.cmake is in the University this is set in your .bash_profile to
# export CMAKE_TOOLCHAIN_FILE=/public/devel/2020/vcpkg/scripts/buildsystems/vcpkg.cmake
# to build see the NGL instructions 
# Windows :- mkdir build; cd build ; cmake -DCMAKE_PREFIX_PATH=~/NGL/ .. ; cmake --build . 
# Linux / Mac mkdir build; cd build; cmake -DCMAKE_PREFIX_PATH~/NGL/ .. ; make
#-------------------------------------------------------------------------------------------
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

# Name of the project
project(PathFinderBuild)
# This is the name of the Exe change this and it will change everywhere
set(TargetName PathFinder)
# This will include the file NGLConfig.cmake, you need to add the location to this either using
# -DCMAKE_PREFIX_PATH=~/NGL or as a system environment variable. 
find_package(NGL CONFIG REQUIRED)
# Instruct CMake to run moc automatically when needed (Qt projects only)
set(CMAKE_AUTOMOC ON)
# find Qt libs
# find Qt libs first we check for Version 6
find_package(Qt6 COMPONENTS OpenGL Widgets QUIET )
if ( Qt6_FOUND )
    message("Found Qt6 Using that")
else()
    message("Found Qt5 Using that")
    find_package(Qt5 COMPONENTS OpenGL Widgets REQUIRED)
endif()

# use C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

find_package(Python COMPONENTS Interpreter Development)

# Set the name of the executable we want to build
add_executable(${TargetName})

## as we are using python we can't use the keyword slots	
ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

# Add NGL include path
include_directories(include $ENV{HOME}/NGL/include)

target_sources(${TargetName} PRIVATE ${PROJECT_SOURCE_DIR}/src/main.cpp  
			${PROJECT_SOURCE_DIR}/src/NGLScene.cpp
            ${PROJECT_SOURCE_DIR}/src/Village.cpp  
			${PROJECT_SOURCE_DIR}/src/Villager.cpp
            ${PROJECT_SOURCE_DIR}/src/NGLSceneMouseControls.cpp  
            ${PROJECT_SOURCE_DIR}/src/Random.cpp
            ${PROJECT_SOURCE_DIR}/src/NavMesh.cpp
			${PROJECT_SOURCE_DIR}/include/NGLScene.h  
            ${PROJECT_SOURCE_DIR}/include/Symedge.h
            ${PROJECT_SOURCE_DIR}/include/Village.h
            ${PROJECT_SOURCE_DIR}/include/Villager.h
            ${PROJECT_SOURCE_DIR}/include/Random.h
            ${PROJECT_SOURCE_DIR}/include/NavMesh.h
            ${PROJECT_SOURCE_DIR}/include/Waypoint.h
            ${PROJECT_SOURCE_DIR}/include/NavTriangle.h
            ${PROJECT_SOURCE_DIR}/shaders/ColourVertex.glsl
            ${PROJECT_SOURCE_DIR}/shaders/ColourFragment.glsl
)

target_link_libraries(${TargetName} PRIVATE Qt::Widgets Qt::OpenGL NGL)
target_link_libraries(${TargetName} PRIVATE ${PROJECT_LINK_LIBS}  Python::Python)# -lpthread -ldl  -lutil -lm -L/opt/homebrew/lib -lgettextpo )

# Add Tests
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
enable_testing()

add_executable(VillagerTests)
target_sources(VillagerTests PRIVATE 
                ${PROJECT_SOURCE_DIR}/tests/VillagerTests.cpp
                ${PROJECT_SOURCE_DIR}/src/Random.cpp
                ${PROJECT_SOURCE_DIR}/src/Villager.cpp
                ${PROJECT_SOURCE_DIR}/include/Villager.h
                ${PROJECT_SOURCE_DIR}/include/Random.h)
target_link_libraries(VillagerTests PRIVATE GTest::gtest GTest::gtest_main Python::Python)
gtest_discover_tests(VillagerTests)

add_executable(NavigationTests)
target_sources(NavigationTests PRIVATE 
                ${PROJECT_SOURCE_DIR}/tests/NavigationTests.cpp
                ${PROJECT_SOURCE_DIR}/src/Random.cpp
                ${PROJECT_SOURCE_DIR}/src/NavMesh.cpp
                ${PROJECT_SOURCE_DIR}/include/Random.h
                ${PROJECT_SOURCE_DIR}/include/NavMesh.h
                ${PROJECT_SOURCE_DIR}/include/Waypoint.h
                ${PROJECT_SOURCE_DIR}/include/NavTriangle.h)
target_link_libraries(NavigationTests PRIVATE GTest::gtest GTest::gtest_main)
gtest_discover_tests(NavigationTests)


# Copy across shader files
add_custom_target(${TargetName}CopyShaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders
    $<TARGET_FILE_DIR:${TargetName}>/shaders
)

# Copy across python script files
add_custom_target(${TargetName}CopyPythonScripts ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/python
    $<TARGET_FILE_DIR:${TargetName}>/python
)

