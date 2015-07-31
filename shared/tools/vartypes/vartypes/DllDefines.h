#ifndef VDATATYPE_DLLDEFINES_H_
#define VDATATYPE_DLLDEFINES_H_

#ifdef _WIN32
#  ifdef vartypes_EXPORTS
#    define VARTYPES_EXPORT __declspec(dllexport)
#  else
#    define VARTYPES_EXPORT __declspec(dllimport)
#  endif
#else
#  define VARTYPES_EXPORT
#endif

#endif

