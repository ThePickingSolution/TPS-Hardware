
#include "esp_heap_caps.h"
#include "util_string.h"

char* str_part(char* str, char delimiter, int32 index){
  char *copy;
  char *result, *resultItr;
  uint32 size;

  size = 0;
  result = heap_caps_malloc(size, MALLOC_CAP_8BIT);
  //result = malloc(size);

  for (copy = str; *copy != '\0'; copy++) {
      if(*copy == delimiter){
          index--;
      }else{
        if(index == 0){
			size++;
          //result = realloc (result, size);
          result = heap_caps_realloc(result, size, MALLOC_CAP_8BIT);
          resultItr = result + size - 1;
          *resultItr = *copy;
        }else if(index < 0){
          break;
        }
      }
  }

  size++;
  //result = realloc (result, size);
  result = heap_caps_realloc(result, size, MALLOC_CAP_8BIT);
  resultItr = result + size - 1;
  *resultItr = '\0';
  return result;
}

void str_part_free(char* pointer){
    heap_caps_free(pointer);
}