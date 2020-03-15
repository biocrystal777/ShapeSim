#include "./shalongrodcalculator.h"

ShaLongRodCalculator::ShaLongRodCalculator(const QString &outPutDirPath,
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
                                           const bool useTrackDensity,
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
                         useTrackDensity,
                         useGnuplot,
                         gnuplotPath) {}

ldouble ShaLongRodCalculator::calcFF0(const ldouble P) const
{
   return pow(twoThird * P *P, third) / log(P) + gammaCorr(P);
}

ldouble ShaLongRodCalculator::calcA0(const ldouble alpha, const ldouble beta) const
{
   return pow((1.5 * alpha * beta * beta), third);
}

ldouble ShaLongRodCalculator::calcVol(const ldouble alpha, const ldouble beta) const
{
   return twoPI * alpha * beta * beta;
}
