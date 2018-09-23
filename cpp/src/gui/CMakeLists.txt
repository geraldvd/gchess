if(WITH_QT)
    # Add subdirectories
    add_subdirectory(widgets)
    INCLUDE_DIRECTORIES(widgets)

    add_subdirectory(promotiondialog)
    INCLUDE_DIRECTORIES(promotiondialog)

    add_subdirectory(newgamedialog)
    INCLUDE_DIRECTORIES(newgamedialog)

    # Specify source files
    set(gui_SRCS
        chesswindow.cpp
        chesslabel.cpp

        # Widgets
        widgets/chessboard/chessboard.cpp

        # Dialogs
        promotiondialog/promotiondialog.cpp
        newgamedialog/newgamedialog.cpp
    )

    # For Ubuntu/gcc - automoc is not working
    qt5_wrap_ui(gui_ui_moc
        # Main window
        chesswindow.ui

        # Dialogs
        promotiondialog/promotiondialog.ui
        newgamedialog/newgamedialog.ui
    )

    add_library(${PROJECT_NAME}_gui ${gui_SRCS} ${gui_hdr_moc} ${gui_ui_moc})
    target_link_libraries(${PROJECT_NAME}_gui ${QT_LIBS})# ${GCHESS_LIBS})
endif(WITH_QT)
