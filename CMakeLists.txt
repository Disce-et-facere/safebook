cmake_minimum_required(VERSION 3.5)

project(safebook VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(CUDAToolkit REQUIRED)

set(OPENSSL_INCLUDE_DIR "C:/Program Files/OpenSSL-Win64/include")
set(OPENSSL_LIB_DIR "C:/Program Files/OpenSSL-Win64/lib/VC/x64/MD")

file(GLOB PROJECT_SOURCES
        src/*.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(safebook
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

else()
    if(ANDROID)
        add_library(safebook SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(safebook
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(safebook PRIVATE "${OPENSSL_INCLUDE_DIR}")
target_include_directories(safebook PRIVATE include)
target_include_directories(safebook PRIVATE ${CUDA_INCLUDE_DIRS})  # Include Thrust
target_link_libraries(safebook PRIVATE
    "${OPENSSL_LIB_DIR}/libcrypto.lib"
    "${OPENSSL_LIB_DIR}/libssl.lib"
    "$${CUDAToolkit_LIBRARY_DIRS}"
)
target_link_libraries(safebook PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(safebook PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS safebook
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(safebook)
endif()