cmake_minimum_required(VERSION 3.0)

project(QwtExample)

find_package(Qt5Widgets         REQUIRED)
find_package(Qt5Gui             REQUIRED)
find_package(Qt5Core            REQUIRED)
find_package(Qt5SerialPort      REQUIRED)
find_package(Qt5PrintSupport    REQUIRED)

# QWT : temporary solution
INCLUDE(FindQwt.cmake)
find_library(Qwt REQUIRED)
include_directories( ${QWT_INCLUDE_DIR} )

# ==============================================================================
# Source
# ==============================================================================
set(APP_SOURCE plot.cpp
main.cpp)
#set(UI_FILES qtMapCoordinatesWidget.ui qtWeatherStations.ui)
#set(QT_WRAP qtMapCoordinatesWidget.h qtWeatherStations.h)

# ==============================================================================
# Target
# ==============================================================================
add_executable(qwtexample
  ${APP_SOURCE}
  ${UISrcs}
  ${MOCSrcs})

set_target_properties(qwtexample PROPERTIES
                    AUTOMOC TRUE
                    AUTORCC TRUE
                    AUTOUIC TRUE)

target_link_libraries(qwtexample Qt5::Core Qt5::Gui Qt5::Widgets Qt5::SerialPort Qt5::PrintSupport
                                ${QWT_LIBRARY})

target_include_directories(qwtexample PRIVATE
                          ${CMAKE_CURRENT_BINARY_DIR}
                          ${CMAKE_CURRENT_SOURCE_DIR}
                          ${CMAKE_SOURCE_DIR})
