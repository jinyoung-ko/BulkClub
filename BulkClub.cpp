/**************************************************************************
*        __          PROGRAMMED BY       : Jinyoung Ko
*        \_}                             : Augusto Cabrejos
*       .-./--.      STUDENT ID          : 589855
*     /# ^^     \                        : 2
*    |           |   CLASS               : CS1C
*     \         /    SECTION             : TTH 12:30-4:20PM
*      \       /     CLASS PROJECT #1    : Bulk Club
*       `"`"`"`
*     TEAM APPLE
**************************************************************************/
#include "BulkClub.h"
#include "MyHeader.h"

BulkClub::BulkClub() {}

BulkClub::~BulkClub() {}

/**************************************************************************
 * AddMemberFromFile
 *************************************************************************/
void BulkClub::AddMemberFromFile(MemberList& list)
{
	string fileName;	// INPUT & CALC - file name

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Please enter member file txt name: ";
	getline(cin, fileName);

	list.AddMemberFromFile(fileName.c_str());
	cout << endl;
}

/**************************************************************************
 * AddMember (from console)
 *************************************************************************/
void BulkClub::AddMember(MemberList &tempMemList)
{
	tempMemList.AddMemberFromConsole();
}

/**************************************************************************
 * RemoveMember (from console)
 *************************************************************************/
void BulkClub::RemoveMember(MemberList &tempMemList)
{
	string  name;			// IN & CALC - name to delete
	bool	removed;		// CALC		 - Found member to remove
	int		selection;		// IN & CALC - Menu choice
	int		num;			// IN &C ALC - membership number

	if(!(tempMemList.IsEmpty()))
	{
		// INPUT - Get input menu choice
		do
		{
			cout << "Remove Member by:\n"
					"-----------------\n"
					"1 - Full name\n"
					"2 - SID #\n"
					"\nEnter choice: ";
			selection = GetAndCheckInt(1, 2);
			cout << endl;
		}while(selection == -1);
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if(selection == 1)
		{
			// INPUT - Get input name
			cout << "Enter Name: ";
			getline(cin, name);

			removed = tempMemList.RemoveMember(name);
		}
		else
		{
			// INPUT - Get input membership number
			do
			{
				cout << "Enter mem#: ";
				num = GetAndCheckInt(0, 99999);
				cout << endl;
			}while(num == -1);
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			removed = tempMemList.RemoveMember(num);
		}

		// OUTPUT - Removed successful/not
		if(!removed)
		{
			cout << "Cannot remove! Not a Bulk Club member\n\n";

		}
		else
		{
			cout << "Removed no longer a Bulk Club member\n\n";
		}
	}
	else
	{
		cout << "There are no members in Bulk Club\n\n";
	}
}

/**************************************************************************
 * RemoveAllMember
 *************************************************************************/
void BulkClub::RemoveAllMember(MemberList& memList)
{
	if(!(memList.IsEmpty()))
	{
		// PROCESSING - Clear list
		memList.ClearList();
		cout << "Removed all Bulk Club members\n\n";
	}
	else
	{
		cout << "There are no members in Bulk Club\n\n";
	}

}

/**************************************************************************
 * AddPurchasesFromFile
 *************************************************************************/
void BulkClub::AddPurchasesFromFile(PurchasesList& purList, MemberList& tempMemList)
{
	string fileName;	// IN & CALC - file name

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Please enter a purchases file txt name: ";
	getline(cin, fileName);

	purList.AddPurchaseFromFile(fileName.c_str(), tempMemList);
	cout << endl;
}

/**************************************************************************
 * AddPurchase (from console)
 *************************************************************************/
void BulkClub::AddPurchase(PurchasesList& purList, MemberList& memList)
{
	purList.AddPurchaseFromConsole(memList);
}

/**************************************************************************
 * PrintMembersList
 *************************************************************************/
void BulkClub::PrintMembersList(MemberList& memList) const
{
	if(!(memList.IsEmpty()))
	{
		cout << "LIST OF MEMBERS:" << endl;
		memList.PrintMemberList();
	}
	else
	{
		cout << "Sorry there are no Bulk Club Members!\n\n";
	}
}

/**************************************************************************
 * PrintPurchasesList
 *************************************************************************/
void BulkClub::PrintPurchasesList(PurchasesList& purList) const
{
	if(purList.GetHead() != NULL)
	{
		cout << "LIST OF PURCHASES:" << endl;
		purList.DisplayPurchasesList();
	}
	else
	{
		cout << "Sorry there are no Bulk Club purchases!\n\n";
	}
}

/**************************************************************************
 * ReportAnyDay
 *************************************************************************/
void BulkClub::ReportAnyDay(PurchasesList& purList, MemberList& memList)
{
	int aMonth;		// CALC - month
	int aDay;		// CALC - day
	int aYear;		// CALC - year

	if(purList.GetHead() != NULL)
	{
		// PROCESSING - Get date to search for, then search
		purList.ConsoleSearchDate(aMonth, aDay, aYear);
		purList.SearchForPurchaseByDate(memList, aMonth, aDay, aYear);
	}
	else
	{
		cout << "Sorry there are no Bulk Club purchases\n\n";
	}
}

/**************************************************************************
 * PurchasesbyMember
 *************************************************************************/
void BulkClub::PurchasesbyMember(MemberList& list,
								 PurchasesList& purchases)
{
	//VARIABLE DECLARATION
	string memberName;				//IN - the member name to search
	int	   memberNumber;			//IN - the membership number to search
	int	   selection;				//IN - user's selection from menu
	Member *searchResult;			//IN - the member found from search
	PurchasesList purchaseByMember;	//IN - list of purchases by member

	if(list.IsEmpty())
	{
		cout << "Sorry there are no Bulk Club members\n\n";
	}
	else
	{
		//PROCESSING - DO-WHILE - Used to prompt user to select search by name
		//			   or number. Exits once a valid selection is input
		do
		{
			cout << "Sales report: of a specific member by:" << endl
				 << "1 - Membership Number" << endl
				 << "2 - Member Name" << endl
				 << "Enter a command: ";

			selection = GetAndCheckInt(1, 2);
			cout << endl;
		}while(selection == -1);

		//PROCESSING - SWITCH - Used to call different functions bases on user
		//			   selection
		switch(selection)
		{
			case 1:	//Searches purchases by membership number
					//PROCESSING - DO-WHILE - Used to prompt user for a
					//			   membership number.
					do
					{
						//INPUT - prompts user for membership number
						cout << "Enter Membership Number: ";
						memberNumber = GetAndCheckInt(1, 99999);
						cout << endl;
					}while(memberNumber == -1);
					
					//SearchForMember - Searches list for member number
					searchResult = list.SearchForMember(memberNumber);
					
					//PROCESSING - IF-THEN-ELSE - check if membership was found
					if(searchResult == NULL)
					{
						//Output - Not found message for membership not found
						cout << "Membership #" << memberNumber << " was not "
							 <<	"found" << endl << endl;
					}
					else
					{
						//Output - Found message for when member was found
						cout << "Purchases Report for membership #"
							 << memberNumber << ": " << endl;

						//FindPurchasesByMember - finds purchases by member
						purchases.FindPurchasesByMember(purchaseByMember,
														memberNumber);

						//DisplayPurchasesList - displays list of purchases
						purchaseByMember.DisplayPurchasesList();

						cout << "Total spent: $" << fixed << setprecision(2)
							 <<	purchaseByMember.GetPurchaseTotal() << endl
							 << endl;
					}
					break;
			case 2: //Searches purchases by member name
					//INPUT - prompts user for member name
					cout << "Enter Member Name: ";
					cin.ignore(1000, '\n');
					getline(cin, memberName);
					
					//SearchForMember - searches list for member name
					searchResult = list.SearchForMember(memberName);
					cout << endl;

					//PROCESSING - IF-THEN-ESLE - Checks if list is empty
					if(searchResult == NULL)
					{
						//OUTPUT - not found message for no member found
						cout << "Member " << memberName << " was not found"
							 << endl << endl;
					}
					else
					{
						//OUTPUT - found message when member was found
						cout << "Purchases Report for member " << memberName
							 << ": " << endl;

						//PurchasesByMember - finds purchases by member
						purchases.FindPurchasesByMember(purchaseByMember,
														searchResult->GetMemberNumber());

						//DisplayPurchaseList- displays list of purchases
						purchaseByMember.DisplayPurchasesList();

						cout << "Total spent: $" << fixed << setprecision(2)
							 <<	purchaseByMember.GetPurchaseTotal() << endl
							 << endl;
					}
					break;
		} // END SWITCH
	} // END IF-ELSE
}

/**************************************************************************
 * TotalPurchasesByAllMembers
 *************************************************************************/
void BulkClub::TotalPurchasesByAllMembers(MemberList    &memList,
										  PurchasesList &purList)
{
	if(purList.GetHead() != NULL)
	{
		purList.PrintAllMemberPurchases(memList);
	}
	else
	{
		cout << "Sorry there are no Bulk Club Members\n\n";
	}
}

/**************************************************************************
 * CheckExpMembers
 *************************************************************************/
void BulkClub::CheckExpMembers(MemberList& list) //list to search
{
	//VARIABLE DECLARATIONS
	MemberList expiring;	// List that stores the expiring memberships
	int		   expMonth;	// IN - membership expiration month to search
	int		   expYear;		// IN - membership expiration year to search

	if(list.IsEmpty())
	{
		cout << "Sorry there are no Bulk Club Members\n\n";
	}
	else
	{
		cout << "CHECK FOR EXPIRING MEMBERSHIPS" << endl;

		//PROCESSING - DO-WHILE LOOP - Used to prompt the user for a month to
		//			   search and validate. Exits once a valid input is entered
		do
		{
			cout << "Enter expiration month to search: ";
			expMonth = GetAndCheckInt(EXP_MONTH_MIN, EXP_MONTH_MAX);
			if(expMonth == -1)
			{
				cout << endl;
			}
		}while(expMonth == -1);

		//PROCESSING - DO-WHILE LOOP - Used to prompt the user for a year to
		//			   search and validate. Exits once a valid input is entered
		do
		{
			cout << "Enter expiration year to search: ";
			expYear = GetAndCheckInt(EXP_YEAR_MIN, EXP_YEAR_MAX);
			if(expYear == -1)
			{
				cout << endl;
			}
		}while(expYear == -1);

		cout << endl;

		//SearchByMonth - this will search a list for nodes that contain
		//				  both expMonth and expYear entered and add them to the
		//				  expiring list object
		list.SearchByMonth(expiring, expMonth, expYear);

		//PROCESSING - IF-THEN-ELSE - Used to check if the expiring list is
		//			   empty, display message if empty, and display the list's
		//			   nodes if not empty
		if(expiring.IsEmpty())
		{
			cout << "No memberships expiring on " << expMonth << "/" << expYear
				 << " found" << endl;
		}
		else
		{
			cout << "The following memberships expiring on " << expMonth << "/"
				 << expYear << " were found:" << endl;
			expiring.PrintExpMembers();
		}
		cout << endl;
	}// END IF-ELSE
}

/**************************************************************************
 * SearchItemsSold
 *************************************************************************/
void BulkClub::SearchItemsSold(PurchasesList& purchases)
{
	//VARIABLE DECLARATIONS
	ProductList itemsSold;		//IN & OUT   - List to store the items sold
	Product	    *result;		//IN & OUT   - Stores search result
	string 		productKey;		//IN & OUT   - Product to search
	float		salesTotal;		//CALC & OUT - Product total sales price

	if(purchases.GetHead() != NULL)
	{
		itemsSold.GetProductFromList(purchases);

		//INPUT - Prompts user to enter a product name to search
		cout << "Enter a product name to search: ";
		cin.ignore(1000, '\n');
		getline(cin, productKey);

		//SearchForProduct - Searches the list for a match
		result = itemsSold.SearchForProduct(productKey);

		//PROCESSING - IF-THEN-ELSE - Used to check if the result returned
		//			   anything
		if(result == NULL)
		{
			//OUTPUT - Message if no match was found
			cout << "Product was not found" << endl;
		}
		else
		{
			//PROCESSING - Calculates the total price for a product
			salesTotal = result->GetPrice() * result->GetQtySold();

			//OUTPUT - Displays the item's details
			cout << left << setw(ITEM_NAME_W) << "PRODUCT"
				 << setw(ITEM_PRICE_W) << "PRICE"
				 << setw(ITEM_QTY_W) << "QTY"
				 << setw(ITEM_TOTAL_W) << "TOTAL"
				 << endl
				 << setw(ITEM_NAME_W) << "-----------------------------"
				 << setw(ITEM_PRICE_W) << "--------"
				 << setw(ITEM_QTY_W) << "---"
				 << setw(ITEM_TOTAL_W) << "--------"
				 << endl;

			result->PrintProductInfo();
			cout << right << setw(4) << "$"
				 << setw(ITEM_TOTAL_W-2) << salesTotal << endl << endl;
		}
	}
	else
	{
		cout << "Sorry there are no Bulk Club products\n\n";
	}
}

/**************************************************************************
 * ItemsSold
 *************************************************************************/
void BulkClub::ItemsSold(PurchasesList& purchases)
{
	//VARIABLE DECLARATION
	ProductList itemsSold; //IN & OUT - the list of products

	if(purchases.GetHead() != NULL)
	{
		//GetProductFromList - Searches purchases list and adds products to
		//					   itemsSold list. Only adds a product once
		itemsSold.GetProductFromList(purchases);

		//OUTPUT - Displays the list of items sold
		cout << left << setw(ITEM_NAME_W) << "PRODUCT"
			 << setw(ITEM_QTY_W) << "QTY SOLD" << endl
			 << setw(ITEM_NAME_W) << "-----------------------------"
			 << setw(ITEM_QTY_W) << "--------" << endl;
		itemsSold.PrintProductAndQtyList();
	}
	else
	{
		cout << "Sorry there are no Bulk Club Products\n\n";
	}
}

/**************************************************************************
 * CheckConvertToPreferred
 *************************************************************************/
void BulkClub::CheckConvertToPreferred(MemberList &memList)
{
	// Variable List
	int				choice;		// IN & CALC - Menu choice
	bool  			convert;	// CALC		 - Convert
	float 			total;		// CALC		 - Total spent
	string			name;		// IN		 - name
	Member 			*tempBasic; // CALC		 - Basic member
	PreferredMember tempPref;	// CALC		 - Pref member

	if(memList.IsEmpty())
	{
		cout << "Sorry there are no Bulk Club members\n\n";
	}
	else
	{
		// INPUT - Get menu choice
		do
		{
			cout << "Change Basic to Preferred membership\n"
					"1 - Single Basic Member\n"
					"2 - All Basic members\n"
					"Enter selection: ";

			choice = GetAndCheckInt(1, 2);
		}while(choice == -1);

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		// PROCESSING - Figure convert for Single basic member
		if(choice == 1)
		{
			// INPUT - Get name
			cout << "Please Enter a Name: ";
			getline(cin, name);

			// PROCESSING - Search for member in list
			tempBasic = memList.SearchForMember(name);

			// PROCESSING - If member is in list
			if(tempBasic != NULL)
			{
				if(tempBasic->GetMemberType() == "Basic")
				{
					// PROCESSING - Calculate if amount that would be saved if pref
					total = (tempBasic->GetTotalSpentNoTax() * tempPref.GetRebate());

					// PROCESSING - If basic member should convert to pref
					if(total > tempPref.GetAnnualDues())
					{
						cout << "Recommended to switch to a preferred customer\n\n";
						convert = true;
					}
					// PROCESSING - If basic member should remain as basic
					else
					{
						cout << "Not recommended to switch to a preferred customer\n\n";
						convert = false;
					}

					cout << tempBasic->GetName() << " has spent $"
						 << tempBasic->GetTotalSpentNoTax() << " and could "
							"accumulated a rebate of $" << fixed
						 << setprecision(2) << total << ".\n\n" << setprecision(6);
					cout.unsetf(ios::fixed);
				}
				else
				{
					cout << "Already a Preferred Member\n\n";
					convert = false;
				}
			}
			else
			{
				cout << "Sorry! " << name << "'s is not a Bulk Club Member!\n\n";
				convert = false;
			}
		}
		else
		{
			tempBasic = memList.GetHeadofList();

			// PROCESSING - Loop through member lsit
			while(tempBasic != NULL)
			{
				if(tempBasic->GetMemberType() == "Basic")
				{
					// PROCESSING - Calculate if amount that would be saved if pref
					total = (tempBasic->GetTotalSpentNoTax() * tempPref.GetRebate());

					// PROCESSING - If basic member should convert to pref
					if(total > tempPref.GetAnnualDues())
					{
						cout << tempBasic->GetName() << " is recommended to "
								"switch to a preferred customer\n";
						convert = true;
					}
					// PROCESSING - If basic member should remain as basic
					else
					{
						cout << tempBasic->GetName() << " is not recommended "
								"to switch to a preferred customer\n";
						convert = false;
					}

					cout << tempBasic->GetName() << " has spent $"
						 << tempBasic->GetTotalSpentNoTax() << " and could "
							"accumulated a rebate of $" << fixed
						 << setprecision(2) << total << ".\n\n" << setprecision(6);
					cout.unsetf(ios::fixed);
				}
				tempBasic = tempBasic->GetNext();
			} // END WHILE
		} // END IF-ELSE
	} // END IF - ELSE
}

/**************************************************************************
 * Rebate
 *************************************************************************/
void BulkClub::Rebate(MemberList &memList) const
{
	Member 			*tempMem;
	PreferredMember tempPref;
	float 			total;
	int 			count;

	if(memList.IsEmpty())
	{
		cout << "Sorry there are no Bulk Club members\n\n";
	}
	else
	{
		tempMem = memList.GetHeadofList();
		count = 0;

		while(tempMem != NULL)
		{
			if(tempMem->GetMemberType() == "Preferred")
			{
				count++;
				if(count == 1)
				{
					cout << left 			  << setfill(' ')
						 << setw(NUM_COL)     << "MEMBER ID" << " "
						 << setw(SPENT_COL+1) << "REBATE"    << "\n"
						 << setfill('-')
						 << setw(NUM_COL)  	  << "-" 		 << " "
						 << setw(SPENT_COL+1) << "-" 		 << "\n"
						 << setfill(' ');
				}
				total = (tempMem->GetTotalSpentNoTax() * tempPref.GetRebate());
				cout << left
					 << setw(NUM_COL) 	<< tempMem->GetMemberNumber() << " "
					 << fixed << setprecision(2) << "$" << right
					 << setw(SPENT_COL) << total << endl;
			}

			tempMem = tempMem->GetNext();
		}

		cout << setprecision(6) << endl;
		cout.unsetf(ios::fixed);
	} // END IF-ELSE
}

/**************************************************************************
 * PreferredToBasicConversion
 *************************************************************************/
void BulkClub::PreferredToBasicConversion(MemberList& list)
{
	//VARIABLE DECLARATIONS
	int 	selection;	//IN & CALC  - The user selection from menu
	string 	nameKey;	//IN & OUT	 - The member name to search
	float 	rebate;		//CALC & OUT - The member's annual rebate
	Member 	*result;	//IN & OUT   - Stores member search result
	Member 	*tempPtr;	//CALC & OUT - To traverse member list

	if(list.IsEmpty())
	{
		cout << "Sorry there are no Bulk Club members\n\n";
	}
	else
	{
		//VARIABLE INITIALIZATION
		tempPtr = list.GetHeadofList();

		//PROCESSING - DO-WHILE - Used to print menu and get user selection.
		//			   exits once a valid input is entered
		do
		{
			cout << "Check preferred to basic membership conversion\n"
				 << "1 - Single Preferred member\n"
				 << "2 - All Preferred members\n"
				 << "Make a selection: ";

			selection = GetAndCheckInt(1, 2);
			cout << endl;
		}while(selection == -1);

		//PROCESSING - IF-THEN-ELSE - Used to branch out into the single or all
		//			   members
		if(selection == 1)
		{
			// INPUT - Get member name
			cout << "Enter a member name: ";
			cin.ignore(1000, '\n');
			getline(cin, nameKey);
			result = list.SearchForMember(nameKey);

			// PROCESSING - Not a member
			if(result == NULL)
			{
				cout << endl <<nameKey << " is not a member of Bulk Club"
					 << endl << endl;
			}
			else
			{
				if(result->GetMemberType() == "Preferred")
				{
					rebate = result->GetTotalSpentNoTax() * .06;

					if(rebate <= result->GetAnnualDues())
					{
						cout << endl << nameKey << " is not saving money and "
							 << "should convert to basic." << endl;
					}
					else
					{
						cout << endl << nameKey << " is saving money and "
							 <<	"should not convert to basic." << endl;
					}
					cout << nameKey << " has spent $"
						 << result->GetTotalSpentNoTax() << " and accumulated "
						 << "a rebate of $" << rebate << ". " << endl << endl;
				}
				else
				{
					cout << endl << nameKey << " is not a preferred member"
						 << endl << endl;
				}
			}
		}
		else
		{
			while(tempPtr != NULL)
			{
				if(tempPtr->GetMemberType() == "Preferred")
				{
					rebate = tempPtr->GetTotalSpentNoTax() * .06;

					if(rebate <= tempPtr->GetAnnualDues())
					{
						cout << endl << tempPtr->GetName() << " is not saving "
							 << "money and should convert to basic." << endl;
					}
					else
					{
						cout << endl << tempPtr->GetName() << " is saving "
							 << "money and should not convert to basic." << endl;
					}
					cout << tempPtr->GetName() << " has spent $"
						 << tempPtr->GetTotalSpentNoTax() << " and accumulated a "
						 << "rebate of $" << rebate << ". " << endl << endl;
				}
				tempPtr = tempPtr->GetNext();
			}
		}
	} // END IF-ELSE
}

/**************************************************************************
 * MembershipsDues
 *************************************************************************/
void BulkClub::MembershipsDues(MemberList& list) //IN - the member's list
{
	//VARIABLE DECLARATIONS
	Member 	   *newMember;	//CALC - pointer to add new members
	Member 	   *tempPtr;	//CALC - to traverse the list
	MemberList duesList;	//OUT  - a list of members sorted by type/name

	if(list.IsEmpty())
	{
		cout << "Sorry there are no Bulk Club members\n\n";
	}
	else
	{
		//VARIABLE INITIALIZATION
		tempPtr = list.GetHeadofList(); //Initializes tempPtr to head

		//PROCESSING - WHILE - Used to traverse the existing list of members
		//			   and create a new list sorted by member type and name
		while(tempPtr != NULL)
		{
			//PROCESSING - IF-THEN-ESLE - Used to check membership type
			if(tempPtr->GetMemberType() == "Basic")
			{
				//Creates new Member
				newMember = new Member(tempPtr->GetName(),
									   tempPtr->GetMemberNumber(),
									   tempPtr->GetExpDate());
			}
			else if(tempPtr->GetMemberType() == "Preferred")
			{
				//Creates new PreferredMember
				newMember = new PreferredMember(tempPtr->GetName(),
											   tempPtr->GetMemberNumber(),
											   tempPtr->GetExpDate());
			}

			//Adds newMember to the new list (in memberType, name order
			duesList.InsertByMembTypeAndName(newMember);

			//Moves to next node
			tempPtr = tempPtr->GetNext();
		}

		//OUTPUT - outputs list header
		cout << left << setw(12) << "MEMBER TYPE"
			 << setw(25) << "MEMEBER NAME"
			 << setw(6) << "DUES" << endl;

		//OUTPUT - prints the list's contents
		duesList.PrintSortedMembersDue();
	} // END IF-ELSE
}

/**************************************************************************
 * SaveMembers
 *************************************************************************/
void BulkClub::SaveMembers(MemberList& memList)
{
	ofstream outFile;		// CALC & OUT - outfile
	Member	*tempMem;		// CAlC		  - members

	tempMem = memList.GetHeadofList();

	outFile.open("defaultMembers.txt");

	while(tempMem != NULL && outFile)
	{
		outFile << tempMem->GetName() << endl;
		outFile << tempMem->GetMemberNumber() << endl;
		outFile << tempMem->GetMemberType() << endl;
		outFile << tempMem->GetExpDate().GetMonth() << "/"
				<< tempMem->GetExpDate().GetDay() << "/"
				<< tempMem->GetExpDate().GetYear() << endl;
		tempMem = tempMem->GetNext();
	}

	outFile.close();
}

/**************************************************************************
 * SavePurchases
 *************************************************************************/
void BulkClub::SavePurchases(PurchasesList& purList)
{
	ofstream outFile;		// CALC & OUT - Outfile
	Purchase *tempPur;		// CALC		  - Purchases

	tempPur = purList.GetHead();

	outFile.open("defaultPurchases.txt");

	while(tempPur != NULL && outFile)
	{
		outFile << tempPur->GetDate().GetMonth() << "/"
				<< tempPur->GetDate().GetDay() << "/"
				<< tempPur->GetDate().GetYear() << endl;
		outFile << tempPur->GetMemberID() << endl;
		outFile << tempPur->GetProduct().GetName() << endl;
		outFile << tempPur->GetProduct().GetPrice() << "\t"
				<< tempPur->GetProduct().GetQtySold() << endl;
		tempPur = tempPur->GetNext();
	}

	outFile.close();
}
