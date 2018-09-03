// Copyright (c) 2016-2018 The CryptoCoderz Team / Espers
// Copyright (c) 2018 The CryptoCoderz Team / INSaNe project
// Copyright (c) 2018 The Endo project
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef BITCOIN_GENESIS_H
#define BITCOIN_GENESIS_H

#include "bignum.h"

/** Genesis Start Time */
static const unsigned int timeGenesisBlock = 1534053600; // Wednesday, July 12, 2017 8:00:00 PM
/** Genesis TestNet Start Time */
static const unsigned int timeTestNetGenesis = 1534053600+30; // Wednesday, July 12, 2017 8:00:00 PM
/** Genesis RegNet Start Time */
static const unsigned int timeRegNetGenesis = 1534053600+90; // Wednesday, July 12, 2017 8:00:00 PM
/** Genesis Nonce Mainnet*/
static const unsigned int nNonceMain = 0;
/** Genesis Nonce Testnet */
static const unsigned int nNonceTest = 0;
/** Genesis Nonce Regnet */
static const unsigned int nNonceReg = 8;
/** Main Net Genesis Block */
static const uint256 nGenesisBlock("0x");
/** Test Net Genesis Block */
static const uint256 hashTestNetGenesisBlock("0x");
/** Reg Net Genesis Block */
static const uint256 hashRegNetGenesisBlock("0x");
/** Genesis Merkleroot */
static const uint256 nGenesisMerkle("0x");

#endif // BITCOIN_GENESIS_H
