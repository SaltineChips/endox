// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 5000;

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (0,      Params().HashGenesisBlock() )
        (1,      uint256("0x0000f2e7e23fd8baed5d3e382f9010d32a1c520ae8104edb118d5ff17dbe7948"))
        (2,      uint256("0x0000950298d9a913453d7cb9d5a94775fcce708f38ebfbc601278f9ab3c3e403"))
        (125,    uint256("0x57661469222c39e3b58f748e3904fa99cd055f6384644d02e3a68cabc88aae0f"))
        (170,    uint256("0x00000091418b8116d4242c6efe962ce221dbade181187b94ea4f3363e6ee34b3"))
        (290,    uint256("0x0000001ff299f243fde3ae2ede4ee09907076b12ac59abeab39fb744edc50bbe"))
        (370,    uint256("0x0000000ecb5fc73f62f411cddf5ae51ded930f312ecfcdaec06deffc4c86dd55"))
        (2500,   uint256("0x0bf38c6d5da20de79c9ccd9206516464df21ad641fe371fbb2e7c42fa9e80fc6"))
        (2750,   uint256("bd4cba63b84f1a8c5d5cc1d3f361dee6590f9bc4b76a5cfe574da1ae50d4093e"))
        (3000,   uint256("4d7106c0f378569d1a474be09910bc1142bf8c6e322a4547183658eec95d0003"))
        (5000,   uint256("2a7fa30b06ac2c12c52e49f589d95d697ecd1af279b51dec460e9724fb59b55a"))
        (7000,   uint256("36f37d1e46b585603af7c070c9ca49af94fae49fc0ca7ef113ed2c64329b208b"))
        (7500,   uint256("c9b9ca78abbd083051e78e9ede1f1415f88c9de0ded4b6906d4982877cf9cfb9"))
        (8000,   uint256("d306c6d91715d1d86d5a0db75d15b53cbb869a29fd6f8436102d30502ef71ef9"))
        (9000,   uint256("c10db8e7e6370838caa0a33ab91512eafbbc09676de18eeec68d0a26e3c714c0"))
        (10000,   uint256("224ef9f8d3d950b27f7175ab908c0345f882232a6d4803f374d8357b83d0ce3e"))
        (10500,   uint256("8a8f88eff4577208a3bed8b95307d84871f5729d27e0afaef9d1af4597c45d12"))
        (10900,   uint256("bd4df34343304c9093ca029bf87dc567f0fc07f7b2ea6bc390df4463934085aa"))

    ;

    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();
        if (nHeight <= pindexSync->nHeight){
            return false;
        }
        return true;
    }
}
