#include "shalog_omp.h"
ShaLog *global_LogPtr = nullptr;

ShaLog::ShaLog(QWidget *parent) :
   QWidget(parent)
{
   logWidget = new QTextEdit(this);
   layout = new QGridLayout(this);
   layout->addWidget(logWidget);
   logWidget->setReadOnly(true);
   if(!global_LogPtr)
      global_LogPtr = this;
   omp_init_lock(&lock);
}

ShaLog::~ShaLog()
{
}

void ShaLog::logText(std::string logMessage, bool qDebugToo )
{
   if(global_LogPtr){
      global_LogPtr->logTextInInstance(QString(logMessage.c_str()));
      if(qDebugToo) qDebug() << logMessage.c_str();
   }
}

void ShaLog::logWarning(std::string logMessage, bool qDebugToo)
{

   if(global_LogPtr){
      global_LogPtr->logWarningInInstance(QString(logMessage.c_str()));
      if(qDebugToo) qDebug() << "WARNING:" << logMessage.c_str();
   }
}

void ShaLog::logError(std::string logMessage, bool qDebugToo)
{
   if(global_LogPtr){
      global_LogPtr->logErrorInInstance(QString(logMessage.c_str()));
      if(qDebugToo) qDebug() << "ERROR:" << logMessage.c_str();
   }
}

void ShaLog::logText(QString logMessage, bool qDebugToo)
{
   if(global_LogPtr){
      global_LogPtr->logTextInInstance(logMessage);
      if(qDebugToo) qDebug() << logMessage;
   }
}

void ShaLog::logWarning(QString logMessage, bool qDebugToo)
{
   if(global_LogPtr){
      global_LogPtr->logWarningInInstance(logMessage);
      if(qDebugToo) qDebug() << "WARNING:" << logMessage;
   }
}

void ShaLog::logError(QString logMessage, bool qDebugToo)
{
   if(global_LogPtr){
      global_LogPtr->logErrorInInstance(logMessage);
      if(qDebugToo) qDebug() << "ERROR:" << logMessage;
   }
}

void ShaLog::logTextInInstance(QString logMessage)
{
   set_lock();
   logWidget->append(tr("<b>%1\n").arg(logMessage));
   unset_lock();
}

void ShaLog::logWarningInInstance(QString logMessage)
{
   set_lock();
   logWidget->append(tr("<font color=\"#DAA520\"><b>WARNING: %1\n</b></font>").arg(logMessage));
   unset_lock();
}

void ShaLog::logErrorInInstance(QString logMessage)
{
   set_lock();
   logWidget->append(tr("<font color=\"#CC0033\"><b>ERROR: %1\n</b></font>").arg(logMessage));
   unset_lock();
}



void ShaLog::clearLog()
{
   if(global_LogPtr){
      global_LogPtr->clearLogInInstance();
   }
}


void ShaLog::clearLogInInstance()
{
   set_lock();
   logWidget->clear();
   unset_lock();
}
