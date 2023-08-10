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

#include "Purchase.h"

/**************************************************************************
 * DEFAULT CONSTRUCTOR
 *************************************************************************/
Purchase::Purchase()
{
	memberID = 0;
	next 			 = NULL;
}

/**************************************************************************
 * OVERLOADED CONSTRUCTOR
 *************************************************************************/
Purchase::Purchase(Date	   saleDate,		// IN & CALC - Sale date
		 	 	   int	   saleMembNum,	// IN & CALC - Membership #
				   Product newProduct)	// IN & CALC - Sale quantity
{
	purchaseDate = saleDate;
	memberID 	 = saleMembNum;
	product		 = newProduct;
	next		 = NULL;
}

/**************************************************************************
 * DESTRUCTOR
 *************************************************************************/
Purchase::~Purchase() {}

/**************************************************************************
 * 								MUTATORS
 * ------------------------------------------------------------------------
 *							SetNext
 *							ValidateItemQuantityFromConsole
 *							ValidateItemPriceFromConsole
 *							ValidateItemQuantityFromFile
 *							ValidateItemPriceFromFile
 *************************************************************************/

/**************************************************************************
 * SetNext
 * 		This method sets the next node (purchase) in the list.
 *
 * 		Returns - nothing (Set next node)
 *************************************************************************/
void Purchase::SetNext(Purchase *nextNode)
{
	next = nextNode;
}

/**************************************************************************
 * ValidateItemQuantityFromConsole
 * 		This method validates the item quantity from console. Checks
 * 		that the quantity does not exceed 200 max limit.
 *
 * 		Returns - valid (bool)
 *************************************************************************/
bool Purchase::ValidateItemQuantityFromConsole(const int CHECK_INT)
												// IN & CALC - Quantity
{
	// Variable List
	bool 		  valid;	// CALC & OUT - Valid quantity
	ostringstream oss;		// CALC		  - Format error message

	cout << left;
	valid = true;

	// PROCESSING - Check if input is an integer
	if(!CHECK_INT)
	{
		// OUTPUT - Error message to input an integer
		oss  << "***** Invalid Item Quantity ";
		cout << endl << setw(ERROR_COL) << oss.str()   << " *****\n";
		oss.str("");

		oss  << "***** Total quantity of all items on a given day is between "
			 << QTY_MIN  << " and " << QTY_MAX;
		cout << setw(ERROR_COL) << oss.str()   << " *****\n\n";
		oss.str("");
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		valid = false;
	}
	// PROCESSING - Check that input is between quantity min & max
	else if(CHECK_INT < QTY_MIN || CHECK_INT > QTY_MAX)
	{
		// OUTPUT - Error message to input a valid integer
		oss  << "***** The number " << CHECK_INT << " is not a valid entry";
		cout << endl << setw(ERROR_COL) << oss.str() << " *****\n";
		oss.str("");

		oss  << "***** Total quantity of all items on a given day is between "
			 << QTY_MIN  << " and " << QTY_MAX;
		cout << setw(ERROR_COL) << oss.str()   << " *****\n\n";
		oss.str("");
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		valid = false;
	}

	cout << right;

	return valid;
}

/**************************************************************************
 * ValidateItemPriceFromConsole
 * 		This method validates the item price from console.
 *
 * 		Returns - valid (bool)
 *************************************************************************/
bool Purchase::ValidateItemPriceFromConsole(const int CHECK_FLOAT)
												// IN & CALC - Price
{
	// Variable List
	bool 		  valid;	// CALC & OUT - Valid price
	ostringstream oss;		// CALC		  - Format error message

	cout << left;
	valid = true;

	// PROCESSING - Check if valid float
	if(!CHECK_FLOAT)
	{
		// OUTPUT - Tell user to enter a valid cost (float)
		oss  << "***** Invalid Item Cost ";
		cout << endl << setw(ERROR_COL) << oss.str()   << " *****\n";
		oss.str("");

		oss  << "***** Cost of items are between "
			 << COST_MIN  << " and " << COST_MAX;
		cout << setw(ERROR_COL) << oss.str()   << " *****\n\n";
		oss.str("");
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		valid = false;
	}
	// PROCESSING - Check if price is between price min & max
	else if(CHECK_FLOAT < COST_MIN || CHECK_FLOAT > COST_MAX)
	{
		// OUTPUT - Tell user to enter price within min & max
		oss  << "***** The number " << CHECK_FLOAT << " is not a valid entry";
		cout << endl << setw(ERROR_COL) << oss.str() << " *****\n";
		oss.str("");

		oss  << "***** Total quantity of all items on a given day is between "
			 << COST_MIN  << " and " << COST_MAX;
		cout << setw(ERROR_COL) << oss.str()   << " *****\n\n";
		oss.str("");
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		valid = false;
	}

	cout << right;

	return valid;
}

/**************************************************************************
 * ValidateItemQuantityFromFile
 * 		This method validates the item quantity from input file.
 *
 * 		Returns - valid (bool)
 *************************************************************************/
bool Purchase::ValidateItemQuantityFromFile(const int CHECK_INT)
												// IN & CALC - Quantity
{
	// Variable List
	bool valid;	// CALC & OUT - Check if valid quantity

	valid = true;

	// PROCESSING - Check if file input is an integer
	if(!CHECK_INT)
	{
		valid = false;
	}
	// PROCESSING - Check file input is between qty min & max
	else if(CHECK_INT < QTY_MIN || CHECK_INT > QTY_MAX)
	{
		valid = false;
	}

	return valid;
}

/**************************************************************************
 * ValidateItemPriceFromFile
 * 		This method validates the item price from input file.
 *
 * 		Returns - valid (bool)
 *************************************************************************/
bool Purchase::ValidateItemPriceFromFile(const int CHECK_FLOAT)
											// IN & CALC - Price
{
	// Variable List
	bool 		  valid;	// CALC & OUT - Check valid price

	valid = true;

	// PROCESSING - Check if file input is a float
	if(!CHECK_FLOAT)
	{
		valid = false;
	}
	// PROCESSING - Check if file input is within min & max price
	else if(CHECK_FLOAT < COST_MIN || CHECK_FLOAT > COST_MAX)
	{
		valid = false;
	}

	return valid;
}

/**************************************************************************
 * 								ACCESSORS
 * ------------------------------------------------------------------------
 * 							GetPurchaseDate
 * 							GetMembershipNumber
 * 							GetPurchaseProduct
 * 							GetPurchasePrice
 * 							GetPurchaseQty
 * 							GetNext
 * 							PrintPurchase
 *************************************************************************/

/**************************************************************************
 * GetPurchaseDate
 * 		This method returns the purchase date of item.
 *
 * 		Returns - purchaseDate (Date)
 *************************************************************************/
Date Purchase::GetDate() const
{
	return purchaseDate;
}

/**************************************************************************
 * GetMembershipNumber
 * 		This method returns the membership number.
 *
 * 		Returns - membershipNumber (int)
 *************************************************************************/
int Purchase::GetMemberID() const
{
	return memberID;
}

/**************************************************************************
 * GetProduct
 * 		This method returns the purchase product.
 *
 * 		Returns - product (Product)
 *************************************************************************/
Product Purchase::GetProduct() const
{
	return product;
}

/**************************************************************************
 * GetNext
 * 		This method returns the next node in list (next purchase).
 *
 * 		Returns - next (Purchase)
 *************************************************************************/
Purchase* Purchase::GetNext() const
{
	return next;
}

/**************************************************************************
 * PrintPurchase
 * 		This method prints to console information about a purchase.
 * 		This includes the purchase date, the membership number, the
 * 		name of the product, the quantity of the product bought, and
 * 		the price of the product
 *
 * 		Returns - nothing (Display to console)
 *************************************************************************/
void Purchase::PrintPurchase() const
{
	// OUTPUT - Information about a purchase
	cout << left
		 << setw(DATE_COL)    << purchaseDate.DisplayDate() << " "
		 << setw(NUM_COL)     << memberID			<< " "
		 << setw(PRODUCT_COL) << product.GetName() 	<< " "
		 << "$" << right
		 << setw(SPENT_COL)   << fixed << setprecision(2)
		 << product.GetPrice()  << " "
		 << setw(QTY_COL)     << product.GetQtySold() << endl;

}
