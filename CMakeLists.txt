cmake_minimum_required(VERSION 3.14.0)
set(CMAKE_CXX_STANDARD 17)

project(dsc)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Auto-run MOC and UIC when needed
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# Set OpenGL legacy preference
set(OpenGL_GL_PREFERENCE GLVND)

#output more error information
#set(CMAKE_VERBOSE_MAKEFILE ON)

# Find libraries
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenCV REQUIRED)
find_package(CUDA 9.0 REQUIRED)
find_package(Caffe REQUIRED)
find_package(dlib 19.17 REQUIRED)
find_package(CGAL REQUIRED COMPONENTS Core)
find_package(glm 0.9.9 REQUIRED)


#Liu added on 2019/06/26
find_package(GLUT REQUIRED)
FIND_PACKAGE(GDAL REQUIRED)
find_package(PythonLibs REQUIRED)
find_package(Qt5Test REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS})
include_directories( ${GLUT_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES(${GDAL_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${PYTHON_INCLUDE_DIRS})
#include_directories(/home/liuhe95/Documents/demo/DSC-master/src)
#include_directories(/home/liuhe95/Documents/demo/DSC-master/src/3rdparty/include)


include_directories(${Caffe_INCLUDE_DIRS})
include_directories(${CUDA_INCLUDE_DIRS})
#include_directories(Qt5::Test)
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)
add_definitions(-DGLM_FORCE_CTOR_INIT)


# Get sources
file(GLOB SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB NVSOURCES CONFIGURE_DEPENDS src/nvModel/*.cpp)
file(GLOB QRC CONFIGURE_DEPENDS src/*.qrc)
file(GLOB UIS src/*.ui)
file(GLOB HEADER src/*.h)

QT5_ADD_RESOURCES(QRC_RESOURCES ${QRC})
QT5_WRAP_UI(UI_RS ${UIS})
QT5_WRAP_CPP(QHEADER ${HEADER})

SET(DSC_SRCS ${SOURCES} ${NVSOURCES} ${QHEADER} ${QRC_RESOURCES} ${UI_RS})

#Liu last modified on 2019/06/27
add_executable(${PROJECT_NAME} ${DSC_SRCS})
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::OpenGL)
target_link_libraries(${PROJECT_NAME} Qt5::Xml)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} ${Caffe_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${CUDA_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${DLIB_LIBRARIES} dlib)
target_link_libraries(${PROJECT_NAME} CGAL::CGAL CGAL::CGAL_Core)

#Liu added on 2019/06/26
target_link_libraries(${PROJECT_NAME} ${GLUT_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GDAL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})
target_link_libraries(${PROJECT_NAME} Qt5::Test)

