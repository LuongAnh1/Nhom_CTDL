#include <stdio.h>
#include <stdlib.h>

void Nhap(int ***a, int x, int y, int z){
    for(int i=0;i<x;i++)
        for(int j=0;j<y;j++)
            for(int k=0;k<z;k++)
                scanf("%d",*(*(a+i)+j)+k);
}
void Xuat(int ***a, int x, int y, int z){
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            for(int k=0;k<z;k++){
                printf("%d ",*(*(*(a+i)+j)+k));
            }
            printf("\n");
        }
        printf("\n");
    }
}
int main(){
    int x,y,z;
    scanf("%d %d %d",&x,&y,&z);
    int ***a;
    a=(int ***)malloc(sizeof(int **)*x);
    for(int i=0;i<x;i++){
        a[i]=(int **)malloc(sizeof(int *)*y);
        for(int j=0;j<y;j++){
            a[i][j]=(int *)malloc(sizeof(int)*z);
        }
    }
    Nhap(a,x,y,z);
    Xuat(a,x,y,z);
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            free(a[i][j]);
        }
        free(a[i]);
    }
    free(a);
    return 0;
}