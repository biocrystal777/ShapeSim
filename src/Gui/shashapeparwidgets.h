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
         .gridResolution = gridResBox->currentText().toDouble()
      };
   }

protected:

   inline void setAxAlphaMin(const ldouble val) {axAlphaMinBox->setValue(val);}
   inline void setAxAlphaMax(const ldouble val) {axAlphaMaxBox->setValue(val);}
   inline void setAxBetaMin(const ldouble val)  {axBetaMinBox->setValue(val);}
   inline void setAxBetaMax(const ldouble val)  {axBetaMaxBox->setValue(val);}

   ~ShaShapeParWidget(){ writeSettings(); }

   QGridLayout    *shapeLay      = nullptr;
   QDoubleSpinBox *axAlphaMinBox = nullptr;
   QDoubleSpinBox *axAlphaMaxBox = nullptr;
   QDoubleSpinBox *axBetaMinBox  = nullptr;
   QDoubleSpinBox *axBetaMaxBox  = nullptr;
   QComboBox      *gridResBox    = nullptr;

   const QString shapeID;

protected slots:
   void ensureAlphaMinDistance(double AlphaMax);
   void ensureAlphaMaxDistance(double AlphMin);
   void ensureBetaMinDistance(double BetaMax);
   void ensureBetaMaxDistance(double BetaMin);

private:
   void loadSettings();
   void writeSettings();

   NO_COPY_ASSIGNMENT_CTORS(ShaShapeParWidget)
};

#endif // SHASHAPEPARWIDGETS_H
