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
#ifndef PRODUCT_H_
#define PRODUCT_H_

#include "Member.h"

/*************************************************************************
 * GLOBAL CONSTANTS
 * -----------------------------------------------------------------------
 * ITEM_NAME_W		: Column width for product name
 * ITEM_QTY_W		: Column width for product quantity sold
 * ITEM_PRICE_W		: Column width for product price
 * ITEM_TOTAL_W		: Column width for product total price
 *************************************************************************/
const int ITEM_NAME_W  = 32;
const int ITEM_QTY_W   = 6;
const int ITEM_PRICE_W = 11;
const int ITEM_TOTAL_W = 9;

class Product
{
	public:
		//CONSTRUCTORS - DESTRUCTOR
		Product();
		Product(string itemName,
				float  intemPrice,
				int    itemQtySold);
		Product(Product const &someProduct);
		virtual ~Product();

		//MUTATORS
		void SetValues(string name, float cost, int qty);
		void SetNext(Product* nextNode);	//Sets next pointer
		void SetPrev(Product* prevNode);	//Sets previous pointer
		void SetQtySold(int saleQty);		//Sets product qty

		//ACCESSORS
		string 	 GetName() const;			//Gets product name
		float  	 GetPrice() const;			//Gets product price
		int		 GetQtySold() const;		//Gets qty sold
		Product* GetNext() const;			//Gets next pointer
		Product* GetPrev() const;			//Gets previous pointer
		void 	 PrintProductInfo() const;	//Prints single product

	private:
		string  productName;		//Product name
		float  	productPrice;		//Product price
		int	  	productQtySold;		//Product quantity sold
		Product *next;				//Pointer to next node
		Product *previous;			//Pointer to previous node
};

#endif /* PRODUCT_H_ */
