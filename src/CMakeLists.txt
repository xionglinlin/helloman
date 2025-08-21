# src/CMakeLists.txt - 源文件定义

# 定义源文件
set(HELLOMAN_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

# 创建可执行文件
qt_add_executable(helloman
    WIN32 MACOSX_BUNDLE
    ${HELLOMAN_SOURCES}
)

# 链接库
target_link_libraries(helloman
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS helloman
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# 安装 desktop 文件
install(FILES ${CMAKE_SOURCE_DIR}/helloman.desktop
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications
)

# 安装图标文件
install(FILES ${CMAKE_SOURCE_DIR}/helloman.svg
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/scalable/apps
) 