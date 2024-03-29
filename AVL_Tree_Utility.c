#include "AVL_Tree_Utility.h"
// Prototypes

/*
Name: clearTree
Process: recursively removes all nodes from tree and returns memory to OS,
         uses post order traversal strategy
Function input/parameters: pointer to root/ working pointer (AvlTreeNodType *)
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: free
*/
AvlTreeNodeType *clearTree( AvlTreeNodeType *wkgPtr )
    {
    if(wkgPtr == NULL)
        {
        return wkgPtr;
        }
    clearTree(wkgPtr->leftChildPtr);

    clearTree(wkgPtr->rightChildPtr);

    free(wkgPtr);

    return wkgPtr;
    }

/*
Name: compareRoomNumbers
Process: compares room numbers as follows:
         - if left room number is greater than the right room number, 
         returns value greater than zero (not necessarily 1)
         - if left room number is less than the right room number, 
         returns value less than zero (not necessarily -1)
         - if room numbers are equal but one is longer, longer one is greater
         - otherwise, returns zero
Function input/parameters: two room numbers (as strings)
                           to be compared (const char *)
Function output/parameters: none
Function output/returned: result as specified above (int)
Device input/---: none
Device output/---: none
Dependencies: isDigit
*/
int compareRoomNumbers( const char *roomNbrOne, const char *roomNbrTwo )
    {
    while(*roomNbrOne && *roomNbrTwo)
        {
        if(*roomNbrOne == *roomNbrTwo)
            {
            roomNbrOne++;
            roomNbrTwo++;
            }
        else
            {
            if(*roomNbrOne < *roomNbrTwo)
                {
                return -1;
                }
            else
                {
                return 1;
                }
            }
        }
    return 0;
    }

/*
Name: copyString
Process: copies string from source to destination
Function input/parameters: source string (const char *)
Function output/parameters: destination string (char *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: none
*/
void copyString( char *dest, const char *source )
    {
    int index = 0;
    int length = 0;
    while(source[index] != NULL_CHAR)
        {
        index++;
        length++;
        }
    for(index = 0; index <= length; index++)
        {
        dest[index] = source[index];
        }
    }

/*
Name: copyTree
Process: creates duplicate copy of given tree, allocates all new nodes,
         returns pointer to root of new tree or NULL if original tree was empty,
         uses pre order traversal strategy
Function input/parameters: tree root/working pointer (AvlTreeNodeType *)
Function output/parameters: none
Function output/returned: tree root of copied tree
                          or NULL as specified (AvlTreeNodeType *)
Device input/---: none
Device output/---: none
Dependencies: variable options
done
*/
AvlTreeNodeType *copyTree( AvlTreeNodeType *rootPtr )
    {
    if(rootPtr == NULL)
        {
        return NULL;
        }

    AvlTreeNodeType *copied = 
                             (AvlTreeNodeType *)malloc(sizeof(AvlTreeNodeType));

    copied = createTreeNodeFromNode(*rootPtr);

    copied->leftChildPtr = copyTree(rootPtr->leftChildPtr);
    copied->rightChildPtr = copyTree(rootPtr->rightChildPtr);

    return copied;
    }

/*
Name: createTreeNodeFromData
Process: captures data from individual data items, 
         dynamically creates new node,
         copies data, sets child pointers to NULL,
         and returns pointer to new node         
Function input/parameters: room number, building room, 
                           and class setup (const char *), capacity (int)
Function output/parameters: none
Function output/returned: pointer to new node as specified (AvlTreeNodeType *)
Device input/---: none
Device output/---: none
Dependencies: malloc, sizeof, copyString
*/
AvlTreeNodeType *createTreeNodeFromData( const char *rmNumber, 
                   const char *buildingRm, const char *clsSetup, int capacity )
    {
    AvlTreeNodeType *newNode = 
                             (AvlTreeNodeType *)malloc(sizeof(AvlTreeNodeType));

    copyString(newNode->buildingRoom, buildingRm);
    copyString(newNode->classSetup, clsSetup);
    copyString(newNode->roomNumber, rmNumber);
    newNode->roomCapacity = capacity;
    newNode->leftChildPtr = NULL;
    newNode->rightChildPtr = NULL;
    return newNode;
    }

/*
Name: createTreeNodeFromNode
Process: captures data from source node pointer, dynamically creates new node,
         copies data, sets child pointers to NULL, 
         and returns pointer to new node,
         one line of code         
Function input/parameters: node to be copied (const AvlTreeNodeType)
Function output/parameters: none
Function output/returned: pointer to new node as specified (AvlTreeNodeType *)
Device input/---: none
Device output/---: none
Dependencies: variable options
*/
AvlTreeNodeType *createTreeNodeFromNode( const AvlTreeNodeType sourceNode )
    {
    AvlTreeNodeType *newNode = 
                             (AvlTreeNodeType *)malloc(sizeof(AvlTreeNodeType));
    copyString(newNode->buildingRoom, sourceNode.buildingRoom);
    copyString(newNode->classSetup, sourceNode.classSetup);
    copyString(newNode->roomNumber, sourceNode.roomNumber);
    newNode->roomCapacity = sourceNode.roomCapacity;
    newNode->leftChildPtr = NULL;
    newNode->rightChildPtr = NULL;

    return newNode;
    }

/*
Name: displayChars
Process: recursively displays a specified number of characters
Function input/parameters: number of characters (int), output character (char)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/monitor: characters displayed as specified
Dependencies: displayChars (recursively)
*/
void displayChars( int numChars, char outChar )
    {
    numChars -= 1;

    printf("%c", outChar);

    if(numChars != 0)
        {
        displayChars(numChars, outChar);
        }
    }

/*
Name: findBalanceFactor
Process: finds balance factor by subtracting
         height differences between left and right subtrees
Function input/parameters: pointer to current tree location (TreeNodeType *)
Function output/parameters: none
Function output/returned: difference between two subtree heights (int)
Device input/---: none
Device output/---: none
Dependencies: variable options
*/
int findBalanceFactor( AvlTreeNodeType *wkgPtr )
    {
    if(wkgPtr == NULL)
        {
        return 0;
        }
    return findTreeHeight(wkgPtr->leftChildPtr) - 
                                          findTreeHeight(wkgPtr->rightChildPtr);
    }

/*
Name: findMax
Process: finds maximum between two values, returns larger
Function input/parameters: two values (int)
Function output/parameters: none
Function output/returned: larger of two values (int)
Device input/---: none
Device output/---: none
Dependencies: none
*/
int findMax( int one, int other )
    {
    return (one > other) ? one : other;
    }

/*
Name: findTreeHeight
Process: recursively finds tree height from current node to bottom of tree
Function input/parameters: pointer to current tree location (AvlTreeNodeType *)
Function output/parameters: none
Function output/returned: -1 if empty tree, 0 if no subtrees,
                          max height of subtrees otherwise
Device input/---: none
Device output/---: none
Dependencies: variable options
*/
int findTreeHeight( AvlTreeNodeType *wkgPtr )
    {
    int empty = -1;
    int noSub = 0;
    int maxHeight = 0;

    int leftHeight;
    int rightHeight;

    if(wkgPtr == NULL)
        {
        return empty;
        }
    if(wkgPtr->leftChildPtr == NULL && wkgPtr->rightChildPtr == NULL)
        {
        return noSub;
        }
    else
        {
        leftHeight = findTreeHeight(wkgPtr->leftChildPtr);
        rightHeight = findTreeHeight(wkgPtr->rightChildPtr);
        maxHeight = findMax(leftHeight, rightHeight) + 1;

        return maxHeight;
        }
    }

/*
Name: initializeTree
Process: returns NULL to set tree to empty
Function input/parameters: none
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: none
*/
AvlTreeNodeType *initializeTree()
    {
    return NULL;
    }

/*
Name: inOrderDisplay
Process: recursively iterates across tree using in order strategy,
         displays node values
Function input/parameters: pointer to current tree location (AvlTreeNodeType *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: inOrderDisplay (recursively)
*/
void inOrderDisplay( AvlTreeNodeType *wkgPtr )
    {
    if(wkgPtr != NULL)
        {
        // recurse to the left
        inOrderDisplay(wkgPtr->leftChildPtr);
        // print data
        printf("%s, ", wkgPtr->roomNumber);
        // recurse to the right
        inOrderDisplay(wkgPtr->rightChildPtr);
        }
    }

/*
Name: insert
Process: recursively finds location to insert node, inserts node,
         then follows recursion back up tree to implement balancing,
         does not allow duplicate entries
Function input/parameters: pointer to current tree location (AvlTreeNodeType *),
                           room number, building room data, class setup (char *)
Function output/parameters: none
Function output/returned: pointer to calling function/tree node above
                          where function is called
Device input/---: none
Device output/monitor: actions displayed as function progresses
Dependencies: createDataNode, compareRoomNumbers, findBalanceFactor,
              insert (recursively), printf
*/
AvlTreeNodeType *insert( AvlTreeNodeType *wkgPtr, 
                     char *rmNmbr, char *bldgRm, char *clsSetup, int capacity )
    {
    int balance;
    int spaces = 3;

    if(wkgPtr == NULL)
        {
        AvlTreeNodeType *newNode = 
                     createTreeNodeFromData(rmNmbr, bldgRm, clsSetup, capacity);

        return newNode;
        }
    
    if(compareRoomNumbers(wkgPtr->roomNumber, rmNmbr) > 0)
        {
        wkgPtr->leftChildPtr = 
               insert(wkgPtr->leftChildPtr, rmNmbr, bldgRm, clsSetup, capacity);
        }
    else if(compareRoomNumbers(wkgPtr->roomNumber, rmNmbr) < 0)
        {
        wkgPtr->rightChildPtr = 
              insert(wkgPtr->rightChildPtr, rmNmbr, bldgRm, clsSetup, capacity);
        }
    else    
        {
        return wkgPtr;
        }

    balance = findBalanceFactor(wkgPtr);

    if(balance > 1 && 
               compareRoomNumbers(rmNmbr, wkgPtr->leftChildPtr->roomNumber) < 0)
        {
        displayChars(findTreeHeight(wkgPtr), SPACE);
        printf("Identified: Left Left Case\n");
        displayChars(spaces, SPACE);
        return rotateRight(wkgPtr);
        }
    if(balance < -1 && 
              compareRoomNumbers(rmNmbr, wkgPtr->rightChildPtr->roomNumber) > 0)
        {
        displayChars(findTreeHeight(wkgPtr), SPACE);
        printf("Identified: Right Right Case\n");
        displayChars(spaces, SPACE);
        return rotateLeft(wkgPtr);
        }
    if(balance > 1 && 
               compareRoomNumbers(rmNmbr, wkgPtr->leftChildPtr->roomNumber) > 0)
        {
        displayChars(findTreeHeight(wkgPtr), SPACE);
        printf("Identified: Left Right Case\n");
        displayChars(spaces, SPACE);
        wkgPtr->leftChildPtr = rotateLeft(wkgPtr->leftChildPtr);
        displayChars(spaces + 1, SPACE);
        wkgPtr = rotateRight(wkgPtr);
        return wkgPtr;
        }
    if(balance < -1 && 
              compareRoomNumbers(rmNmbr, wkgPtr->rightChildPtr->roomNumber) < 0)
        {
        displayChars(findTreeHeight(wkgPtr), SPACE);
        printf("Identified: Right Left Case\n");
        displayChars(spaces, SPACE);
        wkgPtr->rightChildPtr = rotateRight(wkgPtr->rightChildPtr);
        displayChars(spaces + 1, SPACE);
        wkgPtr = rotateLeft(wkgPtr);
        return wkgPtr;
        }
    return wkgPtr;
    }

/*
Name: isDigit
Process: reports if character provided is a character digit
Function input/parameters: test character (char)
Function output/parameters: none
Function output/returned: Boolean result of test (bool)
Device input/---: none
Device output/---: none
Dependencies: none
*/
bool isDigit( char testChar )
    {
    return testChar >= '0' && testChar <= '9';
    }

/*
Name: isEmpty
Process: reports if tree is empty, using one line of code
Function input/parameters: pointer to current root node (AvlTreeNodeType *)
Function output/parameters: none
Function output/returned: Boolean result of test (bool)
Device input/---: none
Device output/---: none
Dependencies: none
*/
bool isEmpty( AvlTreeNodeType *rootPtr )
    {
    return rootPtr == NULL;
    }

/*
Name: rotateLeft
Process: conducts left rotation by manipulation of given pointer
Function input/parameters: pointer to given subtree to rotate
Function output/parameters: none
Function output/returned: pointer to calling function/tree node above
                          where function is called
Device input/---: none
Device output/monitor: rotation action displayed  ("- Rotating Left")
Dependencies: printf
*/
AvlTreeNodeType *rotateLeft( AvlTreeNodeType *oldParentPtr )
    {
    AvlTreeNodeType *newParent = oldParentPtr->rightChildPtr;
    AvlTreeNodeType *temp = newParent->leftChildPtr;
    printf("- Rotating Left\n");

    newParent->leftChildPtr = oldParentPtr;
    oldParentPtr->rightChildPtr = temp;

    return newParent;
    }

/*
Name: rotateRight
Process: conducts right rotation by manipulation of given pointer
Function input/parameters: pointer to given subtree to rotate
Function output/parameters: none
Function output/returned: pointer to calling function/tree node above
                          where function is called
Device input/---: none
Device output/monitor: rotation action displayed  ("- Rotating Right")
Dependencies: printf
*/
AvlTreeNodeType *rotateRight( AvlTreeNodeType *oldParentPtr )
    {
    AvlTreeNodeType *newParent = oldParentPtr->leftChildPtr;
    AvlTreeNodeType *temp = newParent->rightChildPtr;
    printf("- Rotating Right\n");

    newParent->rightChildPtr = oldParentPtr;
    oldParentPtr->leftChildPtr = temp;
    
    return newParent;
    }

/*
Name: search
Process: recursively searches tree for specified data using room number key
Function input/parameters: pointer to working subtree (AvlTreeNodeType *),
                           room number (const char *)
Function output/parameters: none
Function output/returned: pointer to found node (AvlTreeNodeType *)
Device input/---: none
Device output/---: none
Dependencies: search (recursively)
*/
AvlTreeNodeType *search( AvlTreeNodeType *wkgPtr, const char *roomNumber )
    {
    int result = compareRoomNumbers(wkgPtr->roomNumber, roomNumber);

    if(wkgPtr == NULL || result == 0)
        {
        return wkgPtr;
        }
    if(result > 0)
        {
        return search(wkgPtr->rightChildPtr, roomNumber);
        }
    if(result < 0)
        {
        return search(wkgPtr->leftChildPtr, roomNumber);
        }
    
    return NULL;
    }

