/************* COPYRIGHT AND CONFIDENTIALITY INFORMATION *********************
**                                                                          **
** Copyright © 2014 - 2016 – Technicolor Technology Licensing SAS and/or    **
** its Group Company                                                        **
**                                                                          **
** All Rights Reserved                                                      **
**                                                                          **
** This program contains proprietary information which is a trade secret of **
** Technicolor and also is protected by intellectual property as an         **
** unpublished work under applicable Copyright laws/right of authorship.    **
**                                                                          **
** This program is also subject to some patent and pending patent           **
** applications.                                                            **
** Technicolor® is registered trademark and trade name of Technicolor group **
** company, and shall not be used in any manner without express written     **
** from Technicolor.                                                        **
**                                                                          **
** The use of the program and documentation is strictly limited to your own **
** internal evaluation of such program and its functionalities, unless      **
** expressly agreed otherwise by Technicolor under a specific agreement.    **
**                                                                          **
** Recipient is to retain this program in confidence and is not permitted   **
** to use or make copies thereof other than as permitted in a written       **
** agreement with Technicolor, unless otherwise expressly allowed by        **
** applicable laws.                                                         **
**                                                                          **
** Recipient is not allowed to make any copy, decompile, reverse engineer,  **
** disassemble, and attempt to derive the source code of, modify, or create **
** derivative works of the program, any update, or any part thereof.        **
**                                                                          **
** Any violation or attempt to do so is a violation of the rights of        **
** Technicolor. If you or any person under your control or authority breach **
** this restriction, you may be subject to prosecution and damages.         **
**                                                                          **
******************************************************************************
** @file    itmo_main.cpp                                                   **
** @author  $Author$:  Author of last commit                                **
** @version $Rev$:     Revision of last commit                              **
** @date    $Date$:    Date of last commit                                  **
** @brief   Technicolor ITMO-Mobile for Android. Convert SDR YUV-420 8b     **
**          video frames to HDR RGB 8bits video frames using ITMO algorithm **
**                                                                          **
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdint.h>

#include <androidLog.h>
#include <utils.h>

#include "itmo.h"
#include "dspCV.h"
#include "AEEStdErr.h"
#include "itmo_common.h"
#include "itmo_lut.h"
#include "itmo_colorConvert.h"
#include "itmo_main.h"
#include "rpcmem.h" // helper API's for shared buffer allocation

int
main(
        int pArgc,
        char* pArgv[])
{
  
    t_tchITMOAndroidContext * itmoLib = NULL;
    int width = 4;
    int height = 4;
    int imageSize = width*height;
    size_t readSize = 0;
	
static uint8_t m_testY[imageSize] = {
      0,    0,    0,    0, // black
    219,  219,  219,  219, // white
     32,   64,  128,  192, // Greys
     62,  172,   31,  219  // Primaries + Yellow
};
	static uint8_t m_Yf[imageSize];
    t_tch_colorFormat yuvFormat = TCH_COLOR_FORMAT_RGBA;
    t_tch_colorFormat outFormat = TCH_COLOR_FORMAT_RGBA;
    t_tch_retCode rc = TCH_RET_SUCCESS;
	
    rc = itmoopen(&itmoLib);
    if ((rc != TCH_RET_SUCCESS) || (itmoLib == NULL)) {
        goto out;
    }

    rc = itmoconfigure(
            itmoLib,
            width,
            height,
            width,
            yuvFormat,
            outFormat);
    if (rc != TCH_RET_SUCCESS) {
        goto out;
    }

    rc = itmostart(itmoLib);
    if (rc != TCH_RET_SUCCESS) {
        goto out;
    }
	memcpy((t_ITMOAndroidContext*)itmoLib->Y,m_testY, imageSize);

    /* Launch ITMO processing */
    ALOGD("Launch ITMO processing");
	printf("before to ITMO processing\n");
	

printf("###############################WANG#######################################\n");
rc = itmo_filter_Process(
         (t_ITMOAndroidContext*)itmoLib);   
printf("###############################WANG#######################################\n");
	
	memcpy(m_Yf,(t_ITMOAndroidContext*)itmoLib->Y, imageSize);
for (int i=0; i<Width*Height; i+=4) 
        printf("% 3d  % 3d  % 3d  % 3d\n",
                m_Yf[i+0], m_Yf[i+1], m_Yf[i+2], m_Yf[i+3]);
	

out:
    ALOGD("End of processing; exiting...");

    if (yuvBuffer != NULL) 
    {
	rpcmem_free(yuvBuffer);
    }
    if (rgbBuffer != NULL) 
    {
	rpcmem_free(yuvBuffer);
    }
    if (rgbaBuffer != NULL) 
    {
	rpcmem_free(rgbaBuffer);
    }
    rpcmem_deinit();
    return (int)rc;
}



