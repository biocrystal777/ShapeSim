#include <limits>
#include "./shacsvwriter.h"
#include "./shacsvparser.h"
#include "./shamainwidget.h"
#include "./shaprolatecalculator.h"
#include "./shalongrodcalculator.h"

using std::vector;
using std::string;

ShaMainWidget::ShaMainWidget(QWidget *parent)
   : QWidget(parent)
{
   thisLay = new QGridLayout(this);

   parFrame = new ShaParFrame(this);

   // parFrame->setMinimumSize(620, 450);
   // parFrame->setMaximumSize(620, 450);

   thisLay->addWidget(parFrame, 0, 0, 10, 5);

   // Shape parameters

   shapeFrame = new QFrame(this);
   shapeFrame->setFrameStyle(0x1011);
   //shapeFrame->setMinimumSize(550, 450);
   //shapeFrame->setMaximumSize(550, 450);
   thisLay->addWidget(shapeFrame, 0, 5, 10, 10);
   shapeFrameLay = new QGridLayout(shapeFrame);

   QLabel* label = new QLabel("layer<sub>surf</sub> [nm]:", shapeFrame);
   shapeFrameLay->addWidget(label, 0, 0, 1, 3);
   surfLayerThicknessBox = new QDoubleSpinBox(shapeFrame);
   shapeFrameLay->addWidget(surfLayerThicknessBox, 0, 3, 1, 3);
   label = new QLabel("layer<sub>solv</sub> [nm]:", shapeFrame);
   shapeFrameLay->addWidget(label, 0, 6, 1, 3);
   solvLayerThicknessBox = new QDoubleSpinBox(shapeFrame);
   solvLayerThicknessBox->setEnabled(false);
   shapeFrameLay->addWidget(solvLayerThicknessBox, 0, 9, 1, 3);

   shapeGroupBox = new QGroupBox(tr("Shape"),shapeFrame);
   shapeSwitchLay = new QGridLayout(shapeGroupBox);
   sphereSwitch = new QRadioButton(tr("Sphere"), shapeGroupBox);
   //sphereSwitch->setChecked(true);
   sphereSwitch->setDisabled(true);
   shapeSwitchLay->addWidget(sphereSwitch, 0, 0, 1, 3);
   prolateSwitch = new QRadioButton(tr("Prolate"), shapeGroupBox);
   prolateSwitch->setChecked(true);
   shapeSwitchLay->addWidget(prolateSwitch, 0, 3, 1, 3);
   oblateSwitch =  new QRadioButton(tr("Oblate"), shapeGroupBox);
   shapeSwitchLay->addWidget(oblateSwitch, 0, 6, 1, 3);
   oblateSwitch->setDisabled(true); // TEST
   longRodSwitch =  new QRadioButton(tr("Long Rod"), shapeGroupBox);
   shapeSwitchLay->addWidget(longRodSwitch, 0, 9, 1, 3);
   //longRodSwitch->setDisabled(true); // TEST
   shapeFrameLay->addWidget(shapeGroupBox, 2, 0, 2, 12, Qt::AlignTop);

   sphereWidgetPtr = new ShaSphereParWidget(shapeFrame);
   shapeWidget = sphereWidgetPtr;
   shapeFrameLay->addWidget(sphereWidgetPtr, 4, 0, 4, 12);
   prolateWidgetPtr = new ShaProlateParWidget(shapeFrame);
   shapeFrameLay->addWidget(prolateWidgetPtr, 4, 0, 4, 12);
   prolateWidgetPtr->hide();
   oblateWidgetPtr = new ShaOblateParWidget(shapeFrame);
   shapeFrameLay->addWidget(oblateWidgetPtr, 4, 0, 4, 12);
   oblateWidgetPtr->hide();
   longRodWidgetPtr = new ShaLongRodParWidget(shapeFrame);
   shapeFrameLay->addWidget(longRodWidgetPtr, 4, 0, 4, 12);
   longRodWidgetPtr->hide();

   gnuPlotFrame = new ShaGnuplotFrame(this);
   thisLay->addWidget(gnuPlotFrame, 11, 0, 1, 10);

   label = new QLabel("Stride [nm]:", this);
   thisLay->addWidget(label, 12, 9, 1, 2);
   strideBox = new QComboBox(this);
   strideBox->addItem("1.0");
   strideBox->addItem("0.5");
   strideBox->addItem("0.2");
   strideBox->addItem("0.1");
   strideBox->addItem("0.05");
   strideBox->addItem("0.02");
   //strideBox->addItem("0.01");
   //strideBox->addItem("0.005");
   thisLay->addWidget(strideBox, 12, 11, 1, 2);



   startButton = new QPushButton(tr("Calculate"), this);
   QObject::connect(startButton, SIGNAL(clicked()), this, SLOT(startCalculation()));
   thisLay->addWidget(startButton, 12, 3, 1, 6);

   outputFrame = new QFrame(this);
   outputFrame->setFrameStyle(0x1011);
   thisLay->addWidget(outputFrame, 13, 0, 10, 14);
   outputLay =  new QGridLayout(outputFrame);

   label = new QLabel("Output:");
   outputLay->addWidget(label, 0, 0, 1, 2);
   outPutDir = new QLineEdit(outputFrame);
   outputLay->addWidget(outPutDir, 0, 2, 1, 7);

   sphereResWidgetPtr = new ShaSphereResWidget(outputFrame);
   shapeResWidget = sphereResWidgetPtr;
   outputLay->addWidget(sphereResWidgetPtr, 1,3, 1, 7, Qt::AlignCenter);
   prolateResWidgetPtr = new ShaProlateResWidget(outputFrame);
   outputLay->addWidget(prolateResWidgetPtr, 1, 3, 1, 7, Qt::AlignCenter);
   prolateResWidgetPtr->hide();
   oblateResWidgetPtr = new ShaOblateResWidget(outputFrame);
   outputLay->addWidget(oblateResWidgetPtr, 1, 3, 1, 7, Qt::AlignCenter);
   oblateResWidgetPtr->hide();
   longRodResWidgetPtr = new ShaLongRodResWidget(outputFrame);
   outputLay->addWidget(longRodResWidgetPtr, 1, 3, 1, 7, Qt::AlignCenter);
   longRodResWidgetPtr->hide();

   label = new QLabel(outputFrame);
   label->setText(tr("rho<sub>part</sub> [cP]:"));
   outputLay->addWidget(label, 0, 10, 1, 3, Qt::AlignLeft);
   outRhoBox = new QLineEdit(outputFrame);
   outRhoBox->setReadOnly(true);
   outputLay->addWidget(outRhoBox, 0, 13, 1, 3, Qt::AlignLeft);

   label = new QLabel(outputFrame);
   label->setText(tr("P []:"));
   outputLay->addWidget(label, 1, 10, 1, 3, Qt::AlignLeft);
   outPBox = new QLineEdit(outputFrame);
   outPBox->setReadOnly(true);
   outputLay->addWidget(outPBox, 1, 13, 1, 3, Qt::AlignLeft);

   label = new QLabel(outputFrame);
   label->setText(tr("f/f<sub>0</sub> :"));
   outputLay->addWidget(label, 2, 10, 1, 3, Qt::AlignLeft);
   outff0Box = new QLineEdit(outputFrame);
   outff0Box->setReadOnly(true);
   outputLay->addWidget(outff0Box, 2, 13, 1, 3, Qt::AlignLeft);

   label = new QLabel(outputFrame);
   label->setText(tr("chi^2:"));
   outputLay->addWidget(label, 3, 10, 1, 3, Qt::AlignLeft);
   outChiSqBox = new QLineEdit(outputFrame);
   outChiSqBox->setReadOnly(true);
   outputLay->addWidget(outChiSqBox, 3, 13, 1, 3, Qt::AlignLeft);

   logWidget = new ShaLog(this);
   thisLay->addWidget(logWidget, 21, 0, 10,15);

   this->loadParameters();

   QObject::connect(sphereSwitch, SIGNAL(toggled(bool)), this, SLOT(switchToSphere(bool)));
   QObject::connect(prolateSwitch, SIGNAL(toggled(bool)), this, SLOT(switchToProlate(bool)));
   QObject::connect(oblateSwitch, SIGNAL(toggled(bool)), this, SLOT(switchToOblate(bool)));
   QObject::connect(longRodSwitch, SIGNAL(toggled(bool)), this, SLOT(switchToLongRod(bool)));
   switchToProlate(true);
}

ShaMainWidget::~ShaMainWidget()
{
   saveParameters();
}

void ShaMainWidget::saveParameters() const
{
   QSettings settings("AgCoelfen", "ShapeSim");
   settings.setIniCodec("UTF-8");

   settings.setValue(tr("shapeParameters/layer_Surf"), static_cast<double>(surfLayerThicknessBox->value()));
   settings.setValue(tr("shapeParameters/layer_Solv"), static_cast<double>(solvLayerThicknessBox->value()));

   settings.setValue(tr("shapeParameters/sphere/radMin"), static_cast<double>(sphereWidgetPtr->getRadMin()));
   settings.setValue(tr("shapeParameters/sphere/radMax"), static_cast<double>(sphereWidgetPtr->getRadMax()));

   settings.setValue(tr("shapeParameters/prolate/axisAlphaMin"), static_cast<double>(prolateWidgetPtr->getAxAlphaMin()));
   settings.setValue(tr("shapeParameters/prolate/axisAlphaMax"), static_cast<double>(prolateWidgetPtr->getAxAlphaMax()));
   settings.setValue(tr("shapeParameters/prolate/axisBetaMin"), static_cast<double>(prolateWidgetPtr->getAxBetaMin()));
   settings.setValue(tr("shapeParameters/prolate/axisBetaMax"), static_cast<double>(prolateWidgetPtr->getAxBetaMax()));

   settings.setValue(tr("shapeParameters/oblate/axisAlphaMin"), static_cast<double>(oblateWidgetPtr->getAxAlphaMin()));
   settings.setValue(tr("shapeParameters/oblate/axisAlphaMax"),static_cast<double>( oblateWidgetPtr->getAxAlphaMax()));
   settings.setValue(tr("shapeParameters/oblate/axisBetaMin"), static_cast<double>(oblateWidgetPtr->getAxBetaMin()));
   settings.setValue(tr("shapeParameters/oblate/axisBetaMax"), static_cast<double>(oblateWidgetPtr->getAxBetaMax()));

   settings.setValue(tr("shapeParameters/longRod/axisAlphaMin"), static_cast<double>(longRodWidgetPtr->getAxAlphaMin()));
   settings.setValue(tr("shapeParameters/longRod/axisAlphaMax"), static_cast<double>(longRodWidgetPtr->getAxAlphaMax()));
   settings.setValue(tr("shapeParameters/longRod/axisBetaMin"), static_cast<double>(longRodWidgetPtr->getAxBetaMin()));
   settings.setValue(tr("shapeParameters/longRod/axisBetaMax"), static_cast<double>(longRodWidgetPtr->getAxBetaMax()));

   settings.setValue(tr("shapeParameters/strideIndex"), strideBox->currentIndex());
   settings.setValue(tr("outPutParameters/outPutDir"), outPutDir->text());

   parFrame->saveParameters();
}

   void ShaMainWidget::loadParameters()
{
   bool ok(false);
   ldouble initdouble(0.0);
   int initInt(0);
   QSettings settings("AgCoelfen", "ShapeSim");
   settings.setIniCodec("UTF-8");

   // Macro for loading a ldouble parameter and initializing a class member box Widget
#ifndef INIT_PARAMETER_LDOUBLE
#define INIT_PARAMETER_LDOUBLE(keyName, widgetPtr, defaultValue){ \
   initdouble = settings.value(tr(keyName), defaultValue).toDouble(&ok); \
   if(!ok){ \
   ShaLog::logWarning(tr("Could not read parameter %1 from iniFile. Value will be set to %2") \
   .arg(keyName).arg(defaultValue)); \
}\
   widgetPtr->setValue(initdouble); \
};
#endif // INIT_PARAMETER_LDOUBLE

   // Alternative Macro for loading parameters and
   // using the identifier of a setting function fo the initialization
#ifndef INIT_PARAMETER_VARSETFUNC_LDOUBLE
#define INIT_PARAMETER_VARSETFUNC_LDOUBLE(keyName, varSetFunc, defaultValue){ \
   initdouble = settings.value(tr(keyName), defaultValue).toDouble(&ok); \
   if(!ok){ \
   ShaLog::logWarning(tr("Could not read parameter %1 from iniFile. Value will be set to %2") \
   .arg(keyName).arg(defaultValue)); \
}\
   varSetFunc(initdouble); \
};
#endif // INIT_PARAMETER_VARSETFUNC_LDOUBLE

   // Alternative Macro for loading parameters of type int and
   // using the identifier of a setting function fo the initialization
#ifndef INIT_PARAMETER_VARSETFUNC_INT
#define INIT_PARAMETER_VARSETFUNC_INT(keyName, varSetFunc, defaultValue){ \
   initInt = settings.value(tr(keyName), defaultValue).toDouble(&ok); \
   if(!ok){ \
   ShaLog::logWarning(tr("Could not read parameter %1 from iniFile. Value will be set to %2") \
   .arg(keyName).arg(defaultValue)); \
}\
   varSetFunc(initInt); \
};

#endif //INIT_PARAMETER_VARSETFUNC

   INIT_PARAMETER_LDOUBLE("shapeParameters/layer_Surf", surfLayerThicknessBox, "300.0");
   INIT_PARAMETER_LDOUBLE("shapeParameters/layer_Solv", solvLayerThicknessBox, "300.0");
   INIT_PARAMETER_VARSETFUNC_LDOUBLE("shapeParameters/sphere/radMin", sphereWidgetPtr->setRadMin, "1.0");
   INIT_PARAMETER_VARSETFUNC_LDOUBLE("shapeParameters/sphere/radMax", sphereWidgetPtr->setRadMax, "1.0");
   INIT_PARAMETER_VARSETFUNC_LDOUBLE("shapeParameters/prolate/axisAlphaMin", prolateWidgetPtr->setAxAlphaMin, "1.0");
   INIT_PARAMETER_VARSETFUNC_LDOUBLE("shapeParameters/prolate/axisAlphaMax", prolateWidgetPtr->setAxAlphaMax, "1.0");
   INIT_PARAMETER_VARSETFUNC_LDOUBLE("shapeParameters/prolate/axisBetaMin", prolateWidgetPtr->setAxBetaMin, "1.0");
   INIT_PARAMETER_VARSETFUNC_LDOUBLE("shapeParameters/prolate/axisBetaMax", prolateWidgetPtr->setAxBetaMax, "1.0");
   INIT_PARAMETER_VARSETFUNC_LDOUBLE("shapeParameters/oblate/axisAlphaMin", oblateWidgetPtr->setAxAlphaMin, "1.0");
   INIT_PARAMETER_VARSETFUNC_LDOUBLE("shapeParameters/oblate/axisAlphaMax", oblateWidgetPtr->setAxAlphaMax, "1.0");
   INIT_PARAMETER_VARSETFUNC_LDOUBLE("shapeParameters/oblate/axisBetaMin", oblateWidgetPtr->setAxBetaMin, "1.0");
   INIT_PARAMETER_VARSETFUNC_LDOUBLE("shapeParameters/oblate/axisBetaMax", oblateWidgetPtr->setAxBetaMax, "1.0");
   INIT_PARAMETER_VARSETFUNC_LDOUBLE("shapeParameters/longRod/axisAlphaMin", longRodWidgetPtr->setAxAlphaMin, "1.0");
   INIT_PARAMETER_VARSETFUNC_LDOUBLE("shapeParameters/longRod/axisAlphaMax", longRodWidgetPtr->setAxAlphaMax, "1.0");
   INIT_PARAMETER_VARSETFUNC_LDOUBLE("shapeParameters/longRod/axisBetaMin", longRodWidgetPtr->setAxBetaMin, "1.0");
   INIT_PARAMETER_VARSETFUNC_LDOUBLE("shapeParameters/longRod/axisBetaMax", longRodWidgetPtr->setAxBetaMax, "1.0");
   INIT_PARAMETER_VARSETFUNC_INT("shapeParameters/strideIndex", strideBox->setCurrentIndex, 0);
   outPutDir->setText(settings.value("outPutParameters/outPutDir", "").toString());

#undef INIT_PARAMETER_LDOUBLE
#undef INIT_PARAMETER_VARSETFUNC_LDOUBLE
#undef INIT_PARAMETER_VARSETFUNC_INT
}

void ShaMainWidget::startCalculation()
{

   QGuiApplication::setOverrideCursor(Qt::WaitCursor);

   if(parFrame->calcSinglePair())
      singleCalculation();
   else if(parFrame->calcPairDistr())
      distrCalculation();
   else ShaLog::logWarning(tr("No evaluation mode chosen."));

   QGuiApplication::restoreOverrideCursor();

}

void ShaMainWidget::sphereCalculation(QVector<ldouble> &rad, QVector<ldouble> &chiSq
                                      //ShaMainWidget::chiSqType minMode
                                      )
{

   ldouble rMin = sphereWidgetPtr->getRadMin();
   ldouble rMax = sphereWidgetPtr->getRadMax();
   ldouble stride = strideBox->currentText().toDouble();

   createVectorFromTo(rad, rMin, rMax, stride);

   //for(int i = 0; i < rad.size(); ++i) qDebug() << i  << rad[i];

   int gridLength = rad.size();
   chiSq = QVector<ldouble>(gridLength);
   // get Variables:

   constexpr ldouble PI   = 3.141;
   constexpr ldouble tsPI = 3.141 * 3.0 / 4.0;
   constexpr ldouble kB   = 1.3806488e-23;
   const ldouble dShell   = surfLayerThicknessBox->value();
   const ldouble visc     = parFrame->getSolvVisc(); // from P to cP = m*Pa
   const ldouble T        = parFrame->getTemperature();
   const ldouble densCor  = parFrame->getCoreDensity();
   const ldouble densSurf = parFrame->getSurfDensity();
   const ldouble densSolv = parFrame->getSolvDensity();
   const ldouble DMeas    = parFrame->getDiffCoeff();
   const ldouble SMeas    = parFrame->getSedCoeff();

   QVector<ldouble> densParticle(gridLength);
   for(int i = 0; i < gridLength; ++i){
      ldouble coreRad = rad[i];
      ldouble totRad = coreRad + dShell;
      ldouble coreVol = tsPI * pow(coreRad, 3.0);
      ldouble totVol = tsPI * pow(totRad, 3.0);
      ldouble surfLayerVol = totVol - coreVol;
      ldouble volPartialCore = coreVol / totVol;
      ldouble volPartialSurfLay = surfLayerVol / totVol;
      densParticle[i] = volPartialCore * densCor + volPartialSurfLay * densSurf;
      ldouble SCalc = 4 * totRad * totRad * (densParticle[i] - densSolv) / (18 * visc);
      SCalc *= 1e1;                                                                     // adapt units
      ldouble DCalc = ( kB * T ) / (6.0 * PI * visc * rad[i]);
      DCalc *= 1e16;                                                                    // adapt units
      ldouble chiSqTmpS = (SMeas - SCalc) / SMeas;
      chiSqTmpS *= chiSqTmpS;
      ldouble chiSqTmpD = (DMeas - DCalc) / DMeas;
      chiSqTmpD *= chiSqTmpD;
      ldouble chiSqTmp = chiSqTmpS + chiSqTmpD;
      chiSq [ i ] = chiSqTmp;
   }
   ldouble minChiSq = -666.0;
   int minChiSqPos = minAt(chiSq, &minChiSq);

   outRhoBox->setText(QString::number(densParticle[minChiSqPos],'f', 2));
   outChiSqBox->setText(QString::number(minChiSq,'f', 5));
   sphereResWidgetPtr->setRadCore(rad[minChiSqPos]);
   sphereResWidgetPtr->setRadTot(rad[minChiSqPos] + dShell);


   outPBox->setText(tr("     ---   "));
   outff0Box->setText(tr("     ---   "));
}

void ShaMainWidget::switchToSphere(bool chosen)
{
   if(chosen){
      shapeWidget->hide();
      shapeWidget = sphereWidgetPtr;
      shapeWidget->show();

      shapeResWidget->hide();
      shapeResWidget = sphereResWidgetPtr;
      shapeResWidget->show();
      //shapeFrameLay->addWidget(shapeWidget, 2, 0, 4, 12);
   }
}

void ShaMainWidget::switchToProlate(bool chosen)
{
   if(chosen){
      shapeWidget->hide();
      shapeWidget = prolateWidgetPtr;
      shapeWidget->show();

      shapeResWidget->hide();
      shapeResWidget = prolateResWidgetPtr;
      shapeResWidget->show();
   }
   //shapeFrameLay->addWidget(shapeWidget, 2, 0, 4, 12);

}

void ShaMainWidget::switchToOblate(bool chosen)
{
   if(chosen){
      shapeWidget->hide();
      shapeWidget = oblateWidgetPtr;
      shapeWidget->show();

      shapeResWidget->hide();
      shapeResWidget = oblateResWidgetPtr;
      shapeResWidget->show();
   }
   //shapeFrameLay->addWidget(shapeWidget, 2, 0, 4, 12);
}

void ShaMainWidget::switchToLongRod(bool chosen)
{
   if(chosen){
      shapeWidget->hide();
      shapeWidget = longRodWidgetPtr;
      shapeWidget->show();

      shapeResWidget->hide();
      shapeResWidget = longRodResWidgetPtr;
      shapeResWidget->show();
   }
   //shapeFrameLay->addWidget(shapeWidget, 2, 0, 4, 12);
}


void ShaMainWidget::createVectorFromTo(QVector<ldouble> &v, ldouble min, ldouble max, ldouble stride)
{
   int gridLength = int((max-min) / stride);
   v = QVector<ldouble>(gridLength);
   for(int i = 0; i < gridLength; ++i) v [ i ] = min + stride * static_cast<ldouble>(i);
   ++gridLength;
   v.append(max);
}

int ShaMainWidget::minAt(const QVector<ldouble> &v, ldouble *val) const
{
   if(v.size() == 0) return -1;
   int minPos = 0;
   ldouble min = v[0];
   for (int i = 0; i < v.size(); ++i){
      if(v[i] < min){
         minPos = i;
         min = v[i];
      }
   }
   if(val) *val = min;
   return minPos;
}

vector<vector<doublePair>> ShaMainWidget::extractMinLines(const QVector<QVector<QVector<ldouble>>> &chiPlots,
                                                          const QVector<QVector<ldouble>> &axAlpha,
                                                          const QVector<QVector<ldouble>> &axBeta ) const
{
   const uint distSize = chiPlots.size();
   const uint axisSize = chiPlots[0].size();
   vector<vector<doublePair>> minLines(distSize);
   for(vector<doublePair> &v : minLines) v.resize(axisSize);
   //vector<vector<double>> minLines(2);
   //minLines[0].resize(distSize);
   //minLines[1].resize(distSize);
   //QVector<QVector<double>> minLines[0]();
   for(uint sd = 0; sd < distSize; ++sd){
      for(uint i = 0; i < axisSize; ++i){
         minLines[sd][i].alpha = axAlpha[sd][i];
         const QVector<ldouble> &chiSdI = chiPlots[sd][i];
         uint minBetaIndex = std::distance(chiSdI.begin(), std::min_element(chiSdI.begin(), chiSdI.end()));
         //if(sd==0) qDebug() << minBetaIndex;
         minLines[sd][i].beta = axBeta[sd][minBetaIndex];

         //if(minLines[sd][i].beta >= minLines[sd][i].alpha){
         //   minLines[sd][i].beta = std::numeric_limits<double>::quiet_NaN();
         //   minLines[sd][i].alpha = std::numeric_limits<double>::quiet_NaN();
         //};
      }
      uint maxPos = 0;
      double curMax = 0.0;
      for(uint i = 0; i < minLines[sd].size() ; ++i) {
         double val = minLines[sd][i].beta;
         if(val >= curMax){
            maxPos = i;
            curMax = val;
         }
      }
      for(uint i = 0; i < maxPos ; ++i) {
         minLines[sd][i].beta = std::numeric_limits<double>::infinity();
      }

   }
   return minLines;
}

vector<doublePair> ShaMainWidget::findCrossMinima(vector<vector<doublePair> > &data1,
                                                  vector<vector<doublePair> > &data2) const
{
   vector<doublePair> crossMinima(data1.size());

   for(uint sd = 0; sd < data1.size(); ++sd){
      vector<double> diffs(data1[sd].size());
      for(uint i = 0; i < data1[sd].size(); ++i){
         doublePair pair1 = data1[sd][i];
         doublePair pair2 = data2[sd][i];
         if(std::isnormal(pair1.alpha)
               && std::isnormal(pair1.beta)
               && std::isnormal(pair2.alpha)
               && std::isnormal(pair2.beta)
               && pair1.beta < pair1.alpha
               && pair2.beta < pair2.alpha
               ){
            double dif = pair1.beta - pair2.beta;
            diffs[i] = dif * dif;
         }
         else
            diffs[i] = std::numeric_limits<double>::infinity();

      }
      uint minIndex = std::distance(diffs.begin(), std::min_element(diffs.begin(), diffs.end()));

      crossMinima[sd] = data1[sd][minIndex];
   }

   return crossMinima;
}

void ShaMainWidget::singleCalculation()
{

   if(sphereSwitch->isChecked()){
      QVector<ldouble> rads;
      QVector<ldouble> chiSqs;
      sphereCalculation(rads, chiSqs);
   }
   else if(prolateSwitch->isChecked()) {
      QVector<ldouble> axAlpha;
      QVector<ldouble> axBeta;
      QVector<QVector<ldouble> > chiSqD;
      QVector<QVector<ldouble> > chiSqS;
      QVector<QVector<ldouble> > chiSqLam;

      ShaProlateCalculator prolateCalculator(
               outPutDir->text(),
               strideBox->currentText().toDouble(),
               prolateWidgetPtr->getAxAlphaMin(),
               prolateWidgetPtr->getAxAlphaMax(),
               prolateWidgetPtr->getAxBetaMin(),
               prolateWidgetPtr->getAxBetaMax(),
               surfLayerThicknessBox->value(),
               parFrame->getSolvVisc(),
               parFrame->getTemperature(),
               parFrame->getCoreDensity(),
               parFrame->getSurfDensity(),
               parFrame->getSolvDensity(),
               parFrame->getDiffCoeff(),
               parFrame->getSedCoeff(),
               parFrame->getLSPRLambda(),
               parFrame->getDiffCoeffDev(),
               parFrame->getSedCoeffDev(),
               parFrame->getLSPRLambdaDev(),
               parFrame->useDiffCoeff(),
               parFrame->useSedCoeff(),
               parFrame->useLSPRLambda(),
               parFrame->useDiffCoeffDev(),
               parFrame->useSedCoeffDev(),
               parFrame->useLSPRLambaDev(),
               gnuPlotFrame->useGnuplot(),
               gnuPlotFrame->gnuplotPath()
               );

      prolateCalculator.start(axAlpha, axBeta, chiSqD, chiSqS, chiSqLam);

      //outRhoBox->setText(QString::number(densParticle[minChiSqPos],'f', 2));
      //outChiSqBox->setText(QString::number(minChiSq,'f', 5));
      //sphereResWidgetPtr->setRadCore(rad[minChiSqPos]);
      //sphereResWidgetPtr->setRadTot(rad[minChiSqPos] + dShell);


      //outPBox->setText(tr("     ---   "));
      //outff0Box->setText(tr("     ---   "));

   }
   else if(longRodSwitch->isChecked()){
      QVector<ldouble> axAlpha;
      QVector<ldouble> axBeta;
      QVector<QVector<ldouble> > chiSqD;
      QVector<QVector<ldouble> > chiSqS;
      QVector<QVector<ldouble> > chiSqLam;

      ShaLongRodCalculator longRodCalculator(
               outPutDir->text(),
               strideBox->currentText().toDouble(),
               prolateWidgetPtr->getAxAlphaMin(),
               prolateWidgetPtr->getAxAlphaMax(),
               prolateWidgetPtr->getAxBetaMin(),
               prolateWidgetPtr->getAxBetaMax(),
               surfLayerThicknessBox->value(),
               parFrame->getSolvVisc(),
               parFrame->getTemperature(),
               parFrame->getCoreDensity(),
               parFrame->getSurfDensity(),
               parFrame->getSolvDensity(),
               parFrame->getDiffCoeff(),
               parFrame->getSedCoeff(),
               parFrame->getLSPRLambda(),
               parFrame->getDiffCoeffDev(),
               parFrame->getSedCoeffDev(),
               parFrame->getLSPRLambdaDev(),
               parFrame->useDiffCoeff(),
               parFrame->useSedCoeff(),
               parFrame->useLSPRLambda(),
               parFrame->useDiffCoeffDev(),
               parFrame->useSedCoeffDev(),
               parFrame->useLSPRLambaDev(),
               gnuPlotFrame->useGnuplot(),
               gnuPlotFrame->gnuplotPath()
               );
      longRodCalculator.start(axAlpha, axBeta, chiSqD, chiSqS, chiSqLam);
   }
}

void ShaMainWidget::distrCalculation()
{

   // get file name (s)
   QString inFile = parFrame->getDistrFile();

   if(!QFile::exists(inFile)){
      ShaLog::logWarning(tr("File with path %1 does not exist.").arg(inFile));
      return;
   }
   ShaCsvParser parser(inFile.toStdString(), ',', '.');
   parser.parseFile();
   vector<string> headLines = parser.getHeadLines();
   vector<vector<double> > data = parser.getData();

   if(data.size() != 2 || data[0].size() != data[1].size() ){
      ShaLog::logError(tr("%1 has a wrong data Format ").arg(inFile));
      return;
   }

   // Distributions, aligned, same size
   const uint distSize = data[0].size();
   QVector<ldouble> distD(distSize);
   QVector<ldouble> distS(distSize);

   for(int i = 0; i <  static_cast<int>(distSize); ++i){
      distD[i] = static_cast<ldouble>( data[0][i] );
      distS[i] = static_cast<ldouble>( data[1][i] );
   }

   // sD-Pair -> axisLength
   QVector<QVector<ldouble> > axAlpha;
   axAlpha.resize(distSize);
   QVector<QVector<ldouble> > axBeta;
   axBeta.resize(distSize);
   // sD-Pair -> alpha -> beta
   QVector<QVector<QVector<ldouble> > > chiSqD;
   chiSqD.resize(distSize);
   QVector<QVector<QVector<ldouble> > > chiSqS;
   chiSqS.resize(distSize);
   QVector<QVector<QVector<ldouble> > > chiSqLam;
   chiSqLam.resize(distSize);

   if(prolateSwitch->isChecked()){

#pragma omp parallel// private(thread_id)
     {
         //thread_id = 0;
#pragma omp for
         for(uint i = 0; i < distSize; ++i){
            ShaProlateCalculator prolateCalculator(
                     outPutDir->text()
                     .append(tr("D_%1").arg(QString::number(static_cast<double>(distD[i]), 'e', 5)))
                     .append(tr("s_%1").arg(QString::number(static_cast<double>(distS[i]), 'e', 5))),
                     strideBox->currentText().toDouble(),
                     prolateWidgetPtr->getAxAlphaMin(),
                     prolateWidgetPtr->getAxAlphaMax(),
                     prolateWidgetPtr->getAxBetaMin(),
                     prolateWidgetPtr->getAxBetaMax(),
                     surfLayerThicknessBox->value(),
                     parFrame->getSolvVisc(),
                     parFrame->getTemperature(),
                     parFrame->getCoreDensity(),
                     parFrame->getSurfDensity(),
                     parFrame->getSolvDensity(),
                     distD[i],  //parFrame->getDiffCoeff(),
                     distS[i],  //parFrame->getSedCoeff(),
                     0.0,// parFrame->getLSPRLambda(),
                     0.0,//parFrame->getDiffCoeffDev(),
                     0.0,//parFrame->getSedCoeffDev(),
                     0.0,//parFrame->getLSPRLambdaDev(),
                     true, //parFrame->useDiffCoeff(),
                     true,// parFrame->useSedCoeff(),
                     false, //parFrame->useLSPRLambda(),
                     false, //parFrame->useDiffCoeffDev(),
                     false, //parFrame->useSedCoeffDev(),
                     false, //parFrame->useLSPRLambaDev()
                     gnuPlotFrame->useGnuplot(),
                     gnuPlotFrame->gnuplotPath()
                     );
            prolateCalculator.start(axAlpha[i], axBeta[i], chiSqD[i], chiSqS[i], chiSqLam[i]);
         }
      }
   }
   else if(longRodSwitch->isChecked()){

#pragma omp parallel// private(thread_id)
      {
         //thread_id = 0;
#pragma omp for
         for(uint i = 0; i < distSize; ++i){

            ShaLongRodCalculator longRodCalculator(
                     outPutDir->text()
                     .append(tr("D_%1").arg(QString::number(static_cast<double>(distD[i]), 'e', 5)))
                     .append(tr("s_%1").arg(QString::number(static_cast<double>(distS[i]), 'e', 5))),
                     strideBox->currentText().toDouble(),
                     longRodWidgetPtr->getAxAlphaMin(),
                     longRodWidgetPtr->getAxAlphaMax(),
                     longRodWidgetPtr->getAxBetaMin(),
                     longRodWidgetPtr->getAxBetaMax(),
                     surfLayerThicknessBox->value(),
                     parFrame->getSolvVisc(),
                     parFrame->getTemperature(),
                     parFrame->getCoreDensity(),
                     parFrame->getSurfDensity(),
                     parFrame->getSolvDensity(),
                     distD[i],  //parFrame->getDiffCoeff(),
                     distS[i],  //parFrame->getSedCoeff(),
                     0.0,// parFrame->getLSPRLambda(),
                     0.0,//parFrame->getDiffCoeffDev(),
                     0.0,//parFrame->getSedCoeffDev(),
                     0.0,//parFrame->getLSPRLambdaDev(),
                     true, //parFrame->useDiffCoeff(),
                     true,// parFrame->useSedCoeff(),
                     false, //parFrame->useLSPRLambda(),
                     false, //parFrame->useDiffCoeffDev(),
                     false, //parFrame->useSedCoeffDev(),
                     false, //parFrame->useLSPRLambaDev()
                     gnuPlotFrame->useGnuplot(),
                     gnuPlotFrame->gnuplotPath()
                     );
            longRodCalculator.start(axAlpha[i], axBeta[i], chiSqD[i], chiSqS[i], chiSqLam[i]);
         }
      }
   }

   // find minima for each distribution

   //qDebug() << 5;
   vector<vector<doublePair>> minD = extractMinLines(chiSqD, axAlpha, axBeta);
   vector<vector<doublePair>> minS = extractMinLines(chiSqS, axAlpha, axBeta);
   vector<vector<doublePair>> minLam = extractMinLines(chiSqLam, axAlpha, axBeta);
   //qDebug() << 6;


   for(uint i = 0; i < minD[0].size(); ++i){
      qDebug() << minD[0][i].alpha << minD[0][i].beta << minS[0][i].alpha << minS[0][i].beta;
   }

   // find cross point of s/D distribution
   vector<doublePair> minPairs = findCrossMinima(minD, minS);

   vector<string> headOut = {"alpha", "beta"};
   vector<vector<double>> dataToWrite(2);
   dataToWrite[0].resize(minPairs.size());
   dataToWrite[1].resize(minPairs.size());
   for(uint i = 0; i < minPairs.size(); ++i){
      dataToWrite[0][i] = minPairs[i].alpha;
      dataToWrite[1][i] = minPairs[i].beta;
   }

   QString outFile = inFile;
   outFile.remove(outFile.length() - 5,4);
   outFile.append("_distr.cvs");
   ShaCsvWriter writer(outFile.toStdString());
   writer.writeFile(dataToWrite, headOut);

}
