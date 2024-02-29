#include <stdio.h>


void print_sp(int n){
for(int j = n; j>=1; j--){
    printf(" ");
}
}
void print_num(int n){
    for(int j=1; j<=n;j++){
        printf("%d ", n);
    }
}
int main()
{
    int rows=6;
    int spc = rows;
    for(int i=1;i<=rows;i++){
        print_sp(spc);
        print_num(i);
    printf("\n");
    spc--;
    }

    return 0;
}
