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
// Threads.hh
//
// Mike Dixon, EOL, NCAR
// P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// Aug 2019
//
///////////////////////////////////////////////////////////////
//
// Classes for dealing with threads
//
///////////////////////////////////////////////////////////////

#ifndef Threads_hh
#define Threads_hh

#include <pthread.h>
#include <radar/RadarFft.hh>
class BeamReader;
class OutputFmq;
class Beam;
class AparTs2Moments;
class Params;

using namespace std;

////////////////////////////
// Generic thread base class

class Thread {
public:
  
  Thread();
  virtual ~Thread();

  // thread details

  inline void setThreadId(pthread_t val) { _thread = val; }
  
  // application context

  inline void setApp(AparTs2Moments *val) { _app = val; }
  inline AparTs2Moments *getApp() const { return _app; }

  inline void setBeam(Beam *val) { _beam = val; }
  inline Beam *getBeam() const { return _beam; }

  // return code
  
  inline void setReturnCode(int val) { _returnCode = val; }
  inline int getReturnCode() const { return _returnCode; }

  //////////////////////////////////////////////////////////////
  // Mutex handling for communication between caller and thread
  
  // Parent signals thread to start work
  
  void signalWorkToStart();
  
  // Thread waits for parent to signal start

  void waitForStartSignal();

  // Thread signals parent it is complete

  void signalParentWorkIsComplete();

  // Parent waits for thread to be complete

  void waitForWorkToComplete();

  // Mark thread as available

  void markAsAvailable();

  // Wait for thread to be available

  void waitToBeAvailable();
  
  // get flag indicating thread is available

  bool getAvailFlag();

  // set flag to tell thread to exit

  void setExitFlag(bool val);

  // get flag indicating thread should exit

  bool getExitFlag();

protected:

  pthread_t _thread;

  pthread_mutex_t _startMutex;
  pthread_mutex_t _completeMutex;
  pthread_mutex_t _availMutex;
  pthread_mutex_t _exitMutex;

  pthread_cond_t _startCond;
  pthread_cond_t _completeCond;
  pthread_cond_t _availCond;

  bool _startFlag;
  bool _completeFlag;
  bool _availFlag;
  bool _exitFlag;

  // application context

  AparTs2Moments *_app;
  Beam *_beam;

  // return code
  
  int _returnCode;

private:

};

//////////////////////////////
// Moments computation thread

class ComputeThread : public Thread 

{

public:

  ComputeThread();
  virtual ~ComputeThread();
  void initFfts(int nSamples);
  void initFftsStag(int nSamples, int stagM, int stagN);

  //////////////////////////////////////////////////////////////
  // create and destroy FFT objects in a thread safe manner
  
  static RadarFft *createFft(int nSamples);
  static void destroyFft(RadarFft *fft);

  // start and end gates

  int startGate;
  int endGate;

  // FFT support
  
  int nSamplesFft;
  RadarFft *fft;
  RadarFft *fftHalf;

  // FFT support - staggered mode
  
  int nSamplesFftStag;
  int fftStagM, fftStagN;
  RadarFft *fftStag;
  
private:

  static pthread_mutex_t _fftMutex;

};

//////////////////////////////
// Output FMQ writing thread

class WriteThread : public Thread

{

public:

  WriteThread();
  virtual ~WriteThread();

  inline void setVolNum(int val) { _volNum = val; }
  int getVolNum() const { return _volNum; }

  inline void setTiltNum(int val) { _tiltNum = val; }
  int getTiltNum() const { return _tiltNum; }
  
private:
  
  int _volNum;
  int _tiltNum;

};

#endif

