#include "shashapeparwidgets.h"

ShaShapeParWidget::ShaShapeParWidget( QWidget *parent ) : QWidget(parent){
   shapeLay = new QGridLayout(this);
   QLabel *label = new QLabel(tr("<b>Limits:</b>"), this);
   shapeLay->addWidget(label, 0, 1, 1, 3, Qt::AlignCenter);

   label = new QLabel(this);
   label->setText(tr("coreAxisAlpha<sub>min</sub> [nm]:"));
   shapeLay->addWidget(label, 1, 0, 1, 3);
   axAlphaMinBox = new QDoubleSpinBox(this);
   axAlphaMinBox->setMinimum(0.0);
   axAlphaMinBox->setMaximum(999.5);
   shapeLay->addWidget(axAlphaMinBox, 1, 3, 1, 3);

   label = new QLabel(this);
   label->setText(tr("coreAxisAlpha<sub>max</sub> [nm]:"));
   shapeLay->addWidget(label, 1, 6, 1, 3);
   axAlphaMaxBox = new QDoubleSpinBox(this);
   axAlphaMaxBox->setMinimum(0.5);
   axAlphaMaxBox->setMaximum(1000.0);
   shapeLay->addWidget(axAlphaMaxBox, 1, 9, 1, 3);

   label = new QLabel(this);
   label->setText(tr("coreAxisBeta<sub>min</sub> [nm]:"));
   shapeLay->addWidget(label, 2, 0, 1, 3);
   axBetaMinBox = new QDoubleSpinBox(this);
   axBetaMinBox->setMinimum(0.0);
   axBetaMinBox->setMaximum(999.5);
   shapeLay->addWidget(axBetaMinBox, 2, 3, 1, 3);

   label = new QLabel(this);
   label->setText(tr("coreAxisBeta<sub>max</sub> [nm]:"));
   shapeLay->addWidget(label, 2, 6, 1, 3);
   axBetaMaxBox = new QDoubleSpinBox(this);
   axBetaMaxBox->setMinimum(0.5);
   axBetaMaxBox->setMaximum(1000.0);
   shapeLay->addWidget(axBetaMaxBox, 2, 9, 1, 3);
}

ShaProlateParWidget::ShaProlateParWidget(QWidget *parent) : ShaShapeParWidget(parent)
{

   QObject::connect(axAlphaMaxBox, SIGNAL(valueChanged(double)), this, SLOT(ensureAlphaMinDistance(double)));
   QObject::connect(axAlphaMinBox, SIGNAL(valueChanged(double)), this, SLOT(ensureAlphaMaxDistance(double)));
   QObject::connect(axBetaMaxBox, SIGNAL(valueChanged(double)), this, SLOT(ensureBetaMinDistance(double)));
   QObject::connect(axBetaMinBox, SIGNAL(valueChanged(double)), this, SLOT(ensureBetaMaxDistance(double)));
}

void ShaProlateParWidget::ensureAlphaMaxDistance( double alphaMin)
{
   ldouble alphaMax = axAlphaMaxBox->value();
   if(alphaMax <= alphaMin) axAlphaMaxBox->setValue(alphaMin + 0.5);
}

void ShaProlateParWidget::ensureAlphaMinDistance( double alphaMax)
{
   ldouble alphaMin = axAlphaMinBox->value();
   ldouble betaMin = axBetaMinBox->value();
   if(alphaMax <= alphaMin) axAlphaMinBox->setValue(alphaMax - 0.5);
   if(alphaMax <= betaMin) axBetaMinBox->setValue(alphaMax - 0.5);
}

void ShaProlateParWidget::ensureBetaMaxDistance( double betaMin)
{
   ldouble betaMax = axBetaMaxBox->value();
   ldouble alphaMax = axAlphaMaxBox->value();
   if(betaMax <= betaMin) axBetaMaxBox->setValue(betaMin + 0.5);
   if(alphaMax <= betaMin) axAlphaMaxBox->setValue(betaMin + 0.5);
}

void ShaProlateParWidget::ensureBetaMinDistance( double betaMax)
{
   ldouble betaMin = axBetaMinBox->value();
   if(betaMax <= betaMin) axBetaMinBox->setValue(betaMax - 0.5);
}

ShaOblateParWidget::ShaOblateParWidget(QWidget *parent) : ShaShapeParWidget(parent)
{

   QObject::connect(axAlphaMaxBox, SIGNAL(valueChanged(double)), this, SLOT(ensureAlphaMinDistance(double)));
   QObject::connect(axAlphaMinBox, SIGNAL(valueChanged(double)), this, SLOT(ensureAlphaMaxDistance(double)));
   QObject::connect(axBetaMaxBox, SIGNAL(valueChanged(double)), this, SLOT(ensureBetaMinDistance(double)));
   QObject::connect(axBetaMinBox, SIGNAL(valueChanged(double)), this, SLOT(ensureBetaMaxDistance(double)));
}

void ShaOblateParWidget::ensureAlphaMaxDistance( double alphaMin)
{
   ldouble alphaMax = axAlphaMaxBox->value();
   if(alphaMax <= alphaMin) axAlphaMaxBox->setValue(alphaMin + 0.5);
}

void ShaOblateParWidget::ensureAlphaMinDistance( double alphaMax)
{
   ldouble alphaMin = axAlphaMinBox->value();
   ldouble betaMin = axBetaMinBox->value();
   if(alphaMax <= alphaMin) axAlphaMinBox->setValue(alphaMax - 0.5);
   if(alphaMax <= betaMin) axBetaMinBox->setValue(alphaMax - 0.5);
}

void ShaOblateParWidget::ensureBetaMaxDistance( double betaMin)
{
   ldouble betaMax = axBetaMaxBox->value();
   ldouble alphaMax = axAlphaMaxBox->value();
   if(betaMax <= betaMin) axBetaMaxBox->setValue(betaMin + 0.5);
   if(alphaMax <= betaMin) axAlphaMaxBox->setValue(betaMin + 0.5);
}

void ShaOblateParWidget::ensureBetaMinDistance( double betaMax)
{
   ldouble betaMin = axBetaMinBox->value();
   if(betaMax <= betaMin) axBetaMinBox->setValue(betaMax - 0.5);
}

ShaLongRodParWidget::ShaLongRodParWidget(QWidget *parent) : ShaShapeParWidget(parent)
{
   QObject::connect(axAlphaMaxBox, SIGNAL(valueChanged(double)), this, SLOT(ensureAlphaMinDistance(double)));
   QObject::connect(axAlphaMinBox, SIGNAL(valueChanged(double)), this, SLOT(ensureAlphaMaxDistance(double)));
   QObject::connect(axBetaMaxBox, SIGNAL(valueChanged(double)), this, SLOT(ensureBetaMinDistance(double)));
   QObject::connect(axBetaMinBox, SIGNAL(valueChanged(double)), this, SLOT(ensureBetaMaxDistance(double)));
}

void ShaLongRodParWidget::ensureAlphaMaxDistance( double alphaMin)
{
   ldouble alphaMax = axAlphaMaxBox->value();
   if(alphaMax <= alphaMin) axAlphaMaxBox->setValue(alphaMin + 0.5);
}

void ShaLongRodParWidget::ensureAlphaMinDistance( double alphaMax)
{
   ldouble alphaMin = axAlphaMinBox->value();
   ldouble betaMin = axBetaMinBox->value();
   if(alphaMax <= alphaMin) axAlphaMinBox->setValue(alphaMax - 0.5);
   if(alphaMax <= betaMin) axBetaMinBox->setValue(alphaMax - 0.5);
}

void ShaLongRodParWidget::ensureBetaMaxDistance( double betaMin)
{
   ldouble betaMax = axBetaMaxBox->value();
   ldouble alphaMax = axAlphaMaxBox->value();
   if(betaMax <= betaMin) axBetaMaxBox->setValue(betaMin + 0.5);
   if(alphaMax <= betaMin) axAlphaMaxBox->setValue(betaMin + 0.5);
}

void ShaLongRodParWidget::ensureBetaMinDistance( double betaMax)
{
   ldouble betaMin = axBetaMinBox->value();
   if(betaMax <= betaMin) axBetaMinBox->setValue(betaMax - 0.5);
}


