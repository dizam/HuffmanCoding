#ifndef HUFFNODE_H
#define HUFFNODE_H

class HuffNode{
 public:
  HuffNode(int f, char l, bool le, HuffNode *left, HuffNode *right)
    {
      frequency = f;
      letter = l;
      leaf = le;
      bitcode = 0;
      leftChild = left;
      rightChild = right;
    }
  unsigned int getFreq() const;
  unsigned char getChar();
  HuffNode* getLeft();
  HuffNode* getRight();
  HuffNode* buildTree(unsigned int* frequency);
  void printTree();
  void setBit(unsigned int b);
  void setDepth(unsigned int d);
  unsigned int getBit();
  unsigned int getDepth();
  bool isLeaf();
  void setMessage(HuffNode *root, HuffNode** freqTable, unsigned int bitstring, unsigned int depth);
  void writeMessage(int startPos, HuffNode** freqTable, const unsigned char* message, const int size, unsigned char* EncodedMessage, int* encodedSize);  
  int writeTree(unsigned int* frequency, unsigned char* encodedMessage);
 private:
  int frequency;
  char letter;
  bool leaf;
  unsigned int bitcode;
  unsigned int depth;
  HuffNode *leftChild;
  HuffNode *rightChild;
};

#endif

        #ifndef _BINARY_HEAP_H_
        #define _BINARY_HEAP_H_

        #include "dsexceptions.h"
        #include "vector.h"        


        // BinaryHeap class
        //
        // CONSTRUCTION: with a negative infinity sentinel and
        //               optional capacity (that defaults to 100)
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // deleteMin( minItem )   --> Remove (and optionally return) smallest item
        // Comparable findMin( )  --> Return smallest item
        // bool isEmpty( )        --> Return true if empty; else false
        // bool isFull( )         --> Return true if full; else false
        // void makeEmpty( )      --> Remove all items
        // ******************ERRORS********************************
        // Throws Underflow and Overflow as warranted

        class BinaryHeap
        {
          public:
            explicit BinaryHeap( int capacity = 100 );

            bool isEmpty( ) const;
            bool isFull( ) const;
            HuffNode * findMin( );

            void insert(HuffNode *x);
            void deleteMin( );
            void deleteMin(HuffNode *x);
            void makeEmpty( );

          private:
            int                currentSize;  // Number of elements in heap
            vector<HuffNode *> array;        // The heap array

            void buildHeap( );
            void percolateDown( int hole );
        };
        #endif
