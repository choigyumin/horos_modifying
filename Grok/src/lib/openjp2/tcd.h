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
 * Copyright (c) 2002-2014, Universite catholique de Louvain (UCL), Belgium
 * Copyright (c) 2002-2014, Professor Benoit Macq
 * Copyright (c) 2001-2003, David Janssens
 * Copyright (c) 2002-2003, Yannick Verschueren
 * Copyright (c) 2003-2007, Francois-Olivier Devaux
 * Copyright (c) 2003-2014, Antonin Descampe
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
#include "testing.h"
#include <vector>

namespace grk {

// code segment (code block can be encoded into multiple segments)
struct tcd_seg_t {
	tcd_seg_t() : dataindex(0), 
					numpasses(0),
					len(0), 
					maxpasses(0),
					numPassesInPacket(0),
					newlen(0) {}
    uint32_t dataindex;				// segment data offset in contiguous memory block 
    uint32_t numpasses;				// number of passes in segment
    uint32_t len;
    uint32_t maxpasses;				// maximum number of passes in segment
    uint32_t numPassesInPacket;	// number of passes in segment from current packet
    uint32_t newlen;
};

struct packet_length_info_t {
	packet_length_info_t(uint32_t mylength, uint32_t bits) : len(mylength), len_bits(bits) {}
	packet_length_info_t() : len(0), len_bits(0) {}
	bool operator==(packet_length_info_t& rhs)const {
		return (rhs.len == len && rhs.len_bits == len_bits);
	}
	uint32_t len;
	uint32_t len_bits;
};

// encoding/decoding pass
struct tcd_pass_t {
	tcd_pass_t() : rate(0), 
						distortiondec(0),
						len(0),
						term(0),
						slope(0) {}
    uint16_t rate;
    double distortiondec;
    uint16_t len;
    uint8_t term;
	uint16_t slope;  //ln(slope) in 8.8 fixed point
};

//quality layer
struct tcd_layer_t {
	tcd_layer_t() : numpasses(0),
						len(0),
						disto(0),
						data(nullptr) {}
    uint32_t numpasses;		/* Number of passes in the layer */
    uint32_t len;			/* len of information */
    double disto;			/* add for index (Cfr. Marcela) */
    uint8_t *data;			/* data buffer (points to code block data) */
} ;

const uint8_t cblk_compressed_data_pad_left = 1;

// encoder code block
struct tcd_cblk_enc_t {
	tcd_cblk_enc_t() : 	actualData(nullptr),
							data(nullptr),
							data_size(0),
							owns_data(false),
							layers(nullptr),
							passes(nullptr),
							x0(0),
							y0(0),
							x1(0),
							y1(0),
							numbps(0),
							numlenbits(0),
							num_passes_included_in_current_layer(0),
							num_passes_included_in_previous_layers(0),
							num_passes_encoded(0),
#ifdef DEBUG_LOSSLESS_T2
							included(0),
							packet_length_info(nullptr),
#endif
							contextStream(nullptr) 
	{}
	~tcd_cblk_enc_t();
	bool alloc();
	bool alloc_data(size_t nominalBlockSize);
	void cleanup();
	uint8_t* actualData;
    uint8_t* data;              /* data buffer*/
	uint32_t data_size;         /* size of allocated data buffer */
	bool owns_data;				// true if code block manages data buffer, otherwise false
    tcd_layer_t* layers;     
    tcd_pass_t* passes;      
    uint32_t x0, y0, x1, y1;     /* dimension of the code block : left upper corner (x0, y0) right low corner (x1,y1) */
    uint32_t numbps;
    uint32_t numlenbits;
    uint32_t num_passes_included_in_current_layer;  /* number of passes encoded in current layer */
    uint32_t num_passes_included_in_previous_layers;	/* number of passes in previous layers */
    uint32_t num_passes_encoded;					/* number of passes encoded */
    uint32_t* contextStream;
#ifdef DEBUG_LOSSLESS_T2
	uint32_t included;
	std::vector<packet_length_info_t>* packet_length_info;
#endif
} ;

//decoder code block
struct tcd_cblk_dec_t {
	tcd_cblk_dec_t() : data(nullptr),
							dataSize(0),
							segs(nullptr),
							x0(0),
							y0(0),
							x1(0),
							y1(0),
							numbps(0),
							numlenbits(0),
							numPassesInPacket(0),
							numSegments(0),
#ifdef DEBUG_LOSSLESS_T2
							included(0),
#endif
							numSegmentsAllocated(0)
	{}

	tcd_cblk_dec_t(const tcd_cblk_enc_t& rhs) : data(nullptr),
														dataSize(0),
														segs(nullptr),
														x0(rhs.x0),
														y0(rhs.y0),
														x1(rhs.x1),
														y1(rhs.y1),
														numbps(rhs.numbps),
														numlenbits(rhs.numlenbits),
														numPassesInPacket(0),
														numSegments(0),
#ifdef DEBUG_LOSSLESS_T2
														 included(false),
														packet_length_info(nullptr),
#endif
														numSegmentsAllocated(0)
	{}
	/**
	* Allocates memory for a decoding code block (but not data)
	*/
	bool alloc();
	void cleanup();
	uint8_t* data;					// pointer to plugin data. 
	uint32_t dataSize;				/* size of data buffer */
    grok_vec_t seg_buffers;
    tcd_seg_t* segs;			/* information on segments */
    uint32_t x0, y0, x1, y1;		/* position: left upper corner (x0, y0) right low corner (x1,y1) */
    uint32_t numbps;
    uint32_t numlenbits;
    uint32_t numPassesInPacket;		/* number of passes added by current packet */
    uint32_t numSegments;			/* number of segment in block*/
    uint32_t numSegmentsAllocated;  // number of segments allocated for segs array
#ifdef DEBUG_LOSSLESS_T2
	uint32_t included;
	std::vector<packet_length_info_t>* packet_length_info;
#endif

};

// precinct
struct tcd_precinct_t {
	tcd_precinct_t() : x0(0),
							y0(0),
							x1(0),
							y1(0), 
							cw(0),
							ch(0), 
							block_size(0), 
							incltree(nullptr), 
							imsbtree(nullptr) 
	{
		cblks.blocks = nullptr;
	}

	tcd_precinct_t(const tcd_precinct_t& rhs) :x0(rhs.x0),
														y0(rhs.y0),
														x1(rhs.x1),
														y1(rhs.y1),
														cw(0),
														ch(0),
														block_size(0),
														incltree( nullptr),
														imsbtree(nullptr) {
		cblks.blocks = nullptr;
	}
	void initTagTrees(event_mgr_t* manager);

	void cleanupEncodeBlocks() {
		if (!cblks.enc)
			return;
		for (uint32_t i = 0; i < cw*ch; ++i)
			(cblks.enc + i)->cleanup();
		delete[] cblks.enc;
	}
	void cleanupDecodeBlocks() {
		if (!cblks.dec)
			return;
		delete[] cblks.dec;
	}

    uint32_t x0, y0, x1, y1;		/* dimension of the precinct : left upper corner (x0, y0) right low corner (x1,y1) */
    uint32_t cw, ch;				/* number of precinct in width and height */
    union {							/* code-blocks information */
        tcd_cblk_enc_t* enc;
        tcd_cblk_dec_t* dec;
        void*               blocks;
    } cblks;
    uint32_t block_size;			/* size taken by cblks (in bytes) */
    TagTree *incltree;	    /* inclusion tree */
    TagTree *imsbtree;	    /* IMSB tree */
};

// band
struct tcd_band_t {
	tcd_band_t() : x0(0),
						y0(0),
						x1(0),
						y1(0), 
						bandno(0),
						precincts(nullptr),
						precincts_data_size(0),
						numbps(0),
						stepsize(0) {}

	tcd_band_t(const tcd_band_t& rhs) : x0(rhs.x0), 
												  y0(rhs.y0),
												  x1(rhs.x1),
												  y1(rhs.y1),
												bandno(rhs.bandno),
												precincts(nullptr),
												precincts_data_size(0),
												numbps(rhs.numbps),
												stepsize(rhs.stepsize)
	 {}
	bool isEmpty() {
		return ((x1 - x0 == 0) || (y1 - y0 == 0));
	}
    uint32_t x0, y0, x1, y1;		/* dimension of the subband : left upper corner (x0, y0) right low corner (x1,y1) */
    uint32_t bandno;
    tcd_precinct_t* precincts;	/* precinct information */
    uint32_t precincts_data_size;	/* size of data taken by precincts */
	size_t numPrecincts;
    uint32_t numbps;
    float stepsize;
};

// resolution
struct tcd_resolution_t {
	tcd_resolution_t() : x0(0),
							y0(0),
							x1(0),
							y1(0),
							numbands(0) {}
	tcd_resolution_t(const tcd_resolution_t& rhs) : x0(rhs.x0),
															y0(rhs.y0),
															x1(rhs.x1),
															y1(rhs.y1),
															pw(rhs.pw),
															ph(rhs.ph),
															numbands(rhs.numbands)

	 {
		for (int i = 0; i < 3; ++i)
			bands[i] = rhs.bands[i];
	}
    uint32_t x0, y0, x1, y1;	/* dimension of the resolution level : left upper corner (x0, y0) right low corner (x1,y1) */
    uint32_t pw, ph;
    uint32_t numbands;			/* number sub-band for the resolution level */
    tcd_band_t bands[3];	/* subband information */
};

// tile component
struct tcd_tilecomp_t {
    uint32_t x0, y0, x1, y1;			/* dimension of component : left upper corner (x0, y0) right low corner (x1,y1) */
    uint32_t numresolutions;			/* number of resolutions level */
    uint32_t minimum_num_resolutions;	/* number of resolutions level to decode (at max)*/
    tcd_resolution_t *resolutions;		/* resolutions information */
#ifdef DEBUG_LOSSLESS_T2
	tcd_resolution_t* round_trip_resolutions;  /* round trip resolution information */
#endif
    uint32_t resolutions_size;			/* size of data for resolutions (in bytes) */
    uint64_t numpix;                  
    tile_buf_component_t* buf;
};


// tile
struct tcd_tile_t {
    uint32_t x0, y0, x1, y1;	/* dimension of the tile : left upper corner (x0, y0) right low corner (x1,y1) */
    uint32_t numcomps;			/* number of components in tile */
    tcd_tilecomp_t *comps;	/* Components information */
    uint64_t numpix;				
    double distotile;			
    double distolayer[100];	
    uint32_t packno;            /* packet number */
};

/**
Tile coder/decoder
*/
struct tcd_t {
    /** Position of the tile part flag in progression order*/
    uint32_t tp_pos;
    /** Tile part number*/
    uint32_t tp_num;
    /** Current tile part number*/
    uint32_t cur_tp_num;
    /** Total number of tile parts of the current tile*/
    uint32_t cur_totnum_tp;
    /** Current packet iterator number */
    uint32_t cur_pino;
    /** info on image tile */
    tcd_tile_t* tile;
    /** image header */
    opj_image_t *image;
    /** coding parameters */
    cp_t *cp;
    /** coding/decoding parameters common to all tiles */
    tcp_t *tcp;
    /** current encoded tile (not used for decode) */
    uint32_t tcd_tileno;
    /** indicate if the tcd is a decoder. */
    uint32_t m_is_decoder : 1;
    grok_plugin_tile_t* current_plugin_tile;
	uint32_t numThreads;
};

/** @name Exported functions */
/*@{*/
/* ----------------------------------------------------------------------- */

/**
Create a new TCD handle
@param p_is_decoder FIXME DOC
@return a new TCD handle if successful returns nullptr otherwise
*/
tcd_t* tcd_create(bool p_is_decoder);

/**
Destroy a previously created TCD handle
@param tcd TCD handle to destroy
*/
void tcd_destroy(tcd_t *tcd);

/**
 * Initialize the tile coder and may reuse some memory.
 * @param	p_tcd		TCD handle.
 * @param	p_image		raw image.
 * @param	p_cp		coding parameters.
 *
 * @return true if the encoding values could be set (false otherwise).
*/
bool tcd_init(	tcd_t *p_tcd,
                    opj_image_t * p_image,
                    cp_t * p_cp ,
					uint32_t numThreads);

/**
 * Allocates memory for decoding a specific tile.
 *
 * @param	p_tcd		the tile decoder.
 * @param	output_image output image - stores the decode region of interest
 * @param	p_tile_no	the index of the tile received in sequence. This not necessarily lead to the
 * tile at index p_tile_no.
 * @param p_manager the event manager.
 *
 * @return	true if the remaining data is sufficient.
 */
bool tcd_init_decode_tile(tcd_t *p_tcd,
                              opj_image_t* output_image,
                              uint32_t p_tile_no,
                              event_mgr_t* p_manager);

/**
 * Gets the maximum tile size that will be taken by the tile once decoded.
 */
uint64_t tcd_get_decoded_tile_size (tcd_t *p_tcd );

/**
 * Encodes a tile from the raw image into the given buffer.
 * @param	p_tcd			Tile Coder handle
 * @param	p_tile_no		Index of the tile to encode.
 * @param	p_dest			Destination buffer
 * @param	p_data_written	pointer to an int that is incremented by the number of bytes really written on p_dest
 * @param	p_len			Maximum length of the destination buffer
 * @param	p_cstr_info		Codestream information structure
 * @return  true if the coding is successful.
*/
bool tcd_encode_tile(   tcd_t *p_tcd,
                            uint32_t p_tile_no,
							GrokStream* p_stream,
                            uint64_t * p_data_written,
                            uint64_t p_len,
                            opj_codestream_info_t *p_cstr_info,
							event_mgr_t * p_manager);


/**
Decode a tile from a buffer into a raw image
@param tcd TCD handle
@param src Source buffer
@param len Length of source buffer
@param tileno Number that identifies one of the tiles to be decoded
@param cstr_info  FIXME DOC
@param manager the event manager.
*/
bool tcd_decode_tile(   tcd_t *tcd,
                            seg_buf_t* src_buf,
                            uint32_t tileno,
                            event_mgr_t *manager);


/**
 * Copies tile data from the system onto the given memory block.
 */
bool tcd_update_tile_data (	tcd_t *p_tcd,
                                uint8_t * p_dest,
                                uint64_t p_dest_length );

/**
 *
 */
uint64_t tcd_get_encoded_tile_size ( tcd_t *p_tcd );

/**
 * Initialize the tile coder and may reuse some meory.
 *
 * @param	p_tcd		TCD handle.
 * @param	p_tile_no	current tile index to encode.
 * @param p_manager the event manager.
 *
 * @return true if the encoding values could be set (false otherwise).
*/
bool tcd_init_encode_tile (	tcd_t *p_tcd,
                                uint32_t p_tile_no, event_mgr_t* p_manager );

/**
 * Copies tile data from the given memory block onto the system.
 */
bool tcd_copy_tile_data (tcd_t *p_tcd,
                             uint8_t * p_src,
                             uint64_t p_src_length );

/**
 * Allocates tile component data
 *
 *
 */
bool tile_buf_create_component(tcd_tilecomp_t * tilec, bool isEncoder,
                                   bool irreversible,
                                   uint32_t cblkw,
                                   uint32_t cblkh,
                                   opj_image_t* output_image,
                                   uint32_t dx,
                                   uint32_t dy);


bool tcd_needs_rate_control(tcp_t *tcd_tcp, encoding_param_t* enc_params);

/* ----------------------------------------------------------------------- */
/*@}*/

/*@}*/



}