#ifndef FUTUROLANDDEV_GRAPHICS_MODULE_H
#define FUTUROLANDDEV_GRAPHICS_MODULE_H

#include <vector>
#include <android/native_window.h>

using namespace std;

typedef void(*PFN_draw)();
typedef struct Model3D{
    float* vertex_data;
    short* indeex_data;
}Model3D;

extern vector<Model3D> models;

extern PFN_draw draw_func;

class GraphicsModule{
private:

public:
    GraphicsModule(ANativeWindow *wnd,uint32_t width,uint32_t height);
    PFN_draw getDrawFunc();
};


#endif //FUTUROLANDDEV_GRAPHICS_MODULE_H
