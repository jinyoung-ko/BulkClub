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
#include "MemberList.h"
#include "PurchasesList.h"
#include "BulkClub.h"
/**************************************************************************
 * BULK CLUB CLASS PROJECT
 * ------------------------------------------------------------------------
 * This program
 * ------------------------------------------------------------------------
 * INPUTS:
 *
 * OUTPUTS:
 *
 *************************************************************************/
int main()
{
	//VARIABLE DECLARATIONS
	MemberList 	  list;			// list of members
	PurchasesList purchases;	// list of purchases
	BulkClub	  theClub;		// BulkClub object for operations/reports
	int		 	  selection;	// user's selection for main menu
	bool		  run;			// T/F for program run

	// OUTPUT - Print header to console
	PrintHeader("Jinyoung Ko", "Augusto Cabrejos", 589855, 02,
				"Bulk Club", 'G', 1);

	//VARIABLE INITIALIZATIONS
	run = true;
	list.AddMemberFromFile("defaultMembers.txt");
	purchases.AddPurchaseFromFile("defaultPurchases.txt", list);

	//PROCESSING - DO-WHILE LOOP - Used to output the main menu, prompt for
	//			   user input, and go into the different operations.
	do
	{
		//DisplayMainMenu - this will display the main menu
		DisplayMainMenu();

		//GetAndCheckInt - this will prompt for user input and validate it
		selection = GetAndCheckInt(MAIN_MENU_MIN, MAIN_MENU_MAX);
		cout << endl;

		//PROCESSING - SWITCH - Used to route the program into different
		//	       operations based on user's selection from menu
		switch(selection)
		{
		case EXIT: 			//Program ends
							theClub.SaveMembers(list);
							theClub.SavePurchases(purchases);
							cout << "PROGRAM ENDED" << endl;
							run = false;
							break;

		case MEM_FILE: 		theClub.AddMemberFromFile(list);
							break;

		case ADD_MEMBER: 	//Adds member
							theClub.AddMember(list);
							break;

		case REMOVE_MEMBER: theClub.RemoveMember(list);
							break;

		case REMOVE_ALL_MEM:theClub.RemoveAllMember(list);
			break;

		case PURCHASE_FILE: theClub.AddPurchasesFromFile(purchases, list);
			break;

		case ADD_PURCHASE:	// Purchase from console
							theClub.AddPurchase(purchases, list);
							break;

		case MEMBERS: 		//Prints a list of members
							theClub.PrintMembersList(list);
							break;

		case PURCHASES: 	//Prints a list of purchases
							theClub.PrintPurchasesList(purchases);
							break;

		case EXPIRING:  	//Prints a report of memberships expiring on
							//a give date (prompts the user)
							theClub.CheckExpMembers(list);
							break;

		case SALES_BY_DATE:	// Prints a sales report of a particular day
							theClub.ReportAnyDay(purchases, list);
							break;
					
		case SALES_BY_MEMBER: // Prints a report showing purchases by member
							theClub.PurchasesbyMember(list, purchases);
							break;

		case SALES_ALL_MEM: theClub.TotalPurchasesByAllMembers(list, purchases);
							break;

		case ITEMS_SOLD: 	//Displays a list of products sold and their qty.
							theClub.ItemsSold(purchases);
							break;

		case SEARCH_ITEM:	//Searches for a specific product
							theClub.SearchItemsSold(purchases);
							break;

		case BASIC_CONVERT: theClub.CheckConvertToPreferred(list);
							break;

		case PREF_CONVERT: 	//Checks if preferred members need to convert to basic
							theClub.PreferredToBasicConversion(list);
							break;

		case REBATE: 		theClub.Rebate(list);
							break;

		case DUES: 			//Prints a list of membership dues sorted by
							// type and name
							theClub.MembershipsDues(list);
							break;
		default:			break;
		}
	}while(run);

	return 0;
}
