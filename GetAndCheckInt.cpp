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
 * FUNCTION GetAndCheckInt
 * ------------------------------------------------------------------------
 * This function receives values for minimum and maximum valid input
 * and error-checks it
 * -returns the error-checked user selection
 * ------------------------------------------------------------------------
 * PRE-CONDITIONS
 * 		min - minimum value must to be previously defined
 * 		max - maximum value must be previously defined
 * POST-CONDITIONS
 * 		This function will return error-checked user input
 *************************************************************************/
int GetAndCheckInt(int min, //IN -  minimum allowable parameter
				   int max) //IN -  maximum allowable parameter
{
	//VARIABLE DECLARATIONS
	ostringstream buffer; 	//CALC - used for spacing purposes
	bool 		  inputOk;	//CALC - holds T/F value for valid input
	int			  pick;		//IN   - user's input to error check

	//VARIABLE INITIALIZATION
	//pick    = 0;		//initializes pick to 0
	inputOk = false;	//initializes inputOk to false

	//PROCESSING - IF-THEN-ELSE STATEMENT - Used to error check input for
	//			   characters and if check if it is within allowed bounds
	if (!(cin >> pick))
	{
		cout << endl << "**** Please input a NUMBER between " << min
			 << " and " << max << "       ****" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		pick = -1;				// wrong input will return an -1
	}
	else
	{
		inputOk = (pick >= min && pick < max + 1);	//sets bool to true

		//PROCESSING - IF-THEN STATEMENT - Used to check if the input is
		//			   within bounds
		if (!inputOk)
		{
			cout   << left << endl;
			buffer << "**** The number " << pick;
			cout   << buffer.str() << setw(49 - buffer.str().length())
				   << left << " is not a valid entry" << "****" << endl;
			cout   << "**** Please input a NUMBER between " << min
				   << " and " << setw(6) << left << max << "  ****" << endl;
			buffer.str("");
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			pick = -1;			// wrong input will return an -1
		}
	}
	return pick;
}
