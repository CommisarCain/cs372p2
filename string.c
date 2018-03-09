/*
This library is meant to handle c strings
and provide some rudimentary functionality
*/
// TODO: get_delim_at function
// TODO: Comparison function accepting struct or mixture of struct and char[]
// TODO: Copy String to struct from string or other struct checking size


include <string.h>

//primary data strcture of library
struct STR{
  char* str;
  int length;
};

//returns a pointer to a dynamic string of length "length"
struct STR* new_str(int str_length){
  char* s = (char*) malloc((int) (length * sizeof(char));
  struct STR* st = (struct STR*) malloc((int)(sizeof(struct STR)));
  st->length = str_length;
  st->str = s;
  memset(st->str, '\0', str_length);
  return st;
}

// TODO: new_str_with
struct STR* new_str_with(int str_length, char* to_copy){
  char* s = (char*) malloc((int) (length * sizeof(char));
  struct STR* st = (struct STR*) malloc((int)(sizeof(struct STR)));
  st->length = str_length;
  st->str = s;
  memset(st->str, '\0', str_length);
  return st;
}

//clears the string value
void clear_str(struct STR* target){
  memset(target->str, '\0', target->length);
}

//returns the data of index in a delimited string
struct* STR get_delim_at_with(char* target, int index, char delim){
  int length = 0;
  int d_count = 0;
  int t_begin = 0;
  int t_end = 0;
  bool t_found = false;
  struct STR* st;
//from here use a while loop to iterate over string to '\0' or t_found
//the 2 t ints will tell new string length and positon. then allocate struct
// and for loop over target string section to copy it
//handle cases of string "" and no index found "" should return "" and null
//should return null

}

//frees dynamic string
void free_str(struct STR* target){
  free(target->str);
  free(target);
}
