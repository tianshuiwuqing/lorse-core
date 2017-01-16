// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
// ** Copyright UCAR (c) 1990 - 2016                                         
// ** University Corporation for Atmospheric Research (UCAR)                 
// ** National Center for Atmospheric Research (NCAR)                        
// ** Boulder, Colorado, USA                                                 
// ** BSD licence applies - redistribution and use in source and binary      
// ** forms, with or without modification, are permitted provided that       
// ** the following conditions are met:                                      
// ** 1) If the software is modified to produce derivative works,            
// ** such modified software should be clearly marked, so as not             
// ** to confuse it with the version available from UCAR.                    
// ** 2) Redistributions of source code must retain the above copyright      
// ** notice, this list of conditions and the following disclaimer.          
// ** 3) Redistributions in binary form must reproduce the above copyright   
// ** notice, this list of conditions and the following disclaimer in the    
// ** documentation and/or other materials provided with the distribution.   
// ** 4) Neither the name of UCAR nor the names of its contributors,         
// ** if any, may be used to endorse or promote products derived from        
// ** this software without specific prior written permission.               
// ** DISCLAIMER: THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS  
// ** OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      
// ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.    
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
/////////////////////////////////////////////////////////////
// RadxPartRain.hh
//
// RadxPartRain object
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// March 2012
//
///////////////////////////////////////////////////////////////
//
// RadxPartRain reads moments from Radx-supported format files, 
// computes the PID and PRECIP rates and writes out the results 
// to Radx-supported format files
//
///////////////////////////////////////////////////////////////

#ifndef RadxPartRain_H
#define RadxPartRain_H

#include "Args.hh"
#include "Params.hh"
#include "ComputeEngine.hh"
#include <string>
#include <deque>
#include <radar/NoiseLocator.hh>
#include <radar/KdpBringi.hh>
#include <radar/TempProfile.hh>
#include <Radx/RadxVol.hh>
#include <Radx/RadxArray.hh>
#include <Radx/PseudoRhi.hh>
class RadxVol;
class RadxFile;
class RadxRay;
class RadxField;
class ComputeThread;
using namespace std;

class RadxPartRain {
  
public:

  // constructor
  
  RadxPartRain (int argc, char **argv);

  // destructor
  
  ~RadxPartRain();

  // run 

  int Run();

  // data members

  int OK;

  // get methods for threading

  const Params &getParams() const { return _params; }
  pthread_mutex_t *getDebugPrintMutex() { return &_debugPrintMutex; }

  // names for extra fields

  static string smoothedDbzFieldName;
  static string elevationFieldName;
  static string rangeFieldName;
  static string beamHtFieldName;
  static string tempFieldName;
  static string pidFieldName;
  static string pidInterestFieldName;
  static string mlFieldName;
  static string mlExtendedFieldName;
  static string convFlagFieldName;
  
protected:
private:

  string _progName;
  char *_paramsPath;
  Args _args;
  Params _params;
  vector<string> _readPaths;

  // radar volume container

  RadxVol _vol;

  // computations object

  ComputeEngine *_engine;

  // derived rays - after compute

  vector <RadxRay *> _derivedRays;

  // radar properties

  double _radarHtKm;
  double _wavelengthM;

  // temperature profile from sounding, if appropriate

  TempProfile _tempProfile;

  // stats for ZDR bias

  class ZdrStats {
  public:
    void clear() {
      count = 0.0;
      sum = 0.0;
      mean = NAN;
      percentiles.clear();
    }
    double sum;
    double count;
    double mean;
    vector<double> percentiles;
  };
  ZdrStats _zdrmStatsIce;
  ZdrStats _zdrmStatsBragg;
  ZdrStats _zdrStatsIce;
  ZdrStats _zdrStatsBragg;
  
  vector<double> _zdrInIceResults;
  vector<double> _zdrInBraggResults;
  vector<double> _zdrmInIceResults;
  vector<double> _zdrmInBraggResults;

  // site temp

  double _siteTempC;
  time_t _timeForSiteTemp;

  // self consistency

  vector<ComputeEngine::self_con_t> _selfConResults;

  // threading
  
  deque<ComputeThread *> _activeThreads;
  deque<ComputeThread *> _availThreads;
  pthread_mutex_t _debugPrintMutex;

  // pseudo RHIs

  vector<PseudoRhi *> _pseudoRhis;

  // private methods
  
  int _runFilelist();
  int _runArchive();
  int _runRealtime();
  void _setupRead(RadxFile &file);
  void _setupWrite(RadxFile &file);
  int _writeVol();
  int _processFile(const string &filePath);
  void _encodeFieldsForOutput();
  
  void _addExtraFieldsToInput();
  void _addExtraFieldsToOutput();

  int _compute();
  int _computeSingleThreaded();
  int _computeMultiThreaded();
  int _storeDerivedRay(ComputeThread *thread);
  static void *_computeInThread(void *thread_data);

  int _retrieveTempProfile();
  int _retrieveSiteTempFromSpdb(double &tempC,
                                time_t &timeForTemp);

  void _computeZdrBias();

  void _loadZdrResults(vector<double> &results,
                       ZdrStats &stats,
                       int nPercentiles,
                       double *percentiles);

  double _computeZdrPerc(const vector<double> &zdrmResults,
                         double percent);

  void _computeSelfConZBias();

  void _locateMeltingLayer();
  void _checkForConvection(double htMlTop);
  void _expandMlRhi(double htMlTop, double dbzThreshold);
  void _expandMlPpi(double htMlTop, double dbzThreshold);
  
  void _applyInfillFilter(int nGates,
                          Radx::si32 *flag);
  
  void _applyInfillFilter(int nGates,
                          Radx::si32 *flag,
                          bool removeShortRuns);
  
};

#endif
