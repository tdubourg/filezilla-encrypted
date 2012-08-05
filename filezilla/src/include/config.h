/* src/include/config.h.  Generated from config.h.in by configure.  */
/* src/include/config.h.in.  Generated from configure.in by autoheader.  */

/* Buildtype, indicates official builds and nightly builds */
/* #undef BUILDTYPE */

/* Define this to the include prefix of crypto++ */
#define CRYPTOPP_INCLUDE_PREFIX cryptopp

/* Define ENABLE_BINRELOC on systems where the executable location can be
   obtained using /proc/self/maps */
#define ENABLE_BINRELOC 1

/* Set to 1 to add support for automated update checks */
#define FZ_AUTOUPDATECHECK 1

/* Set to 1 to enable user initiated update checks */
#define FZ_MANUALUPDATECHECK 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the `ftime' function. */
#define HAVE_FTIME 1

/* Define to 1 if you have the `getaddrinfo' function. */
#define HAVE_GETADDRINFO 1

/* Define to 1 if you have the `gettimeofday' function. */
#define HAVE_GETTIMEOFDAY 1

/* Define to 1 if you have the `in6addr_any' function. */
#define HAVE_IN6ADDR_ANY 1

/* Define to 1 if you have the `in6addr_loopback' function. */
#define HAVE_IN6ADDR_LOOPBACK 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if your system has the `tinyxml' library (-ltinyxml). */
/* #undef HAVE_LIBTINYXML */

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `ptsname' function. */
#define HAVE_PTSNAME 1

/* Define to 1 if putenv function is available. */
#define HAVE_PUTENV 1

/* Define to 1 if setenv function is available. */
#define HAVE_SETENV 1

/* Define to 1 if you have the `setresuid' function. */
#define HAVE_SETRESUID 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strsignal' function. */
#define HAVE_STRSIGNAL 1

/* Define to 1 if you have the <sys/select.h> header file. */
#define HAVE_SYS_SELECT_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define HAVE_TR1_UNORDERED_MAP on systems where unordered_map is in tr1/
   subdirectory. */
/* #undef HAVE_TR1_UNORDERED_MAP */

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `updwtmpx' function. */
#define HAVE_UPDWTMPX 1

/* Define to 1 if you have the <utmpx.h> header file. */
#define HAVE_UTMPX_H 1

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Define to 1 if your C compiler doesn't accept -c and -o together. */
/* #undef NO_MINUS_C_MINUS_O */

/* Name of package */
#define PACKAGE "filezilla"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "tim.kosse@filezilla-project.org"

/* Define to the full name of this package. */
#define PACKAGE_NAME "FileZilla"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "FileZilla 3.5.3"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "filezilla"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "3.5.3"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Build system under which the program was compiled on. */
#define USED_BUILD "i686-pc-linux-gnu"

/* Define to name and version of used compiler */
#define USED_COMPILER "gcc (Ubuntu/Linaro 4.6.1-9ubuntu3) 4.6.1"

/* Define to the used CXXFLAGS to compile this package. */
#define USED_CXXFLAGS "-g -O2 -Wall -g -fexceptions -std=gnu++0x"

/* Host system under which the program will run. */
#define USED_HOST "i686-pc-linux-gnu"

/* Version number of package */
#define VERSION "3.5.3"

/* Set to 2 to if libdbus >= 1.2 is available, set to 1 if an older version is
   available. */
#define WITH_LIBDBUS 2
