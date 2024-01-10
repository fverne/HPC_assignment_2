#include "util.h"

void* emalloc(size_t size)
{
  void *ptr;
  if ((ptr = malloc(sizeof(size))) == NULL)
  {
    perror("Error: Allocating memory failed.");
    exit(EXIT_FAILURE);
  }
  return ptr;
}