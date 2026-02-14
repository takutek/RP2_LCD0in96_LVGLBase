#ifdef PC_SIMULATOR
#include <SDL.h>
#endif

#include "Board/BoardInit/BoardInit.h"
#include "Fifo/Fifo.h"
#include "Tasks/Background/BackgroundTask.h"
#include "Tasks/Foreground/ForegroundTask.h"
static Fifo g_fifo;

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;
  BoardInit::ModuleInit();
  BackgroundTask backgroundTask(g_fifo);
  backgroundTask.Start();
  ForegroundTask foregroundTask(g_fifo);
  foregroundTask.Run();
  return 0;
}