#ifndef MININGPAGE_H
#define MININGPAGE_H

#include "clientmodel.h"
#include "walletmodel.h"
#include "main.h"
#include "wallet.h"
#include "base58.h"
#include <QWidget>

#include <QDir>
#include <QFile>
#include <QProcess>
#include <QTime>
#include <QTimer>
#include <QStringList>
#include <QMap>
#include <QSettings>
#include <QSlider>

double getPoSHardness(int);
double convertPoSCoins(int64_t);
int getPoSTime(int);
int PoSInPastHours(int);
const CBlockIndex* getPoSIndex(int);

namespace Ui {
class MiningPage;
}
class WalletModel;
class ClientModel;

class MiningPage : public QWidget
{
    Q_OBJECT

public:
    explicit MiningPage(QWidget *parent = 0);
    ~MiningPage();
    
    void setModel(WalletModel *model);
    
public slots:
    
    // PoW section
    void minerToggle();
    // PoS section
    void updatePoSstat(bool);
    void setCntBlocks(int pseudo);
    void setCntConnections(int count);

private slots:

    void on_miningToggle_clicked();

private:
    Ui::MiningPage *ui;
    WalletModel *model;
    ClientModel *clientModel;
    
};

#endif // MiningPage_H
