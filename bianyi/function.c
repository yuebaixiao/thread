#include "function.h"

int nCompletionStatus = 0;

float add(float x, float y){
  float z = x + y;
  return z;
}

float add_and_mul(float x, float y){
  float z = add(x, y);
  z *= MUL;
  return z;
}
