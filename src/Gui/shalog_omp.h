#ifndef FFFLOGWIDGET_H
#define FFFLOGWIDGET_H


#include <QtGlobal>
#include "./shadefinitions.h"
#include <omp.h>

#if QT_VERSION< 0x050000
#include <QTextEdit>
#include <QGridLayout>
#else
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QGridLayout>
#endif

#include <QDebug>
#include <string>

/**************************************************************
***
***  FFFLog (using Qt 4.8.2)
***
**************************************************************/

/*!
 * \brief The FFFLog class allows global logging into a central logWidget
 * \author Benedikt Haeusele
 * \details The class is implemented as singleton. For this reason, all loggging
 * functions are globally accessible.
 * \version 1.0
 * \date March 2013
 * \copyright GNU General Public License version 3.0
 */

class ShaLog: public QWidget
{
   Q_OBJECT
public:

   /*!
     * \brief FFFLog the constructor of this class
     * \param parent parent widget
     */
   explicit ShaLog(QWidget *parent = nullptr);

    ShaLog(const ShaLog& src) = delete;
    ShaLog& operator= (ShaLog& src) = delete;
    ShaLog(ShaLog&& src) = delete;
    ShaLog& operator= (ShaLog&& src) = delete;

   /*!
    * \brief destructor of this
    */
   ~ShaLog();

   /*!
     * \brief logText global overloaded logging function, calls the
     *        internal logging function
     * \param logMessage message to be logged
     */
    static void logText(std::string logMessage, bool qDebugToo = false);

    /*!
      * \brief logWarning global overloaded logging function, calls the
      *        internal logging function
      * \param logMessage message to be logged
      */
    static void logWarning(std::string logMessage, bool qDebugToo = false);

    /*!
      * \brief logError global overloaded logging function, calls the
      *        internal logging function
      * \param logMessage message to be logged
      */
   static void logError(std::string logMessage, bool qDebugToo = false);

   /*!
      * \brief logText global overloaded logging function, calls the
      *        internal logging function
      * \param logMessage message to be logged
      */
   static void logText(QString logMessage, bool qDebugToo = false);

   /*!
      * \brief logWarning global overloaded logging function, calls the
      *        internal logging function
      * \param logMessage message to be logged
      */
   static void logWarning(QString logMessage, bool qDebugToo = false);

   /*!
      * \brief logError global overloaded logging function, calls the
      *        internal logging function
      * \param logMessage message to be logged
      */
   static void logError(QString logMessage, bool qDebugToo = false);

   /*!
     * \brief clearLog clears the logWidget from existing text, calls the
     *        internal logging function
     */
   static void clearLog();

protected:
   QGridLayout *layout;
   QTextEdit *logWidget;

   //static
   omp_lock_t lock;
   inline void set_lock(){ omp_set_lock(&lock); }
   inline void unset_lock(){ omp_unset_lock(&lock); }

   /*!
     * \brief logTextInInstance class internal logging function
     * \param logMessage message to be logged
     */
   void logTextInInstance(QString logMessage) ;

   /*!
     * \brief logWarningInInstance class internal logging function
     * \param logMessage message to be logged
     */
   void logWarningInInstance(QString logMessage) ;

   /*!
     * \brief logWarningInInstance class internal logging function
     * \param logMessage message to be logged
     */
   void logErrorInInstance(QString logMessage) ;

   /*!
     * \brief logWarningInInstance class internal logging function
     * \param logMessage message to be logged
     */
   void clearLogInInstance();
};

#endif // FFFLOGWIDGET_H
