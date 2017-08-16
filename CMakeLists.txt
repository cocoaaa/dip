
cmake_minimum_required(VERSION 2.8.12)
# Every project needs a name.  We call this the "examples" project.
project(dip)

# Add include directory for the .h file search path
include_directories(include)

# Tell cmake we will need dlib.  This command will pull in dlib and compile it
# into your project.  Note that you don't need to compile or install dlib.  All
# it needs is the dlib source code folder and it will take care of everything.
#include(/Local/Users/hjsong/Playground/dlib/dlib/cmake)

# Header files from online sources
include_directories(external external/glad/include)

# Eigen
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

# PANGOLIN
find_package(Pangolin REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})
MESSAGE(STATUS "pangolin include: ${Pangolin_INCLUDE_DIRS}")


# OpenCV
find_package(Opencv REQUIRED)
MESSAGE(STATUS "Include dirs ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "LINK LIBRARIES ${OpenCV_LIBS}")

#message(${Pangolin_LIBRARIES})
#message(${Pangolin_CONFIG})
#include_directories(${Pangolin_DIR/include} ${Pangolin_INCLUDE_DIR}/../../include)
#ADD_DEFINITIONS(-D DLIB_NO_GUI_SUPPORT=0)

# The next thing we need to do is tell CMake about the code you want to
# compile.  We do this with the add_executable() statement which takes the name
# of the output executable and then a list of .cpp files to compile.  Here we
# are going to compile one of the dlib example programs which has only one .cpp
# file, assignment_learning_ex.cpp.  If your program consisted of multiple .cpp
# files you would simply list them here in the add_executable() statement.  
set(SRCS
#        src/main.cpp
#         src/glad.c
        include/Image.h src/Image.cpp
         test/test_image.cpp
#         experiments/helloOpenCV.cpp
#         src/helloWindow.cpp

        )
add_executable(main ${SRCS})
# Finally, you need to tell CMake that this program, assignment_learning_ex,
# depends on dlib.  You do that with this statement: 
target_link_libraries(main
#        dlib::dlib
        glfw
        ${GLFW_LIBRARIES}
        ${Eigen_LIBRARIES}
        ${Pangolin_LIBRARIES}
        ${OpenCV_LIBS}
        )
#Note: Eigen_LIBRARIES is not required



# To compile this program all you need to do is ask cmake.  You would type
# these commands from within the directory containing this CMakeLists.txt
# file:
#   mkdir build
#   cd build
#   cmake ..
#   cmake --build . --config Release
#
# The cmake .. command looks in the parent folder for a file named
# CMakeLists.txt, reads it, sets up everything needed to build program.  Also,
# note that CMake can also generate Visual Studio or XCode project files.  So
# if instead you had written:
#   mkdir build
#   cmake .. -G "Visual Studio 14 2015 Win64" ..
#
# You would be able to open the resulting visual studio project and compile and
# edit the example programs within the visual studio IDE.  CMake can generate a
# lot of different types of IDE projects.  Run the cmake -h command to see a list
# of arguments to -G to see what kinds of projects cmake can generate for you.
# It probably includes your favorite IDE in the list.






