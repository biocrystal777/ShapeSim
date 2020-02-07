#ifndef SHARODLIKESCALCULATOR_H
#define SHARODLIKESCALCULATOR_H
#include "./shatwoaxiscalculator.h"

class ShaRodLikesCalculator : public ShaTwoAxisCalculator
{
public:
   ShaRodLikesCalculator(const QString &outPutDirPath,
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
                         const bool useGnuplot,
                         const QString &gnuplotPath);
   ~ShaRodLikesCalculator(){}
   ShaRodLikesCalculator(const ShaRodLikesCalculator& src) = delete;
   ShaRodLikesCalculator& operator= (ShaRodLikesCalculator& src) = delete;
   ShaRodLikesCalculator(ShaRodLikesCalculator&& src) = delete;
   ShaRodLikesCalculator& operator= (ShaRodLikesCalculator&& src) = delete;


protected:
   ldouble calcLam(const ldouble aCore,
                   const ldouble bCore
                   ) const override;

};

#endif // SHARODLIKESCALCULATOR_H
