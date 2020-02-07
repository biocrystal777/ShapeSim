#ifndef SHAMAINWIDGET_H
#define SHAMAINWIDGET_H

#include <QtGlobal>
#include "./shadefinitions.h"


#include <QGuiApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QCheckBox>

#include <QProcess>
#include <QSettings>
#include <QVector>
#include <QString>
#include <cmath>
#include <limits>
#include <algorithm>
#include <QFile>
#include <QDir>
/*
#include "qwt_plot_spectrogram.h"
#include "qwt_plot.h"
#include "qwt_plot_grid.h"
#include "qwt_plot_curve.h"
#include "qwt_color_map.h"
#include "qwt_raster_data.h"
*/
#include "./shatwoboxwidget.h"
#include "./shaparframe.h"
#include "./shacsvparser.h"
#include "./shashapeparwidgets.h"
#include "./shashapereswidgets.h"
#include "./shagnuplotframe.h"

#include "./shalog_omp.h"
#include <string>
#include <ostream>
#include <fstream>
#include <iomanip>

struct doublePair{
   double alpha;
   double beta;
};


class ShaMainWidget : public QWidget
{
   Q_OBJECT
public:

   ShaMainWidget(QWidget *parent = nullptr);
   ~ShaMainWidget();
   ShaMainWidget(const ShaMainWidget& src) = delete;
   ShaMainWidget& operator= (ShaMainWidget& src) = delete;
   ShaMainWidget(ShaMainWidget&& src) = delete;
   ShaMainWidget& operator= (ShaMainWidget&& src) = delete;

private:

   QGridLayout *thisLay = nullptr;
   // Input Frame Density rest
   ShaParFrame* parFrame = nullptr;

   // Shape model frame
   QFrame *shapeFrame               = nullptr;
   QGridLayout *shapeFrameLay       = nullptr;

   QDoubleSpinBox* surfLayerThicknessBox = nullptr;
   QDoubleSpinBox* solvLayerThicknessBox = nullptr;
   QComboBox *strideBox                  = nullptr;



   QGroupBox *shapeGroupBox              = nullptr;
   QGridLayout *shapeSwitchLay           = nullptr;
   QRadioButton *sphereSwitch            = nullptr;
   QRadioButton *prolateSwitch           = nullptr;
   QRadioButton *oblateSwitch            = nullptr;
   QRadioButton *longRodSwitch           = nullptr;

   ShaShapeParWidget *shapeWidget        = nullptr;
   ShaSphereParWidget *sphereWidgetPtr   = nullptr;
   ShaProlateParWidget *prolateWidgetPtr = nullptr;
   ShaOblateParWidget *oblateWidgetPtr   = nullptr;
   ShaLongRodParWidget *longRodWidgetPtr = nullptr;

   ShaGnuplotFrame *gnuPlotFrame         = nullptr;

   QPushButton *startButton              = nullptr;

   //Output Frame
   QFrame *outputFrame                   = nullptr;
   QGridLayout *outputLay                = nullptr;

   QLineEdit *outRhoBox                  = nullptr;
   QLineEdit *outPBox                    = nullptr;
   QLineEdit *outff0Box                  = nullptr;
   QLineEdit *outChiSqBox                = nullptr;
   QLineEdit *outPutDir                  = nullptr;

   ShaShapeResWidget *shapeResWidget         = nullptr;
   ShaSphereResWidget *sphereResWidgetPtr    = nullptr;
   ShaProlateResWidget *prolateResWidgetPtr  = nullptr;
   ShaOblateResWidget *oblateResWidgetPtr    = nullptr;
   ShaLongRodResWidget *longRodResWidgetPtr  = nullptr;

   // log Widget
   ShaLog *logWidget = nullptr;

   /*
  Uses Macros to load parameters:
  Macros are defined.for different data types, targeting member widgets or setter functions
  They generally are implemented using the following scheme:
  1. Fetch value from settings object
  2. Check if the conversion from QVariant (return value of settings object) worked fine
  3. write value to member widget or call setter function
*/

   void sphereCalculation(QVector<ldouble> &rad,
                          QVector<ldouble> &chiSq
                          //chiSqType minMode
                          );

   void createVectorFromTo(QVector<ldouble> &v, ldouble min, ldouble max, ldouble stride);
   int minAt(const QVector<ldouble> &v, ldouble *val = nullptr) const;

   std::vector<std::vector<doublePair>> extractMinLines(const QVector<QVector<QVector<ldouble>>> &chiPlots,
                                                        const QVector<QVector<ldouble>> &axAlpha,
                                                        const QVector<QVector<ldouble>> &axBeta ) const;

   std::vector<doublePair> findCrossMinima(std::vector<std::vector<doublePair>> & data1,
                                           std::vector<std::vector<doublePair>> & data2) const;

   void singleCalculation();
   void distrCalculation();

public slots:
   void loadParameters();

private slots:
   void startCalculation();
    void saveParameters() const;

   void switchToSphere(bool chosen);
   void switchToProlate(bool chosen);
   void switchToOblate(bool chosen);
   void switchToLongRod(bool chosen);
};

#endif // SHAMAINWIDGET_H
