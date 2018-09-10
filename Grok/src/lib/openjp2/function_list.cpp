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
 * Copyright (c) 2008, Jerome Fimes, Communications & Systemes <jerome.fimes@c-s.fr>
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
#include "grok_includes.h"

namespace grk {


/**
 * Default size of the validation list, if not sufficient, data will be reallocated with a double size.
 */
	
const int validation_size = 10;

procedure_list_t *  procedure_list_create()
{
    /* memory allocation */
    procedure_list_t * l_validation = (procedure_list_t *) grok_calloc(1,sizeof(procedure_list_t));
    if (! l_validation) {
        return nullptr;
    }
    /* initialization */
    l_validation->m_nb_max_procedures = validation_size;
    l_validation->m_procedures = (procedure*)grok_calloc(validation_size, sizeof(procedure));
    if (! l_validation->m_procedures) {
        grok_free(l_validation);
        return nullptr;
    }
    return l_validation;
}

void  procedure_list_destroy(procedure_list_t * p_list)
{
    if (! p_list) {
        return;
    }
    /* initialization */
    if (p_list->m_procedures) {
        grok_free(p_list->m_procedures);
    }
    grok_free(p_list);
}

bool procedure_list_add_procedure (procedure_list_t * p_validation_list, procedure p_procedure, event_mgr_t* p_manager )
{

    assert(p_manager != nullptr);

    if (p_validation_list->m_nb_max_procedures == p_validation_list->m_nb_procedures) {
        procedure * new_procedures;

        p_validation_list->m_nb_max_procedures += validation_size;
        new_procedures = (procedure*)grok_realloc(
                             p_validation_list->m_procedures,
                             p_validation_list->m_nb_max_procedures * sizeof(procedure));
        if (! new_procedures) {
            grok_free(p_validation_list->m_procedures);
            p_validation_list->m_nb_max_procedures = 0;
            p_validation_list->m_nb_procedures = 0;
            event_msg(p_manager, EVT_ERROR, "Not enough memory to add a new validation procedure\n");
            return false;
        } else {
            p_validation_list->m_procedures = new_procedures;
        }
    }
    p_validation_list->m_procedures[p_validation_list->m_nb_procedures] = p_procedure;
    ++p_validation_list->m_nb_procedures;

    return true;
}

uint32_t procedure_list_get_nb_procedures (procedure_list_t * p_validation_list)
{
    return p_validation_list->m_nb_procedures;
}

procedure* procedure_list_get_first_procedure (procedure_list_t * p_validation_list)
{
    return p_validation_list->m_procedures;
}

void procedure_list_clear (procedure_list_t * p_validation_list)
{
    p_validation_list->m_nb_procedures = 0;
}
}