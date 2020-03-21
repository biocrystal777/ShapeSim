#include "shashapeparwidgets.h"

using std::function;

ShaShapeParWidget::ShaShapeParWidget(const QString &shapeID, QWidget *parent ) : QWidget(parent), shapeID(shapeID){

   shapeLay = new QGridLayout(this);
   QLabel *label = new QLabel(tr("<b>Grid parameters:</b>"), this);
   shapeLay->addWidget(label, 0, 1, 1, 3, Qt::AlignCenter);

   auto makeLabeledSpinBox = [this](const QString &labelText, QDoubleSpinBox **spinBox, int row, int col, double minVal, double maxVal){
      QLabel *label = new QLabel(labelText, this);
      const int dist = 3;
      shapeLay->addWidget(label, row, col, 1, dist);
      *spinBox = new QDoubleSpinBox(this);
      shapeLay->addWidget(*spinBox, row, col+dist, 1, 3);
      (*spinBox)->setMinimum(minVal);
      (*spinBox)->setMaximum(maxVal);
   };
   makeLabeledSpinBox(tr("coreAxisAlpha<sub>min</sub> / nm:"), &axAlphaMinBox, 1, 0, 0.0, 999.5);
   makeLabeledSpinBox(tr("coreAxisAlpha<sub>max</sub> / nm:"), &axAlphaMaxBox, 1, 6, 5.0, 1000.0);
   makeLabeledSpinBox(tr("coreAxisAlpha<sub>min</sub> / nm:"), &axBetaMinBox,  2, 0, 0.0, 999.5);
   makeLabeledSpinBox(tr("coreAxisBeta<sub>max</sub> / nm:"),  &axBetaMaxBox,  2, 6, 1.0, 1000.0);

   label = new QLabel("Grid resolution / nm:", this);
   shapeLay->addWidget(label, 3, 0, 1, 4);
   gridResBox = new QComboBox(this);
   gridResBox->addItems(QStringList() << "1.0" << "0.5" << "0.2" << "0.1" << "0.05" << "0.02" << "0.01");
   shapeLay->addWidget(gridResBox, 3, 4, 1, 2);

   loadSettings();

   QObject::connect(axAlphaMaxBox, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &ShaShapeParWidget::ensureAlphaMinDistance);
   QObject::connect(axAlphaMinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &ShaShapeParWidget::ensureAlphaMaxDistance);
   QObject::connect(axBetaMaxBox,  qOverload<double>(&QDoubleSpinBox::valueChanged), this, &ShaShapeParWidget::ensureBetaMinDistance);
   QObject::connect(axBetaMinBox,  qOverload<double>(&QDoubleSpinBox::valueChanged), this, &ShaShapeParWidget::ensureBetaMaxDistance);
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
   loadValue(tr("shapeParameters/%1/axisBetaMin").arg(shapeID),  "0.0", [this](double d){setAxBetaMin(d); } );
   loadValue(tr("shapeParameters/%1/axisBetaMax").arg(shapeID),  "0.0", [this](double d){setAxBetaMax(d); } );
   gridResBox->setCurrentIndex( settings.value(tr("shapeParameters/%1/gridRes").arg(shapeID), "0").toInt()  );
}

void ShaShapeParWidget::writeSettings()
{
   QSettings settings("AgCoelfen", "ShapeSim");
   settings.setIniCodec("UTF-8");
   settings.setValue(tr("shapeParameters/%1/axisAlphaMin").arg(shapeID), axAlphaMinBox->value());
   settings.setValue(tr("shapeParameters/%1/axisAlphaMax").arg(shapeID), axAlphaMaxBox->value());
   settings.setValue(tr("shapeParameters/%1/axisBetaMin").arg(shapeID),  axBetaMinBox->value());
   settings.setValue(tr("shapeParameters/%1/axisBetaMax").arg(shapeID),  axBetaMaxBox->value());
   settings.setValue(tr("shapeParameters/%1/gridRes").arg(shapeID), gridResBox->currentIndex());
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
