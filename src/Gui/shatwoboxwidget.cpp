#include "shatwoboxwidget.h"

FFFTwoBoxWidget::FFFTwoBoxWidget(const QString &toolTipString, QWidget *parent) :
   QWidget(parent)
{


   setToolTip(toolTipString);
   layout = new QHBoxLayout(this);
   significand = new QDoubleSpinBox(this);
   significand->setFixedSize(90,25);

   QObject::connect(significand, SIGNAL(valueChanged(QString)), this, SLOT(callValueChanged(QString)));
   layout->addWidget(significand, 0, Qt::AlignLeft);
   layout->addWidget(new QLabel("E", this), 0);
   exponent = new QSpinBox(this);
   exponent->setFixedSize(40, 25);
   QObject::connect(exponent, SIGNAL(valueChanged(QString)), this, SLOT(callValueChanged(QString)));
   significand->setSingleStep(0.01);
   significand->setDecimals(5);
   significand->setRange(1.0, 9.99999);
   exponent->setRange(-20, 20);
   layout->addWidget(exponent, 0, Qt::AlignLeft);
   layout->addStretch(4);
}

FFFTwoBoxWidget::FFFTwoBoxWidget(QWidget *parent) :
   QWidget(parent)
{
   layout = new QHBoxLayout(this);
   significand = new QDoubleSpinBox(this);
   significand->setFixedSize(90,25);

   QObject::connect(significand, SIGNAL(valueChanged(QString)), this, SLOT(callValueChanged(QString)));
   layout->addWidget(significand, 0, Qt::AlignLeft);
   layout->addWidget(new QLabel("E", this), 0);
   exponent = new QSpinBox(this);
   exponent->setFixedSize(40, 25);
   QObject::connect(exponent, SIGNAL(valueChanged(QString)), this, SLOT(callValueChanged(QString)));
   significand->setSingleStep(0.01);
   significand->setDecimals(5);
   significand->setRange(1.0, 9.99999);
   exponent->setRange(-20, 20);
   layout->addWidget(exponent, 0, Qt::AlignLeft);
   layout->addStretch(4);
}


FFFTwoBoxWidget::~FFFTwoBoxWidget()
{
}

ldouble FFFTwoBoxWidget::value() const
{

   return significand->value() * ((ldouble) std::pow(10, exponent->value()));
}

void FFFTwoBoxWidget::setValue(ldouble signif, int exp, int callID)
{

   if(( 1.0 <= std::fabs(signif)) && (std::fabs(signif) < 10.00)){
      significand->setValue(signif);
      exponent->setValue(exp);
   }
   else if ((0.0 <= signif) && (signif <= 0.0)){
      significand->setValue(0.0);
      exponent->setValue(0);
   } else {
      ShaLog::logWarning(tr("Significand was not adjusted correctly for the TwoBoxWidget:"));
      ShaLog::logWarning(tr("Significand: %1, Exponent: %2, callID: %3")
                         .arg(static_cast<double>(signif))
                         .arg(static_cast<double>(exp))
                         .arg(static_cast<double>(callID)));
   }
}

void FFFTwoBoxWidget::setValue(ldouble value)
{
   ldouble signif(0.0);
   int exp(0);
   signif = calcSignificand(value, &exp);
   setValue(signif, exp);
}

void FFFTwoBoxWidget::setMaximum(ldouble sign, int exp)
{
   maximumSign = sign;
   maximumExp = exp;
   exponent->setMaximum(exp);
   significand->setMaximum(sign);
}

void FFFTwoBoxWidget::setMinimum(ldouble sign, int exp)
{
   minimumSign = sign;
   minimumExp = exp;
   exponent->setMinimum(exp);
   significand->setMinimum(sign);
}


void FFFTwoBoxWidget::setReadOnly(bool r)
{
   significand->setReadOnly(r);
   exponent->setReadOnly(r);
}

void FFFTwoBoxWidget::callValueChanged(QString dummyArgument)
{
   valueChanged();
}


void FFFTwoBoxWidget::reNormValues(ldouble signInput)
{
   significand->blockSignals(true);

   int newExponent = exponent->value();
   if(std::fabs(signInput) > 0){
      while(signInput >= 10.0){
         signInput /= 10.0;
         newExponent++;
      }
      while(signInput < 1.0){
         signInput *= 10.0;
         newExponent--;
      }
   } else {
      newExponent = 0;
   }
   significand->setValue(signInput);
   exponent->setValue(newExponent);
   significand->blockSignals(false);
}

ldouble FFFTwoBoxWidget::calcSignificand(ldouble number, int *exponent)
{
   // remove sign for convenience and initialize exponent result:
   ldouble absNumber = std::fabs(number);
   (*exponent) = 0;
   // special cases 0.0 and -0.0 :
   if (!(absNumber > 0.0)){
      return absNumber;
   }
   // calculate, until the actual significand has an exponent = 1;
   // adjust, thereby, the  exponent of the actual number;
   while(absNumber < 1.0){
      absNumber *= 10.0;
      (*exponent)--;
   }
   int test = 0;
   while(absNumber >= 10.0){
      absNumber /= 10.0;

      (*exponent)++;

      test++;
      if (test == 20) break;
   }

   // reinsert sign:
   if(number > 0.0){
      return absNumber;
   } else {
      return -absNumber;
   }
}


void FFFTwoBoxWidget::setSignifandStep(ldouble stepSize)
{
   significand->setSingleStep(stepSize);
}

void FFFTwoBoxWidget::setSignifandDecimals(uint number)
{
   significand->setDecimals(number);
}
