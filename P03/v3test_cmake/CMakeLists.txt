cmake_minimum_required(VERSION 3.5)

project(v3test LANGUAGES CXX)

# Für QT5-Entwicklung unter ubuntu muss noch
#    qt5-base
# installiert werden
#
# Einstellung für das Extra-Terminal befinden sich im QtCreator
#  1) links auf "Projekte" -> "Ausführen" -> "In Terminal starten"
#  2) falls sich das Terminal nicht öffnet, dann
#     im Menü "Extras" -> "Einstellungen" -> "Umgebung" -> "System" -> "Terminal"
#     das korrekt Terminalprogramm auswählen (z. B. /bin/gnome-terminal)
#     Standard ist der Terminal-Emulator, der unter Ubuntu/Debian Probleme macht.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Threads REQUIRED)

if ($ENV{GOOGLETEST_DIR})
    set(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
else ()
    if (NOT "/usr/src/googletest" STREQUAL "")
        message(WARNING "Using googletest src dir specified at Qt Creator wizard")
    endif ()
    #
    # Nachfolgend wird das Verzeichnis fuer googletest festgelegt
    #
    set(GOOGLETEST_DIR "/usr/src/googletest")
endif ()

# Activate for Windows:
##set(GOOGLETEST_DIR "C:/Qt/googletest")
if (EXISTS ${GOOGLETEST_DIR})
    set(GTestSrc ${GOOGLETEST_DIR}/googletest)
    set(GMockSrc ${GOOGLETEST_DIR}/googlemock)
elseif (UNIX AND EXISTS /usr/src/gtest)
    set(GTestSrc /usr/src/gtest)
    message(WARNING "Using gtest from system")
    if (EXISTS /usr/src/gmock)
        set(GMockSrc /usr/src/gmock)
    endif ()
else ()
    message( FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
endif ()

set(GTestFiles ${GTestSrc}/src/gtest-all.cc)
set(GTestIncludes ${GTestSrc} ${GTestSrc}/include)
if (NOT ${GMockSrc} STREQUAL "")
    list(APPEND GTestFiles ${GMockSrc}/src/gmock-all.cc)
    list(APPEND GTestIncludes ${GMockSrc} ${GMockSrc}/include)
endif ()

include_directories(${GTestIncludes})

#
# Nachfolgend werden die Quelldateien des Projekts festgelegt
#
set(PROJECT_SOURCES
        bohrung.h bohrung.cpp telement.h ikomponente.h ikomponente.cpp
        fraesung.h fraesung.cpp
        delist.h iterator.h delist_impl.h iterator_impl.h
        serializer.h serializer.cpp
        komponente.h komponente.cpp
        werkstueck.h werkstueck.cpp
)

add_executable(v3test v3test_main.cpp v3test.h
               ${GTestFiles} ${PROJECT_SOURCES})
add_test(NAME v3test COMMAND v3test)

target_link_libraries(v3test PRIVATE Threads::Threads)
target_link_libraries(v3test PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

