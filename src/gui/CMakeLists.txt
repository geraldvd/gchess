set(gui_SRCS chessgame.cpp chessboard.cpp chesslabel.cpp promotiondialog.cpp)

# For Ubuntu/gcc - automoc is not working
qt5_wrap_ui(gui_ui_moc promotiondialog.ui)

add_library(${PROJECT_NAME}_gui ${gui_SRCS} ${gui_hdr_moc} ${gui_ui_moc})
target_link_libraries(${PROJECT_NAME}_gui ${QT_LIBS} ${GCHESS_LIBS})
