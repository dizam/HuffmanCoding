// Author: Sean Davis

#include "BinaryHeap.h"

#ifndef ENCODER_H
#define	ENCODER_H


class Encoder
{
public:
  Encoder();
  void encode(const unsigned char *message, const int size, 
    unsigned char *encodedMessage, int *encodedSize);
  ~Encoder();
  void getFrequency(const unsigned char *message, const int size, unsigned int* frequency);
private:

};

#endif	/* ENCODER_H */

