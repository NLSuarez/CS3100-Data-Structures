#ifndef my_BST_H 
#define my_BST_H 

// *********************************************************
// Header file BST.h for the ADT binary search tree.
// Assumption: A tree contains at most one item with a given
// search key at any time.
// *********************************************************

#include <iostream>
#include <fstream>
#include "TreeException.h"
#include "TreeNodeBST.h"  // Note use of file TreeNodeBST.h
                          // Defines TreeNode with KeyedItem

typedef void (*FunctionType)(TreeItemType& anItem);
//Functions for saving nodes via a specialized visit
typedef void (*FunctionTypeSave)(TreeItemType& anItem, ofstream& stream);
//Functions for counting number of suspects still available
typedef void (*FunctionTypeSCount)(TreeItemType& anItem, int& sCount);
//Functions for passing a tip through the tree
typedef void (*FunctionTypeTip)(TreeItemType& anItem, string tip);

class BinarySearchTree
{
   public:
   // constructors and destructor:
      BinarySearchTree();
      BinarySearchTree(const BinarySearchTree& tree);
      virtual ~BinarySearchTree();
   
   // binary search tree operations:
   // Precondition for all methods: No two items in a binary
   // search tree have the same search key.
   
      virtual bool isEmpty() const;
      // Determines whether a binary search tree is empty.
      // Postcondition: Returns true if the tree is empty;
      // otherwise returns false.
   
      virtual void searchTreeInsert(const TreeItemType& newItem);
      // Inserts an item into a binary search tree.
      // Precondition: The item to be inserted into the tree
      // is newItem.
      // Postcondition: newItem is in its proper order in the
      // tree.
   
      virtual void searchTreeDelete(KeyType searchKey)
            throw (TreeException);
      // Deletes an item with a given search key from a binary
      // search tree.
      // Precondition: searchKey is the search key of the item
      // to be deleted.
      // Postcondition: If the item whose search key equals
      // searchKey existed in the tree, the item is deleted.
      // Otherwise, the tree is unchanged and TreeException
      // is thrown.
   
      virtual void searchTreeRetrieve(KeyType searchKey,
                                      TreeItemType& treeItem) const
            throw (TreeException);
      // Retrieves an item with a given search key from a
      // binary search tree.
      // Precondition: searchKey is the search key of the item
      // to be retrieved.
      // Postcondition: If the retrieval was successful,
      // treeItem contains the retrieved item.
      // If no such item exists, throws TreeException.
   
	 virtual void countSuspects(FunctionTypeSCount visit, int& sCount);
      // Special version of in-order traverse used to count
	 // all instances of isSuspect encountered in a tree.
	 // Can also be used to count all nodes in an original
	 // tree because the base value of the suspect field
	 // on each node should be true.

	 virtual void tipTraverse(FunctionTypeTip visit, string tip);
      // Special version of post-order traverse used to
	 // evaluate all remaining nodes with isSuspect set
	 // to true, compare their attributes to a given tip
	 // , and mark their isSuspect status as false if
	 // no attributes matched the tip.

	 virtual void saveTree(FunctionTypeSave visit, ofstream& stream);
      // Traverses a binary search tree in preorder,
      // calling function visit() once for each item
	 // to save it to a specified file.
      // Precondition: The function represented by visit()
      // exists outside of the class implementation.
      // Postcondition: visit's action occurred once for each
      // item in the tree.
      // Note: visit() can alter the tree.

	 virtual void preorderTraverse(FunctionType visit);
      // Traverses a binary search tree in preorder,
      // calling function visit() once for each item.
      // Precondition: The function represented by visit()
      // exists outside of the class implementation.
      // Postcondition: visit's action occurred once for each
      // item in the tree.
      // Note: visit() can alter the tree.
   
      virtual void inorderTraverse(FunctionType visit);
      // Traverses a binary search tree in sorted order,
      // calling function visit() once for each item.
   
      virtual void postorderTraverse(FunctionType visit);
      // Traverses a binary search tree in postorder,
      // calling function visit() once for each item.    
    
      // overloaded operator:
      virtual BinarySearchTree& operator=(
                                const BinarySearchTree& rhs);
   protected:
      void insertItem(TreeNode * &treePtr,
                      const TreeItemType& newItem);
      // Recursively inserts an item into a binary search tree.
      // Precondition: treePtr points to a binary search tree,
      // newItem is the item to be inserted.
      // Postcondition: Same as searchTreeInsert.
   
      void deleteItem(TreeNode * &treePtr, KeyType searchKey)
            throw (TreeException);
      // Recursively deletes an item from a binary search tree.
      // Precondition: treePtr points to a binary search tree,
      // searchKey is the search key of the item to be deleted.
      // Postcondition: Same as searchTreeDelete.
   
      void deleteNodeItem(TreeNode * &nodePtr);
      // Deletes the item in the root of a given tree.
      // Precondition: nodePtr points to the root of a
      // binary search tree; nodePtr != NULL.
      // Postcondition: The item in the root of the given
      // tree is deleted.
   
      void processLeftmost(TreeNode * &nodePtr,
                           TreeItemType& treeItem);
      // Retrieves and deletes the leftmost descendant of a
      // given node.
      // Precondition: nodePtr points to a node in a binary
      // search tree; nodePtr != NULL.
      // Postcondition: treeItem contains the item in the
      // leftmost descendant of the node to which nodePtr
      // points. The leftmost descendant of nodePtr is
      // deleted.
   
      void retrieveItem(TreeNode *treePtr, KeyType searchKey,
                        TreeItemType& treeItem) const
            throw (TreeException);
      // Recursively retrieves an item from a binary search
      // tree.
      // Precondition: treePtr points to a binary search tree,
      // searchKey is the search key of the item to be
      // retrieved.
      // Postcondition: Same as searchTreeRetrieve.
      // The following 9 methods are the same as for the ADT
      // binary tree, and so their specifications are abbreviated.
   
      void copyTree(TreeNode *treePtr, TreeNode * &newTreePtr) const;
      void destroyTree(TreeNode * &treePtr);
   
	 void preorderSave(TreeNode *treePtr, ofstream& stream, FunctionTypeSave visit);
      void preorder(TreeNode *treePtr, FunctionType visit);
	 void inorderSCount(TreeNode *treePtr, int& sCount, FunctionTypeSCount visit);
      void inorder(TreeNode *treePtr, FunctionType visit);
      void processTip(TreeNode *treePtr, FunctionTypeTip visit, string tip);
	 void postorder(TreeNode *treePtr, FunctionType visit);
                     TreeNode *rootPtr() const;
      void setRootPtr(TreeNode *newRoot);
      void getChildPtrs(TreeNode *nodePtr,
                        TreeNode * &leftChildPtr,
                        TreeNode * &rightChildPtr) const;
      void setChildPtrs(TreeNode *nodePtr,
                        TreeNode *leftChildPtr,
                        TreeNode *rightChildPtr);
   
   private:
      TreeNode *root; // pointer to root of tree
}; // end class
// End of header file.
   
#endif
