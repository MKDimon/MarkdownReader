cmake_minimum_required(VERSION 3.14)

project(MarkdownReader VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick LinguistTools Multimedia Concurrent)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick LinguistTools Multimedia Concurrent)

include_directories(${CMAKE_SOURCE_DIR}/3rdParty/include)
include_directories(${CMAKE_SOURCE_DIR}/3rdParty/libs)
add_library(cmark STATIC IMPORTED)
set_target_properties(cmark PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/3rdParty/libs/libcmark.so)

set(TS_FILES MarkdownReader_ru_RU.ts)

set(PROJECT_SOURCES
        main.cpp
        qml.qrc
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MarkdownReader
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
   # set_property(TARGET MarkdownReader APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
   #              ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(MarkdownReader SHARED
            ${PROJECT_SOURCES}
            blockmodel.h blockmodel.cpp
            customblockhandler.h
            block.h block.cpp
            warningblock.h warningblock.cpp
            videoblock.h videoblock.cpp
            blocks.h
            warningblockhandler.h warningblockhandler.cpp
            videoblockhandler.h videoblockhandler.cpp
            textblockhandler.h textblockhandler.cpp
            blockhandlers.h
            markdownprocessor.h markdownprocessor.cpp
            documenttreemodel.h documenttreemodel.cpp
            documenttreeitem.h documenttreeitem.cpp
        )
# Define properties for Android with Qt 5 after find_package() calls as:
    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MarkdownReader
          ${PROJECT_SOURCES}
          blockmodel.h blockmodel.cpp
          customblockhandler.h
          block.h block.cpp
          warningblock.h warningblock.cpp
          videoblock.h videoblock.cpp
          blocks.h
          warningblockhandler.h warningblockhandler.cpp
          videoblockhandler.h videoblockhandler.cpp
          textblockhandler.h textblockhandler.cpp
          blockhandlers.h
          markdownprocessor.h markdownprocessor.cpp
          documenttreemodel.h documenttreemodel.cpp
          documenttreeitem.h documenttreeitem.cpp
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(MarkdownReader
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::Concurrent)
target_link_libraries(MarkdownReader PRIVATE cmark)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.MarkdownReader)
endif()
set_target_properties(MarkdownReader PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS MarkdownReader
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(MarkdownReader)
    qt_finalize_executable(MarkdownReader)
endif()
