#ifndef SHAPARAMSTRUCTS_H
#define SHAPARAMSTRUCTS_H

struct gridParameters {
   double alphaMin;
   double alphaMax;
   double betaMin;
   double betaMax;
   double stride;
};

struct fixedParameters {
   double densCore;
   double densSurf;
   double densSolv;
   double viscSolv;
   double temperature;
   double layerSurf;
   double layerSolv;
};

struct evalParamaters {
   bool useD;
   bool useS;
   bool useLam;
   bool useDDev;
   bool useSDev;
   bool useLamDev;
   bool trackDensity;

   double DMeas;
   double sMeas;
   double lamMeas;
   double DDev;
   double sDev;
   double lamDev;
};

#endif // SHAPARAMSTRUCTS_H
