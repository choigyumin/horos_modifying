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

namespace grk {

/**
@file event.h
@brief Implementation of a event callback system

The functions in EVENT.C have for goal to send output messages (errors, warnings, debug) to the user.
*/
/**
Message handler object
used for
<ul>
<li>Error messages
<li>Warning messages
<li>Debugging messages
</ul>
*/
struct event_mgr_t {
    /** Data to call the event manager upon */
    void *			m_error_data;
    /** Data to call the event manager upon */
    void *			m_warning_data;
    /** Data to call the event manager upon */
    void *			m_info_data;
    /** Error message callback if available, nullptr otherwise */
    opj_msg_callback error_handler;
    /** Warning message callback if available, nullptr otherwise */
    opj_msg_callback warning_handler;
    /** Debug message callback if available, nullptr otherwise */
    opj_msg_callback info_handler;
};


#define EVT_ERROR	1	/**< Error event type */
#define EVT_WARNING	2	/**< Warning event type */
#define EVT_INFO	4	/**< Debug event type */

/** @defgroup EVENT EVENT - Implementation of a event callback system */
/*@{*/

/** @name Exported functions (see also openjpeg.h) */
/*@{*/
/* ----------------------------------------------------------------------- */


/* ----------------------------------------------------------------------- */

/**
 * Write formatted data to a string and send the string to a user callback.
 *
 * @param event_mgr			Event handler
 * @param event_type 		Event type or callback to use to send the message
 * @param fmt 				Format-control string (plus optional arguments)
 *
 * @return true if successful, returns false otherwise
 */
bool event_msg(event_mgr_t* event_mgr, int32_t event_type, const char *fmt, ...);
/* ----------------------------------------------------------------------- */

/**
 * Set the event manager with the default callback function for the 3 levels.
 */
void set_default_event_handler(event_mgr_t * p_manager);

/*@}*/

/*@}*/


}