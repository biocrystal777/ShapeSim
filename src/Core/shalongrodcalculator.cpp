#include "./shalongrodcalculator.h"

ShaLongRodCalculator::ShaLongRodCalculator(const QString &outPutDirPath,
                                           const ldouble stride,
                                           const ldouble axAlphaMin,
                                           const ldouble axAlphaMax,
                                           const ldouble axBetaMin,
                                           const ldouble axBetaMax,
                                           const PhysicalParameters physPars,
                                           const MeasurementParamaters measPars,
                                           const bool useGnuplot,
                                           const QString &gnuplotPath) :
   ShaRodLikesCalculator(outPutDirPath,
                         stride,
                         axAlphaMin,
                         axAlphaMax,
                         axBetaMin,
                         axBetaMax,                         
                         physPars.layerSurf,
                         physPars.viscSolv,
                         physPars.temperature,
                         physPars.densCore,
                         physPars.densSurf,
                         physPars.densSolv,
                         measPars.DMeas,
                         measPars.sMeas,
                         measPars.lamMeas,
                         measPars.DDev,
                         measPars.sDev,
                         measPars.lamDev,
                         measPars.useD,
                         measPars.useS,
                         measPars.useLam,
                         measPars.useDDev,
                         measPars.useSDev,
                         measPars.useLamDev,
                         measPars.trackDensity,
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
