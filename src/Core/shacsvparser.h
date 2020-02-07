#ifndef SHACSVPARSER_H
#define SHACSVPARSER_H
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <algorithm>
#include <qdebug.h>
#include "../Gui/shalog_omp.h"

/*! ***********************************************************
***
***  \class     ShaCsvParser "src/Core/af4csvparser.h"
***  \author    Benedikt Häusele
***  \version   1.0
***  \date      2018
***  \copyright 4-clause BSD-license
***
**************************************************************/

class ShaCsvParser final
{

public:
   /*!
    * \brief AF4CsvParser
    * \param filePath absolute path of the file to be read
    */
   explicit ShaCsvParser(const std::string& filePath,
                         const char sep,
                         const char dec
                         );

   /*!
    * \brief ~FFFCsvParser Default Destructor
    */
   ~ShaCsvParser(){}

   /*!
    * \brief parseFile is used to the parse the file and create the data structures
    * \brief errorInLine indicates the line in the file where a possible error occured
    * \return integer indicates errorvalue
    */
   int parseFile(uint *badLineNo = nullptr);

   int parseFileASCII(std::ifstream &inpFile, uint *badLineNo);


   /*!
    * \brief getHeadLines returns a vector with the entries of the headline of the csv-file.
    *        Has
    * \return Pointer to the data on heap. Use delete on this address
    *         as soon as you don't need data are not need anymore!
    */
   std::vector<std::string> getHeadLines() const;

   /*!
    * \brief getHeadLines returns a vector with data columns, which are stored in a vector
    *        themselves each. Access: data->at(column)->at(row)
    * \return Pointer to the data on heap. Use delete on this address
    *         as soon as you don't need data are not need anymore!
    */
   matD getData() const;

   bool dataIsComplete(matD &data);

private:

   /////////////
   // Members //
   /////////////

   const std::string filePath;
   const char sep;
   const char dec;

   std::vector<std::string> headLineEntries;
   matD dataVectorList;


   /////////////////////////
   // Protected functions //
   /////////////////////////

   std::vector<std::string> split(const std::string& s,
                                  const char delim,
                                  const bool keepEmpty = false) const;
   std::vector<std::wstring> split(const std::wstring& str,
                                   const wchar_t delim,
                                   const bool keepEmpty = false) const;


   std::string::const_iterator findCharPos(std::string::const_iterator start,
                                           std::string::const_iterator end,
                                           const char c) const;

   NO_COPY_ASSIGNMENT_CTORS(ShaCsvParser)
};

#endif // SHACSVPARSER_H
