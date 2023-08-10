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
#ifndef DATE_H_
#define DATE_H_

#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>
#include <ios>
using namespace std;

class Date
{
public:

	/******************************
	 ***CONSTRUCTOR & DESTRUCTOR***
	 ******************************/
	Date();					// Default constructor
	Date(int updateMonth,	// Overloaded constructor
		 int updateDay,
		 int updateyear);
	virtual ~Date();		// Destructor

	/**************
	 ***MUTATORS***
	 **************/
	bool CheckDate(int updateMonth,		// Checks the month, day, year
			       int updateDay,
				   int updateYear);
	void SetDate(int updateMonth,		// Sets the month, day, year
				 int updateDay,
				 int updateYear);
	void SetDay(int updateDay);			// Sets the day
	void SetMonth(int updateMonth);		// Sets the month
	void SetYear(int updateYear);		// Sets the year

	/***************
	 ***ACCESSORS***
	 ***************/
	void GetDate(int &updateMonth,		// Gets month, day, year
				 int &updateDay,
				 int &updateYear) const;
	int    GetYear()     const; 		// Gets the year
	int    GetMonth()    const; 		// Gets the month
	int    GetDay()      const; 		// Gets the day
	string DisplayDate() const; 		// Displays in MM/DD/YYYY format

private:
	int month;	// Month of a Date
	int day;	// Day of a Date
	int year;	// Year of a Date
};

#endif /* DATE_H_ */
