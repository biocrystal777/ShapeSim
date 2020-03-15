#ifndef SHALONGRODCALCULATOR_H
#define SHALONGRODCALCULATOR_H
#include "./sharodlikescalculator.h"
#include "./shaparamstructs.h"

class ShaLongRodCalculator final : public ShaRodLikesCalculator
{
public:
   ShaLongRodCalculator(const QString &outPutDirPath,
                        const ldouble stride,
                        const ldouble axAlphaMin,
                        const ldouble axAlphaMax,
                        const ldouble axBetaMin,
                        const ldouble axBetaMax,
                        const PhysicalParameters physPars,
                        //
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
                        const QString &gnuplotPath);
   ~ShaLongRodCalculator(){}
   ShaLongRodCalculator(const ShaLongRodCalculator& src) = delete;
   ShaLongRodCalculator& operator= (ShaLongRodCalculator& src) = delete;
   ShaLongRodCalculator(ShaLongRodCalculator&& src) = delete;
   ShaLongRodCalculator& operator= (ShaLongRodCalculator&& src) = delete;

private:

   inline ldouble gammaCorr(const ldouble P) const { return 0.312 + 0.565 / P + 0.100 / (P*P); }
   ldouble calcFF0(const ldouble P) const override;
   ldouble calcA0(const ldouble alpha, const ldouble beta) const override;
   ldouble calcVol(const ldouble alpha, const ldouble beta) const override;

};

#endif // SHALONGRODCALCULATOR_H
