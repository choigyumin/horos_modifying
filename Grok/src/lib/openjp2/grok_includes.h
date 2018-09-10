/*
*    Copyright (C) 2016-2018 Grok Image Compression Inc.
*
*    This source code is free software: you can redistribute it and/or  modify
*    it under the terms of the GNU Affero General Public License, version 3,
*    as published by the Free Software Foundation.
*
*    This source code is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU Affero General Public License for more details.
*
*    You should have received a copy of the GNU Affero General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*
*    This source code incorporates work covered by the following copyright and
*    permission notice:
*
 * The copyright in this software is being made available under the 2-clauses
 * BSD License, included below. This software may be subject to other third
 * party and contributor rights, including patent rights, and no such rights
 * are granted under this license.
 *
 * Copyright (c) 2005, Herve Drolon, FreeImage Team
 * Copyright (c) 2008, 2011-2012, Centre National d'Etudes Spatiales (CNES), FR
 * Copyright (c) 2012, CS Systemes d'Information, France
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS `AS IS'
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#pragma once


/*
 * This must be included before any system headers,
 * since they can react to macro defined there
 */
#include "opj_config_private.h"

/*
 ==========================================================
   Standard includes used by the library
 ==========================================================
*/
#include "overflow_utils.h"
#include <memory.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <float.h>
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <assert.h>
#include <inttypes.h>
#include <climits>
#include <algorithm>
#include <sstream>
#include <iostream>


/* Avoid compile-time warning because parameter is not used */
#define ARG_NOT_USED(x) (void)(x)

/*
  Use fseeko() and ftello() if they are available since they use
  'off_t' rather than 'long'.  It is wrong to use fseeko() and
  ftello() only on systems with special LFS support since some systems
  (e.g. FreeBSD) support a 64-bit off_t by default.
*/
#if defined(GROK_HAVE_FSEEKO) && !defined(fseek)
#  define fseek  fseeko
#  define ftell  ftello
#endif


#if defined(_WIN32)
#  define GROK_FSEEK(stream,offset,whence) _fseeki64(stream,/* __int64 */ offset,whence)
#  define GROK_FSTAT(fildes,stat_buff) _fstati64(fildes,/* struct _stati64 */ stat_buff)
#  define GROK_FTELL(stream) /* __int64 */ _ftelli64(stream)
#  define GROK_STAT_STRUCT_T struct _stati64
#  define GROK_STAT(path,stat_buff) _stati64(path,/* struct _stati64 */ stat_buff)
#else
#  define GROK_FSEEK(stream,offset,whence) fseek(stream,offset,whence)
#  define GROK_FSTAT(fildes,stat_buff) fstat(fildes,stat_buff)
#  define GROK_FTELL(stream) ftell(stream)
#  define GROK_STAT_STRUCT_T struct stat
#  define GROK_STAT(path,stat_buff) stat(path,stat_buff)
#endif


/*
 ==========================================================
   Grok interface
 ==========================================================
 */

#include "minpf_plugin_manager.h"
#include "plugin_interface.h"
#include "grok.h"

/*
 ==========================================================
   Grok modules
 ==========================================================
*/

/* Are restricted pointers available? (C99) */
#if (__STDC_VERSION__ != 199901L)
/* Not a C99 compiler */
#ifdef __GNUC__
#define restrict __restrict__
#else
#define restrict /* restrict */
#endif
#endif

#ifdef __has_attribute
#if __has_attribute(no_sanitize)
#define GROK_NOSANITIZE(kind) __attribute__((no_sanitize(kind)))
#endif
#endif
#ifndef GROK_NOSANITIZE
#define GROK_NOSANITIZE(kind)
#endif


/* MSVC before 2013 and Borland C do not have lrintf */
#if defined(_MSC_VER)
#include <intrin.h>
static inline long grok_lrintf(float f)
{
#ifdef _M_X64
    return _mm_cvt_ss2si(_mm_load_ss(&f));

    /* commented out line breaks many tests */
    /* return (long)((f>0.0f) ? (f + 0.5f):(f -0.5f)); */
#elif defined(_M_IX86)
    int i;
    _asm{
        fld f
        fistp i
    };

    return i;
#else
    return (long)((f>0.0f) ? (f + 0.5f) : (f - 0.5f));
#endif
}
#else
static inline long grok_lrintf(float f)
{
    return lrintf(f);
}
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1400)
#define vsnprintf _vsnprintf
#endif

/* MSVC x86 is really bad at doing int64 = int32 * int32 on its own. Use intrinsic. */
#if defined(_MSC_VER) && (_MSC_VER >= 1400) && !defined(__INTEL_COMPILER) && defined(_M_IX86)
#	include <intrin.h>
#	pragma intrinsic(__emul)
#endif

#include "mem_stream.h"
#include "grok_clock.h"
#include "grok_malloc.h"
#include "event.h"
#include "function_list.h"
#include "vector.h"
#include "util.h"
#include "grok_exceptions.h"
#include "segmented_stream.h"
#include "BitIO.h"
#include "GrokStream.h"
#include "EncodedTileData.h"

#include "image.h"
#include "invert.h"
#include "j2k.h"
#include "jp2.h"
#include "BitIO.h"
#include "tile_buf.h"
#include "pi.h"
#include "tgt.h"
#include "tcd.h"
#include "dwt_interface.h"
#include "dwt.h"
#include "dwt53.h"
#include "dwt97.h"
#include "t2.h"
#include "mct.h"
#include "grok_intmath.h"
#include "plugin_bridge.h"
#include "grok_codec.h"
#include "RateControl.h"
#include "RateInfo.h"
