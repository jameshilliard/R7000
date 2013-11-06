csc_list(l)

NAME
	csc_list

DESCRIPTION
	List Subsystem

	The csc library's list subsystem; there are functions for managing
	arbitrary data in lists.  These lists can act like queues, stacks, or
	just linked lists.

FUNCTIONS
	CSClistNew - create a new libcsc list
	CSClistDel - remove a libcsc list
	CSClistRead - read an ASCII format libcsc list
	CSClistWrite - write a libcsc list in an ASCII format
	CSClistSetCFunc - set a libcsc list entry data compare function
	CSClistStat - retrieve libcsc list statistics
	CSClistPush - create a new entry and push it onto a libcsc list
	CSClistPop - pop an entry from a libcsc list and retrieve its data
	CSClistPeek - retrieve data from entry at libcsc list head or tail
	CSClistNodeNext - find next entry (node) in a libcsc list
	CSClistNodeFindByValue - find libcsc list entry by data value
	CSClistNodeFindByReference - find libcsc list entry (node) by reference
	CSClistNodeStat - retrieve data fields from a libcsc list entry (node)
	CSClistNodeValidate - verify an entry (node) is really in a libcsc list
	CSClistNodeDel - remove an entry (node) from a libcsc list
