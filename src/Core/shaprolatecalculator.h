#ifndef SHAPROLATECALCULATOR_H
#define SHAPROLATECALCULATOR_H
#include "./sharodlikescalculator.h"

class ShaProlateCalculator final : public ShaRodLikesCalculator
{
public:
   ShaProlateCalculator(const QString &outPutDirPath,
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
                        const QString &gnuplotPath);
   ~ShaProlateCalculator(){}
   ShaProlateCalculator(const ShaProlateCalculator& src) = delete;
   ShaProlateCalculator& operator= (ShaProlateCalculator& src) = delete;
   ShaProlateCalculator(ShaProlateCalculator&& src) = delete;
   ShaProlateCalculator& operator= (ShaProlateCalculator&& src) = delete;

private:

   ldouble calcFF0(const ldouble P) const override;
   ldouble calcA0(const ldouble alpha, const ldouble beta) const override;
   ldouble calcVol(const ldouble alpha, const ldouble beta) const override;

};

#endif // SHAPROLATECALCULATOR_H
