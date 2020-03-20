#include "shashapeparwidgets.h"

using std::function;

ShaShapeParWidget::ShaShapeParWidget(const QString &shapeID, QWidget *parent ) : QWidget(parent), shapeID(shapeID){
   shapeLay = new QGridLayout(this);
   QLabel *label = new QLabel(tr("<b>Limits:</b>"), this);
   shapeLay->addWidget(label, 0, 1, 1, 3, Qt::AlignCenter);

   label = new QLabel(this);
   label->setText(tr("coreAxisAlpha<sub>min</sub> / nm:"));
   shapeLay->addWidget(label, 1, 0, 1, 3);
   axAlphaMinBox = new QDoubleSpinBox(this);
   axAlphaMinBox->setMinimum(0.0);
   axAlphaMinBox->setMaximum(999.5);
   shapeLay->addWidget(axAlphaMinBox, 1, 3, 1, 3);

   label = new QLabel(this);
   label->setText(tr("coreAxisAlpha<sub>max</sub> / nm:"));
   shapeLay->addWidget(label, 1, 6, 1, 3);
   axAlphaMaxBox = new QDoubleSpinBox(this);
   axAlphaMaxBox->setMinimum(0.5);
   axAlphaMaxBox->setMaximum(1000.0);
   shapeLay->addWidget(axAlphaMaxBox, 1, 9, 1, 3);

   label = new QLabel(this);
   label->setText(tr("coreAxisBeta<sub>min</sub> / nm :"));
   shapeLay->addWidget(label, 2, 0, 1, 3);
   axBetaMinBox = new QDoubleSpinBox(this);
   axBetaMinBox->setMinimum(0.0);
   axBetaMinBox->setMaximum(999.5);
   shapeLay->addWidget(axBetaMinBox, 2, 3, 1, 3);

   label = new QLabel(this);
   label->setText(tr("coreAxisBeta<sub>max</sub> / nm:"));
   shapeLay->addWidget(label, 2, 6, 1, 3);
   axBetaMaxBox = new QDoubleSpinBox(this);
   axBetaMaxBox->setMinimum(0.5);
   axBetaMaxBox->setMaximum(1000.0);
   shapeLay->addWidget(axBetaMaxBox, 2, 9, 1, 3);

   label = new QLabel("Grid resolution / nm:", this);
   shapeLay->addWidget(label, 3, 0, 1, 4);
   strideBox = new QComboBox(this);
   strideBox->addItem("1.0");
   strideBox->addItem("0.5");
   strideBox->addItem("0.2");
   strideBox->addItem("0.1");
   strideBox->addItem("0.05");
   strideBox->addItem("0.02");

   shapeLay->addWidget(strideBox, 3, 4, 1, 2);

   loadSettings();

   QObject::connect(axAlphaMaxBox, SIGNAL(valueChanged(double)), this, SLOT(ensureAlphaMinDistance(double)));
   QObject::connect(axAlphaMinBox, SIGNAL(valueChanged(double)), this, SLOT(ensureAlphaMaxDistance(double)));
   QObject::connect(axBetaMaxBox, SIGNAL(valueChanged(double)), this, SLOT(ensureBetaMinDistance(double)));
   QObject::connect(axBetaMinBox, SIGNAL(valueChanged(double)), this, SLOT(ensureBetaMaxDistance(double)));
}

void ShaShapeParWidget::loadSettings()
{
   QSettings settings("AgCoelfen", "ShapeSim");
   settings.setIniCodec("UTF-8");

   auto loadValue = [&,this](const QString &key, const QString &defaultVal, function<void(double)> setter){
      bool ok;
      double init = settings.value(key, defaultVal).toDouble(&ok);
      if(!ok){
         ShaLog::logWarning(tr("Could not read parameter %1 from iniFile. Value will be set to %2").arg(key).arg(0.0));
         init = 0.0;
      }
      setter(init);
   };

   loadValue(tr("shapeParameters/%1/axisAlphaMin").arg(shapeID), "0.0", [this](double d){setAxAlphaMin(d);} );
   loadValue(tr("shapeParameters/%1/axisAlphaMax").arg(shapeID), "0.0", [this](double d){setAxAlphaMax(d);} );
   loadValue(tr("shapeParameters/%1/axisBetaMin").arg(shapeID),  "0.0", [this](double d){setAxBetaMin(d);  } );
   loadValue(tr("shapeParameters/%1/axisBetaMax").arg(shapeID),  "0.0", [this](double d){setAxBetaMax(d);  } );
   strideBox->setCurrentIndex( settings.value(tr("shapeParameters/%1/gridRes").arg(shapeID), "0").toInt() );
}

void ShaShapeParWidget::writeSettings()
{
   QSettings settings("AgCoelfen", "ShapeSim");
   settings.setIniCodec("UTF-8");

   settings.setValue(tr("shapeParameters/%1/axisAlphaMin").arg(shapeID), axAlphaMinBox->value());
   settings.setValue(tr("shapeParameters/%1/axisAlphaMax").arg(shapeID), axAlphaMaxBox->value());
   settings.setValue(tr("shapeParameters/%1/axisBetaMin").arg(shapeID),  axBetaMinBox->value());
   settings.setValue(tr("shapeParameters/%1/axisBetaMax").arg(shapeID),  axBetaMaxBox->value());
   settings.setValue(tr("shapeParameters/%1/gridRes").arg(shapeID), strideBox->currentIndex());
}

void ShaShapeParWidget::ensureAlphaMaxDistance( double alphaMin )
{
   ldouble alphaMax = axAlphaMaxBox->value();
   if(alphaMax <= alphaMin) axAlphaMaxBox->setValue(alphaMin + 0.5);
}

void ShaShapeParWidget::ensureAlphaMinDistance( double alphaMax )
{
   ldouble alphaMin = axAlphaMinBox->value();
   ldouble betaMin = axBetaMinBox->value();
   if(alphaMax <= alphaMin) axAlphaMinBox->setValue(alphaMax - 0.5);
   if(alphaMax <= betaMin) axBetaMinBox->setValue(alphaMax - 0.5);
}

void ShaShapeParWidget::ensureBetaMaxDistance( double betaMin )
{
   ldouble betaMax = axBetaMaxBox->value();
   ldouble alphaMax = axAlphaMaxBox->value();
   if(betaMax <= betaMin) axBetaMaxBox->setValue(betaMin + 0.5);
   if(alphaMax <= betaMin) axAlphaMaxBox->setValue(betaMin + 0.5);
}

void ShaShapeParWidget::ensureBetaMinDistance( double betaMax)
{
   ldouble betaMin = axBetaMinBox->value();
   if(betaMax <= betaMin) axBetaMinBox->setValue(betaMax - 0.5);

}
/*
ShaProlateParWidget::ShaProlateParWidget(const QString &shapeID, QWidget *parent) : ShaShapeParWidget(shapeID, parent)
{
}

ShaOblateParWidget::ShaOblateParWidget(const QString &shapeID, QWidget *parent) : ShaShapeParWidget(shapeID, parent)
{
}

ShaLongRodParWidget::ShaLongRodParWidget(const QString &shapeID, QWidget *parent) : ShaShapeParWidget(shapeID, parent)
{
}
*/
