csc_notify(l)

NAME
	csc_notify

DESCRIPTION
	Notification System (callback) Subsystem

	Create a notification board, add some notifications to it, then
	regisiter some functions, each with some private data (pointer is
	useful) on some the the notifications.  When a notification is posted,
	the registered functions will be called, each with their corresponding
	private data.

FUNCTIONS
	CSCnotificationBoardNew   - create a new notification board
	CSCnotificationBoardDel   - completely remove a notification board
	CSCnotificationBoardPrint - print a notification board in ASCII format
	CSCnotificationNew        - create a new notification in a board
	CSCnotificationDel        - delete a notification from a board
	CSCnotificationPost       - post to a notification in a board
	CSCnotificationRegister   - register client function to a notification
