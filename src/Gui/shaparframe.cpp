#include "shaparframe.h"
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include "./shalog_omp.h"

ShaParFrame::ShaParFrame(QWidget *parent, Qt::WindowFlags f) : QFrame(parent, f){

   this->setFrameStyle(0x1011);
   //this->setMinimumSize(620, 350);
   //this->setMaximumSize(620, 350);

   lay = new QGridLayout(this);

   QLabel *label = new QLabel(this);
   label->setText(tr("ρ<sub>core</sub> [g/ml]:"));
   lay->addWidget(label, 0, 0, 1, 3, Qt::AlignLeft);
   coreDensityBox = new QDoubleSpinBox(this);
   coreDensityBox->setDecimals(4);
   lay->addWidget(coreDensityBox, 0, 3, 1, 4);

   label = new QLabel(this);
   label->setText(tr("ρ<sub>surf</sub> [g/ml]:"));
   lay->addWidget(label, 1, 0, 1, 3, Qt::AlignLeft);
   surfDensityBox = new QDoubleSpinBox(this);
   surfDensityBox->setDecimals(4);
   lay->addWidget(surfDensityBox, 1, 3, 1, 4);

   label = new QLabel(this);
   label->setText(tr("ρ<sub>solv</sub> [g/ml]:"));
   lay->addWidget(label, 2, 0, 1, 3, Qt::AlignLeft);
   solvDensityBox = new QDoubleSpinBox(this);
   solvDensityBox->setDecimals(4);
   lay->addWidget(solvDensityBox, 2, 3, 1, 4);

   label = new QLabel(this);
   label->setText(tr("η<sub>solvent</sub> [cP]:"));
   lay->addWidget(label, 3, 0, 1, 3, Qt::AlignLeft);
   viscSolvBox = new QDoubleSpinBox(this);
   viscSolvBox->setDecimals(4);
   lay->addWidget(viscSolvBox, 3, 3, 1, 4);

   label = new QLabel(this);
   label->setText(tr("T [K]:"));
   lay->addWidget(label, 4, 0, 1, 3, Qt::AlignLeft);
   temperatureBox = new QDoubleSpinBox(this);
   temperatureBox->setMinimum(100.0);
   temperatureBox->setMaximum(500.0);
   lay->addWidget(temperatureBox, 4, 3, 1, 4);

   singDistSwitchBox = new QGroupBox(QString("Evaluation Mode"), this);
   lay->addWidget(singDistSwitchBox, 5, 0, 2, 10);

   singleSDPairWidget = new ShaSingleSDPairWidget(this);

   distSDPairWidget = new ShaDistrSDPairWidget(this);
   distSDPairWidget->hide();
   lay->addWidget(singleSDPairWidget, 7, 0, 5, 10);
   lay->addWidget(distSDPairWidget, 7, 0, 5, 10);

   singleSwitcher = new QRadioButton("Single Values", singleSDPairWidget);
   distrSwitcher = new QRadioButton("Distributions", singleSDPairWidget);
   singDistLay = new QHBoxLayout(singDistSwitchBox);
   singDistLay->addWidget(singleSwitcher);
   singDistLay->addWidget(distrSwitcher);
   singleSwitcher->setChecked(true);

   QObject::connect(singleSwitcher, SIGNAL(toggled(bool)), this, SLOT(switchToSing(bool)));
   QObject::connect(distrSwitcher, SIGNAL(toggled(bool)), this, SLOT(switchToDist(bool)));


   loadParameters();
}

ShaParFrame::~ShaParFrame(){

}

void ShaParFrame::loadParameters()
{
   bool ok(false);
   ldouble initdouble(0.0);
   //int initInt(0);
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

   INIT_PARAMETER_LDOUBLE("expSettings/density_Core", coreDensityBox, "10.0");
   INIT_PARAMETER_LDOUBLE("expSettings/density_Surf", surfDensityBox, "10.0");
   INIT_PARAMETER_LDOUBLE("expSettings/density_Solvent", solvDensityBox, "10.0");
   INIT_PARAMETER_LDOUBLE("expSettings/viscosity_Solvent", viscSolvBox, "10.0");
   INIT_PARAMETER_LDOUBLE("expSettings/Temperature", temperatureBox, "300.0");

#undef INIT_PARAMETER_LDOUBLE

   //singleSDPairWidget->loadParameters();
}

void ShaParFrame::saveParameters() const
{
   QSettings settings("AgCoelfen", "ShapeSim");
   settings.setIniCodec("UTF-8");

   settings.setValue(tr("expSettings/density_Core"), coreDensityBox->value());
   settings.setValue(tr("expSettings/density_Surf"), surfDensityBox->value());
   settings.setValue(tr("expSettings/density_Solvent"), solvDensityBox->value());
   settings.setValue(tr("expSettings/viscosity_Solvent"), viscSolvBox->value());
   settings.setValue(tr("expSettings/Temperature"), temperatureBox->value());

   if(singleSDPairWidget) singleSDPairWidget->saveParameters();
}

void ShaParFrame::switchToSing(bool chosen)
{
   if(chosen){
      singleSDPairWidget->show();
      distSDPairWidget->hide();
   }
}

void ShaParFrame::switchToDist(bool chosen)
{
   if(chosen){
      distSDPairWidget->show();
      singleSDPairWidget->hide();
   }
}

ShaSingleSDPairWidget::ShaSingleSDPairWidget(QWidget *parent, Qt::WindowFlags f) : QWidget(parent, f)
{
   lay = new QGridLayout(this);

   useDBox = new QCheckBox(this);
   useDBox->setChecked(true);
   QObject::connect(useDBox, SIGNAL(toggled(bool)), this, SLOT(toggleD(bool)));
   lay->addWidget(useDBox, 0, 0, 1, 1);

   QLabel *label = new QLabel(this);
   label->setText(tr("D<sub>meas</sub>[cm<sup>2</sup>/min]:"));
   lay->addWidget(label, 0, 1, 1, 2, Qt::AlignLeft);
   diffCoeffBox = new FFFTwoBoxWidget(this);
   lay->addWidget(diffCoeffBox, 0, 3, 1, 4);

   label = new QLabel(this);
   label->setText(tr("+-"));
   lay->addWidget(label, 0, 7, 1, 1);
   diffCoeffDevBox = new FFFTwoBoxWidget(this);
   lay->addWidget(diffCoeffDevBox, 0, 8, 1, 4);

   useDDevBox = new QCheckBox(this);
   useDDevBox->setChecked(true);
   QObject::connect(useDDevBox, SIGNAL(toggled(bool)), this, SLOT(toggleDevD(bool)));
   lay->addWidget(useDDevBox, 0, 12, 1, 1);



   useSBox = new QCheckBox(this);
   useSBox->setChecked(true);
   QObject::connect(useSBox, SIGNAL(toggled(bool)), this, SLOT(toggleS(bool)));
   lay->addWidget(useSBox, 1, 0, 1, 1);

   label = new QLabel(this);
   label->setText(tr("s<sub>meas</sub> [S]:"));
   lay->addWidget(label, 1, 1, 1, 2, Qt::AlignLeft);
   sedCoeffBox = new FFFTwoBoxWidget(this);
   lay->addWidget(sedCoeffBox, 1, 3, 1, 4);

   label = new QLabel(this);
   label->setText(tr("+-"));
   lay->addWidget(label, 1, 7, 1, 1, Qt::AlignLeft);
   sedCoeffDevBox = new FFFTwoBoxWidget(this);
   lay->addWidget(sedCoeffDevBox, 1, 8, 1, 4);

   useSDevBox = new QCheckBox(this);
   useSDevBox->setChecked(true);
   QObject::connect(useSDevBox, SIGNAL(toggled(bool)), this, SLOT(toggleDevS(bool)));
   lay->addWidget(useSDevBox, 1, 12, 1, 4);

   useSDevBox = new QCheckBox(this);
   useSDevBox->setChecked(true);
   QObject::connect(useSDevBox, SIGNAL(toggled(bool)), this, SLOT(toggleDevS(bool)));
   lay->addWidget(useSDevBox, 1, 12, 1, 4);

   trackDensityBox = new QCheckBox(this);
   trackDensityBox->setChecked(true);
   lay->addWidget(trackDensityBox, 2, 0, 1, 1);
   label = new QLabel(this);
   label->setText(tr("track density"));
   lay->addWidget(label, 2, 1, 1, 4, Qt::AlignLeft);



   useLamBox = new QCheckBox(this);
   useLamBox->setChecked(true);
   QObject::connect(useLamBox, SIGNAL(toggled(bool)), this, SLOT(toggleLam(bool)));
   lay->addWidget(useLamBox, 3, 0, 1, 1);

   label = new QLabel(this);
   label->setText(tr("λ<sub>meas</sub> [nm]:"));
   lay->addWidget(label, 3, 1, 1, 3, Qt::AlignLeft);
   waveLengthBox = new QDoubleSpinBox(this);
   waveLengthBox->setMinimum(100);
   waveLengthBox->setMaximum(1000);
   lay->addWidget(waveLengthBox, 3, 4, 1, 3);

   label = new QLabel(this);
   label->setText(tr("+-"));
   lay->addWidget(label, 3, 7, 1, 1, Qt::AlignLeft);
   waveLengthDevBox = new QDoubleSpinBox(this);
   lay->addWidget(waveLengthDevBox, 3, 8, 1, 3);

   useLamDevBox = new QCheckBox(this);
   useLamDevBox->setChecked(true);
   QObject::connect(useLamDevBox, SIGNAL(toggled(bool)), this, SLOT(toggleDevLam(bool)));
   lay->addWidget(useLamDevBox, 3, 11, 1, 3);

   loadParameters();
}

ShaSingleSDPairWidget::~ShaSingleSDPairWidget()
{

}

void ShaSingleSDPairWidget::loadParameters()
{
   QSettings settings("AgCoelfen", "ShapeSim");
   settings.setIniCodec("UTF-8");
   bool ok(false);
   double initdouble(0.0);

#ifndef INIT_PARAMETER_LDOUBLE
#define INIT_PARAMETER_LDOUBLE(keyName, widgetPtr, defaultValue){ \
   initdouble = settings.value(tr(keyName), defaultValue).toDouble(&ok); \
   if(!ok){ \
   ShaLog::logWarning(tr("Could not read parameter %1 from iniFile. Value will be set to %2") \
   .arg(keyName).arg(defaultValue)); \
}\
   widgetPtr->setValue(initdouble); \
};
#endif

   INIT_PARAMETER_LDOUBLE("expSettings/D_meas", diffCoeffBox, "300.0");
   INIT_PARAMETER_LDOUBLE("expSettings/S_meas", sedCoeffBox, "300.0");
   INIT_PARAMETER_LDOUBLE("expSettings/lambda_meas", waveLengthBox, "500.0");
   INIT_PARAMETER_LDOUBLE("expSettings/D_measDev", diffCoeffDevBox, "300.0");
   INIT_PARAMETER_LDOUBLE("expSettings/S_measDev", sedCoeffDevBox, "300.0");
   INIT_PARAMETER_LDOUBLE("expSettings/lambda_measDev", waveLengthDevBox, "500.0");

#undef INIT_PARAMETER_LDOUBLE
}

void ShaSingleSDPairWidget::saveParameters() const
{
   QSettings settings("AgCoelfen", "ShapeSim");
   settings.setIniCodec("UTF-8");

   settings.setValue(tr("expSettings/D_meas"), static_cast<double>(diffCoeffBox->value()));
   settings.setValue(tr("expSettings/S_meas"), static_cast<double>(sedCoeffBox->value()));
   settings.setValue(tr("expSettings/lambda_meas"), static_cast<double>(waveLengthBox->value()));
   settings.setValue(tr("expSettings/D_measDev"), static_cast<double>(diffCoeffDevBox->value()));
   settings.setValue(tr("expSettings/S_measDev"), static_cast<double>(sedCoeffDevBox->value()));
   settings.setValue(tr("expSettings/lambda_measDev"), static_cast<double>(waveLengthDevBox->value()));
}

void ShaSingleSDPairWidget::toggleD(bool on)
{
   if(diffCoeffBox) diffCoeffBox->setEnabled(on);
   if(useDDevBox){
      if(on){
         toggleDevD(useDDevBox->isChecked());
         useDDevBox->setEnabled(true);
      }
      else {
         toggleDevD(false);
         useDDevBox->setEnabled(false);
      }
   }
}

void ShaSingleSDPairWidget::toggleS(bool on)
{
   if(sedCoeffBox) sedCoeffBox->setEnabled(on);
   if(trackDensityBox) trackDensityBox->setEnabled(on);
   if(useSDevBox){
      if(on){
         toggleDevS(useSDevBox->isChecked());
         useSDevBox->setEnabled(true);

      }
      else {
         toggleDevS(false);
         useSDevBox->setEnabled(false);
      }
   }
}

void ShaSingleSDPairWidget::toggleLam(bool on)
{
   if(waveLengthBox) waveLengthBox->setEnabled(on);
   if(useLamDevBox){
      if(on){
         toggleDevLam(useLamDevBox->isChecked());
         useLamDevBox->setEnabled(true);
      }
      else {
         toggleDevLam(false);
         useLamDevBox->setEnabled(false);
      }
   }
}

void ShaSingleSDPairWidget::toggleDevD(bool on)
{
   if(diffCoeffDevBox && diffCoeffBox) diffCoeffDevBox->setEnabled(on);

}

void ShaSingleSDPairWidget::toggleDevS(bool on)
{
   if(sedCoeffDevBox) sedCoeffDevBox->setEnabled(on);
}

void ShaSingleSDPairWidget::toggleDevLam(bool on)
{
   if(waveLengthDevBox) waveLengthDevBox->setEnabled(on);
}


ShaDistrSDPairWidget::ShaDistrSDPairWidget(QWidget *parent, Qt::WindowFlags f) : QWidget(parent, f)
{
   lay = new QGridLayout(this);
   QLabel *label = new QLabel("File Path:", this);
   lay->addWidget(label, 1,0,1,2);

   filePathChooser = new QToolButton(this);
   filePathChooser->setText("..");
   filePathChooser->setToolTip("Browse Files");
   QObject::connect(filePathChooser, SIGNAL(clicked()), this, SLOT(chooseFilePath()));
   lay->addWidget(filePathChooser, 2,0,2,1);

   filePath = new QLineEdit(this);
   lay->addWidget(filePath, 2,1,2,5);
   loadParameters();
}

ShaDistrSDPairWidget::~ShaDistrSDPairWidget()
{
   saveParameters();
}

void ShaDistrSDPairWidget::loadParameters()
{
   QSettings settings("AgCoelfen", "ShapeSim");
   settings.setIniCodec("UTF-8");
   QString stringValue = settings.value(tr("expSettings/distr/filepath"), "").toString();
   setInputFilePath(stringValue, true);
}

bool ShaDistrSDPairWidget::setInputFilePath(QString path, bool quoted)
{
   bool ok(true);
   QString testPath = path;
   chopStringsQuotMarksEntirely(testPath);
   if(!QFile::exists(testPath)){
      path = QDir::homePath();
      path.prepend('"');
      path.append('"');
      ok = false;
   }
   else {
      if(quoted) chopStringsQuotMarksToOne(path);
      else chopStringsQuotMarksEntirely(path);
      filePath->setText(path);
   }
   return ok;
}


void ShaDistrSDPairWidget::saveParameters()
{
   QSettings settings("AgCoelfen", "ShapeSim");
   settings.setIniCodec("UTF-8");
   settings.setValue(tr("expSettings/distr/filepath"), filePath->text());
}

void ShaDistrSDPairWidget::chooseFilePath()
{
   QString s;
   QString oldInputFile = filePath->text();
   if(!QFile::exists(oldInputFile)) oldInputFile = QDir::homePath();
   s = QFileDialog::getOpenFileName(this, tr("Choose a File to evaluate"), oldInputFile,
                                    QString(), nullptr,
                                    ( QFileDialog::DontConfirmOverwrite |
                                      QFileDialog::ReadOnly |
                                      QFileDialog::HideNameFilterDetails )
                                    );
   if(QFile::exists(s)) filePath->setText(chopStringsQuotMarksToOne(s));
   else ShaLog::logWarning(tr("Chosen input file does not exist."));
}

QString ShaDistrSDPairWidget::getDistrFilePath(bool quoted) const {
   QString path = filePath->text();
   if(quoted)
      chopStringsQuotMarksToOne(path);
   else
      chopStringsQuotMarksEntirely(path);
    return path;
}


QString ShaDistrSDPairWidget::chopStringsQuotMarksToOne(QString & string) const
{
#if QT_VERSION >= 0x05000
   chopStringsQuotMarksEntirely(string);
   string.prepend('\"');
   string.append('\"');
#else
   const QChar compChar('\"');
   uint stringLength = string.length();
   if(stringLength < 5)
      return QString("");
   while(string.at(1) == compChar){
      string.remove(0, 1);
   }
   stringLength = string.length();

   while(string.at(stringLength - 2).toAscii() == compChar.toAscii()){
      string.remove(stringLength - 1, 1);
      stringLength = string.length();
   }
   stringLength = string.length();
   if(string.at(0).toAscii() != compChar.toAscii()) string.prepend(compChar);
   if(string.at(stringLength - 1).toAscii() != compChar.toAscii()) string.append((compChar));
#endif
   return string;
}

QString ShaDistrSDPairWidget::chopStringsQuotMarksEntirely(QString & string) const
{
#if QT_VERSION >= 0x05000
   const QChar quotMark('\"');
   while(!string.isEmpty() && string.at(0) == quotMark)
      string.remove(0, 1);
   while(!string.isEmpty() && string.at(string.length()-1) == quotMark)
      string.remove(string.length()-1, 1);

#else
   const QChar compChar('\"');
   uint stringLength = string.length();
   int removed=0;
   for(int i = 0; i < stringLength; ++i)
      if(string.at(i-removed).toAscii() == compChar.toAscii()){
         string.remove(i-removed, 1);
         ++removed;
      }
#endif
   return string;
}
