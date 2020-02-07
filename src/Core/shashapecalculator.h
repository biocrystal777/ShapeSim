#ifndef SHASHAPECALCULATOR_H
#define SHASHAPECALCULATOR_H

/*
                                              +--------------------+
                                              | ShaShapeCalculator |
                                              +--------------------+
                                              |  Utility functions |
                                              +--------------------+
                                                         ^
                                                         |
                                                         |
                                             +---------------------------+
                                             |   ShaTwoAxixCalculator    |
                                             +---------------------------+
                                             |        Parameters         |
                                             +---------------------------+
                                             |     GnuPlot functions     |
                                             | Diffusion & Sedimentation |
                                             +---------------------------+
                                                         ^
                                                         |
                                                         +------------------------------------------------+
                                                         |                                                |
                                             +----------------------------+                 +----------------------------+
                                             |   ShaRodLikesCalculator    |                 |     ShaOblateCalculator    |
                                             +----------------------------+                 +----------------------------+
                                                         ^
                                                         |
                               +-------------------------------+-----------------------------------+
                               |                               |                                   |
                   +-----------------------+  +-----------------------+
                   |  ShaProlateCalculator |  |  ShaLongRodCalculator |
                   +-----------------------+  +-----------------------+

*/

#include "./shadefinitions.h"

#include <QObject>
#include <QProcess>
#include <QSettings>
#include <QVector>
#include <QString>
#include <cmath>
#include <limits>
#include <algorithm>
#include <QFile>
#include <QDir>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "./shalog_omp.h"

class ShaShapeCalculator : public QObject
{
public:
   explicit ShaShapeCalculator(){}
   virtual ~ShaShapeCalculator(){}
   ShaShapeCalculator(const ShaShapeCalculator& src) = delete;
   ShaShapeCalculator& operator= (ShaShapeCalculator& src) = delete;
   ShaShapeCalculator(ShaShapeCalculator&& src) = delete;
   ShaShapeCalculator& operator= (ShaShapeCalculator&& src) = delete;

   virtual int start(
         QVector<ldouble> &axAlpha,
         QVector<ldouble> &axBeta,
         QVector<QVector<ldouble> >&chiSqD, // optima for D
         QVector<QVector<ldouble> >&chiSqS, // optima for S
         QVector<QVector<ldouble> >&chiSqLam
         ) = 0;




protected:
   // constants
   constexpr static ldouble minThird = -1.0 / 3.0;
   constexpr static ldouble third = 1.0 / 3.0;
   constexpr static ldouble twoThird = 1.0 / 3.0;
   constexpr static ldouble PI = 3.14159265359;
   constexpr static ldouble ftPI = 4.0 / 3.0 * PI;
   constexpr static ldouble twoPI = 2.0 * PI;
   constexpr static ldouble kB = 1.3806488e-23;



   // functions
   inline ldouble calcChiSq(const ldouble valCalc,
                            const ldouble valMeas,
                            const ldouble norm) const
   {
      ldouble chiSq = (valCalc - valMeas) / norm;
      chiSq *= chiSq;
      return chiSq;
   }


   void plotAlphaBetaOptima(const QString& outPutDirPath,
                            const bool plotD, const QVector<ldouble> &minDAlpha, const QVector<ldouble> &minDBeta,
                            const bool plotS, const QVector<ldouble> &minSAlpha, const QVector<ldouble> &minSBeta,
                            const bool plotLam, const QVector<ldouble> &minLamAlpha, const QVector<ldouble> &minLamBeta,
                            const bool plotDDev, const QVector<ldouble> &minDAlphaDevU, const QVector<ldouble> &minDBetaDevU,
                            const QVector<ldouble> &minDAlphaDevL, const QVector<ldouble> &minDBetaDevL,
                            const bool plotSDev, const QVector<ldouble> &minSAlphaDevU, const QVector<ldouble> &minSBetaDevU,
                            const QVector<ldouble> &minSAlphaDevL, const QVector<ldouble> &minSBetaDevL,
                            const bool plotLamDev, const QVector<ldouble> &minLamAlphaDevU, const QVector<ldouble> &minLamBetaDevU,
                            const QVector<ldouble> &minLamAlphaDevL, const QVector<ldouble> &minLamBetaDevL
                            ) const;


   void createVectorFromTo(QVector<ldouble> &v, ldouble min, ldouble max, ldouble stride);
   int minAt(const QVector<ldouble> &v, ldouble *val = nullptr) const;
   ldouble minOf(const QVector<QVector<ldouble> > &v, int *iPos = nullptr, int *jPos = nullptr) const;
   ldouble maxOf(const QVector<QVector<ldouble> > &v, int *iPos = nullptr, int *jPos = nullptr) const;
   ldouble meanOf(QVector<QVector<ldouble> > &v);

   /* Only alphaGrids working valid by now;
*/
   enum refGrid {
      gridOnAlpha = 0,
      gridOnBeta = 1
   };



   void extractMinLine(const QVector<ldouble> &axAlpha,
                       const QVector<ldouble> &axBeta,
                       const ldouble minDistAB,
                       const QVector<QVector<ldouble> > &chiSq,
                       QVector<ldouble> &minAlpha,
                       QVector<ldouble> &minBeta,
                       refGrid grid = gridOnAlpha
                                      );

    pairLDouble findIntersection(const QVector<ldouble> &alpha1, const QVector<ldouble> &beta1,
                                 const QVector<ldouble> &alpha2, const QVector<ldouble> &beta2,
                                 bool * foundIntersection, ldouble *rms = nullptr);



    /*
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
 */



   void writeGnuPlotChiSqData(const QString &fileName,
                              const QVector<ldouble> &axAlpha,
                              const QVector<ldouble> &axBeta,
                              const QVector<QVector<ldouble> > &chiSq
                              );

   void writeGnuPlotChiSqPlotScript(const QString &scriptFileName,
                                    const QString &dataFileName,
                                    const QString &imgFileName,
                                    const QVector<ldouble> &axAlpha,
                                    const QVector<ldouble> &axBeta
                                    );

   void callGnuPlot(const QString &gnuplotPath,
                    const QString &scriptFileName
                    );

   int plotCSV(const QString &fileName,
               const QStringList &headLine,
               const QVector<QVector<ldouble> > &plotValues) const;

};

#endif // SHASHAPECALCULATOR_H
