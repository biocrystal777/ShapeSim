#include "shatwoaxiscalculator.h"

ShaTwoAxisCalculator::ShaTwoAxisCalculator(const QString &outPutDirPath,
                                           const GridParameters gridPars,
                                           const PhysicalParameters physPars,
                                           const MeasurementParamaters measPars,
                                           const bool useGnuplot,
                                           const QString &gnuplotPath) :
   outPutDirPath(outPutDirPath),
   gridRes(gridPars.gridResolution),
   axAlphaMin(gridPars.alphaMin),
   axAlphaMax(gridPars.alphaMax),
   axBetaMin(gridPars.betaMin),
   axBetaMax(gridPars.betaMax),
   dShell(physPars.layerSurf),
   visc(physPars.viscSolv),
   T(physPars.temperature),
   densCore(physPars.densCore),
   densSurf(physPars.densSurf),
   densSolv(physPars.densSolv),
   DMeas(measPars.DMeas),
   SMeas(measPars.sMeas),
   lamMeas(measPars.lamMeas),
   DDev(measPars.DDev),
   SDev(measPars.sDev),
   lamDev(measPars.lamDev),
   plotD(measPars.useD),
   plotS(measPars.useS),
   plotLam(measPars.useLam),
   plotDDev(measPars.useDDev),
   plotSDev(measPars.useSDev),
   plotLamDev(measPars.useLamDev),
   trackDensity(measPars.trackDensity),
   useGnuplot(useGnuplot),
   gnuplotPath(gnuplotPath)
{
}

SimulationResults ShaTwoAxisCalculator::doSimulation(int * errCode)
{
   SimulationResults results;
   QVector<ldouble> &axAlpha = results.axAlpha;
   QVector<ldouble> &axBeta = results.axBeta;
   QVector<QVector<ldouble> > chiSqD = results.chiSqD;   // optima for D
   QVector<QVector<ldouble> > &chiSqS = results.chiSqS;   // optima for S
   QVector<QVector<ldouble> > &chiSqLam = results.chiSqLam;



   {
      QDir outPutDir;
      if(!(outPutDir.exists(outPutDirPath)))
         outPutDir.mkpath(outPutDirPath);
   }
   createVectorFromTo(axAlpha, axAlphaMin, axAlphaMax, gridRes);
   createVectorFromTo(axBeta, axBetaMin, axBetaMax, gridRes);

   //-//////////////////////////////////
   // Get optimal beta(alpha) for D
   QVector<ldouble> minDAlpha;
   QVector<ldouble> minDBeta;
   QVector<ldouble> minDAlphaDevU;
   QVector<ldouble> minDBetaDevU;
   QVector<ldouble> minDAlphaDevL;
   QVector<ldouble> minDBetaDevL;
   if(plotD){
      QVector<QVector<ldouble> > chiSqDDevUpper;
      QVector<QVector<ldouble> > chiSqDDevLower;
      calcChiSqD(axAlpha, axBeta, dShell, visc, T, DMeas, chiSqD, plotDDev, chiSqDDevUpper, chiSqDDevLower, DDev);


      if(useGnuplot){
      writeGnuPlotChiSqData(tr("%1/chiSqD").arg(outPutDirPath), axAlpha, axBeta, chiSqD);
      writeGnuPlotChiSqPlotScript(tr("%1/scriptD.gnpl").arg(outPutDirPath),
                                  tr("%1/chiSqD").arg(outPutDirPath), tr("%1/chiSqD.png").arg(outPutDirPath), axAlpha, axBeta);
      ShaLog::logText(tr("Plot raw extraction of D with gnuplot to %1/chiSqD.png").arg(outPutDirPath), true);
      callGnuPlot(gnuplotPath, tr("%1/scriptD.gnpl").arg(outPutDirPath));
      }

      extractMinLine(axAlpha, axBeta, 2.0 * gridRes, chiSqD, minDAlpha, minDBeta);
      if(plotDDev){
         extractMinLine(axAlpha, axBeta, 2.0 * gridRes, chiSqDDevUpper, minDAlphaDevU, minDBetaDevU);
         extractMinLine(axAlpha, axBeta, 2.0 * gridRes, chiSqDDevLower, minDAlphaDevL, minDBetaDevL);
      }
   }
   //-////////////////////////////////
   // Get optimal beta(alpha) for s //
   QVector<ldouble> minSAlpha;
   QVector<ldouble> minSBeta;
   QVector<ldouble> minSAlphaDevU;
   QVector<ldouble> minSBetaDevU;
   QVector<ldouble> minSAlphaDevL;
   QVector<ldouble> minSBetaDevL;
   if(plotS){
      QVector<QVector<ldouble> > chiSqSDevUpper;
      QVector<QVector<ldouble> > chiSqSDevLower;
      calcChiSqS(axAlpha, axBeta, dShell, visc, densCore, densSurf, densSolv, SMeas, chiSqS, plotSDev, chiSqSDevUpper, chiSqSDevLower, SDev);
      if(useGnuplot){
         //for(double v : chiSqS[0])    qDebug() << v;
      writeGnuPlotChiSqData(tr("%1/chiSqS").arg(outPutDirPath), axAlpha, axBeta, chiSqS);
       writeGnuPlotChiSqPlotScript(tr("%1/scriptS.gnpl").arg(outPutDirPath),
                                  tr("%1/chiSqS").arg(outPutDirPath), tr("%1/chiSqS.png").arg(outPutDirPath), axAlpha, axBeta);
      ShaLog::logText(tr("Plot raw extraction of s with gnuplot to %1/chiSqS.png").arg(outPutDirPath), true);
      callGnuPlot("/usr/bin/gnuplot", tr("%1/scriptS.gnpl").arg(outPutDirPath));
      }

      extractMinLine(axAlpha, axBeta, 2.0 * gridRes, chiSqS, minSAlpha, minSBeta);
      if(plotSDev){
         extractMinLine(axAlpha, axBeta, 2.0 * gridRes, chiSqSDevUpper, minSAlphaDevU, minSBetaDevU);
         extractMinLine(axAlpha, axBeta, 2.0 * gridRes, chiSqSDevLower, minSAlphaDevL, minSBetaDevL);
      }
   }
   //-/////////////////////////////////////
   // Get optimal beta(alpha) for Lambda //
   QVector<ldouble> minLamAlpha;
   QVector<ldouble> minLamBeta;
   QVector<ldouble> minLamAlphaDevU;
   QVector<ldouble> minLamBetaDevU;
   QVector<ldouble> minLamAlphaDevL;
   QVector<ldouble> minLamBetaDevL;
   if(plotLam){
      QVector<QVector<ldouble> > chiSqLamDevUpper;
      QVector<QVector<ldouble> > chiSqLamDevLower;
      calcChiSqLam(axAlpha, axBeta, lamMeas, chiSqLam, plotLamDev, chiSqLamDevUpper, chiSqLamDevLower, lamDev);      
      if(useGnuplot){
         writeGnuPlotChiSqData(tr("%1/chiSqLambda").arg(outPutDirPath), axAlpha, axBeta, chiSqLam);
         writeGnuPlotChiSqPlotScript(tr("%1/scriptLambda.gnpl").arg(outPutDirPath),
                                     tr("%1/chiSqLambda").arg(outPutDirPath), tr("%1/chiSqLambda.png").arg(outPutDirPath), axAlpha, axBeta);
      ShaLog::logText(tr("Plot raw extraction of λmax with gnuplot to %1/chiSqLambda.png").arg(outPutDirPath), true);
      callGnuPlot("/usr/bin/gnuplot", tr("%1/scriptLambda.gnpl").arg(outPutDirPath));
      }

      extractMinLine(axAlpha, axBeta, 2.0 * gridRes, chiSqLam, minLamAlpha, minLamBeta);
      if(plotLamDev){
         extractMinLine(axAlpha, axBeta, 2.0 * gridRes, chiSqLamDevUpper, minLamAlphaDevU, minLamBetaDevU);
         extractMinLine(axAlpha, axBeta, 2.0 * gridRes, chiSqLamDevLower, minLamAlphaDevL, minLamBetaDevL);
      }
   }
   plotAlphaBetaOptima( outPutDirPath,
                        plotD,minDAlpha, minDBeta,
                        plotS, minSAlpha, minSBeta,
                        plotLam, minLamAlpha, minLamBeta,
                        plotDDev, minDAlphaDevU, minDBetaDevU, minDAlphaDevL, minDBetaDevL,
                        plotSDev, minSAlphaDevU, minSBetaDevU, minSAlphaDevL, minSBetaDevL,
                        plotLamDev, minLamAlphaDevU, minLamBetaDevU, minLamAlphaDevL, minLamBetaDevL);

   // intersection:


   // return parameters:


   return results;
}


void ShaTwoAxisCalculator::calcChiSqD(const QVector<ldouble> &axAlpha,
                                      const QVector<ldouble> &axBeta,
                                      const ldouble dShell, const ldouble visc, const ldouble T,
                                      const ldouble DMeas,
                                      QVector<QVector<ldouble> > &chiSq,
                                      const bool calcDevs,
                                      QVector<QVector<ldouble> > &chiSqUp, QVector<QVector<ldouble> > &chiSqL,
                                      const ldouble DDev)
{
   const ldouble aGridLength = axAlpha.size();
   const ldouble bGridLength = axBeta.size();

   chiSq = QVector<QVector<ldouble> >(aGridLength);
   for(QVector<ldouble> &v : chiSq) v = QVector<ldouble>(bGridLength);
   if(calcDevs){
      chiSqUp =  QVector<QVector<ldouble> >(aGridLength);
      for(QVector<ldouble> &v : chiSqUp) v = QVector<ldouble>(bGridLength);
      chiSqL = QVector<QVector<ldouble> >(aGridLength);
      for(QVector<ldouble> &v : chiSqL) v = QVector<ldouble>(bGridLength);
   }
   const ldouble DDevU = DMeas + DDev;
   const ldouble DDevL = DMeas - DDev;
   for(int i = 0; i < aGridLength; ++i){
      for(int j = 0; j < bGridLength; ++j){
         ldouble DCalc = calcD(axAlpha[i], axBeta[j], dShell, visc, T);
         chiSq[i][j] = calcChiSq(DCalc, DMeas, DMeas);
         if(calcDevs){
            chiSqUp[i][j] = calcChiSq(DCalc, DDevU, DMeas);
            chiSqL[i][j] = calcChiSq(DCalc, DDevL, DMeas);
         }
      }
   }
}

void ShaTwoAxisCalculator::calcChiSqS(const QVector<ldouble> &axAlpha,
                                      const QVector<ldouble> &axBeta,
                                      const ldouble dShell,
                                      const ldouble visc,
                                      const ldouble densCore, const ldouble densSurf,
                                      const ldouble densSolv, const ldouble SMeas,
                                      QVector<QVector<ldouble> > &chiSq, const bool calcDevs,
                                      QVector<QVector<ldouble> > &chiSqUp, QVector<QVector<ldouble> > &chiSqL, const ldouble SDev)
{
   const ldouble aGridLength = axAlpha.size();
   const ldouble bGridLength = axBeta.size();
   chiSq = QVector<QVector<ldouble> >(aGridLength);
   for(QVector<ldouble> &v : chiSq) v = QVector<ldouble>(bGridLength);
   if(calcDevs){
      chiSqUp = QVector<QVector<ldouble> > (aGridLength);
      for(QVector<ldouble> &v : chiSqUp) v = QVector<ldouble>(bGridLength);
      chiSqL =QVector<QVector<ldouble> > (aGridLength);
      for(QVector<ldouble> &v : chiSqL) v = QVector<ldouble>(bGridLength);
   }
   const ldouble SDevU = SMeas + SDev;
   const ldouble SDevL = SMeas - SDev;
   for(int i = 0; i < aGridLength; ++i){
      for(int j = 0; j < bGridLength; ++j){
         ldouble densAveragePart = calcAverageDens(axAlpha[i], axBeta[j], dShell,densCore, densSurf);
         ldouble SCalc = calcS(axAlpha[i], axBeta[j], dShell, visc, densAveragePart, densSolv);

         chiSq[i][j] = calcChiSq(SCalc, SMeas, SMeas);
        // qDebug() << (double) axAlpha[i] << (double) axBeta[j] << (double) chiSq[i][j] << (double) SCalc << (double) SMeas << (double) dShell << (double) visc;
         if(calcDevs){
            chiSqUp[i][j] = calcChiSq(SCalc, SDevU, SMeas);
            chiSqL[i][j] = calcChiSq(SCalc, SDevL, SMeas);
         }
      }
   }
}

void ShaTwoAxisCalculator::calcChiSqLam(const QVector<ldouble> &axAlpha,
                                        const QVector<ldouble> &axBeta,
                                        const ldouble lamMeas,
                                        QVector<QVector<ldouble> > &chiSq,
                                        const bool calcDevs,
                                        QVector<QVector<ldouble> > &chiSqUp,
                                        QVector<QVector<ldouble> > &chiSqL,
                                        const ldouble lamDev)
{
   const ldouble aGridLength = axAlpha.size();
   const ldouble bGridLength = axBeta.size();
   chiSq = QVector<QVector<ldouble> >(aGridLength);
   for(QVector<ldouble> &v : chiSq) v = QVector<ldouble>(bGridLength);
   if(calcDevs){
      chiSqUp = QVector<QVector<ldouble> >(aGridLength);
      chiSqL = QVector<QVector<ldouble> > (aGridLength);
      for(QVector<ldouble> &v : chiSqUp) v = QVector<ldouble>(bGridLength);
      for(QVector<ldouble> &v : chiSqL) v = QVector<ldouble>(bGridLength);
   }
   const ldouble lamDevU = lamMeas + lamDev;
   const ldouble lamDevL = lamMeas - lamDev;
   for(int i = 0; i < aGridLength; ++i){
      for(int j = 0; j < bGridLength; ++j){
         ldouble lamCalc = calcLam(axAlpha[i], axBeta[j]);
         chiSq[i][j] = calcChiSq(lamCalc, lamMeas, lamMeas);
         if(calcDevs){
            chiSqUp[i][j] = calcChiSq(lamCalc, lamDevU, lamMeas);
            chiSqL[i][j] = calcChiSq(lamCalc, lamDevL, lamMeas);
         }
      }
   }
}


ldouble ShaTwoAxisCalculator::calcD(const ldouble aCore, const ldouble bCore, const ldouble dShell, const ldouble visc, const ldouble T) const
{
   ldouble rAlpha = aCore + dShell;                     // [nm]
   ldouble rBeta = bCore + dShell;                       // [nm]
   ldouble P = rAlpha / rBeta;                   // ratio = [nm] / [nm] => no dimension
   ldouble a0 = calcA0(rAlpha, rBeta);    // [nm] = rt3([nm]*[nm]*[nm])
   ldouble f_f0 = calcFF0(P);                   // no dimension
   ldouble f0 =  6 * PI * visc * a0;                   //   = mPa*s * nm
   ldouble fShape = f_f0 * f0;                         // mPa*s*nm
   //if( i == aGridLength/2 && j ==  bGridLength/2 ) qDebug() << double(fShape);
   ldouble DCalc = kB  * T / (fShape);
   // m*m*kg / (s * s * K) * K / mPa*s*nm
   // m*m*kg / (s * s ) / (1e-3 * kg/m*s^2)  *s*nm)
   DCalc *= 1e16;  // unit conversions
   return DCalc;
}

ldouble ShaTwoAxisCalculator::calcAverageDens(const ldouble aCore,
                                              const ldouble bCore,
                                              const ldouble dShell,
                                              const ldouble densCore,
                                              const ldouble densSurf)
{
   ldouble rAlpha = aCore + dShell;                     // [nm]
   ldouble rBeta = bCore + dShell;                       // [nm]
   ldouble coreVol = calcVol(aCore, bCore);
   ldouble totVol = calcVol(rAlpha, rBeta);
   ldouble shellVol = coreVol - totVol;
   ldouble volPartialCore = coreVol / totVol;
   ldouble volPartialShell = shellVol / totVol;
   //ldouble rhoPart = volPartialCore * densCore + volPartialShell * densSurf;
   ldouble rhoPart = volPartialCore * densCore + volPartialShell * densSurf;
   return rhoPart;
}


ldouble ShaTwoAxisCalculator::calcS(const ldouble aCore,
                                           const ldouble bCore,
                                           const ldouble dShell,
                                           const ldouble visc,
                                           const ldouble densAveragePart,
                                           const ldouble densSolv) const
{

   //constexpr ldouble PI = 3.141;

   ldouble rAlpha = aCore + dShell;                     // [nm]
   ldouble rBeta = bCore + dShell;                       // [nm]
   // calc fshape
   ldouble P = rAlpha / rBeta;
   ldouble a0 = calcA0(rAlpha, rBeta);
   ldouble ff0 = calcFF0(P);
   ldouble f0 =  6 * PI * visc * a0;
   ldouble fShape = ff0 * f0;

   ldouble totVol = calcVol(rAlpha, rBeta);
   ldouble mass = densAveragePart * totVol;
   // calc S and chiSqS
   ldouble SCalc = mass * (1.0 - densSolv / densAveragePart) / fShape;
   SCalc *= 1e1; // adapt to unit conversion

   return SCalc;
}

