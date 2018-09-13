
//  Author: Sean Davis

#include "BinaryHeap.h"
#include "QueueAr.h"
#include "encoder.h"
#include <iostream>

using namespace std;

Encoder::Encoder()
{
} // Encoder()


Encoder::~Encoder()
{
} // ~Encoder()

void Encoder::encode(const unsigned char *message, const int size, 
  unsigned char *encodedMessage, 
    int *encodedSize)
{
  unsigned int bitstring = 0, depth = 0;
  unsigned  int startPos = 0;
  unsigned int frequency[512] = {0};
  getFrequency(message, size, frequency);
  HuffNode *tree = new HuffNode (0, 't', false, NULL, NULL);
  tree = tree->buildTree(frequency);
  HuffNode **table = new HuffNode *[256];
  //tree->printTree();
   tree->setMessage(tree, table, bitstring, depth);
   startPos = tree->writeTree(frequency, encodedMessage);
   tree->writeMessage(startPos, table, message, size, encodedMessage, encodedSize);
  delete tree;
  delete [] table;
}  // encode()

int HuffNode::writeTree(unsigned int* frequency, unsigned char* encodedMessage)
{
  unsigned int pos = 0;
  for (int i = 0; i < 256; i++)
  {
    unsigned int freq = frequency[i];
    //    cout << frequency[i] << "        " << i << "\n";
    unsigned int copy = freq;
    unsigned int copy2 = freq;
    unsigned int power = 1;
    unsigned int digit = 0;
    unsigned char put = 0;
    while (copy/power > 1)
    {
      power *= 10;
    }
    //    if (i == 32)
    // cout << power;
    /*
    if (power > 10)
      {
    power/=10;
    }*/
    while (power > 0)
    {
      digit = copy2/power;
      while (digit >= 10)
	{
        
        digit %= 10;
	}


      put = (unsigned char)(digit + 48);
      encodedMessage[pos++] = put;
      power/=10;
    }
    encodedMessage[pos++] = 'S';
  }
  return pos;
}

unsigned int HuffNode::getBit()
{
  return bitcode;
}

unsigned int HuffNode::getDepth()
{
  return depth;
}

void HuffNode::writeMessage(int startPos, HuffNode** bitkey, const unsigned char* message, const int size, unsigned char* encodedMessage, int* encodedSize)
{
  unsigned int count = 0;
  unsigned int pos = startPos;
  for (int i = 0; i < size; i++)
  {
    HuffNode *current = bitkey[message[i]];
    unsigned int code = current->getBit();
    unsigned int depth = current->getDepth();
    //cout << depth << "\n";
    // cout << depth << "\n";
    //cout.flush();
    unsigned int endPos = (depth + count)/8;
    unsigned int rightSide = (depth+count)%8;
    if (depth + count == 8)
    {
      endPos--;
    }
    
    if (endPos >= 1)
    {
      if (rightSide == 0)
	{
        rightSide = 8;
        endPos--;
	}
      unsigned int temp = endPos;
      encodedMessage[pos + endPos] |= code >> (24-depth + rightSide);
      endPos--;
      unsigned int charCount = 1;
      while (endPos > 0)
      {
        encodedMessage[pos + endPos] |= code >> (24 - depth + rightSide + 8 * charCount);
        endPos--;
        charCount++;
      }
      encodedMessage[pos] |= code >> (count + 24);
      count = rightSide;
      pos += temp;
    }
    else

      {
    encodedMessage[pos] |= code >> (count + 24);
    count += depth;
      }
  }
  *encodedSize = pos + 1;
}

void HuffNode::setBit(unsigned int b)
{
  bitcode = b;
}

void HuffNode::setDepth(unsigned int d)
{
  depth = d;
}

void HuffNode::setMessage(HuffNode* root, HuffNode** bitkey, unsigned int bitstring, unsigned int depth)
{
  if (root->isLeaf())
    {
      root->setBit(bitstring);
      root->setDepth(depth);
      bitkey[root->getChar()] = root;
    }
  else
  {
    depth++;
    if (root->getLeft())
    {
      setMessage(root->getLeft(), bitkey, bitstring, depth);
    }
    if (root->getRight())
    {
      bitstring |= 0x80000000 >> (depth-1);
      setMessage(root->getRight(), bitkey, bitstring, depth);
    }
  }
}

bool HuffNode::isLeaf()
{
  return leaf;
}

void Encoder::getFrequency(const unsigned char *message, const int size, unsigned int* frequency)
{
  for (int i = 0; i < size; i++)
    {
      unsigned int code = (unsigned int)message[i];
      frequency[code]++;
    }
}

HuffNode* HuffNode::buildTree(unsigned int* frequency)
{
  BinaryHeap priority (511);
  unsigned  int count = 0;
  for (unsigned int i = 0; i < 256; i++)
    {
            while (frequency[i] == 0)
        {
      	i++;
	}
      if (i >= 256)
      {
      	break;
	}
      count++;
      HuffNode *element = new HuffNode(frequency[i], (unsigned char)i, true, NULL, NULL);
      priority.insert(element);
    }
  for (unsigned int i = 0; i < count - 1; i ++)
  {
  HuffNode *bLeft = priority.findMin();
  priority.deleteMin();
  HuffNode *bRight = priority.findMin();
  priority.deleteMin();
  HuffNode *root = new HuffNode(bLeft->getFreq() + bRight->getFreq(), 't', false, bLeft, bRight);
  priority.insert(root);
  }
  return priority.findMin();
}

unsigned int HuffNode::getFreq() const
{
  return frequency;
}

unsigned char HuffNode::getChar()
{
  return letter;
}

HuffNode* HuffNode::getLeft()
{
  return leftChild;
}
HuffNode* HuffNode::getRight()
{
  return rightChild;
}

void HuffNode::printTree()
{
  Queue <HuffNode*> test (256);
  test.enqueue(this);
  while (!test.isEmpty())
    {
      HuffNode *ptr = test.dequeue();
      cout << ptr->getChar() << ptr->getFreq() << "\n";
      if (ptr->getLeft())
      {
        test.enqueue(ptr->getLeft());
      }
      if (ptr->getRight())
	{
	  test.enqueue(ptr->getRight());
	}
    }
}
