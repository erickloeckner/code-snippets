#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *text;
    int size;
} data;

void point_func(void *inp, char *new_text) {
    data *ptr = (data *)inp;
    char *new_ptr = realloc(ptr->text, strlen(new_text) + 1);

    ptr->text = new_ptr;
    memcpy(ptr->text, new_text, strlen(new_text) + 1);

    ptr->size = strlen(ptr->text) + 1;
}

int main(void) {
    data var1;
    char *orig_text = "foobar";
  
    var1.text = malloc(strlen(orig_text) + 1);
    strncpy(var1.text, orig_text, strlen(orig_text) + 1);
    var1.size = strlen(var1.text) + 1;

    printf("struct before function:\n");
    printf("text: %s | size: %d\n\n", var1.text, var1.size);
  
    point_func((void *)&var1, "foobar2.......................");

    printf("struct after function:\n");
    printf("text: %s | size: %d\n", var1.text, var1.size);
  
    return 0;
}
