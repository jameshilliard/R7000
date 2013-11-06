csc_mem(l)

NAME
	csc_mem

DESCRIPTION
	Memory (Dynamic Allocation) Subsystem

FUNCTIONS
	CSCmemInit - initialize a csc memlist for subsequent memory allocations
	CSCmemDone - cleanup and remove a memList (free all its memory)
	CSCmemAlloc - allocate memory (and keep thrack of it in memList)
	CSCmemDup - duplicate (dynamically allocate and copy) memory
	CSCmemFree - free dynamically allocated memory
	CSCmemLookup - lookup a memory pointer in memList
	CSCmemValidate - validate that a memory pointer is in memList
	CSCmemListFree - free all memory allocated in a memList
	CSCmemListStat - get information about a memList
	CSCmemListPrintProfile - write a memlist profile to standard output
	CSCmemListWriteProfile - write a memlist profile to a file descriptor
