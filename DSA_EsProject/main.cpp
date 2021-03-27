/*
 * CS-250 DATA STRUCTURES AND ALGORITHMS
 * *Project By
 * Group Members:
 * Fatima Seemab (291310)
 * Maryam Fatima (290479)
 * Mahum Samar (290647)
 * BSCS-9B
 *
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "CircularQueue.cpp"


using namespace std;

class ArticleTree;

class Article;

class ArticleNode;

class JournalAvlTree;

class JournalInfo;

class HashJournal;

class Author;

class AuthorAVLtree;

class CoAuthorAVLtree;

class JournalInfo {
public:
    string name;
    string journalIso;
    string issn;

};

class JournalAvlNode {
    //class to create the nodes for AVL tree
public:
    JournalInfo *journalInfo;
    JournalAvlNode *leftChild;
    JournalAvlNode *rightChild;
};

class JournalAvlTree {
//    class to create AVL tree for storing the journal info
public:
    JournalAvlNode *root;
//    loc and preLoc used in searching
    JournalAvlNode *loc;
    JournalAvlNode *preLoc;

    JournalAvlTree() {
        //constructor
        root = NULL;
        preLoc = NULL;
        loc = NULL;
    }

    bool IsEmpty() {
        //method to check if the tree is empty
        return root == NULL;
    }

    JournalInfo *SearchJournal(string issn) {
        // Method to search the issn in the tree
        loc = root;
        preLoc = NULL;
        while (loc != NULL && loc->journalInfo->issn != issn) {
            // Until value is not found or reached the end of the tree
            if (issn < loc->journalInfo->issn) {
                preLoc = loc;
                loc = loc->leftChild;
            } else {
                preLoc = loc;
                loc = loc->rightChild;
            }
        }
        if (loc != NULL) {
//            returns the journal object if its found otherwise NULL
            return loc->journalInfo;
        } else {
            return NULL;
        }

    }

    JournalInfo *InsertWithoutDuplicationJournal(JournalInfo *journalInfo) {
        //method to insert the new node if the value is not already existing in tree
        JournalInfo *ji = SearchJournal(journalInfo->issn);
        //if value is not found
        if (loc == NULL) {
            //new node is created
            JournalAvlNode *newNode = new JournalAvlNode();
            newNode->journalInfo = journalInfo;
            if (preLoc != NULL) {
                //if node is not root tree
                if (journalInfo->issn < preLoc->journalInfo->issn) {
                    //if value is less
                    preLoc->leftChild = newNode;
                } else {
                    preLoc->rightChild = newNode;
                }
            } else {
                //if tree is empty
                root = newNode;
            }
            //balances tree after insertion
            CheckBalancedAvlTreeJournal(root);
            return newNode->journalInfo;

        } else {
            //if value already existing
            return ji;
        }

    }

    void PreOrder(JournalAvlNode *treeNode) {
        // method used to print he values in preOrder
        if (treeNode != NULL) {
            cout << "ISO:\t " << treeNode->journalInfo->journalIso << "\t\t";
            cout << "ISSN:\t " << treeNode->journalInfo->issn << "\n";
            cout << "Name:\t " << treeNode->journalInfo->name;
            printf("\n____________________________________________________________________________________________________________\n");

            PreOrder(treeNode->leftChild);
            PreOrder(treeNode->rightChild);
        }
    }

    int height(JournalAvlNode *treeNode) {

        //method used to find the height of the tree
        if (treeNode == NULL) {
            //base case
            return -1;
        } else {
            //recursive case
            //until the leaf node is reached
//            its left and right child are transversed to find the height
            return (1 + max(height(treeNode->leftChild), height(treeNode->rightChild)));
        }
    }

private:
    int BalanceFactor(JournalAvlNode *treeNode) {
        //method to find the balance factor of a given node.
        if (treeNode == NULL) {
            //if node is null
            return 0;
        }
        //recursive call
        //balance factor function calls the height method recursively.
        //returns the height of left subtree subtracted by the height of right subtree.
        return height(treeNode->leftChild) - height(treeNode->rightChild);
    }

    static JournalAvlNode *LeftRotate(JournalAvlNode *x) {
        //method to left rotate the subtree which is left left heavy
//for the tree like this
//                    C  -> x
//                   /
//                  B   -> y
//                 /
//                A

        JournalAvlNode *y = x->rightChild;
        x->rightChild = y->leftChild;
        y->leftChild = x;
        return y;
    }

    static JournalAvlNode *RightRotate(JournalAvlNode *x) {
        //method to right rotate the subtree
        //which is right right heavy
//                A     -> x
//                  \
//                    B     -> y
//                     \
//                       C

        JournalAvlNode *y = x->leftChild;
        x->leftChild = y->rightChild;
        y->rightChild = x;
        return y;
    }

    JournalAvlNode *RightLeftRotate(JournalAvlNode *x) {
        //method to right left rotate the subtree
        //which is right left heavy
//            A     -> x
//              \
//                C     -> y
//               /
//              B
        JournalAvlNode *y = x->rightChild;
        if (BalanceFactor(y) == 1) {
            //when right child of x is having balance factor of 1
            y = RightRotate(y);
        }
        x->rightChild = y;
        //left rotate
        return LeftRotate(x);
    }

    JournalAvlNode *LeftRightRotate(JournalAvlNode *x) {
        //method to left right rotate subtree
        //which is left right heavy
//        for the case like below

//                C -> x
//               /
//              A   -> y
//                \
//                  B
        JournalAvlNode *y = x->leftChild;
        if (BalanceFactor(y) == -1) {
            //if left subtree have balance factor of -1
            y = LeftRotate(y);
        }
        x->leftChild = y;
        return RightRotate(x);
    }

    void CheckBalancedAvlTreeJournal(JournalAvlNode *treeNode) {
        //this is the function that checks the tree is balanced or not after each insertion and deletion
        //this method uses bottom up approach

        if (treeNode != NULL) {
            //goes to the leaf node recursively
            CheckBalancedAvlTreeJournal(treeNode->leftChild);
            CheckBalancedAvlTreeJournal(treeNode->rightChild);
        }
        //after transversing tree in post order
        //the balance factor is checked for each node
        if (BalanceFactor(treeNode) == -2) {
            //if balance factor of node is -2
            //left rotate or right-left rotate function needs to be called
            //search function is called so that the preLoc and loc can be get
            //to get the reference of the parent of the node which is balanced
            //so that its address can be updated in its parent after rotation function returns.
            SearchJournal(treeNode->journalInfo->issn);
            if (BalanceFactor(treeNode->rightChild) == 1 && BalanceFactor(treeNode->rightChild->rightChild) == 0) {
                //if left rotate case
                if (preLoc != NULL) {
                    //if the unbalanced node is not the root node
                    if (preLoc->rightChild == treeNode) {
                        //if right child of parent
                        preLoc->rightChild = LeftRotate(treeNode);
                    } else {
                        //if left child of parent
                        preLoc->leftChild = LeftRotate(treeNode);
                    }
                } else {
                    //if the unbalanced node is root node
                    root = LeftRotate(treeNode);
                }
            } else {
                //if the double rotation case occurs
                //unbalanced node have right-left heavy subtree
                if (preLoc != NULL) {
                    if (preLoc->rightChild == treeNode) {

                        preLoc->rightChild = RightLeftRotate(treeNode);
                    } else {
                        preLoc->leftChild = RightLeftRotate(treeNode);
                    }
                } else {
                    root = RightLeftRotate(treeNode);
                }
            }
        }

        if (BalanceFactor(treeNode) == 2) {
            //if balance factor of node is -2
            SearchJournal(treeNode->journalInfo->issn);
            if (BalanceFactor(treeNode->leftChild) == 1 && BalanceFactor(treeNode->leftChild->leftChild) == 0) {
                //if right rotate
                //left left heavy subtree
                if (preLoc != NULL) {
                    //if unbalanced node is not root
                    if (preLoc->rightChild == treeNode) {

                        preLoc->rightChild = RightRotate(treeNode);
                    } else {
                        preLoc->leftChild = RightRotate(treeNode);
                    }
                } else {
                    //if unbalanced node is root
                    root = RightRotate(treeNode);
                }
            } else {
                //if unbalanced node needs double rotation
                if (preLoc != NULL) {
                    //if not root
                    if (preLoc->rightChild == treeNode) {

                        preLoc->rightChild = LeftRightRotate(treeNode);
                    } else {
                        preLoc->leftChild = LeftRightRotate(treeNode);
                    }
                } else {
                    //if root
                    root = LeftRightRotate(treeNode);
                }
            }
        }
    }

};

class HashJournal {
public:
    //    class for creating hash table for journal
    static const unsigned int arraySize = 29;
    JournalAvlTree *journalHashArray[arraySize];

    HashJournal() {
        //constructor
        for (int i = 0; i < arraySize; ++i) {
            journalHashArray[i] = new JournalAvlTree();
        }
    }

    static unsigned short int JournalHashFunction(string issn) {
        //        hash function for journal hash table
        int seed = 13; //prime number
        unsigned long hash = 0;
        for (int i = 0; i < issn.length(); i++) {
            hash = (hash * seed) + issn[i];
        }
        return hash % arraySize; //SIZE is prime, bigger than total journals like 29
    }

    JournalInfo *InsertJournalInfo(JournalInfo *journalInfo) {
        //method to insert journal info in avl tree
        int index = JournalHashFunction(journalInfo->issn);
        return journalHashArray[index]->InsertWithoutDuplicationJournal(journalInfo);
    }

    void PrintTable() {
        printf("\t\t\t\t\t Journal Information");
        printf("\n____________________________________________________________________________________________________________\n\n");
        //method to print hash table for journal
        for (int i = 0; i < arraySize; i++) {
            journalHashArray[i]->PreOrder(journalHashArray[i]->root);
        }
    }

};

//global pointer for hash table of journal
HashJournal *hashJournal = new HashJournal();

class YearPosAuthorNode {
//Node for containing year of article written by author and position
public:
    int year;   //used to store year or position
    int count;
    YearPosAuthorNode *lChild;
    YearPosAuthorNode *rChild;
};

class YearPosAuthorTree {
//    class for creating AVL tree of author position wise
public:
    YearPosAuthorNode *root;
    YearPosAuthorNode *loc;
    YearPosAuthorNode *ploc;
    YearPosAuthorNode *x;
    YearPosAuthorNode *y;
    int balance_factor_x;
    int balance_factor_y;

    YearPosAuthorTree() {
//        constructor
        root = NULL;
        loc = NULL;
        ploc = NULL;
        x = NULL;
        y = NULL;
        balance_factor_x = 0;
        balance_factor_y = 0;
    }

    //Returns true if tree is empty
    bool IsEmpty() {
        return (root == NULL);
    }

    //Searches a value in tree, if not found loc becomes NULL
    YearPosAuthorNode *Search(int year) {
        loc = root;
        ploc = NULL;
        while (loc != NULL && loc->year != year) {
            if (year < loc->year) {
                //equal not used since
                //duplicate insertion is not allowed
                ploc = loc;
                loc = loc->lChild;
            } else {
                ploc = loc;
                loc = loc->rChild;
            }
        }

        if (loc != NULL) {
            return loc;
        } else
            return NULL;
    }

    //Inserts a value, and balances the tree if imbalance exists
    //Calls Balance method
    YearPosAuthorNode *Insert(int year) {
        //find logical position and parent node address
        YearPosAuthorNode *a = Search(year);
        //if not found
        if (loc == NULL) {
            YearPosAuthorNode *nn = new YearPosAuthorNode();
            nn->year = year;
            if (ploc != NULL) {
                //if not root, update the corresponding
                //child node pointer of parent
                if (year < ploc->year)
                    ploc->lChild = nn;
                else
                    ploc->rChild = nn;
                Balance();
            } else
                //if root, update root pointer
            {
                root = nn;
            }
            nn->count++;
            return nn;
        }

            //if already present
        else {
            loc->count++;
            return a;
        }
    }

private:
    //--------------Balancing Methods--------------

    //Finds Balance Factor of node using Height method
    int BalanceFactor(YearPosAuthorNode *pTree) {
        if (pTree != NULL)
            return Height(pTree->lChild) - Height(pTree->rChild);
        else
            return -1;
    }

    // IMBALANCE if found WHERE and OF WHAT TYPE
    void FindImbalance(YearPosAuthorNode *pTree) {
        if (pTree != NULL && (x == NULL || y == NULL)) {

            balance_factor_x = BalanceFactor(pTree);
            //if x is not null and its balance factor is 2 or -2
            if (x == NULL && 2 == abs(balance_factor_x)) {
                x = pTree;
                //find the balance factor of sub-trees of x
                //store y and its balance factor
                if (pTree->lChild != NULL) {
                    balance_factor_y = BalanceFactor(pTree->lChild);
                    y = pTree->lChild;
                }
                if (pTree->rChild != NULL) {
                    balance_factor_y = BalanceFactor(pTree->rChild);
                    y = pTree->rChild;
                }
                //output value of x and y about which rotation will happen
            }
            //traversal in preOrder
            FindImbalance(pTree->lChild);
            FindImbalance(pTree->rChild);
        }
    }

    //--------------Rotation Methods---------------
    void LeftRotate(YearPosAuthorNode *x) {
        //Search to get the parent of x
        Search(x->year);
        //y is right child of x
        YearPosAuthorNode *y = x->rChild;
        x->rChild = y->lChild;
        y->lChild = x;

        //update parent of x
        if (ploc == NULL)
            root = y;
        else if (ploc->rChild == x)
            ploc->rChild = y;
        else
            ploc->lChild = y;
    }

    void RightRotate(YearPosAuthorNode *x) {
        //Search to get the parent of x
        Search(x->year);
        //y is left child of x
        YearPosAuthorNode *y = x->lChild;
        x->lChild = y->rChild;
        y->rChild = x;
        //update parent of x
        if (ploc == NULL)
            root = y;
        else if (ploc->rChild == x)
            ploc->rChild = y;
        else
            ploc->lChild = y;
    }

    void RightLeftRotate(YearPosAuthorNode *x) {
        //first rotate right and then rotate left
        RightRotate(y);
        LeftRotate(x);
    }

    void LeftRightRotate(YearPosAuthorNode *x) {
        //first rotate left and then rotate right
        LeftRotate(y);
        RightRotate(x);
    }

    void Balance() {
//        method for balancing AVL tree
        x = NULL;
        y = NULL;
        FindImbalance(root);
        if (x != NULL && y != NULL) {

            if (balance_factor_x == -2 && balance_factor_y != 1) {
                LeftRotate(x);
            }
            if (balance_factor_x == 2 && balance_factor_y != -1) {
                RightRotate(x);
            }
            if (balance_factor_x == -2 && balance_factor_y == 1) {
                RightLeftRotate(x);
            }
            if (balance_factor_x == 2 && balance_factor_y == -1) {
                LeftRightRotate(x);
            }
        }
    }

public:
    /*
     *Recursive Case: To calculate the height of a node x, one needs to first calculate
     *the height of its left sub-tree and right-subtree.
     *The height of x is 1+Max(height of x�s left subtree, height of x�s right sub-tree).
     *Base Case: Height of an empty tree is -1.
    */
    int Height(YearPosAuthorNode *node) {
        int height = -1;
        if (node != NULL)
            height = 1 + max(Height(node->lChild), Height(node->rChild));
        return height;
    }

public:

    void PreOrder(YearPosAuthorNode *pTree) {
//first print year then go to left child and
//on returning go to right child
        if (pTree != NULL) {
            PreOrder(pTree->lChild);
            cout << " ___________ _____________ " << endl;
            cout << "\t" << pTree->year << "\t\t";
            cout << pTree->count << endl;

            PreOrder(pTree->rChild);

        }
    }

};

class Article {
//    class for storing information about particular article
public:
    int SIZE = 51;
    string Title;
    string DOI;
    int year;
    AuthorAVLtree *List_of_Authors;
    int numberOfAuthors;
    string month;
    string publisher;
    string type;
    string cited_references;
    int no_of_citation;
    JournalInfo *journal;

    static int HashFunction(string doi) {
        //hash function for article class
        int sum = 0;
        int n = doi.length();
        int start = 0;
        char cutDOI[400];
        try {
            for (int i = 0; i < n; i++) {
                cutDOI[i] = doi[i];
            }
        }
        catch (exception) {};
        for (int i = 0; i < n; i++) {
            sum = sum + int(cutDOI[i]);
        }
        sum = (sum % 50);
        return sum;
    }


};

class ArticleWrittenNode {
//    class for creating node that stores articles written by author
public:
    Article *article;
    ArticleWrittenNode *leftChild = NULL;
    ArticleWrittenNode *rightChild = NULL;
    unsigned short int position = 0;
};

class ArticleWrittenTree {
//class for creating AVL tree
public:
    int nodes = 0;
    ArticleWrittenNode *loc = NULL;
    ArticleWrittenNode *ploc = NULL;
    ArticleWrittenNode *root;
    bool leftHeavy;
    int l;
    int r;

    int Height(ArticleWrittenNode *pointer) {
        //Function to traverse left and right subtree of node to find the height
        if (pointer == NULL) {
            return -1;
        } else {
            return (1 + max(Height(pointer->leftChild), Height(pointer->rightChild)));
        }

    }

    int balanceFactor(ArticleWrittenNode *node) {
        leftHeavy = false;
        if (node == NULL) {
            return -1;
        } else {
            l = Height(node->leftChild);
            r = Height(node->rightChild);
            if (l > r) {
                leftHeavy = true;
            }
            int b_factor = l - r;
            return b_factor;
        }
    }

    bool isEmpty() {//To check whether tree is empty or not
        return (root == NULL);
    }

    ArticleWrittenNode *Insertion(Article *an, int position) {//To insert values in tree

        //New node is created and assigned a value
        ArticleWrittenNode *nn = new ArticleWrittenNode();

        nn->article = an;
        nn->position = position;
        nodes++;

        if (isEmpty()) {//If tree is empty new node is made as root

            root = nn;
            return nn;
        } else {
            //otherwise loc and ploc finds for the logical position and insert it
            ploc = NULL;
            loc = root;
            while (loc != NULL) {
                if (loc->article->Title[0] >= nn->article->Title[0]) {
                    ploc = loc;
                    loc = loc->leftChild;
                } else {
                    ploc = loc;
                    loc = loc->rightChild;
                }
            }
            if (ploc->article->Title[0] >= nn->article->Title[0]) {
                ploc->leftChild = nn;
                if (!IsBalanced(root)) {
                    if (leftHeavy) {
                        balanceFactor(root->leftChild);
                        if (leftHeavy) {
                            RotateForLeft(root);
                        } else {
                            RotateForLeftRight(root);
                        }
                    } else {
                        balanceFactor(root->rightChild);
                        if (!leftHeavy) {
                            RotateForRight(root);
                        } else {
                            RotateForRightLeft(root);
                        }
                    }
                } else {}
            } else {
                ploc->rightChild = nn;
                if (!IsBalanced(root)) {
                    if (leftHeavy) {
                        balanceFactor(root->leftChild);
                        if (leftHeavy) {
                            RotateForLeft(root);
                        } else {
                            RotateForLeftRight(root);
                        }
                    } else {
                        balanceFactor(ploc->rightChild);
                        if (!leftHeavy) {
                            RotateForRight(root);
                        } else {
                            RotateForRightLeft(root);
                        }
                    }
                } else {}
            }
            return nn;
        }
    }

    void InsertionYearWise(Article *an, int position) {//To insert values in tree
        //New node is created and assigned a value
        ArticleWrittenNode *nn = new ArticleWrittenNode();
        nn->article = an;
        nn->position = position;
        if (isEmpty()) {//If tree is empty new node is made as root
            root = nn;
            return;
        } else {
            //otherwise loc and ploc finds for the logical position and insert it
            ploc = NULL;
            loc = root;
            while (loc != NULL) {
                if (loc->article->year >= nn->article->year) {
                    ploc = loc;
                    loc = loc->leftChild;
                } else {
                    ploc = loc;
                    loc = loc->rightChild;
                }
            }
            if (ploc->article->year >= nn->article->year) {

                ploc->leftChild = nn;
                if (!IsBalanced(root)) {
                    if (leftHeavy) {
                        balanceFactor(root->leftChild);
                        if (leftHeavy) {
                            RotateForLeft(root);
                        } else {

                            RotateForLeftRight(root);
                        }
                    } else {
                        balanceFactor(root->rightChild);
                        if (!leftHeavy) {
                            RotateForRight(root);
                        } else {
                            RotateForRightLeft(root);
                        }
                    }
                } else {}
            } else {
                ploc->rightChild = nn;
                if (!IsBalanced(root)) {
                    if (leftHeavy) {
                        balanceFactor(root->leftChild);
                        if (leftHeavy) {
                            RotateForLeft(root);
                        } else {
                            RotateForLeftRight(root);
                        }
                    } else {
                        balanceFactor(ploc->rightChild);
                        if (!leftHeavy) {
                            RotateForRight(root);
                        } else {
                            RotateForRightLeft(root);
                        }
                    }
                } else {}
            }
        }
    }

    void SearchUnbalanced(ArticleWrittenNode *node) {
        ArticleWrittenNode *temp;
        if (loc == NULL) {
            return;
        }
        if (!IsBalanced(loc)) {
            if (leftHeavy) {
                balanceFactor(loc->leftChild);
                if (leftHeavy) {
                    RotateForLeft(loc);
                } else {
                    RotateForLeftRight(loc);
                }
            } else {
                balanceFactor(loc->leftChild);
                if (leftHeavy) {
                    RotateForRightLeft(loc);
                } else {
                    RotateForRight(loc);
                }
            }
            return;
        } else {
            PreOrderTraversal(loc->leftChild);
            PreOrderTraversal(loc->rightChild);
        }
    }

    void Search(string value) {//To search for a value in tree
        //As a result loc and ploc will be updated
        ploc = NULL;
        loc = root;
        //searches until value is found or tree ends
        while (loc != NULL && loc->article->Title != value) {//ploc points to the previous node of loc
            ploc = loc;
            if (loc->article->Title > value) {   //In BST,left side has small values and right side has larger
                loc = loc->leftChild;
            } else { loc = loc->rightChild; }
        }
    }

    bool IsBalanced(ArticleWrittenNode *root) {
        int b = balanceFactor(root);
        if (b == 0 || b == 1 || b == -1) {
            return true;
        } else { return false; }
    }

    void RotateForRight(ArticleWrittenNode *x) {
        ploc = NULL;
        loc = root;
        if (x != root) {
            Search(x->article->Title);
        }
        //Rotation start from here
        ArticleWrittenNode *y = x->rightChild;
        x->rightChild = y->leftChild;
        y->leftChild = x;
        if (x == root) {//If x is root,after rotation we make y as root
            root = y;
        } else { ploc->leftChild = y; }
    }

    void RotateForLeft(ArticleWrittenNode *x) {
        ploc = NULL;
        loc = root;
        if (x != root) {//To restore the connection with the previous node
            Search(x->article->Title);
        }
        //Rotation start from here
        ArticleWrittenNode *y = x->leftChild;
        x->leftChild = y->rightChild;
        y->rightChild = x;
        if (x == root) {//If x is root,after rotation we make y as root
            root = y;
        } else {
            ploc->rightChild = y;
        }
    }

    void RotateForRightLeft(ArticleWrittenNode *x) {
        ArticleWrittenNode *y = x->rightChild;
        RotateForLeft(x->rightChild);
        RotateForRight(x);
    }

    void RotateForLeftRight(ArticleWrittenNode *x) {
        RotateForRight(x->leftChild);
        RotateForLeft(x);
    }

    void PreOrderTraversal(ArticleWrittenNode *pointer) {
        //In this function tree is traversed first its root than left and right subtree
        if (pointer != NULL) {
            cout << pointer->article->Title << endl;
            PreOrderTraversal(pointer->leftChild);
            PreOrderTraversal(pointer->rightChild);
        }
    }

    void InOrderTraversalYearWise(ArticleWrittenNode *pointer) {
        //In this function tree is traversed first its root than left and right subtree
        if (pointer != NULL) {
            InOrderTraversalYearWise(pointer->leftChild);
            cout << "Year: " << pointer->article->year << endl;
            cout << "Article: " << pointer->article->Title << endl;
            cout << "Journal Name: " << pointer->article->journal->name << "\n" << endl;
            InOrderTraversalYearWise(pointer->rightChild);
        }
    }

    AuthorAVLtree *authorAvlTree;

    void InOrderArticleCoAuthor(ArticleWrittenNode *pointer) {
        //In this function tree is traversed first its root than left and right subtree
        if (pointer != NULL) {
            InOrderArticleCoAuthor(pointer->leftChild);
            cout << "Year: " << pointer->article->year << endl;
            cout << "Number of Co-Authors: " << pointer->article->numberOfAuthors << endl;
            cout << "Article: " << pointer->article->Title << endl;
            cout << endl;
            InOrderArticleCoAuthor(pointer->rightChild);
        }
    }

};

class Author {
    //class for storing info about author
public:
    string name;
    string affiliations;
    ArticleWrittenTree *articles_written_yearwise;
    ArticleWrittenTree *articles_written;
    YearPosAuthorTree *yearAuthor;
    YearPosAuthorTree *pos;
    CoAuthorAVLtree *co_authors;
    int no_articles_written = 0;

    Author() {
        articles_written = new ArticleWrittenTree();
        yearAuthor = new YearPosAuthorTree();
        pos = new YearPosAuthorTree();
        articles_written_yearwise = new ArticleWrittenTree();
        //co_authors = new CoAuthorAVLtree(); created in insert method of author in hash table
        // because It is possible to declare a pointer to a declared but undefined type.
        //But C++ does not allow a reference to an undefined type.
    };
    // Author AVL Tree of articles written along with the position AuthorArticlesAVL
    // number of nodes in above Author AVL tree

    //Author AVL Tree of number of articles written per year by author
    // Author AVL Tree of number of co-authors of author for publication year
    void ToString() {
        cout << "Name: " << name << "\n";
        cout << "Number of Publications: " << no_articles_written << endl;
    }

    void ToStringYearwise() {
        cout << name << "\t";
        cout << "no of articles written: " << no_articles_written << endl;
        articles_written_yearwise->InOrderTraversalYearWise(articles_written_yearwise->root);
    }
};

class CoAuthorAVLnode {
//   class to create node for storing coAuthor
public:
    Author *data;
    unsigned short int articles_co_authored = 0;
    CoAuthorAVLnode *lChild;
    CoAuthorAVLnode *rChild;
};

class CoAuthorAVLtree {
//    class for creating AVL tree of coAuthors
public:
    CoAuthorAVLnode *root;
    CoAuthorAVLnode *loc;
    CoAuthorAVLnode *ploc;
    int nodes;
    CoAuthorAVLnode *x;
    CoAuthorAVLnode *y;
    int balance_factor_x;
    int balance_factor_y;

    CoAuthorAVLtree() {
//        constructor
        root = NULL;
        loc = NULL;
        ploc = NULL;

        x = NULL;
        y = NULL;
        nodes = 0;
        balance_factor_x = 0;
        balance_factor_y = 0;
    }

    //Returns true if tree is empty
    bool IsEmpty() {
        return root == NULL;
    }

    //Searches a value in tree, if not found loc becomes NULL
    CoAuthorAVLnode *Search(string name) {
        loc = root;
        ploc = NULL;
        while (loc != NULL && loc->data->name != name) {
            if (name < loc->data->name) {
                //equal not used since
                //duplicate insertion is not allowed
                ploc = loc;
                loc = loc->lChild;
            } else {
                ploc = loc;
                loc = loc->rChild;
            }
        }
        return loc;
    }


    //Inserts a value, and balances the tree if imbalance exists
    //Calls Balance method
    CoAuthorAVLnode *Insert(Author *value) {
        //find logical position and parent node address
        CoAuthorAVLnode *co_author_node = Search(value->name);
        //if not found
        if (loc == NULL) {
            CoAuthorAVLnode *nn = new CoAuthorAVLnode();
            nn->data = value;
            if (ploc != NULL) {
                //if not root, update the corresponding
                //child node pointer of parent
                if (value->name < ploc->data->name)
                    ploc->lChild = nn;
                else
                    ploc->rChild = nn;
                Balance();
            } else
                //if root, update root pointer
                root = nn;
            nodes++;
            nn->articles_co_authored++;
            return nn;
        }
            //if already present
        else {
            co_author_node->articles_co_authored++;
            return co_author_node;
        }
    }

private:
    //--------------Balancing Methods--------------

    //Finds Balance Factor of node using Height method
    int BalanceFactor(CoAuthorAVLnode *pTree) {
        if (pTree != NULL)
            return Height(pTree->lChild) - Height(pTree->rChild);
        else
            return -1;
    }

    // IMBALANCE if found WHERE and OF WHAT TYPE
    void FindImbalance(CoAuthorAVLnode *pTree) {
        if (pTree != NULL && (x == NULL || y == NULL)) {
            balance_factor_x = BalanceFactor(pTree);
            //if x is not null and its balance factor is 2 or -2
            if (x == NULL && 2 == abs(balance_factor_x)) {
                x = pTree;
                //find the balance factor of sub-trees of x
                //store y and its balance factor
                if (pTree->lChild != NULL) {
                    balance_factor_y = BalanceFactor(pTree->lChild);
                    y = pTree->lChild;
                }
                if (pTree->rChild != NULL) {
                    balance_factor_y = BalanceFactor(pTree->rChild);
                    y = pTree->rChild;
                }
            }
            //traversal in preOrder
            FindImbalance(pTree->lChild);
            FindImbalance(pTree->rChild);
        }
    }

    //--------------Rotation Methods---------------
    void LeftRotate(CoAuthorAVLnode *x) {
        //Search to get the parent of x
        Search(x->data->name);
        //y is right child of x
        CoAuthorAVLnode *y = x->rChild;
        x->rChild = y->lChild;
        y->lChild = x;

        //update parent of x
        if (ploc == NULL)
            root = y;
        else if (ploc->rChild == x)
            ploc->rChild = y;
        else
            ploc->lChild = y;
    }

    void RightRotate(CoAuthorAVLnode *x) {
        //Search to get the parent of x
        Search(x->data->name);
        //y is left child of x
        CoAuthorAVLnode *y = x->lChild;
        x->lChild = y->rChild;
        y->rChild = x;

        //update parent of x
        if (ploc == NULL)
            root = y;
        else if (ploc->rChild == x)
            ploc->rChild = y;
        else
            ploc->lChild = y;
    }

    void RightLeftRotate(CoAuthorAVLnode *x) {
        //first rotate right and then rotate left
        RightRotate(y);
        LeftRotate(x);
    }

    void LeftRightRotate(CoAuthorAVLnode *x) {
        //first rotate left and then rotate right
        LeftRotate(y);
        RightRotate(x);
    }

    void Balance() {
        x = NULL;
        y = NULL;
        FindImbalance(root);
        if (x != NULL && y != NULL) {

            if (balance_factor_x == -2 && balance_factor_y != 1) {
                LeftRotate(x);
            }
            if (balance_factor_x == 2 && balance_factor_y != -1) {
                RightRotate(x);
            }
            if (balance_factor_x == -2 && balance_factor_y == 1) {
                RightLeftRotate(x);
            }
            if (balance_factor_x == 2 && balance_factor_y == -1) {
                LeftRightRotate(x);
            }
        }
    }

public:
    /*
     *Recursive Case: To calculate the height of a node x, one needs to first calculate
     *the height of its left sub-tree and right-subtree.
     *The height of x is 1+Max(height of x�s left subtree, height of x�s right sub-tree).
     *Base Case: Height of an empty tree is -1.
    */
    int Height(CoAuthorAVLnode *node) {
        int height = -1;
        if (node != NULL)
            height = 1 + max(Height(node->lChild), Height(node->rChild));
        return height;
    }

    void PreOrder(CoAuthorAVLnode *pTree) {
        //first print data then go to left child and
        //on returning go to right child
        if (pTree != NULL) {
            PreOrder(pTree->lChild);
            printf("\n____________________________________________________________________________________________________________\n");
            cout << "Articles co_authored: " << pTree->articles_co_authored << endl;
            cout << pTree->data->name << endl;
            PreOrder(pTree->rChild);

        }
    }

};

class AuthorAVLnode {
//    node for storing author info in AVL tree
public:
    Author *data;
    string color;
    unsigned short int d;
    unsigned short int f;
    AuthorAVLnode *p;
    AuthorAVLnode *lChild;
    AuthorAVLnode *rChild;
};

class AuthorAVLtree {
public:
    AuthorAVLnode *root;
    AuthorAVLnode *loc;
    AuthorAVLnode *ploc;
    int numAuthor = 0;
    int nodes;
    AuthorAVLnode *x;
    AuthorAVLnode *y;
    int balance_factor_x;
    int balance_factor_y;

    AuthorAVLtree() {
//        constructor
        root = NULL;
        loc = NULL;
        ploc = NULL;

        x = NULL;
        y = NULL;
        nodes = 0;
        balance_factor_x = 0;
        balance_factor_y = 0;
    }

    //Returns true if tree is empty
    bool IsEmpty() {
        return root == NULL;
    }

    //Searches a value in tree, if not found loc becomes NULL
    Author *Search(string name) {
        loc = root;
        ploc = NULL;
        while (loc != NULL && loc->data->name != name) {
            if (name < loc->data->name) {
                //equal not used since
                //duplicate insertion is not allowed
                ploc = loc;
                loc = loc->lChild;
            } else {
                ploc = loc;
                loc = loc->rChild;
            }
        }

        if (loc != NULL)
            return loc->data;
        else
            return NULL;
    }


    //Inserts a value, and balances the tree if imbalance exists
    //Calls Balance method
    Author *Insert(Author *value) {
        //find logical position and parent node address
        Author *a = Search(value->name);
        //if not found
        if (loc == NULL) {
            AuthorAVLnode *nn = new AuthorAVLnode();
            nn->data = value;
            if (ploc != NULL) {
                //if not root, update the corresponding
                //child node pointer of parent
                if (value->name < ploc->data->name)
                    ploc->lChild = nn;
                else
                    ploc->rChild = nn;
                Balance();
            } else
                //if root, update root pointer
                root = nn;
            nodes++;
            return nn->data;
        }
            //if already present
        else {

            return a;
        }
    }

private:
    //--------------Balancing Methods--------------

    //Finds Balance Factor of node using Height method
    int BalanceFactor(AuthorAVLnode *pTree) {
        if (pTree != NULL)
            return Height(pTree->lChild) - Height(pTree->rChild);
        else
            return -1;
    }

    // IMBALANCE if found WHERE and OF WHAT TYPE
    void FindImbalance(AuthorAVLnode *pTree) {
        if (pTree != NULL && (x == NULL || y == NULL)) {
            balance_factor_x = BalanceFactor(pTree);
            //if x is not null and its balance factor is 2 or -2
            if (x == NULL && 2 == abs(balance_factor_x)) {
                x = pTree;
                //find the balance factor of sub-trees of x
                //store y and its balance factor
                if (pTree->lChild != NULL) {
                    balance_factor_y = BalanceFactor(pTree->lChild);
                    y = pTree->lChild;
                }
                if (pTree->rChild != NULL) {
                    balance_factor_y = BalanceFactor(pTree->rChild);
                    y = pTree->rChild;
                }
                //output value of x and y about which rotation will happen
            }
            //traversal in preOrder
            FindImbalance(pTree->lChild);
            FindImbalance(pTree->rChild);

        }
    }

    //--------------Rotation Methods---------------
    void LeftRotate(AuthorAVLnode *x) {
        //Search to get the parent of x
        Search(x->data->name);
        //y is right child of x
        AuthorAVLnode *y = x->rChild;
        x->rChild = y->lChild;
        y->lChild = x;

        //update parent of x
        if (ploc == NULL)
            root = y;
        else if (ploc->rChild == x)
            ploc->rChild = y;
        else
            ploc->lChild = y;
    }

    void RightRotate(AuthorAVLnode *x) {
        //Search to get the parent of x
        Search(x->data->name);
        //y is left child of x
        AuthorAVLnode *y = x->lChild;
        x->lChild = y->rChild;
        y->rChild = x;

        //update parent of x
        if (ploc == NULL)
            root = y;
        else if (ploc->rChild == x)
            ploc->rChild = y;
        else
            ploc->lChild = y;
    }

    void RightLeftRotate(AuthorAVLnode *x) {
        //first rotate right and then rotate left
        RightRotate(y);
        LeftRotate(x);
    }

    void LeftRightRotate(AuthorAVLnode *x) {
        //first rotate left and then rotate right
        LeftRotate(y);
        RightRotate(x);
    }

    void Balance() {
        x = NULL;
        y = NULL;
        FindImbalance(root);
        if (x != NULL && y != NULL) {

            if (balance_factor_x == -2 && balance_factor_y != 1) {
                LeftRotate(x);
            }
            if (balance_factor_x == 2 && balance_factor_y != -1) {
                RightRotate(x);
            }
            if (balance_factor_x == -2 && balance_factor_y == 1) {
                RightLeftRotate(x);
            }
            if (balance_factor_x == 2 && balance_factor_y == -1) {
                LeftRightRotate(x);
            }
        }
    }

public:
    /*
     *Recursive Case: To calculate the height of a node x, one needs to first calculate
     *the height of its left sub-tree and right-subtree.
     *The height of x is 1+Max(height of x�s left subtree, height of x�s right sub-tree).
     *Base Case: Height of an empty tree is -1.
    */
    int Height(AuthorAVLnode *node) {
        int height = -1;
        if (node != NULL)
            height = 1 + max(Height(node->lChild), Height(node->rChild));
        return height;
    }

public:
    void PreOrder(AuthorAVLnode *pTree) {
        //first print data then go to left child and
        //on returning go to right child
        if (pTree != NULL) {
            printf("\n____________________________________________________________________________________________________________\n");
            pTree->data->ToString();
            PreOrder(pTree->lChild);
            PreOrder(pTree->rChild);
        }
    }

    void InOrderYearWise(AuthorAVLnode *pTree) {
        //first print data then go to left child and
        //on returning go to right child
        if (pTree != NULL) {
            InOrderYearWise(pTree->lChild);
            cout << "------------------------------------------------" << endl;
            pTree->data->ToStringYearwise();
            InOrderYearWise(pTree->rChild);
            cout << "------------------------------------------------" << endl;
        }
    }

    void countingNodes(AuthorAVLnode *pTree) {
        //first print data then go to left child and
        //on returning go to right child
        if (pTree != NULL) {
            numAuthor++;
            countingNodes(pTree->lChild);
            countingNodes(pTree->rChild);
        }
    }

    //Searches a value in tree, if not found loc becomes NULL
    AuthorAVLnode *SearchAndReturnNode(string name) {
        loc = root;
        ploc = NULL;
        while (loc != NULL && loc->data->name != name) {
            if (name < loc->data->name) {
//equal not used since
//duplicate insertion is not allowed
                ploc = loc;
                loc = loc->lChild;
            } else {
                ploc = loc;
                loc = loc->rChild;
            }
        }
        return loc;
    }

};

class AuthorHash {
//    class for creating author hash table
public:
    unsigned int total = 0;
    static const unsigned int table_size = 163;
    AuthorAVLtree *author_table[table_size];

    AuthorHash() {
//        constructor
        for (int i = 0; i < table_size; i++) {
            author_table[i] = new AuthorAVLtree();
        }
    }

    static unsigned short int Hash(string key) {
        //Hash function
        int seed = 3;
        unsigned long hash = 0;
        for (int i = 0; i < key.length(); i++) {
            hash = (hash * seed) + key[i];
        }
        return hash % table_size; //SIZE is prime, bigger than total number of authors like 151
    }

    Author *AddAuthor(Author *author) {
        int index = Hash(author->name);
        //instead of  creating in constructor
        author->co_authors = new CoAuthorAVLtree();
        return author_table[index]->Insert(author);
    }

    int NumberOfItemsInIndex(int index) {
        return author_table[index]->nodes;
    }

    //if found return pointer to author
    Author *Search(string name) {
        int index = Hash(name);
        return author_table[index]->Search(name);
    }

    void ViewAuthor(string name) {
        int index = Hash(name);
        Author *author = author_table[index]->Search(name);
        cout << "Number of Publications: " << author->no_articles_written << endl;
        cout << "Publications:\n";
        author->articles_written->PreOrderTraversal(author->articles_written->root);
        
    }

    AuthorAVLnode *SearchAndReturnNode(string name) {
        int index = Hash(name);
        return author_table[index]->SearchAndReturnNode(name);
    }

    static void InsertEdge(Author *s, Author *d) {
        s->co_authors->Insert(d);
        d->co_authors->Insert(s);
        // weight handled inside co-authors tree
    }

    void CoAuthors(string name, unsigned short int hop) {
//        method for printing co-author
        int index = Hash(name);
        Author *a = author_table[index]->Search(name);
        if (a != NULL) {
            if (hop < 1)
                cout << "Negative or zero hop can not be made." << endl;
            else
                changeHop(hop, a);
        } else {
            cout << "Author Not in Database." << endl;
        }
    }

private:

    void changeHop(unsigned short int hop, Author *author) {
        if (hop == 1) {
            cout << author->name << endl;
            cout << "Direct co-authors: " << author->co_authors->nodes << endl;
            author->co_authors->PreOrder(author->co_authors->root);
            cout << endl;
        } else
            SameHopRecursion(hop - 1, author->co_authors->root);
    }

    void SameHopRecursion(unsigned short int hop, CoAuthorAVLnode *pTree) {
        if (pTree != NULL) {
            changeHop(hop, pTree->data);
            SameHopRecursion(hop, pTree->lChild);
            SameHopRecursion(hop, pTree->rChild);
        }
    }

public:
    void PrintAuthorJournalYearWise(string name) {
        //method 5
        Author *author = Search(name);
        author->articles_written_yearwise->InOrderTraversalYearWise(author->articles_written_yearwise->root);
    }

    void PrintAuthorCoAuthor(string name) {
        //method 3
        Author *author = Search(name);
        author->articles_written_yearwise->InOrderArticleCoAuthor(author->articles_written_yearwise->root);
    }

    void PrintTable() {
        for (int i = 0; i < table_size; i++) {

            if (author_table[i]->root != NULL) {
                author_table[i]->PreOrder(author_table[i]->root);
            }
            total = total + NumberOfItemsInIndex(i);
        }
    }

    void PrintTableYearWise() {
//        method for printing author articles yearwise
        for (int i = 0; i < table_size; i++) {
            cout << "____________________________________________________________" << endl;
            cout << "Index = " << i << "  ";
            cout << "Authors: " << NumberOfItemsInIndex(i) << endl;
            if (author_table[i]->root != NULL) {
                cout << "Root: ";
                author_table[i]->InOrderYearWise(author_table[i]->root);
            }
            total = total + NumberOfItemsInIndex(i);
            cout << "____________________________________________________________" << endl;
        }
        cout << "Total: " << total;
    }

private:
    void InitializeBFT(AuthorAVLnode *pTree) {
//Initializing in preOrder
        if (pTree != NULL) {
            pTree->color = "white";
            pTree->d = 9999;
            pTree->p = NULL;

            InitializeBFT(pTree->lChild);
            InitializeBFT(pTree->rChild);
        }
    }

    void
    TraverseAndUpdateBFT(AuthorAVLnode *u, CoAuthorAVLnode *pTree, CircularQueue<AuthorAVLnode *> *circular_queue,
                         unsigned short int distance) {
        if (pTree != NULL) {
//traverse all co authors
            AuthorAVLnode *v = SearchAndReturnNode(pTree->data->name);
//if not already discovered
            if (v->color == "white") {
                v->color = "gray";
                v->d = u->d + 1;
                v->p = u;
                if (v->d == distance) {
                    cout << v->data->name << "\n";
                }
                circular_queue->Enqueue(v);
            }
            TraverseAndUpdateBFT(u, pTree->lChild, circular_queue, distance);
            TraverseAndUpdateBFT(u, pTree->rChild, circular_queue, distance);
        }
    }

    void InitializeDFT(AuthorAVLnode *pTree) {
//Initializing in preOrder
        if (pTree != NULL) {
            pTree->color = "white";
            pTree->p = NULL;
            InitializeDFT(pTree->lChild);
            InitializeDFT(pTree->rChild);
        }
    }

    void ForAllu(AuthorAVLnode *pTree, unsigned short int time) {
        if (pTree != NULL) {
            if (pTree->color == "white") {
                DFTvisit(pTree, time);
                cout << endl << pTree->data->name << " d: " << pTree->d << " f: " << pTree->f << endl;
            }
            ForAllu(pTree->lChild, time);
            ForAllu(pTree->rChild, time);
        }
    }

    void DFTvisit(AuthorAVLnode *u, unsigned short int time) {
        u->color = "gray";
        time = time + 1;
        u->d = time;
        TraverseandUpdateDFT(u, u->data->co_authors->root, time);
        u->color = "black";
        time = time + 1;
        u->f = time;
    }

    void TraverseandUpdateDFT(AuthorAVLnode *u, CoAuthorAVLnode *pTree, unsigned short int time) {
        if (pTree != NULL) {
//traverse all co authors
            AuthorAVLnode *v = SearchAndReturnNode(pTree->data->name);
//if not already discovered
            if (v->color == "white") {
                v->p = u;
                DFTvisit(v, time);
                cout << endl << v->data->name << " d: " << v->d << " f: "
                     << v->f << endl;
            }
            TraverseandUpdateDFT(u, pTree->lChild, time);
            TraverseandUpdateDFT(u, pTree->rChild, time);
        }
    }

public:
//BREADTH FIRST TRAVERSAL
    void BFT(string name, unsigned short int distance) {
        AuthorAVLnode *s = SearchAndReturnNode(name);
        if (s == NULL) {
            cout << "Author not in database.\n";
            return;
        }
        cout << "Name: " << name;
        printf("\n____________________________________________________________________________________________________________\n\t\t\t\t\t");

        for (int i = 0; i < distance; ++i) {
            cout << "Co-Authors ";
        }
        printf("\n____________________________________________________________________________________________________________\n");

        //initializing
        for (int i = 0; i < table_size; i++) {
            if (author_table[i]->root != NULL) {
                InitializeBFT(author_table[i]->root);
            }
        }

        //make the start node gray and set its distance to 0.
//and its predecessor is NULL
        s->color = "gray";
        s->d = 0;

        //create queue and enqueue start vertex
        CircularQueue<AuthorAVLnode *> *circular_queue = new CircularQueue<AuthorAVLnode *>();
        circular_queue->Enqueue(s);
        AuthorAVLnode *u, *v;

        //pointer to traverse the AVL tree of nodes connected to u
        CoAuthorAVLnode *v_adjacent_temp;

        //loop till the queue becomes empty
        while (!circular_queue->IsEmpty()) {
//dequeue the traversed node
            u = circular_queue->Dequeue();
//update the nodes color and distance if white
            TraverseAndUpdateBFT(u, u->data->co_authors->root, circular_queue, distance);
            //u is now fully explored so set it black
            u->color = "black";
        }
        delete circular_queue;
    }

//DEPTH FIRST TRAVERSAL
    void DFT() {
        //initializing
        for (int i = 0; i < table_size; i++) {
            if (author_table[i]->root != NULL) {
                InitializeDFT(author_table[i]->root);
            }
        }
        unsigned short int time = 0;

        for (int i = 0; i < table_size; i++) {
            if (author_table[i]->root != NULL) {
                ForAllu(author_table[i]->root, time);
            }
        }
    }


};

AuthorHash *authorHash = new AuthorHash();

class ArticleNode {
//    class for creating article node
public:
    Article *article;
    ArticleNode *leftChild = NULL;
    ArticleNode *rightChild = NULL;

};

class ArticleTree {
//    class for creating article AVL tree
public:
    int nodes = 0;
    ArticleNode *loc = NULL;
    ArticleNode *ploc = NULL;
    ArticleNode *root;
    bool leftHeavy;
    int l;
    int r;

    int Height(ArticleNode *pointer) {//Function to traverse left and right subtree of node to find the height
        if (pointer == NULL) {
            return -1;
        } else {
            return (1 + max(Height(pointer->leftChild), Height(pointer->rightChild)));
        }
    }

    int balanceFactor(ArticleNode *node) {
        leftHeavy = false;
        if (node == NULL) {
            return -1;
        } else {
            l = Height(node->leftChild);
            r = Height(node->rightChild);

            if (l > r) {
                leftHeavy = true;
            }
            int b_factor = l - r;
            return b_factor;
        }
    }

    bool isEmpty() {//To check whether tree is empty or not
        return (root == NULL);
    }

    void Insertion(ArticleNode *nn) {//To insert values in tree
        //New node is created and assigned a value
        if (isEmpty()) {//If tree is empty new node is made as root
            root = nn;
            return;
        } else {
            //otherwise loc and ploc finds for the logical position and insert it
            ploc = NULL;
            loc = root;
            while (loc != NULL) {
                if (loc->article->Title[0] > nn->article->Title[0]) {
                    ploc = loc;
                    loc = loc->leftChild;
                } else {
                    ploc = loc;
                    loc = loc->rightChild;
                }
            }
            if (ploc->article->Title[0] >= nn->article->Title[0]) {
                ploc->leftChild = nn;
                if (!IsBalanced(root)) {

                    if (leftHeavy) {
                        balanceFactor(root->leftChild);
                        if (leftHeavy) {
                            RotateForLeft(root);
                        } else {

                            RotateForLeftRight(root);
                        }
                    } else {
                        balanceFactor(root->rightChild);
                        if (!leftHeavy) {
                            RotateForRight(root);
                        } else {
                            RotateForRightLeft(root);
                        }
                    }
                } else {}
            } else {
                ploc->rightChild = nn;
                if (!IsBalanced(root)) {
                    if (leftHeavy) {
                        balanceFactor(root->leftChild);
                        if (leftHeavy) {

                            RotateForLeft(root);
                        } else {
                            RotateForLeftRight(root);
                        }
                    } else {
                        balanceFactor(ploc->rightChild);
                        if (!leftHeavy) {
                            RotateForRight(root);
                        } else {

                            RotateForRightLeft(root);
                        }
                    }
                } else {}
            }
            nodes++;
        }
    }

    void SearchUnbalanced(ArticleNode *node) {
        ArticleNode *temp;
        if (loc == NULL) {
            return;
        }
        if (!IsBalanced(loc)) {
            if (leftHeavy) {
                balanceFactor(loc->leftChild);
                if (leftHeavy) {

                    RotateForLeft(loc);
                } else {
                    RotateForLeftRight(loc);
                }
            } else {
                balanceFactor(loc->leftChild);
                if (leftHeavy) {
                    RotateForRightLeft(loc);
                } else {
                    RotateForRight(loc);
                }
            }
            return;
        } else {
            PreOrderTraversal(loc->leftChild);
            PreOrderTraversal(loc->rightChild);
        }
    }

    void Search(string value) {  //To search for a value in tree
        //As a result loc and ploc will be updated
        ploc = NULL;
        loc = root;
        //seraches until value is found or tree ends
        while (loc != NULL && loc->article->Title != value) {//ploc points to the previous node of loc
            ploc = loc;
            if (loc->article->Title > value) {   //In BST,left side has small values and right side has larger
                loc = loc->leftChild;
            } else { loc = loc->rightChild; }
        }
    }

    bool IsBalanced(ArticleNode *root) {
        int b = balanceFactor(root);
        if (b == 0 || b == 1 || b == -1) {
            return true;
        } else { return false; }
    }

    void RotateForRight(ArticleNode *x) {
        ploc = NULL;
        loc = root;
        if (x != root) {
            Search(x->article->Title);
        }
        //Rotation start from here
        ArticleNode *y = x->rightChild;
        x->rightChild = y->leftChild;
        y->leftChild = x;
        if (x == root) {//If x is root,after rotation we make y as root
            root = y;
        } else {
            ploc->leftChild = y;
        }
    }

    void RotateForLeft(ArticleNode *x) {
        ploc = NULL;
        loc = root;
        if (x != root) {//To restore the connection with the previous node
            Search(x->article->Title);
        }
        //Rotation start from here
        ArticleNode *y = x->leftChild;
        x->leftChild = y->rightChild;
        y->rightChild = x;
        if (x == root) {//If x is root,after rotation we make y as root
            root = y;
        } else {
            ploc->rightChild = y;
        }
    }

    void RotateForRightLeft(ArticleNode *x) {
        ArticleNode *y = x->rightChild;
        RotateForLeft(x->rightChild);
        RotateForRight(x);
    }

    void RotateForLeftRight(ArticleNode *x) {
        RotateForRight(x->leftChild);
        RotateForLeft(x);
    }

    void PreOrderTraversal(
            ArticleNode *pointer) {   //In this function tree is traversed first its root than left and right subtree
        ArticleNode *temp;
        if (pointer != NULL) {
            cout
                    << "_____________________________________________________________________________________________________________________"
                    << endl << endl;
            cout << "Article Name " << pointer->article->Title << "\n";
            AuthorAVLnode *temp = pointer->article->List_of_Authors->root;
            pointer->article->List_of_Authors->PreOrder(temp);
            cout << endl;
            PreOrderTraversal(pointer->leftChild);
            PreOrderTraversal(pointer->rightChild);
        }
    }

    void PrintTree(ArticleNode *pointer) {
        PreOrderTraversal(pointer);
    }

};

class HashTable {
public:
    static void InsertInHash(ArticleTree *hs[], ArticleNode *node, int index) {
        //Tree* pointer;
        hs[index]->Insertion(node);
    }
};

class Controller {
public:
    //line variable ofr reading whole row at a time
    string line;
    //32 columns in row
    string array[32];

    void FileRead(ArticleTree *hash_Article[]) {
        //method to read file
        int index;
        ifstream file;
        file.open("updated.csv");

        getline(file, line);
        stringstream ss(line);
        for (int i = 0; i <= 31; i++) {
            //loop to read first row containing column name
            getline(ss, array[i], ',');
        }
        cout << endl;
        while (getline(file, line, '@')) {
            //loop to read each row and split it into the fields in which data is to be stored
            if (file.eof()) {
                break;
            }
            Article *a = new Article();
            ArticleNode *node = new ArticleNode();

            stringstream ss(line);
            string var;

            getline(ss, var, '{');
            getline(ss, array[0], '}');
            getline(ss, var, '{');
            //to split read row into 21 columns
            //for reading 1st 10 columns
            for (int i = 1; i <= 10; i++) {
                if (i == 8) {
                    getline(ss, array[i], '#');
                } else {
                    if (i == 9) {
                        getline(ss, var, '{');
                    }
                    getline(ss, array[i], '}');
                    if (i == 10) {
                        getline(ss, var, ',');
                    } else {
                        getline(ss, var, '{');
                    }
                }
            }
            //reading authors
            for (int i = 11; i <= 20; i++) {
                getline(ss, array[i], ',');
            }

            //reading author affiliation
            for (int i = 21; i < 31; ++i) {
                getline(ss, var, '"');
                getline(ss, array[i], '#');
                getline(ss, var, ',');

            }

            index = Article::HashFunction(array[6]);
            a->Title = array[0];
            a->year = stoi(array[2]);
            a->month = array[3];
            a->publisher = array[4];
            a->type = array[5];
            a->DOI = array[6];
            a->cited_references = array[8];
            a->no_of_citation = stoi(array[9]);
            a->List_of_Authors = new AuthorAVLtree();
            node->article = a;
            Author *author1 = new Author();
            Author *author2 = new Author();
            Author *author3 = new Author();
            Author *author4 = new Author();
            Author *author5 = new Author();
            Author *author6 = new Author();
            Author *author7 = new Author();
            Author *author8 = new Author();
            Author *author9 = new Author();
            Author *author10 = new Author();
            ArticleWrittenNode *articleWritten;
            for (int i = 11; i < 21; i++) {
                if (!array[i].empty()) {
                    if (i == 11) {
                        author1->name = array[i];
                        author1 = authorHash->AddAuthor(author1);
                        author1->affiliations = array[21];
                        articleWritten = author1->articles_written->Insertion(a, 1);
                        author1->no_articles_written = author1->articles_written->nodes;
                        a->List_of_Authors->Insert(author1);
                        author1->articles_written_yearwise->InsertionYearWise(a, 1);
                        YearPosAuthorNode *y = author1->yearAuthor->Insert(a->year);
                        y = author1->pos->Insert(articleWritten->position);

                    } else if (i == 12) {
                        author2->name = array[i];
                        author2 = authorHash->AddAuthor(author2);
                        author2->affiliations = array[22];
                        articleWritten = author2->articles_written->Insertion(a, 2);
                        author2->articles_written_yearwise->InsertionYearWise(a, 2);
                        author2->no_articles_written = author2->articles_written->nodes;
                        a->List_of_Authors->Insert(author2);
                        AuthorHash::InsertEdge(author1, author2);
                        YearPosAuthorNode *y = author2->yearAuthor->Insert(a->year);
                        y = author2->pos->Insert(articleWritten->position);

                    } else if (i == 13) {
                        author3->name = array[i];
                        author3 = authorHash->AddAuthor(author3);
                        author3->affiliations = array[23];
                        articleWritten = author3->articles_written->Insertion(a, 3);
                        author3->articles_written_yearwise->InsertionYearWise(a, 3);
                        author3->no_articles_written = author3->articles_written->nodes;
                        a->List_of_Authors->Insert(author3);
                        AuthorHash::InsertEdge(author3, author1);
                        AuthorHash::InsertEdge(author3, author2);
                        YearPosAuthorNode *y = author3->yearAuthor->Insert(a->year);
                        y = author3->pos->Insert(articleWritten->position);
                    } else if (i == 14) {
                        author4->name = array[i];
                        author4 = authorHash->AddAuthor(author4);
                        author4->affiliations = array[24];
                        articleWritten = author4->articles_written->Insertion(a, 4);
                        author4->articles_written_yearwise->InsertionYearWise(a, 4);
                        author4->no_articles_written = author4->articles_written->nodes;
                        a->List_of_Authors->Insert(author4);
                        AuthorHash::InsertEdge(author4, author1);
                        AuthorHash::InsertEdge(author4, author2);
                        AuthorHash::InsertEdge(author4, author3);
                        YearPosAuthorNode *y = author4->yearAuthor->Insert(a->year);
                        y = author4->pos->Insert(articleWritten->position);
                    } else if (i == 15) {
                        author5->name = array[i];
                        author5 = authorHash->AddAuthor(author5);
                        author5->affiliations = array[25];
                        articleWritten = author5->articles_written->Insertion(a, 5);
                        author5->articles_written_yearwise->InsertionYearWise(a, 5);
                        author5->no_articles_written = author5->articles_written->nodes;
                        a->List_of_Authors->Insert(author5);
                        AuthorHash::InsertEdge(author5, author1);
                        AuthorHash::InsertEdge(author5, author2);
                        AuthorHash::InsertEdge(author5, author3);
                        AuthorHash::InsertEdge(author5, author4);
                        YearPosAuthorNode *y = author5->yearAuthor->Insert(a->year);
                        y = author5->pos->Insert(articleWritten->position);
                    } else if (i == 16) {
                        author6->name = array[i];
                        author6 = authorHash->AddAuthor(author6);
                        author6->affiliations = array[26];
                        articleWritten = author6->articles_written->Insertion(a, 6);
                        author6->articles_written_yearwise->InsertionYearWise(a, 6);
                        author6->no_articles_written = author6->articles_written->nodes;
                        a->List_of_Authors->Insert(author6);
                        AuthorHash::InsertEdge(author6, author1);
                        AuthorHash::InsertEdge(author6, author2);
                        AuthorHash::InsertEdge(author6, author3);
                        AuthorHash::InsertEdge(author6, author4);
                        AuthorHash::InsertEdge(author6, author5);
                        YearPosAuthorNode *y = author6->yearAuthor->Insert(a->year);
                        y = author6->pos->Insert(articleWritten->position);
                    } else if (i == 17) {
                        author7->name = array[i];
                        author7 = authorHash->AddAuthor(author7);
                        author7->affiliations = array[27];
                        articleWritten = author7->articles_written->Insertion(a, 7);
                        author7->articles_written_yearwise->InsertionYearWise(a, 7);
                        author7->no_articles_written = author7->articles_written->nodes;
                        a->List_of_Authors->Insert(author7);
                        AuthorHash::InsertEdge(author7, author1);
                        AuthorHash::InsertEdge(author7, author2);
                        AuthorHash::InsertEdge(author7, author3);
                        AuthorHash::InsertEdge(author7, author4);
                        AuthorHash::InsertEdge(author7, author5);
                        AuthorHash::InsertEdge(author7, author6);
                        YearPosAuthorNode *y = author7->yearAuthor->Insert(a->year);
                        y = author7->pos->Insert(articleWritten->position);
                    } else if (i == 18) {
                        author8->name = array[i];
                        author8 = authorHash->AddAuthor(author8);
                        author8->affiliations = array[28];
                        articleWritten = author8->articles_written->Insertion(a, 8);
                        author8->articles_written_yearwise->InsertionYearWise(a, 8);
                        author8->no_articles_written = author8->articles_written->nodes;
                        a->List_of_Authors->Insert(author8);
                        AuthorHash::InsertEdge(author8, author1);
                        AuthorHash::InsertEdge(author8, author2);
                        AuthorHash::InsertEdge(author8, author3);
                        AuthorHash::InsertEdge(author8, author4);
                        AuthorHash::InsertEdge(author8, author5);
                        AuthorHash::InsertEdge(author8, author6);
                        AuthorHash::InsertEdge(author8, author7);
                        YearPosAuthorNode *y = author8->yearAuthor->Insert(a->year);
                        y = author8->pos->Insert(articleWritten->position);
                    } else if (i == 19) {
                        author9->name = array[i];
                        author9 = authorHash->AddAuthor(author9);
                        author9->affiliations = array[29];
                        articleWritten = author9->articles_written->Insertion(a, 9);
                        author9->articles_written_yearwise->InsertionYearWise(a, 9);
                        author9->no_articles_written = author9->articles_written->nodes;
                        a->List_of_Authors->Insert(author9);
                        AuthorHash::InsertEdge(author9, author1);
                        AuthorHash::InsertEdge(author9, author2);
                        AuthorHash::InsertEdge(author9, author3);
                        AuthorHash::InsertEdge(author9, author4);
                        AuthorHash::InsertEdge(author9, author5);
                        AuthorHash::InsertEdge(author9, author6);
                        AuthorHash::InsertEdge(author9, author7);
                        AuthorHash::InsertEdge(author9, author8);
                        YearPosAuthorNode *y = author9->yearAuthor->Insert(a->year);
                        y = author9->pos->Insert(articleWritten->position);
                    } else {
                        author10->name = array[i];
                        author10 = authorHash->AddAuthor(author10);
                        author10->affiliations = array[30];
                        articleWritten = author10->articles_written->Insertion(a, 10);
                        author10->articles_written_yearwise->InsertionYearWise(a, 10);
                        author10->no_articles_written = author10->articles_written->nodes;
                        a->List_of_Authors->Insert(author10);
                        AuthorHash::InsertEdge(author10, author1);
                        AuthorHash::InsertEdge(author10, author2);
                        AuthorHash::InsertEdge(author10, author3);
                        AuthorHash::InsertEdge(author10, author4);
                        AuthorHash::InsertEdge(author10, author5);
                        AuthorHash::InsertEdge(author10, author6);
                        AuthorHash::InsertEdge(author10, author7);
                        AuthorHash::InsertEdge(author10, author8);
                        AuthorHash::InsertEdge(author10, author9);
                        YearPosAuthorNode *y = author10->yearAuthor->Insert(a->year);
                        y = author10->pos->Insert(articleWritten->position);
                    }

                }
            }

            AuthorAVLtree *authorAvlTree = new AuthorAVLtree();
            authorAvlTree->countingNodes(a->List_of_Authors->root);
            a->numberOfAuthors = authorAvlTree->numAuthor;

            HashTable *hash = new HashTable();

            HashTable::InsertInHash(hash_Article, node, index);
            JournalInfo *journalInfo = new JournalInfo();
            journalInfo->journalIso = array[10];
            journalInfo->issn = array[7];
            journalInfo->name = array[1];
            journalInfo = hashJournal->InsertJournalInfo(journalInfo);
            a->journal = journalInfo;

        }

    }

};

int Menu() {
    printf("\n____________________________________________________________________________________________________________\n");
    printf("\t\t\t\t Main Menu");
    printf("\n____________________________________________________________________________________________________________\n");
    printf("\n");
    printf("\t 1 - Calculate the total number of articles published by an author.\n");
    printf("\t 2 - Calculates the number of publications of an author per year.\n");
    printf("\t 3 - Calculates the number of co-authors of an author x per publication sorted timewise.\n");
    printf("\t 4 - Counts the numbers of papers published by an author x for each author position\n");
    printf("\t 5 - Sorted timewise,prints the name of the journal in which an author x has published his research work\n");
    printf("\t 6 - Enter the name of author x and distance d to find all authors at distance d from x using recursion\n");
    printf("\t 7 - Enter the name of author x and distance d to find all authors at distance d from x using BFT\n");
    printf("\t 8 - Show All Article Details\n");
    printf("\t 9 - Show All Journal Details\n");
    printf("\t 10 - Show All Author Details\n");
    printf("\t 11 - Authorship graph Depth First Traversal\n");
    printf("\t 12 - View Author Record\n");
    printf("\t 0 - Exit\n");
    printf("\n____________________________________________________________________________________________________________\n");
    printf("\t\t\t Enter Your Choice: ");
    int choice;
    cin >> choice;
    printf("\n____________________________________________________________________________________________________________\n");
    return choice;
}


int main() {
    Controller *controller = new Controller();
    ArticleTree *article[50];
    AuthorAVLtree *at = new AuthorAVLtree();
    for (int i = 0; i < 50; i++) {
        article[i] = new ArticleTree();

    }
    controller->FileRead(article);

    while (true) {
        int choice = Menu();//
        string name1;
        Author *a;
        unsigned short int d;

        switch (choice) {
            case 0:
                break;
            case 1:
                cout << "Enter Author name: ";
                std::getline(std::cin >> std::ws, name1);
                a = authorHash->Search(name1);
                cout << "Total Articles of " << name1 << " are : " << a->no_articles_written << endl;
                break;
            case 2:
                cout << "Enter Author name: ";
                std::getline(std::cin >> std::ws, name1);
                cout << endl;
                a = authorHash->Search(name1);
                cout << "      Year   No of Articles " << endl;
                a->yearAuthor->PreOrder(a->yearAuthor->root);
                break;
            case 3:
                cout << "Enter Author name: ";
                std::getline(std::cin >> std::ws, name1);
                cout << endl;
                authorHash->PrintAuthorCoAuthor(name1);
                break;
            case 4:
                cout << "Enter Author name: ";
                std::getline(std::cin >> std::ws, name1);
                cout << endl;
                a = authorHash->Search(name1);
                cout << "   Position  No of Articles " << endl;
                if (a == NULL) {
                    cout << "good to go";
                    cout << endl;
                    break;
                }
                a->pos->PreOrder(a->pos->root);
                break;
            case 5:
                cout << "Enter Author name: ";
                std::getline(std::cin >> std::ws, name1);
                cout << endl;
                authorHash->PrintAuthorJournalYearWise(name1);
                break;
            case 6:
                cout << "Enter Author name: ";
                std::getline(std::cin >> std::ws, name1);
                cout << "Enter d: ";
                cin >> d;
                cout << endl << endl;
                authorHash->CoAuthors(name1, d);
                break;
            case 7:
                cout << "Enter Author name: ";
                std::getline(std::cin >> std::ws, name1);
                cout << "Enter d: ";
                cin >> d;
                cout << endl << endl;
                authorHash->BFT(name1, d);
                break;
            case 8:

                for (int i = 0; i < 50; i++) {
                    article[i]->PrintTree(article[i]->root);
                }
                break;
            case 9:
                hashJournal->PrintTable();
                break;
            case 10:
                authorHash->PrintTable();
                break;
            case 11:
                authorHash->DFT();
                break;
            case 12:
                cout << "Enter Author name: ";
                std::getline(std::cin >> std::ws, name1);
                authorHash->ViewAuthor(name1);
                break;

            default:
                printf("\t\t\t Invalid Choice");
                break;
        }
        if (choice != 0)continue;
        else
            break;
    };


}







