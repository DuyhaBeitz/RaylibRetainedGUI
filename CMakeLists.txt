cmake_minimum_required(VERSION 3.20)

project(RaylibRetainedGUI LANGUAGES CXX VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)

option(RAYLIBRETAINEDGUI_BUILD_EXAMPLES "Build examples" OFF)

add_library(${PROJECT_NAME} STATIC 
    src/UIElement.cpp
    src/UIStyle.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# find_package(raylib QUIET)
# if (NOT raylib_FOUND)
#     include(FetchContent)
#     FetchContent_Declare(
#         raylib
#         GIT_REPOSITORY https://github.com/raysan5/raylib.git
#         GIT_TAG 5.5
#     )
#     FetchContent_MakeAvailable(raylib)
# endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    raylib
)

if(RAYLIBRETAINEDGUI_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

################################### Installation
if (PROJECT_IS_TOP_LEVEL)
    include(GNUInstallDirs)

    install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Config.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    )
endif()
