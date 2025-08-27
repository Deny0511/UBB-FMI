cmake_minimum_required(VERSION 3.0.0)
project(lab6_7)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.9.0/mingw_64/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
#find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
#qt6_wrap_cpp(MOC_SOURCES ${HEADERS}) # Rulare moc pe fișierele cu Q_OBJECT

add_executable(lab6_7 main.cpp
                      teste.cpp
        teste.h
        domain.h
        service.h
        ui.h
        validator.h
        CosFilme.h
        gui.h
        CosCRUDGUI.h
        CosReadOnlyGUI.h
        filmeModel.h
        filmeModel.h
                        domain.cpp
                        repo.cpp
                        service.cpp
                        ui.cpp
                        validator.cpp
                        CosFilme.cpp
                        gui.cpp
                        filmTableModel.cpp
                        filmeModel.cpp
                        )



target_link_libraries(lab6_7
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

configure_file(${CMAKE_SOURCE_DIR}/filme1.txt ${CMAKE_BINARY_DIR}/filme1.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/test_filmee_output.txt ${CMAKE_BINARY_DIR}/test_filmee_output.txt COPYONLY)
#target_link_libraries(lab6_7 Qt6::Core Qt6::Widgets Qt6::Gui)