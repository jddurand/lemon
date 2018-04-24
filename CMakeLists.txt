CMAKE_MINIMUM_REQUIRED (VERSION 3.0.0 FATAL_ERROR)
PROJECT (lemon_lang VERSION 0.0.1 LANGUAGES C CXX)
#
# Policies
# --------
FOREACH (_policy
    CMP0063             # Honor visibility properties for all target types
    CMP0018)            # Ignore CMAKE_SHARED_LIBRARY_<Lang>_FLAGS variables
  IF (POLICY ${_policy})
    CMAKE_POLICY (SET ${_policy} NEW)
  ENDIF ()
ENDFOREACH ()
#
# Options
# -------
OPTION (LEMON_LANG_OPT_USE_STD_MALLOC "stdlib's `malloc` ensure return aligned pointer" OFF)
OPTION (LEMON_LANG_OPT_BUILD_MODULE_OS "POSIX builtin os library" ON)
OPTION (LEMON_LANG_OPT_BUILD_MODULE_SOCKET "BSD Socket builtin library" ON)
OPTION (LEMON_LANG_OPT_BUILD_DYNAMIC_LIB "Build dynamic library" ON)
OPTION (LEMON_LANG_OPT_BUILD_STATIC_LIB "Build static library" ON)
OPTION (LEMON_LANG_APPEND_STATIC_TO_STATIC_LIBNAME "Add _static to static library" ON) # Recommended -;
OPTION (LEMON_LANG_OPT_BUILD_STATIC_LEMON_EXECUTABLE "Link lemon executable with static library" OFF)

IF (LEMON_LANG_OPT_BUILD_STATIC_LEMON_EXECUTABLE)
  SET (LEMON_LANG_OPT_BUILD_STATIC_LIB TRUE)
ENDIF ()

IF (LEMON_LANG_OPT_USE_STD_MALLOC)
  ADD_DEFINITIONS(-DUSE_MALLOC)
ENDIF ()
IF (LEMON_LANG_OPT_BUILD_MODULE_OS)
  ADD_DEFINITIONS(-DMODULE_OS)
ENDIF ()
IF (LEMON_LANG_OPT_BUILD_MODULE_SOCKET)
  ADD_DEFINITIONS(-DMODULE_SOCKET)
ENDIF ()
IF (LEMON_LANG_OPT_BUILD_STATIC_LEMON_EXECUTABLE)
  ADD_DEFINITIONS(-DSTATICLIB)
ENDIF ()
#
# Sources
# -------
SET (LEMON_LANG_SRCS
  src/lemon.c
  src/hash.c
  src/shell.c
  src/mpool.c
  src/arena.c
  src/table.c
  src/token.c
  src/input.c
  src/lexer.c
  src/scope.c
  src/syntax.c
  src/parser.c
  src/symbol.c
  src/extend.c
  src/compiler.c
  src/peephole.c
  src/generator.c
  src/allocator.c
  src/collector.c
  src/machine.c
  src/lnil.c
  src/ltype.c
  src/lkarg.c
  src/lvarg.c
  src/ltable.c
  src/lvkarg.c
  src/larray.c
  src/lframe.c
  src/lclass.c
  src/lsuper.c
  src/lobject.c
  src/lmodule.c
  src/lnumber.c
  src/lstring.c
  src/linteger.c
  src/lboolean.c
  src/linstance.c
  src/literator.c
  src/lfunction.c
  src/lsentinel.c
  src/laccessor.c
  src/lexception.c
  src/lcoroutine.c
  src/ldictionary.c
  src/lcontinuation.c
  lib/builtin.c)

IF (LEMON_LANG_OPT_BUILD_MODULE_OS)
  LIST (APPEND LEMON_LANG_SRCS lib/os.c)
ENDIF ()
IF (LEMON_LANG_OPT_BUILD_MODULE_SOCKET)
  LIST (APPEND LEMON_LANG_SRCS lib/socket.c)
ENDIF ()
#
# Include directories
# -------------------
INCLUDE_DIRECTORIES(. src)
#
# Compiler settings
# -----------------
SET (CMAKE_C_VISIBILITY_PRESET   hidden)
SET (CMAKE_CXX_VISIBILITY_PRESET hidden)
SET (CMAKE_POSITION_INDEPENDENT_CODE ON)
#
# Installation settings
# ---------------------
INCLUDE (GNUInstallDirs) # enforce lib64 if needed
INCLUDE (InstallRequiredSystemLibraries) # system libraries if needed
#
# Libraries
# ---------
ADD_LIBRARY (lemon_objects OBJECT ${LEMON_LANG_SRCS})
ADD_LIBRARY (lemon SHARED $<TARGET_OBJECTS:lemon_objects>)
IF (LEMON_LANG_OPT_BUILD_STATIC_LIB)
  IF (LEMON_LANG_APPEND_STATIC_TO_STATIC_LIBNAME)
    ADD_LIBRARY (lemon_static STATIC $<TARGET_OBJECTS:lemon_objects>)
  ELSE ()
    ADD_LIBRARY (lemon STATIC $<TARGET_OBJECTS:lemon_objects>)
  ENDIF ()
ENDIF ()
SET (CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
#
# Implicit dependencies on dl, m
#
IF (UNIX)
  SET (CMAKE_M_LIBS m)
ENDIF ()
IF ((NOT ("${CMAKE_DL_LIBS}" STREQUAL "")) OR (NOT ("${CMAKE_M_LIBS}" STREQUAL "")))
  TARGET_LINK_LIBRARIES(lemon PUBLIC ${CMAKE_DL_LIBS} ${CMAKE_M_LIBS})
  IF (LEMON_LANG_OPT_BUILD_STATIC_LIB)
    TARGET_LINK_LIBRARIES(lemon_static PUBLIC ${CMAKE_DL_LIBS} ${CMAKE_M_LIBS})
  ENDIF ()
ENDIF ()
#
# Export definition
#
INCLUDE (GenerateExportHeader)
GENERATE_EXPORT_HEADER(lemon
  EXPORT_FILE_NAME "src/lemon_export.h"
  )
ADD_DEFINITIONS(-Dlemon_EXPORTS)
#
# Target properties
#
SET_TARGET_PROPERTIES(lemon
  PROPERTIES
  VERSION    ${lemon_lang_VERSION}
  SOVERSION  ${lemon_lang_VERSION_MAJOR}
  )
#
# Executables
# -----------
ADD_EXECUTABLE(lemon_executable src/main.c)
SET_TARGET_PROPERTIES(lemon_executable PROPERTIES OUTPUT_NAME "lemon")
IF (LEMON_LANG_OPT_BUILD_STATIC_LEMON_EXECUTABLE)
  TARGET_LINK_LIBRARIES(lemon_executable PUBLIC lemon_static)
ELSE ()
  TARGET_LINK_LIBRARIES(lemon_executable PUBLIC lemon)
ENDIF ()
#
# Enable Testing
# --------------
ENABLE_TESTING()
ADD_TEST(test ${CMAKE_COMMAND} -E echo "$<TARGET_FILE:lemon_executable>" test/test.lm)
ADD_TEST(test_hello_world ${CMAKE_COMMAND} -E echo "$<TARGET_FILE:lemon_executable>" test/test_helloworld.lm)
