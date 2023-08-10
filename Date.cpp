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
#include "Date.h"
/**************************************************************************
 * 					CONSTRUCTORS & DESTRUCTOR
 *************************************************************************/

/**************************************************************************
 * DEFAULT CONSTRUCTOR
 *************************************************************************/
Date::Date()
{
	month = 0;
	day   = 0;
	year  = 0;

}

/**************************************************************************
 * OVERLOADED CONSTRUCTOR
 *************************************************************************/
Date::Date(int updateMonth,	// IN & CALC - Set month
		   int updateDay,	// IN & CALC - Set day
		   int updateYear)	// IN & CALC - Set year
{
	// Variable List
	bool valid;	// CALC - Check if inputs for Date are valid

	valid = CheckDate(updateMonth, updateDay, updateYear);

	if(valid)
	{
		SetDate(updateMonth, updateDay, updateYear);
	}
	else
	{
		cout << "error\n";
	}
}

/**************************************************************************
 * DESTRUCTOR
 *************************************************************************/
Date::~Date() { }

/**************************************************************************
 * 							MUTATORS
 * ------------------------------------------------------------------------
 * 						CheckDate
 * 						SetDate
 * 						SetDay
 * 						SetMonth
 * 						SetYear
 *************************************************************************/

/**************************************************************************
 * CheckDate
 * 		This method receives an updated day, month, and year (integer) and
 * 		checks if the month, day, and year make a valid date. This method
 * 		also takes into consideration leap year. Also checks to see if the
 * 		date is valid prior to setting the actual date.
 *
 * 		Returns - nothing (Updates the Date (month, day, year)
 *************************************************************************/
bool Date::CheckDate(int updateMonth, 	// IN & CALC - Update month
				   	 int updateDay,		// IN & CALC - Update day
					 int updateYear)	// IN & CALC - Update year
{
	// Variable List
	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
						// CALC 	  - Number of days in each month
	int currentYear;	// CALC 	  - Current year
	int currentMonth;	// CALC 	  - Current month
	int currentDay;		// CALC 	  - Current day
	int lastDayInMonth;	// CALC 	  - Last day in month
	tm *currentTime;    // CALC 	  - Used to find the current time
	bool validDate;		// CALC & OUT - If Date is valid or not

	// PROCESSING - Find the current year based on the currentTime
	time_t now   = time(0);
	currentTime  = localtime(&now);
	currentYear  = 1900 + currentTime->tm_year + 1;
	currentMonth = 1 + currentTime->tm_mon;
	currentDay   = currentTime->tm_mday;

	// PROCESSING - Check to make sure inputs are integers
	if(!updateMonth || !updateYear || !updateDay)
	{
		validDate = false;
	}
	else
	{
		// PROCESSING - Error checks: The year, month & day
		//				Note: The year must be between 1900 and the currentYear
		if(updateYear > currentYear || updateYear < 1900)
		{
			validDate = false;
		}
		//    MONTH: The month must be between 0 and 12 or
		//           <=  currentMonth for the currentYear
		else if ((updateYear != currentYear &&
				 (updateMonth > 12 || updateMonth < 0)) ||
				 (updateYear == currentYear && updateMonth > currentMonth))
		{
			validDate = false;
		}
		// PROCESSING - Note: The day must be <= the # of days in the month
		//            - This also account for Leap Year
		else
		{
			lastDayInMonth = daysInMonth[updateMonth - 1];

			// PROCESSING - LEAP YEAR Adjustment to lastDayInMonth
			if(updateMonth == 2 &&
			  ((updateYear % 4 == 0 || updateYear % 400 == 0) &&
				updateYear % 100 != 0))
			{
				lastDayInMonth++;
			}

			// PROCESSING - Check if Day is valid
			if ((updateDay > lastDayInMonth || updateDay < 0) ||
				(updateYear == currentYear && updateMonth == currentMonth &&
				 updateDay > currentDay))
			{
				validDate = false;
			}
			else
			{
				validDate = true;

			} // END - DAY CHECK
		} // END - YEAR - MONTH If-else-if
	} // END IF ELSE

	return validDate;
}

/**************************************************************************
 * SetDate
 * 		This method receives an updated day, month, and year (integer)
 * 		that is to be set as the new date in a Date.
 *
 * 		Returns - nothing (Updates the Date (month, day, year)
 *************************************************************************/
void Date::SetDate(int updateMonth,	// IN & CALC - Update month
				   int updateDay,	// IN & CALC - Update day
				   int updateYear)	// IN & CALC - Update Year
{
	month = updateMonth;
	day   = updateDay;
	year  = updateYear;
}

/**************************************************************************
 * SetDay
 * 		This method receives an updated day (integer) that is to be
 * 		set as the new day in a Date.
 *
 * 		Returns - nothing (Updates day)
 *************************************************************************/
void Date::SetDay(int updateDay)	// IN & CALC - Updated day
{
	day = updateDay;
}

/**************************************************************************
 * SetMonth
 * 		This method receives an updated month (integer) that is to be
 * 		set as the new month in a Date.
 *
 * 		Returns - nothing (Updates month)
 *************************************************************************/
void Date::SetMonth(int updateMonth)	// IN & CALC - Updated month
{
	month = updateMonth;
}

/**************************************************************************
 * SetYear
 * 		This method receives an updated year (integer) that is to be
 * 		set as the new year in a Date.
 *
 * 		Returns - nothing (Updates year)
 *************************************************************************/
void Date::SetYear(int updateYear)	// IN & CALC - Updated year
{
	year = updateYear;
}

/**************************************************************************
 * 							ACCESSORS
 * ------------------------------------------------------------------------
 * 							GetDate
 * 							GetYear
 * 							GetMonth
 * 							GetDay
 * 							DisplayDate
 *************************************************************************/

/**************************************************************************
 * GetDate
 * 		This method gets the full Date (month, day, year) and passes
 * 		it back by reference. Just gives the month, day, year - not
 * 		formatted.
 *
 * 		Returns - updateMonth, updateDay, updateYear (int - by ref)
 *************************************************************************/
void Date::GetDate(int &updateMonth,		// IN, CALC & OUT - Update Month
				   int &updateDay,			// IN, CALC & OUT - Update Day
				   int &updateYear) const	// IN, CALC & OUT - Update Year
{
	  updateMonth = month;
	  updateDay   = day;
	  updateYear  = year;
}

/**************************************************************************
 * GetYear
 * 		This method gets the year.
 *
 * 		Returns - year (int)
 *************************************************************************/
int  Date::GetYear() const
{
	return year;
}

/**************************************************************************
 * GetMonth
 * 		This method gets the month.
 *
 * 		Returns - month (int)
 *************************************************************************/
int  Date::GetMonth() const
{
	return month;
}

/**************************************************************************
 * GetDay
 * 		This method gets the day.
 *
 * 		Returns - day (int)
 *************************************************************************/
int  Date::GetDay() const
{
	return day;
}

/**************************************************************************
 * DisplayDate
 * 		This method formats the Date into MM/DD/YYYY.
 *
 * 		Returns - formatDate (string)
 *************************************************************************/
string Date::DisplayDate() const
{
	// Variable List
	ostringstream oss;				// CALC 	  - Formatting Date
	string 		  formatDate;		// CALC & OUT - Fully format Date
	string 		  strUpdateDay;		// CALC		  - Formatted day
	string 		  strUpdateMonth;	// CALC		  - Formatted month

	// PROCESSING - Check if month needs to be formatted with leading 0
	if(month < 10)
	{
		oss << 0 << month;
		strUpdateMonth = oss.str();
		oss.str("");
	}
	// PROCESSING - Month is >= 10 (i.e. October - December)
	else
	{
		oss << month;
		strUpdateMonth = oss.str();
		oss.str("");
	}

	// PROCESSING - Check if day needs to be formatted with leading 0
	if(day < 10)
	{
		oss << 0 << day;
		strUpdateDay = oss.str();
		oss.str("");
	}
	// PROCESSING - Day is >= 10 (i.e. 10-31)
	else
	{
		oss << day;
		strUpdateDay   = oss.str();
		oss.str("");
	}

	// PROCESSING - Formats full Date to MM/DD/YYYY
	oss  << strUpdateMonth << '/' << strUpdateDay << '/' << year;
	formatDate = oss.str();
	oss.str("");

	return formatDate;
}
