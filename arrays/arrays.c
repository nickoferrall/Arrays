#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Array
{
  int capacity;    // How many elements can this array hold?
  int count;       // How many states does the array currently hold?
  char **elements; // The string elements contained in the array
} Array;

/************************************
 *
 *   CREATE, DESTROY, RESIZE FUNCTIONS
 *
 ************************************/

/*****
 * Allocate memory for a new array
 *****/
Array *create_array(int capacity)
{
  // Allocate memory for the Array struct
  Array *arr = malloc(sizeof(Array));

  // Set initial values for capacity and count
  arr->capacity = capacity;
  arr->count = 0;

  // Allocate memory for elements
  arr->elements = malloc(capacity * sizeof(char *)); // creating space for capacity * pointer

  return arr;
}

/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr)
{
  // Free all elements
  for (int i = 0; i < arr->capacity; i++)
  {
    free(arr->elements[i]);
  }

  free(arr->elements);
  // Free array
  free(arr);
}

// /*****
//  * Create a new elements array with double capacity and copy elements
//  * from old to new
//  *****/
void resize_array(Array *arr)
{

  // Create a new element storage with double capacity
  char **storage = malloc(2 * (arr->capacity * (sizeof(char *))));

  // char **storage;
  // Array **storage;
  // storage = create_array(2 * (arr->capacity));

  // Copy elements into the new storage
  for (int i = 0; i < arr->count; i++) // this is copying the pointers
  {
    storage[i] = arr->elements[i];
  }

  // Free the old elements array (but NOT the strings they point to)
  // for (int i = 0; i < strlen(&arr->elements); i++)
  // {
  //   free(&arr->elements[i]);
  // }
  free(arr->elements);
  // free(arr);

  // Update the elements and capacity to new values
  arr->capacity = 2 * (arr->capacity);
  arr->elements = storage;
  // for (int i = 0; i <= arr->count; i++)
  // {
  //   arr->elements[i] = storage[i];
  // }
}

// /************************************
//  *
//  *   ARRAY FUNCTIONS
//  *
//  ************************************/

// /*****
//  * Return the element in the array at the given index.
//  *
//  * Throw an error if the index is out of range.
//  *****/

char *arr_read(Array *arr, int index)
{

  // Throw an error if the index is greater or equal to than the current count
  if (index >= arr->count)
  {
    printf("Error: index %d is not valid.\n", index);
  }

  // Otherwise, return the element at the given index
  else
  {
    return arr->elements[index];
  }

  return 0;
}

// /*****
//  * Insert an element to the array at the given index
//  *****/
void arr_insert(Array *arr, char *element, int index)
{

  // Throw an error if the index is greater than the current count
  if (index > arr->count)
  {
    printf("Error: index is not valid.");
  }

  // Resize the array if the number of elements is over capacity
  if (strlen(element) > arr->capacity)
  {
    resize_array(arr);
  }

  // Move every element after the insert index to the right one position
  for (int i = arr->count; i > index; i--)
  {
    arr->elements[i] = arr->elements[i - 1];
  }

  // Copy the element and add it to the array
  char *copy = strdup(element);
  arr->elements[index] = copy;

  // Increment count by 1
  arr->count++;
}

// /*****
//  * Append an element to the end of the array
//  *****/
void arr_append(Array *arr, char *element)
{
  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
  if (arr->capacity <= arr->count)
  {
    resize_array(arr);
  }

  // Copy the element and add it to the end of the array

  char *copy = strdup(element);
  arr->elements[arr->count] = copy;

  // we want to copy addresses to our storage array which is arr->elements
  // char ** = address pointing to an address of a strings. Like a box holding multiple addresses
  // difficult to store strings as arrays because we don't know how long the string will be. Pointer is easier
  // use strdup. It will malloc and do the memcopy. return type will be char*
  // a pointer to the block of memory holding the string

  // Increment count by 1
  arr->count++;
}

// /*****
//  * Remove the first occurence of the given element from the array,
//  * then shift every element after that occurence to the left one slot.
//  *
//  * Throw an error if the value is not found.
//  *****/
void arr_remove(Array *arr, char *element)
{

  // Search for the first occurence of the element and remove it.
  // Don't forget to free its memory!
  int index;
  for (int i = 0; i < arr->count; i++)
  {
    if (*arr->elements[i] == *element)
    {
      free(arr->elements[i]);
      index = i;
      break;
    }
  }

  // Shift over every element after the removed element to the left one position
  for (int i = index; i < arr->count; i++)
  {
    arr->elements[i + 1] = arr->elements[i];
  }

  // Decrement count by 1
  arr->count--;
}

/*****
 * Utility function to print an array.
 *****/
void arr_print(Array *arr)
{
  printf("Beginning of print function..\n");
  printf("[");
  for (int i = 0; i < arr->count; i++)
  {
    printf("%s", arr->elements[i]);
    if (i != arr->count - 1)
    {
      printf(",");
    }
  }
  printf("]\n");
}

// #ifndef TESTING
int main(void)
{

  Array *arr = create_array(1);

  // char arr[4];
  // *arr = [ 2, 3, 4, 5 ];
  // resize_array(arr);

  // arr_insert(arr, "STRING1", 0);
  // arr_append(arr, "STRING4");
  arr_insert(arr, "STRING2", 0);
  // arr_insert(arr, "STRING3", 1);
  // arr_print(arr);
  // arr_remove(arr, "STRING3");

  // I created arr_read test
  // arr_read(arr, 0);

  arr_print(arr);

  // destroy_array(arr);

  return 0;
}
// #endif
