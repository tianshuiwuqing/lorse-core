/*******************************************
 * wsi_ingest_tdrp.h
 *
 * TDRP header file for 'wsi_ingest' module.
 *
 * Code for program wsi_ingest
 *
 * This header file has been automatically
 * generated by TDRP, do not modify.
 *
 *******************************************/

#ifndef _wsi_ingest_tdrp_h
#define _wsi_ingest_tdrp_h

#ifdef __cplusplus
extern "C" {
#endif

#include <tdrp/tdrp.h>

/*
 * typedefs
 */

typedef enum {
  DEBUG_OFF = 0,
  DEBUG_WARNINGS = 1,
  DEBUG_NORM = 2,
  DEBUG_EXTRA = 3
} wsi_ingest_debug_t;

typedef struct {
  char* product_type;
  char* product_coverage;
  char* output_dir;
  char* output_ext;
} wsi_ingest_output_data_t;

/*
 * typedef for main struct - wsi_ingest_tdrp_struct
 */

typedef struct {

  size_t struct_size;

  /***** debug_level *****/

  wsi_ingest_debug_t debug_level;

  /***** malloc_debug_level *****/

  long malloc_debug_level;

  /***** instance *****/

  char* instance;

  /***** wsi_ip_address *****/

  char* wsi_ip_address;

  /***** wsi_port *****/

  long wsi_port;

  /***** output_data *****/

  struct {
    wsi_ingest_output_data_t *val;
    int len;
  } output_data;
  wsi_ingest_output_data_t *_output_data;
  int output_data_n;

} wsi_ingest_tdrp_struct;

/*
 * function prototypes
 */

/*************************************************************
 * wsi_ingest_tdrp_load_from_args()
 *
 * Loads up TDRP using the command line args.
 *
 * Check TDRP_usage() for command line actions associated with
 * this function.
 *
 *   argc, argv: command line args
 *
 *   wsi_ingest_tdrp_struct *params: loads up this struct
 * 
 *   char **override_list: A null-terminated list of overrides
 *     to the parameter file.
 *     An override string has exactly the format of an entry
 *     in the parameter file itself.
 *
 *   char **params_path_p: if non-NULL, this is set to point to
 *                         the path of the params file used.
 *
 *  Returns 0 on success, -1 on failure.
 */

extern int wsi_ingest_tdrp_load_from_args(int argc, char **argv,
                                wsi_ingest_tdrp_struct *params,
                                char **override_list,
                                char **params_path_p);

/*************************************************************
 * wsi_ingest_tdrp_load()
 *
 * Loads up TDRP for a given module.
 *
 * This version of load gives the programmer the option to load
 * up more than one module for a single application. It is a
 * lower-level routine than wsi_ingest_tdrp_load_from_args,
 * and hence more flexible, but the programmer must do more work.
 *
 *   char *param_file_path: the parameter file to be read in.
 *
 *   wsi_ingest_tdrp_struct *params: loads up this struct
 *
 *   char **override_list: A null-terminated list of overrides
 *     to the parameter file.
 *     An override string has exactly the format of an entry
 *     in the parameter file itself.
 *
 *  expand_env: flag to control environment variable
 *                expansion during tokenization.
 *              If TRUE, environment expansion is set on.
 *              If FALSE, environment expansion is set off.
 *
 *  Returns 0 on success, -1 on failure.
 */

extern int wsi_ingest_tdrp_load(char *param_file_path,
                      wsi_ingest_tdrp_struct *params,
                      char **override_list,
                      int expand_env, int debug);

/*************************************************************
 * wsi_ingest_tdrp_load_defaults()
 *
 * Loads up defaults for a given module.
 *
 * See wsi_ingest_tdrp_load() for more details.
 *
 *  Returns 0 on success, -1 on failure.
 */

extern int wsi_ingest_tdrp_load_defaults(wsi_ingest_tdrp_struct *params,
                               int expand_env);

/*************************************************************
 * wsi_ingest_tdrp_sync()
 *
 * Syncs the user struct data back into the parameter table,
 * in preparation for printing.
 */

extern void wsi_ingest_tdrp_sync(void);

/*************************************************************
 * wsi_ingest_tdrp_print()
 * 
 * Print params file
 *
 * The modes supported are:
 *
 *   PRINT_SHORT:   main comments only, no help or descriptions
 *                  structs and arrays on a single line
 *   PRINT_NORM:    short + descriptions and help
 *   PRINT_LONG:    norm  + arrays and structs expanded
 *   PRINT_VERBOSE: long  + private params included
 */

extern void wsi_ingest_tdrp_print(FILE *out, tdrp_print_mode_t mode);

/*************************************************************
 * wsi_ingest_tdrp_free_all()
 *
 * Frees up all TDRP dynamic memory.
 */

extern void wsi_ingest_tdrp_free_all(void);

/*************************************************************
 * wsi_ingest_tdrp_check_all_set()
 *
 * Return TRUE if all set, FALSE if not.
 *
 * If out is non-NULL, prints out warning messages for those
 * parameters which are not set.
 */

extern int wsi_ingest_tdrp_check_all_set(FILE *out);

/*************************************************************
 * wsi_ingest_tdrp_check_is_set()
 *
 * Return TRUE if parameter is set, FALSE if not.
 *
 */

extern int wsi_ingest_tdrp_check_is_set(char *param_name);

/*************************************************************
 * wsi_ingest_tdrp_array_realloc()
 *
 * Realloc 1D array.
 *
 * If size is increased, the values from the last array entry is
 * copied into the new space.
 *
 * Returns 0 on success, -1 on error.
 */

extern int wsi_ingest_tdrp_array_realloc(char *param_name,
                              int new_array_n);

/*************************************************************
 * wsi_ingest_tdrp_array2D_realloc()
 *
 * Realloc 2D array.
 *
 * If size is increased, the values from the last array entry is
 * copied into the new space.
 *
 * Returns 0 on success, -1 on error.
 */

extern int wsi_ingest_tdrp_array2D_realloc(char *param_name,
                                 int new_array_n1,
                                 int new_array_n2);

/*************************************************************
 * wsi_ingest_tdrp_table()
 *
 * Returns pointer to static Table for this module.
 */

extern TDRPtable *wsi_ingest_tdrp_table(void);

/*************************************************************
 * wsi_ingest_tdrp_init()
 *
 * Module table initialization function.
 *
 *
 * Returns pointer to static Table for this module.
 */

extern TDRPtable *wsi_ingest_tdrp_init(wsi_ingest_tdrp_struct *params);

#ifdef __cplusplus
}
#endif

#endif

