// Copyright (c) 2016-2018 The CryptoCoderz Team / Espers
// Copyright (c) 2018 The CryptoCoderz Team / INSaNe project
// Copyright (c) 2018 The Endo project
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef BITCOIN_MINING_H
#define BITCOIN_MINING_H

#include "bignum.h"
#include "fork.h"

/** Minimum nCoinAge required to stake PoS */
static const unsigned int nStakeMinAge = 2 / 60; // 30 minutes
/** Time to elapse before new modifier is computed */
static const unsigned int nModifierInterval = 2 * 60;
/** Genesis block subsidy */
static const int64_t nGenesisBlockReward = 1 * COIN;
/** Reserve block subsidy */
static const int64_t nBlockRewardReserve = 14000000 * COIN; // 10% reserved for development
/** Starting block subsidy */
static const int64_t nBlockPoWReward = 30 * COIN;
/** PoW Superblock modifier */
static const int64_t nSuperModifier = 2;
/** PoS Reward */
static const int64_t COIN_YEAR_REWARD = 8.2 * CENT; // Corrected in v2.0.0.0+
/** PoS Superblock Reward */
static const int64_t COIN_SPRB_REWARD = 12 * CENT; // Corrected in v2.0.0.0+
/** Block spacing preferred */
static const int64_t BLOCK_SPACING = 2 * 60; // 2 minutes and 0 seconds
/** Block spacing minimum */
static const int64_t BLOCK_SPACING_MIN = 4 * 60; // 4 minutes and 0 seconds
/** Block spacing maximum */
static const int64_t BLOCK_SPACING_MAX = 8 * 60; // 8 minutes and 0 seconds
/** Desired block times/spacing */
static const int64_t GetTargetSpacing = BLOCK_SPACING;
/** Darksend collateral */
static const int64_t DARKSEND_COLLATERAL = (0.01*COIN);
/** Darksend pool values */
static const int64_t DARKSEND_POOL_MAX = (4999.99*COIN);
/** MasterNode required collateral (Legacy) */
inline int64_t MasternodeCollateral_v1(int nHeight) { return 50000250; } // 50.00025M ENDO required as collateral
/** MasterNode required collateral (Current) */
inline int64_t MasternodeCollateral_v2(int nHeight) { return 43200; } // 43200 Million ENDO required as collateral
/** MasterNode required collateral (Toggle) */
inline int64_t MasternodeCollateral(int nHeight, int nProtocolTime) { return IsProtocolV3_1(nProtocolTime) ? MasternodeCollateral_v2(nHeight) : MasternodeCollateral_v1(nHeight); }
/** Coinbase transaction outputs can only be staked after this number of new blocks (network rule) */
static const int nStakeMinConfirmations = 12;
/** Coinbase transaction outputs can only be spent after this number of new blocks (network rule) */
static const int nCoinbaseMaturity = 15; // 15-TXs | 90-Mined

#endif // BITCOIN_MINING_H
