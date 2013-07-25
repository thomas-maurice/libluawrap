cmake_minimum_required(VERSION 2.6)

#SET(CMAKE_INSTALL_PREFIX "/usr/local")

PROJECT(libluawrap)

INCLUDE(FindPkgConfig)

INCLUDE(cmake/FindGZIP.cmake)

SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/home/thomas/git-repositories/lua/build/foo/lib")

IF(NOT PKG_CONFIG_FOUND)
	message(FATAL_ERROR "You need to install pkg-config. Exiting.")
ENDIF()

pkg_check_modules(LUA REQUIRED lua)

IF(NOT LUA_FOUND)
	message(FATAL_ERROR "You need to install lua5.2. Exiting.")
ENDIF()

ADD_DEFINITIONS(-Wall -O2 -s)

SET(BINARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

SET(CMAKE_CXX_FLAGS "-fPIC")

INCLUDE_DIRECTORIES("include" "include/libluawrap" ${LUA_INCLUDE_DIRS})
LINK_DIRECTORIES(${LUA_LIBRARY_DIRS} ${LIBRARY_OUTPUT_PATH})

SET(MAJORV "0")
SET(MINORV "2")

SET(MAN_PAGES "man/libluawrap.LuaBoolean.3"
              "man/libluawrap.LuaFunction.3"
              "man/libluawrap.LuaNil.3"
              "man/libluawrap.LuaNumber.3"
              "man/libluawrap.LuaString.3"
              "man/libluawrap.LuaWrap.3"
              "man/libluawrap.LuaTable.3"
              "man/libluawrap.LuaTableElement.3")

INCLUDE(cmake/BuildMan.cmake)

# Configuration des fichiers sources
# Lecture de tout les .cpp et .h
FILE(
	GLOB_RECURSE
	source_files
	src/*.cpp
	include/*.h
)


# Fichiers OBJECT communs aux fichiers
# de lib statique et dynamique
ADD_LIBRARY(        
	libluawrap_common
	OBJECT
	${source_files}
)

# Ajoute la lib dynamique construite
# à partir des fichiers OBJECT
ADD_LIBRARY(        
	libluawrap
	SHARED
	$<TARGET_OBJECTS:libluawrap_common>
)

# Ajoute la lib statique a partir des fichiers OBJECT
ADD_LIBRARY(        
	libluawrap_static
	STATIC
	$<TARGET_OBJECTS:libluawrap_common>
)

# Création de l'éxecutable de test
ADD_EXECUTABLE(
	luawrap_test
	luawrap_test/main.cpp
)

ADD_EXECUTABLE(
	readtable
	luawrap_test/readtable.cpp
)

ADD_EXECUTABLE(
	basic_export
	luawrap_test/basic_export.cpp
)

ADD_EXECUTABLE(
	object
	luawrap_test/object.cpp
)

ADD_DEPENDENCIES(readtable libluawrap)
ADD_DEPENDENCIES(basic_export libluawrap)
ADD_DEPENDENCIES(luawrap_test libluawrap)
ADD_DEPENDENCIES(object libluawrap)

# Link la lib dynamique et Lua au programme de test
TARGET_LINK_LIBRARIES(
	luawrap_test
	luawrap
	${LUA_LIBRARIES}
)

# Link la lib dynamique et Lua au programme de test
TARGET_LINK_LIBRARIES(
	readtable
	luawrap
	${LUA_LIBRARIES}
)

# Link la lib dynamique et Lua au programme de test
TARGET_LINK_LIBRARIES(
	object
	luawrap
	${LUA_LIBRARIES}
)

# Link la lib dynamique et Lua au programme de test
TARGET_LINK_LIBRARIES(
  basic_export
	luawrap
	${LUA_LIBRARIES}
)

# Link Lua à la lib dynamique
TARGET_LINK_LIBRARIES(
	libluawrap
	${LUA_LIBRARIES}
)


# Change le nom de la lib statique
SET_TARGET_PROPERTIES(
	libluawrap_static
	PROPERTIES
	OUTPUT_NAME "luawrap"
)

# Change le nom, la version et la SONAME de la lib dynamique
SET_TARGET_PROPERTIES(
  libluawrap
  PROPERTIES
  VERSION ${MAJORV}.${MINORV}
  SOVERSION ${MAJORV}
  PREFIX ""
 )

# Installation
INSTALL(TARGETS libluawrap DESTINATION lib)
INSTALL(TARGETS libluawrap_static DESTINATION lib)
INSTALL(FILES include/libluawrap.h DESTINATION include)
INSTALL(FILES pkgconfig/libluawrap.pc DESTINATION lib/pkgconfig)
INSTALL(DIRECTORY include/libluawrap DESTINATION include)
