#include "shashaperesultswidgets.h"

ShaStandardShapeResWidget::ShaStandardShapeResWidget(QWidget *parent) : ShaShapeResultsWidget(parent)
{
   auto makeLineEdit = [this](const QString &labelText, QLineEdit **lineEditPtr, int row, int col){
      QLabel *label = new QLabel(labelText, this);
      const int dist = 3;
      shapeLay->addWidget(label, row, col, 1, dist);
      *lineEditPtr = new QLineEdit(this);
      (*lineEditPtr)->setReadOnly(true);
      shapeLay->addWidget(*lineEditPtr, row, col+dist, 1, 3);
   };

   makeLineEdit(tr("Core Axis<sub>alpha</sub> [nm]:"),  &axAlphaCoreBox, 1, 0);
   makeLineEdit(tr("Total Axis<sub>alpha</sub> [nm]:"), &axAlphaTotBox,  2, 0);
   makeLineEdit(tr("Core Axis<sub>beta</sub> [nm]:"),   &axBetaCoreBox,  3, 0);
   makeLineEdit(tr("Total Axis<sub>beta</sub> [nm]:"),  &axBetaTotBox,   4, 0);

}

ShaProlateResWidget::ShaProlateResWidget(QWidget *parent) : ShaStandardShapeResWidget(parent)
{
}

ShaOblateResWidget::ShaOblateResWidget(QWidget *parent) : ShaStandardShapeResWidget(parent)
{
}

ShaLongRodResWidget::ShaLongRodResWidget(QWidget *parent) : ShaStandardShapeResWidget(parent)
{

}
