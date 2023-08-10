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
#ifndef MYHEADER_H_
#define MYHEADER_H_

#include <iostream>
#include <iomanip>
#include "Member.h"
using namespace std;

enum Menu
{
	EXIT,
	MEM_FILE,
	ADD_MEMBER,
	REMOVE_MEMBER,
	REMOVE_ALL_MEM,
	PURCHASE_FILE,
	ADD_PURCHASE,
	MEMBERS,
	PURCHASES,
	EXPIRING,
	SALES_BY_DATE,
	SALES_BY_MEMBER,
	SALES_ALL_MEM,
	ITEMS_SOLD,
	SEARCH_ITEM,
	BASIC_CONVERT,
	PREF_CONVERT,
	REBATE,
	DUES
};

/**************************************************************************
* CONSTANT DECLARATION
* -------------------------------------------------------------------------
* MAIN_MENU_MIN	: The minimum allowable value for menu selection
* MAIN_MENU_MAX : The maximum allowable value for menu selection
* EXP_MONTH_MIN	: The minimum allowable value for month
* EXP_MONTH_MAX	: The maximum allowable value for month
* EXP_YEAR_MIN  : The minimum allowable value for year
* EXP_YEAR_MAX  : The maximum allowable value for year
**************************************************************************/
const int MAIN_MENU_MIN = 0;
const int MAIN_MENU_MAX = 18;
const int EXP_MONTH_MIN = 1;
const int EXP_MONTH_MAX = 12;
const int EXP_YEAR_MIN = 2000;
const int EXP_YEAR_MAX = 3000;

/**************************************************************************
 * PrintHeader
 * 		This function receives four programmers name and student id number.
 * 		It also receives the programmers' assignment, lab, or group project
 * 		name, type (assignment, lab, or group), and assignment/lab/group
 * 		number. This prints the heading output for Team Apple.
 *
 * 	Returns : nothing (Displays header to console)
 *************************************************************************/
void PrintHeader(const string programmer1, // IN & OUT 		 - Programmer 1
				 const string programmer2, // IN & OUT 		 - Programmer 2
				 const int    sidNum1,	   // IN & OUT 		 - SID # 1
				 const int    sidNum2,	   // IN & OUT 		 - SID # 2
				 const string assgName,	   // IN & OUT       - Assg Name
				 const char   assgType,    // IN, CALC & OUT - Assg Type
				 const int    assgNum);	   // IN & OUT		 - Assg #

/**************************************************************************
 * DisplayMainMenu
 * ------------------------------------------------------------------------
 * This function outputs the main menu to the screen.
 * -returns nothing
 *************************************************************************/
void DisplayMainMenu();

/**************************************************************************
 * GetAndCheckInt
 * ------------------------------------------------------------------------
 * This function receives values for minimum and maximum valid input
 * and error-checks it
 * -returns the error-checked user selection
 *************************************************************************/
int GetAndCheckInt(int min,  //IN -  minimum allowable parameter
				   int max); //IN -  maximum allowable parameter


#endif /* MYHEADER_H_ */
