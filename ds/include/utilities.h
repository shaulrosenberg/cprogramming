#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include "uid.h"

/*  write a function with the following signature to compare "ds_data" with
    internal data in the function
    "param" is extra data
    return 1 if match is found, 0 otherwise                                   */
typedef int (*is_match_func_ty)(const void *ds_data, void *param);

/*  write a function with the following signature to perform whichever action
    you need on "ds_data"
    "param" is extra data                                              
    return 0 if succeeded, otherwise - not 0                                  */
typedef int (*action_func_ty)(void *ds_data, void *param);

/*  write a function with the following signature to perform the comparison of 
    the sorting criteria 
    "data1" and "data2" are the compared elements
    returns:    > 0 if data1 > data2
                < 0 if data1 < data2
                = 0 if data1 == data2                                         */
typedef int (*cmp_func_ty)(void *data1, void *data2);

/*  write a function with this signature to state an operation to be executed 
    the function should return 0 if it should be repeated, 1 if it should
    be stopped                                                                */
typedef int (*oper_func_ty)(void *params);

/*  write a function with this signature to free resources used by operation,
    if needed                                                                 */
typedef void (*clean_func_ty)(ilrd_uid_ty uid, void *params);

#endif  /*  __UTILITIES_H__  */
