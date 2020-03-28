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
#include <functional>


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
#include "./shashaperesultswidgets.h"
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

//   QComboBox *strideBox                  = nullptr;



   QGroupBox *shapeGroupBox              = nullptr;
   QGridLayout *shapeSwitchLay           = nullptr;
   QRadioButton *prolateSwitch           = nullptr;
   QRadioButton *oblateSwitch            = nullptr;
   QRadioButton *longRodSwitch           = nullptr;

   ShaShapeParWidget *curShapeWidget   = nullptr;
   ShaShapeParWidget *prolateWidgetPtr = nullptr;
   ShaShapeParWidget *oblateWidgetPtr  = nullptr;
   ShaShapeParWidget *longRodWidgetPtr = nullptr;

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

   ShaShapeResultsWidget *shapeResWidget         = nullptr;
   ShaProlateResWidget *prolateResWidgetPtr  = nullptr;
   ShaOblateResWidget *oblateResWidgetPtr    = nullptr;
   ShaLongRodResWidget *longRodResWidgetPtr  = nullptr;

   // log Widget
   ShaLog *logWidget = nullptr;

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

   void switchToProlate(bool chosen);
   void switchToOblate(bool chosen);
   void switchToLongRod(bool chosen);
};

#endif // SHAMAINWIDGET_H
