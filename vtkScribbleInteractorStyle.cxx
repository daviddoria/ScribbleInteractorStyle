/*
Copyright (C) 2010 David Doria, daviddoria@gmail.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "vtkScribbleInteractorStyle.h"

// VTK
#include <vtkActor.h>
#include <vtkAppendPolyData.h>
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>
#include <vtkImageSlice.h>
#include <vtkImageData.h>
#include <vtkImageTracerWidget.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkObjectFactory.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

vtkStandardNewMacro(vtkScribbleInteractorStyle);

vtkScribbleInteractorStyle::vtkScribbleInteractorStyle()
{
  this->ScribbleEvent = vtkCommand::UserEvent + 1;

  this->Selection = NULL;

  // Initializations
  this->Tracer = vtkSmartPointer<vtkImageTracerWidget>::New();
  this->Tracer->GetLineProperty()->SetLineWidth(5);
  this->Tracer->HandleMiddleMouseButtonOff();

  // Update the selection when the EndInteraction event is fired.
  this->Tracer->AddObserver(vtkCommand::EndInteractionEvent, this, &vtkScribbleInteractorStyle::CatchWidgetEvent);
}

void vtkScribbleInteractorStyle::SetColorToGreen()
{
  this->Tracer->GetLineProperty()->SetColor(0,1,0);
}

void vtkScribbleInteractorStyle::SetColorToRed()
{
  this->Tracer->GetLineProperty()->SetColor(1,0,0);
}

void vtkScribbleInteractorStyle::OnLeftButtonDown()
{
  vtkInteractorStyleImage::OnMiddleButtonDown();
}

void vtkScribbleInteractorStyle::OnLeftButtonUp()
{
  vtkInteractorStyleImage::OnMiddleButtonUp();
}

vtkPoints* vtkScribbleInteractorStyle::GetSelection()
{
  return this->Selection;
}

void vtkScribbleInteractorStyle::InitializeTracer(vtkImageSlice* imageSlice)
{
  //std::cout << "Enter InitializeTracer()" << std::endl;
  //this->CurrentRenderer->AddActor(imageSlice);
  this->CurrentRenderer->AddViewProp(imageSlice);
  this->Tracer->SetInteractor(this->Interactor);
  this->Tracer->SetViewProp(imageSlice);
  this->Tracer->ProjectToPlaneOn();

  this->Tracer->On();
}

void vtkScribbleInteractorStyle::CatchWidgetEvent(vtkObject* caller, long unsigned int eventId, void* callData)
{
  // Get the tracer object (this is the object that triggered this event)
  vtkImageTracerWidget* tracer = static_cast<vtkImageTracerWidget*>(caller);

  // Get the points in the selection
  vtkSmartPointer<vtkPolyData> path = vtkSmartPointer<vtkPolyData>::New();
  tracer->GetPath(path);

  // !!!
  //this->Selection = ITKVTKHelpers::PolyDataToPixelList(path);

  this->Selection = path->GetPoints();

  // "Clear" the tracer. We must rely on the foreground and background actors to maintain the appropriate colors.
  // If we did not clear the tracer, if we draw a stroke then change the color of the strokes, the last stoke would turn
  // the old color until we finished drawing the next stroke.

  vtkSmartPointer<vtkPoints> emptyPoints = vtkSmartPointer<vtkPoints>::New();
  emptyPoints->InsertNextPoint(0, 0, 0);
  emptyPoints->InsertNextPoint(0, 0, 0);

  this->Tracer->InitializeHandles(emptyPoints);
  this->Tracer->Modified();

  this->Refresh();

  this->InvokeEvent(this->ScribbleEvent, NULL);

  std::cout << "Exit CatchWidgetEvent()" << std::endl;
};

void vtkScribbleInteractorStyle::Refresh()
{
  this->CurrentRenderer->Render();
  this->Interactor->GetRenderWindow()->Render();
}
