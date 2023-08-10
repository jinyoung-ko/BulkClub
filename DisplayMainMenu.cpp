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
#include "MyHeader.h"

/**************************************************************************
 * FUNCTION DisplayMainMenu
 * ------------------------------------------------------------------------
 * This function outputs the main menu to the screen.
 * -returns nothing
 * ------------------------------------------------------------------------
 * PRE-CONDITIONS
 * 		none
 * POST-CONDITIONS
 * 		This function prints the main menu
 *************************************************************************/
void DisplayMainMenu()
{
	//OUTPUT - Displays the main menu
	cout << "WELCOME TO BULK CLUB\n"
			"MAIN MENU\n"
			"1  - Add Members from file\n"
			"2  - Add Member\n"
			"3  - Remove Member\n"
			"4  - Remove All Members\n"
			"5  - Add Purchases from file\n"
			"6  - Add Purchase\n"
			"7  - Display List of Members\n"
			"8  - Display List of Purchases\n"
			"9  - Check for expiring members\n"
			"10 - Sales Report: of a specific day\n"
			"11 - Sales Report: of a specific member\n"
			"12 - Sales Report: of all members\n"
			"13 - Sales Report: quantities of all products sold\n"
			"14 - Sales Report: of a specific product\n"
			"15 - Check if a Basic member should convert to Preferred\n"
			"16 - Check if a Preferred member should convert to Basic\n"
			"17 - Get Rebate of All Preferred Members\n"
			"18 - Report: Amount paid per year for the membership dues\n"
			"0  - EXIT\n"
			"Please enter a command: ";
}
