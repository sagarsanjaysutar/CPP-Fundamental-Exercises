#include <iostream>

void stackPointer() {
  /**
   * Stack allocated variable. Value can be reassigned.
   */
  int data = 50;

  /**
   * Stack allocated pointer. Pointer is on stack. Data is on stack.
   * Both the pointer & the data can be changed.
   */
  int *dataPtr = &data;
  // delete dataPtr; // Cannot delete stack variable. Undefined behaviour.

  /**
   * Stack allocated "pointer array". Pointer is on stack & the data i.e. the pointers can be on stack or heap.
   * Both the pointer & the data can be changed.
   */
  int *intPtrList[4] = {dataPtr, dataPtr, dataPtr, dataPtr};
  // delete[] intPtrList; // Cannot delete stack variable. Undefined behaviour.
}

void heapPointer() {
  /**
   * Heap allocated pointer. Pointer is on stack & the data is on heap.
   * Both the pointer & the data can be changed.
   */
  int *intPtr = new int(45);

  /**
   * Heap allocated "pointer array". Pointer is on stack & the data i.e. the pointers are on heap.
   * Both the pointer & the data
   *
   * Note: This is a double pointer. It can store other pointers or point to the first element of pointer array.
   */
  int **intPtrList = new int *[4]{intPtr, intPtr, intPtr, intPtr};

  // Note: The following line can also be written as `delete intPtrList` but this is undefined behaviour.
  delete[] intPtrList;
  delete intPtr;
}

void constPointer() {
  // #00. Data is const. Pointer can be changed to point to different memory.
  const int *constDataPtr = new int(45);
  delete constDataPtr;

  // #01. Pointer is const. Data can be changed.
  int *const dataConstPtr = new int(34);
  delete dataConstPtr;

  // #02. Both Pointer & Data is const.
  const int *const constDataConstPtr = new int(34);
  delete constDataConstPtr;
}

int main() {
  stackPointer();
  heapPointer();
  constPointer();
  return 0;
}