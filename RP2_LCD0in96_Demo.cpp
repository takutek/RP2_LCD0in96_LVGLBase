#ifdef PC_SIMULATOR
#include <SDL.h>
#endif

#include "Board/BoardInit/BoardInit.h"
#include "Drivers/Fifo/Fifo.h"
#include "Tasks/BackgroundTask/BackgroundTask.h"
#include "Tasks/ForegroundTask/ForegroundTask.h"

static Fifo g_fifo;

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;
  BoardInit::ModuleInit();
  ForegroundTask foregroundTask(g_fifo);
  BackgroundTask backgroundTask(g_fifo);
  backgroundTask.Start();
  foregroundTask.Run();
  return 0;
}