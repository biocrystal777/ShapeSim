#include <QtGlobal>
#include <QApplication>


#include "./shamainwidget.h"

int main(int argc, char *argv[])
{

   QApplication a(argc, argv);

   ShaMainWidget w;
   w.show();
   return a.exec();
}
