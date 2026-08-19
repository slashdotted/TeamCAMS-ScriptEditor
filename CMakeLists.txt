cmake_minimum_required(VERSION 3.5)

project(
  TeamCAMSScriptEditor
  VERSION 2026.8
  LANGUAGES C CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_COMPONENTS Widgets LinguistTools Svg)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CONFIG MATCHES "Debug")
  set(ENABLE_QT_TEST TRUE)
  list(APPEND QT_COMPONENTS Test)
else()
  set(ENABLE_QT_TEST FALSE)
endif()

if(EMSCRIPTEN)
  list(APPEND QT_COMPONENTS WebSockets)
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS ${QT_COMPONENTS})

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS ${QT_COMPONENTS})

set(TS_FILES i18n/teamcamsscripteditor_it.ts i18n/teamcamsscripteditor_fr.ts
             i18n/teamcamsscripteditor_de.ts i18n/teamcamsscripteditor_es.ts)

add_custom_target(
  release_translations
  COMMAND lrelease ${TS_FILES}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

set(TEST_SOURCES
    src/tests/testadaptiveelementeditor.cpp
    src/tests/testassistanceelementeditor.cpp
    src/tests/testcodeelementeditor.cpp
    src/tests/testcontrolelementeditor.cpp
    src/tests/testerrorelementeditor.cpp
    src/tests/testfilterelementeditor.cpp
    src/tests/testinterfaceelementeditor.cpp
    src/tests/testquestionelementeditor.cpp
    src/tests/testpopupelementeditor.cpp
    src/tests/testscriptelementeditor.cpp
    src/tests/testmessageelementeditor.cpp
    src/tests/testaccesselementeditor.cpp
    src/tests/testadaptiveelementeditor.h
    src/tests/testassistanceelementeditor.h
    src/tests/testcodeelementeditor.h
    src/tests/testcontrolelementeditor.h
    src/tests/testerrorelementeditor.h
    src/tests/testfilterelementeditor.h
    src/tests/testinterfaceelementeditor.h
    src/tests/testquestionelementeditor.h
    src/tests/testpopupelementeditor.h
    src/tests/testscriptelementeditor.h
    src/tests/testmessageelementeditor.h
    src/tests/testaccesselementeditor.h)

set(PROJECT_SOURCES
    ${TS_FILES}
    src/main.cpp
    src/editors/filterelementeditor.cpp
    src/editors/popupelementeditor.cpp
    src/gui/mainwindow.cpp
    src/gui/timelinewidget.cpp
    src/editors/scriptelementeditor.cpp
    src/io/xmlconfighandler.cpp
    src/models/elementlist.cpp
    src/models/element.cpp
    src/editors/errorelementeditor.cpp
    src/editors/interfaceelementeditor.cpp
    src/editors/adaptiveelementeditor.cpp
    src/editors/codeelementeditor.cpp
    src/editors/durationelementeditor.cpp
    src/editors/controlelementeditor.cpp
    src/editors/questionelementeditor.cpp
    src/editors/assistanceelementeditor.cpp
    src/editors/messageelementeditor.cpp
    src/editors/accesselementeditor.cpp
    src/editors/editor.cpp
    src/io/xmlconfigwriter.cpp
    src/gui/mainwindow.h
    src/gui/timelinewidget.h
    src/editors/filterelementeditor.h
    src/editors/popupelementeditor.h
    src/editors/scriptelementeditor.h
    src/io/xmlconfighandler.h
    src/models/elementlist.h
    src/models/element.h
    src/editors/errorelementeditor.h
    src/editors/interfaceelementeditor.h
    src/editors/adaptiveelementeditor.h
    src/editors/codeelementeditor.h
    src/editors/durationelementeditor.h
    src/editors/controlelementeditor.h
    src/editors/questionelementeditor.h
    src/editors/assistanceelementeditor.h
    src/editors/messageelementeditor.h
    src/editors/accesselementeditor.h
    src/editors/editor.h
    src/io/xmlconfigwriter.h
    src/gui/mainwindow.ui
    src/editors/filterelementeditor.ui
    src/editors/popupelementeditor.ui
    src/editors/scriptelementeditor.ui
    src/editors/errorelementeditor.ui
    src/editors/interfaceelementeditor.ui
    src/editors/adaptiveelementeditor.ui
    src/editors/codeelementeditor.ui
    src/editors/durationelementeditor.ui
    src/editors/controlelementeditor.ui
    src/editors/questionelementeditor.ui
    src/editors/assistanceelementeditor.ui
    src/editors/messageelementeditor.ui
    src/editors/accesselementeditor.ui)

if(ENABLE_QT_TEST)
  list(APPEND PROJECT_SOURCES ${TEST_SOURCES})
endif()

set(ICON_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/assets/app_icon.ico")
set(ICON_MACOS "${CMAKE_CURRENT_SOURCE_DIR}/assets/app_icon.icns")
set(ICON_LINUX "${CMAKE_CURRENT_SOURCE_DIR}/assets/app_icon.png")

if(WIN32)
  set(RES_FILE "${CMAKE_CURRENT_BINARY_DIR}/app_icon.rc")
  file(WRITE "${RES_FILE}" "IDI_ICON1 ICON DISCARDABLE \"${ICON_WINDOWS}\"\n")
  list(APPEND PROJECT_SOURCES "${RES_FILE}")
endif()

if(APPLE)
  list(APPEND PROJECT_SOURCES "${ICON_MACOS}")
  set_source_files_properties("${ICON_MACOS}" PROPERTIES MACOSX_PACKAGE_LOCATION
                                                         Resources)
endif()

qt_add_executable(TeamCAMSScriptEditor MANUAL_FINALIZATION ${PROJECT_SOURCES}
                  src/resources.qrc)

target_compile_definitions(
  TeamCAMSScriptEditor PRIVATE $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
                               $<$<CONFIG:MinSizeRel>:QT_NO_DEBUG_OUTPUT>)

if(ENABLE_QT_TEST)
  target_compile_definitions(TeamCAMSScriptEditor PRIVATE QT_TEST_ENABLED)
else()
  target_compile_definitions(TeamCAMSScriptEditor PRIVATE)
endif()

# Enable if required target_compile_options( TeamCAMSScriptEditor PRIVATE
# -fsanitize=address -fno-omit-frame-pointer) target_link_options(
# TeamCAMSScriptEditor PRIVATE -fsanitize=address)

if(EMSCRIPTEN)
  target_compile_definitions(TeamCAMSScriptEditor PRIVATE NO_WEBSOCKET_SERVER)
  target_link_options(TeamCAMSScriptEditor PRIVATE "-lidbfs.js")
endif()

qt_add_translations(TeamCAMSScriptEditor TS_FILES ${TS_FILES})

target_include_directories(TeamCAMSScriptEditor
                           PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(TEAM_CAMS_PRIVATE_LIBS Qt${QT_VERSION_MAJOR}::Core
                           Qt${QT_VERSION_MAJOR}::Widgets)

if(ENABLE_QT_TEST)
  list(APPEND TEAM_CAMS_PRIVATE_LIBS Qt${QT_VERSION_MAJOR}::Test)
endif()

target_link_libraries(TeamCAMSScriptEditor PRIVATE ${TEAM_CAMS_PRIVATE_LIBS})

set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER
                     "ch.unifr.teamcams.scripteditor")

set_target_properties(
  TeamCAMSScriptEditor
  PROPERTIES WIN32_EXECUTABLE TRUE
             MACOSX_BUNDLE TRUE
             ${BUNDLE_ID_OPTION} MACOSX_BUNDLE_BUNDLE_VERSION
             "${PROJECT_VERSION}" MACOSX_BUNDLE_SHORT_VERSION_STRING
             "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
             MACOSX_BUNDLE_ICON_FILE
             "app_icon.icns")

if(NOT APPLE AND NOT WIN32)
  install(
    FILES "${ICON_LINUX}"
    DESTINATION "share/icons/hicolor/512x512/apps"
    RENAME "TeamCAMSScriptEditor.png")
  install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/TeamCAMSScriptEditor.desktop"
          DESTINATION "share/applications")
endif()

include(GNUInstallDirs)

install(
  TARGETS TeamCAMSScriptEditor
  BUNDLE DESTINATION .
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(TeamCAMSScriptEditor)
endif()

if(QT_VERSION_MAJOR EQUAL 6
   AND NOT EMSCRIPTEN
   AND NOT APPLE
   AND NOT WIN32)
  install(TARGETS TeamCAMSScriptEditor
          RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
elseif(QT_VERSION_MAJOR EQUAL 6 AND NOT EMSCRIPTEN)
  include(QtCMakeMacros OPTIONAL)
  qt_generate_deploy_app_script(
    TARGET TeamCAMSScriptEditor OUTPUT_SCRIPT deploy_script.cmake
    NO_UNSUPPORTED_PLATFORM_ERROR)
  install(SCRIPT ${deploy_script.cmake})
endif()
