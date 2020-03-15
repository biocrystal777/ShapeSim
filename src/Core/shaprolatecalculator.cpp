#include "shaprolatecalculator.h"

ShaProlateCalculator::ShaProlateCalculator(const QString &outPutDirPath,
                                           const ldouble stride,
                                           const ldouble axAlphaMin,
                                           const ldouble axAlphaMax,
                                           const ldouble axBetaMin,
                                           const ldouble axBetaMax,
                                           const ldouble dShell,
                                           const ldouble visc,
                                           const ldouble T,
                                           const ldouble densCore,
                                           const ldouble densSurf,
                                           const ldouble densSolv,
                                           const ldouble DMeas,
                                           const ldouble SMeas,
                                           const ldouble lamMeas,
                                           const ldouble DDev,
                                           const ldouble SDev,
                                           const ldouble lamDev,
                                           const bool plotD,
                                           const bool plotS,
                                           const bool plotLam,
                                           const bool plotDDev,
                                           const bool plotSDev,
                                           const bool plotLamDev,
                                           const bool useTrackDenisity,
                                           const bool useGnuplot,
                                           const QString &gnuplotPath) :
   ShaRodLikesCalculator(outPutDirPath,
                         stride,
                         axAlphaMin,
                         axAlphaMax,
                         axBetaMin,
                         axBetaMax,
                         dShell,
                         visc,
                         T,
                         densCore,
                         densSurf,
                         densSolv,
                         DMeas,
                         SMeas,
                         lamMeas,
                         DDev,
                         SDev,
                         lamDev,
                         plotD,
                         plotS,
                         plotLam,
                         plotDDev,
                         plotSDev,
                         plotLamDev,
                         trackDensity,
                         useGnuplot,
                         gnuplotPath) {}

ldouble ShaProlateCalculator::calcFF0(const ldouble P) const
{

   ldouble sqrtPsqMinOne =  sqrt(P * P - 1.0);
   ldouble ff0 = pow(P, minThird) * sqrtPsqMinOne;
   return ff0 / log(P + sqrtPsqMinOne);
}

ldouble ShaProlateCalculator::calcA0(const ldouble alpha, const ldouble beta) const
{
   return pow((alpha * beta * beta), third);
}

ldouble ShaProlateCalculator::calcVol(const ldouble alpha, const ldouble beta) const
{
   return ftPI * alpha * beta * beta;
}
/*
ldouble ShaProlateCalculator::calcLam(const ldouble aCore, const ldouble bCore) const
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
*/
