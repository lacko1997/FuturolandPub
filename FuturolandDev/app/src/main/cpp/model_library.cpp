//
// Created by Lacko on 2018. 05. 22..
//

#include "model_library.h"

void ModelLibrary::push_back(Model3D model) {
    if(size==0){
        list->model=model;
        size++;
    }else{
        ModelList *prev=end;

        end->next=(ModelList*)malloc(sizeof(ModelList));
        end=end->next;
        end->model=model;
        end->prev=prev;

        size++;
    }
}

ModelLibrary::ModelLibrary() {
    list = (ModelList *) malloc(sizeof(ModelList));
    list->prev = NULL;
    list->next = NULL;

    uint32_t size = 0;

    beg = list;
    end = list;
}

void ModelLibrary::push_front(Model3D model) {
    if(size==0){
        list->model=model;
        size++;
    }else{
        ModelList *next=beg;

        beg->prev=(ModelList*)malloc(sizeof(ModelList));
        beg=beg->prev;
        beg->model=model;
        beg->next=next;

        size++;
    }
}
