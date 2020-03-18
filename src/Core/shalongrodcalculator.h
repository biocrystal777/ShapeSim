#ifndef SHALONGRODCALCULATOR_H
#define SHALONGRODCALCULATOR_H
#include "./sharodlikescalculator.h"
#include "./shaparamstructs.h"

class ShaLongRodCalculator final : public ShaRodLikesCalculator
{
public:
   ShaLongRodCalculator(const QString &outPutDirPath,
                        const GridParameters gridpars,
                        const PhysicalParameters physPars,
                        const MeasurementParamaters measPars,
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
