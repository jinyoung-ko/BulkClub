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
#ifndef PREFERREDMEMBER_H_
#define PREFERREDMEMBER_H_

#include "Member.h"

/**************************************************************************
 * GLOBAL CONSTANTS
 * ------------------------------------------------------------------------
 * REBATE_COL : Formatting column for printing rebate
 *************************************************************************/
const int REBATE_COL = 5;

class PreferredMember: public Member {
public:
	/******************************
	 ***CONSTRUCTOR & DESTRUCTOR***
	 ******************************/
	PreferredMember();						// Default Constructor
	PreferredMember(string setName,			// Overloaded Constructor
					int    setMemberNum,
					Date   setDate);
	virtual ~PreferredMember();				// Destructor

	/**************
	 ***MUTATORS***
	 **************/
	void SetRebate(float setRebate); // Set rebate

	/***************
	 ***ACCESSORS***
	 ***************/
	float GetRebate() const;				// Get rebate
	virtual float GetAnnualDues() const;	// Get annual dues
	virtual string GetMemberType() const;	// Get membership type
	virtual void Print() const;				// Print preferred member info

private:
	float rebate;	// Rebate
	float annualDues; //Annual dues
};

#endif /* PREFERREDMEMBER_H_ */
