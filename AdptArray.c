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
#include <string.h>
// the array itself
struct AdptArray_
{
    DEL_FUNC del;           // function to delete an element
    COPY_FUNC copy;         // function to copy an element
    PRINT_FUNC print;       // function to print an element
    PElement *pointers_arr; // array of pointers to elements
    int capacity;           // number of elements that can be stored in the array
};

PAdptArray CreateAdptArray(COPY_FUNC c, DEL_FUNC d, PRINT_FUNC p)
{
    PAdptArray pArray = (PAdptArray)malloc(sizeof(struct AdptArray_));
    // if allocation failed, return NULL
    if (pArray == NULL)
    {
        return NULL;
    }
    //  initialize the array
    pArray->copy = c;
    pArray->del = d;
    pArray->print = p;
    pArray->pointers_arr = (PElement *)malloc(1);
    // if allocation failed, free the array and return NULL
    if (pArray->pointers_arr == NULL)
    {
        free(pArray);
        return NULL;
    }
    pArray->capacity = 0;
    return pArray;
}
void DeleteAdptArray(PAdptArray pArray)
{
    if (pArray == NULL)
    {
        return;
    }
    // free all the elements in the array
    for (int i = 0; i < pArray->capacity; i++)
    {
        if (pArray->pointers_arr[i] != NULL)
            pArray->del(pArray->pointers_arr[i]);
    }
    // free the array itself
    free(pArray->pointers_arr);
    free(pArray);
}
// adding an element to the array
Result SetAdptArrayAt(PAdptArray pArray, int index, PElement element)
{
    // if the array is NULL, return FAIL
    if (pArray == NULL)
    {
        return FAIL;
    }
    // if the index is out of bounds, expand the array
    if (index >= pArray->capacity)
    {
        pArray->pointers_arr = (PElement *)realloc(pArray->pointers_arr, (index + 1) * sizeof(PElement));
        if (pArray->pointers_arr == NULL)
        {
            return FAIL;
        }
        for (int i = pArray->capacity; i <= index; i++)
        {
            pArray->pointers_arr[i] = NULL;
        }
        
        pArray->capacity = index + 1;
    }
    // if allocation failed, free the array and return NULL
    if (pArray->pointers_arr == NULL)
    {
        return FAIL;
    }
    else
    { // free the element that is already in the array
        if (pArray->pointers_arr[index] != NULL)
        {
            pArray->del(pArray->pointers_arr[index]);
        }
    }
    // add the copy new element to the array
    pArray->pointers_arr[index] = pArray->copy(element);
    // PrintDB(pArray);
    return SUCCESS;
}
// returns a copy of the element at the index
PElement GetAdptArrayAt(PAdptArray pArray, int index)
{
    if (pArray->capacity < index || pArray->pointers_arr[index] == NULL)
    {
        return NULL;
    }
    // return the copy of the element at the index
    return pArray->copy(pArray->pointers_arr[index]);
}

// returns the number of elements in the array
int GetAdptArraySize(PAdptArray pArray)
{
    if (pArray == NULL)
    {
        return -1;
    }
    return pArray->capacity;
}

// Prints the array according to the print function of the elements
void PrintDB(PAdptArray pArray)
{
    if (pArray == NULL)
    {
        return;
    }
    for (int i = 0; i < pArray->capacity; i++)
    {   // if the element is not NULL, print it
        if (pArray->pointers_arr[i] != NULL)
        {
            pArray->print(pArray->pointers_arr[i]);
        }
    }
}