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
//////////////////////////////////////////////////////////////////////////
// HcrVelCorrect.hh
//
// Mike Dixon, EOL, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// March 2015
//
//////////////////////////////////////////////////////////////////////////
//
// HcrVelCorrect reads in HCR moments, computes the apparent velocity
// of the ground echo, filters the apparent velocity in time to remove
// spurious spikes, and then corrects the weather echo velocity using
// the filtered ground velocity as the correction to be applied.
//
// Also computes spectrum width corrected for aircraft motion.
//
//////////////////////////////////////////////////////////////////////////

#ifndef HcrVelCorrect_HH
#define HcrVelCorrect_HH

#include "Args.hh"
#include "Params.hh"
#include <string>
#include <deque>
#include <cmath>
#include <Radx/RadxVol.hh>
#include <Radx/RadxRay.hh>
#include <Radx/RadxField.hh>
#include <Radx/RadxTime.hh>
#include <radar/HcrSurfaceVel.hh>
#include <radar/HcrVelFirFilt.hh>
#include <radar/Egm2008.hh>
#include <rapformats/DsRadarMsg.hh>
#include <rapmath/PolyFit.hh>
class RadxFile;
class RadxRay;
using namespace std;

class HcrVelCorrect {
  
public:

  // constructor
  
  HcrVelCorrect (int argc, char **argv);

  // destructor
  
  ~HcrVelCorrect();

  // run 

  int Run();

  // data members

  int OK;

protected:
private:

  string _progName;
  char *_paramsPath;
  Args _args;
  Params _params;
  vector<string> _readPaths;

  // input volume files
  
  RadxVol _inVol;
  deque<RadxTime> _inputFileEndTime;

  // filtered volume - output
  
  RadxVol _filtVol;

  // Object for computing surface velocity
  
  HcrSurfaceVel _surfVel;

  // vel filtering results from either the FIR
  // or wave filter
  
  RadxRay *_filtRay;

  // FIR filtering

  HcrVelFirFilt _firFilt;

  // wave filtering

  PolyFit _poly;

  class FiltNode {
  public:
    RadxRay *ray;
    double velSurf;
    double dbzSurf;
    double rangeToSurf;
    double velNoiseFilt;
    double velWaveFilt;
    bool corrFieldAdded;
    FiltNode() {
      ray = NULL;
      velSurf = NAN;
      dbzSurf = NAN;
      rangeToSurf = NAN;
      velNoiseFilt = NAN;
      velWaveFilt = NAN;
      corrFieldAdded = false;
    }
    RadxTime getTime() { return ray->getRadxTime(); }
  };

  deque<FiltNode> _filtQueue;

  double _noiseFiltSecs;
  double _waveFiltSecs;

  FiltNode *_waveNodeMid;
  deque<FiltNode *> _nodesPending;

  size_t _noiseIndexStart;
  size_t _noiseIndexMid;
  size_t _noiseIndexEnd;

  size_t _waveIndexStart;
  size_t _waveIndexMid;
  size_t _waveIndexEnd;

  // altitude correction

  Egm2008 _egm;

  // methods

  int _runFilelist();
  int _runArchive();
  int _runRealtime();

  int _processFile(const string &filePath);

  int _processRayFirFilt(RadxRay *ray);
  int _processRayWaveFilt(RadxRay *ray);

  void _initWaveFilt();
  int _applyWaveFilt(RadxRay *ray, 
                     double velSurf,
                     double dbzSurf,
                     double rangeToSurf,
                     bool velIsValid);

  int _setWaveFilterLimits();

  int _runNoiseFilter();
  int _runWaveFilter();

  void _addNodeRayToFiltVol(FiltNode &node);

  void _setupRead(RadxFile &file);

  void _convertFieldsForOutput(RadxVol &vol);
  void _setupWrite(RadxFile &file);
  void _setGlobalAttr(RadxVol &vol);
  int _writeFiltVol();
  
  void _correctVelForRay(RadxRay *ray, double surfFilt);
  void _copyVelForRay(RadxRay *ray);

  void _addDeltaField(RadxRay *ray, double deltaVel);
  int _addCorrectedSpectrumWidth(RadxRay *ray);
  void _correctAltitudeForGeoid(RadxRay *ray);

  void _writeWaveFiltResultsToSpdb(FiltNode &node);
  void _writeFirFiltResultsToSpdb(const RadxRay *filtRay);
  

};

#endif
