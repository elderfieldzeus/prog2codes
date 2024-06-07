#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "cis1201.h"

/*********************************************/
/*************** MAIN FUNCTION ***************/
/*********************************************/

int main(){
	customerList CL;
	productList PL;
	productList toRestock;
	customer tempCust;
	product tempProd;
	order tempOrder;
	float tempVal;
	char tempProdID[16], tempCustID[16];
	int tempQty;
	
	char choice = -1;
	float bal = 0;
	int numItems = 0;
	float rev = 0;
	
	CL = initCustomerList();
	PL = initProductList();
	
	do{
		system("cls");
		printf("\n==========================================");
        printf("\n                MAIN MENU                 ");
        printf("\n==========================================");
        printf("\n| Total amount reloaded: Php %5.2f        ",bal);
        printf("\n| Total items sold:      %d               ",numItems);
        printf("\n| Total revenue:         Php %5.2f        ",rev);
        printf("\n==========================================");
        printf("\n| [ 1 ]    Display product list          |");
        printf("\n| [ 2 ]    Display customer list         |");
        printf("\n| [ 3 ]    Add product                   |");
        printf("\n| [ 4 ]    Add customer                  |");
        printf("\n| [ 5 ]    Reload balance                |");
        printf("\n| [ 6 ]    Sort products by price        |");
        printf("\n| [ 7 ]    Process an order              |");
        printf("\n| [ 8 ]    Get items to restock          |");
        printf("\n| [ 9 ]    Display items to restock      |");
        printf("\n| [ 0 ]    Exit                          |");
        printf("\n==========================================");
        printf("\n\nYour Choice: ");

        fflush(stdin);
        scanf("%c", &choice);
        
        switch (choice)
        {
        case '1':
			displayProductList(PL);
            break;
        case '2':
			displayCustomerList(CL);
			break;
        case '3':
        	// DONE Change the condition below to trigger the following statement if the product list is full
        	if(PL.count == MAX){
        		printf("\n ERROR: List out of space!\n");
			}else{
	        	printf("\n Enter new product ID:");
	        	fflush(stdin);
	        	scanf("%s",tempProd.ID);
	        	printf("\n Enter new product name:");
	        	fflush(stdin);
				scanf("%s",tempProd.name);
				printf("\n Enter new product price:");
	        	fflush(stdin);
				scanf("%f",&tempProd.price);
				printf("\n Enter new product quantity:");
	        	fflush(stdin);
				scanf("%d",&tempProd.qtyRemaining);
	            // Add the function call for inserting the product into the list
	            addProduct(&PL, tempProd);
	        }
            break;
        case '4':
        	// DONE Change the condition below to trigger the following statement if the customer list is full
        	if(CL.count == MAX){
        		printf("\n ERROR: List out of space!\n");
			}else{
	        	printf("\n Enter new customer ID:");
	        	fflush(stdin);
	        	scanf("%s",tempCust.ID);
	        	printf("\n Enter new customer name:");
	        	fflush(stdin);
				scanf("%s",tempCust.name);
				tempCust.balance = 0.0;
	            // Add the function call for inserting the customer into the list
	            addCustomer(&CL, tempCust);
	        }
            break;
        case '5':
        	printf("\n Enter customer ID to reload:");
        	fflush(stdin);
        	scanf("%s",tempCustID);
        	// DONE Change the condition below to trigger the following statement if the customer ID inputted does not exist in the list
        	if(findCustomer(CL, tempCustID) == FALSE){
        		printf("\n ERROR: Customer not found!\n");
			}else{
				printf("\n Enter amount to reload:");
	        	fflush(stdin);
				scanf("%f",&tempVal);
	            reloadBalance(&CL,tempCustID,tempVal);
	            bal += tempVal;
			}
            break;
        case '6':
            sortProductList(&PL);
            break;
		case '7':
			printf("\n Enter customer ID:");
        	fflush(stdin);
        	scanf("%s",tempCustID);
        	printf("\n Enter product ID:");
        	fflush(stdin);
			scanf("%s",tempProdID);
			printf("\n Enter quantity to order:");
        	fflush(stdin);
			scanf("%d",&tempQty);	
			// Uncomment and complete the code fragment below by adding the function call for processing the order.
				
					 
            tempOrder = processOrder(&CL, &PL, tempCustID, tempProdID, tempQty);
            numItems+=tempOrder.actualQty;
            rev+=tempOrder.totalPrice;
            switch(tempOrder.status){
            	case SUCCESS: printf("\n Order successful!"); break;
            	case OUT_OF_BAL: printf("\n Error: Insufficient balance!"); break;
            	case OUT_OF_STOCK: printf("\n Error: Item out of stock!"); break;
            	case ERROR: printf("\nError: Item or customer not found!"); break;
			}
			
			
            break;
        case '8':
        	// Uncomment and complete the function call below for getting the items to restock
            
			
			toRestock = getItemsToRestock(&PL);
            
			
			break;
		case '9':
			// Uncomment the line below when the function for getting items to restock is finished.
			displayProductList(toRestock);
            break;
		case '0':
            printf("\nPress any key to exit program...");
            break;
        default:
            printf("\nInvalid Choice - Please use digits only");
            break;
        }

		if(choice != '0'){
			printf("\n\nPress any key to continue...");   
		}
		fflush(stdin);
		getch();
	}while(choice!='0');
	
	return 0;
}
