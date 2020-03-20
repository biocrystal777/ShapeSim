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
   qDebug() << 1;

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

   shapeGroupBox = new QGroupBox(tr("Shape"),shapeFrame);
   shapeSwitchLay = new QGridLayout(shapeGroupBox);

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

   //reWidgetPtr = new ShaSphereParWidget(shapeFrame);
   //shapeWidget = sphereWidgetPtr;
   //shapeFrameLay->addWidget(sphereWidgetPtr, 4, 0, 4, 12);
   qDebug() << 4;
   prolateWidgetPtr = new ShaShapeParWidget(tr("Prolate"), shapeFrame);
   qDebug() << 5;
   shapeFrameLay->addWidget(prolateWidgetPtr, 4, 0, 4, 12);
   prolateWidgetPtr->hide();
   curShapeWidget = prolateWidgetPtr;
   oblateWidgetPtr = new ShaShapeParWidget(tr("Oblate"), shapeFrame);
   shapeFrameLay->addWidget(oblateWidgetPtr, 4, 0, 4, 12);
   oblateWidgetPtr->hide();
   longRodWidgetPtr = new ShaShapeParWidget(tr("LongRod"), shapeFrame);
   shapeFrameLay->addWidget(longRodWidgetPtr, 4, 0, 4, 12);
   longRodWidgetPtr->hide();

   gnuPlotFrame = new ShaGnuplotFrame(this);
   thisLay->addWidget(gnuPlotFrame, 11, 0, 1, 10);
   qDebug() << 2;

   startButton = new QPushButton(tr("Calculate"), this);
   QObject::connect(startButton, SIGNAL(clicked()), this, SLOT(startCalculation()));
   thisLay->addWidget(startButton, 12, 3, 1, 6);


   outputFrame = new QFrame(this);
   outputFrame->setFrameStyle(0x1011);
   thisLay->addWidget(outputFrame, 13, 0, 10, 14);
   outputLay =  new QGridLayout(outputFrame);

   QLabel *label = new QLabel("Output:");
   outputLay->addWidget(label, 0, 0, 1, 2);
   outPutDir = new QLineEdit(outputFrame);
   outputLay->addWidget(outPutDir, 0, 2, 1, 7);

   prolateResWidgetPtr = new ShaProlateResWidget(outputFrame);
   outputLay->addWidget(prolateResWidgetPtr, 1, 3, 1, 7, Qt::AlignCenter);
   prolateResWidgetPtr->hide();   
   shapeResWidget = prolateResWidgetPtr;
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
   qDebug() << 3;
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

   loadParameters();
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

   settings.setValue(tr("outPutParameters/outPutDir"), outPutDir->text());
   parFrame->saveParameters();
}

void ShaMainWidget::loadParameters()
{
   QSettings settings("AgCoelfen", "ShapeSim");
   settings.setIniCodec("UTF-8");
   outPutDir->setText(settings.value("outPutParameters/outPutDir", "").toString());
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


void ShaMainWidget::switchToProlate(bool chosen)
{
   if(chosen){


      curShapeWidget->hide();

      curShapeWidget = prolateWidgetPtr;
      curShapeWidget->show();

      shapeResWidget->hide();
      shapeResWidget = prolateResWidgetPtr;
      shapeResWidget->show();
   }
   //shapeFrameLay->addWidget(shapeWidget, 2, 0, 4, 12);

}

void ShaMainWidget::switchToOblate(bool chosen)
{
   if(chosen){
      curShapeWidget->hide();
      curShapeWidget = oblateWidgetPtr;
      curShapeWidget->show();

      shapeResWidget->hide();
      shapeResWidget = oblateResWidgetPtr;
      shapeResWidget->show();
   }
   //shapeFrameLay->addWidget(shapeWidget, 2, 0, 4, 12);
}

void ShaMainWidget::switchToLongRod(bool chosen)
{
   if(chosen){
      curShapeWidget->hide();
      curShapeWidget = longRodWidgetPtr;
      curShapeWidget->show();

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

   if(prolateSwitch->isChecked()) {
      QVector<ldouble> axAlpha;
      QVector<ldouble> axBeta;
      QVector<QVector<ldouble> > chiSqD;
      QVector<QVector<ldouble> > chiSqS;
      QVector<QVector<ldouble> > chiSqLam;

      ShaProlateCalculator prolateCalculator(
               outPutDir->text(),
               prolateWidgetPtr->getGridParameters(),
               parFrame->getPhysicalParameters(),
               parFrame->getMeasurementParameters(),
               gnuPlotFrame->useGnuplot(),
               gnuPlotFrame->gnuplotPath()
               );

      prolateCalculator.start(axAlpha, axBeta, chiSqD, chiSqS, chiSqLam);

      //outRhoBox->setText(QString::number(densParticle[minChiSqPos],'f', 2));
      //outChiSqBox->setText(QString::number(minChiSq,'f', 5));

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
               longRodWidgetPtr->getGridParameters(),
               parFrame->getPhysicalParameters(),
               parFrame->getMeasurementParameters(),
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

            MeasurementParamaters measPars {
               true, //parFrame->useDiffCoeff(),
               true,// parFrame->useSedCoeff(),
               false, //parFrame->useLSPRLambda(),
               false, //parFrame->useDiffCoeffDev(),
               false, //parFrame->useSedCoeffDev(),
               false, //parFrame->useLSPRLambaDev()
               false, //parFrame->useTrackDensity(),
               distD[i],  //parFrame->getDiffCoeff(),
               distS[i],  //parFrame->getSedCoeff(),
               0.0,// parFrame->getLSPRLambda(),
               0.0,//parFrame->getDiffCoeffDev(),
               0.0,//parFrame->getSedCoeffDev(),
               0.0,//parFrame->getLSPRLambdaDev(),
            };

            ShaProlateCalculator prolateCalculator(
                     outPutDir->text()
                     .append(tr("D_%1").arg(QString::number(static_cast<double>(distD[i]), 'e', 5)))
                     .append(tr("s_%1").arg(QString::number(static_cast<double>(distS[i]), 'e', 5))),
                     //strideBox->currentText().toDouble(),
                     prolateWidgetPtr->getGridParameters(),
                     //surfLayerThicknessBox->value(),
                     parFrame->getPhysicalParameters(),
                     measPars,
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

            MeasurementParamaters measPars {
               true, //parFrame->useDiffCoeff(),
               true,// parFrame->useSedCoeff(),
               false, //parFrame->useLSPRLambda(),
               false, //parFrame->useDiffCoeffDev(),
               false, //parFrame->useSedCoeffDev(),
               false, //parFrame->useLSPRLambaDev()
               false, //parFrame->useTrackDensity(),
               distD[i],  //parFrame->getDiffCoeff(),
               distS[i],  //parFrame->getSedCoeff(),
               0.0,// parFrame->getLSPRLambda(),
               0.0,//parFrame->getDiffCoeffDev(),
               0.0,//parFrame->getSedCoeffDev(),
               0.0,//parFrame->getLSPRLambdaDev(),
            };

            ShaLongRodCalculator longRodCalculator(
                     outPutDir->text()
                     .append(tr("D_%1").arg(QString::number(static_cast<double>(distD[i]), 'e', 5)))
                     .append(tr("s_%1").arg(QString::number(static_cast<double>(distS[i]), 'e', 5))),
                     longRodWidgetPtr->getGridParameters(),
                     parFrame->getPhysicalParameters(),
                     measPars,
                     gnuPlotFrame->useGnuplot(),
                     gnuPlotFrame->gnuplotPath()
                     );
            longRodCalculator.start(axAlpha[i], axBeta[i], chiSqD[i], chiSqS[i], chiSqLam[i]);
         }
      }
   }

   // find minima for each distribution


   vector<vector<doublePair>> minD = extractMinLines(chiSqD, axAlpha, axBeta);
   vector<vector<doublePair>> minS = extractMinLines(chiSqS, axAlpha, axBeta);
   vector<vector<doublePair>> minLam = extractMinLines(chiSqLam, axAlpha, axBeta);

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
