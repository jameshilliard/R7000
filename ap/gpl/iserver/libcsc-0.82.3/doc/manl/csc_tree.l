csc_tree(l)

NAME
	csc_tree

DESCRIPTION
	Balanced Binary Tree Subsystem

	The CSCbinTree functions provide an interface to a balanced binary tree
	subsystem.  The tree is an opaque data type, and client code never has
	direct access to the nodes.  Note that you can't remove nodes, but the
	tree can be deleted.

	The CSCbinTreeNode functions provide individual node manipulation
	capability.  Trees can be built with the CSCbinTreeNodeJoin function,
	which returns a pointer to the upper node.  These trees are not likely
	to be balanced.

	Don't try mixing the CSCbinTree and CSCbinTreeNode functions on the
	same tree.

FUNCTIONS
		tree
		----
	CSCbinTreeNew - create an empty libcsc balanced binary tree
	CSCbinTreeDel - delete a libcsc balanced binary tree
	CSCbinTreeInsert - insert a node into a libcsc balanced binary tree
	CSCbinTreeTagOrderedInsert - put node into libcsc balanced binary tree
	CSCbinTreeTraverse - traverse a libcsc balanced binary tree
	CSCbinTreeUserSearch - arbitrary search of libcsc balanced binary tree
	CSCbinTreeTagSearch - search a balanced binary tree for node with tag
	CSCbinTreeStat - retrieve libcsc balanced binary tree statistics
	CSCbinTreePrint - print a libcsc balanced binary tree

		node
		----
	CSCbinTreeNodeNew - create a new empty libcsc binary tree node
	CSCbinTreeNodeDel - deallocate a libcsc binary tree node
	CSCbinTreeNodeJoin - join libcsc binary tree nodes
	CSCbinTreeNodeBreak - break libcsc binary tree at a node
	CSCbinTreeNodeTraverse - traverse a libcsc binary tree
	CSCbinTreeNodeUserSearch - arbitrary libcsc binary tree traversal
	CSCbinTreeNodeTagSearch - search a libcsc binary tree for a given tag
	CSCbinTreeNodeStat - retrieve fields from a libcsc binary tree node
	CSCbinTreeNodePrint - print the values of a libcsc binary tree node
