#ifndef SHAPARAMSTRUCTS_H
#define SHAPARAMSTRUCTS_H

#include "./shadefinitions.h"
#include <QVector>

struct GridParameters {
   ldouble alphaMin;
   ldouble alphaMax;
   ldouble betaMin;
   ldouble betaMax;
   ldouble gridResolution;
};

struct PhysicalParameters {
   ldouble densCore;
   ldouble densSurf;
   ldouble densSolv;
   ldouble viscSolv;
   ldouble temperature;
   ldouble layerSurf;
   ldouble layerSolv;
};

struct MeasurementParamaters {
   bool useD;
   bool useS;
   bool useLam;
   bool useDDev;
   bool useSDev;
   bool useLamDev;
   bool trackDensity;

   ldouble DMeas;
   ldouble sMeas;
   ldouble lamMeas;
   ldouble DDev;
   ldouble sDev;
   ldouble lamDev;
};

struct SimulationResults{
   QVecLDouble axAlpha;
   QVecLDouble axBeta;
   QMatLDouble chiSqD; // optima for D
   QMatLDouble chiSqS; // optima for s
   QMatLDouble avDensityPart;
   QMatLDouble chiSqLam;
};

#endif // SHAPARAMSTRUCTS_H
