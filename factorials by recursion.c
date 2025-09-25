//FACTORIAL BY RECURSION
#include <stdio.h>
int factorial(int n){
  if (n == 0 || n == 1){
    return 1;
  }
  else
    return n * factorial(n - 1);
}
int main(){
int n = 5, result,i;
result = factorial(n);
printf ("The factorial by recursion is %d",result);


    return 0;
}