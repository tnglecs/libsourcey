//
// LibSourcey
// Copyright (C) 2005, Sourcey <http://sourcey.com>
//
// LibSourcey is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// LibSourcey is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//


#ifndef SOURCEY_Types_H
#define SOURCEY_Types_H


#include "Sourcey/Base.h"
#include "Sourcey/Mutex.h"
//#include "Poco/Foundation.h"
#include "Poco/Exception.h"

#include <vector>
#include <map>


//
/// Cross platform normalization
//
#ifdef WIN32
#define strncasecmp strnicmp
#define strcasecmp stricmp
#endif 


namespace scy {


	
//
// Reduce namespace pollution by forwarding some 
// extensively used basic Poco types to our namespace.
//
using Poco::Exception;

/*
//using Poco::Mutex;
using Poco::Int8;
using Poco::UInt8;
using Poco::Int16;
using Poco::UInt16;
using Poco::Int32;
using Poco::UInt32;
using Poco::Int32;
using Poco::UInt32;
using Poco::Int64;
using Poco::UInt64;
*/


typedef std::vector<std::string>			StringVec;
typedef std::map<std::string, std::string>	StringMap;


//
// Error type
//

struct Error 
	/// Simple error type 
{
	std::string message;
		/// Error message (set by application)

	int syserr;
		/// System error code

	int uverr;
		/// Libuv error code

	Error()
	{
		reset();
	}

	Error(const std::string& msg)
	{
		reset();
		message = msg;
	}

	bool any() 
	{
		return uverr != 0 || syserr != 0 || !message.empty();
	}

	void reset() 
	{
		uverr = 0;
		syserr = 0;
		message.clear();
	}
};


//
// Integer types
//

#if defined(_MSC_VER)
	//
	// Windows/Visual C++
	//
	typedef signed char            Int8;
	typedef unsigned char          UInt8;
	typedef signed short           Int16;
	typedef unsigned short         UInt16;
	typedef signed int             Int32;
	typedef unsigned int           UInt32;
	typedef signed __int64         Int64;
	typedef unsigned __int64       UInt64;
	#if defined(_WIN64)
		#define POCO_PTR_IS_64_BIT 1
		typedef signed __int64     IntPtr;
		typedef unsigned __int64   UIntPtr;
	#else
		typedef signed long        IntPtr;
		typedef unsigned long      UIntPtr;
	#endif
	#define POCO_HAVE_INT64 1
#elif defined(__GNUC__) || defined(__clang__)
	//
	// Unix/GCC
	//
	typedef signed char            Int8;
	typedef unsigned char          UInt8;
	typedef signed short           Int16;
	typedef unsigned short         UInt16;
	typedef signed int             Int32;
	typedef unsigned int           UInt32;
	typedef signed long            IntPtr;
	typedef unsigned long          UIntPtr;
	#if defined(__LP64__)
		#define POCO_PTR_IS_64_BIT 1
		#define POCO_LONG_IS_64_BIT 1
		typedef signed long        Int64;
		typedef unsigned long      UInt64;
	#else
		typedef signed long long   Int64;
		typedef unsigned long long UInt64;
	#endif
	#define POCO_HAVE_INT64 1
#elif defined(__DECCXX)
	//
	// Compaq C++
	//
	typedef signed char            Int8;
	typedef unsigned char          UInt8;
	typedef signed short           Int16;
	typedef unsigned short         UInt16;
	typedef signed int             Int32;
	typedef unsigned int           UInt32;
	typedef signed __int64         Int64;
	typedef unsigned __int64       UInt64;
	#if defined(__VMS)
		#if defined(__32BITS)
			typedef signed long    IntPtr;
			typedef unsigned long  UIntPtr;
		#else
			typedef Int64          IntPtr;
			typedef UInt64         UIntPtr;
			#define POCO_PTR_IS_64_BIT 1
		#endif
	#else
		typedef signed long        IntPtr;
		typedef unsigned long      UIntPtr;
		#define POCO_PTR_IS_64_BIT 1
		#define POCO_LONG_IS_64_BIT 1
	#endif
	#define POCO_HAVE_INT64 1
#elif defined(__HP_aCC)
	//
	// HP Ansi C++
	//
	typedef signed char            Int8;
	typedef unsigned char          UInt8;
	typedef signed short           Int16;
	typedef unsigned short         UInt16;
	typedef signed int             Int32;
	typedef unsigned int           UInt32;
	typedef signed long            IntPtr;
	typedef unsigned long          UIntPtr;
	#if defined(__LP64__)
		#define POCO_PTR_IS_64_BIT 1
		#define POCO_LONG_IS_64_BIT 1
		typedef signed long        Int64;
		typedef unsigned long      UInt64;
	#else
		typedef signed long long   Int64;
		typedef unsigned long long UInt64;
	#endif
	#define POCO_HAVE_INT64 1
#elif defined(__SUNPRO_CC)
	//
	// SUN Forte C++
	//
	typedef signed char            Int8;
	typedef unsigned char          UInt8;
	typedef signed short           Int16;
	typedef unsigned short         UInt16;
	typedef signed int             Int32;
	typedef unsigned int           UInt32;
	typedef signed long            IntPtr;
	typedef unsigned long          UIntPtr;
	#if defined(__sparcv9)
		#define POCO_PTR_IS_64_BIT 1
		#define POCO_LONG_IS_64_BIT 1
		typedef signed long        Int64;
		typedef unsigned long      UInt64;
	#else
		typedef signed long long   Int64;
		typedef unsigned long long UInt64;
	#endif
	#define POCO_HAVE_INT64 1
#elif defined(__IBMCPP__) 
	//
	// IBM XL C++
	//
	typedef signed char            Int8;
	typedef unsigned char          UInt8;
	typedef signed short           Int16;
	typedef unsigned short         UInt16;
	typedef signed int             Int32;
	typedef unsigned int           UInt32;
	typedef signed long            IntPtr;
	typedef unsigned long          UIntPtr;
	#if defined(__64BIT__)
		#define POCO_PTR_IS_64_BIT 1
		#define POCO_LONG_IS_64_BIT 1
		typedef signed long        Int64;
		typedef unsigned long      UInt64;
	#else
		typedef signed long long   Int64;
		typedef unsigned long long UInt64;
	#endif
	#define POCO_HAVE_INT64 1
#elif defined(__sgi) 
	//
	// MIPSpro C++
	//
	typedef signed char            Int8;
	typedef unsigned char          UInt8;
	typedef signed short           Int16;
	typedef unsigned short         UInt16;
	typedef signed int             Int32;
	typedef unsigned int           UInt32;
	typedef signed long            IntPtr;
	typedef unsigned long          UIntPtr;
	#if _MIPS_SZLONG == 64
		#define POCO_PTR_IS_64_BIT 1
		#define POCO_LONG_IS_64_BIT 1
		typedef signed long        Int64;
		typedef unsigned long      UInt64;
	#else
		typedef signed long long   Int64;
		typedef unsigned long long UInt64;
	#endif
	#define POCO_HAVE_INT64 1
#elif defined(_DIAB_TOOL)
	typedef signed char        Int8;
	typedef unsigned char      UInt8;
	typedef signed short       Int16;
	typedef unsigned short     UInt16;
	typedef signed int         Int32;
	typedef unsigned int       UInt32;
	typedef signed long        IntPtr;
	typedef unsigned long      UIntPtr;
	typedef signed long long   Int64;
	typedef unsigned long long UInt64;
	#define POCO_HAVE_INT64 1
#endif


} // namespace scy


#endif // SOURCEY_Types_H


// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//