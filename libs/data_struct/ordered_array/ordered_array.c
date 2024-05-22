
#include <stdio.h>
#include <stdlib.h>
#include "ordered_array.h"

// возвращает пустое множество, в которое можно вставить capacity элементов
ordered_array_set ordered_array_set_create (size_t capacity){
    return (ordered_array_set) {malloc(sizeof(int) * capacity), 0, capacity};
}

// возвращает множество, состоящее из элементов массива a размера size
ordered_array_set ordered_array_set_create_from_array (const int *a, size_t size, size_t capacity){
    ordered_array_set res = ordered_array_set_create(capacity);
    for(int i = 0; i < size; i++){
        res.data[i] = a[i];
    }
    res.size = size;
    return res;
}

// возвращает значение позиции элемента в множестве,
// если значение value имеется в множестве set,
// иначе - n
size_t ordered_array_set_in (ordered_array_set *set, int value){
    for(int i = 0; i < set->size; i++){
        if (set->data[i] == value){
            return i;
        }
    }
    return set->size-1;
}

// истина если элемент есть в множестве
bool ordered_array_value_in_set(ordered_array_set set, int value){
    for(size_t i = 0; i < set.size; i++){
        if (set.data[i] == value)
            return true;
    }
    return false;
}

// возвращает значение ’истина’, если элементы множеств set1 и set2 равны
// иначе - ’ложь’
bool ordered_array_set_isEqual (ordered_array_set set1, ordered_array_set set2){
    if (set1.size != set2.size) {
        return 0;
    }
    return memcmp(set1.data, set2.data, sizeof(int) * set1.size) == 0;
}

// возвращает значение ’истина’, если subset является подмножеством set
// иначе - ’ложь’
bool ordered_array_set_isSubset (ordered_array_set subset, ordered_array_set set){
    int co = 0;
    for(int i = 0; i < subset.size; i++){
        if(ordered_array_value_in_set(set, subset.data[i])){
            co++;
        }
    }
    return co == subset.size;
}

// возбуждает исключение, если в множество по адресу set
// нельзя вставить элемент
void ordered_array_set_isAbleAppend (ordered_array_set *set){
    assert(set->size < set->capacity);
}

// добавляет элемент value в множество set
void ordered_array_set_insert (ordered_array_set *set, int value){

    assert(!ordered_array_value_in_set(*set, value));

    if(set->size == set->capacity) {
        int a[set->size];
        for(int i = 0; i < set->size; i++){
            a[i] = set->data[i];
        }
        free(set->data);
        set->data = malloc(sizeof(int) * (set->capacity*2));
        set->capacity*=2;
        for(int i = 0; i < set->size; i++){
            set->data[i] = a[i];
        }
    }
    set->data[set->size] = value;
    set->size++;
}

// удаляет элемент value из множества set
void ordered_array_set_deleteElement (ordered_array_set *set, int value){
    for(size_t i = ordered_array_set_in(set, value); i < set->size; i++){
        set->data[i] = set->data[i+1];
    }
    set->size--;
    ordered_array_set_delete(set);
}

// освобождает память, занимаемую множеством set
void ordered_array_set_delete (ordered_array_set * set){
    if(set->size < set->capacity/2){
        int a[set->size];
        for(int i = 0; i < set->size; i++){
            a[i] = set->data[i];
        }
        free(set->data);
        set->data = malloc(sizeof(int) * (set->capacity/2));
        set->capacity/=2;
        for(int i = 0; i < set->size; i++){
            set->data[i] = a[i];
        }
    }
}



// вывод множества set
void ordered_array_set_print (ordered_array_set set){
    for(int i = 0; i < set.size; i++)
        printf("%d ", set.data[i]);
    printf("\n");
}

//setA равно setB
bool ordered_array_set_isEquale_(ordered_array_set a, ordered_array_set b){
    bool F = false;
    if(a.data[0] == b.data[0] && b.size == a.size){
        for(int i = 1; i < b.size; i++){
            F = a.data[i] == b.data[i];
        }
    }
    return F;
}
//setA включено в setB
bool ordered_array_set_setA_In_setB(ordered_array_set setA, ordered_array_set
setB){
    bool F = setA.size <= setB.size;
    int i = 0;
    while (i < setA.size && F){
        F = false;
        for(int j = 0; j < setB.size; j++){
            if(setA.data[i] == setB.data[j]){
                F = true;
                break;
            }
        }
        i++;
    }
    return F;
}
//объединение
ordered_array_set ordered_array_set_union(ordered_array_set setA,ordered_array_set setB){
    ordered_array_set setC = ordered_array_set_create(setA.capacity);
    int i = 0;
    int j = 0;
    while (i < setA.size && j < setB.size){
        setC.size++;
        if(setA.data[i] == setB.data[j]){
            setC.data[setC.size-1] = setA.data[i];
            i++;
            j++;
        }
        else{
            if (setA.data[i] > setB.data[j]) {
                setC.data[setC.size - 1] = setB.data[j];
                j++;
            } else {
                setC.data[setC.size - 1] = setA.data[i];
                i++;
            }
        }
    }
    while (i < setA.size){
        setC.size++;
        setC.data[setC.size - 1] = setA.data[i];
        i++;
    }
    while (j < setB.size){
        setC.size++;
        setC.data[setC.size - 1] = setB.data[j];
        j++;
    }
    return setC;
}
//пересечение
ordered_array_set ordered_array_set_intersection(ordered_array_set setA, ordered_array_set setB){
    ordered_array_set setC = ordered_array_set_create(setA.capacity);
    int i = 0;
    int j = 0;
    while (i < setA.size && j < setB.size){
        if(setA.data[i] == setB.data[j]){
            setC.size++;
            setC.data[setC.size-1] = setA.data[i];
            i++;
            j++;
        }
        else{
            if(setA.data[i] > setB.data[j]){
                j++;
            } else{
                i++;
            }
        }
    }
    return setC;
}
//разница
ordered_array_set ordered_array_set_difference(ordered_array_set setA,ordered_array_set setB){
    ordered_array_set setC = ordered_array_set_create(setA.capacity);
    int i = 0;
    int j = 0;
    while (i < setA.size && j < setB.size){
        if(setA.data[i] == setB.data[j]){
            i++;
            j++;
        } else{
            if(setA.data[i] > setB.data[j]){
                j++;
            } else{
                setC.size++;
                setC.data[setC.size-1] = setA.data[i];
                i++;
            }
        }
    }
    while (i < setA.size){
        setC.size++;
        setC.data[setC.size-1] = setA.data[i];
        i++;
    }
    return setC;
}
//симетрическая разница
ordered_array_set ordered_array_set_symmetricDifference(ordered_array_set setA, ordered_array_set setB){
    ordered_array_set setC = ordered_array_set_create(setA.capacity);
    int i = 0;
    int j = 0;
    while (i < setA.size && j < setB.size){
        int t = setA.data[i];
        int d = setB.data[j];
        if(setA.data[i] == setB.data[j]){
            i++;
            j++;
        } else{
            if(setA.data[i] > setB.data[j]){
                setC.size++;
                setC.data[setC.size-1] = setB.data[j];
                j++;
            } else{
                setC.size++;
                setC.data[setC.size-1] = setA.data[i];
                i++;
            }
        }
    }
    while (i < setA.size){
        setC.size++;
        setC.data[setC.size - 1] = setA.data[i];
        i++;
    }
    while (j < setB.size){
        setC.size++;
        setC.data[setC.size - 1] = setB.data[j];
        j++;
    }
    return setC;
}
//дополнение
ordered_array_set ordered_array_set_complement(ordered_array_set setA){
    ordered_array_set setC = ordered_array_set_create(setA.capacity);
    int u = 1;
    int j = 0;
    while (u <= setA.capacity && j < setA.size){
        if(u == setA.data[j]){
            u++;
            j++;
        } else{
            if(u > setA.data[j]){
                j=j++;
            } else{
                setC.size++;
                setC.data[setC.size - 1] = u;
                u++;
            }
        }
    }
    while (u <= setA.capacity){
        setC.size++;
        setC.data[setC.size - 1] = u;
        u++;
    }
    return setC;
}

//дополнение вариация 2
ordered_array_set ordered_array_set_complement_fromArray(ordered_array_set setA, int *arr){
    ordered_array_set setC = ordered_array_set_create(setA.capacity);
    for(int i = 0; i < setA.capacity; i++){
        if(!ordered_array_value_in_set(setA, arr[i])){
            setC.data[setC.size] = arr[i];
            setC.size++;
        }
    }
    return setC;
}