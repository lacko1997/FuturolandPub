//
// Created by Lacko on 2018. 05. 22..
//

#ifndef FUTUROLANDDEV_MODEL_LIBRARY_H
#define FUTUROLANDDEV_MODEL_LIBRARY_H

#include <cstdlib>

typedef struct Model3D{
    float* vertex_data;
    short* index_data;
}Model3D;

struct ModelList;
struct ModelList{
    ModelList* prev;
    Model3D model;
    ModelList* next;
};


class ModelLibrary {
private:
    uint32_t size;

    ModelList *beg;
    ModelList *end;
    ModelList *list;
public:
    ModelLibrary();
    void push_front(Model3D model);
    void push_back(Model3D model);
};


#endif //FUTUROLANDDEV_MODEL_LIBRARY_H
