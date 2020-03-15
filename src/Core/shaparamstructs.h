#ifndef SHAPARAMSTRUCTS_H
#define SHAPARAMSTRUCTS_H

#include "./shadefinitions.h"

struct GridParameters {
   double alphaMin;
   double alphaMax;
   double betaMin;
   double betaMax;
   double stride;
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

#endif // SHAPARAMSTRUCTS_H
