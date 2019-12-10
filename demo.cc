#include <backend/PixelBufferDescriptor.h>
#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <filament/View.h>

int main(int argc, char* argv[]) {
  // Change backend to filament::backend::Backend::METAL resolves the issue of
  //   zsh: illegal hardware instruction
  // but face another issue of:
  //   -[MTLTextureDescriptorInternal validateWithDevice:]:1249: failed
  //   assertion `MTLTextureDescriptor has invalid pixelFormat (255).

  // Change to (filament::backend::Backend::METAL) for Metal:
  filament::Engine* pEngine = filament::Engine::create();
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
