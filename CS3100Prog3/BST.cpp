// *********************************************************
// Implementation file BST.cpp.
// *********************************************************
#include "BST.h" // header file
#include <cstddef> // definition of NULL
#include <iostream>
#include <fstream>

bool check_BST_code = false ;

BinarySearchTree::BinarySearchTree() : root(NULL)
{
} // end default constructor

BinarySearchTree::BinarySearchTree(
                               const BinarySearchTree& tree)
{
   copyTree(tree.root, root);
} // end copy constructor

BinarySearchTree::~BinarySearchTree()
{
   if (check_BST_code) cout << "Start Tree Destructor" << endl ;
   destroyTree(root);
   if (check_BST_code) cout << "Finish Tree Destructor" << endl ;
} // end destructor

bool BinarySearchTree::isEmpty() const
{
   return (root == NULL);
} // end searchTreeIsEmpty

void BinarySearchTree::searchTreeInsert(
                               const TreeItemType& newItem)
{
   insertItem(root, newItem);
} // end searchTreeInsert

void BinarySearchTree::searchTreeDelete(KeyType searchKey) 
                           throw (TreeException)
{
   deleteItem(root, searchKey);
} // end searchTreeDelete

void BinarySearchTree::searchTreeRetrieve(KeyType searchKey,
                                          TreeItemType& treeItem) const
                                           throw (TreeException)
{
   // if retrieveItem throws a TreeException, it is
   // ignored here and passed on to the point in the code
   // where searchTreeRetrieve was called
   retrieveItem(root, searchKey, treeItem);
} // end searchTreeRetrieve


//BEGIN ADDED FUNCTIONS
void BinarySearchTree::saveTree(FunctionTypeSave visit, ofstream& stream)
{
   preorderSave(root, stream, visit);
}

void BinarySearchTree::countSuspects(FunctionTypeSCount visit, int& sCount)
{
   inorderSCount(root, sCount, visit);
}

void BinarySearchTree::tipTraverse(FunctionTypeTip visit, string tip)
{
   processTip(root, visit, tip);
}

void BinarySearchTree::processTip(TreeNode *treePtr, FunctionTypeTip visit,
                          string tip)
{
   if (treePtr != NULL)
   {  processTip(treePtr->leftChildPtr, visit, tip);
      processTip(treePtr->rightChildPtr, visit, tip);
      visit(treePtr->item, tip);
   }
}

void BinarySearchTree::inorderSCount(TreeNode *treePtr, int& sCount,
                          FunctionTypeSCount visit)
{
  if (treePtr != NULL)
   {  inorderSCount(treePtr->leftChildPtr, sCount, visit);
      visit(treePtr->item, sCount);
      inorderSCount(treePtr->rightChildPtr, sCount, visit);
   }
}

void BinarySearchTree::preorderSave(TreeNode *treePtr, ofstream& stream,
                          FunctionTypeSave visit)
{
   if (treePtr != NULL)
   {  visit(treePtr->item, stream);
      preorderSave(treePtr->leftChildPtr, stream, visit);
      preorderSave(treePtr->rightChildPtr, stream, visit);
   }
}
//END ADDED FUNCTIONS

void BinarySearchTree::preorderTraverse(FunctionType visit)
{
   preorder(root, visit);
} // end preorderTraverse

void BinarySearchTree::inorderTraverse(FunctionType visit)
{
   inorder(root, visit);
} // end inorderTraverse

void BinarySearchTree::postorderTraverse(FunctionType visit)
{
   postorder(root, visit);
} // end postorderTraverse

void BinarySearchTree::insertItem(TreeNode *& treePtr,
                                  const TreeItemType& newItem)
{
   if (treePtr == NULL)
   {  // position of insertion found; insert after leaf

      // create a new node
      treePtr = new TreeNode(newItem, NULL, NULL);

      // was allocation successful?
      if (treePtr == NULL)
         throw TreeException("TreeException: insert failed");
   }

   // else search for the insertion position
   else if (newItem.getKey() < treePtr->item.getKey())
      // search the left subtree
      insertItem(treePtr->leftChildPtr, newItem);

   else // search the right subtree
      insertItem(treePtr->rightChildPtr, newItem);
} // end insertItem

void BinarySearchTree::deleteItem(TreeNode * &treePtr,
                                  KeyType searchKey)
                                throw (TreeException)
// Calls: deleteNodeItem.
{
   if (treePtr == NULL)
      throw TreeException(
         "TreeException: delete failed"); // empty tree

   else if (searchKey == treePtr->item.getKey())
      // item is in the root of some subtree
      deleteNodeItem(treePtr); // delete the item

   // else search for the item
   else if (searchKey < treePtr->item.getKey())
      // search the left subtree
      deleteItem(treePtr->leftChildPtr, searchKey);

   else // search the right subtree
      deleteItem(treePtr->rightChildPtr, searchKey);
} // end deleteItem

void BinarySearchTree::deleteNodeItem(TreeNode * &nodePtr)
// Algorithm note: There are four cases to consider:
// 1. The root is a leaf.
// 2. The root has no left child.
// 3. The root has no right child.
// 4. The root has two children.
// Calls: processLeftmost.
{
   TreeNode *delPtr;
   TreeItemType replacementItem;

   // test for a leaf
   if ( (nodePtr->leftChildPtr == NULL) &&
        (nodePtr->rightChildPtr == NULL) )
   {  delete nodePtr;
      nodePtr = NULL;
   } // end if leaf

   // test for no left child
   else if (nodePtr->leftChildPtr == NULL)
   {  delPtr = nodePtr;
      nodePtr = nodePtr->rightChildPtr;
      delPtr->rightChildPtr = NULL;
      delete delPtr;
   } // end if no left child

   // test for no right child
   else if (nodePtr->rightChildPtr == NULL)
   {  delPtr = nodePtr;
      nodePtr = nodePtr->leftChildPtr;
      delPtr->leftChildPtr = NULL;
      delete delPtr;
   } // end if no right child

   // there are two children:
   // retrieve and delete the inorder successor
   else
   {  processLeftmost(nodePtr->rightChildPtr,
                      replacementItem);
      nodePtr->item = replacementItem;
   } // end if two children
} // end deleteNodeItem

void BinarySearchTree::processLeftmost(TreeNode *&nodePtr,
                                       TreeItemType& treeItem)
{
   if (nodePtr->leftChildPtr == NULL)
   {  treeItem = nodePtr->item;
      TreeNode *delPtr = nodePtr;
      nodePtr = nodePtr->rightChildPtr;
      delPtr->rightChildPtr = NULL; // defense
      delete delPtr;
   }

   else
      processLeftmost(nodePtr->leftChildPtr, treeItem);
} // end processLeftmost

void BinarySearchTree::retrieveItem(TreeNode *treePtr,
                                    KeyType searchKey,
                                    TreeItemType& treeItem) const
                                    throw (TreeException)
{
   if (treePtr == NULL)
      throw TreeException(
         "TreeException: searchKey not found");

   else if (searchKey == treePtr->item.getKey())
      // item is in the root of some subtree
      treeItem = treePtr->item;

   else if (searchKey < treePtr->item.getKey())
      // search the left subtree
      retrieveItem(treePtr->leftChildPtr,
                   searchKey, treeItem);

   else // search the right subtree
      retrieveItem(treePtr->rightChildPtr,
                   searchKey, treeItem);
} // end retrieveItem

// Implementations of copyTree, destroyTree, preorder,
// inorder, postorder, setRootPtr, rootPtr, getChildPtrs,
// setChildPtrs, and the overloaded assignment operator are
// the same as for the ADT binary tree.

void BinarySearchTree::copyTree(TreeNode *treePtr,
                          TreeNode *& newTreePtr) const
{
   // preorder traversal
   if (treePtr != NULL)
   {  // copy node
      newTreePtr = new TreeNode(treePtr->item, NULL, NULL);
      if (newTreePtr == NULL)
         throw TreeException(
            "TreeException: Cannot allocate memory");

      copyTree(treePtr->leftChildPtr, newTreePtr->leftChildPtr);
      copyTree(treePtr->rightChildPtr, newTreePtr->rightChildPtr);
   }
   else
      newTreePtr = NULL; // copy empty tree
} // end copyTree

void BinarySearchTree::destroyTree(TreeNode *& treePtr)
{
   // postorder traversal
   if (treePtr != NULL)
   {  
      if (check_BST_code) cout << "NOT NULL" << endl ;
      destroyTree(treePtr->leftChildPtr);
      destroyTree(treePtr->rightChildPtr);
      delete treePtr;
      treePtr = NULL;
   } // end if
} // end destroyTree

void BinarySearchTree::preorder(TreeNode *treePtr,
                          FunctionType visit)
{
   if (treePtr != NULL)
   {  visit(treePtr->item);
      preorder(treePtr->leftChildPtr, visit);
      preorder(treePtr->rightChildPtr, visit);
   } // end if
} // end preorder

void BinarySearchTree::inorder(TreeNode *treePtr,
                         FunctionType visit)
{
   if (treePtr != NULL)
   {  inorder(treePtr->leftChildPtr, visit);
      visit(treePtr->item);
      inorder(treePtr->rightChildPtr, visit);
   } // end if
} // end inorder

void BinarySearchTree::postorder(TreeNode *treePtr,
                           FunctionType visit)
{
   if (treePtr != NULL)
   {  postorder(treePtr->leftChildPtr, visit);
      postorder(treePtr->rightChildPtr, visit);
      visit(treePtr->item);
   } // end if
} // end postorder

void BinarySearchTree::setRootPtr(TreeNode *newRoot)
{
   root = newRoot;
} // end setRoot

TreeNode *BinarySearchTree::rootPtr() const
{
  return root;
} // end rootPtr

void BinarySearchTree::getChildPtrs(TreeNode *nodePtr,
                              TreeNode *& leftPtr,
                              TreeNode *& rightPtr) const
{
   leftPtr = nodePtr->leftChildPtr;
   rightPtr = nodePtr->rightChildPtr;
} // end getChildPtrs

void BinarySearchTree::setChildPtrs(TreeNode *nodePtr,
                              TreeNode *leftPtr,
                              TreeNode *rightPtr)
{
   nodePtr->leftChildPtr = leftPtr;
   nodePtr->rightChildPtr = rightPtr;
} // end setChildPtrs

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& rhs)
{
   if (this != &rhs)
   {  destroyTree(root); // deallocate left-hand side
      copyTree(rhs.root, root); // copy right-hand side
   } // end if
   return *this;
} // end operator=

// End of implementation file.
