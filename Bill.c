#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

struct items{
    char item[20];
    float price;
    int qty;
};
struct orders{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];

};


void generateBillHeader(char name[50],char date[30]){
    printf("\n\n");

    printf("\n\t\t\t\t==========MOONLIGHT RESTAURANT==========");
    printf("\n\t\t\t\t    --------------------------------");
    printf("\n\n\t\t\tDate:%s",date);
    printf("\n\t\t\tInvoice To : %s",name);
    printf("\n\t\t\t-----------------------------------------------------\n");
    printf("\t\t\tItems");
    printf("\t\t\tQty");
    printf("\t\t\tTotal");
    printf("\n\t\t\t-----------------------------------------------------");
    printf("\t\t\t\n\n");
}

void generateBillBody(char item[30], int qty, float price){
    printf("\t\t\t%s\t\t\t",item);
    printf("%d\t\t\t",qty);
    printf("%2.f",qty*price);
    printf("\n");
}



void generateBillFooter(float total) {
    printf("\n");
    float dis = 0.1 * total;
    float netTotal = total - dis;
    float cgst = 0.09 * netTotal;
    float grandTotal = netTotal + 2 * cgst;

    printf("\t\t\t-----------------------------------------------------\n");
    printf("\t\t\tSub Total\t\t\t\t\t%.2f", total);
    printf("\n\t\t\tDiscount @10%%\t\t\t\t\t%.2f", dis);
    printf("\n\t\t\t-----------------------------------------------------\n");
    printf("\n\t\t\tNet Total\t\t\t\t\t%.2f", netTotal);
    printf("\n\t\t\tCGST @9%%\t\t\t\t\t%.2f", cgst);
    printf("\n\t\t\tCGST @9%%\t\t\t\t\t%.2f", cgst);
    printf("\n\t\t\t-----------------------------------------------------\n");
    printf("\n\t\t\tGrand Total\t\t\t\t\t%.2f", grandTotal);
    printf("\n\t\t\t-----------------------------------------------------\n\n");
}


int main(){
    struct orders ord;
    int opt,n;
    FILE *fp;
    char savebill = 'y',contFlag='y'; 
    char name[50] ;
    while(contFlag == 'y'){
    int invoiceFound = 0;
    float total =0;
    printf("\n\n\t\t===========MOONLIGHT RESTAURENT===========");
    printf("\n\n\t\t\t 1.Generatee Invoice");
    printf("\n\t\t\t 2.Show all Invoice");
    printf("\n\t\t\t 3.Search Invoice");
    printf("\n\t\t\t 4.Exit");
    printf("\n\t\t------------------------------------------");

    printf("\n\n\t\t\t Enter Your choice->");
    scanf("%d",&opt);
    
    fgetc(stdin);
     switch(opt){
        case 1:
        system("cls");
            printf("\n\t\t------------------------------------------");
            printf("\n\t\t\tPlease Enter the name of the Customer    :");
            fgets(ord.customer,50,stdin);  
            ord.customer[strlen(ord.customer)-1] = 0;
            strcpy(ord.date,__DATE__);
            printf("\n\t\t\tPlease Enter the number of items         :");
            scanf("%d",&n);
            ord.numOfItems = n;
            for(int i=0; i<n; i++){
                fgetc(stdin);
                printf("\n\n");
                printf("\t\t\tPlease enter the item %d                  :",i+1);
                fgets(ord.itm[i].item,20,stdin);
                ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
                printf("\n\t\t\tPlease enter the quantity of the item    :");
                scanf("%d",&ord.itm[i].qty);
                printf("\n\t\t\tPlease enter the unit Price              :");
                scanf("%f",&ord.itm[i].price);
                total +=ord.itm[i].qty*ord.itm[i].price; 


            }
            
            generateBillHeader(ord.customer,ord.date);
            for(int i=0; i<ord.numOfItems;i++){
                generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
            }
            generateBillFooter(total);

            printf("\n\t\t\tDo you want to save the Bill(y/n):");
            scanf("%s",&savebill);

            if(savebill == 'y'){
                fp = fopen("RestaurantBill.dat","a+");
                fwrite(&ord, sizeof(struct orders), 1, fp);
                if (fwrite(&ord, sizeof(struct orders), 1, fp) == 1) {
                    printf("\n\t\t\tSuccessfully Saved");
                } else {
                    printf("\n\t\t\tError Saving");
                 }
                fclose(fp);
            }
            break;

            case 2:
                system("cls");
                fp = fopen("RestaurantBill.dat","r");
                printf("\n  ****Your Previous Invoice****");
                while(fread(&ord,sizeof(struct orders),1,fp)){
                    float tot;
                    generateBillHeader(ord.customer,ord.date);
                    for(int i=0;i<ord.numOfItems; i++){
                        generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
                        tot += ord.itm[i].qty * ord.itm[i].price;
                    }
                    generateBillFooter(tot);
                }
                fclose(fp);
                break;
            case 3:
            printf("\n\t\t\tEnter the name of the customer:\t");
            //fgetc("stdin");
            fgets(name,50,stdin);
            name[strlen(name)-1] = 0;
                system("cls");
                fp = fopen("RestaurantBill.dat","r");
                printf("\n\t\t\t  ****Invoice of %s****",name);
                while(fread(&ord,sizeof(struct orders),1,fp)){
                    float tot;
                    if(!strcmp(ord.customer,name)){
                        generateBillHeader(ord.customer,ord.date);
                    for(int i=0;i<ord.numOfItems; i++){
                        generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
                        tot += ord.itm[i].qty * ord.itm[i].price;
                    }
                    generateBillFooter(tot);
                    invoiceFound = 1;
                    }
                    
                }
                if(!invoiceFound){
                    printf("\t\t\tsorry the invoice for %s doesnot found ",name);
                }
                fclose(fp);
                break;

            case  4:
            printf("\n\t\t\t Bye bye :");
            exit(0);
            break;

            default:  
            printf("\t\t\tSorry invalid option");
            break;

    }
    printf("\n\n\t\t\tDo you want to perform another Operation [y/n]:");
    scanf("%s",&contFlag);
    }


    return 0;
}