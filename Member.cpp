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
#include "Member.h"

/**************************************************************************
 * DEFAULT CONSTRUCTOR
 *************************************************************************/
Member::Member()
{
	nextMember   		= NULL;
	prevMember  		= NULL;
	name.clear();
	memberNumber 		= 0;
	annualDues   		= 55;
	totalSpentNoTax   	= 0;
	totalSpentPlusTax 	= 0;
}

/**************************************************************************
 * OVERLOADED CONSTRUCTOR
 *************************************************************************/
Member::Member(string setName,			// IN & CALC - Name
			   int	  setMemberNumber,	// IN & CALC - Member #
			   Date	  setDate)			// IN & CALC - Member Exp Date
{
	nextMember   	  = NULL;
	prevMember   	  = NULL;
	name 		 	  = setName;
	memberNumber 	  = setMemberNumber;
	expDate		 	  = setDate;
	annualDues   	  = 55;
	totalSpentNoTax   = 0;
	totalSpentPlusTax = 0;
}

/**************************************************************************
 * COPY CONSTRUCTOR
 *************************************************************************/
Member::Member(const Member& aMember)
{
	nextMember 		  = NULL;
	prevMember 		  = NULL;
	name 			  = aMember.GetName();
	memberNumber 	  = aMember.GetMemberNumber();
	expDate 		  = aMember.GetExpDate();
	annualDues 		  = aMember.GetAnnualDues();
	totalSpentNoTax   = aMember.GetTotalSpentNoTax();
	totalSpentPlusTax = aMember.GetTotalSpentPlusTax();

	cout << "CALLING COPY CONSTRUCTOR\n\n";
}

/**************************************************************************
 * DESTRUCTOR
 *************************************************************************/
Member::~Member() { }

/**************************************************************************
 * 								MUTATORS
 * ------------------------------------------------------------------------
 *							SetName
 *							SetMemberNumber
 *							SetNext
 *							SetPrev
 *							UpdateTotalSpentNoTax
 *							UpdateTotalSpentPlusTax
 *							ValidateMemberNumFromFile
 *							ValidateMemberTypeFromFile
 *							ValidateMemberNumFromConsole
 *							ValidateMemberTypeFromConsole
 *							ValidateTotalSpent
 *************************************************************************/

/**************************************************************************
 * SetName
 * 		This method sets the name of the member.
 *
 * 		Returns - nothing
 *************************************************************************/
void Member::SetName(string setName) // IN & CALC - Name of member
{
	name = setName;
}

/**************************************************************************
 * SetMemberNumber
 * 		This method sets the member number for a member.
 *
 * 		Returns - nothing
 *************************************************************************/
void Member::SetMemberNumber(int setMemberNum) // IN & CALC - Member number
{
	memberNumber = setMemberNum;
}

/**************************************************************************
 * SetNext
 * 		This method sets the next node in the members list.
 *
 * 		Returns - nothing
 *************************************************************************/
void Member::SetNext(Member *nextNode) // IN & CALC - Next member
{
	nextMember = nextNode;
}

/**************************************************************************
 * SetPrev
 * 		This method sets the previous node in the members list.
 *
 * 		Returns - nothing
 *************************************************************************/
void Member::SetPrev(Member *prevNode)	// IN & CALC - Previous member
{
	prevMember = prevNode;
}

/**************************************************************************
 * UpdateTotalSpentNoTax
 * 		This method updates the total amount spent for a user without
 * 		including tax.
 *
 * 		Returns - nothing (Updates total spent without tax)
 *************************************************************************/
void Member::UpdateTotalSpentNoTax(float addToTotal)
{
	totalSpentNoTax += addToTotal;
}

/**************************************************************************
 * UpdateTotalSpentPlusTax
 * 		This method updates the total amount spent for a member
 * 		including tax.
 *
 * 		Returns - nothing (Updates total spent with tax)
 *************************************************************************/
void Member::UpdateTotalSpentPlusTax(float addToTotal) // IN & CALC - Spent
{
	totalSpentPlusTax += addToTotal;
}

/**************************************************************************
 * ValidateMemberNumFromFile
 * 		This method receives a member number (5 digit - integer) to check.
 * 		The valid member numbers are from 00000-99999
 *
 * 		Returns - valid (bool)
 *************************************************************************/
bool Member::ValidateMemberNumFromFile(const int CHECK_INT) // IN & CALC -
														    // Mem num
{
	// Variable List
	bool valid;		// CALC & OUT - If valid member number

	valid = true;

	// PROCESSING - Check if input is a number or not
	if(!CHECK_INT)
	{
		valid = false;
	}
	// PROCESSING - Check if the number is between 00000 & 99999
	else if(CHECK_INT < MIN_MEM_NUM || CHECK_INT > MAX_MEM_NUM)
	{
		valid = false;
	}

	return valid;
}

/**************************************************************************
 * ValidateMemberTypeFromFile
 * 		This method receives a membership type from the input file to
 * 		validate. Choices are basic and preferred customers.
 *
 * 		Returns - valid (bool)
 *************************************************************************/
bool Member::ValidateMemberTypeFromFile(const char CHECK_CHAR) // IN & CALC
															   // - Type
{
	// Variable List
	bool 	 valid; // CALC & OUT - Check if membership type is valid

	valid = true;

	// PROCESSING - Membership type is not basic and not preferred
	if(CHECK_CHAR != TYPE_BASIC && CHECK_CHAR != TYPE_PREF)
	{
		valid = false;
	}

	return valid;
}

/**************************************************************************
 * ValidateMemberNumFromConsole
 * 		This method receives a member number from the console to check.
 * 		The membership number can range from 00000 - 99999. It will
 * 		also notify the user that this membership number is not valid.
 *
 * 		Returns - valid (bool)
 *************************************************************************/
bool Member::ValidateMemberNumFromConsole(const int CHECK_INT) // IN & CALC
															   // - Mem num
{
	// Variable List
	bool 		  valid;	// CALC & OUT - If member number is valid
	ostringstream oss;		// CALC		  - Formatting error column

	cout << left;
	valid = true;

	// PROCESSING - Check if input is an integer
	if(!CHECK_INT)
	{
		oss  << "***** Invalid Member Number ";
		cout << endl << setw(ERROR_COL) << oss.str() << " *****\n";
		oss.str("");

		oss  << "***** Member Number's are between " << MIN_MEM_NUM
			 << " and " << MAX_MEM_NUM;
		cout << setw(ERROR_COL) << oss.str() << " *****\n\n";
		oss.str("");
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		valid = false;
	}
	// PROCESSING - Check input is between membership range 00000 - 99999
	else if(CHECK_INT < MIN_MEM_NUM || CHECK_INT > MAX_MEM_NUM)
	{
		oss  << "***** The number " << CHECK_INT << " is not a valid entry";
		cout << endl << setw(ERROR_COL) << oss.str() << " *****\n";
		oss.str("");

		oss  << "***** Member Number's are between " << MIN_MEM_NUM
			 << " and " << MAX_MEM_NUM;
		cout << setw(ERROR_COL) << oss.str()   << " *****\n\n";
		oss.str("");
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		valid = false;
	}

	cout << right;

	return valid;
}

/**************************************************************************
 * ValidateMemberTypeFromConsole
 * 		This method receives a member type from the console to check.
 * 		The membership type can be either basic or preferred. It will
 * 		also notify the user that this membership type is not valid.
 *
 * 		Returns - valid (bool)
 *************************************************************************/
bool Member::ValidateMemberTypeFromConsole(const char CHECK_CHAR)
{
	// Variable List
	bool 		  valid; // CALC & OUT - Check if membership type is valid
	ostringstream oss;	 // CALC	   - Formatting column

	valid = true;
	cout << left;

	// PROCESSING - Check member type is neither basic nor preferred
	if(CHECK_CHAR != TYPE_BASIC && CHECK_CHAR != TYPE_PREF)
	{
		oss  << "***** The membership type " << CHECK_CHAR << " is invalid";
		cout << endl << setw(ERROR_COL) << oss.str() << " *****\n\n";
		oss.str("");
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		valid = false;
	}

	cout << right;

	return valid;
}

/**************************************************************************
 * 							ACCESSORS
 * ------------------------------------------------------------------------
 * 						GetName
 * 						GetMembershipNumber
 * 						GetTotalSpentNoTax
 * 						GetTotalSpentWithTax
 * 						GetExpDate
 * 						GetNext
 * 						GetPrev
 * 						GetAnnualDues
 * 						GetMemberType
 * 						Print
 *************************************************************************/

/**************************************************************************
 * GetName
 * 		This method gets the name of the member.
 *
 * 		Returns - name (string)
 *************************************************************************/
string Member::GetName() const
{
	return name;
}

/**************************************************************************
 * GetMemberNumber
 * 		This method gets the member number of a member.
 *
 * 		Returns - memberNumber (int)
 *************************************************************************/
int Member::GetMemberNumber() const
{
	return memberNumber;
}

/**************************************************************************
 * GetTotalSpentNoTax
 * 		This method returns the total amount spent by a member that
 * 		does not include any of the tax.
 *
 * 		Returns - totalSpentNoTax (float)
 *************************************************************************/
float Member::GetTotalSpentNoTax() const
{
	return totalSpentNoTax;
}

/**************************************************************************
 * GetTotalSpentPlusTax
 * 		This method returns the total amount spent by a member that
 * 		does include tax.
 *
 * 		Returns - totalSpentPlusTax (float)
 *************************************************************************/
float Member::GetTotalSpentPlusTax() const
{
	return totalSpentPlusTax;
}

/**************************************************************************
 * GetExpDate
 * 		This method returns the expiration date of the membership card.
 *
 * 		Returns - expDate (Date)
 *************************************************************************/
Date Member::GetExpDate() const
{
	return expDate;
}

/**************************************************************************
 * GetNext
 * 		This method gets the next node in the members list.
 *
 * 		Returns - nextMember (Member)
 *************************************************************************/
Member* Member::GetNext() const
{
	return nextMember;
}

/**************************************************************************
 * SetPrev
 * 		This method gets the previous node in the members list
 *
 * 		Returns - prevMember (Member)
 *************************************************************************/
Member* Member::GetPrev() const
{
	return prevMember;
}

/**************************************************************************
 * GetAnnualDues
 * 		This method returns the annual fee to be a basic member. ($55.00)
 *
 * 		Returns - annualDues (float)
 *************************************************************************/
float Member::GetAnnualDues() const
{
	return annualDues;
}

/**************************************************************************
 * GetMemberType
 * 		This method gets the member type.
 *
 * 		Returns - "Basic" (string)
 *************************************************************************/
string Member::GetMemberType() const
{
	return "Basic";
}

/**************************************************************************
 * Print
 * 		This method prints out information about a member which is
 * 		essentially a Basic member. The following information is printed
 * 		the full name of the member, the member type, the member number,
 * 		and total spent.
 *
 * 		Returns - nothing (Prints Basic member info to console)
 *************************************************************************/
void Member::Print() const
{
	// OUTPUT - Display Basic member info to console
	cout << left;
	cout << setfill(' ');
	cout << setw(NAME_COL)  << name 		   << setw(COL_SPACE) << " ";
	cout << setw(TYPE_COL)  << GetMemberType() << setw(COL_SPACE) << " ";
	cout << setw(NUM_COL-5) << " "
		 << setw(NUM_COL-5) << right << setfill('0')
		 << memberNumber    << left << setfill(' ')<< setw(COL_SPACE) << " ";
	cout << right 			<< fixed 		   << setprecision(2);
	cout << "$"  			<< setw(SPENT_COL) << totalSpentPlusTax
		 << setw(COL_SPACE) << " ";
	cout << left 			<< setprecision(6);
	cout.unsetf(ios::fixed);
	cout << setw(DATE_COL)  << expDate.DisplayDate()
		 << setw(COL_SPACE) << " ";
	cout << right;
}

