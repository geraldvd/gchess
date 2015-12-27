#########################################################################
### Qt 5 settings
if(WITH_QT)
    list(APPEND CMAKE_PREFIX_PATH ${BASE_DIR_QT5})
    include_directories(${BASE_DIR_QT5}/include)

    # Qt code generation settings
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)

    find_package(Qt5Core REQUIRED)
    find_package(Qt5Widgets REQUIRED)
    find_package(Qt5Gui REQUIRED)

    # Define Qt Libs
    set(QT_LIBS Qt5::Core)
    set(QT_LIBS ${QT_LIBS} Qt5::Widgets Qt5::Gui)
endif(WITH_QT)

#########################################################################
### Subdirectories
# 3rd party libraries
add_subdirectory(3rdparty)

# Add pieces
add_subdirectory(piece)
include_directories(piece)

# Add board
add_subdirectory(board)
include_directories(board)

# Add engine
add_subdirectory(engine)
include_directories(engine)

# Add player
add_subdirectory(player)
include_directories(player)

# Add gui
if(WITH_QT)
    add_subdirectory(gui)
    include_directories(gui)
endif(WITH_QT)

#########################################################################
### CMake options
# Set c++ defines from cmake options
configure_file(config.h.in ../config.h)
include_directories(${PROJECT_BINARY_DIR})

#########################################################################
### Compilation settings
add_executable(${PROJECT_NAME} 
    main.cpp
    gamemanager.cpp
    utils.cpp
    operators.cpp

    # Board
    board/field.cpp
    board/tile.cpp
    board/move.cpp
    board/board.cpp

    # Pieces
    piece/piece.cpp
    piece/king.cpp
    piece/linepiece.cpp
    piece/queen.cpp
    piece/rook.cpp
    piece/bishop.cpp
    piece/knight.cpp
    piece/pawn.cpp

    # Player
    player/player.cpp
)

if(WITH_QT)
    target_link_libraries(${PROJECT_NAME} ${QT_LIBS})
    target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_gui)
endif(WITH_QT)
