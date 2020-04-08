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
   QVecLDouble &axAlpha = results.axAlpha;
   QVecLDouble &axBeta = results.axBeta;
   QMatLDouble chiSqD = results.chiSqD;   // optima for D
   QMatLDouble &chiSqS = results.chiSqS;   // optima for S
   QMatLDouble &chiSqLam = results.chiSqLam;

   {
      QDir outPutDir;
      if(!(outPutDir.exists(outPutDirPath)))
         outPutDir.mkpath(outPutDirPath);
   }
   createVectorFromTo(axAlpha, axAlphaMin, axAlphaMax, gridRes);
   createVectorFromTo(axBeta, axBetaMin, axBetaMax, gridRes);

   //-//////////////////////////////////
   // Get optimal beta(alpha) for D
   QVecLDouble minDAlpha;
   QVecLDouble minDBeta;
   QVecLDouble minDAlphaDevU;
   QVecLDouble minDBetaDevU;
   QVecLDouble minDAlphaDevL;
   QVecLDouble minDBetaDevL;
   if(plotD){
      QMatLDouble chiSqDDevUpper;
      QMatLDouble chiSqDDevLower;
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
   QVecLDouble minSAlpha;
   QVecLDouble minSBeta;
   QVecLDouble minSAlphaDevU;
   QVecLDouble minSBetaDevU;
   QVecLDouble minSAlphaDevL;
   QVecLDouble minSBetaDevL;
   QMatLDouble densityPart;
   if(plotS){
      QMatLDouble chiSqSDevUpper;
      QMatLDouble chiSqSDevLower;
      calcChiSqS(axAlpha,
                 axBeta,
                 dShell,
                 visc,
                 densCore,
                 densSurf,
                 densSolv,
                 SMeas,
                 chiSqS,
                 trackDensity,
                 densityPart,
                 plotSDev,
                 chiSqSDevUpper,
                 chiSqSDevLower,
                 SDev
                 );
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
   QVecLDouble minLamAlpha;
   QVecLDouble minLamBeta;
   QVecLDouble minLamAlphaDevU;
   QVecLDouble minLamBetaDevU;
   QVecLDouble minLamAlphaDevL;
   QVecLDouble minLamBetaDevL;
   if(plotLam){
      QMatLDouble chiSqLamDevUpper;
      QMatLDouble chiSqLamDevLower;
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


void ShaTwoAxisCalculator::calcChiSqD(const QVecLDouble &axAlpha,
                                      const QVecLDouble &axBeta,
                                      const ldouble dShell, const ldouble visc, const ldouble T,
                                      const ldouble DMeas,
                                      QMatLDouble &chiSq,
                                      const bool calcDevs,
                                      QMatLDouble &chiSqUp, QMatLDouble &chiSqL,
                                      const ldouble DDev)
{
   const ldouble aGridLength = axAlpha.size();
   const ldouble bGridLength = axBeta.size();

   chiSq = QMatLDouble(aGridLength);
   for(QVecLDouble &v : chiSq) v = QVecLDouble(bGridLength);
   if(calcDevs){
      chiSqUp =  QMatLDouble(aGridLength);
      for(QVecLDouble &v : chiSqUp) v = QVecLDouble(bGridLength);
      chiSqL = QMatLDouble(aGridLength);
      for(QVecLDouble &v : chiSqL) v = QVecLDouble(bGridLength);
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

void ShaTwoAxisCalculator::calcChiSqS(const QVecLDouble &axAlpha,
                                      const QVecLDouble &axBeta,
                                      const ldouble dShell,
                                      const ldouble visc,
                                      const ldouble densCore, const ldouble densSurf,
                                      const ldouble densSolv, const ldouble SMeas,
                                      QMatLDouble &chiSq,
                                      const bool trackDensity,
                                      QMatLDouble &densityPart,
                                      const bool calcDevs,
                                      QMatLDouble &chiSqUp, QMatLDouble &chiSqL, const ldouble SDev)
{
   const ldouble aGridLength = axAlpha.size();
   const ldouble bGridLength = axBeta.size();
   chiSq = QMatLDouble(aGridLength);
   for(QVecLDouble &v : chiSq) v = QVecLDouble(bGridLength);
   if(trackDensity){
      densityPart = QMatLDouble (aGridLength);
      for(QVecLDouble &v : densityPart) v = QVecLDouble(bGridLength);
   }
   if(calcDevs){
      chiSqUp = QMatLDouble (aGridLength);
      for(QVecLDouble &v : chiSqUp) v = QVecLDouble(bGridLength);
      chiSqL =QMatLDouble (aGridLength);
      for(QVecLDouble &v : chiSqL) v = QVecLDouble(bGridLength);
   }   
   const ldouble SDevU = SMeas + SDev;
   const ldouble SDevL = SMeas - SDev;
   for(int i = 0; i < aGridLength; ++i){
      for(int j = 0; j < bGridLength; ++j){
         ldouble densAveragePart = calcAverageDens(axAlpha[i], axBeta[j], dShell,densCore, densSurf);
         if(trackDensity) densityPart[i][j] = densAveragePart;
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

void ShaTwoAxisCalculator::calcChiSqLam(const QVecLDouble &axAlpha,
                                        const QVecLDouble &axBeta,
                                        const ldouble lamMeas,
                                        QMatLDouble &chiSq,
                                        const bool calcDevs,
                                        QMatLDouble &chiSqUp,
                                        QMatLDouble &chiSqL,
                                        const ldouble lamDev)
{
   const ldouble aGridLength = axAlpha.size();
   const ldouble bGridLength = axBeta.size();
   chiSq = QMatLDouble(aGridLength);
   for(QVecLDouble &v : chiSq) v = QVecLDouble(bGridLength);
   if(calcDevs){
      chiSqUp = QMatLDouble(aGridLength);
      chiSqL = QMatLDouble (aGridLength);
      for(QVecLDouble &v : chiSqUp) v = QVecLDouble(bGridLength);
      for(QVecLDouble &v : chiSqL) v = QVecLDouble(bGridLength);
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

