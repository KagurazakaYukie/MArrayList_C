#ifndef MARRAYLISET_H
#define MARRAYLISET_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "mtmm.h"
#include "init.h"

typedef struct MAL {
    MemoryInfo *mi,*mal;
    void **Element;
    DataSizeType length;
} MArrayList;

MArrayList *MArrayListInit(MTMemoryManager *mm,DataSizeType InitSize);

MArrayList *GetMArrayList(MemoryInfo *mi);

void *MArrayListGetIndex(MArrayList * arraylist, DataSizeType i);

bool MArrayListSetIndex(MArrayList * arraylist, DataSizeType i, void *element);

DataSizeType MArrayListSize(MArrayList * arraylist);

void MArrayListDestroy(MTMemoryManager *mm,MArrayList *arraylist);

void MArrayListDestroy2(MTMemoryManager *mm,MArrayList * arraylist);

bool MArrayListDeleteIndex(MTMemoryManager *mm,MArrayList * arraylist, void *element, Cmp c);

bool MArrayListDeleteIndex2(MArrayList * arraylist, void *element, Cmp c);

bool MArrayListDeleteAppointIndex(MTMemoryManager *mm,MArrayList * arraylist, DataSizeType i);

bool MArrayListDeleteAppointIndex2(MArrayList * arraylist, DataSizeType i);

bool MArrayListAddIndexs(MTMemoryManager *mm,MArrayList * arraylist, void **element, DataSizeType size);

bool MArrayListAddIndex(MTMemoryManager *mm,MArrayList * arraylist, void *element);

bool MArrayListInsertIndex(MTMemoryManager *mm,MArrayList * arraylist, DataSizeType position,void *element);

#endif
