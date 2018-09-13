// Author: Sean Davis
#include "BinaryHeap.h"
#ifndef DECODER_H
#define	DECODER_H


class Decoder
{
public:
  Decoder();
  ~Decoder();
  void decode(const unsigned char* encodedMessage, const int encodedSize, 
    unsigned char* decodedMessage, int *decodedSize);
  int buildFrequency(unsigned int* frequency, const unsigned char* encodedMessage);
  void printMessage(const unsigned char* encodedMessage, const int encodedSize, unsigned int startPos, HuffNode *root, unsigned char* decodedMessage, int* decodedSize);
private:

};

#endif	/* DECODER_H */

