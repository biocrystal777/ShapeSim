#ifndef SHAPROLATECALCULATOR_H
#define SHAPROLATECALCULATOR_H
#include "./shaparamstructs.h"
#include "./sharodlikescalculator.h"

class ShaProlateCalculator final : public ShaRodLikesCalculator
{
public:
   ShaProlateCalculator(const QString &outPutDirPath,
                        const GridParameters gridpars,
                        const PhysicalParameters physPars,
                        const MeasurementParamaters measPars,
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
