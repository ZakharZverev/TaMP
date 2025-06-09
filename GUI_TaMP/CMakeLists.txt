cmake_minimum_required(VERSION 3.16)

project(TIMP_KKZM LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ищем необходимые модули Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network Sql Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network Sql Widgets)

# Добавляем исходные файлы
add_executable(TIMP_KKZM
  main.cpp
  mytcpserver.cpp
  mytcpserver.h
  DatabaseManager.h
  rsa_encryption.cpp
  rsa_encryption.h
  simplehash.h simplehash.cpp
  bisection_method.h bisection_method.cpp
  graph.h graph.cpp
  mainwindow.h
  mainwindow.cpp
  Dockerfile
  clientmanager.h
)

# Линкуем с библиотеками Qt
target_link_libraries(TIMP_KKZM
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Sql
  Qt${QT_VERSION_MAJOR}::Widgets
)

# Указываем для установки
include(GNUInstallDirs)
install(TARGETS TIMP_KKZM
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)



