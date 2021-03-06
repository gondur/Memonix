# CMakeLists.txt for Memonix by Dmitry Marakasov <amdmi3@amdmi3.ru>
# 
# Usage:
#
# unzip MemonixSourceCode.zip
# cd MemonixSourceCode
# cmake .
# make
#
# Of course you need cmake installed on your system. After the build
# is complete, copy gamedata.vfs from game binary distribution archive
# into current directory and run ./Memonix
#

# project name
PROJECT(Memonix)

# depends
set(SDL_CONFIG "sdl-config" CACHE STRING "Path to sdl-config script")

FIND_PACKAGE(OpenGL REQUIRED)
IF(OPENGL_FOUND)
	INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
ELSE(OPENGL_FOUND)
	MESSAGE(FATAL "OpenGL not found")
ENDIF(OPENGL_FOUND)

FIND_PACKAGE(GLU REQUIRED)
FIND_PACKAGE(SDL REQUIRED)
FIND_PACKAGE(SDL_image REQUIRED)
FIND_PACKAGE(SDL_mixer REQUIRED)

# sources
FILE(GLOB_RECURSE memonix_SRCS *.cpp)

# targets
ADD_DEFINITIONS(`${SDL_CONFIG} --cflags`)
ADD_EXECUTABLE(Memonix ${memonix_SRCS})
TARGET_LINK_LIBRARIES(Memonix `${SDL_CONFIG} --libs` ${SDLIMAGE_LIBRARY} ${SDLMIXER_LIBRARY} ${OPENGL_gl_LIBRARY} ${GLU_LIBRARY})
