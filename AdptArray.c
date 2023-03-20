// Author: Anna Pinchuk
// Date: 22/03/2023
// Description: Implementation of the AdptArray.h header file, as part of exercise 1 in CPP class.
//              This file contains the implementation of the functions declared in the header file.
//              The functions are used to create an array of pointers to elements, and to manipulate it.
//              The array is dynamic, and can grow and shrink as needed.
//              The array is generic, and can store any type of element.
// credit to: course staff for the header file, and the functions' descriptions.To copilot for the comments.


#include "AdptArray.h"
#include <stdlib.h>
#include <stdio.h>      
// the array itself
struct AdptArray_ {
    DEL_FUNC del;               // function to delete an element
    COPY_FUNC copy;             // function to copy an element
    PRINT_FUNC print;           // function to print an element
    PElement* pointers_arr;     // array of pointers to elements
    int size;                   // number of elements in the array
    int capacity;               // number of elements that can be stored in the array
};

PAdptArray CreateAdptArray(COPY_FUNC c, DEL_FUNC d,PRINT_FUNC p){
    PAdptArray pArray = (PAdptArray)malloc(sizeof(PAdptArray));
    // if allocation failed, return NULL
    if (pArray == NULL)
    {
        return NULL;
    }
    //  initialize the array
    pArray->copy = c;
    pArray->del = d;
    pArray->print = p;
    pArray->size = 0;
    pArray->capacity = 1;
    pArray->pointers_arr = (PElement*)malloc(sizeof(PElement));
    // if allocation failed, free the array and return NULL
    if (pArray->pointers_arr == NULL)
    {
        free(pArray);
        return NULL;
    }
    return pArray;

} 
void DeleteAdptArray(PAdptArray pArray){
    if (pArray == NULL)
    {
        return;
    }   
    // free all the elements in the array
    for (int i = 0; i < pArray->size-1; i++)
    {
        pArray->del(pArray->pointers_arr[i]);
    }
    // free the array itself
    free(pArray->pointers_arr);
    free(pArray);
}

Result SetAdptArrayAt(PAdptArray pArray, int num, PElement element){
    

}
int GetAdptArraySize(PAdptArray pArray){
    if (pArray == NULL)
    {
        return -1;
    }
    return pArray->size;
}

// Prints the array according to the print function of the elements
void PrintDB(PAdptArray pArray){
    if (pArray == NULL)
    {
        return;
    }
    for (int i = 0; i < pArray->size-1; i++)
    {
        pArray->print(pArray->pointers_arr[i]);
    }
    
}