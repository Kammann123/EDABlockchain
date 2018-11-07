#include "BlockchainContext.h"
#include "../blockchain/cryptoeda.h"

#include <time.h>
#include <iostream>

/* Establecen valores por defecto del BlockchainContext */
unsigned int BlockchainContext::challenge = DEFAULT_CHALLENGE;
double BlockchainContext::minerFee = DEFAULT_FEE;
double BlockchainContext::satoshi = DEFAULT_SATOSHI;

unsigned int BlockchainContext::
getChallenge(void) {

	return BlockchainContext::challenge;
}

double BlockchainContext::
getMinerFee(void) {

	return BlockchainContext::minerFee;
}

void BlockchainContext::
generateFee(void) {

	BlockchainContext::minerFee /= 2;
}

double BlockchainContext::
getSatoshi(void) {

	return BlockchainContext::satoshi;
}

void BlockchainContext::
generateChallenge(void) {
}

bool BlockchainContext::
validatePOW(string hash) {

	unsigned int counter = getChallenge();
	unsigned int mask;

	for (unsigned char c : hash) {

		if (c >= '0' && c <= '9') {
			c -= '0';
		}
		else {
			c = c - 'A' + 10;
		}

		mask = 0x40;
		while (mask) {

			if (c & mask) {

				return false;
			}
			else {
				counter--;
				if (!counter) {

					return true;
				}
			}
			mask /= 2;
		}
	}

	return false;
}