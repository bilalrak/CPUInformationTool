/*
 *
 *
 */
#include "procfs.h"
#include <stdio.h>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>
#include <stdlib.h>
#include <stdio.h>


using namespace std;



/**
 * @brief This constructor creates an object of the procfs class.
 *
 * @details
 * The procfs object reads the /proc/cpuinfo file and gets all the required CPU info
 * by calling the readNumOfCPUs and updateCPUDetails metthods. It also initializes a timer and
 * connect the timeout singal to private slot member of this class: onTimerTimeout()
 *
 */
procfs::procfs():
    Num_cpus(0),
    requested_CPUindex(0)
{
    readNumOfCPUs();
    updateCPUDetails();
    timer = new QTimer(this); //This timer is used to periodically call the updateCPUDetails method at regular intervals
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimerTimeout()));
    timer->start(3000);
}



/**
 * @brief updates the CPU infomation being viewed on the qml UI
 *
 * @details parses the /proc/cpuinfo file and stores the information in a QVector of string: CPU_infocvector, where each index corresponds to
 * the details of a particular CPU core. The UI is updated on a label component through emitting a  singal (connection made in main.qml)
 * Only the  CPU_infovector[requested_CPUindex] is emitted, where requested_CPUindex is equal to index of CPU begin viewed on UI
 */
void procfs::updateCPUDetails()
{
    std::string line;
    CPU_infoVector.clear();
    fp.open("/proc/cpuinfo",ios::in);
    for(int i=0;i<Num_cpus;i++)
    {
        QString temp="";
        while(std::getline(fp,line))
        {
            if(line.length()>2)                                                         //read till block end -> each processor detail is composed in a single block, de-limited by empty line
            {
                std::string parameter = line.substr(0,line.find(':'));                  //parse parameter
                parameter.erase( std::remove(parameter.begin(), parameter.end(), '\t'), parameter.end() ); //remove tabs (sometimes there exit more than one tab)
                std::string value;
                if((line.find(':')+1)!=line.length())                                   //check if value exit
                {
                    value=line.substr(line.find(':')+2,line.length());                  //parse value

                }
                else
                    value="-";

                temp += QString::fromStdString(parameter + "\t: " + value);             //reformat the CPU information
                temp+="\n";
            }
            else                                                                        //processor[n] detail read till the block end
            {
                CPU_infoVector.push_back(temp);                                         //insert processor[n] detail in a vector
                break;
            }
        }
    }
    fp.close();

    QString compser="";
    if(requested_CPUindex>Num_cpus-1 || requested_CPUindex<0)
    {
        compser = "Invalid CPU. \nNot found in your hardware!";
    }
    else
    {
        compser = CPU_infoVector[requested_CPUindex];
    }
    emit cpuInfoText(compser);                                             //notify the UI display for updated details, only for the processor[n], where n=requested_CPUindex
                                                                           //requested_CPUindex is received from UI through procfs slot: onRequestDetails(int index)

}



/**
 * @brief reads the number of cores
 *
 * @details count is stored in a private int Num_cpus. Reads the count by counting the occurence of string "processor"
 * /proc/cpuinfo file
 */
void procfs::readNumOfCPUs()
{
    fp.open("/proc/cpuinfo",ios::in);
    int count = 0;
    std::string line;
    while (std::getline(fp, line))
    {
        std::stringstream stream(line);
        std::string word;
        stream>>word;
        if(word == "processor")
        {
            count++;
        }
    }
    Num_cpus = count;
    fp.close();
}



/**
 * @brief Get method for Q_PROPERTY binding
 * @return The count of cores found
 *
 * @details The property is exposed in qml.main so that UI is able to dynamically create view buttons corresponding to each core of the system.
 */
int procfs::numOfCPUs()
{
    return Num_cpus;
}



/**
 * @brief Set method for Q_PROPERTY binding
 * @param a: Dummy variable. Not used in the method.
 *
 * @details The method is left empty since UI is not allowed to change the number of cores found on the machine. The exixtance of this
 * method is mandatory for proper binding to qml
 */
void procfs::setnumOfCPUs(int a)
{

}


/**
 * @brief Slot method to act as setter for requested_CPUindex private variable
 * @param index: requested_CPUindex is set to index
 *
 * @details Calls the updateCPUDetails method internally, so that appropriate core information may be loaded on the qml UI
 */
void procfs::onRequestDetails(int index)
{
    requested_CPUindex = index;
    mutex.lock();
    updateCPUDetails();             //upon receiving the new index, updateCPUDetails() is called forcefully to immediately reflect change on UI's display label.
    mutex.unlock();                 //updateCPUDetails() is ensapsulated in mutex lock since it can be also called from the timer timeout handler: onTimerTimeout()
}


/**
 * @brief Slot method for QTimer 'timer' timeout singal
 *
 * @details This method periodically (3 second intervals) calls updateCPUDetails method,
 * making sure that the CPU details are updated in real time for the last requested cpu core (through onRequestDetails() slot)
 *
 */
void procfs::onTimerTimeout()
{
    mutex.lock();
    updateCPUDetails();
    mutex.unlock();
}

