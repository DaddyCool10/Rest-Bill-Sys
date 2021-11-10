#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items{
	char item[20];
	float price;
	int qty;
};
struct orders{
	char customer[50];
	char date[20];
	int numOfItems;
	struct items itm[50];
};

//Functions to generate Bills
void generateBillHeader(char name[50],char date[30]){
	printf("\n\n");
		printf("        CodeZero Restaurant");
		printf("\n        -------------------");
		printf("\nDate:%s",date);
		printf("\nBill to: %s",name);
		printf("\n");
		printf("--------------------------------------\n");
		printf("Iteams\t\t");
		printf("Qty\t\t");
		printf("Total\t\t\n");
		printf("--------------------------------------\n");
		printf("\n\n");
		
}
void generateBillBody(char item[50],int qty,float price){
	printf("%s\t\t",item);
		printf("%d\t\t",qty);
		printf("%.2f\t\t",qty*price);
		printf("\n");
		
}
void generateBillFooter(float total){
	float dis=0.1*total;
	float netTotal=total-dis;
	float vat=0.13*netTotal;
	float grandTotal=netTotal+2*vat;
	printf("---------------------------------------\n");
	printf("Sub Total\t\t\t%.2f",total);
	printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
	printf("\n\t\t\t\t-------");
	printf("\nNet Total\t\t\t%.2f",netTotal);
	printf("\nVAT @13%s\t\t\t%.2f","%",vat);
	printf("\nService Charge @13%s\t\t%.2f","%",vat);
	printf("\n---------------------------------------\n");
	printf("\nGrand Total\t\t\t%.2f",grandTotal);
	printf("\n---------------------------------------\n");
	printf("\n\n\t   ---Thank You---");
	
}



int main()
{
	
	int opt,n,i;
	struct orders ord;
	struct orders order;
	char saveBill='y',contBill='y';
	char name[50];
	FILE*fp;
	//dashboard
	while(contBill=='y'){
	system("cls");	
	float total=0;	
	int billFound=0;
	printf("===========CODEZERO RESTAURANT===========");
	printf("\n\nPlease select your prefered operation:\t");
	printf("\n\n1.Generate Bill");
	printf("\n2.Show all Bills");
	printf("\n3.Search a bill");
	printf("\n4.Exit");
	
	printf("\n\nYour Choice:\t");
	scanf("%d",&opt);
	fgetc(stdin);
	switch(opt){
		case 1:
			system("cls");
			printf("\nPlease enter the name of the customer:\t");
			fgets(ord.customer,50,stdin);
			ord.customer[strlen(ord.customer)-1]=0;
			strcpy(ord.date,__DATE__);
			printf("Please enter the number of items:\t");
			scanf("%d",&n);
			ord.numOfItems=n;
			for(i=0;i<n;i++){
				fgetc(stdin);
				printf("\n\n");
				printf("Please enter the name of item %d:\t",i+1);
				fgets(ord.itm[i].item,20,stdin);
				ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
				printf("Please enter the quantity:\t");
				scanf("%d",&ord.itm[i].qty);
				printf("Please enter the unit price:\t");
				scanf("%f",&ord.itm[i].price);
				total+=ord.itm[i].qty*ord.itm[i].price;
			}
			generateBillHeader(ord.customer,ord.date);
			for(i=0;i<ord.numOfItems;i++){
			generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
				
			}
			generateBillFooter(total);
			printf("\nDo you want to save the bill [y/n]?\t");
			scanf("%s",&saveBill);
			
			if(saveBill=='y'){
				fp=fopen("RestaurantBill.txt","a+");
				fwrite(&ord,sizeof(struct orders),1,fp);
				if(fwrite!=0){
					printf("\nSuccessffully Saved");
					
				}
				else{
					printf("\nError Saving");
				}
				fclose(fp);
			}
			break;
			
		case 2:
			system("cls");
			fp=fopen("RestaurantBill.txt","r");
			printf("\n *****Your Previous Bills*****\n");
			while(fread(&order,sizeof(struct orders),1,fp)){
				float tot=0;
				generateBillHeader(order.customer,order.date);
				for(i=0;i<order.numOfItems;i++){
					generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
					tot+=order.itm[i].qty*order.itm[i].price;
				}
				generateBillFooter(tot);
			}
			fclose(fp);
			break;
		case 3:
			printf("\nEnter the name of the customer:\t");
			fgets(name,50,stdin);
			name[strlen(name)-1]=0;
			system("cls");
			fp=fopen("RestaurantBill.txt","r");
			printf("\n     *****Bill Of %s*****\n",name);
			while(fread(&order,sizeof(struct orders),1,fp)){
				float tot=0;
				if(!strcmp(order.customer,name)){
				generateBillHeader(order.customer,order.date);
				for(i=0;i<order.numOfItems;i++){
					generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
					tot+=order.itm[i].qty*order.itm[i].price;
			    }
				generateBillFooter(tot);
				billFound=1;	
				}
				
			}
			if(!billFound){
				printf("Sorry  the Bill for %s doesn't exist",name);
			}
			fclose(fp);
			break;
		case 4:
			printf("\n\t-----Thank You----- ");
			exit(0);
			break;
			
		default:
			printf("\n !!! Invalid Option !!!");
			break;			
	}
	printf("\nDo you want to perform another operation?[y/n]:\t");
	scanf("%s",&contBill);
	}
	
	printf("\n\n\n");
	
 	 return 0;
}

