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
#ifndef MEMBERLIST_H_
#define MEMBERLIST_H_

#include "PreferredMember.h"
#include "Purchase.h"

class MemberList {
public:
	/*******************************
	 ***CONSTRUCTOR & DESTRUCTOR****
	 *******************************/
	MemberList();			// Default Constructor
	virtual ~MemberList();	// Destructor

	/**************
	 ***MUTATORS***
	 **************/
	void AddMemberFromFile(string fileName);	// Add members from file
	void AddMemberFromConsole();				// Add member from console
	void InsertInOrder(Member *addNode);		// Insert a member
	bool RemoveMember(string fullName);			// Remove a member
	bool RemoveMember(int removeSID);
	bool ClearList();							// Clear all members
	void InsertByMembTypeAndName(Member *node);	//Insers by type then by name


	/***************
	 ***ACCESSORS***
	 ***************/
	Member* GetHeadofList() const;					// Peek
	bool    IsEmpty() const;						// Check empty list
	int		MemberListSize() const;					// Size of list
	Member* SearchForMember(string keyName) const;	// Search by name
	Member* SearchForMember(int keyNum) const;		// Search by member #
	void	SearchByMonth(MemberList& expMembers, 	// Search month & year
						  int 		  monthKey,
						  int 		  yearKey) const;
	void	PrintMemListHeader() const;			// Print Header for table
	void    PrintMemberList() const;			// Print members in list
	void	PrintExpMembers() const;			// Prints Expired Members
	void	PrintAllMemberPurchase(Purchase &purList) const; // Print all
															 // mem. purchases

	void 	PrintSortedMembersDue() const;		//Prints memb dues

private:
	Member *headMember;	// Head of list
	Member *tailMember;	// Tail of list
	int		memberSize;	// Number of members in list
};

#endif /* MEMBERLIST_H_ */
