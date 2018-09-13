//  Author: Sean Davis

#include "decoder.h"
#include <iostream>
using namespace std;
#include "BinaryHeap.h"

Decoder::Decoder()
{
} // Decoder()


Decoder::~Decoder()
{
} // ~Decoder()


void Decoder::decode(const unsigned char* encodedMessage, const int encodedSize, 
  unsigned char* decodedMessage, int *decodedSize)
{
  unsigned int frequency[256] = {0};
  unsigned int startpos = 0;
  startpos = buildFrequency(frequency, encodedMessage);
  HuffNode *tree = new HuffNode (0, 't', false, NULL, NULL);
  tree = tree->buildTree(frequency);
  //tree->printTree();
  printMessage(encodedMessage, encodedSize, startpos, tree, decodedMessage, decodedSize);
  delete tree;
} // decode()

int Decoder::buildFrequency(unsigned int* frequency, const unsigned char* encodedMessage)
{
  unsigned int pos = 0, pos2 = 0;
  for (unsigned int i = 0; i < 256; i++)
  {
    //    cout << encodedMessage[i] << "             " << i << "\n";
    pos2 = pos;
    unsigned int freq = 0;
    unsigned int power = 1;
    while (encodedMessage[pos] != 'S')
    {
      power *= 10;
      pos++;
    }
    if (power >= 10)
      {
      power /= 10;
      }
    while (encodedMessage[pos2] != 'S')
    {
      freq += (encodedMessage[pos2] - 48) * power;
      power/=10;
      pos2++;
    }
    pos++;
    frequency[i] = freq;
    //    cout << frequency[i] << "           " << i << "\n";
    }
  return pos;
}

void Decoder::printMessage(const unsigned char* encodedMessage, const int encodedSize, unsigned int startPos, HuffNode *root, unsigned char* decodedMessage, int* decodedSize)
{
  HuffNode *top = root;
  int i = 0;
  for (int pos = startPos; pos < encodedSize; pos++)
  {
    for (unsigned int j = 0x80; j > 0; j>>=1)
      {
      if (encodedMessage[pos] & j)
	{
	// cout << '1';
    root = root->getRight();
	}
      else
	{
        //cout << '0';
    root = root->getLeft();
	}
      if (root->isLeaf())
      {
        decodedMessage[i++] = root->getChar();
	//	      cout << root->getChar();
        root = top;
      }
      }
  }
  *decodedSize = i;
} 
