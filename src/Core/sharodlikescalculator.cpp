#include "sharodlikescalculator.h"

ShaRodLikesCalculator::ShaRodLikesCalculator(const QString &outPutDirPath,
                                             const GridParameters gridPars,
                                             const PhysicalParameters physPars,
                                             const MeasurementParamaters measPars,
                                             const bool useGnuplot,
                                             const QString &gnuplotPath) :
   ShaTwoAxisCalculator(outPutDirPath,
                        gridPars,
                        physPars,
                        measPars,
                        useGnuplot,
                        gnuplotPath) {}

ldouble ShaRodLikesCalculator::calcLam(const ldouble aCore, const ldouble bCore) const
{
   ldouble dA = 2.0 * aCore;
   ldouble dB = 2.0 * bCore;
   ldouble P = dA / dB;
   // CALCULATIONS
   constexpr double a[3][3] = {
      {425.98,   77.098,     2.2488   },
      {0.039777, -0.04831,   0.010482  },
      {-0.0201,   0.017986,  0.0014387 }
   };
   ldouble lamCalc =
         a[0][0]      + a[0][1] * P + a[0][2] * P * P
         + (a[1][0] * + a[1][1] * P + a[1][2] * P * P) * dB
         + (a[2][0] * + a[2][1] * P + a[2][2] * P * P) * dB * dB;

   return lamCalc;
}

