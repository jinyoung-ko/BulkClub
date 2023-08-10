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
#include "MyHeader.h"
/**************************************************************************
 *  FUNCTION: PrintHeader
 *------------------------------------------------------------------------
 *  This function receives an assignment name, type, and number then outputs
 * 		the appropriate header - returns nothing.
 *------------------------------------------------------------------------
 *  PRE-CONDITIONS
 *  	outFile		: To output file.
 *  	assgName	: Assignment Name has to be previously defined.
 *  	assgType	: Type has to be previously defined.
 *  	assgNum		: Assignment Number has to be previously defined.
 *
 *  POST-CONDITIONS
 *  	This function will output the class heading.
 *************************************************************************/

void PrintHeader(const string programmer1, // IN & OUT 		 - Programmer 1
				 const string programmer2, // IN & OUT 		 - Programmer 4
				 const int    sidNum1,	   // IN & OUT 		 - SID # 1
				 const int    sidNum2,	   // IN & OUT 		 - SID # 4
				 const string assgName,	   // IN & OUT       - Assg Name
				 const char   assgType,    // IN, CALC & OUT - Assg Type
				 const int    assgNum)	   // IN & OUT		 - Assg #

{
	/**********************************************************************
	 * 	CONSTANTS
	 * 	__________________________________________________________________
	 * 	USED FOR CLASS HEADING - ALL WILL BE OUTPUT
	 *  -------------------------------------------------------------------
	 *  PROGRAMMER	: Name of Programmer
	 *  SID_NUM		: SID #
	 *  CLASS		: Student's Course
	 *  SECTION		: Student's Time of course
	 *  -------------------------------------------------------------------
	 *  USED FOR FORMATTING
	 * 	-------------------------------------------------------------------
	 *  COL_WIDTH	: Column width for user input info.
	 *  LAB_WIDTH	: The column width for lab info.
	 *  ASSG_WIDTH	: The column with for assg info.
	 *********************************************************************/
	const string CLASS		= "CS1C";
	const string SECTION    = "TTH 12:30-4:20PM";

	const int COL_WIDTH  	   = 20;
	const int LAB_WIDTH  	   = 15;
	const int ASSG_WIDTH 	   = 8;
	const int GROUP_PROJ_WIDTH = 5;

	// OUTPUT - Class Heading
	cout << left;
//	cout << "**********************************************************\n";
//	cout <<	   "      __                    \n"
//			   "      \\_}                  \n"
//			   "     .-./--.                \n"
//			   "   /# ^^     \\  TEAM       \n"
//			   "  |           | APPLE       \n"
//			   "   \\         /             \n"
//			   "    \\       /              \n"
//			   "     `\"`\"`\"`             \n";
	cout << "*************************************************************"
			"**************";
	cout << "\n*        __          " << setw(COL_WIDTH) << "PROGRAMMED BY"
		 << ": "   					  << programmer1;
	cout << "\n*        \\_}        " << setw(COL_WIDTH) << " "  << " : "
		 << programmer2;
	cout << "\n*       .-./--.      " << setw(COL_WIDTH) << "STUDENT ID"
		 << ": " 					  << sidNum1;
	cout << "\n*     /# ^^     \\   " << setw(COL_WIDTH) << " "  << " : "
		 << sidNum2;
	cout << "\n*    |           |   " << setw(COL_WIDTH) << "CLASS"  << ": "
		 << CLASS;
	cout << "\n*     \\         /    "<< setw(COL_WIDTH) << "SECTION" << ": "
		 << SECTION;
	cout << "\n*      \\       /     ";

	// PROCESSING - Checks if lab or assignment.
	if (toupper(assgType) == 'L')
	{
		cout << "LAB #" << setw(LAB_WIDTH);
	}
	else if(toupper(assgType) == 'A')
	{
		cout << "ASSIGNMENT #" << setw(ASSG_WIDTH);
	}
	else
	{
		cout << "CLASS PROJECT #" << setw(GROUP_PROJ_WIDTH);
	}

	cout << assgNum << ": " << assgName << endl;
	cout << "*       `\"`\"`\"`    \n";
	cout << "*     TEAM APPLE\n";
	cout << "*************************************************************"
			"**************\n\n";
	cout << right;
}
