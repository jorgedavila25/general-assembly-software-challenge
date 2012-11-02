#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream> 
#include <string>
using namespace std;

class AvlTree
{
public:
    AvlTree( ) : root( NULL )
    {  largest = NULL; }
    AvlTree( const AvlTree & rhs ) : root( NULL )
    {
        largest = NULL;
        *this = rhs;
    }
    
    ~AvlTree( )
    {
        makeEmpty( );
    }
    
    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == NULL;
    }
    
    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }
    
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( string & x )
    {
        insert( x, root );
    }
    string getLargestElement(){ return largest->element; };
    int getLargest(){ return largest->numberOfTimes; };
    
private:
    struct AvlNode // the Struct of the AVL Node
    {
        string element;
        AvlNode *left;
        AvlNode *right;
        int height;
        int numberOfTimes;
        
        AvlNode( string & theElement,AvlNode *lt, AvlNode *rt, int h = 0, int num = 1){
            element = theElement;
            left = lt;
            right = rt;
            height = h;
            numberOfTimes = num;
        };
    };;
    AvlNode *root;
    AvlNode *largest;
    
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( string & x, AvlNode * & t )
    {
        if( t == NULL )
            t = new AvlNode( x, NULL, NULL );
        else if( x < t->element )
        {
            insert( x, t->left);
            if( height( t->left ) - height( t->right ) == 2 )
                if( x < t->left->element )
                    rotateWithLeftChild( t );
                else
                    doubleWithLeftChild( t );
        }
        else if( t->element < x )
        {
            insert( x, t->right );
            if( height( t->right ) - height( t->left ) == 2 )
                if( t->right->element < x )
                    rotateWithRightChild( t );
                else
                    doubleWithRightChild( t );
        }
        else if (t->element == x){
            t->numberOfTimes = t->numberOfTimes + 1; 
            if(largest == NULL){
                largest = t;
            }else if (largest->numberOfTimes < t->numberOfTimes){
                largest = t;
            }
        
        }// Duplicate, update counter, check if current pointer value is larger or not
        
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }
    /*
     *  Internal method to make subtree empty
     */
     void makeEmpty( AvlNode * &t )
     {
        if( t!= NULL)
        {
            makeEmpty( t-> left );
            makeEmpty( t-> right);
            delete t;
        }
        t = NULL;
     }
    
    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const string & x, AvlNode *t ) const
    {
        if( t == NULL )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
    
    // Avl manipulations
    /**
     * Return the height of node t or -1 if NULL.
     */
    int height( AvlNode *t ) const
    {
        return t == NULL ? -1 : t->height;
    }
    
    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }
    
    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }
    
    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }
    
    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }
    
    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }
};

#endif
