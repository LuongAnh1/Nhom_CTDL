#include <stdio.h>
#include <stdlib.h>

struct PolyNode{
    int coef;
    int expon;
    struct PolyNode *link;
};
typedef struct PolyNode Polynom;
void In(Polynom *Poly){
    Polynom *cur = Poly;
    while(cur != NULL){
        printf("%dx^%d ", cur->coef, cur->expon);
        cur = cur->link;
    }
    printf("\n");
}
Polynom* Sap_Xep(Polynom *Poly){
    Polynom *cur = Poly;
    while(cur != NULL){
        Polynom *temp = cur->link;
        while(temp != NULL){
            if(cur->expon < temp->expon){
                int t = cur->expon;
                cur->expon = temp->expon;
                temp->expon = t;
                t = cur->coef;
                cur->coef = temp->coef;
                temp->coef = t;
            }
            temp = temp->link;
        }
        cur = cur->link;
    }
    return Poly;
}
Polynom* Don_Gt(Polynom *Poly){
    Polynom *cur=Poly;
    while(cur->link != NULL){
        if(cur->link->expon == cur->expon){
            cur->coef += cur->link->coef;
            Polynom *temp = cur->link;
            cur->link = cur->link->link;
            free(temp);
        }
        else
            cur = cur->link;
    }
    return Poly;
}
Polynom* PolyMutl(Polynom *Poly1, Polynom *Poly2){
    Polynom *Poly3 = (Polynom*)malloc(sizeof(Polynom));
    Polynom *cur1 = Poly1, *cur2, *cur3;
    int k=1;
    while(cur1 != NULL){
        cur2 = Poly2;
        while(cur2 != NULL){
            if(k==1){
                Poly3->coef = cur1->coef * cur2->coef;
                Poly3->expon = cur1->expon + cur2->expon;
                Poly3->link = NULL;
                cur3 = Poly3;
            }
            else{
                Polynom *newNode = (Polynom*)malloc(sizeof(Polynom));
                newNode->coef = cur1->coef * cur2->coef;
                newNode->expon = cur1->expon + cur2->expon;
                newNode->link = NULL;
                cur3->link = newNode;
                cur3 = newNode;
            }
            cur2 = cur2->link;
            k++;
        }
        cur1 = cur1->link;
    }
    Sap_Xep(Poly3);
    Don_Gt(Poly3);
    return Poly3;
}
Polynom* Nhap(Polynom *Poly){
    Polynom *cur = Poly;
    int n;
    printf("Nhap so phan tu cua da thuc: ");
    scanf("%d", &n);
    printf("Nhap ma tran cho da thuc: \n");
    for(int i=0;i<n;i++){
        if(i == 0){
            scanf("%d", &Poly->coef); // Hệ số
            scanf("%d", &Poly->expon); // Số mũ
            Poly->link = NULL;
        }
        else{
            Polynom *newNode = (Polynom*)malloc(sizeof(Polynom));
            scanf("%d", &newNode->coef); // Hệ số
            scanf("%d", &newNode->expon); // Số mũ
            // Nếu số mũ của newNode nhỏ hơn số mũ của cur thì thêm vào sau cur
            if(newNode->expon <= cur->expon){
                newNode->link = NULL;
                cur->link = newNode;
                cur = newNode;
            }
            else{
                Polynom *temp = Poly;
                while(newNode->expon < temp->expon)
                    temp = temp->link;
                Polynom *temp0 = Poly;
                while(temp0->link != temp && temp0->link != NULL)
                    temp0 = temp0->link;
                if(temp == Poly){
                    newNode->link = temp;
                    Poly = newNode;
                }
                else{
                    newNode->link = temp;
                    temp0->link = newNode;
                }
            }
        }
    }
    return Poly;
}
int main(){
    Polynom *Poly1, *Poly2;
    Poly1 = (Polynom*)malloc(sizeof(Polynom));
    Poly2 = (Polynom*)malloc(sizeof(Polynom));
    // Nhập dữ liệu cho Poly1
    printf("Da thuc thu nhat: \n");
    Poly1 = Nhap(Poly1);
    // Nhập dữ liệu cho Poly2
    printf("Da thuc thu nhat: \n");
    Poly2 = Nhap(Poly2);
    Polynom *Poly3;
    Poly3 = PolyMutl(Poly1, Poly2);
    In(Poly3);
    return 0;
}