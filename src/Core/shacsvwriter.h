#ifndef AF4CSVWRITER_H
#define AF4CSVWRITER_H
#include <string>
#include <fstream>
#include <list>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <iomanip>
//#include "./af4constants.h"
//#include "./af4datatypes.h"

#include "../Gui/shalog_omp.h"

/*! ***********************************************************
***
***  \class     AF4CSVWriter "src/Core/af4csvwriter.h"
***  \author    Benedikt Häusele
***  \version   1.0
***  \date      2018
***  \copyright CC CC BY-NC-ND 4.0
***
**************************************************************/

class ShaCsvWriter final
{
public:

   /*!
    * \brief FFFCsvWriter is the constructor of the class.
    * \param filePath path of the file. A file that already exists will be overwritten
    */
   explicit ShaCsvWriter(const std::string& filePath) :
   filePath(filePath), sep(','), dec('.'), lineSep('\n'){}

   /*!
    * \brief FFFCsvWriter Default destructor
    */
   ~ShaCsvWriter(){}

   /*!
    * \brief writeFile The function has to be called to write the file to the path stated above
    * \param data dataMatrix to be written. Format has to be data->at(column)->at(row).
    * \param headLineEntries are the entries that will form the headline
    *        headLineEntries-> has to be equal to data->size() !
    * \return bool indicates whether writing the fil was successful or not
    */
   bool writeFile(const matD &data, const std::vector<std::string>& headLineEntries);

   /*!
    * \brief maxElementIndex returns the index of the biggest uint-Element.
    * \param searchData vector
    * \param startIndex start search here
    * \param EndIndex end search here
    * \param maxElementValue can be used to return the actual value of the biggest element
    * \return the index of the biggest element
    */
   uint maxElementIndex(const std::vector<uint>& searchData, uint startIndex, uint EndIndex,
                        uint* maxElementValue = nullptr) const;
private:
   const std::string filePath;
   const char sep;
   const char dec;
   const char lineSep;

   NO_COPY_ASSIGNMENT_CTORS(ShaCsvWriter)
};

#endif // AF4CSVWRITER_H
