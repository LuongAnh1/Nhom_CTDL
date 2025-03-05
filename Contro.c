#include <stdio.h>
#include <stdlib.h>

void Nhap1chieu(int *a, int n){
    for(int i=0;i<n;i++){
        scanf("%d",a+i);
    }
}
void Xuat1chieu(int a[], int n){
    for(int i=0;i<n;i++){
        printf("%d ",a[i]);
    }
}
void Nhap2chieu(int *a, int x, int y){
    for(int i=0;i<x;i++)
        for(int j=0;j<y;j++)
            scanf("%d",a+i*y+j);
}
int main(void){
    // Con trỏ và mảng 1 chiều
    int n,*p;
    scanf("%d",&n);
    int numb[n];
    p=numb;
    Nhap1chieu(p,n);
    Xuat1chieu(numb,n); 
//----------------------------------------------------------------------------------------------
    // Con tro va mang 2 chieu
//-----------------------------------------------------------------------------------------
    //Cách 1:
    // Sử dụng hàm malloc để cấp phát bộ nhớ và free để giải phóng bộ nhớ (ở trong thư viện stdliib.h)
    // Cần tạo x con trỏ ứng với x hàng => cần mảng mẹ để lưu x con trỏ và 1 con trỏ chỉ đến con trỏ
    int x,y;
    scanf("%d %d",&x,&y);
    // Khai báo con trỏ của con trỏ
    int **a;
    // Cấp phát bộ nhớ cho mảng mẹ
    a=(int **)malloc(sizeof(int *)*x);
    // Cấp phát bộ nhớ cho mảng con
    for(int i=0;i<x;i++)
        a[i]=(int *)malloc(sizeof(int)*y);
    // Nhập mảng 2 chiều
    for(int i=0;i<x;i++)
        for(int j=0;j<y;j++)
            scanf("%d",*(a+i)+j);
    // Xuất mảng 2 chiều
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++)
            printf("%d ",*(*(a+i)+j));
        printf("\n");
    }
    // Giải phóng bộ nhớ
    for(int i=0;i<x;i++)
        free(a[i]);
    free(a);
//----------------------------------------------------------------------------------------------    
    //Cách 2: Sử dụng hàm và coi như mảng 1 chiều
    int z,g;
    scanf("%d %d",&z,&g);
    int *numb2;
    // Cấp phát bộ nhớ cho mảng có kích thước z*g
    // Gán địa chỉ mảng lên con trỏ numb2
    numb2=(int *)malloc(sizeof(int)*z*g);
    Nhap2chieu(numb2,z,g);
    // Xuất mảng 2 chiều
    for(int i=0;i<z;i++){
        for(int j=0;j<g;j++)
            printf("%d ",*(numb2+i*g+j));
        printf("\n");
    }
    // Giải phóng bộ nhớ
    free(numb2);
    return 0;
}
