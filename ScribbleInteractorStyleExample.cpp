#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>

#include "vtkScribbleInteractorStyle.h"

void MySlot(vtkPolyData*);

int main(int argc, char* argv[])
{
  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  int dims[3] = {100,100,1};
  image->SetDimensions(dims);
  image->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

  // Create an actor
  vtkSmartPointer<vtkImageActor> actor =
    vtkSmartPointer<vtkImageActor>::New();
  actor->SetInputData(image);

  // Setup renderer
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->ResetCamera();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // Setup render window interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkScribbleInteractorStyle> scribbleInteractorStyle =
    vtkSmartPointer<vtkScribbleInteractorStyle>::New();

  scribbleInteractorStyle->StrokeUpdated.connect(MySlot);

  // Render and start interaction
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Initialize();

  renderWindowInteractor->SetInteractorStyle(scribbleInteractorStyle);
  scribbleInteractorStyle->InitializeTracer(actor); // this must come after the SetInteractorStyle call

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

void MySlot(vtkPolyData* polydata)
{
  std::cout << "Slot called." << std::endl;
}