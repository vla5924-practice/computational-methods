cmake_minimum_required(VERSION 3.14)

project(RungeKutta)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4996")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archive)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Qt5 COMPONENTS Core Gui Widgets Network PrintSupport REQUIRED)
#find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets Network PrintSupport REQUIRED)

set(TARGET_NAME "03_rungekutta")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")

file(GLOB_RECURSE TARGET_HEADERS
    include/*.h
    thirdparty/qcustomplot/*.h
)

file(GLOB_RECURSE TARGET_SRC
    src/*.cpp
    thirdparty/qcustomplot/*.cpp
)

file(GLOB_RECURSE TARGET_UI_FILES
    ui/*.ui
)

add_executable(${TARGET_NAME} ${TARGET_SRC} ${TARGET_HEADERS} ${TARGET_UI_FILES} ${TARGET_RESOURCES})

target_include_directories(${TARGET_NAME} PUBLIC
    include
    thirdparty/qcustomplot
)

target_link_libraries(${TARGET_NAME}
PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::PrintSupport
)
