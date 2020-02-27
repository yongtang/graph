#include <backend/PixelBufferDescriptor.h>
#include <filament/Engine.h>
#include <filament/Material.h>
#include <filament/Renderer.h>
#include <filament/Viewport.h>
#include <filament/View.h>
#include <iostream>

// matc -o bakedColor.inc -f header bakedColor.mat
static constexpr uint8_t BAKED_COLOR_PACKAGE[] = {
    #include "bakedColor.inc"
};

int main(int argc, char* argv[]) {
  // Change backend to OpenGL (default) below resolves the issue of crash.
  //     filament::Engine* pEngine = filament::Engine::create()
  // Use (filament::backend::Backend::METAL) for Metal to expose the issue.
  filament::Engine* pEngine = filament::Engine::create(filament::backend::Backend::METAL);
  filament::SwapChain* pSurface = pEngine->createSwapChain(16, 16);
  filament::Renderer* pRenderer = pEngine->createRenderer();
  filament::Scene* pScene = pEngine->createScene();
  filament::Camera* pCamera = pEngine->createCamera();

  filament::View* pView = pEngine->createView();
  pView->setViewport({0, 0, 16, 16});
  pView->setScene(pScene);
  pView->setCamera(pCamera);

  pView->setClearColor(filament::LinearColorA{1, 0, 0, 1});
  pView->setToneMapping(filament::View::ToneMapping::LINEAR);
  pView->setDithering(filament::View::Dithering::NONE);

  filament::Material* pMaterial = filament::Material::Builder()
        .package((void*) BAKED_COLOR_PACKAGE, sizeof(BAKED_COLOR_PACKAGE))
        .build(*pEngine);
  filament::MaterialInstance* pMaterialInstance = pMaterial->createInstance();

  size_t size = 16 * 16 * 4;
  void* buffer = malloc(size);
  memset(buffer, 0, size);
  filament::backend::PixelBufferDescriptor pd(
      buffer, size, filament::backend::PixelDataFormat::RGBA,
      filament::backend::PixelDataType::UBYTE);  // callback, user);

  pRenderer->beginFrame(pSurface);
  pRenderer->render(pView);
  pRenderer->readPixels(0, 0, 16, 16, std::move(pd));
  pRenderer->endFrame();

  pEngine->flushAndWait();

  free(buffer);

  std::cerr << "Hello, world!" << std::endl;

  pEngine->destroy(pCamera);
  pEngine->destroy(pScene);
  pEngine->destroy(pView);
  pEngine->destroy(pRenderer);
  pEngine->destroy(pSurface);
  filament::Engine::destroy(&pEngine);

  return 0;
};
