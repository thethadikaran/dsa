#include "darray.h"


darray_t* da_init() {
  // allocate memory for dynamic array
  darray_t *da = malloc(sizeof(darray_t));
  if (!da) return NULL;

  // initialize the members
  da->size = 0;
  da->capacity = INIT_CAPACITY;

  da->data = malloc(da->capacity * sizeof(element_t *));
  if (!da->data) {
    free(da);
    return NULL;
  }

  return da;
}



const element_t* da_get(darray_t *da, int idx) {
  if (!da || da_is_empty(da)) return NULL;

  return da->data[idx];
}



bool da_append(darray_t *da, etype_t etype, void *val) {
  if (!da || !val) return false;

  // if the array is full, then resize the array
  if (da_is_full(da)) da_resize(da);

  // create a element_t and udpate it with the value
  element_t *new_element = da_new_element(etype, val);
  if (!new_element) return false;

  // update the array with the element
  da->data[da->size++] = new_element;
  return true;
}



bool da_insert(darray_t *da, int idx, etype_t etype, void *val) {
  if (!da || !val || idx < 0 || idx > da->size) return false;

  // if the insertion is at the end
  if (idx == da->size) 
    return da_append(da, etype, val);
  
  // move the elements from idx positon to right by one
  if (!da_move_right(da, idx)) return false;

  // create a element_t and udpate it with the value
  element_t *new_element = da_new_element(etype, val);
  if (!new_element) return false;

  // finally insert the element to the position
  da->data[idx] = new_element;
  return true;
}



int da_count(darray_t *da, etype_t etype, void *val) {
  if (!da || !val || da_is_empty(da)) return 0;

  int freq = 0;

  for (int i = 0; i < da->size; i++) {
    // if the element types don't match, then skip that element
    if (da->data[i]->etype != etype) continue;

    switch (etype) {
      case INT:
        freq += da->data[i]->value.ival == *(int *)val ? 1 : 0;
        break;

      case FLO:
        freq += da->data[i]->value.fval == *(float *)val ? 1 : 0;
        break;

      case STR:
        freq += strcmp(da->data[i]->value.sval, (char *)val) == 0 ? 1 : 0;
        break;
    }
  }

  return freq;
}



int da_index(darray_t *da, etype_t etype, void *val) {
  if (!da || !val || da_is_empty(da)) return -1;

  for (int i = 0; i < da->size; i++) {
    // if the element types don't match, then skip that element
    if (da->data[i]->etype != etype) continue;

    switch (etype) {
      case INT:
        if (da->data[i]->value.ival == *(int *)val) return i;
        break;

      case FLO:
        if (da->data[i]->value.fval == *(float *)val) return i;
        break;

      case STR:
        if (strcmp(da->data[i]->value.sval, (char *)val) == 0) return i;
        break;
    }

    // if we reach here, then there is no match
    return -1;
  }
}



element_t* da_pop(darray_t *da) {
  if (!da || da_is_empty(da)) return NULL;

  return da->data[--da->size];   // caller is ezpected to free the memory
}



void da_remove(darray_t *da, etype_t etype, void *val) {
  if (!da || !val || da_is_empty(da)) return;

  // get the index of the first occurance
  int idx = da_index(da, etype, val);
  if (idx == -1) return;

  element_t *to_del = da->data[idx];
  da_free_element(to_del);

  // move the elements to the left
  da_move_left(da, idx);
}



int da_size(darray_t *da) {
  return da ? da->size : 0;
}



void da_free(darray_t *da) {
  if (!da) return;

  for (int i = 0; i < da->size; i++) {
    da_free_element(da->data[i]);
  }

  free(da);   // finally free the dynamic array
}





bool da_resize(darray_t *da) {
  if (!da) return false;

  // double the current capacity
  int new_capacity = da->capacity * SCALE_SIZE;

  // reallocate new memory with double the current capacity
  element_t **new_memory = realloc(da->data, new_capacity * sizeof(element_t *));
  if (!new_memory) return false;

  // update the values
  da->capacity = new_capacity;
  da->data = new_memory;
  return true;
}


bool da_move_right(darray_t *da, int idx) {
  if (!da || idx < 0 || idx >= da->size) return false;

  int tmp_swp;

  // if the array is full, then resize the array
  if (da_is_full(da)) da_resize(da);

  // move the element to right by one position
  for (int i = da->size-1; i >= idx; i--) {
    da->data[i + 1] = da->data[i];
  }

  da->size++;   // increase size, after moving the element
  return true;
}



bool da_move_left(darray_t *da, int idx) {
  if (!da || idx >= da->size) return false;

  int tmp_swp;

  // move the elements to the left by one position
  for (int i = idx; i < da->size - 1; i++)
    da->data[i] = da->data[i + 1];

  da->size--;   // decrease size, after removing the element
  return true;
}


/* ---------- UTIL FUNCTIONS ---------- */

bool da_is_full(darray_t *da) {
  return (da->size == da->capacity);
}

bool da_is_empty(darray_t *da) {
  return da && (da->size == 0);
}



element_t* da_new_element(etype_t etype, void *val) {
  if (!val) return NULL;

  // allocate memeory for new element
  element_t *new_element = malloc(sizeof(element_t));
  if (!new_element) return NULL;

  switch (etype) {
    case INT:
      new_element->value.ival = *(int *)val;
      break;

    case FLO:
      new_element->value.fval = *(float *)val;
      break;

    case STR:
      new_element->value.sval = strdup((char *)val);
      if (!new_element->value.sval) {
        free(new_element);
        return NULL;
      }
      break;

    default:
      free(new_element);       // invalid element type
      return NULL;
  }

  new_element->etype = etype;  // update the element type
  return new_element;
}



void da_free_element(element_t *ele) {
  if (!ele) return;

  // free allocated memeory for string element
  if (ele->etype == STR) free(ele->value.sval);

  free(ele);
}
