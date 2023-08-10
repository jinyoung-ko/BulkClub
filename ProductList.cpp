
/**************************************************************************
*        __          PROGRAMMED BY       : Jinyoung Ko, Nicole Montecillo
*        \_}                             : Augusto Cabrejos, Andrew Gadbois
*       .-./--.      STUDENT ID          : 589855, 2
*     /# ^^     \                        : 3, 4
*    |           |   CLASS               : CS1C
*     \         /    SECTION             : TTH 12:30-4:20PM
*      \       /     CLASS PROJECT #1    : Bulk Club
*       `"`"`"`
*     TEAM APPLE
**************************************************************************/
#include "ProductList.h"

ProductList::ProductList()
{
	head = NULL;
	tail = NULL;
	productCount = 0;
}

ProductList::~ProductList() {}


void ProductList::GetProductFromList(PurchasesList& purchases)
{
	//VARIABLE DECLARATIONS
	Purchase *purchasesPtr;	//CALC - pointer to traverse purchases list.
	Product  *tempPtr;		//CALC - pointer to traverse current list
	Product  *newProduct;	//CALC - pointer to new product

	//VARIABLE INITIALIZATIONS
	purchasesPtr = purchases.GetHead(); //initializes to head of purchases

	//Adds first product to head of list as it is empty
	newProduct = new Product(purchasesPtr->GetProduct());
	AddProductByName(newProduct);
	purchasesPtr = purchasesPtr->GetNext();

	tempPtr = head; //Initializes tempPtr to head

	//PROCESSING - WHILE - Used to traverse the purchases list. Exits once
	//			   end of list is reached
	while(purchasesPtr != NULL)
	{
		//PROCESSING - IF-THEN-ELSE - Used to check if the new list is not
		//			   at its end and if the current product from purchases
		//			   list is not already in the new list
		if(purchasesPtr->GetProduct().GetName() != tempPtr->GetName() &&
		   tempPtr->GetNext() == NULL)
		{
			//Adds product to new list
			newProduct = new Product(purchasesPtr->GetProduct());
			AddProductByName(newProduct);

			//PROCESSING - moves to the next node
			purchasesPtr = purchasesPtr->GetNext();

			tempPtr = head; //reinitializes to head to start over
		}
		else //when product from purchases list is already in new list
		{
			//PROCESSING - IF-THEN - Checks if the products from both lists
			//			   match. If they do their quantities are added
			if(purchasesPtr->GetProduct().GetName() == tempPtr->GetName())
			{
				//CALCULATIN - adds items quantities
				tempPtr->SetQtySold(tempPtr->GetQtySold() +
									purchasesPtr->GetProduct().GetQtySold());

				//PROCESSING - moves to the next node
				purchasesPtr = purchasesPtr->GetNext();
			}
			tempPtr = tempPtr->GetNext();
		}
	}
}


void ProductList::AddProductByName(Product *newProduct)
{
	//VARIABLE DECLARATIONS
	Product *tempPtr;	//CALC - Pointer to traverse the list

	//PROCESSING - IF-THEN - Used to check if the list empty.
	if(head == NULL)
	{
		//Adds node to head of list
		head = newProduct;
		tail = newProduct;
	}
	//PROCESSING - ELSE IF-THEN - To add to the the front of the list
	else if(head->GetName() > newProduct->GetName())
	{
		//Adds to head
		newProduct->SetNext(head);
		head->SetPrev(newProduct);
		head = newProduct;
	}
	//PROCESSING - ELSE IF-THEN - To add node to the end of list
	else if(tail->GetName() < newProduct->GetName())
	{
		//Add to tail
		tail->SetNext(newProduct);
		newProduct->SetPrev(tail);
		tail = newProduct;
	}
	//PROCESSING - ELSE - To add node to the middle of the list
	else
	{
		tempPtr = head;

		//PROCESSING - WHILE - Used to traverse the list and check for the
		//					   right place to add the node (alphabetically)
		while(tempPtr != NULL && tempPtr->GetName() < newProduct->GetName())
		{
			//Moves to the next node
			tempPtr = tempPtr->GetNext();
		}

		//Sets the pointers correctly
		newProduct->SetPrev(tempPtr->GetPrev());
		newProduct->SetNext(tempPtr);
		tempPtr->GetPrev()->SetNext(newProduct);
		tempPtr->SetPrev(newProduct);
	}

	//PROCESSING - Increments product count
	productCount++;
}

Product* ProductList::SearchForProduct(string productKey)
{
	//VARIABLE DECLARATIONS
	Product *tempPtr;	//CALC - pointer to traverse the list
	bool	found;		//CALC - T/F for finding a product

	//VARIABLE DECLARATIONS
	tempPtr = head;		//Initializes tempPtr to head of list
	found 	= false;	//found initialized to false

	//PROCESSING - WHILE - Used to traverse the list. Exits once the end of
	//			   the list is reached or the item is found
	while(tempPtr != NULL && !found)
	{
		//PROCESSING - IF-THEN-ELSE - Checks if the name matches the name
		//			   to search
		if(tempPtr->GetName() == productKey)
		{
			found = true;	//found is changed true
		}
		else
		{
			tempPtr = tempPtr->GetNext();	//moves to next node
		}
	}

	return tempPtr;
}

Product* ProductList::GetHead() const
{
	return head;
}


Product* ProductList::GetTail() const
{
	return tail;
}

void ProductList::PrintProductAndQtyList() const
{
	//VARIABLE DECLARATION
	Product *displayPtr;	//Pointer to traverse the list

	//VARIABLE INITIALIZATION
	displayPtr = head;		//displayPtr is initialized to head

	//PROCESSING - WHILE - Used to traverse the list. Exits once the end of
	//			   list is reached
	while(displayPtr != NULL)
	{
		//OUTPUT - Prints the product and quantity contents of the list
		cout << setw(ITEM_NAME_W) << displayPtr->GetName()
			 << setw(ITEM_QTY_W) << displayPtr->GetQtySold()
			 << endl;

		//Moves to next node
		displayPtr = displayPtr->GetNext();
	}
	cout << endl;
}
