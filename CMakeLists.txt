cmake_minimum_required(VERSION 2.6)

Project(ScribbleInteractorStyle)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE( ${USE_VTK_FILE} )

ADD_LIBRARY(Scribble vtkInteractorStyleScribble.cxx)
TARGET_LINK_LIBRARIES(Scribble ${VTK_LIBRARIES})

ADD_EXECUTABLE(ScribbleInteractorStyle ScribbleInteractorStyleExample.cpp)
TARGET_LINK_LIBRARIES(ScribbleInteractorStyle ${VTK_LIBRARIES} Scribble)
