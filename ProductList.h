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
#ifndef PRODUCTLIST_H_
#define PRODUCTLIST_H_

#include "Product.h"
#include "PurchasesList.h"

class ProductList
{
	public:
		//CONSTRUCTORS - DESTRUCTOR
		ProductList();
		virtual ~ProductList();

		//MUTATORS
		void 	 GetProductFromList(PurchasesList& purchases); //Gets products from a list of purchases
		void 	 AddProductByName(Product *newProduct);		   //Adds products to list in alphabetical order
		Product* SearchForProduct(string productKey);		   //Searches for a particular product

		//ACCESSORS
		Product* GetHead() const;				 //Gets head pointer
		Product* GetTail() const;				 //Gets tail pointer
		void 	 PrintProductAndQtyList() const; //Prints a list

	private:
		Product *head;			//head pointer
		Product *tail;			//tail pointer
		int		productCount;	//product count
};

#endif /* PRODUCTLIST_H_ */
