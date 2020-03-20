#ifndef SHASHAPEPARWIDGETS_H
#define SHASHAPEPARWIDGETS_H

#include <QtGlobal>
#include <QSettings>
#include "./shadefinitions.h"
#include "./shaparamstructs.h"
#include "./shalog_omp.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QComboBox>
#include <functional>

/*
class ShaGridDataWidget : public QWidget {
   Q_OBJECT
public:
   ShaShapeParWidget(QWidget *parent = nullptr);


private:
   NO_COPY_ASSIGNMENT_CTORS(ShaShapeParWidget)
}
*/

class ShaShapeParWidget : public QWidget {
   Q_OBJECT
public:
  ShaShapeParWidget(const QString &shapeID, QWidget *parent = nullptr);

   inline GridParameters getGridParameters(){
      return GridParameters {
         .alphaMin = axAlphaMinBox->value(),
         .alphaMax = axAlphaMaxBox->value(),
         .betaMin = axAlphaMinBox->value(),
         .betaMax = axBetaMaxBox->value(),
         .gridResolution = strideBox->currentText().toDouble()
      };
   }

protected:

   inline ldouble getAxAlphaMin() const {return axAlphaMinBox->value();}
   inline void setAxAlphaMin(const ldouble val) {axAlphaMinBox->setValue(val);}
   inline ldouble getAxAlphaMax() const {return axAlphaMaxBox->value();}
   inline void setAxAlphaMax(const ldouble val) {axAlphaMaxBox->setValue(val);}
   inline ldouble getAxBetaMin() const {return axBetaMinBox->value();}
   inline void setAxBetaMin(const ldouble val) {axBetaMinBox->setValue(val);}
   inline ldouble getAxBetaMax() const {return axBetaMaxBox->value();}
   inline void setAxBetaMax(const ldouble val) {axBetaMaxBox->setValue(val);}

   ~ShaShapeParWidget(){ writeSettings(); }

   QGridLayout    *shapeLay;
   QDoubleSpinBox *axAlphaMinBox;
   QDoubleSpinBox *axAlphaMaxBox;
   QDoubleSpinBox *axBetaMinBox;
   QDoubleSpinBox *axBetaMaxBox;
   QComboBox *strideBox;

   const QString shapeID;

protected slots:
   void ensureAlphaMinDistance( double AlphaMax);
   void ensureAlphaMaxDistance( double AlphMin);
   void ensureBetaMinDistance( double BetaMax);
   void ensureBetaMaxDistance( double BetaMin);

private:

   void loadSettings();
   void writeSettings();

   NO_COPY_ASSIGNMENT_CTORS(ShaShapeParWidget)
};
/*
class ShaProlateParWidget : public ShaShapeParWidget {
   Q_OBJECT
public:
   ShaProlateParWidget(const QString &shapeID, QWidget *parent = 0);
   ~ShaProlateParWidget(){}

private:
   NO_COPY_ASSIGNMENT_CTORS(ShaProlateParWidget)
};

class ShaOblateParWidget : public ShaShapeParWidget {
   Q_OBJECT
public:
   ShaOblateParWidget(const QString &shapeID, QWidget *parent = 0);
   ~ShaOblateParWidget(){}

private:
   NO_COPY_ASSIGNMENT_CTORS(ShaOblateParWidget)
};

class ShaLongRodParWidget : public ShaShapeParWidget {
   Q_OBJECT
public:
   ShaLongRodParWidget(const QString &shapeID, QWidget *parent = 0);
   ~ShaLongRodParWidget(){}

private:
   NO_COPY_ASSIGNMENT_CTORS(ShaLongRodParWidget)
};
*/
#endif // SHASHAPEPARWIDGETS_H
