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
#include <shaparamstructs.h>
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

   virtual SimulationResults doSimulation(int *errCode = nullptr
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
                            const bool plotD, const QVecLDouble &minDAlpha, const QVecLDouble &minDBeta,
                            const bool plotS, const QVecLDouble &minSAlpha, const QVecLDouble &minSBeta,
                            const bool plotLam, const QVecLDouble &minLamAlpha, const QVecLDouble &minLamBeta,
                            const bool plotDDev, const QVecLDouble &minDAlphaDevU, const QVecLDouble &minDBetaDevU,
                            const QVecLDouble &minDAlphaDevL, const QVecLDouble &minDBetaDevL,
                            const bool plotSDev, const QVecLDouble &minSAlphaDevU, const QVecLDouble &minSBetaDevU,
                            const QVecLDouble &minSAlphaDevL, const QVecLDouble &minSBetaDevL,
                            const bool plotLamDev, const QVecLDouble &minLamAlphaDevU, const QVecLDouble &minLamBetaDevU,
                            const QVecLDouble &minLamAlphaDevL, const QVecLDouble &minLamBetaDevL
                            ) const;


   QMatLDouble makeLDoubleMatrix(const int aGridLength, const int bGridLength);


   void createVectorFromTo(QVecLDouble &v, ldouble min, ldouble max, ldouble stride);
   int minAt(const QVecLDouble &v, ldouble *val = nullptr) const;
   ldouble minOf(const QMatLDouble &v, int *iPos = nullptr, int *jPos = nullptr) const;
   ldouble maxOf(const QMatLDouble &v, int *iPos = nullptr, int *jPos = nullptr) const;
   ldouble meanOf(QMatLDouble &v);

   /* Only alphaGrids working valid by now;
*/
   enum refGrid {
      gridOnAlpha = 0,
      gridOnBeta = 1
   };



   void extractMinLine(const QVecLDouble &axAlpha,
                       const QVecLDouble &axBeta,
                       const ldouble minDistAB,
                       const QMatLDouble &chiSq,
                       QVecLDouble &minAlpha,
                       QVecLDouble &minBeta,
                       refGrid grid = gridOnAlpha
                                      );

    pairLDouble findIntersection(const QVecLDouble &alpha1, const QVecLDouble &beta1,
                                 const QVecLDouble &alpha2, const QVecLDouble &beta2,
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
                              const QVecLDouble &axAlpha,
                              const QVecLDouble &axBeta,
                              const QMatLDouble &chiSq
                              );

   void writeGnuPlotChiSqPlotScript(const QString &scriptFileName,
                                    const QString &dataFileName,
                                    const QString &imgFileName,
                                    const QVecLDouble &axAlpha,
                                    const QVecLDouble &axBeta
                                    );

   void callGnuPlot(const QString &gnuplotPath,
                    const QString &scriptFileName
                    );

   int plotCSV(const QString &fileName,
               const QStringList &headLine,
               const QMatLDouble &plotValues) const;

};

#endif // SHASHAPECALCULATOR_H
