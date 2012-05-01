cmake_minimum_required(VERSION 2.6)

Project(ScribbleInteractorStyle)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE( ${USE_VTK_FILE} )

ADD_EXECUTABLE(ScribbleInteractorStyle ScribbleInteractorStyleExample.cpp vtkInteractorStyleScribble.cxx)
TARGET_LINK_LIBRARIES(ScribbleInteractorStyle ${VTK_LIBRARIES})

message("Building libScribble")
ADD_LIBRARY(libScribble vtkInteractorStyleScribble.cxx)
TARGET_LINK_LIBRARIES(libScribble ${VTK_LIBRARIES})
