#include "miningpage.h"
#include "ui_miningpage.h"
#include "main.h"
#include "wallet.h"
#include "base58.h"
#include "clientmodel.h"
#include "walletmodel.h"
#include "rpcconsole.h"
#include "rpcserver.h"
#include "miner.h"
#include "transactionrecord.h"
#include "init.h"
#include "blockparams.h"

#include <sstream>
#include <string>

MiningPage::MiningPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MiningPage)
{
    ui->setupUi(this);
}

void MiningPage::setModel(WalletModel *model)
{
    this->model = model;

    setCntConnections(clientModel->getNumConnections());
    connect(clientModel, SIGNAL(numConnectionsChanged(int)), this, SLOT(setCntConnections(int)));

    setCntBlocks(clientModel->getNumBlocks());
    connect(clientModel, SIGNAL(numBlocksChanged(int)), this, SLOT(setCntBlocks(int)));
}

MiningPage::~MiningPage()
{
    delete ui;
}


//
// PoW Mining and Network logic rerporting
//
//

bool isMining = false;

void MiningPage::minerToggle()
{
    if(!isMining)
    {
        // Generate coins
        isMining = true;
        if (pwalletMain)
            GenerateBitcoins(GetBoolArg("-gen", true), pwalletMain, GetArg("-genproclimit", -1));
        QString QMiningON = "Stop Mining";
        QString QMiningStatus = "Wallet is Mining";
        ui->miningToggle->setText(QMiningON);
        ui->miningstatus->setText(QMiningStatus);
        return;
    }
    else if(isMining)
    {
        // Generate coins
        isMining = false;
        if (pwalletMain)
            GenerateBitcoins(GetBoolArg("-gen", false), pwalletMain, GetArg("-genproclimit", -1));
        QString QMiningOFF = "Start Mining";
        QString QMiningStatus = "Not Mining";
        ui->miningToggle->setText(QMiningOFF);
        ui->miningstatus->setText(QMiningStatus);
        return;
    }

}

void MiningPage::on_miningToggle_clicked()
{
    minerToggle();
    return;
}

//
// PoS Minting and Network logic rerporting
//
//

std::string getPoSHash(int Height)
{
    if(Height < 0) { return "351c6703813172725c6d660aa539ee6a3d7a9fe784c87fae7f36582e3b797058"; }
    int desiredheight;
    desiredheight = Height;
    if (desiredheight < 0 || desiredheight > nBestHeight)
        return 0;

    CBlock block;
    CBlockIndex* pblockindex = mapBlockIndex[hashBestChain];
    while (pblockindex->nHeight > desiredheight)
        pblockindex = pblockindex->pprev;
    return pblockindex->phashBlock->GetHex();
}


double getPoSHardness(int height)
{
    const CBlockIndex* blockindex = getPoSIndex(height);

    int nShift = (blockindex->nBits >> 24) & 0xff;

    double dDiff =
        (double)0x0000ffff / (double)(blockindex->nBits & 0x00ffffff);

    while (nShift < 29)
    {
        dDiff *= 256.0;
        nShift++;
    }
    while (nShift > 29)
    {
        dDiff /= 256.0;
        nShift--;
    }

    return dDiff;

}

const CBlockIndex* getPoSIndex(int height)
{
    std::string hex = getPoSHash(height);
    uint256 hash(hex);
    return mapBlockIndex[hash];
}

int getPoSTime(int Height)
{
    std::string strHash = getPoSHash(Height);
    uint256 hash(strHash);

    if (mapBlockIndex.count(hash) == 0)
        return 0;

    CBlock block;
    CBlockIndex* pblockindex = mapBlockIndex[hash];
    return pblockindex->nTime;
}

int PoSInPastHours(int hours)
{
    int wayback = hours * 3600;
    bool check = true;
    int height = pindexBest->nHeight;
    int heightHour = pindexBest->nHeight;
    int utime = (int)time(NULL);
    int target = utime - wayback;

    while(check)
    {
        if(getPoSTime(heightHour) < target)
        {
            check = false;
            return height - heightHour;
        } else {
            heightHour = heightHour - 1;
        }
    }

    return 0;
}

double convertPoSCoins(int64_t amount)
{
    return (double)amount / (double)COIN;
}

void MiningPage::updatePoSstat(bool stat)
{
    if(stat)
    {
        uint64_t nWeight = 0;
        if (pwalletMain)
            nWeight = pwalletMain->GetStakeWeight();
        uint64_t nNetworkWeight = GetPoSKernelPS();
        bool staking = nLastCoinStakeSearchInterval && nWeight;
        uint64_t nExpectedTime = staking ? (BLOCK_SPACING * nNetworkWeight / nWeight) : 0;
        QString Qseconds = " Second(s)";
        if(nExpectedTime > 86399)
        {
           nExpectedTime = nExpectedTime / 60 / 60 / 24;
           Qseconds = " Day(s)";
        }
        else if(nExpectedTime > 3599)
        {
           nExpectedTime = nExpectedTime / 60 / 60;
           Qseconds = " Hour(s)";
        }
        else if(nExpectedTime > 59)
        {
           nExpectedTime = nExpectedTime / 60;
           Qseconds = " Minute(s)";
        }
        ui->lbTime->show();

        int nHeight = pindexBest->nHeight;

        // Net weight percentage
        double nStakePercentage = (double)nWeight / (double)nNetworkWeight * 100;
        double nNetPercentage = (100 - (double)nStakePercentage);
        if(nWeight > nNetworkWeight)
        {
            nStakePercentage = (double)nNetworkWeight / (double)nWeight * 100;
            nNetPercentage = (100 - (double)nStakePercentage);
        }
        // Sync percentage
        // (1498887616 - 1498884018 / 100) / (1498887616 - 1467348018 / 100) * 100
        double nTimeLapse = (GetTime() - pindexBest->GetBlockTime()) / 100;
        double nTimetotalLapse = (GetTime() - Params().GenesisBlock().GetBlockTime()) / 100;
        double nSyncPercentage = 100 - (nTimeLapse / nTimetotalLapse * 100);

        QString QStakePercentage = QString::number(nStakePercentage, 'f', 2);
        QString QNetPercentage = QString::number(nNetPercentage, 'f', 2);
        QString QSyncPercentage = QString::number(nSyncPercentage, 'f', 2);
        QString QTime = clientModel->getLastBlockDate().toString();
        QString QBlockHeight = QString::number(nHeight);
        QString QExpect = QString::number(nExpectedTime, 'f', 0);
        QString QStaking = "Disabled";
        QString QStakeEN = "Not Staking";
        QString QSynced = "Ready (Synced)";
        QString QSyncing = "Not Ready (Syncing)";
        QString QFailed = "Not Connected";
        ui->estnxt->setText(QExpect + Qseconds);
        ui->stkstat->setText(QStakeEN);
        ui->lbHeight->setText(QBlockHeight);
        ui->clStat->setText("<font color=\"red\">" + QFailed + "</font>");
        if(nExpectedTime == 0)
        {
            QExpect = "Not Staking";
            ui->estnxt->setText(QExpect);
        }
        if(staking)
        {
            QStakeEN = "Staking";
            ui->stkstat->setText(QStakeEN);
        }
        if(GetBoolArg("-staking", true))
        {
            QStaking = "Enabled";
        }
        if((GetTime() - pindexBest->GetBlockTime()) < 45 * 60)
        {
            QSyncPercentage = "100";
            nSyncPercentage = 100;
        }
        ui->lbTime->setText(QTime);
        ui->stken->setText(QStaking);
        ui->urweight_2->setText(QStakePercentage + "%");
        ui->netweight_2->setText(QNetPercentage + "%");
        ui->sncStatus->setText(QSyncPercentage + "%");
        if(nSyncPercentage == 100)
            ui->clStat->setText("<font color=\"green\">" + QSynced + "</font>");
        if(nSyncPercentage != 100)
        {
            if(clientModel->getNumConnections() > 0)
                ui->clStat->setText("<font color=\"orange\">" + QSyncing + "</font>");
        }
        return;
    }
}

void MiningPage::setCntBlocks(int pseudo)
{
    pseudo = pindexBest->GetBlockTime();

    if(pseudo > Params().GenesisBlock().GetBlockTime())
        updatePoSstat(true);

    return;
}

void MiningPage::setCntConnections(int count)
{
    ui->lbcon->setText(QString::number(count));
}
