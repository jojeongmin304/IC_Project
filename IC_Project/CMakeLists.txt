cmake_minimum_required(VERSION 3.16)

project(IC_Project VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appIC_Project
    main.cpp
)

qt_add_qml_module(appIC_Project
    URI IC_Project
    VERSION 1.0
    QML_FILES
        Main.qml
        QML_FILES InstrumentCluster.qml
        QML_FILES Gear.qml
        RESOURCES image.qrc
        RESOURCES qml.qrc
        QML_FILES LeftCluster.qml
        QML_FILES RightCluster.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appIC_Project PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appIC_Project
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appIC_Project
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appIC_Project
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
