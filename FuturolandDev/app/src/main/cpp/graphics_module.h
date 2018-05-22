#ifndef FUTUROLANDDEV_GRAPHICS_MODULE_H
#define FUTUROLANDDEV_GRAPHICS_MODULE_H

#include <vector>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include "model_library.h"

using namespace std;

typedef void(*PFN_draw)();

extern PFN_draw draw_func;


class GraphicsModule{
private:

public:
    GraphicsModule(ANativeWindow *wnd,uint32_t width,uint32_t height);
    PFN_draw getDrawFunc();
    ~GraphicsModule();
};


#endif //FUTUROLANDDEV_GRAPHICS_MODULE_H
