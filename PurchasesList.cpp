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

#include "PurchasesList.h"

/**************************************************************************
 * DEFAULT CONSTRUCTOR
 *************************************************************************/
PurchasesList::PurchasesList()
{
	head 		  = NULL;
	tail 		  = NULL;
	purchaseCount = 0;
	purchaseTotal = 0.0;
}

/**************************************************************************
 * DESTRUCTOR
 *************************************************************************/
PurchasesList::~PurchasesList() {}

/**************************************************************************
 * 								MUTATORS
 * ------------------------------------------------------------------------
 *							AddPurchaseFromFile
 *							AddPurchaseFromConsole
 *							AddPurchase
 *							AddSpentToMemberTotalFromFile
 *							AddSpentToMemberTotalFromConsole
 *							SearchForPurchaseByDate
 *							ConsoleSearchDate
 *							ValidateToBuyMore
 *************************************************************************/

/**************************************************************************
 * AddPurchaseFromFile
 * 		This method adds a purchase to the list. The information
 * 		about the purchase is received from the input list. All purchases
 * 		with valid information will be added.Once adding all the purchases,
 * 		the total spent for each member will be updated. All the items
 * 		that were purchased by one member on the same date will be
 * 		considered as one transaction process.
 *
 * 		Returns - nothing (Add purchases to list)
 *************************************************************************/
void PurchasesList::AddPurchaseFromFile(string     inputFileName,
										MemberList &theMemList)
													// IN & CALC - file name
													// IN & CALC - Mem list
{
	//VARIABLE DECLARATION
	ifstream inFile;			// CALC		 - Input file name
	Member	 *tempMem;			// CALC 	 - Temp member
	Purchase *newPurchase;		// CALC 	 - New purchase to list
	Date	 *transDate;		// CALC 	 - Transaction date
	Product	 *newProduct;		// CALC 	 - Product
	int		 transMonth;		// IN & CALC - Month
	int		 transDay;			// IN & CALC - Day
	int		 transYear;			// IN & CALC - Year
	int		 transMemberNum;	// IN & CALC - Membership #
	string	 transItem;			// IN & CALC - Name of item
	float	 transPrice;		// IN & CALC - Price of item
	int		 transQty;			// IN & CALC - Quantity of item
	bool	 validCost;			// CALC		 - Check valid cost
	bool	 validQty;			// CALC		 - Check valid quantity
	bool	 validDate;			// CALC		 - Check valid date
	bool	 validMemNum;		// CALC		 - Check valid member number
	Purchase *tempPur;
	int		 totalBuy;

	tempMem   = NULL;
	transDate = NULL;

	inFile.open(inputFileName.c_str());

	// PROCESSING - Check if file exists
	if(!inFile)
	{
		cout << "Sorry! This file is not found.\n";
	}
	else
	{
		// PROCESSING - Read & get info until end of file
		while(!inFile.eof())
		{
			// INPUT - Get purchase month
			if(!(inFile >> transMonth))
			{
				inFile.clear();
				validDate = false;
			}
			inFile.ignore(numeric_limits<streamsize>::max(), '/');

			// INPUT - Get purchase day
			if(!(inFile >> transDay))
			{
				inFile.clear();
				validDate = false;
			}
			inFile.ignore(numeric_limits<streamsize>::max(), '/');

			// INPUT - Get purchase year
			if(!(inFile >> transYear))
			{
				inFile.clear();
				validDate = false;
			}
			inFile.ignore(numeric_limits<streamsize>::max(), '\n');

			validDate = transDate->CheckDate(transMonth, transDay, transYear);

			// PROCESSING - If the input date is not valid
			if(!validDate)
			{
				if(!transMonth || !transDay || !transYear)
				{
					inFile.clear();
					inFile.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			}
			// PROCESSING - If input date is valid add Date
			else
			{
				transDate = new Date(transMonth, transDay, transYear);
			}

			// INPUT - Get & Check valid membership number
			if(!(inFile >> transMemberNum))
			{
				inFile.clear();
				validMemNum = false;
			}
			validMemNum = tempMem->ValidateMemberNumFromFile(transMemberNum);
			inFile.ignore(numeric_limits<streamsize>::max(), '\n');

			// PROCESSING - Check for valid membership number
			if(validMemNum)
			{
				// PROCESSING - Check if member exists in member list
				tempMem = theMemList.SearchForMember(transMemberNum);

				// PROCESSING - If member does NOT exist in list
				if(tempMem == NULL)
				{
					validMemNum = false;
					cout << "Sorry this Bulk Club member does not exist\n\n";
				}
				else
				{
					validMemNum = true;
				}
			}

			// INPUT - Get item name
			getline(inFile, transItem);

			// INPUT - Get price of item & check if valid
			if(!(inFile >> transPrice))
			{
				inFile.clear();
				inFile.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			validCost = newPurchase->ValidateItemPriceFromFile(transPrice);

			// INPUT - Get quantity purchased of item & check if valid
			if(!(inFile >> transQty))
			{
				inFile.clear();
				inFile.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			inFile.ignore(numeric_limits<streamsize>::max(), '\n');
			validQty = newPurchase->ValidateItemQuantityFromFile(transQty);

			// PROCESSING - If all info is valid add purchase to list
			if(validDate && validQty && validCost && validMemNum)
			{
				tempPur  = head;
				totalBuy = 0;

				while(tempPur != NULL)
				{
					if(tempPur->GetMemberID() == transMemberNum &&
					   tempPur->GetDate().GetDay() == transMonth &&
					   tempPur->GetDate().GetMonth() == transDay &&
					   tempPur->GetDate().GetYear() == transYear)
					{
						totalBuy += (transQty +
									tempPur->GetProduct().GetQtySold());

						if(totalBuy > 200)
						{
							validQty = false;
						}
					}
					tempPur = tempPur->GetNext();
				}

				if(validQty)
				{
					newProduct = new Product(transItem, transPrice,
											 transQty);

					newPurchase = new Purchase(*transDate, transMemberNum,
												*newProduct);
					AddPurchase(newPurchase);
				}
				else
				{
					cout << "Sorry, " << transMemberNum << " the maximum "
							"purchase on any given trip is 200 items. "
							"Bulk Club cannot allow the last purchase\n";
				}
			}// END IF
		} // END WHILE

		// PROCESSING - Update the total for each member that purchased items
		AddSpentToMemberTotalFromFile(theMemList, transDate);
		cout << endl;
	} // END IF-ELSE

	inFile.close();
}

/**************************************************************************
 * AddPurchaseFromConsole
 * 		This method allows a member to make a purchase from the console.
 * 		First the membership number is required. If the member number
 * 		does not exist then the user will be notified until the member
 * 		number is correct. Then the member will input information
 * 		including: transaction/purchase date (month, day, year), the
 * 		name of the item the member would like to purchase, the quantity
 * 		of that item the user would like to purchase, and the cost
 * 		of that item. The member can make as many purchases so long as
 * 		the total quantity purchase amount (200) is not exceeded.
 *
 * 		Returns - nothing (Add purchase(s) to the purchase list)
 *************************************************************************/
void PurchasesList::AddPurchaseFromConsole(MemberList &tempMemList)
{
	// Variable List
	Member	 *tempMem;		// CALC 	 - Temp member to check inputs
	Purchase *newPurchase;	// CALC 	 - Add new purchase
	Product	 *newProduct;
	int  	 memNum;		// IN & CALC - Membership #
	int  	 addTrnMonth;	// IN & CALC - Transaction month
	int  	 addTrnDay;		// IN & CALC - Transaction day
	int  	 addTrnYear;	// IN & CALC - Transaction year
	string	 itemName;		// IN & CALC - Item name to purchase
	int		 itemQty;		// IN & CALC - Quantity of item to buy
	float	 itemCost;		// IN & CALC - Cost of item
	Date 	 *addTrnDate;	// CALC		 - Full transaction date
	char	 answer;		// CALC		 - Member response to buy more
	bool	 buyMore;		// CALC		 - Check to buy more
	bool	 validCost;		// CALC		 - Check valid cost
	bool	 validQty;		// CALC		 - Check valid quantity
	bool 	 validDate;		// CALC		 - Check valid date
	bool 	 validMemNum;	// CALC		 - Check member number
	int		 count;
	Purchase *tmpPurPtr;
	bool	 foundItem;

	newPurchase = NULL;
	tempMem     = NULL;
	addTrnDate  = NULL;

	cout << "Information to purchase an item\n";

	// INPUT - Get valid member number from member & member is in list
	do
	{
		validMemNum = true;

		cout << "Membership number (5 digit #): ";
		cin >> memNum;

		// PROCESSING - Check if input is valid
		validMemNum = tempMem->ValidateMemberNumFromConsole(memNum);

		if(validMemNum)
		{
			// PROCESSING - Check if member exists in member list
			tempMem = tempMemList.SearchForMember(memNum);
		}
	}while(!validMemNum);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	if(tempMem != NULL)
	{
		// INPUT - Get valid purchase date from member
		do
		{
			cout << "PurchaseDate Date (i.e. MM/DD/YYYY): ";
			cin  >> addTrnMonth;
			cin.ignore(numeric_limits<streamsize>::max(), '/');
			cin  >> addTrnDay;
			cin.ignore(numeric_limits<streamsize>::max(), '/');
			cin  >> addTrnYear;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			validDate = addTrnDate->CheckDate(addTrnMonth, addTrnDay, addTrnYear);

			// PROCESSING - If the input date is not valid
			if(!validDate)
			{
				if(!addTrnMonth || !addTrnDay || !addTrnYear)
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			}
		}while(!validDate);

		// PROCESSING - Add transaction date since valid
		addTrnDate = new Date(addTrnMonth, addTrnDay, addTrnYear);

		// PROCESSING - Initialize variables
		buyMore = true;
		answer  = 'Y';
		count	= 0;

		// PROCESSING - Keep adding items to purchase
		while(buyMore && answer == 'Y')
		{
			// INPUT - Get name of item member would like to purcahse
			cout << "Item Name: ";
			getline(cin, itemName);

			// INPUT - Get valid quantity of item member would like to purchase
			do
			{
				validQty = true;

				cout << "Quantity of item: ";
				cin  >> itemQty;
				validQty = newPurchase->ValidateItemQuantityFromConsole(itemQty);
				count += itemQty;

				if(count >= 201)
				{
					validQty = false;
					count -= itemQty;
					cout << "Sorry over 200 item limit\n"
							" Bulk Club member has purchased " << count
						 << " items already.\n\n";
				}
				else if(count == 200)
				{
					cout << "Bulk Club member has reached the 200 item "
							"limit\n\n";
					validQty = true;
				}
			}while(!validQty);

			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			foundItem = false;
			tmpPurPtr = head;

			while(tmpPurPtr != NULL)
			{
				if(tmpPurPtr->GetProduct().GetName() == itemName)
				{
					foundItem = true;
					validCost = true;
					itemCost  = tmpPurPtr->GetProduct().GetPrice();
					cout << "Item cost: $" << itemCost << endl;
				}
				tmpPurPtr = tmpPurPtr->GetNext();
			}

			if(!foundItem)
			{
				// INPUT - Get valid price of item
				do
				{
					validCost = true;

					cout << "Price of item: ";
					cin  >> itemCost;
					validCost = newPurchase->ValidateItemPriceFromConsole(itemCost);
				}while(!validCost);
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			// PROCESSING - Only add purchase if information is valid
			if(validMemNum && validDate && validQty && validCost )
			{
				newProduct = new Product(itemName, itemCost, itemQty);

				newPurchase = new Purchase(*addTrnDate, memNum, *newProduct);

				AddPurchase(newPurchase);
			}

			// INPUT - Check if member would like to purchase more items (y/n)
			do
			{
				cout << "Would you like to purchase more items (Y/N) ";
				cin.get(answer);
				answer = toupper(answer);
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				buyMore = ValidateToBuyMore(answer);
			}while(!buyMore);
		}
	} // END WHILE

	// PROCESSING - Updating total spent with and without taxes
	AddSpentToMemberTotalFromConsole(tempMemList);
}

/**************************************************************************
 * AddPurchase
 * 		This method receives a purchase object that is to be added to
 * 		the purchase list. The purchase count is also incremented.
 *
 * 		Returns - nothing (Add purchases to list)
 *************************************************************************/
void PurchasesList::AddPurchase(Purchase *newPurchase)
{
	//VARIABLE DECLARATION
	float total;		//CALC - result of item price * item quantity

	newPurchase->SetNext(NULL);

	//PROCESSING - IF-THEN-ELSE - Used to check if the list is empty and
	//			   insert node in correct place
	if(head == NULL)
	{
		head = newPurchase;
	}
	else
	{
		tail->SetNext(newPurchase);
	}
	tail = newPurchase;

	purchaseCount++; //Increments purchase count
	total = newPurchase->GetProduct().GetPrice() *
			newPurchase->GetProduct().GetQtySold();
	purchaseTotal = purchaseTotal + total;
}

/**************************************************************************
 * AddSpentToMemberTotalFromFile
 * 		This method adds loops through all the members and the updated
 * 		purchase list. It will search for the date all of the items
 * 		that were added to be purchased that day. All those items
 * 		will then be calculated to find a total sum for that day. This
 * 		method is updating total spent from the file.
 *
 * 		Returns - nothing (Add total spent for members)
 *************************************************************************/
void PurchasesList::AddSpentToMemberTotalFromFile(MemberList &theMemList,
												  Date       *theDate)
											// IN, CALC & OUT - Mem list
											// IN & CALC	  - Date
{
	// Variable list
	Member   *tempMem;		// CALC - Temporary member list
	Purchase *tempPur;		// CALC - Temp purchase list
	float	 amtNoTax;		// CALC - Total spent without tax
	float	 amtWithTax;	// CALC - Total spent with tax

	// PROCESSING - Set values for variables
	tempMem	   = theMemList.GetHeadofList();

	// PROCESSING - Loop through each member to figure total spent
	while(tempMem != NULL)
	{
		tempPur = head;
		amtNoTax = 0;
		amtWithTax = 0;

		// PROCESSING - Loop through purchases to
		while(tempPur != NULL)
		{
			if(tempMem->GetMemberNumber() == tempPur->GetMemberID()
			   && tempPur->GetDate().GetDay() == theDate->GetDay()
			   && tempPur->GetDate().GetMonth() == theDate->GetMonth()
			   && tempPur->GetDate().GetYear() == theDate->GetYear())
			{
				amtNoTax += (tempPur->GetProduct().GetPrice() *
						tempPur->GetProduct().GetQtySold());
			}
			tempPur = tempPur->GetNext();

		}

		// PROCESSING - Calculate total spent with tax for that day
		amtWithTax = amtNoTax + (0.0875 * amtNoTax);

		// PROCESSING - Update total spent w/ tax and w/o tax for member
		tempMem->UpdateTotalSpentNoTax(amtNoTax);
		tempMem->UpdateTotalSpentPlusTax(amtWithTax);

		tempMem = tempMem->GetNext();
	}

}

/**************************************************************************
 * AddSpentToMemberTotalFromConsole
 * 		This method adds loops through all the members and the updated
 * 		purchase list. All those items will then be calculated to find a
 * 		total sum for that day. This method is updating total spent from
 * 		the console. This will not check the date because the user is
 * 		ordering again after already making a purchase that day.
 *
 * 		Returns - nothing (Add total spent for members)
 *************************************************************************/
void PurchasesList::AddSpentToMemberTotalFromConsole(MemberList &theMemList)
												// IN, CALC & OUT - mem list
{
	// Variable List
	Member   *tempMem;		// CALC - Temp member
	Purchase *tempPur;		// CALC - Temp purchase
	float	 amtNoTax;		// CALC - Total spent without tax
	float	 amtWithTax;	// CALC - Total spent with tax

	// PROCESSING - Set values for variables
	tempMem	   = theMemList.GetHeadofList();
	amtNoTax   = 0;
	amtWithTax = 0;

	// PROCESSING - Loop through each member to figure total spent
	while(tempMem != NULL)
	{
		tempPur = head;

		// PROCESSING - Loop through purchases to
		while(tempPur != NULL)
		{
			if(tempMem->GetMemberNumber() == tempPur->GetMemberID())
			{
				amtNoTax += (tempPur->GetProduct().GetPrice() *
						tempPur->GetProduct().GetQtySold());
			}
			tempPur = tempPur->GetNext();

		}

		// PROCESSING - Calculate total spent with tax for that day
		amtWithTax = amtNoTax + (0.0875 * amtNoTax);

		// PROCESSING - Update total spent w/ tax and w/o tax for member
		tempMem->UpdateTotalSpentNoTax(amtNoTax);
		tempMem->UpdateTotalSpentPlusTax(amtWithTax);

		tempMem = tempMem->GetNext();
	}

}

/**************************************************************************
 * SearchForPurchaseByDate
 * 		This method receives the current up to date member list,
 * 		and the date to search for (month, day & year). This method
 * 		will then loop through the entire purchases list and print out
 * 		to the console all the items that were purchased on this date.
 * 		It will also tell the user how many preferred members and basic
 * 		customers shopped that day. This will also calculate
 * 		the total revenue for the day with tax and without tax.
 *
 * 		Returns - nothing (Add total spent for members)
 *************************************************************************/
void PurchasesList::SearchForPurchaseByDate(MemberList &tempMemList,
									  	  	int 	   searchMonth,
											int 	   searchDay,
											int 	   searchYear)
{
	// Variable List
	Member		*tempMem;		// CALC 	  - Temp member
	Purchase 	*tempPur;		// CALC 	  - Temp purchase
	bool     	found;			// CALC 	  - Found purchase on date
	int		 	countTotMem;	// CALC 	  - Total members
	int			countBasic;		// CALC & OUT - Total basic member
	int			countPref;		// CALC & OUT - Total preferred members
	float		memTotal;		// CALC		  - Members total
	float		totalRevNoTax;	// CALC & OUT - Total revenue w/o tax
	float		totalRevWithTax;// CALC & OUT - Total revenue w/ tax
	bool		valid;			// CALC		  - Valid member of the day

	tempPur 	= head;
	tempMem 	= NULL;
	found    	= false;
	countTotMem = 0;

	// PROCESSING - Loop through entire purchase list
	while(tempPur != NULL)
	{
		// PROCESSING - Check if purchase date in list is same as search
		if(tempPur->GetDate().GetDay()   == searchDay   &&
		   tempPur->GetDate().GetMonth() == searchMonth &&
		   tempPur->GetDate().GetYear()  == searchYear)
		{
			countTotMem++;

			// PROCESSING - If member count is 1 then output header
			if(countTotMem == 1)
			{
				// OUTPUT - Print header
				cout << left
					 << setfill(' ')
					 << setw(PRODUCT_COL) << "ITEM PURCHASED" << " "
					 << setw(QTY_COL) 	  << "QUANTITY"  	  << " "
					 << setw(NAME_COL) 	  << "MEMBER NAME"    << " "
					 << setw(TYPE_COL)    << "MEMBER TYPE"    << "\n"
					 << setfill('-')
					 << setw(PRODUCT_COL) << "-" << " "
					 << setw(QTY_COL)     << "-" << " "
					 << setw(NAME_COL)    << "-" << " "
					 << setw(TYPE_COL) 	  << "-" << "\n"
					 << setfill(' ');
			}

			// OUTPUT - Display item name & quantity
			cout << setw(PRODUCT_COL) << tempPur->GetProduct().GetName() << " "
				 << setw(QTY_COL)     << tempPur->GetProduct().GetQtySold()
				 << " ";

			// PROCESSING - Search for member
			tempMem = tempMemList.SearchForMember(tempPur->GetMemberID());

			// PROCESSING - If member not found tell user no name & mem type
			if(tempMem == NULL)
			{
				cout << setw(NAME_COL) << "Name D.N.E" << " ";
				cout << setw(TYPE_COL) << "Type D.N.E" << endl;
			}
			// PROCESSING - Member is found
			else
			{
				// OUTPUT - Member name & membership type
				cout << setw(NAME_COL) << tempMem->GetName()       << " ";
				cout << setw(TYPE_COL) << tempMem->GetMemberType() << endl;
			}

			found = true;
		}
		tempPur = tempPur->GetNext();
	}

	// PROCESSING - No purchases of that date
	if(!found)
	{
		cout << "No sales report of that date\n\n";
	}

	tempMem 		= tempMemList.GetHeadofList();
	totalRevNoTax   = 0.0;
	totalRevWithTax = 0.0;
	countBasic 		= 0;
	countPref 		= 0;

	// PROCESSING - Loop through all the members
	while(tempMem != NULL)
	{
		tempPur   = head;
		memTotal  = 0.0;
		valid 	  = false;

		// PROCESSING - Loop through the purchases list
		while(tempPur != NULL)
		{
			// PROCESSING - If the purchase membership # & member membership
			//			  - number are the same & the date are the same
			//			  - then add the total to that member
			if(tempPur->GetMemberID() == tempMem->GetMemberNumber() &&
			   tempPur->GetDate().GetDay()   == searchDay   &&
			   tempPur->GetDate().GetMonth() == searchMonth &&
			   tempPur->GetDate().GetYear()  == searchYear)
			{
				valid = true;

				// PROCESSING - Update total for member for that day
				memTotal += (tempPur->GetProduct().GetPrice() *
						tempPur->GetProduct().GetQtySold());
			}

			tempPur = tempPur->GetNext();
		}

		// PROCESSING - If valid customer of the day
		if(valid == true)
		{
			// PROCESSING - Check to add basic or pref customer of the day
			if(tempMem->GetMemberType() == "Basic")
			{
				countBasic++;
			}
			else
			{
				countPref++;
			}
		}

		// PROCESSING - Calculate members' total spent for the day w/o tax
		totalRevNoTax += memTotal;

		tempMem = tempMem->GetNext();
	}

	// PROCESSING - Calculate members' total spent for the day w/ tax
	totalRevWithTax = (totalRevNoTax * .0875) + totalRevNoTax;

	// OUTPUT - Display to user # of basic cust, # of pref, & revenue
	//		  - with and without tax
	cout << "\nTotal Basic Customers: "   << countBasic 	 << endl;
	cout << "Total Preferred Customers: " << countPref  	 << endl;
	cout << "Total Revenue without tax: " << totalRevNoTax   << endl;
	cout << "Total Revenue with tax: "    << totalRevWithTax << endl << endl;
}

/**************************************************************************
 * ConsoleSearchDate
 * 		This method receives user input about a search month,
 * 		day, and year from the user. It will first validate the date.
 *
 * 		Returns - nothing (searchMonth, searchDay, searchYear by ref)
 *************************************************************************/
void PurchasesList::ConsoleSearchDate(int &searchMonth, // IN, CALC & OUT - month
									  int &searchDay,	// IN, CALC & OUT - day
									  int &searchYear)  // IN, CALC & OUT - year
{
	// Variable List
	Date *tempDate;		// CALC - Temp date
	bool validDate;		// CALC - Check valid date

	tempDate = NULL;

	// INPUT - Get a valid expiration date
	do
	{
		validDate = true;

		cout << "Enter Date (i.e. MM/DD/YYYY): ";
		cin  >> searchMonth;
		cin.ignore(numeric_limits<streamsize>::max(), '/');
		cin  >> searchDay;
		cin.ignore(numeric_limits<streamsize>::max(), '/');
		cin  >> searchYear;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		validDate = tempDate->CheckDate(searchMonth, searchDay, searchYear);

		if(!validDate)
		{
			if(!searchMonth || !searchDay || !searchYear)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
	}while(!validDate);
}

/**************************************************************************
 * ValidateToBuyMore
 * 		This method checks a character to see whether or not the member
 * 		entered a valid character. This character should be either 'Y'
 * 		or 'N' to indicate whether or not the member would like to purchase
 * 		more items.
 *
 * 		Returns - valid (bool)
 *************************************************************************/
bool PurchasesList::ValidateToBuyMore(const char CHECK_CHAR)
{
	// Variable List
	bool valid;		// CALC & OUT - Check if valid buy more input

	valid = true;

	// PROCESSING - Check if member input was either 'Y' or 'N'
	if(CHECK_CHAR != YES_BUY && CHECK_CHAR != NO_BUY)
	{
		valid = false;
	}

	return valid;
}

/**************************************************************************
 * 								ACCESSORS
 * ------------------------------------------------------------------------
 *							PrintAllMemberPurchases
 *							DisplayPurchaseHeader
 *							DisplayPurchaseList
 *							GetPurchaseCount
 *							GetPurchaseTotal
 *							GetHead
 *************************************************************************/

/**************************************************************************
 * PrintAllMemberPurchases
 * 		This method checks a character to see whether or not the member
 * 		entered a valid character. This character should be either 'Y'
 * 		or 'N' to indicate whether or not the member would like to purchase
 * 		more items.
 *
 * 		Returns - nothing (Display member purchase list to console)
 *************************************************************************/
void PurchasesList::PrintAllMemberPurchases(MemberList &tempMemList) const
{
	// Variable List
	Member		*tempMem;	// CALC - Temp member
	Purchase 	*tempPur;	// CALC - Temp pointer
	int 		countPur;	// CALC - count purchases

	tempMem	= tempMemList.GetHeadofList();
	cout << left;

	// PROCESSING - Loop through all members in the list
	while(tempMem != NULL)
	{
		countPur = 0;
		tempPur  = head;

		// OUTPUT - Purchases by member
		cout << "Purchase(s) By Member: "
			 << setw(NUM_COL) << tempMem->GetMemberNumber() << endl;

		// PROCESSING - Loop through all the purchases in the list
		while(tempPur != NULL)
		{
			// PROCESSING - Check if the membership id #s are the same
			if(tempMem->GetMemberNumber() == tempPur->GetMemberID())
			{
				countPur++;

				if(countPur == 1)
				{
					cout << setfill(' ') << left
						 << setw(PRODUCT_COL) << "PRODUCT" << " "
						 << setw(SPENT_COL+1) << "PRICE" << " "
						 << setw(QTY_COL) << "QTY" << " "
						 << setw(DATE_COL) << "DATE" << "\n"
						 << setfill('-')
						 << setw(PRODUCT_COL) << "-" << " "
						 << setw(SPENT_COL+1) << "-" << " "
						 << setw(QTY_COL) << "-" << " "
						 << setw(DATE_COL) << "-" << "\n" << setfill(' ');
				}
				// OUTPUT - Product name, price of item, & quantity of item
				//		  - the date, and add to purchase count
				cout << left;
				cout << setw(PRODUCT_COL) << tempPur->GetProduct().GetName()
					 << " " << "$" << right << fixed << setprecision(2)
					 << setw(SPENT_COL) << tempPur->GetProduct().GetPrice()
					 <<  " " << left << setprecision(6) << "  ";
				cout.unsetf(ios::fixed);
				cout << setw(QTY_COL-2) << tempPur->GetProduct().GetQtySold();
				cout << " " << tempPur->GetDate().DisplayDate();
				cout << endl;
			}
			tempPur = tempPur->GetNext();
		}

		cout << endl;

		// PROCESSING - If member did not make any purchases
		if(countPur == 0)
		{
			cout << tempMem->GetMemberNumber() << " did not make any purchases\n\n";
		}
		tempMem = tempMem->GetNext();
	}
	cout << right;
}

/**************************************************************************
 * DisplayPurchaseHeader
 * 		This method displays to the user a purchase header. These are the
 * 		all the information that is in a purchase.
 *
 * 		Returns - nothing (Display purchase table header)
 *************************************************************************/
void PurchasesList::DisplayPurchaseHeader() const
{
	// OUTPUT - Sale date, member #, item name, price, & qty
	cout << left
		 << setfill(' ')
		 << setw(DATE_COL)    << "SALE DATE"	  << " "
		 << setw(NUM_COL) 	  << "MEMBER#"		  << " "
		 << setw(PRODUCT_COL) << "ITEM PURCHASED" << " "
		 << setw(SPENT_COL+1) << "PRICE"		  << " "
		 << setw(QTY_COL) 	  << "QTY"			  << "\n"
		 << setfill('-')
		 << setw(DATE_COL)    << "-" << " "
		 << setw(NUM_COL)     << "-" << " "
		 << setw(PRODUCT_COL) << "-" << " "
		 << setw(SPENT_COL+1) << "-" << " "
		 << setw(QTY_COL)     << "-" << endl
		 << setfill(' ');
}

/**************************************************************************
 * DisplayPurchasesList
 * 		This method displays to the user all the purchases
 * 		in the purchases list.
 *
 * 		Returns - nothing (Display purchases in list)
 *************************************************************************/
void PurchasesList::DisplayPurchasesList() const
{
	// Variable List
	Purchase *current;	// CALC - Temp pointer

	current = head;

	// OUTPUT - Display purchase header table
	DisplayPurchaseHeader();

	// PROCESSING - Keep looping through purchase list until end
	while(current != NULL)
	{
		current->PrintPurchase();
		current = current->GetNext();
	}
	cout << endl;
}

/**************************************************************************
 * GetPurchaseCount
 * 		This method returns purchases count.
 *
 * 		Returns - purchaseCount (int)
 *************************************************************************/
int PurchasesList::GetPurchaseCount() const
{
	return purchaseCount;
}

/**************************************************************************
 * GetPurchaseTotal
 * 		This method returns purchaseTotal (not including tax)
 *
 * 		Returns - purchaseTotal (float)
 *************************************************************************/
float PurchasesList::GetPurchaseTotal() const
{
	return purchaseTotal;
}

/**************************************************************************
 * GetHead
 * 		This method returns the head of the purchase list. (Peek)
 *
 * 		Returns - head (Purchase)
 *************************************************************************/
Purchase* PurchasesList::GetHead() const
{
	return head;
}

/**************************************************************************
 * FindPurchasesByMember
 * 		This method receives the purchase list and the membership number.
 * 		It will loop through the purchase list until it finds the
 * 		purchases made by that member.
 *
 * 		Returns - nothing (Display purchases of a member)
 *************************************************************************/
void PurchasesList::FindPurchasesByMember(PurchasesList& purchasesFound,
									  	  int 			 membershipNum) const
{
	//VARIABLE DECLARATIONS
	Purchase *tempPtr;		//temporary pointer to traverse the list
	Purchase *newPurchase;	//pointer to create nodes for found purchases

	//VARIABLE INITIALIZATION
	tempPtr = head;

	//PROCESSING - DO-WHILE - Used to traverse the list. Exits once end of
	//			   list is reached
	while(tempPtr != NULL)
	{
		//PROCESSING - IF-THEN - Used to check if the current's node
		//			   membership number matches the search key
		if(tempPtr->GetMemberID() == membershipNum)
		{
			//Creates a new purchase node
			newPurchase = new Purchase(tempPtr->GetDate(),
									   tempPtr->GetMemberID(),
									   tempPtr->GetProduct());
			//AddPurchase - adds node to the list
			purchasesFound.AddPurchase(newPurchase);
		}
		//Moves to the next node of the list
		tempPtr = tempPtr->GetNext();
	}
}
