// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

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

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x4d;
        pchMessageStart[1] = 0xb1;
        pchMessageStart[2] = 0x24;
        pchMessageStart[3] = 0xc1;
        vAlertPubKey = ParseHex("041af3b5d1b92e76158b6ef737608ee5773646a6a55a5320d7181fcc83bf3d262790b2261649911d63c84fea5572ea591011bc9d54c43036d2812c5cd52736d323");
        nDefaultPort = 17356;
        nRPCPort = 17358;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        const char* pszTimestamp = "Copico to launch one of it's innovative products on the blockchain";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1504749600, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1504749600;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 709039;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000cd46ca7101c7a71a611aa9af257c473e3a466e500352699494f916b5694"));
        assert(genesis.hashMerkleRoot == uint256("0x47f3bfadbc9a2dcb1ac2fd0f0769981559c10f39870ff522749e6cbfbe74cf72"));

        vSeeds.push_back(CDNSSeedData("seed1.copico.io", "seed1.copico.io"));
		vSeeds.push_back(CDNSSeedData("seed2.copico.io", "seed2.copico.io"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,28);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,43);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,144);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 10000;
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
        pchMessageStart[0] = 0x21;
        pchMessageStart[1] = 0x7c;
        pchMessageStart[2] = 0xb4;
        pchMessageStart[3] = 0xba;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("047e860b4b315a11898f023bc5db4df598d0bdb81e1cb9d408ed2227a5cbf05cfd6e4f73630cde2192df3ff6e8d2f280565392ee3ac37e176ba7dc882aa00ac26c");
        nDefaultPort = 17357;
        nRPCPort = 17359;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 709039;		
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xb3150dc092afdeb901a1ee19279961aec89841c69bfd692571ca6401e8bf7639"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,28);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,43);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,229);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


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
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
