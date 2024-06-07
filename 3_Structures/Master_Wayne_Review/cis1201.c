#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "cis1201.h"

customerList initCustomerList(){
	//initializes the customer list
	customerList CL = 
	{
	{{"111111","Customer 1",0.0},
	 {"222222","Customer 2",50.0},
	 {"333333","Customer 3",150.0},
	 {"444444","Customer 4",250.0},
	 {"555555","Customer 5",0.0},
	 {"666666","Customer 6",50.0},
	 {"777777","Customer 7",150.0},
	 {"888888","Customer 8",250.0},
	}
	,8};
	return CL;
}

productList initProductList(){
	//initializes the product list
	productList PL = 
	{
	{{"111111","Product 1",20.0,5},
	 {"222222","Product 2",50.0,5},
	 {"333333","Product 3",70.0,5},
	 {"444444","Product 4",100.0,5},
	 {"555555","Product 5",10.0,5},
	 {"666666","Product 6",40.0,5},
	 {"777777","Product 7",60.0,5},
	 {"888888","Product 8",150.0,5},
	}
	,8};
	return PL;
}

void displayProductList(productList PL){
	int x;
	int count = PL.count;
	system("cls");
	printf("\nNumber of products: %d\n",count);
	for(x=0;x<count;x++){
		printf("\n %s \t %s \t %7.2f \t Remaining: %d",PL.prod[x].ID,PL.prod[x].name,PL.prod[x].price,PL.prod[x].qtyRemaining);
	}
}

void displayCustomerList(customerList CL){
	int x;
	int count = CL.count;
	system("cls");
	printf("\nNumber of customers: %d\n",count);
	for(x=0;x<count;x++){
		printf("\n %s \t %s \t %7.2f",CL.cust[x].ID,CL.cust[x].name,CL.cust[x].balance);
	}
}

/* 5 POINTS */
boolean findCustomer(customerList CL, char ID[]){
	//Returns TRUE is the customer record with the given ID is in the list and FALSE otherwise.
	int i;

	for(i = 0; i < CL.count && strcmp(ID, CL.cust[i].ID) != 0; i++) {}

	return i == CL.count ? FALSE : TRUE;
}

boolean findProduct(productList PL, char ID[]){
	//Returns TRUE is the product record with the given ID is in the list and FALSE otherwise.
	int i;

	for(i = 0; i < PL.count && strcmp(ID, PL.prod[i].ID) != 0; i++) {}

	return i == PL.count ? FALSE : TRUE;
}

/* 5 POINTS */
void addProduct(productList *PL, product P){
	//Adds the given product record to the end of the product list only if it has not yet found in the list.
	//Otherwise, if the product record is already present, modify the record by adding the quantity found in the parameter
	//to the quantity recorded in the product list for the given item.

	int i;

	for(i = 0; i < PL->count && strcmp(P.ID, PL->prod[i].ID) != 0; i++) {}

	if(i == PL->count) {
		PL->prod[PL->count++] = P;
	}
	else {
		PL->prod[i].qtyRemaining += P.qtyRemaining;
	}
}

/* 10 POINTS */
void addCustomer(customerList *CL, customer C){
	//Inserts the given customer info into its proper sorted position in the customer list ONLY if
	//the customer info is not yet present in the list. Invoke function findCustomer() whenever necessary.

	if(findCustomer(*CL, C.ID) == FALSE) {
		int i;
		for(i = 0; i < CL->count && strcmp(C.ID, CL->cust[i].ID) > 0; i++) {}
		for(int j = ++CL->count; j > i; j--) {
			CL->cust[j] = CL->cust[j - 1];
		}

		CL->cust[i] = C;
	}
}

/* 10 POINTS */
void reloadBalance(customerList *CL, char ID[], float amount){
	//Adds the given balance into the given customer's record in the customer list.
	//In addition, this function shall output 4 lines of display:
	//(1) the customer name, 
	//(2) the customer's old balance, 
	//(3) the balance added,
	//(4) the customer's new balance.

	//assuming customer is already in list because of main code

	int i;

	for(i = 0; i < CL->count && strcmp(ID, CL->cust[i].ID) > 0; i++) {}
	

	printf("Name of customer: %s\n", CL->cust[i].name);
	printf("Old balance:\tPhp%3.2f\n", CL->cust[i].balance);
	printf("Amount added:\tPhp%3.2f\n", amount);

	CL->cust[i].balance += amount;
	printf("New balance:\tPhp%3.2f\n", CL->cust[i].balance);
}

/* 10 POINTS */
void sortProductList(productList *PL){
	//Sorts the product list by increasing order of price.
	//bubble sort

	for(int i = 0; i < PL->count; i++) {
		for(int j = 0; j < PL->count - 1 - i; j++) {
			if(PL->prod[j].price > PL->prod[j + 1].price) {
				product temp = PL->prod[j];
				PL->prod[j] = PL->prod[j + 1];
				PL->prod[j + 1] = temp;
			}
		}
	}
}

/* 30 POINTS */
order processOrder(customerList *CL, productList *PL, char custID[], char prodID[], int qty){
	//Create an order item that records the customer transacting, the product and its quantity being ordered.
	//**Process order only if both product ID and customer ID exist in the lists.
	//**If there's insufficient balance for the requested quantity, do not process the order at all. 
	//**Otherwise, supply whatever is available in stock.
	//Update the affected customer and product records accordingly by decreasing the balance and remaining quantity
	//of the customer and product.
	//Record the actual quantity supplied based on the available stock and the customer's balance.
	//Record the appropriate order status (SUCCESS/OUT_OF_BAL - insufficient balance/OUT_OF_STOCK - incomplete stock/ERROR - item not found)
	//Return the order item to the calling function.

	order O = {"XXXX", "XXXX", 0, 0, 0, ERROR};

	int i, j;

	for(i = 0; i < CL->count && strcmp(custID, CL->cust[i].ID) != 0; i++) {}
	for(j = 0; j < PL->count && strcmp(prodID, PL->prod[j].ID) != 0; j++) {}

	if(i < CL->count && j < PL->count) {
		customer *C = &CL->cust[i];
		product *P = &PL->prod[j];

		strcpy(O.customerID, custID);
		strcpy(O.productID, prodID);
		O.orderQty = qty;

		// printf("%f %f\n\n", C->balance, P->price * qty);

		if(C->balance >= P->price * qty) {
			if(P->qtyRemaining >= qty) {
				O.status = SUCCESS;
				O.actualQty = qty;
				O.totalPrice = P->price * qty;

				P->qtyRemaining -= qty;
			}
			else {
				O.status = OUT_OF_STOCK;
				O.actualQty = P->qtyRemaining;
				O.totalPrice = P->price * P->qtyRemaining;

				P->qtyRemaining = 0;
			}

			C->balance -= O.totalPrice;
		}
		else {
			O.status = OUT_OF_BAL;
		}
	}

	return O;
	
}

/* 30 POINTS */
productList getItemsToRestock(productList *PL){
	//Transfers the product records with quantity of 0 to a new list which represents the items need to be restocked
	//Note: Items that are transferred must be deleted from the original product list.
	//Return the newly created list to the calling function.

	productList zero = {.count = 0};

	int i = 0; 
	
	while(i < PL->count) {
		if(PL->prod[i].qtyRemaining == 0) {
			addProduct(&zero, PL->prod[i]);
			for(int j = i; j < PL->count - 1; j++) {
				PL->prod[j] = PL->prod[j + 1];
			}

			PL->count--;
		}
		else {
			i++;
		}
	}

	return zero;
}

