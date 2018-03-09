/*
This library is meant to handle c strings
and provide some rudimentary functionality
*/
// TODO: get_delim_at function
// TODO: Comparison function accepting struct or mixture of struct and char[]
// TODO: Copy String to struct from string or other struct checking size


#include <string.h>

//primary data strcture of library
struct STR{
  char* str;
  int length;
};

//returns a pointer to a dynamic string of length "length"
struct STR* new_str(int str_length){
  char* s = (char*) malloc((int) (str_length+1 * sizeof(char)));
  struct STR* st = (struct STR*) malloc((int)(sizeof(struct STR)));
  st->length = str_length;
  st->str = s;
  memset(st->str, '\0', str_length);
  return st;
}

// TODO: new_str_with
struct STR* new_str_with(int str_length, char* to_copy){
  char* s = (char*) malloc((int) (str_length+1 * sizeof(char)));
  struct STR* st = (struct STR*) malloc((int)(sizeof(struct STR)));
  st->length = str_length;
  st->str = s;
  memset(st->str, '\0', str_length);

  int i = 0;
  while(i < str_length && to_copy[i] != '\0'){
    st->str[i] = to_copy[i];
    i++;
  }

  return st;
}

//clears the string value
void clear_str(struct STR* target){
  memset(target->str, '\0', target->length);
}

//compares the two strings within STR structs
int compare_str(struct STR* target1, struct STR* target2){

  int i = 0;
  while(i < target1->length && i < target2->length){
    if(target1->str[i] != target2->str[i] ){
      return 0;
    }
    i++;
  }
  return 1;
}

// directly compares 2 strings
int compare_string(char* target1, char* target2){

  int i = 0;
  while(target1[i] != '\0' && target2[i] != '\0'){
    if(target1[i] != target2[i] ){
      return 0;
    }
    i++;
  }
  if (target1[i] == target2[i]){
    return 1;
  }
  else{
    return 0;
  }
}

//copies a string to a STR struct string
void copy_to(struct STR* target, char* to_copy){
  int i = 0;
  while(i < target->length && to_copy[i] != '\0'){
    target->str[i] = to_copy[i];
    i++;
  }
}

//returns the data of index in a delimited string
struct STR* get_delim_at_with(char* target, int index, char delim){
  int length = 0;
  int d_count = 0;
  int t_begin = 0;
  int t_end = 0;
  int t_found = 0;
  struct STR* st;

  int i = 0;
  do{
    if(target[i] == delim){
        d_count++;
    }
    else if(d_count == index && !t_found){
      t_found = 1;
      t_begin = i;
    }
    else if(t_found && (target[i] == '\0' || target[i] == delim)){
        t_end = i;
    }


    i++;
  }while(target[i] != '\0');

  if (t_end == 0){
    return st = new_str_with(0, 0);
  }
  else{
    st = new_str(t_end - t_begin);
    for(int j = t_begin; j<t_end; j++ ){
      st->str[j-t_begin] = target[j];
    }
    return st;
  }

}

//frees dynamic string
void free_str(struct STR* target){
  free(target->str);
  free(target);
}

int main(argv){
  struct STR* s = new_str_with(10, "what");
  printf("%s\n",s->str );
  printf("%d\n",s->length );
}
