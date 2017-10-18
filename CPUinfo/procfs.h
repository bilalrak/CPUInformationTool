#ifndef PROCFS_H
#define PROCFS_H

#include <QObject>
#include <QVector>
#include <QtCore>
#include <fstream>
#include <QMutex>








class procfs : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int numOfCPUs READ numOfCPUs WRITE setnumOfCPUs NOTIFY numOfCPUsChanged)

public:
    procfs();
    void setnumOfCPUs (int a);
    int numOfCPUs (void);

signals:
    void numOfCPUsChanged();
    void cpuInfoText(QString details);

public slots:
    void onRequestDetails(int index);

private slots:
    void onTimerTimeout();

private:
    void readNumOfCPUs();
    void updateCPUDetails();
    std::fstream fp;
    int Num_cpus;
    QTimer * timer;
    QMutex mutex;
    int requested_CPUindex;
    QVector<QString> CPU_infoVector;

};

#endif // PROCFS_H
