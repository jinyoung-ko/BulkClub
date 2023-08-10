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
#include "PreferredMember.h"

/**************************************************************************
 * DEFAULT CONSTRUCTOR
 *************************************************************************/
PreferredMember::PreferredMember() {
	rebate 	   = 0.06;
	annualDues = 95;
}

/**************************************************************************
 * OVERLOADED CONSTRUCTOR
 *************************************************************************/
PreferredMember::PreferredMember(string setName,	  // IN & CALC - Name
								 int    setMemberNum, // IN & CALC - Mem#
								 Date	setDate)	  // IN & CALC - Exp Date
			: Member(setName, setMemberNum, setDate)
{
	rebate 	   = 0.06;
	annualDues = 95;
}

/**************************************************************************
 * DESTRUCTOR
 *************************************************************************/
PreferredMember::~PreferredMember() {
}

/**************************************************************************
 * 								MUTATORS
 * ------------------------------------------------------------------------
 * 							SetRebate
 *************************************************************************/

/**************************************************************************
 * SetRebate
 * 		This method sets the rebate amount.
 *
 * 		Returns - nothing
 *************************************************************************/
void PreferredMember::SetRebate(float setRebate) // IN & CALC - Rebate amt
{
	rebate = setRebate;
}

/**************************************************************************
 * 								ACCESSORS
 * ------------------------------------------------------------------------
 * 							GetRebate
 *************************************************************************/

/**************************************************************************
 * GetRebate
 * 		This method gets the rebate amount.
 *
 * 		Returns - rebate (float)
 *************************************************************************/
float PreferredMember::GetRebate() const
{
	return rebate;
}

/**************************************************************************
 * GetAnnualDues
 * 		This method gets the annual dues.
 *
 * 		Returns - annualDues (float)
 *************************************************************************/
float PreferredMember::GetAnnualDues() const
{
	return annualDues;
}

/**************************************************************************
 * GetMemberType
 * 		This method gets the member type.
 *
 * 		Returns - "Preferred" (string)
 *************************************************************************/
string PreferredMember::GetMemberType() const
{
	return "Preferred";
}

/**************************************************************************
 * Print
 * 		This method prints all the information about a Preferred member.
 * 		This includes the full name of the member, the member number,
 * 		the member type, the total spent, and the rebate amount.
 *
 * 		Returns - nothing (Prints Preferred member info to console)
 *************************************************************************/
void PreferredMember::Print() const
{
	// OUTPUT - Display Preferred member info to console
	cout << left;
	cout << setfill(' ');
	Member::Print();
	cout << setw(REBATE_COL) << rebate;
	cout << right;
}
