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
 * Copyright (c) 2011-2012, Centre National d'Etudes Spatiales (CNES), France
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

/*
 * This is equivalent to the UNIX `cmp` command
 */

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "grok_getopt.h"
}
#include <string>

typedef struct test_cmp_parameters {
    /**  */
    char* base_filename;
    /**  */
    char* test_filename;
} test_cmp_parameters;

/*******************************************************************************
 * Command line help function
 *******************************************************************************/
static void compare_raw_files_help_display(void)
{
    fprintf(stdout,"\nList of parameters for the compare_raw_files function  \n");
    fprintf(stdout,"\n");
    fprintf(stdout,"  -b \t REQUIRED \t filename to the reference/baseline RAW image \n");
    fprintf(stdout,"  -t \t REQUIRED \t filename to the test RAW image\n");
    fprintf(stdout,"\n");
}

/*******************************************************************************
 * Parse command line
 *******************************************************************************/
static int parse_cmdline_cmp(int argc, char **argv, test_cmp_parameters* param)
{
    size_t sizemembasefile, sizememtestfile;
    int index;
    const char optlist[] = "b:t:";
    int c;

    /* Init parameters*/
    param->base_filename = nullptr;
    param->test_filename = nullptr;

    grok_opterr = 0;
    while ((c = grok_getopt(argc, argv, optlist)) != -1)
        switch (c) {
        case 'b':
            sizemembasefile = strlen(grok_optarg)+1;
            free(param->base_filename); /* handle dup option */
            param->base_filename = (char*) malloc(sizemembasefile);
			if (!param->base_filename) {
				fprintf(stderr, "Out of memory\n");
				return 1;
			}
            strcpy(param->base_filename, grok_optarg);
            /*printf("param->base_filename = %s [%d / %d]\n", param->base_filename, strlen(param->base_filename), sizemembasefile );*/
            break;
        case 't':
            sizememtestfile = strlen(grok_optarg) + 1;
            free(param->test_filename); /* handle dup option */
            param->test_filename = (char*) malloc(sizememtestfile);
			if (!param->test_filename) {
				fprintf(stderr, "Out of memory\n");
				return 1;
			}
            strcpy(param->test_filename, grok_optarg);
            /*printf("param->test_filename = %s [%d / %d]\n", param->test_filename, strlen(param->test_filename), sizememtestfile);*/
            break;
        case '?':
            if ((grok_optopt == 'b') || (grok_optopt == 't'))
                fprintf(stderr, "Option -%c requires an argument.\n", grok_optopt);
            else if (isprint(grok_optopt))	fprintf(stderr, "Unknown option `-%c'.\n", grok_optopt);
            else	fprintf(stderr, "Unknown option character `\\x%x'.\n", grok_optopt);
            return 1;
        default:
            fprintf(stderr, "WARNING -> this option is not valid \"-%c %s\"\n", c, grok_optarg);
            break;
        }

    if (grok_optind != argc) {
        for (index = grok_optind; index < argc; index++)
            fprintf(stderr,"Non-option argument %s\n", argv[index]);
        return 1;
    }

    return 0;
}

/*******************************************************************************
 * MAIN
 *******************************************************************************/
int main(int argc, char **argv)
{
#ifndef NDEBUG
	std::string out;
	for (int i = 0; i < argc; ++i) {
		out += std::string(" ") + argv[i];
	}
	out += "\n";
	printf(out.c_str());
#endif

    int pos = 0;
    test_cmp_parameters inParam;
    FILE *file_test=nullptr, *file_base=nullptr;
    unsigned char equal = 0U; /* returns error by default */

    /* Get parameters from command line*/
    if (parse_cmdline_cmp(argc, argv, &inParam)) {
        compare_raw_files_help_display();
        goto cleanup;
    }

    file_test = fopen(inParam.test_filename, "rb");
    if (!file_test) {
        fprintf(stderr, "Failed to open %s for reading !!\n", inParam.test_filename);
        goto cleanup;
    }

    file_base = fopen(inParam.base_filename, "rb");
    if (!file_base) {
        fprintf(stderr, "Failed to open %s for reading !!\n", inParam.base_filename);
        goto cleanup;
    }

    /* Read simultaneously the two files*/
    equal = 1U;
    while (equal) {
        unsigned char value_test = 0;
        unsigned char eof_test = 0;
        unsigned char value_base = 0;
        unsigned char eof_base = 0;

        /* Read one byte*/
        if (!fread(&value_test, 1, 1, file_test)) {
            eof_test = 1;
        }

        /* Read one byte*/
        if (!fread(&value_base, 1, 1, file_base)) {
            eof_base = 1;
        }

        /* End of file reached by the two files?*/
        if (eof_test && eof_base)
            break;

        /* End of file reached only by one file?*/
        if (eof_test || eof_base) {
            fprintf(stdout,"Files have different sizes.\n");
            equal = 0;
        }

        /* Binary values are equal?*/
        if (value_test != value_base) {
            fprintf(stdout,"Binary values read in the file are different %x vs %x at position %d.\n", value_test, value_base, pos);
            equal = 0;
        }
        pos++;
    }

    if(equal) fprintf(stdout,"---- TEST SUCCEED: Files are equal ----\n");
cleanup:
    if(file_test) fclose(file_test);
    if(file_base) fclose(file_base);

    /* Free Memory */
    free(inParam.base_filename);
    free(inParam.test_filename);

    return equal ? EXIT_SUCCESS : EXIT_FAILURE;
}
