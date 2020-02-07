#include <QtGlobal>
//#if QT_VERSION < 0x050000
//#include <QApplication>
//#else
#include <QApplication>
//#endif

#include "./shamainwidget.h"

int main(int argc, char *argv[])
{
  // Q_DECLARE_METATYPE(QTextBlock);
  // qRegisterMetaType<QTextBlock>("QTextBlock");
#if QT_VERSION< 0x050000
   QApplication a(argc, argv);
#else
   QApplication a(argc, argv);
#endif //USE_QT_5_3
   ShaMainWidget w;
   w.show();
   return a.exec();
}
