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
#include "MemberList.h"
/**************************************************************************
 * 					CONSTRUCTOR & DESTRUCTOR
 *************************************************************************/

/**************************************************************************
 * DEFAULT CONSTRUCTOR
 *************************************************************************/
MemberList::MemberList() {
	headMember = NULL;
	tailMember = NULL;
	memberSize = 0;

}

/**************************************************************************
 * DESTRUCTOR
 *************************************************************************/
MemberList::~MemberList() {
	ClearList();
}

/**************************************************************************
 * 								MUTATORS
 * ------------------------------------------------------------------------
 * 							AddMemberFromFile
 * 							AddMemberFromConsole
 * 							InsertInOrder
 * 							RemoveMember
 * 							ClearList
 *************************************************************************/

/**************************************************************************
 * CreateMemberListFromFile
 * 		This method gets a file name that contains information about
 * 		the members that are to be added to Bulk Club. The information
 * 		about a member contains: full name (first & last), member number,
 * 		member type (basic or preferred), and member expiration date.
 * 		The information about a member will be stored into a list of
 * 		members.
 *
 * 		Returns - nothing (Adds members to list)
 *************************************************************************/
void MemberList::AddMemberFromFile(string fileName)
{
	// Variable List
	ifstream inFile;		// CALC      - File input
	string 	 getName;		// IN & CALC - Full name
	int		 getMemberNum;	// IN & CALC - Member number
	int		 expMonth;		// IN & CALC - Expiration month
	int		 expDay;		// IN & CALC - Expiration day
	int		 expYear;		// IN & CALC - Expiration year
	char	 memberType;	// IN & CALC - Membership type
	Date	 *newDate;		// CALC		 - Full expiration date
	Member   *newNode;		// CALC		 - Adds a member to list of members
	bool	 validMemNum;	// CALC		 - Valid member number
	bool	 validType;		// CALC		 - Valid type
	bool	 validDate;		// CALC		 - Valid date

	inFile.open(fileName.c_str());

	// PROCESSING - Check if file exists
	if(!inFile)
	{
		cout << "Sorry! This file is not found.\n";
	}
	else
	{
		// PROCESSING - Keep looping until end of input file
		while(!inFile.eof())
		{
			// INPUT - Get full name
			getline(inFile, getName);

			// INPUT - Get membership number & check if it is valid
			if(!(inFile >> getMemberNum))
			{
				validMemNum = false;
				inFile.clear();
			}
			validMemNum = newNode->ValidateMemberNumFromFile(getMemberNum);
			inFile.ignore(numeric_limits<streamsize>::max(), '\n');

			// INPUT - Get membership type and check if it is valid
			inFile.get(memberType);
			memberType = toupper(memberType);
			validType = newNode->ValidateMemberTypeFromFile(memberType);
			inFile.ignore(numeric_limits<streamsize>::max(), '\n');

			// INPUT - Get membership date and check if it is valid
			if(!(inFile >> expMonth))
			{
				inFile.clear();
				validDate = false;
			}
			inFile.ignore(numeric_limits<streamsize>::max(), '/');
			if(!(inFile >> expDay))
			{
				inFile.clear();
				validDate = false;
			}
			inFile.ignore(numeric_limits<streamsize>::max(), '/');
			if(!(inFile >> expYear))
			{
				inFile.clear();
				validDate = false;
			}
			inFile.ignore(numeric_limits<streamsize>::max(), '\n');

			validDate = newDate->CheckDate(expMonth, expDay, expYear);

			// PROCESSING - Add member if valid information
			if(validMemNum && validType && validDate && getName != " ")
			{
				// PROCESSING - Setting new date
				newDate = new Date(expMonth, expDay, expYear);

				// PROCESSING - Check if member is Basic or Preferred
				if(memberType == 'B')
				{
					// PROCESSING - Add a Basic member to the list in order
					newNode = new Member(getName, getMemberNum, *newDate);
					InsertInOrder(newNode);
				}
				else
				{
					// PROCESSING - Add a Preferred member to list in order
					newNode = new PreferredMember(getName, getMemberNum,
												  *newDate);
					InsertInOrder(newNode);
				} // END IF-ELSE (MEMBERSHIP TYPE)
			}
			else
			{
				cout << getName << " contains invalid information & cannot"
						" be a Bulk Club Member\n";
			} // END IF-ELSE (validations)
		} // END WHILE (inFile)
	} // End IF-ELSE (inFile)

	cout << endl;
	inFile.close();
}

/**************************************************************************
 * AddMemberFromConsole
 * 		This method gets information about a member that is to be
 * 		added the list of members. The following information will be
 * 		received from the user: Full name, membership id, membership
 * 		card expiration date, and membership type.
 *
 * 		Returns - nothing (Puts a member in order in the list)
 *************************************************************************/
void MemberList::AddMemberFromConsole()
{
	// Variable List
	string 	addName;		// IN & CALC - Member's name
	int		addMemNum;		// IN & CALC - Membership #
	int		addExpMonth;	// IN & CALC - Expiration month
	int		addExpDay;		// IN & CALC - Expiration day
	int		addExpYear;		// IN & CALC - Expiration year
	char	addMemType;		// IN & CALC - Membership type
	Date	*addDate;		// CALC		 - Full Date
	Member  *addMem;		// CALC		 - Member to add
	bool	validMemNum;	// CALC		 - Valid membership number
	bool	validDate;		// CALC		 - Valid date
	bool	validType;		// CALC		 - Valid membership type
	bool	validID;		// CALC		 - if membership already exists
	addMem  = NULL;
	addDate = NULL;

	// OUTPUT - Notify user filling out application to be added as a member
	cout << "Application to become a Bulk Club Member\n";

	// INPUT - Get a valid Membership Type (keep looping until valid
	do
	{
		validType = true;

		cout << "Membership Type\n"
				"---------------------\n"
				"B - Basic Member\n"
				"P - Preferred Member\n"
				"\nEnter Member Type: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get(addMemType);
		addMemType = toupper(addMemType);
		validType = addMem->ValidateMemberTypeFromConsole(addMemType);

	}while(!validType);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// INPUT - Get full name of member to add
	cout << "Enter Full Name: ";
	getline(cin, addName);

	// INPUT - Get a valid membership id #
	do
	{
		//PROCESSING - DO-WHILE - Used to check if membership ID
		//	       is valid
		do
		{
			validMemNum = true;

			cout << "Enter Membership ID: ";
			cin  >> addMemNum;
			validMemNum = addMem->ValidateMemberNumFromConsole(addMemNum);
		}
		while(!validMemNum);
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		//PROCESSING - IF-THEN-ELSE - Checks if membership already exitsts 
		if(SearchForMember(addMemNum) != NULL)
		{
			cout << endl << "Membership ID already exists" << endl << endl;
			validID = false;
		}
		else
		{
			validID = true;
		}
	}
	while(!validID);

	// INPUT - Get a valid expiration date
	do
	{
		validDate = true;

		cout << "Enter Expiration Date (i.e. MM/DD/YYYY): ";
		cin  >> addExpMonth;
		cin.ignore(numeric_limits<streamsize>::max(), '/');
		cin  >> addExpDay;
		cin.ignore(numeric_limits<streamsize>::max(), '/');
		cin  >> addExpYear;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		validDate = addDate->CheckDate(addExpMonth, addExpDay, addExpYear);

		if(!validDate)
		{
			if(!addExpMonth || !addExpDay || !addExpYear)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
	}while(!validDate);

	// PROCESSING - If all information from file is valid add member
	if(validType && validMemNum && validDate)
	{
		addDate = new Date(addExpMonth, addExpDay, addExpYear);

			// PROCESSING - Check if member is a Basic or Preferred member
			if(addMemType == 'B')
			{
				// PROCESSING - Add a Basic member to the list in order
				addMem = new Member(addName, addMemNum, *addDate);
				InsertInOrder(addMem);
			}
			else
			{
				// PROCESSING - Add a Preferred member to the list in order
				addMem = new PreferredMember(addName, addMemNum, *addDate);
				InsertInOrder(addMem);
			} // END IF-ELSE
	} // END IF

	cout << endl;
}

/**************************************************************************
 * InsertInOrder
 * 		This method gets information about a member that is to be
 * 		added the list of members. The list is ordered by the membership
 * 		number. The member size is also incremented (which counts the
 * 		number of members in the list).
 *
 * 		Returns - nothing (Puts a member in order in the list)
 *************************************************************************/
void MemberList::InsertInOrder(Member *addNode) // IN & CALC - A member
{
	// Variable List
	Member *tempPtr;	// CALC - Temporary pointer to insert in order

	// PROCESSING - If the list of members is empty add new member to
	//			  - head (beginning) and tail (end) of list
	if(headMember == NULL)
	{
		headMember = addNode;
		tailMember = addNode;
	}
	// PROCESSING - If adding to the head of the list
	else if(headMember->GetMemberNumber() > addNode->GetMemberNumber())
	{
		addNode->SetNext(headMember);
		headMember->SetPrev(addNode);
		headMember = addNode;
	}
	// PROCESSING - If adding to the tail of the list
	else if(tailMember->GetMemberNumber() < addNode->GetMemberNumber())
	{
		tailMember->SetNext(addNode);
		addNode->SetPrev(tailMember);
		tailMember = addNode;
	}
	// PROCESSING - If adding in the middle of the list
	else
	{
		tempPtr = headMember;

		// PROCESSING = Keep looping through until placement spot found
		while(tempPtr != NULL &&
			  tempPtr->GetMemberNumber() < addNode->GetMemberNumber())
		{
			tempPtr = tempPtr->GetNext();
		}

		// PROCESSING - Add new node to the list of members
		addNode->SetPrev(tempPtr->GetPrev());
		addNode->SetNext(tempPtr);

		tempPtr->GetPrev()->SetNext(addNode);
		tempPtr->SetPrev(addNode);
	}

	// PROCESSING - Increment member size
	memberSize++;
	tempPtr = NULL;
}

/**************************************************************************
 * RemoveMember
 * 		This function receives a name that is to be removed from the
 * 		list of members. This method calls the SearchForMember method
 * 		to find the location of the member to be deleted. Then the member
 * 		is removed while simultaneously updated the list of members
 * 		and updating the list of members size.
 *
 * 		Returns - found (bool)
 *************************************************************************/
bool MemberList::RemoveMember(string fullName)	// IN & CALC - Remove name
{
	// Variable List
	bool    found;		// CALC & OUT - If removed or not
	Member *tempPtr;	// CALC		  - Temp ptr to remove from list
	Member *toRemove;	// CALC		  - Ptr of member to remove

	// PROCESSING - Remove member not found & search for member to remove
	found    = false;
	toRemove = SearchForMember(fullName);

	// PROCESSING - Check that list is not empty
	if(toRemove != NULL)
	{
		tempPtr = headMember;

		// PROCESSING - Keep looping until end of list or remove item found
		while(tempPtr != NULL && !found)
		{
			// PROCESSING - If remove member is found or go to next in list
			if(tempPtr == toRemove)
			{
				found = true;
			}
			else
			{
				tempPtr = tempPtr->GetNext();
			}
		} // END - While loop
	} // END - If (toRemove != NULL)

	// PROCESSING - If member to remove is found
	if(found)
	{
		// PROCESSING - If member to remove is at the front of the list
		if(tempPtr == headMember)
		{
			headMember = headMember->GetNext();
			headMember->SetPrev(NULL);
			delete tempPtr;
		}
		// PROCESSING - If member to remove is at the end of the list
		else if(tempPtr == tailMember)
		{
			tailMember = tailMember->GetPrev();
			tailMember->SetNext(NULL);
			delete tempPtr;
		}
		// PROCESSING - If member to remove is in middle of list
		else
		{
			tempPtr->GetPrev()->SetNext(tempPtr->GetNext());
			tempPtr->GetNext()->SetPrev(tempPtr->GetPrev());
			delete tempPtr;
		}

		memberSize--;
	}

	return found;
}

/**************************************************************************
 * RemoveMember
 * 		This function receives a name that is to be removed from the
 * 		list of members. This method calls the SearchForMember method
 * 		to find the location of the member to be deleted. Then the member
 * 		is removed while simultaneously updated the list of members
 * 		and updating the list of members size.
 *
 * 		Returns - found (bool)
 *************************************************************************/
bool MemberList::RemoveMember(int removeSID)	// IN & CALC - Remove name
{
	// Variable List
	bool    found;		// CALC & OUT - If removed or not
	Member *tempPtr;	// CALC		  - Temp ptr to remove from list
	Member *toRemove;	// CALC		  - Ptr of member to remove

	// PROCESSING - Remove member not found & search for member to remove
	found = false;
	toRemove = SearchForMember(removeSID);

	// PROCESSING - Check that list is not empty
	if(toRemove != NULL)
	{
		tempPtr = headMember;

		// PROCESSING - Keep looping until end of list or remove item found
		while(tempPtr != NULL && !found)
		{
			// PROCESSING - If remove member is found or go to next in list
			if(tempPtr == toRemove)
			{
				found = true;
			}
			else
			{
				tempPtr = tempPtr->GetNext();
			}
		} // END - While loop
	} // END - If (toRemove != NULL)

	// PROCESSING - If member to remove is found
	if(found)
	{
		// PROCESSING - If member to remove is at the front of the list
		if(tempPtr == headMember)
		{
			headMember = headMember->GetNext();
			headMember->SetPrev(NULL);
			delete tempPtr;
		}
		// PROCESSING - If member to remove is at the end of the list
		else if(tempPtr == tailMember)
		{
			tailMember = tailMember->GetPrev();
			tailMember->SetNext(NULL);
			delete tempPtr;
		}
		// PROCESSING - If member to remove is in middle of list
		else
		{
			tempPtr->GetPrev()->SetNext(tempPtr->GetNext());
			tempPtr->GetNext()->SetNext(tempPtr->GetPrev());
			delete tempPtr;
		}

		memberSize--;
	}

	return found;
}

/**************************************************************************
 * ClearList
 * 		This method clears the entire list of members. This returns
 * 		a bool to indicate that the list of members has been cleared.
 *
 * 		Returns - cleared (bool)
 *************************************************************************/
bool MemberList::ClearList()
{
	// Variable List
	Member *tempPtr;	// CALC 	  - Temp ptr to clear list
	bool	cleared;	// CALC & OUT - Cleared list or not

	tempPtr = headMember;
	cleared = false;

	// PROCESSING - If list of members is already cleared
	if(headMember == NULL)
	{
		cleared = true;
	}
	// PROCESSING - Clear list
	else
	{
		// PROCESSING - Keep looping until each member is removed
		//			  - Also decrement list of member size
		while(tempPtr != NULL)
		{
			tempPtr = tempPtr->GetNext();
			delete headMember;
			headMember = tempPtr;
			memberSize--;
		}

		// PROCESSING - Ensure list of members is thoroughly cleared
		headMember = NULL;
		tailMember = NULL;
		memberSize = 0;
		cleared	   = true;
	}

	// PROCESSING - Delete temp ptr
	delete tempPtr;

	return cleared;
}

/**************************************************************************
 * 								ACCESSORS
 * ------------------------------------------------------------------------
 * 							GetHeadofList
 * 							IsEmpty
 * 							MemberListSize
 * 							SearchForMember
 * 							SearchForMember
 * 							SearchByMonth
 * 							PrintMemListHeader
 * 							PrintMemberList
 * 							PrintExpMembers
 * 							PrintAllMemberPurchase
 *************************************************************************/

/**************************************************************************
 * GetHeadofList
 * 		This method returns the head member of the list. Peeking.
 *
 * 		Returns - headMember (Member)
 *************************************************************************/
Member* MemberList::GetHeadofList() const
{
	return headMember;
}

/**************************************************************************
 * IsEmpty
 * 		This method determines whether or not the list of members is
 * 		empty or not.
 *
 * 		Returns - empty (bool)
 *************************************************************************/
bool MemberList::IsEmpty() const
{
	// Variable List
	bool empty;	// CALC & OUT - List empty or not

	empty = false;

	// PROCESSING - Check if front of list is empty
	if(headMember == NULL)
	{
		empty = true;
	}

	return empty;
}

/**************************************************************************
 * MemberListSize
 * 		This method returns the size of the member list.
 *
 * 		Returns - memberSize (int)
 *************************************************************************/
int MemberList::MemberListSize() const
{
	return memberSize;
}

/**************************************************************************
 *	SearchForMember
 *		This method searches for a member in the list. It receives a
 *		name that is to be searched for. Then it loops through the
 *		entire list of members until the member is found or the end
 *		of the list has been reached.
 *
 *		Returns - tempPtr (Member)
 *************************************************************************/
Member* MemberList::SearchForMember(string keyName) const // IN & CALC - Name
{
	// Variable List
	Member *tempPtr;	// CALC & OUT - Temp ptr to index list
	bool	found;		// CALC		  - Find name

	tempPtr = headMember;
	found   = false;

	// Processing - Keep looping until member found or end of list
	while(tempPtr != NULL && !found)
	{
		if(tempPtr->GetName() == keyName)
		{
			found = true;
		}
		else
		{
			tempPtr = tempPtr->GetNext();
		}
	}

	return tempPtr;
}

/**************************************************************************
 *	SearchForMember
 *		This method searches for a member in the list. It receives a
 *		member number that is to be searched for. Then it loops through
 *		the entire list of members until the member is found or the end
 *		of the list has been reached.
 *
 *		Returns - tempPtr (Member)
 *************************************************************************/
Member* MemberList::SearchForMember(int keyNum) const // IN & CALC - Name
{
	// Variable List
	Member *tempPtr;	// CALC & OUT - Temp ptr to index list
	bool	found;		// CALC		  - Find membership number

	tempPtr = headMember;
	found   = false;

	// Processing - Keep looping until member found or end of list
	while(tempPtr != NULL && !found)
	{
		if(tempPtr->GetMemberNumber() == keyNum)
		{
			found = true;
		}
		else
		{
			tempPtr = tempPtr->GetNext();
		}
	}

	return tempPtr;
}

/**************************************************************************
 *	SearchByMonth
 *		This method receives a list for expiring members, a month search
 *		key, and a year search key. The method then traverses the list
 *		searching for a match for month and year. If a match is found, the
 *		node's content is added to the expMembers list.
 *		Returns - nothing
 *************************************************************************/
void MemberList::SearchByMonth(MemberList& expMembers,    //List to fill
							   int 		   monthKey, 	  //month search key
							   int 		   yearKey) const //year search key
{
	//VARIABLE DECLARATIONS
	Member *tempPtr;	//temporary pointer to traverse the list
	Member *expMember;	//pointer to create new nodes for expiring members

	//VARIABLE INITIALIZATIONS
	tempPtr = headMember;	//Initializes tempPtr to head pointer of list

	//PROCESSING - DO-WHILE - Used to traverse the list. Exits once end of
	//			   list is reached
	while(tempPtr != NULL)
	{
		//PROCESSING - IF-THEN - Used to check if the current node's month
		//			   and year match the monthKye and yearKey
		if(tempPtr->GetExpDate().GetMonth() == monthKey &&
		   tempPtr->GetExpDate().GetYear() == yearKey)
		{
			//PROCESSING - IF-THEN-ELSE - Used to check if the member found
			//			   is a Basic or Preferred member
			if(tempPtr->GetMemberType() == "Basic")
			{
				//Creates a new Member node
				expMember = new Member(tempPtr->GetName(),
							   	   tempPtr->GetMemberNumber(),
								   tempPtr->GetExpDate());
			}
			else
			{
				//Creates a new PreferredMember node
				expMember = new PreferredMember(tempPtr->GetName(),
					   	   	   	   	   	   	    tempPtr->GetMemberNumber(),
												tempPtr->GetExpDate());
			}
			//InsertInOder - adds node to the list
			expMembers.InsertInOrder(expMember);
		}
		//Moves to the next node of the list
		tempPtr = tempPtr->GetNext();
	}
}

/**************************************************************************
 *	PrintMemListHeader
 *		This method prints the membership list header for the table.
 *		This includes the member name, member type, member number,
 *		total spent, expiration date, and rebate.
 *
 *		Returns - nothing (Prints header to console)
 *************************************************************************/
void MemberList::PrintMemListHeader() const
{
	// OUTPUT - Display header for table
	cout << left;
	cout << setfill(' ');
	cout << setw(NAME_COL)  << "MEMBER NAME"   << setw(COL_SPACE) << " ";
	cout << setw(TYPE_COL)  << "MEMBER TYPE"   << setw(COL_SPACE) << " ";
	cout << setw(NUM_COL)   << "MEMBER #"      << setw(COL_SPACE) << "  ";
	cout << right 			<< fixed 		   << setprecision(2);
	cout << setw(SPENT_COL) << "TOTAL SPENT"
		 << setw(COL_SPACE) << " ";
	cout << left 			<< setprecision(6);
	cout.unsetf(ios::fixed);
	cout << setw(DATE_COL)  << "EXPIRATION DATE"
		 << setw(COL_SPACE) << " "
		 << setw(REBATE_COL) << "REBATE\n";
	cout << setfill('-');
	cout << setw(NAME_COL)  << "-"   << setw(COL_SPACE) << " ";
	cout << setw(TYPE_COL)  << "-"   << setw(COL_SPACE) << " ";
	cout << setw(NUM_COL)   << "-"      << setw(COL_SPACE) << "  ";
	cout << right 			<< fixed 		   << setprecision(2);
	cout << setw(SPENT_COL) << "-"
		 << setw(COL_SPACE) << " ";
	cout << left 			<< setprecision(6);
	cout.unsetf(ios::fixed);
	cout << setw(DATE_COL)  << "-"
		 << setw(COL_SPACE) << " "
		 << setw(REBATE_COL) << "-" << endl;
	cout << right;
}

/**************************************************************************
 * PrintMemberList
 * 		This method prints information about all the members in the list.
 * 		It will index through until all members have been printed.
 *
 * 		Returns - nothing (Prints list of members to console)
 *************************************************************************/
void MemberList::PrintMemberList() const
{
	// Variable List
	Member *currPtr; // CALC & OUT - Prints list of members

	PrintMemListHeader();

	currPtr = headMember;

	// PROCESSING - Loop until all members in list are printed
	while(currPtr != NULL)
	{
		currPtr->Print();
		cout << endl;
		currPtr = currPtr->GetNext();
	}

	cout << endl;
}

/**************************************************************************
 * PrintExpMembers
 * 		This method prints information about all the members that are
 * 		about to have their membership expired.
 *
 * 		Returns - nothing (Prints list of expiring members to console)
 *************************************************************************/
void MemberList::PrintExpMembers() const
{
	// Variable List
	Member *current; // CALC - Temp ptr for member

	current = headMember;

	// OUTPUT - Header for expired members
	cout << left << endl
		 << setw(NAME_COL) << "MEMBER NAME" << setw(NUM_COL)  << "MEMBER#"
		 << setw(TYPE_COL) << "MEMBER TYPE" << setw(DATE_COL) << "EXP DATE"
		 << setw(DUES_COL) << "DUES" << endl
		 << setw(NAME_COL) << "-------------------"
		 << setw(NUM_COL) << "---------"
		 << setw(TYPE_COL) << "--------------"
		 << setw(DATE_COL) << "-----------"
		 << setw(DUES_COL) << "------"
		 << endl;

	// PROCESSING - Keep looping through exp member list
	while(current != NULL)
	{

		cout << left << setw(NAME_COL) 	<< current->GetName()
			 << setw(NUM_COL) 		   	<< current->GetMemberNumber()
			 << setw(TYPE_COL) 			<< current->GetMemberType()
			 << setw(DATE_COL) 			<< current->GetExpDate().DisplayDate()
			 << "$" << fixed 			<< setprecision(2)
			 << setw(DUES_COL) 			<< current->GetAnnualDues() << endl;
		current = current->GetNext();
	}
	cout << right;
}

/**************************************************************************
 * PrintAllMemberPurchase
 * 		This method prints information about all the members and the
 * 		purchases he/she has or has not made
 *
 * 		Returns - nothing (Prints list of all members & purchases to console)
 *************************************************************************/
void MemberList::PrintAllMemberPurchase(Purchase &purList) const
												// IN & CALC - Purchase list
{
	// Variable List
	Member *temp;	// CALC - Temp ptr for member

	temp = headMember;

	// PROCESSING - Loop through all members in list until end
	while(temp != NULL)
	{
		purList.PrintPurchase();
		temp = temp->GetNext();
	}
}

void MemberList::InsertByMembTypeAndName(Member* node)
{
	//VARIABLE DECLARATION
	Member *tempPtr;	//CALC - Pointer to traverse the list

	//PROCESSING - IF-THEN - Used to add first node to head if list is empty
	if(headMember == NULL)
	{
		headMember = node;
		tailMember = node;
	}

	// PROCESSING - ELSE-IF - Checks if headMember's member type is = or >
	//				node's type and if the list has more than 1 member
	else if(headMember->GetMemberType() >= node->GetMemberType() &&
			tailMember->GetMemberType() != node->GetMemberType())
	{
		//PROCESSING - IF-THEN-ELSE - Checks if headMember's member type is
		//			   equal to node's member type
		if(headMember->GetMemberType() == node->GetMemberType())
		{
			//PROCESSING - IF-THEN-ELSE - Used to perform second sorting
			//			   criteria, check if head's name is > node's
			//			   name. If true node is added to front
			if(headMember->GetName() > node->GetName())
			{
				//Adds node to front
				node->SetNext(headMember);
				headMember->SetPrev(node);
				headMember = node;
			}
			else	//If head's name is <= node's name
			{
				tempPtr = headMember;

				//PROCESSING - WHILE - Traverses list checking for right
				//			   alphabetical place while member type does
				//			   not change.
				while(tempPtr->GetMemberType() <=
					  tempPtr->GetNext()->GetMemberType() &&
					  tempPtr->GetMemberType() <= node->GetMemberType() &&
					  tempPtr->GetName() <= node->GetName())
				{
					tempPtr = tempPtr->GetNext();
				}

				//Adds the node to the place found by the while loop
				node->SetPrev(tempPtr->GetPrev());
				node->SetNext(tempPtr);

				tempPtr->GetPrev()->SetNext(node);
				tempPtr->SetPrev(node);
			}
		}
		else  //adds to front of list
		{
			node->SetNext(headMember);
			headMember->SetPrev(node);
			headMember = node;
		}
	}

	// PROCESSING - ELSE-IF - Checks if headMember's member type is = or <
	//				node's type and if the list has more than 1 member
	else if(tailMember->GetMemberType() <= node->GetMemberType() &&
			headMember->GetMemberType() != node->GetMemberType())
	{
		//PROCESSING - IF-THEN-ELSE - Checks if tailMember member type is
		//			   equal to node's member type
		if(tailMember->GetMemberType() == node->GetMemberType())
		{
			//PROCESSING - IF-THEN-ELSE - Used to perform second sorting
			//			   criteria, check if tail's name is < node's
			//			   name. If true node is added to the end
			if(tailMember->GetName() < node->GetName())
			{
				tailMember->SetNext(node);
				node->SetPrev(tailMember);
				tailMember = node;
			}
			else	//If tail's name is >= node's name
			{
				tempPtr = tailMember;

				//PROCESSING - WHILE - Traverses list checking for right
				//			   alphabetical place while member type does
				//			   not change.
				while(tempPtr->GetMemberType() ==
					  tempPtr->GetPrev()->GetMemberType() &&
					  node->GetName() <= tempPtr->GetName() &&
					  node->GetName() <= tempPtr->GetPrev()->GetName())
				{
					tempPtr = tempPtr->GetPrev();
				}

				//Adds the node to the place found by the while loop
				node->SetPrev(tempPtr->GetPrev());
				node->SetNext(tempPtr);

				tempPtr->GetPrev()->SetNext(node);
				tempPtr->SetPrev(node);
			}
		}
		else	//adds to end of list
		{
			tailMember->SetNext(node);
			node->SetPrev(tailMember);
			tailMember = node;
		}
	}

	else	//If second node inserted is of the same member type as head
	{
		//PROCESSING - IF-THEN-ELSE - If head's name is > node's name
		if(headMember->GetName() > node->GetName())
		{
			//Adds to head
			node->SetNext(headMember);
			headMember->SetPrev(node);
			headMember = node;
		}
		else
		{
			//Adds to tail
			tailMember->SetNext(node);
			node->SetPrev(tailMember);
			tailMember = node;
		}
	}
}

void MemberList::PrintSortedMembersDue() const
{
	//VARIABLE DECLARATION
	Member *tempPtr;	//CALC - Pointer to traverse list

	//VARIABLE INITIALIZATION
	tempPtr = headMember; //Initializes tempPtr to head of list

	//PROCESSING - WHILE LOOP - Used to traverse the list. Exits upon
	//			   reaching end of list
	while(tempPtr != NULL)
	{
		//OUTPUT - Displays member's type, name, and dues
		cout << left << setw(12) << tempPtr->GetMemberType()
			 << setw(25) << tempPtr->GetName()
			 << "$" << right << fixed << setprecision(2)
			 << setw(6) << tempPtr->GetAnnualDues() << endl;

		tempPtr = tempPtr->GetNext();
	}
	cout << endl;
}
