#include "shacsvparser.h"
#include <locale>

using std::string;
using std::wstring;
using std::stringstream;
using std::ifstream;
using std::vector;

ShaCsvParser::ShaCsvParser(const string& filePath, const char sep, const char dec) :
   filePath(filePath), sep(sep), dec(dec)
{
}

int ShaCsvParser::parseFile(uint *badLineNo)
{
   headLineEntries.clear();
   dataVectorList.clear();
   ifstream inpFile;
   inpFile.open(filePath.c_str());
   if(!inpFile.is_open()){
      ShaLog::logError(string("File could not be opened."), true);
      return 1;
   }

   string firstLine;
   std::getline(inpFile, firstLine);
   inpFile.seekg(0);

   if(firstLine.size() == 0 ){
      return 5;
   }

   return parseFileASCII(inpFile, badLineNo);

}

int ShaCsvParser::parseFileASCII(ifstream &inpFile, uint* badLineNo)
{
   string dataLine;
   std::getline(inpFile, dataLine);
   dataLine.erase(std::remove(dataLine.begin(), dataLine.end(), '\n'), dataLine.end());
   dataLine.erase(std::remove(dataLine.begin(), dataLine.end(), '\r'), dataLine.end());
   headLineEntries = split(dataLine, sep); // first line = header


   if(badLineNo) *badLineNo = 1;
   dataVectorList.resize(headLineEntries.size());

   while(std::getline(inpFile, dataLine))
   {
      vector<string> dataSplit = split(dataLine, sep);
      for(uint i = 0; i < dataSplit.size(); ++i){
         double d = std::strtod(dataSplit[i].c_str(), nullptr);
         dataVectorList[i].push_back(d);
      }
      if(badLineNo) ++(*badLineNo);
   }

   return 0;
}

vector<string> ShaCsvParser::getHeadLines() const
{
   return headLineEntries;
}

matD ShaCsvParser::getData() const
{
   return dataVectorList;
}

bool ShaCsvParser::dataIsComplete(matD &data)
{
   if (data.size() <= 1) return false;
   const uint length = data[0].size();
   for(uint i = 1; i < data.size(); ++i)
      if (data[i].size() != length) return false;
   return true;
}

vector<string> ShaCsvParser::split(const string& s,
                                   const char delim,
                                   const bool keepEmpty) const {
   vector<string> result;
   string::const_iterator substart = s.begin();
   string::const_iterator subend = substart;
   while (subend != s.end()) {
      subend = findCharPos(substart, s.end(), delim);
      string subElem(substart, subend);
      if (keepEmpty || !subElem.empty())
         result.push_back(std::move(subElem));
      substart = subend + 1;
   }
   return result;
}

auto ShaCsvParser::findCharPos(std::string::const_iterator start,
                               std::string::const_iterator end,
                               const char c) const -> std::string::const_iterator
{
   do {
      if(c == *start) return start;
      ++start;
   } while(start != end);
   return end;
}
