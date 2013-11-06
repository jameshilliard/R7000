csc_file(l)

NAME
	csc_file

DESCRIPTION
	File Subsystem

FUNCTIONS
	CSCfileReadLock       - read-lock a region in a file
	CSCfileWriteLock      - write-lock a region in a file
	CSCfileUnlock         - unlock a region in a file
	CSCfileGetHomeDir     - find home directory pathname
	CSCfileGetUserHomeDir - find home directory pathname of specific user
	CSCfileBaseName       - strip directory from pathname
	CSCfilePathName       - strip last component (file) from pathname
	CSCfileExpandPath     - expand ~ and environment variables in pathname
	CSCfileOpen           - create a file in a path that doesn't (yet) exist
