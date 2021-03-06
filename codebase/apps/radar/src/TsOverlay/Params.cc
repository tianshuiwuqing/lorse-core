/* *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* */
/* ** Copyright UCAR                                                         */
/* ** University Corporation for Atmospheric Research (UCAR)                 */
/* ** National Center for Atmospheric Research (NCAR)                        */
/* ** Boulder, Colorado, USA                                                 */
/* ** BSD licence applies - redistribution and use in source and binary      */
/* ** forms, with or without modification, are permitted provided that       */
/* ** the following conditions are met:                                      */
/* ** 1) If the software is modified to produce derivative works,            */
/* ** such modified software should be clearly marked, so as not             */
/* ** to confuse it with the version available from UCAR.                    */
/* ** 2) Redistributions of source code must retain the above copyright      */
/* ** notice, this list of conditions and the following disclaimer.          */
/* ** 3) Redistributions in binary form must reproduce the above copyright   */
/* ** notice, this list of conditions and the following disclaimer in the    */
/* ** documentation and/or other materials provided with the distribution.   */
/* ** 4) Neither the name of UCAR nor the names of its contributors,         */
/* ** if any, may be used to endorse or promote products derived from        */
/* ** this software without specific prior written permission.               */
/* ** DISCLAIMER: THIS SOFTWARE IS PROVIDED 'AS IS' AND WITHOUT ANY EXPRESS  */
/* ** OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      */
/* ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.    */
/* *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* */
////////////////////////////////////////////
// Params.cc
//
// TDRP C++ code file for class 'Params'.
//
// Code for program TsOverlay
//
// This file has been automatically
// generated by TDRP, do not modify.
//
/////////////////////////////////////////////

/**
 *
 * @file Params.cc
 *
 * @class Params
 *
 * This class is automatically generated by the Table
 * Driven Runtime Parameters (TDRP) system
 *
 * @note Source is automatically generated from
 *       paramdef file at compile time, do not modify
 *       since modifications will be overwritten.
 *
 *
 * @author Automatically generated
 *
 */
#include "Params.hh"
#include <cstring>

  ////////////////////////////////////////////
  // Default constructor
  //

  Params::Params()

  {

    // zero out table

    memset(_table, 0, sizeof(_table));

    // zero out members

    memset(&_start_, 0, &_end_ - &_start_);

    // class name

    _className = "Params";

    // initialize table

    _init();

    // set members

    tdrpTable2User(_table, &_start_);

    _exitDeferred = false;

  }

  ////////////////////////////////////////////
  // Copy constructor
  //

  Params::Params(const Params& source)

  {

    // sync the source object

    source.sync();

    // zero out table

    memset(_table, 0, sizeof(_table));

    // zero out members

    memset(&_start_, 0, &_end_ - &_start_);

    // class name

    _className = "Params";

    // copy table

    tdrpCopyTable((TDRPtable *) source._table, _table);

    // set members

    tdrpTable2User(_table, &_start_);

    _exitDeferred = false;

  }

  ////////////////////////////////////////////
  // Destructor
  //

  Params::~Params()

  {

    // free up

    freeAll();

  }

  ////////////////////////////////////////////
  // Assignment
  //

  void Params::operator=(const Params& other)

  {

    // sync the other object

    other.sync();

    // free up any existing memory

    freeAll();

    // zero out table

    memset(_table, 0, sizeof(_table));

    // zero out members

    memset(&_start_, 0, &_end_ - &_start_);

    // copy table

    tdrpCopyTable((TDRPtable *) other._table, _table);

    // set members

    tdrpTable2User(_table, &_start_);

    _exitDeferred = other._exitDeferred;

  }

  ////////////////////////////////////////////
  // loadFromArgs()
  //
  // Loads up TDRP using the command line args.
  //
  // Check usage() for command line actions associated with
  // this function.
  //
  //   argc, argv: command line args
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   char **params_path_p:
  //     If this is non-NULL, it is set to point to the path
  //     of the params file used.
  //
  //   bool defer_exit: normally, if the command args contain a 
  //      print or check request, this function will call exit().
  //      If defer_exit is set, such an exit is deferred and the
  //      private member _exitDeferred is set.
  //      Use exidDeferred() to test this flag.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadFromArgs(int argc, char **argv,
                           char **override_list,
                           char **params_path_p,
                           bool defer_exit)
  {
    int exit_deferred;
    if (_tdrpLoadFromArgs(argc, argv,
                          _table, &_start_,
                          override_list, params_path_p,
                          _className,
                          defer_exit, &exit_deferred)) {
      return (-1);
    } else {
      if (exit_deferred) {
        _exitDeferred = true;
      }
      return (0);
    }
  }

  ////////////////////////////////////////////
  // loadApplyArgs()
  //
  // Loads up TDRP using the params path passed in, and applies
  // the command line args for printing and checking.
  //
  // Check usage() for command line actions associated with
  // this function.
  //
  //   const char *param_file_path: the parameter file to be read in
  //
  //   argc, argv: command line args
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   bool defer_exit: normally, if the command args contain a 
  //      print or check request, this function will call exit().
  //      If defer_exit is set, such an exit is deferred and the
  //      private member _exitDeferred is set.
  //      Use exidDeferred() to test this flag.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadApplyArgs(const char *params_path,
                            int argc, char **argv,
                            char **override_list,
                            bool defer_exit)
  {
    int exit_deferred;
    if (tdrpLoadApplyArgs(params_path, argc, argv,
                          _table, &_start_,
                          override_list,
                          _className,
                          defer_exit, &exit_deferred)) {
      return (-1);
    } else {
      if (exit_deferred) {
        _exitDeferred = true;
      }
      return (0);
    }
  }

  ////////////////////////////////////////////
  // isArgValid()
  // 
  // Check if a command line arg is a valid TDRP arg.
  //

  bool Params::isArgValid(const char *arg)
  {
    return (tdrpIsArgValid(arg));
  }

  ////////////////////////////////////////////
  // isArgValid()
  // 
  // Check if a command line arg is a valid TDRP arg.
  // return number of args consumed.
  //

  int Params::isArgValidN(const char *arg)
  {
    return (tdrpIsArgValidN(arg));
  }

  ////////////////////////////////////////////
  // load()
  //
  // Loads up TDRP for a given class.
  //
  // This version of load gives the programmer the option to load
  // up more than one class for a single application. It is a
  // lower-level routine than loadFromArgs, and hence more
  // flexible, but the programmer must do more work.
  //
  //   const char *param_file_path: the parameter file to be read in.
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   expand_env: flag to control environment variable
  //               expansion during tokenization.
  //               If TRUE, environment expansion is set on.
  //               If FALSE, environment expansion is set off.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::load(const char *param_file_path,
                   char **override_list,
                   int expand_env, int debug)
  {
    if (tdrpLoad(param_file_path,
                 _table, &_start_,
                 override_list,
                 expand_env, debug)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // loadFromBuf()
  //
  // Loads up TDRP for a given class.
  //
  // This version of load gives the programmer the option to
  // load up more than one module for a single application,
  // using buffers which have been read from a specified source.
  //
  //   const char *param_source_str: a string which describes the
  //     source of the parameter information. It is used for
  //     error reporting only.
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   const char *inbuf: the input buffer
  //
  //   int inlen: length of the input buffer
  //
  //   int start_line_num: the line number in the source which
  //     corresponds to the start of the buffer.
  //
  //   expand_env: flag to control environment variable
  //               expansion during tokenization.
  //               If TRUE, environment expansion is set on.
  //               If FALSE, environment expansion is set off.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadFromBuf(const char *param_source_str,
                          char **override_list,
                          const char *inbuf, int inlen,
                          int start_line_num,
                          int expand_env, int debug)
  {
    if (tdrpLoadFromBuf(param_source_str,
                        _table, &_start_,
                        override_list,
                        inbuf, inlen, start_line_num,
                        expand_env, debug)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // loadDefaults()
  //
  // Loads up default params for a given class.
  //
  // See load() for more detailed info.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadDefaults(int expand_env)
  {
    if (tdrpLoad(NULL,
                 _table, &_start_,
                 NULL, expand_env, FALSE)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // sync()
  //
  // Syncs the user struct data back into the parameter table,
  // in preparation for printing.
  //
  // This function alters the table in a consistent manner.
  // Therefore it can be regarded as const.
  //

  void Params::sync(void) const
  {
    tdrpUser2Table(_table, (char *) &_start_);
  }

  ////////////////////////////////////////////
  // print()
  // 
  // Print params file
  //
  // The modes supported are:
  //
  //   PRINT_SHORT:   main comments only, no help or descriptions
  //                  structs and arrays on a single line
  //   PRINT_NORM:    short + descriptions and help
  //   PRINT_LONG:    norm  + arrays and structs expanded
  //   PRINT_VERBOSE: long  + private params included
  //

  void Params::print(FILE *out, tdrp_print_mode_t mode)
  {
    tdrpPrint(out, _table, _className, mode);
  }

  ////////////////////////////////////////////
  // checkAllSet()
  //
  // Return TRUE if all set, FALSE if not.
  //
  // If out is non-NULL, prints out warning messages for those
  // parameters which are not set.
  //

  int Params::checkAllSet(FILE *out)
  {
    return (tdrpCheckAllSet(out, _table, &_start_));
  }

  //////////////////////////////////////////////////////////////
  // checkIsSet()
  //
  // Return TRUE if parameter is set, FALSE if not.
  //
  //

  int Params::checkIsSet(const char *paramName)
  {
    return (tdrpCheckIsSet(paramName, _table, &_start_));
  }

  ////////////////////////////////////////////
  // freeAll()
  //
  // Frees up all TDRP dynamic memory.
  //

  void Params::freeAll(void)
  {
    tdrpFreeAll(_table, &_start_);
  }

  ////////////////////////////////////////////
  // usage()
  //
  // Prints out usage message for TDRP args as passed
  // in to loadFromArgs().
  //

  void Params::usage(ostream &out)
  {
    out << "TDRP args: [options as below]\n"
        << "   [ -params/--params path ] specify params file path\n"
        << "   [ -check_params/--check_params] check which params are not set\n"
        << "   [ -print_params/--print_params [mode]] print parameters\n"
        << "     using following modes, default mode is 'norm'\n"
        << "       short:   main comments only, no help or descr\n"
        << "                structs and arrays on a single line\n"
        << "       norm:    short + descriptions and help\n"
        << "       long:    norm  + arrays and structs expanded\n"
        << "       verbose: long  + private params included\n"
        << "       short_expand:   short with env vars expanded\n"
        << "       norm_expand:    norm with env vars expanded\n"
        << "       long_expand:    long with env vars expanded\n"
        << "       verbose_expand: verbose with env vars expanded\n"
        << "   [ -tdrp_debug] debugging prints for tdrp\n"
        << "   [ -tdrp_usage] print this usage\n";
  }

  ////////////////////////////////////////////
  // arrayRealloc()
  //
  // Realloc 1D array.
  //
  // If size is increased, the values from the last array 
  // entry is copied into the new space.
  //
  // Returns 0 on success, -1 on error.
  //

  int Params::arrayRealloc(const char *param_name, int new_array_n)
  {
    if (tdrpArrayRealloc(_table, &_start_,
                         param_name, new_array_n)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // array2DRealloc()
  //
  // Realloc 2D array.
  //
  // If size is increased, the values from the last array 
  // entry is copied into the new space.
  //
  // Returns 0 on success, -1 on error.
  //

  int Params::array2DRealloc(const char *param_name,
                             int new_array_n1,
                             int new_array_n2)
  {
    if (tdrpArray2DRealloc(_table, &_start_, param_name,
                           new_array_n1, new_array_n2)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // _init()
  //
  // Class table initialization function.
  //
  //

  void Params::_init()

  {

    TDRPtable *tt = _table;

    // Parameter 'Comment 0'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 0");
    tt->comment_hdr = tdrpStrDup("TsOverlay reads raw time-series data from two sets of files. It combines these time series by summing the I and Q data, to create an overlaid data set. Typically this is used for combining clutter and weather data together, for testing the clutter mitigation algorithms.");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'Comment 1'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 1");
    tt->comment_hdr = tdrpStrDup("DEBUGGING AND PROCESS CONTROL.");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'debug'
    // ctype is '_debug_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("debug");
    tt->descr = tdrpStrDup("Debug option");
    tt->help = tdrpStrDup("If set, debug messages will be printed appropriately");
    tt->val_offset = (char *) &debug - &_start_;
    tt->enum_def.name = tdrpStrDup("debug_t");
    tt->enum_def.nfields = 4;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("DEBUG_OFF");
      tt->enum_def.fields[0].val = DEBUG_OFF;
      tt->enum_def.fields[1].name = tdrpStrDup("DEBUG_NORM");
      tt->enum_def.fields[1].val = DEBUG_NORM;
      tt->enum_def.fields[2].name = tdrpStrDup("DEBUG_VERBOSE");
      tt->enum_def.fields[2].val = DEBUG_VERBOSE;
      tt->enum_def.fields[3].name = tdrpStrDup("DEBUG_EXTRA");
      tt->enum_def.fields[3].val = DEBUG_EXTRA;
    tt->single_val.e = DEBUG_OFF;
    tt++;
    
    // Parameter 'Comment 2'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 2");
    tt->comment_hdr = tdrpStrDup("INPUT DATA");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'primary_file_paths'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("primary_file_paths");
    tt->descr = tdrpStrDup("Primary time series data files.");
    tt->help = tdrpStrDup("This is an array of file paths, that are read in sequence, for the primary data set.");
    tt->array_offset = (char *) &_primary_file_paths - &_start_;
    tt->array_n_offset = (char *) &primary_file_paths_n - &_start_;
    tt->is_array = TRUE;
    tt->array_len_fixed = FALSE;
    tt->array_elem_size = sizeof(char*);
    tt->array_n = 4;
    tt->array_vals = (tdrpVal_t *)
        tdrpMalloc(tt->array_n * sizeof(tdrpVal_t));
      tt->array_vals[0].s = tdrpStrDup("/d1/dixon/data/tsarchive/overlay/weather/20111221_091607_005_153.sur_trans.iwrf_ts");
      tt->array_vals[1].s = tdrpStrDup("/d1/dixon/data/tsarchive/overlay/weather/20111221_091608_015_162.sur.iwrf_ts");
      tt->array_vals[2].s = tdrpStrDup("/d1/dixon/data/tsarchive/overlay/weather/20111221_091644_015_163.sur_trans.iwrf_ts");
      tt->array_vals[3].s = tdrpStrDup("/d1/dixon/data/tsarchive/overlay/weather/20111221_091645_025_172.sur.iwrf_ts");
    tt++;
    
    // Parameter 'secondary_file_paths'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("secondary_file_paths");
    tt->descr = tdrpStrDup("Secondary time series data files.");
    tt->help = tdrpStrDup("This is an array of file paths, that are read in sequence, for the secondary data set.");
    tt->array_offset = (char *) &_secondary_file_paths - &_start_;
    tt->array_n_offset = (char *) &secondary_file_paths_n - &_start_;
    tt->is_array = TRUE;
    tt->array_len_fixed = FALSE;
    tt->array_elem_size = sizeof(char*);
    tt->array_n = 2;
    tt->array_vals = (tdrpVal_t *)
        tdrpMalloc(tt->array_n * sizeof(tdrpVal_t));
      tt->array_vals[0].s = tdrpStrDup("/d1/dixon/data/tsarchive/overlay/clutter/20110107_155619_005_131.sur.iwrf_ts");
      tt->array_vals[1].s = tdrpStrDup("/d1/dixon/data/tsarchive/overlay/clutter/20110107_155621_005_150.sur.iwrf_ts");
    tt++;
    
    // Parameter 'primary_cal_file_path'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("primary_cal_file_path");
    tt->descr = tdrpStrDup("Path to XML calibration file for primary data.");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &primary_cal_file_path - &_start_;
    tt->single_val.s = tdrpStrDup("./primary_cal.xml");
    tt++;
    
    // Parameter 'secondary_cal_file_path'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("secondary_cal_file_path");
    tt->descr = tdrpStrDup("Path to XML calibration file for secondary data.");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &secondary_cal_file_path - &_start_;
    tt->single_val.s = tdrpStrDup("./secondary_cal.xml");
    tt++;
    
    // Parameter 'Comment 3'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 3");
    tt->comment_hdr = tdrpStrDup("CONFIGURING THE INPUT DATA");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'primary_start_azimuth'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("primary_start_azimuth");
    tt->descr = tdrpStrDup("Starting azimuth for the primary time series (deg).");
    tt->help = tdrpStrDup("Only pulses between the start and end azimuths will be used. Assumes clockwise rotation - i.e. this is the couterclockwise limit.");
    tt->val_offset = (char *) &primary_start_azimuth - &_start_;
    tt->single_val.d = 0;
    tt++;
    
    // Parameter 'primary_end_azimuth'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("primary_end_azimuth");
    tt->descr = tdrpStrDup("Ending azimuth for the primary time series (deg).");
    tt->help = tdrpStrDup("Only pulses between the start and end azimuths will be used. Assumes clockwise rotation - i.e. this is the clockwise limit.");
    tt->val_offset = (char *) &primary_end_azimuth - &_start_;
    tt->single_val.d = 0;
    tt++;
    
    // Parameter 'primary_start_range'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("primary_start_range");
    tt->descr = tdrpStrDup("Starting range for the primary data (km).");
    tt->help = tdrpStrDup("Gates before this range will be discarded.");
    tt->val_offset = (char *) &primary_start_range - &_start_;
    tt->single_val.d = 0;
    tt++;
    
    // Parameter 'primary_end_range'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("primary_end_range");
    tt->descr = tdrpStrDup("Ending range for the primary data (km).");
    tt->help = tdrpStrDup("Gates after this range will be discarded.");
    tt->val_offset = (char *) &primary_end_range - &_start_;
    tt->single_val.d = 150;
    tt++;
    
    // Parameter 'secondary_start_azimuth'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("secondary_start_azimuth");
    tt->descr = tdrpStrDup("Starting azimuth for the secondary time series (deg).");
    tt->help = tdrpStrDup("Only pulses between the start and end azimuths will be used. Assumes clockwise rotation - i.e. this is the couterclockwise limit.");
    tt->val_offset = (char *) &secondary_start_azimuth - &_start_;
    tt->single_val.d = 0;
    tt++;
    
    // Parameter 'secondary_end_azimuth'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("secondary_end_azimuth");
    tt->descr = tdrpStrDup("Ending azimuth for the secondary time series (deg).");
    tt->help = tdrpStrDup("Only pulses between the start and end azimuths will be used. Assumes clockwise rotation - i.e. this is the clockwise limit.");
    tt->val_offset = (char *) &secondary_end_azimuth - &_start_;
    tt->single_val.d = 0;
    tt++;
    
    // Parameter 'secondary_start_range'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("secondary_start_range");
    tt->descr = tdrpStrDup("Starting range for the secondary data (km).");
    tt->help = tdrpStrDup("Gates before this range will be discarded.");
    tt->val_offset = (char *) &secondary_start_range - &_start_;
    tt->single_val.d = 0;
    tt++;
    
    // Parameter 'secondary_end_range'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("secondary_end_range");
    tt->descr = tdrpStrDup("Ending range for the secondary data (km).");
    tt->help = tdrpStrDup("Gates after this range will be discarded.");
    tt->val_offset = (char *) &secondary_end_range - &_start_;
    tt->single_val.d = 150;
    tt++;
    
    // Parameter 'Comment 4'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 4");
    tt->comment_hdr = tdrpStrDup("TIME, SCAN RATE FOR OUTPUT DATA");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'output_start_time'
    // ctype is '_datetime_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRUCT_TYPE;
    tt->param_name = tdrpStrDup("output_start_time");
    tt->descr = tdrpStrDup("Start time for output data.");
    tt->help = tdrpStrDup("The pulse times will start at this time, and the time will then be incremented to simulate the reqested scan rate (see below).");
    tt->val_offset = (char *) &output_start_time - &_start_;
    tt->struct_def.name = tdrpStrDup("datetime_t");
    tt->struct_def.nfields = 6;
    tt->struct_def.fields = (struct_field_t *)
        tdrpMalloc(tt->struct_def.nfields * sizeof(struct_field_t));
      tt->struct_def.fields[0].ftype = tdrpStrDup("int");
      tt->struct_def.fields[0].fname = tdrpStrDup("year");
      tt->struct_def.fields[0].ptype = INT_TYPE;
      tt->struct_def.fields[0].rel_offset = 
        (char *) &output_start_time.year - (char *) &output_start_time;
      tt->struct_def.fields[1].ftype = tdrpStrDup("int");
      tt->struct_def.fields[1].fname = tdrpStrDup("month");
      tt->struct_def.fields[1].ptype = INT_TYPE;
      tt->struct_def.fields[1].rel_offset = 
        (char *) &output_start_time.month - (char *) &output_start_time;
      tt->struct_def.fields[2].ftype = tdrpStrDup("int");
      tt->struct_def.fields[2].fname = tdrpStrDup("day");
      tt->struct_def.fields[2].ptype = INT_TYPE;
      tt->struct_def.fields[2].rel_offset = 
        (char *) &output_start_time.day - (char *) &output_start_time;
      tt->struct_def.fields[3].ftype = tdrpStrDup("int");
      tt->struct_def.fields[3].fname = tdrpStrDup("hour");
      tt->struct_def.fields[3].ptype = INT_TYPE;
      tt->struct_def.fields[3].rel_offset = 
        (char *) &output_start_time.hour - (char *) &output_start_time;
      tt->struct_def.fields[4].ftype = tdrpStrDup("int");
      tt->struct_def.fields[4].fname = tdrpStrDup("min");
      tt->struct_def.fields[4].ptype = INT_TYPE;
      tt->struct_def.fields[4].rel_offset = 
        (char *) &output_start_time.min - (char *) &output_start_time;
      tt->struct_def.fields[5].ftype = tdrpStrDup("int");
      tt->struct_def.fields[5].fname = tdrpStrDup("sec");
      tt->struct_def.fields[5].ptype = INT_TYPE;
      tt->struct_def.fields[5].rel_offset = 
        (char *) &output_start_time.sec - (char *) &output_start_time;
    tt->n_struct_vals = 6;
    tt->struct_vals = (tdrpVal_t *)
        tdrpMalloc(tt->n_struct_vals * sizeof(tdrpVal_t));
      tt->struct_vals[0].i = 2014;
      tt->struct_vals[1].i = 5;
      tt->struct_vals[2].i = 20;
      tt->struct_vals[3].i = 20;
      tt->struct_vals[4].i = 0;
      tt->struct_vals[5].i = 0;
    tt++;
    
    // Parameter 'output_scan_rate'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("output_scan_rate");
    tt->descr = tdrpStrDup("Antenna rate for output data (deg/s)");
    tt->help = tdrpStrDup("The pulses will be time-tagged to yield this rate.");
    tt->val_offset = (char *) &output_scan_rate - &_start_;
    tt->single_val.d = 15;
    tt++;
    
    // Parameter 'output_azimuth_start'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("output_azimuth_start");
    tt->descr = tdrpStrDup("Starting azimuth for output pulses (deg)");
    tt->help = tdrpStrDup("The azimuth for each pulse will be computed from this starting point, the scan rate and the elapsed time.");
    tt->val_offset = (char *) &output_azimuth_start - &_start_;
    tt->single_val.d = 0;
    tt++;
    
    // Parameter 'output_azimuth_coverage'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("output_azimuth_coverage");
    tt->descr = tdrpStrDup("Coverage of output scan in azimuth (deg)");
    tt->help = tdrpStrDup("The output data will cover this angular width in azimuth.");
    tt->val_offset = (char *) &output_azimuth_coverage - &_start_;
    tt->single_val.d = 360;
    tt++;
    
    // Parameter 'output_elevation_angle'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("output_elevation_angle");
    tt->descr = tdrpStrDup("Elevation angle for tagging the output data (deg)");
    tt->help = tdrpStrDup("The measured elevation angles will be overwritten.");
    tt->val_offset = (char *) &output_elevation_angle - &_start_;
    tt->single_val.d = 1;
    tt++;
    
    // Parameter 'output_n_volumes'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("output_n_volumes");
    tt->descr = tdrpStrDup("Number of volumes to generate");
    tt->help = tdrpStrDup("The app keeps going until this number of volumes has been created.");
    tt->val_offset = (char *) &output_n_volumes - &_start_;
    tt->single_val.i = 10;
    tt++;
    
    // Parameter 'output_delta_volume_time'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("output_delta_volume_time");
    tt->descr = tdrpStrDup("Time between volumes (sec)");
    tt->help = tdrpStrDup("As each volume is written, the time is incremented by this value.");
    tt->val_offset = (char *) &output_delta_volume_time - &_start_;
    tt->single_val.d = 300;
    tt++;
    
    // Parameter 'Comment 5'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 5");
    tt->comment_hdr = tdrpStrDup("OUTPUT FILES");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'primary_output_dir'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("primary_output_dir");
    tt->descr = tdrpStrDup("Path to output directory for primary data.");
    tt->help = tdrpStrDup("Files will be written under this directory in a sub-directory computed from the date/time.");
    tt->val_offset = (char *) &primary_output_dir - &_start_;
    tt->single_val.s = tdrpStrDup("/tmp/time_series/primary");
    tt++;
    
    // Parameter 'secondary_output_dir'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("secondary_output_dir");
    tt->descr = tdrpStrDup("Path to output directory for secondary data.");
    tt->help = tdrpStrDup("Files will be written under this directory in a sub-directory computed from the date/time.");
    tt->val_offset = (char *) &secondary_output_dir - &_start_;
    tt->single_val.s = tdrpStrDup("/tmp/time_series/secondary");
    tt++;
    
    // Parameter 'combined_output_dir'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("combined_output_dir");
    tt->descr = tdrpStrDup("Path to output directory for combined data.");
    tt->help = tdrpStrDup("Files will be written under this directory in a sub-directory computed from the date/time.");
    tt->val_offset = (char *) &combined_output_dir - &_start_;
    tt->single_val.s = tdrpStrDup("/tmp/time_series/combined");
    tt++;
    
    // Parameter 'use_fixed_angle_for_file_name'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("use_fixed_angle_for_file_name");
    tt->descr = tdrpStrDup("Option to use the fixed angle (el or az) to compute the file name.");
    tt->help = tdrpStrDup("If false, the actual measured angle will be used.");
    tt->val_offset = (char *) &use_fixed_angle_for_file_name - &_start_;
    tt->single_val.b = pTRUE;
    tt++;
    
    // Parameter 'add_scan_mode_to_file_name'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("add_scan_mode_to_file_name");
    tt->descr = tdrpStrDup("Option to add a string indicating the scan mode to the file name.");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &add_scan_mode_to_file_name - &_start_;
    tt->single_val.b = pTRUE;
    tt++;
    
    // trailing entry has param_name set to NULL
    
    tt->param_name = NULL;
    
    return;
  
  }
