/*
 *
 *  Copyright (C) 1994-2005, OFFIS
 *
 *  This software and supporting documentation were developed by
 *
 *    Kuratorium OFFIS e.V.
 *    Healthcare Information and Communication Systems
 *    Escherweg 2
 *    D-26121 Oldenburg, Germany
 *
 *  THIS SOFTWARE IS MADE AVAILABLE,  AS IS,  AND OFFIS MAKES NO  WARRANTY
 *  REGARDING  THE  SOFTWARE,  ITS  PERFORMANCE,  ITS  MERCHANTABILITY  OR
 *  FITNESS FOR ANY PARTICULAR USE, FREEDOM FROM ANY COMPUTER DISEASES  OR
 *  ITS CONFORMITY TO ANY SPECIFICATION. THE ENTIRE RISK AS TO QUALITY AND
 *  PERFORMANCE OF THE SOFTWARE IS WITH THE USER.
 *
 *  Module:  dcmdata
 *
 *  Author:  Marco Eichelberg
 *
 *  Purpose: singleton class that registers RLE encoder.
 *
 *  Last Update:      $Author: lpysher $
 *  Update Date:      $Date: 2006/03/01 20:15:22 $
 *  Source File:      $Source: /cvsroot/osirix/osirix/Binaries/dcmtk-source/dcmdata/dcrleerg.cc,v $
 *  CVS/RCS Revision: $Revision: 1.1 $
 *  Status:           $State: Exp $
 *
 *  CVS/RCS Log at end of file
 *
 */

#include "osconfig.h"
#include "dcrleerg.h"

#include "dccodec.h"  /* for DcmCodecStruct */
#include "dcrlecce.h" /* for class DcmRLECodecEncoder */
#include "dcrlecp.h"  /* for class DcmRLECodecParameter */

// initialization of static members
OFBool DcmRLEEncoderRegistration::registered                  = OFFalse;
DcmRLECodecParameter *DcmRLEEncoderRegistration::cp           = NULL;
DcmRLECodecEncoder *DcmRLEEncoderRegistration::codec          = NULL;

void DcmRLEEncoderRegistration::registerCodecs(
    OFBool pCreateSOPInstanceUID,
    OFBool pVerbose,
    Uint32 pFragmentSize,
    OFBool pCreateOffsetTable,
    OFBool pConvertToSC)
{
  if (! registered)
  {
    cp = new DcmRLECodecParameter(
      pVerbose,
      pCreateSOPInstanceUID,
      pFragmentSize,
      pCreateOffsetTable,
      pConvertToSC);

    if (cp)
    {
      codec = new DcmRLECodecEncoder();
      if (codec) DcmCodecList::registerCodec(codec, NULL, cp);
      registered = OFTrue;
    }
  }
}

void DcmRLEEncoderRegistration::cleanup()
{
  if (registered)
  {
    DcmCodecList::deregisterCodec(codec);
    delete codec;
    delete cp;
    registered = OFFalse;
#ifdef DEBUG
    // not needed but useful for debugging purposes
    codec = NULL;
    cp     = NULL;
#endif

  }
}


/*
 * CVS/RCS Log
 * $Log: dcrleerg.cc,v $
 * Revision 1.1  2006/03/01 20:15:22  lpysher
 * Added dcmtkt ocvs not in xcode  and fixed bug with multiple monitors
 *
 * Revision 1.2  2005/12/08 15:41:34  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.1  2002/06/06 14:52:42  meichel
 * Initial release of the new RLE codec classes
 *   and the dcmcrle/dcmdrle tools in module dcmdata
 *
 *
 */
