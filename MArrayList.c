#include <stdlib.h>
#include <stdbool.h>
#include "init.h"
#include "MArrayList.h"
#include "mtmm.h"

MArrayList *MArrayListInit(MTMemoryManager *mm, DataSizeType InitSize) {
    MemoryInfo *ma = MTMemoryManagerCalloc(mm, sizeof(MArrayList));
    MemoryInfo *mi = NULL;
    MArrayList *mal = (MArrayList *) ma->m;
    mal->Element = NULL;
    mal->mal = ma;
    mal->mi = mi;
    mal->length = 0;
    return mal;
}

MArrayList *GetMArrayList(MemoryInfo *mi) {
    return (MArrayList *) mi->m;
}

void *MArrayListGetIndex(MArrayList *arraylist, DataSizeType i) {
    if (i <= (arraylist->length - 1)) {
        return arraylist->Element[i];
    } else {
        return NULL;
    }
}

bool MArrayListSetIndex(MArrayList *arraylist, DataSizeType i, void *element) {
    if (i <= (arraylist->length - 1)) {
        arraylist->Element[i] = element;
        return true;
    } else {
        return false;
    }
}

DataSizeType MArrayListSize(MArrayList *arraylist) {
    return arraylist->length;
}

void MArrayListDestroy(MTMemoryManager *mm, MArrayList *arraylist) {
    if (arraylist->mi != NULL) {
        MTMemoryManagerFree(mm, arraylist->mi);
    }
    MTMemoryManagerFree(mm, arraylist->mal);
}

void MArrayListDestroy2(MTMemoryManager *mm, MArrayList *arraylist) {
    if (arraylist->mi != NULL) {
        for (int i = 0; i < arraylist->length; i++) {
            MTMemoryManagerFree(mm, (MemoryInfo *) MArrayListGetIndex(arraylist, i));
        }
        MTMemoryManagerFree(mm, arraylist->mi);
    }
    MTMemoryManagerFree(mm, arraylist->mal);
}

bool MArrayListDeleteIndex(MTMemoryManager *mm, MArrayList *arraylist, void *element, Cmp c) {
    int i = -1;
    for (int ii = 0; ii < arraylist->length; ii++) {
        if (c(arraylist->Element[ii], element)) {
            i = ii;
            break;
        }
    }
    if (i >= 0) {
        MTMemoryManagerFree(mm, (MemoryInfo *) arraylist->Element[i]);
        for (; i < arraylist->length; i++) {
            arraylist->Element[i] = arraylist->Element[i + 1];
        }
        arraylist->length--;
    }
    return true;
}

bool MArrayListDeleteIndex2(MArrayList *arraylist, void *element, Cmp c) {
    int i = -1;
    for (int ii = 0; ii < arraylist->length; ii++) {
        if (c(arraylist->Element[ii], element)) {
            i = ii;
            break;
        }
    }
    if (i >= 0) {
        for (; i < arraylist->length; i++) {
            arraylist->Element[i] = arraylist->Element[i + 1];
        }
        arraylist->length--;
    }
    return true;
}

bool MArrayListDeleteAppointIndex(MTMemoryManager *mm, MArrayList *arraylist, DataSizeType i) {
    if (i >= 0) {
        if (arraylist->Element[i] != NULL) {
            MTMemoryManagerFree(mm, (MemoryInfo *) arraylist->Element[i]);
        }
        for (; i < arraylist->length; i++) {
            arraylist->Element[i] = arraylist->Element[i + 1];
        }
        arraylist->length--;
        return true;
    } else {
        return false;
    }
}

bool MArrayListDeleteAppointIndex2(MArrayList *arraylist, DataSizeType i) {
    if (i >= 0) {
        for (; i < arraylist->length; i++) {
            arraylist->Element[i] = arraylist->Element[i + 1];
        }
        arraylist->length--;
        return true;
    } else {
        return false;
    }
}

bool MArrayListAddIndexs(MTMemoryManager *mm, MArrayList *arraylist, void **element, DataSizeType size) {
    int p = 0;
    if (arraylist->mi == NULL) {
        if (ListLength > size) {
            MemoryInfo *mi = MTMemoryManagerCalloc(mm, ListLength << PointerSize);
            arraylist->Element = mi->m;
            for (DataSizeType i = arraylist->length; i < arraylist->length + size; i++) {
                arraylist->Element[i] = element[p];
                p++;
            }
            arraylist->length += size;
            return true;
        }
        MemoryInfo *mi = MTMemoryManagerCalloc(mm,(((size >> ListBinaryLength) << 1) << ListBinaryLength << PointerSize));
        arraylist->Element = mi->m;
        for (DataSizeType i = arraylist->length; i < arraylist->length + size; i++) {
            arraylist->Element[i] = element[p];
            p++;
        }
        arraylist->length += size;
        return true;
    }
    if ((arraylist->length + size) > (arraylist->mi->size >> PointerSize)) {
        arraylist->mi = MTMemoryManagerRealloc(mm, arraylist->mi, arraylist->mi->size +(((size >> ListBinaryLength) << 1) << ListBinaryLength<< PointerSize));
        arraylist->Element = arraylist->mi->m;
        for (DataSizeType i = arraylist->length; i < arraylist->length + size; i++) {
            arraylist->Element[i] = element[p];
            p++;
        }
        arraylist->length += size;
        return true;
    }
    for (DataSizeType i = arraylist->length; i < arraylist->length + size; i++) {
        arraylist->Element[i] = element[p];
        p++;
    }
    arraylist->length += size;
    return true;
}

bool MArrayListAddIndex(MTMemoryManager *mm, MArrayList *arraylist, void *element) {
    if (arraylist->mi == NULL) {
        arraylist->mi = MTMemoryManagerCalloc(mm, (ListLength << PointerSize));
        arraylist->Element = arraylist->mi->m;
        arraylist->Element[0] = element;
        arraylist->length++;
        return true;
    }
    if ((arraylist->length + 1) > (arraylist->mi->size >> PointerSize)) {
        arraylist->mi = MTMemoryManagerRealloc(mm, arraylist->mi,arraylist->mi->size + (ListLength << PointerSize));
        arraylist->Element = arraylist->mi->m;
    }
    arraylist->Element[arraylist->length] = element;
    arraylist->length++;
    return true;
}

bool MArrayListInsertIndex(MTMemoryManager *mm, MArrayList *arraylist, DataSizeType position, void *element) {
    if (position <= arraylist->length) {
        if ((arraylist->length + 1) > (arraylist->mi->size >> PointerSize)) {
            arraylist->mi = MTMemoryManagerRealloc(mm, arraylist->mi,arraylist->mi->size + (ListLength << PointerSize));
        }
        for (DataSizeType i = (arraylist->mi->size >> PointerSize) - 1; i > position; i--) {
            arraylist->Element[i] = arraylist->Element[i - 1];
        }
        arraylist->Element[position] = element;
        arraylist->length ++;
        return true;
    } else {
        return false;
    }
}
