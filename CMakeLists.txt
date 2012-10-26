cmake_minimum_required(VERSION 2.6)

Project(ScribbleInteractorStyle)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE( ${USE_VTK_FILE} )

set(ScribbleInteractorStyle_libraries ${ScribbleInteractorStyle_libraries} ${VTK_LIBRARIES})

# Create a library
ADD_LIBRARY(Scribble vtkInteractorStyleScribble.cxx)
TARGET_LINK_LIBRARIES(Scribble ${ScribbleInteractorStyle_libraries})

# Add the library to the list of libraries used
set(ScribbleInteractorStyle_libraries ${ScribbleInteractorStyle_libraries} Scribble)

# Create an example
ADD_EXECUTABLE(ScribbleInteractorStyle ScribbleInteractorStyleExample.cpp)
TARGET_LINK_LIBRARIES(ScribbleInteractorStyle ${VTK_LIBRARIES} Scribble)

# Allow this project to be detected and used as a submodule
set(ScribbleInteractorStyle_include_dirs ${ScribbleInteractorStyle_include_dirs} ${CMAKE_CURRENT_SOURCE_DIR})
set_property(GLOBAL PROPERTY ScribbleInteractorStyleIncludeDirs ${ScribbleInteractorStyle_include_dirs})
set_property(GLOBAL PROPERTY ScribbleInteractorStyleLibs ${ScribbleInteractorStyle_libraries})
