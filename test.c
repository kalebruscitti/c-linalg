#include<stdio.h>

void main(){
  int i;
  for (i=0; i<11; i++){
    printf("%d\n", 1-((i&1)<<1));
  }
}
