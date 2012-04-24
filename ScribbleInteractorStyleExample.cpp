#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>

#include "vtkScribbleInteractorStyle.h"

void MySlot(vtkPolyData*);

void CreateImage(vtkImageData* const);
int main(int argc, char* argv[])
{
  // Create an image
  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  CreateImage(image);
  
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

void CreateImage(vtkImageData* const image)
{
  int dims[3] = {100,100,1};
  image->SetDimensions(dims);
  image->AllocateScalars(VTK_UNSIGNED_CHAR, 3);

  // Make the image red
  for(unsigned int i = 0; i < dims[0]; ++i)
  {
    for(unsigned int j = 0; j < dims[0]; ++j)
    {
    unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(i,j,0));
    pixel[0] = 255;
    pixel[1] = 0;
    pixel[2] = 0;
    }
  }
}