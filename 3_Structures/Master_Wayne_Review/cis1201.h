#ifndef CIS1201_H
#define CIS1201_H
#define MAX 10

/*********************************************/
/********* DATA STRUCTURE DEFINITION *********/
/*********************************************/

typedef struct{
	char ID[16];
	char name[64];
	float balance;
}customer; //customer info

typedef struct{
	char ID[16];
	char name[64];
	float price;
	int qtyRemaining;
}product; //product info

typedef enum{
	PENDING, SUCCESS, OUT_OF_BAL, OUT_OF_STOCK, ERROR
}orderStatus; //order status

typedef enum{
	TRUE, FALSE
}boolean;

typedef struct{
	char customerID[16];
	char productID[16];
	int orderQty;
	int actualQty;
	float totalPrice;
	orderStatus status;
}order; //order info

typedef struct{
	customer cust[MAX];
	int count;
}customerList;

typedef struct{
	product prod[MAX];
	int count;
}productList;

/*********************************************/
/************ FUNCTION PROTOTYPES ************/
/*********************************************/

customerList initCustomerList();
productList initProductList();
void displayProductList(productList PL);
void displayCustomerList(customerList CL);

boolean findCustomer(customerList CL, char ID[]);
boolean findProduct(productList PL, char ID[]);
void addProduct(productList *PL, product P);
void addCustomer(customerList *CL, customer C);
void reloadBalance(customerList *CL, char ID[], float amount);
void sortProductList(productList *PL);
order processOrder(customerList *CL, productList *PL, char custID[], char prodID[], int qty);
productList getItemsToRestock(productList *PL); 

#endif
