#ifndef SHATWOAXISCALCULATOR_H
#define SHATWOAXISCALCULATOR_H

#include "./shashapecalculator.h"
/*!
 * \brief The ShaTwoAxisCalculator class
 * \todo : Documentation
 *         Extract prolate specific formula into seperate class
 *         create parameter objects and reduce header overhead
 *         reduce "local global" member variables
 */
class ShaTwoAxisCalculator : public ShaShapeCalculator
{
public:
   ShaTwoAxisCalculator(const QString &outPutDirPath,
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
   virtual ~ShaTwoAxisCalculator(){}
   ShaTwoAxisCalculator(const ShaTwoAxisCalculator& src) = delete;
   ShaTwoAxisCalculator& operator= (ShaTwoAxisCalculator& src) = delete;
   ShaTwoAxisCalculator(ShaTwoAxisCalculator&& src) = delete;
   ShaTwoAxisCalculator& operator= (ShaTwoAxisCalculator&& src) = delete;

   virtual int start(QVector<ldouble> &axAlpha,
                     QVector<ldouble> &axBeta,
                     QVector<QVector<ldouble> >&chiSqD, // optima for D
                     QVector<QVector<ldouble> >&chiSqS, // optima for S
                     QVector<QVector<ldouble> >&chiSqLam
                     );


   // return values:
   // double getAlpha
   // double getBeta
   //

protected:
   // constants

   // parameters
   const QString outPutDirPath;
   const ldouble stride;
   const ldouble axAlphaMin;
   const ldouble axAlphaMax;
   const ldouble axBetaMin;
   const ldouble axBetaMax;
   const ldouble dShell;

   const ldouble visc;
   const ldouble T;
   const ldouble densCore;
   const ldouble densSurf;
   const ldouble densSolv;
   const ldouble DMeas;
   const ldouble SMeas;
   const ldouble lamMeas;
   const ldouble DDev;
   const ldouble SDev;
   const ldouble lamDev;

   const bool plotD;
   const bool plotS;
   const bool plotLam;
   const bool plotDDev;
   const bool plotSDev;
   const bool plotLamDev;
   const bool trackDensity;

const bool useGnuplot;
const QString gnuplotPath;

    // results

//outRhoBox->setText(QString::number(densParticle[minChiSqPos],'f', 2));
//outChiSqBox->setText(QString::number(minChiSq,'f', 5));
//sphereResWidgetPtr->setRadCore(rad[minChiSqPos]);
//sphereResWidgetPtr->setRadTot(rad[minChiSqPos] + dShell);
//outPBox->setText(tr("     ---   "));
//outff0Box->setText(tr("     ---   "));

   // methods

   void calcChiSqD(const QVector<ldouble> &axAlpha,
                   const QVector<ldouble> &axBeta,
                   const ldouble dShell,
                   const ldouble visc,
                   const ldouble T,
                   const ldouble DMeas,
                   QVector<QVector<ldouble> > &chiSq,
                   const bool calcDevs,
                   QVector<QVector<ldouble> > &chiSqUp,
                   QVector<QVector <ldouble> > &chiSqL,
                   const ldouble DDev);

   void calcChiSqS(const QVector<ldouble> &axAlpha,
                   const QVector<ldouble> &axBeta,
                   const ldouble dShell,
                   const ldouble visc,
                   const ldouble densCore,
                   const ldouble densSurf,
                   const ldouble densSolv,
                   const ldouble SMeas,
                   QVector<QVector<ldouble> > &chiSq,
                   const bool calcDevS,
                   QVector<QVector<ldouble> > &chiSqUp,
                   QVector<QVector <ldouble> > &chiSqL,
                   const ldouble SDev);

   void calcChiSqLam(const QVector<ldouble> &axAlpha,
                     const QVector<ldouble> &axBeta,
                     const ldouble lamMeas,
                     QVector<QVector<ldouble> > &chiSq,
                     const bool calcDevs,
                     QVector<QVector<ldouble> > &chiSqUp,
                     QVector<QVector <ldouble> > &chiSqL,
                     const ldouble lamDev);




   virtual ldouble calcFF0(const ldouble P) const = 0;
   virtual ldouble calcA0(const ldouble alpha, const ldouble beta) const = 0;
   virtual ldouble calcVol(const ldouble alpha, const ldouble beta) const = 0;

   virtual ldouble calcS(const ldouble aCore,
                         const ldouble bCore,
                         const ldouble dShell,
                         const ldouble visc,
                         const ldouble densCore,
                         const ldouble densSurf,
                         const ldouble densSolv) const;
   virtual ldouble calcLam(const ldouble aCore,
                           const ldouble bCore
                           ) const = 0;


   virtual ldouble calcD(const ldouble aCore,
                         const ldouble bCore,
                         const ldouble dShell,
                         const ldouble visc,
                         const ldouble T) const;

};

#endif // SHATWOAXISCALCULATOR_H
