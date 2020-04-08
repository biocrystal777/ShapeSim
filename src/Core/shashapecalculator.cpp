#include "shashapecalculator.h"

int ShaShapeCalculator::minAt(const QVecLDouble &v, ldouble *val) const
{
    if(v.size() == 0) return -1;
    int minPos = 0;
    ldouble min = v[0];
    for (int i = 0; i < v.size(); ++i){
        if(v[i] < min){
            minPos = i;
            min = v[i];
        }
    }
    if(val) *val = min;
    return minPos;
}

ldouble ShaShapeCalculator::minOf(const QMatLDouble &v, int *iPos, int *jPos) const
{
    if(v.size() == 0) return -1;
    int minPosI = 0;
    int minPosJ = 0;
    ldouble min = std::numeric_limits<ldouble>::max();
    for (int i = 0; i < v.size(); ++i){
        for (int j = 0; j < v[i].size(); ++j){
            ldouble vTest = v[i][j];
            if(std::isnormal(vTest) && vTest < min){
                minPosI = i;
                minPosJ = j;
                min = vTest;
            }
        }
    }
    if(iPos) *iPos = minPosI;
    if(jPos) *jPos = minPosJ;
    return min;
}

ldouble ShaShapeCalculator::maxOf(const QMatLDouble &v, int *iPos, int *jPos) const
{
    if(v.size() == 0) return -1.0;
    int maxPosI = 0;
    int maxPosJ = 0;
    ldouble max = std::numeric_limits<ldouble>::min();
    for (int i = 0; i < v.size(); ++i){
        for (int j = 0; j < v[i].size(); ++j){
            ldouble vTest = v[i][j];
            if(std::isnormal(vTest) && vTest > max){
                maxPosI = i;
                maxPosJ = j;
                max = vTest;
            }
        }
    }
    if(iPos) *iPos = maxPosI;
    if(jPos) *jPos = maxPosJ;
    return max;
}

ldouble ShaShapeCalculator::meanOf(QMatLDouble &v)
{
    ldouble sum(0);
    //QVector<int> sizes;
    long int totalSize = 0;
    for(int i = 0; i < v.size(); ++i){
        for(int j = 0; j < v[i].size(); ++j){
            if(std::isnormal(v[i][j])){
                sum += v[i][j];
                ++totalSize;
            }
        }
    }
    return sum / totalSize;
}

void ShaShapeCalculator::extractMinLine(const QVecLDouble &axAlpha,
                                        const QVecLDouble &axBeta,
                                        const ldouble minDistAB,
                                        const QMatLDouble &chiSq,
                                        QVecLDouble &minAlpha,
                                        QVecLDouble &minBeta,
                                        refGrid grid)
{
    if(grid == gridOnAlpha)
    {
        int gridLength = axAlpha.size();
        minAlpha.reserve(gridLength);
        minBeta.reserve(gridLength);
        for(int i = 0; i < gridLength; ++i){
            int pos = minAt(chiSq[i]);
            if(axAlpha[i] > (axBeta[pos] + minDistAB)){
                minAlpha << axAlpha[i];
                minBeta << axBeta[pos];
            }
        }
    }
}

pairLDouble ShaShapeCalculator::findIntersection(const QVecLDouble &alpha1, const QVecLDouble &beta1,
                                                 const QVecLDouble &alpha2, const QVecLDouble &beta2,
                                                 bool * foundIntersection, ldouble *rms){


}

void ShaShapeCalculator::writeGnuPlotChiSqData(const QString &fileName,
                                               const QVecLDouble &axAlpha,
                                               const QVecLDouble &axBeta,
                                               const QMatLDouble &chiSq)
{
    // Write data file and replace nan/inf by missing sign"?"
    std::ofstream data;
    data.open(std::string(fileName.toStdString()));
    data << "# alpha" << " beta" << " chiSq" << "\n";
    //ldouble upLimit = (maxOf(chiSqS) - minOf(chiSqS)) * 0.01 +  minOf(chiSqS); // show only the lowest 20 %
    const ldouble lowLimit = minOf(chiSq);
    const ldouble highLimit = maxOf(chiSq);
    const ldouble deadValue = lowLimit - 1e-12 * (highLimit - lowLimit);
    // const ldouble deadValue = -1.0;
    for(int i = 0 ; i <  chiSq.size(); ++i){
       for(int j = 0 ; j < chiSq[i].size(); ++j){
          data << axAlpha[i] << " " << axBeta[j] << " ";
          if(std::isnormal(chiSq[i][j]) && axAlpha[i] > axBeta[j]){
             //if(std::isnormal(chiSq[i][j])){
             ldouble plotValue = chiSq[i][j];
             data << std::setprecision(15) << plotValue;
             }
          else data << std::setprecision(15) << deadValue;
          data << "\n";
       }
       data << "\n";
    }
}

    void ShaShapeCalculator::writeGnuPlotChiSqPlotScript(const QString &scriptFileName,
                                                     const QString &dataFileName,
                                                     const QString &imgFileName,
                                                     const QVecLDouble &axAlpha,
                                                     const QVecLDouble &axBeta
                                                     )
{
    // write gnuplot script for chiSqS and insert axis sizes (later also file paths)
    {
        std::ofstream script;
        script.open(scriptFileName.toStdString());
        script << "\
          # Auto generated gnuplot script ### \n\
              set terminal pngcairo  transparent enhanced font \"tex-gyre-schola, 48\" fontscale 1.0 size 1800, 1300 background rgb 'white'\n\
                  set termoption enhanced \n\
                  set output '" << imgFileName.toStdString() << "'\n\
                  unset key \n\
                  set view map \n\
                  set xtics border  0,10 mirror norotate  offset character 0, 0.9, 0 font \"tex-gyre-schola, 40\" autojustify \n\
                set ytics border 0,5 mirror norotate  offset character 0, 0.1, 0 font \"tex-gyre-schola, 40\" autojustify \n\
                set ztics border in scale 0,0 nomirror norotate  offset character 0, 0, 0 autojustify \n\
                set nocbtics \n\
                set rtics axis in scale 0,0 nomirror norotate  offset character 0, 0, 0 autojustify \n\
              set xrange [ " << axAlpha.first() << " : " << axAlpha.last() << " ] noreverse nowriteback \n\
                                                                                  set yrange [ " << axBeta.first() << " : " << axBeta.last() << " ] noreverse nowriteback\n\
                                                                                  set xlabel \'{/Symbol a} / nm\' enhanced offset character 0, 1.6, 0 font \"tex-gyre-schola, 48\" \n\
                                                                                  set ylabel \'{/Symbol b} / nm\' enhanced offset character 0, 0.2, 0 font \"tex-gyre-schola, 48\"\n\
                                                                                  set logscale cb\n\
                                                                                  set cblabel \'log_{10}({/Symbol D}^2\)' enhanced  font \"tex-gyre-schola, 42\"\n\
                                                                                  set palette defined (00 \"#FFFFFF\", 20 \"#FFFF33\", 30 \"#CC0000\", 40 \"#0000CC\", 50 \"#000000\" ) \n\
                                                                                    set datafile missing \"?\"\n\
                                                                                    splot '"<< dataFileName.toStdString() << "' with image\n\
                                                                                    ";
                                                                                    ;
    }
}

void ShaShapeCalculator::callGnuPlot(const QString &gnuplotPath, const QString &scriptFileName)
{
    QStringList arguments;
    arguments << scriptFileName;
    int retErr = QProcess::execute(gnuplotPath, arguments);
    if(retErr) ShaLog::logError(QObject::tr("gnuplot finished with error Code %1.").arg(retErr));
    else { ShaLog::logText(QObject::tr("gnuplot finished without errors.")); }
}

int ShaShapeCalculator::plotCSV(const QString &fileName,
                                const QStringList &headLine,
                                const QMatLDouble &plotValues) const
{
    if(headLine.size() != plotValues.size()) return 1;

    int noOfCols = plotValues.size();
    int last = noOfCols-1;
    QVector<bool> stopFlags;
    for(int i = 0; i < noOfCols; ++i) stopFlags << false;
    std::ofstream data;
    data.open(fileName.toStdString());
    //  for(const QString & s : headLine) data << s.toStdString();
    for(int i =0; i < noOfCols-1; ++i) data << headLine[i].toStdString() << ",";
    data << headLine[last].toStdString() << "\n";
    bool stopPlotting = false;
    int i = 0;
    while(!stopPlotting){
        for(int j = 0; j < noOfCols - 1; ++j){
            if(plotValues[j].size() - 1 > i)
                data << plotValues[j][i] << ",";
            else {
                data << "nan" << ","; stopFlags[j] = true;
            }
        }
        if(plotValues[last].size()-1 > i)
            data << plotValues[last][i] << "\n";
        else {
            data << "nan" << "\n"; stopFlags[last] = true;
        }
        stopPlotting = true;
        for(bool &b : stopFlags) stopPlotting &= b;
        ++i;
    }
    return 0;
}



void ShaShapeCalculator::createVectorFromTo(QVecLDouble &v, ldouble min, ldouble max, ldouble stride)
{
    int gridLength = int((max-min) / stride);
    v = QVecLDouble(gridLength);
    for(int i = 0; i < gridLength; ++i) v [ i ] = min + stride * static_cast<ldouble>(i);
    ++gridLength;
    v.append(max);
}

void ShaShapeCalculator::plotAlphaBetaOptima(const QString& outPutDirPath,
                                             const bool plotD, const QVecLDouble &minDAlpha, const QVecLDouble &minDBeta,
                                             const bool plotS, const QVecLDouble &minSAlpha, const QVecLDouble &minSBeta,
                                             const bool plotLam, const QVecLDouble &minLamAlpha, const QVecLDouble &minLamBeta,
                                             const bool plotDDev, const QVecLDouble &minDAlphaDevU, const QVecLDouble &minDBetaDevU,
                                             const QVecLDouble &minDAlphaDevL, const QVecLDouble &minDBetaDevL,
                                             const bool plotSDev, const QVecLDouble &minSAlphaDevU, const QVecLDouble &minSBetaDevU,
                                             const QVecLDouble &minSAlphaDevL, const QVecLDouble &minSBetaDevL,
                                             const bool plotLamDev, const QVecLDouble &minLamAlphaDevU, const QVecLDouble &minLamBetaDevU,
                                             const QVecLDouble &minLamAlphaDevL, const QVecLDouble &minLamBetaDevL) const
{
    // Write data file and replace nan/inf by missing sign"?"
    QStringList headLine;
    QMatLDouble plotValues;
    if(plotD){
        headLine << "alpha D" << "beta D";
        plotValues << minDAlpha << minDBeta;
    }
    if(plotS){
        headLine << "alpha S" << "beta S";
        plotValues << minSAlpha << minSBeta;
    }
    if(plotLam){
        headLine << "alpha lambda" << "beta lambda";
        plotValues << minLamAlpha << minLamBeta;
    }
    if(plotDDev){
        headLine << "alpha D UpLim" << "beta D UpLim" << "alpha D LowLim" << "beta D LowLim";
        plotValues << minDAlphaDevU << minDBetaDevU << minDAlphaDevL << minDBetaDevL;
    }
    if(plotSDev){
        headLine << "alpha S UpLim" << "beta S UpLim" << "alpha S LowLim" << "beta S LowLim";
        plotValues << minSAlphaDevU << minSBetaDevU << minSAlphaDevL << minSBetaDevL;
    }
    if(plotLamDev){
        headLine << "alpha Lam UpLim" << "beta Lam UpLim" << "alpha Lam LowLim" << "beta Lam LowLim";
        plotValues << minLamAlphaDevU << minLamBetaDevU << minLamAlphaDevL << minLamBetaDevL;
    }
    int err = plotCSV(tr("%1/optLines.csv").arg(outPutDirPath), headLine, plotValues);
    if(err == 1) ShaLog::logError(tr("Plotting alpha/beta failed; HeadLine incompatible with data set."));
}

