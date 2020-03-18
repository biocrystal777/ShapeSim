#ifndef SHARODLIKESCALCULATOR_H
#define SHARODLIKESCALCULATOR_H
#include "./shatwoaxiscalculator.h"
#include "./shaparamstructs.h"

class ShaRodLikesCalculator : public ShaTwoAxisCalculator
{
public:
   ShaRodLikesCalculator(const QString &outPutDirPath,
                         const GridParameters gridPars,
                         const PhysicalParameters physPars,
                         const MeasurementParamaters measPars,
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
