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
   QVector<ldouble> axAlpha;
   QVector<ldouble> axBeta;
   QVector<QVector<ldouble> > chiSqD; // optima for D
   QVector<QVector<ldouble> > chiSqS; // optima for s
   QVector<QVector<ldouble> > avDensityPart;
   QVector<QVector<ldouble> > chiSqLam;
};

#endif // SHAPARAMSTRUCTS_H
