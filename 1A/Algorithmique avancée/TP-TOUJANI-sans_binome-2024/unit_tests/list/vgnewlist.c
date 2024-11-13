#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../list/list.h"

int main(){
    List l;
    for(int i=0;i<1000;i++){
        l = newList();
    }
    free(l);
    l=NULL;
}
