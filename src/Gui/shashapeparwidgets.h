#ifndef SHASHAPEPARWIDGETS_H
#define SHASHAPEPARWIDGETS_H

#include <QtGlobal>
#include "./shadefinitions.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>

class ShaShapeParWidget : public QWidget {
   Q_OBJECT
public:
  ShaShapeParWidget(QWidget *parent = nullptr);

   inline ldouble getAxAlphaMin() const {return axAlphaMinBox->value();}
   inline void setAxAlphaMin(const ldouble val) {axAlphaMinBox->setValue(val);}
   inline ldouble getAxAlphaMax() const {return axAlphaMaxBox->value();}
   inline void setAxAlphaMax(const ldouble val) {axAlphaMaxBox->setValue(val);}
   inline ldouble getAxBetaMin() const {return axBetaMinBox->value();}
   inline void setAxBetaMin(const ldouble val) {axBetaMinBox->setValue(val);}
   inline ldouble getAxBetaMax() const {return axBetaMaxBox->value();}
   inline void setAxBetaMax(const ldouble val) {axBetaMaxBox->setValue(val);}

protected:
   virtual ~ShaShapeParWidget(){}

   QGridLayout    *shapeLay;
   QDoubleSpinBox *axAlphaMinBox;
   QDoubleSpinBox *axAlphaMaxBox;
   QDoubleSpinBox *axBetaMinBox;
   QDoubleSpinBox *axBetaMaxBox;

private:
   NO_COPY_ASSIGNMENT_CTORS(ShaShapeParWidget)
};

class ShaProlateParWidget : public ShaShapeParWidget {
   Q_OBJECT
public:
   ShaProlateParWidget(QWidget *parent = 0);
   ~ShaProlateParWidget(){}

protected slots:
   void ensureAlphaMinDistance( double AlphaMax);
   void ensureAlphaMaxDistance( double AlphMin);
   void ensureBetaMinDistance( double BetaMax);
   void ensureBetaMaxDistance( double BetaMin);

private:
   NO_COPY_ASSIGNMENT_CTORS(ShaProlateParWidget)
};

class ShaOblateParWidget : public ShaShapeParWidget {
   Q_OBJECT
public:
   ShaOblateParWidget(QWidget *parent = 0);
   ~ShaOblateParWidget(){}

protected slots:
   void ensureAlphaMinDistance( double AlphaMax);
   void ensureAlphaMaxDistance( double AlphMin);
   void ensureBetaMinDistance( double BetaMax);
   void ensureBetaMaxDistance( double BetaMin);

private:

   NO_COPY_ASSIGNMENT_CTORS(ShaOblateParWidget)
};

class ShaLongRodParWidget : public ShaShapeParWidget {
   Q_OBJECT
public:
   ShaLongRodParWidget(QWidget *parent = 0);
   ~ShaLongRodParWidget(){}

   protected slots:
   void ensureAlphaMinDistance( double AlphaMax);
   void ensureAlphaMaxDistance( double AlphMin);
   void ensureBetaMinDistance( double BetaMax);
   void ensureBetaMaxDistance( double BetaMin);

private:
   NO_COPY_ASSIGNMENT_CTORS(ShaLongRodParWidget)
};

#endif // SHASHAPEPARWIDGETS_H
