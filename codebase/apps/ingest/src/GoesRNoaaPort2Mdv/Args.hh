/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 ** Copyright (c) 2008 UCAR
 ** University Corporation for Atmospheric Research(UCAR)
 ** National Center for Atmospheric Research(NCAR)
 ** Research Applications Program(RAP)
 ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
 ** All rights reserved. Licenced use only.
 ** $Date: 2018/03/21 16:27:34 $
 *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

//////////////////////////////////////////////////////////////////////////
// 
// Header:	Args
// 
// Author:	D. Megenhardt
// 
// Date:	March 21, 2018
// 
// Description:	This class manages the argument list for GoesRNoaaPort2Mdv.
// 
// 
// 
// 


#ifndef    ARGS_H
#define    ARGS_H

#include <vector>
#include <cstdio>
#include <string>
#include <iostream>

#include <tdrp/tdrp.h>


class Args {

public:


  // Flag indicating whether the current object status is okay.
  bool isOK;

  // TDRP overrides specified in the command line arguments.
  tdrp_override_t override;

  // constructor
  Args(int argc, char **argv, const std::string &prog_name);

  // destructor
  ~Args();

  const std::vector<std::string> &getFileList() {
    return _inputFileList;
  }


protected:

private:


  std::string _errStr;
  static const std::string _className;
  std::vector<std::string> _inputFileList;

  // Disallow the copy constructor and assignment operator
  Args(const Args &);

  Args &operator=(const Args &);

  void _setOverride(const std::string &);

  void _setOverride(const std::string &, const char *);
  // Print the usage for this program.

  void _usage(const std::string &prog_name, std::ostream &out);

};


# endif     /* ARGS_H */
