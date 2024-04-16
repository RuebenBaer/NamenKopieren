#include <iostream>
#include <windows.h>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

void VerzeichnisInhaltLesen(std::string& strEinrueckung, fs::path pfad, std::string& pchContainer);
std::string tokenEinrueckung = "  ";

void copyToClipboard(std::string str)//const char *str)
{
    if(!OpenClipboard(NULL))
        return;

    EmptyClipboard();

    HGLOBAL hClipboardData;
    hClipboardData = GlobalAlloc(GMEM_DDESHARE, str.length()+1);

    char *pchData;
    pchData = (char*)GlobalLock(hClipboardData);
    strcpy(pchData, str.c_str());

    GlobalUnlock(hClipboardData);
    SetClipboardData(CF_TEXT, hClipboardData);
    CloseClipboard();
    return;
}

extern int main(int argc, char **argv)
{
    std::string pchContainer;
    if(argc > 1)
    {
        char *pchBuffer;
        for(int i = 1; i < argc; i++)
        {
          if(i!=1)
          pchContainer += "\n";
          pchBuffer = strrchr(argv[i], '\\');

          fs::path pfad(argv[i]);
      		if(fs::exists(pfad))
      		{
      			if(fs::is_directory(pfad))
      			{
              pchContainer += "*";
              pchContainer += ++pchBuffer;
              std::string strEinrueckung = tokenEinrueckung;
      				VerzeichnisInhaltLesen(strEinrueckung, pfad, pchContainer);
      			}else if(fs::is_regular_file(pfad))
            {
              pchContainer += ++pchBuffer;
            }
      		}
        }
        copyToClipboard(pchContainer);
    }
    return EXIT_SUCCESS;
}

void VerzeichnisInhaltLesen(std::string& strEinrueckung, fs::path pfad, std::string& pchContainer)
{
  std::string strNeueEinrueckung;
  for(auto&& x : fs::directory_iterator(pfad))
  {
    fs::path xPfad = x.path();
    if(fs::is_directory(xPfad))
    {
      pchContainer += "\n" + strEinrueckung + "*" + xPfad.filename().generic_string();
      strNeueEinrueckung = strEinrueckung + tokenEinrueckung;
      VerzeichnisInhaltLesen(strNeueEinrueckung, xPfad, pchContainer);
    }else if(fs::is_regular_file(xPfad))
    {
      pchContainer += "\n" + strEinrueckung + xPfad.filename().generic_string();
    }
  }
  return;
}
