#########################################################################
### Qt 5 settings
list(APPEND CMAKE_PREFIX_PATH ${BASE_DIR_QT5})
include_directories(${BASE_DIR_QT5}/include)

# Qt code generation settings
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Qt5Core REQUIRED)
if(WITH_GRAPHICS)
    find_package(Qt5Widgets REQUIRED)
    find_package(Qt5Gui REQUIRED)
endif()

# Define Qt Libs
set(QT_LIBS Qt5::Core)
if(WITH_GRAPHICS)
    set(QT_LIBS ${QT_LIBS} Qt5::Widgets Qt5::Gui)
endif()

#########################################################################
### Subdirectories

## Add include directory
#add_subdirectory(include) # For Qt Creator
#include_directories(include)

# 3rd party libraries
add_subdirectory(3rdparty)

# Add game library
if(WITH_GAME)
    add_subdirectory(game)
    include_directories(game)
endif()

# Add engine library
if(WITH_ENGINE)
    add_subdirectory(engine)
    include_directories(engine)
endif()

# Add gui library
if(WITH_GRAPHICS)
    add_subdirectory(gui)
    include_directories(gui)
endif()

#########################################################################
### CMake options
# Set c++ defines from cmake options
# TODO config.h is not found by Qt Creator
configure_file(config.h.in ../config.h)
include_directories(${PROJECT_BINARY_DIR})

#########################################################################
### Compilation settings
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${GCHESS_LIBS} ${QT_LIBS})
if(WITH_GRAPHICS)
    target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_gui)
endif()
