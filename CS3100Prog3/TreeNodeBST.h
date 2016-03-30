#ifndef my_TREENODEBST_H
#define my_TREENODEBST_H

// *********************************************************
// Header file TreeNodeBST.h for the ADT binary search tree.
// This is the TreeNode class defined on page page 541
// of text.
// *********************************************************

#include "KeyedItem.h"

typedef KeyedItem TreeItemType;

class TreeNode // a node in the tree
{
private:
   TreeNode() { }
   TreeNode
    (const TreeItemType& nodeItem,  
            TreeNode *left = NULL, 
            TreeNode *right = NULL )
              : item(nodeItem.searchKey,
                     nodeItem.attributes,
                     nodeItem.isSuspect),
                leftChildPtr(left),
	        rightChildPtr(right)  { }

   TreeItemType item; // a data item in the tree
   // pointers to children
   TreeNode *leftChildPtr, *rightChildPtr;

   // friend class - can access private parts
   friend class BinarySearchTree;
}; // end class

#endif
