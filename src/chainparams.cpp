// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"
#include "base58.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//
// Main network
//
class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xa2;
        pchMessageStart[2] = 0xa3;
        pchMessageStart[3] = 0xa4;
        vAlertPubKey = ParseHex("04c244288a8c6ebbf491443eba15207275d71cb009f201c118b01569877641cacd4987165ba909842c009af3456985c1c7368e8d7e2066168c40ce3cb629cf212f");
        nDefaultPort = 40506;
        nRPCPort = 39495;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 18);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 18);

        const char* pszTimestamp = "What Is Proof-of-Weight? | By JP Buntinx | July 12, 2017"; // Sunday, August 12, 2018 6:00:00 AM;
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].nValue = nGenesisBlockReward;
        vout[0].SetEmpty();
        CTransaction txNew(1, 1534053600, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = timeGenesisBlock;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   =  28166;

        /** Genesis Block MainNet
        Hashed MainNet Genesis Block Output
        block.hashMerkleRoot == 6e10960f60a9c1de72cf0c0458ced859810e1fa3e192314fbff39b3ec3eae766
        block.nTime = 1534053600
        block.nNonce = 28166
        block.GetHash = 000022a321fb5d4cdd4b60e77e1f6c0ae00d6d129d730eabad706bdc763d04b2
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000022a321fb5d4cdd4b60e77e1f6c0ae00d6d129d730eabad706bdc763d04b2"));
        assert(genesis.hashMerkleRoot == uint256("0x6e10960f60a9c1de72cf0c0458ced859810e1fa3e192314fbff39b3ec3eae766"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,33); //All PubKey Addresses Begin With 'E'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,53); //All ScriptAddresses Begin With 'N'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,30); //All SecretKeys Begin With 'D'
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,115); //All StealthAddresses Begin With 'o'
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

       // vSeeds.push_back(CDNSSeedData("someLabel",  "someIP"));
       // vSeeds.push_back(CDNSSeedData("someLabel",  "someIP"));
       // vSeeds.push_back(CDNSSeedData("someLabel",  "someIP"));
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nPoolMaxTransactions = 3;
        strDarksendPoolDummyAddress = "RmTXZQ9W92y13UkyEoxcEsbjA6oZeQUFZu";
        nEndPoWBlock = 0x7fffffff;
        nStartPoSBlock = 0;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xb2;
        pchMessageStart[1] = 0xb3;
        pchMessageStart[2] = 0xb4;
        pchMessageStart[3] = 0xb5;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04ac24ab003c828cdd9cf4db2ebbde8e1cecb3bbf16589abc459dd9b84d44112080827ed7c49a648165ab788ff42e316aee665879c553f099e55299d6b54edd7e0");
        nDefaultPort = 20029;
        nRPCPort = 20189;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime    = timeTestNetGenesis;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 13620;

        /** Genesis Block TestNet */
        /*
        Hashed TestNet Genesis Block Output
        block.hashMerkleRoot == 6e10960f60a9c1de72cf0c0458ced859810e1fa3e192314fbff39b3ec3eae766
        block.nTime = 1534053630
        block.nNonce = 13620
        block.GetHash = 000041b06dfdd85df95db099f7335f8d2ac8ae2608aa18b656b798bca560b92a
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000041b06dfdd85df95db099f7335f8d2ac8ae2608aa18b656b798bca560b92a"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,92);  //All PubKey Addresses Begin With 'e'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,112); //All ScriptAddresses Begin With 'n'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,90);  //All SecretKeys Begin With 'd'
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,142); //All StealthAddresses Begin With 'z'
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        nEndPoWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;

//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xc1;
        pchMessageStart[1] = 0xc2;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0xc4;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = timeRegNetGenesis;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = nNonceReg;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 19429;
        strDataDir = "regtest";

        /** Genesis Block TestNet */
        /*
        Hashed RegNet Genesis Block Output
        block.hashMerkleRoot == 6e10960f60a9c1de72cf0c0458ced859810e1fa3e192314fbff39b3ec3eae766
        block.nTime = 1534053690
        block.nNonce = 8
        block.GetHash = 04edbc333d0ee11f96436dca976413e992747fb0b42920200463a301a729292b

        */

        assert(hashGenesisBlock == uint256("0x04edbc333d0ee11f96436dca976413e992747fb0b42920200463a301a729292b"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
