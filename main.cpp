
#ifdef __WIN32
#include "XGetopt.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "langen.h"
#include "logger.h"
#include "constants.h"

#include <iostream>
#include <fstream>

#include <QtWidgets/QApplication>

void allocConsole();
void deallocConsole();
void displayVersion(const char*);
void displayHelp(const char*);

void cmdOut(char*);              // simple command line output for debugging
void fileOut(char*);

std::ofstream debugLog;

int main(int argc, char* argv[])
{
  int retVal = 0;
  int debugLevel = 3;                               // default level is warning or higher
  int choice = -1;

  allocConsole();

  while (-1 != (choice = getopt(argc, argv, "dvh")))
  {
    switch (choice)
    {
    case 'd':                                    // modify the debug level, lower number is more verbose
      --debugLevel;
      if (debugLevel < 0) debugLevel = 0;
      if (debugLevel > 5) debugLevel = 5;
      break;

    case 'v':                                    // show current version of the application
      displayVersion(argv[0]);
      exit(retVal);

    case '?':                                    // unknown command line option
      std::cout << "unknown command line argument " << argv[optind] << std::endl;
      // fall through is intended
    case 'h':                                    // help screen
      displayHelp(argv[0]);
      exit(retVal);
    }
  }


  QApplication a(argc, argv);

  CLogger* pLogger = CLogger::getInstance();
  pLogger->setLevel(debugLevel);
  pLogger->regOutDevice(cmdLine, cmdOut);
  pLogger->regOutDevice(fileLine, fileOut);

  debugLog.open(".\\debugLog.txt");

  LanGen w;
  w.show();
  retVal = a.exec();

  pLogger->outMsg(cmdLine, CLogger::level::NOTICE, "...logging terminated");
  debugLog.close();
  pLogger->delInstance();

  deallocConsole();
}

void displayVersion(const char* progName)
{
  std::cout << progName << "\nA word generator based on phonemes" << std::endl;
  std::cout << "Version is : " << major << "." << minor << "." << patch << std::endl;
}

void displayHelp(const char* progName)
{

}

// printing debugging information, status information is common and helpful...
// except if you are brain-dead idiots from Microsoft who disable this stuff
// So, lets fix this.  (taken from Adding Console I/O to a Win32 GUI App,
// Windows Developer Journal, Dec 1997; and updated from 
// https://smacdo.com/programming/redirecting-standard-output-to-console-in-windows/)
//
void allocConsole()
#ifdef __WIN32                 // code for Windows...
{
  // Create the console window and set the window title.
  if (AllocConsole() == 0)
  {
    // Handle error here. Use ::GetLastError() to get the error.
  }

  // Redirect CRT standard input, output and error handles to the console window.
  FILE* pNewStdout = nullptr;
  FILE* pNewStderr = nullptr;
  FILE* pNewStdin = nullptr;

  ::freopen_s(&pNewStdout, "CONOUT$", "w", stdout);
  ::freopen_s(&pNewStderr, "CONOUT$", "w", stderr);
  ::freopen_s(&pNewStdin, "CONIN$", "r", stdin);

  // Clear the error state for all of the C++ standard streams. Attempting to accessing the streams before they refer
  // to a valid target causes the stream to enter an error state. Clearing the error state will fix this problem,
  // which seems to occur in newer version of Visual Studio even when the console has not been read from or written
  // to yet.

  std::cout.clear();
  std::cerr.clear();
  std::cin.clear();

  std::wcout.clear();
  std::wcerr.clear();
  std::wcin.clear();
}
#else                              // code for Linux...wait there is none, Linux is not brain-dead
{

}
#endif


void deallocConsole()
#ifdef __WIN32                    // code for Windows, clean up our mess
{
  FreeConsole();
}
#else                             // code for Linux...nothing to do
{

}
#endif


void cmdOut(char* msg)
{
  std::cout << msg << std::endl;
}

void fileOut(char* msg)
{
  debugLog << msg << std::endl;
}

