#ifndef SHASHAPEPARWIDGETS_H
#define SHASHAPEPARWIDGETS_H

#include <QtGlobal>
#include "./shadefinitions.h"

#if QT_VERSION < 0x050000
#include <QWidget>
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#else
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#endif


class ShaShapeParWidget : public QWidget {
   Q_OBJECT
public:
   ShaShapeParWidget(QWidget *parent = 0) : QWidget(parent){
      shapeLay = new QGridLayout(this);
      QLabel *label = new QLabel(tr("<b>Limits:</b>"), this);
      shapeLay->addWidget(label, 0, 1, 1, 3, Qt::AlignCenter);
   }
   ShaShapeParWidget(const ShaShapeParWidget& src) = delete;
   ShaShapeParWidget& operator= (ShaShapeParWidget& src) = delete;
   ShaShapeParWidget(ShaShapeParWidget&& src) = delete;
   ShaShapeParWidget& operator= (ShaShapeParWidget&& src) = delete;
protected:
   virtual ~ShaShapeParWidget(){}
   QGridLayout *shapeLay;
};

class ShaSphereParWidget : public ShaShapeParWidget {
   Q_OBJECT
public:
   ShaSphereParWidget(QWidget *parent = 0);
   ~ShaSphereParWidget(){}
   ShaSphereParWidget(const ShaSphereParWidget& src) = delete;
   ShaSphereParWidget& operator= (ShaSphereParWidget& src) = delete;
   ShaSphereParWidget(ShaSphereParWidget&& src) = delete;
   ShaSphereParWidget& operator= (ShaSphereParWidget&& src) = delete;

   inline ldouble getRadMin() const {return radMinBox->value();}
   inline void setRadMin(const ldouble val) {radMinBox->setValue(val);}
   inline ldouble getRadMax() const {return radMaxBox->value();}
   inline void setRadMax(const ldouble val) {radMaxBox->setValue(val);}

protected:
   QDoubleSpinBox *radMinBox;
   QDoubleSpinBox *radMaxBox;

protected slots:
   void ensureRadMinDistance( double radMax);
   void ensureRadMaxDistance( double radMin);
};

class ShaProlateParWidget : public ShaShapeParWidget {
   Q_OBJECT
public:
   ShaProlateParWidget(QWidget *parent = 0);
   ~ShaProlateParWidget(){}
   ShaProlateParWidget(const ShaProlateParWidget& src) = delete;
   ShaProlateParWidget& operator= (ShaProlateParWidget& src) = delete;
   ShaProlateParWidget(ShaProlateParWidget&& src) = delete;
   ShaProlateParWidget& operator= (ShaProlateParWidget&& src) = delete;

   inline ldouble getAxAlphaMin() const {return axAlphaMinBox->value();}
   inline void setAxAlphaMin(const ldouble val) {axAlphaMinBox->setValue(val);}
   inline ldouble getAxAlphaMax() const {return axAlphaMaxBox->value();}
   inline void setAxAlphaMax(const ldouble val) {axAlphaMaxBox->setValue(val);}
   inline ldouble getAxBetaMin() const {return axBetaMinBox->value();}
   inline void setAxBetaMin(const ldouble val) {axBetaMinBox->setValue(val);}
   inline ldouble getAxBetaMax() const {return axBetaMaxBox->value();}
   inline void setAxBetaMax(const ldouble val) {axBetaMaxBox->setValue(val);}

protected:
   QDoubleSpinBox *axAlphaMinBox;
   QDoubleSpinBox *axAlphaMaxBox;
   QDoubleSpinBox *axBetaMinBox;
   QDoubleSpinBox *axBetaMaxBox;

protected slots:
   void ensureAlphaMinDistance( double AlphaMax);
   void ensureAlphaMaxDistance( double AlphMin);
   void ensureBetaMinDistance( double BetaMax);
   void ensureBetaMaxDistance( double BetaMin);
};

class ShaOblateParWidget : public ShaShapeParWidget {
   Q_OBJECT
public:
   ShaOblateParWidget(QWidget *parent = 0);
   ~ShaOblateParWidget(){}
   ShaOblateParWidget(const ShaOblateParWidget& src) = delete;
   ShaOblateParWidget& operator= (ShaOblateParWidget& src) = delete;
   ShaOblateParWidget(ShaOblateParWidget&& src) = delete;
   ShaOblateParWidget& operator= (ShaOblateParWidget&& src) = delete;

   inline ldouble getAxAlphaMin() const {return axAlphaMinBox->value();}
   inline void setAxAlphaMin(const ldouble val) {axAlphaMinBox->setValue(val);}
   inline ldouble getAxAlphaMax() const {return axAlphaMaxBox->value();}
   inline void setAxAlphaMax(const ldouble val) {axAlphaMaxBox->setValue(val);}
   inline ldouble getAxBetaMin() const {return axBetaMinBox->value();}
   inline void setAxBetaMin(const ldouble val) {axBetaMinBox->setValue(val);}
   inline ldouble getAxBetaMax() const {return axBetaMaxBox->value();}
   inline void setAxBetaMax(const ldouble val) {axBetaMaxBox->setValue(val);}

protected:
   QDoubleSpinBox *axAlphaMinBox;
   QDoubleSpinBox *axAlphaMaxBox;
   QDoubleSpinBox *axBetaMinBox;
   QDoubleSpinBox *axBetaMaxBox;

   protected slots:
   void ensureAlphaMinDistance( double AlphaMax);
   void ensureAlphaMaxDistance( double AlphMin);
   void ensureBetaMinDistance( double BetaMax);
   void ensureBetaMaxDistance( double BetaMin);
};

class ShaLongRodParWidget : public ShaShapeParWidget {
   Q_OBJECT
public:
   ShaLongRodParWidget(QWidget *parent = 0);
   ~ShaLongRodParWidget(){}
   ShaLongRodParWidget(const ShaLongRodParWidget& src) = delete;
   ShaLongRodParWidget& operator= (ShaLongRodParWidget& src) = delete;
   ShaLongRodParWidget(ShaLongRodParWidget&& src) = delete;
   ShaLongRodParWidget& operator= (ShaLongRodParWidget&& src) = delete;

   inline ldouble getAxAlphaMin() const {return axAlphaMinBox->value();}
   inline void setAxAlphaMin(const ldouble val) {axAlphaMinBox->setValue(val);}
   inline ldouble getAxAlphaMax() const {return axAlphaMaxBox->value();}
   inline void setAxAlphaMax(const ldouble val) {axAlphaMaxBox->setValue(val);}
   inline ldouble getAxBetaMin() const {return axBetaMinBox->value();}
   inline void setAxBetaMin(const ldouble val) {axBetaMinBox->setValue(val);}
   inline ldouble getAxBetaMax() const {return axBetaMaxBox->value();}
   inline void setAxBetaMax(const ldouble val) {axBetaMaxBox->setValue(val);}

protected:
   QDoubleSpinBox *axAlphaMinBox;
   QDoubleSpinBox *axAlphaMaxBox;
   QDoubleSpinBox *axBetaMinBox;
   QDoubleSpinBox *axBetaMaxBox;

   protected slots:
   void ensureAlphaMinDistance( double AlphaMax);
   void ensureAlphaMaxDistance( double AlphMin);
   void ensureBetaMinDistance( double BetaMax);
   void ensureBetaMaxDistance( double BetaMin);
};

#endif // SHASHAPEPARWIDGETS_H
