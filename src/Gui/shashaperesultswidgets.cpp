#include "shashaperesultswidgets.h"
/*
ShaSphereResWidget::ShaSphereResWidget(QWidget *parent) : ShaShapeResWidget(parent)
{
   QLabel *label = new QLabel(this);
   label->setText(tr("Core radius [nm]:"));
   shapeLay->addWidget(label, 1, 0, 1, 3);
   radCoreBox = new QLineEdit(this);
   radCoreBox->setReadOnly(true);
   shapeLay->addWidget(radCoreBox, 1, 3, 1, 3);

   label = new QLabel(this);
   label->setText(tr("Total radius [nm]:"));
   shapeLay->addWidget(label, 2, 0, 1, 3);
   radTotBox = new QLineEdit(this);
   radTotBox->setReadOnly(true);
   shapeLay->addWidget(radTotBox, 2, 3, 1, 3);
}
*/

ShaProlateResWidget::ShaProlateResWidget(QWidget *parent) : ShaNonSphereResWidget(parent)
{
   QLabel *label = new QLabel(this);
   label->setText(tr("CoreAxis<sub>alpha</sub> [nm]:"));
   shapeLay->addWidget(label, 1, 0, 1, 3);
   axAlphaCoreBox = new QLineEdit(this);
   axAlphaCoreBox->setReadOnly(true);
   shapeLay->addWidget(axAlphaCoreBox, 1, 3, 1, 3);

   label = new QLabel(this);
   label->setText(tr("Total Axis<sub>alpha</sub> [nm]:"));
   shapeLay->addWidget(label, 2, 0, 1, 3);
   axAlphaTotBox = new QLineEdit(this);
   axAlphaTotBox->setReadOnly(true);
   shapeLay->addWidget(axAlphaTotBox, 2, 3, 1, 3);

   label = new QLabel(this);
   label->setText(tr("CoreAxis<sub>beta</sub> [nm]:"));
   shapeLay->addWidget(label, 3, 0, 1, 3);
   axBetaCoreBox = new QLineEdit(this);
   axBetaCoreBox->setReadOnly(true);
   shapeLay->addWidget(axBetaCoreBox, 3, 3, 1, 3);

   label = new QLabel(this);
   label->setText(tr("Total Axis<sub>beta</sub> [nm]:"));
   shapeLay->addWidget(label, 4, 0, 1, 3);
   axBetaTotBox = new QLineEdit(this);
   axBetaTotBox->setReadOnly(true);
   shapeLay->addWidget(axBetaTotBox, 4, 3, 1, 3);
}

ShaOblateResWidget::ShaOblateResWidget(QWidget *parent) : ShaNonSphereResWidget(parent)
{
   QLabel *label = new QLabel(this);
   label->setText(tr("CoreAxis<sub>alpha</sub> [nm]:"));
   shapeLay->addWidget(label, 1, 0, 1, 3);
   axAlphaCoreBox = new QLineEdit(this);
   axAlphaCoreBox->setReadOnly(true);
   shapeLay->addWidget(axAlphaCoreBox, 1, 3, 1, 3);

   label = new QLabel(this);
   label->setText(tr("Total Axis<sub>alpha</sub> [nm]:"));
   shapeLay->addWidget(label, 2, 0, 1, 3);
   axAlphaTotBox = new QLineEdit(this);
   axAlphaTotBox->setReadOnly(true);
   shapeLay->addWidget(axAlphaTotBox, 2, 3, 1, 3);

   label = new QLabel(this);
   label->setText(tr("CoreAxis<sub>beta</sub> [nm]:"));
   shapeLay->addWidget(label, 3, 0, 1, 3);
   axBetaCoreBox = new QLineEdit(this);
   axBetaCoreBox->setReadOnly(true);
   shapeLay->addWidget(axBetaCoreBox, 3, 3, 1, 3);

   label = new QLabel(this);
   label->setText(tr("Total Axis<sub>beta</sub> [nm]:"));
   shapeLay->addWidget(label, 4, 0, 1, 3);
   axBetaTotBox = new QLineEdit(this);
   axBetaTotBox->setReadOnly(true);
   shapeLay->addWidget(axBetaTotBox, 4, 3, 1, 3);
}

ShaLongRodResWidget::ShaLongRodResWidget(QWidget *parent) : ShaNonSphereResWidget(parent)
{
   QLabel *label = new QLabel(this);
   label->setText(tr("CoreAxis<sub>alpha</sub> [nm]:"));
   shapeLay->addWidget(label, 1, 0, 1, 3);
   axAlphaCoreBox = new QLineEdit(this);
   axAlphaCoreBox->setReadOnly(true);
   shapeLay->addWidget(axAlphaCoreBox, 1, 3, 1, 3);

   label = new QLabel(this);
   label->setText(tr("Total Axis<sub>alpha</sub> [nm]:"));
   shapeLay->addWidget(label, 2, 0, 1, 3);
   axAlphaTotBox = new QLineEdit(this);
   axAlphaTotBox->setReadOnly(true);
   shapeLay->addWidget(axAlphaTotBox, 2, 3, 1, 3);

   label = new QLabel(this);
   label->setText(tr("CoreAxis<sub>beta</sub> [nm]:"));
   shapeLay->addWidget(label, 3, 0, 1, 3);
   axBetaCoreBox = new QLineEdit(this);
   axBetaCoreBox->setReadOnly(true);
   shapeLay->addWidget(axBetaCoreBox, 3, 3, 1, 3);

   label = new QLabel(this);
   label->setText(tr("Total Axis<sub>beta</sub> [nm]:"));
   shapeLay->addWidget(label, 4, 0, 1, 3);
   axBetaTotBox = new QLineEdit(this);
   axBetaTotBox->setReadOnly(true);
   shapeLay->addWidget(axBetaTotBox, 4, 3, 1, 3);
}
