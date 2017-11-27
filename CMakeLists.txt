
cmake_minimum_required(VERSION 2.8.12)
set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -std=c++11 -g")
# Every project needs a name.  We call this the "examples" project.
project(dip)

# Add include directory for the .h file search path
include_directories(include)

# Header files from external/online sources
include_directories(external)

# Eigen
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
MESSAGE(STATUS "eigen3 include: ${EIGEN3_INCLUDE_DIRS}")


# PANGOLIN
find_package(Pangolin REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})
MESSAGE(STATUS "pangolin include: ${Pangolin_INCLUDE_DIRS}")

# Matplotlib wrapper
find_package(PythonLibs 2.7)
include_directories(${PYTHON_INCLUDE_DIRS})
MESSAGE(STATUS "Python include: ${PYTHON_INCLUDE_DIRS}")
MESSAGE(STATUS "Python libraries: ${PYTHON_LIBRARIES}")

# OpenCV
#find_package(Opencv REQUIRED)
#MESSAGE(STATUS "Include dirs ${OpenCV_INCLUDE_DIRS}")
#MESSAGE(STATUS "LINK LIBRARIES ${OpenCV_LIBS}")

# The next thing we need to do is tell CMake about the code you want to
# compile.  We do this with the add_executable() statement which takes the name
# of the output executable and then a list of .cpp files to compile.  Here we
# are going to compile one of the dlib example programs which has only one .cpp
# file, assignment_learning_ex.cpp.  If your program consisted of multiple .cpp
# files you would simply list them here in the add_executable() statement.  
set(SRCS
        #contains main
#        src/main.cpp
        #        test/test_image_proc.cpp
        #         experiments/helloOpenCV.cpp
        #        test/test_glWindow.cpp #needs src/glad.c and target_link_libraries with glfw
#        test/test_image.cpp
#                test/test_pangolin_plot.cpp
        test/test_imageOperations.cpp
#        test/test_filter.cpp
#        test/test_otherFilters.cpp
#         test/test_sparseMtx.cpp
#         test/test_gauss_seidel.cpp
#        test/test_matplotlibcpp.cpp

        external/lodepng.cpp
        src/Image.cpp
        src/Grid.cpp
        src/Filter.cpp #todo: finish this
        src/imageOperations.cpp
        src/proc.cpp
        src/levelset.cpp

#        src/meshProc.cpp


        )

add_executable(main ${SRCS})

#link python libraries for matplotlibcpp
set(NUMPY_INCLUDE_DIR
        "/usr/local/lib/python2.7/site-packages/numpy/core/include")
MESSAGE(STATUS "Numpy include dir: ${NUMPY_INCLUDE_DIR}")
target_include_directories(main
        PRIVATE ${PYTHON_INCLUDE_DIRS}
                ${NUMPY_INCLUDE_DIR})

# Finally, you need to tell CMake that this program, assignment_learning_ex,
# depends on dlib.  You do that with this statement: 
target_link_libraries(main
        ${Pangolin_LIBRARIES}
        ${PYTHON_LIBRARIES} #matplotlib
#        ${OpenCV_LIBS}
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






