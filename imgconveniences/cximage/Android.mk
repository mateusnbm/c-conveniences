LOCAL_PATH := $(call my-dir)
#include $(CLEAR_VARS)

LOCAL_MODULE := cximagelib

LOCAL_C_INCLUDES += CxImage
LOCAL_C_INCLUDES += zlib
LOCAL_C_INCLUDES += jasper/include
LOCAL_C_INCLUDES += jpeg
LOCAL_C_INCLUDES += png
LOCAL_C_INCLUDES += tiff
 
ZLIB_SRC := \
	zlib/adler32.c \
  	zlib/compress.c \
  	zlib/crc32.c \
  	zlib/gzclose.c \
  	zlib/gzlib.c \
  	zlib/gzread.c \
  	zlib/gzwrite.c \
  	zlib/uncompr.c \
  	zlib/deflate.c \
  	zlib/trees.c \
  	zlib/zutil.c \
  	zlib/inflate.c \
  	zlib/infback.c \
  	zlib/inftrees.c \
  	zlib/inffast.c \

JASPER_SRC := \
	jasper/base/jas_cm.c \
  	jasper/base/jas_debug.c \
  	jasper/base/jas_getopt.c \
  	jasper/base/jas_icc.c \
  	jasper/base/jas_iccdata.c \
  	jasper/base/jas_image.c \
  	jasper/base/jas_init.c \
  	jasper/base/jas_malloc.c \
  	jasper/base/jas_seq.c \
  	jasper/base/jas_stream.c \
  	jasper/base/jas_string.c \
  	jasper/base/jas_tvp.c \
  	jasper/base/jas_version.c \
  	jasper/bmp/bmp_cod.c \
  	jasper/bmp/bmp_dec.c \
  	jasper/bmp/bmp_enc.c \
  	jasper/jp2/jp2_cod.c \
  	jasper/jp2/jp2_dec.c \
  	jasper/jp2/jp2_enc.c \
  	jasper/jpc/jpc_bs.c \
  	jasper/jpc/jpc_cs.c \
  	jasper/jpc/jpc_dec.c \
  	jasper/jpc/jpc_enc.c \
  	jasper/jpc/jpc_math.c \
  	jasper/jpc/jpc_mct.c \
  	jasper/jpc/jpc_mqcod.c \
  	jasper/jpc/jpc_mqdec.c \
  	jasper/jpc/jpc_mqenc.c \
  	jasper/jpc/jpc_qmfb.c \
  	jasper/jpc/jpc_t1cod.c \
  	jasper/jpc/jpc_t1dec.c \
  	jasper/jpc/jpc_t1enc.c \
  	jasper/jpc/jpc_t2cod.c \
  	jasper/jpc/jpc_t2dec.c \
  	jasper/jpc/jpc_t2enc.c \
  	jasper/jpc/jpc_tagtree.c \
  	jasper/jpc/jpc_tsfb.c \
  	jasper/jpc/jpc_util.c \
  	jasper/jpg/jpg_dec.c \
  	jasper/jpg/jpg_enc.c \
  	jasper/jpg/jpg_val.c \
  	jasper/mif/mif_cod.c \
  	jasper/pgx/pgx_cod.c \
  	jasper/pgx/pgx_dec.c \
  	jasper/pgx/pgx_enc.c \
  	jasper/ras/ras_cod.c \
  	jasper/ras/ras_dec.c \
  	jasper/ras/ras_enc.c \
  	jasper/pnm/pnm_cod.c \
  	jasper/pnm/pnm_dec.c \
  	jasper/pnm/pnm_enc.c 

JPEG_SRC := \
	jpeg/jerror.c \
	jpeg/jdatasrc.c \
	jpeg/jdmarker.c \
	jpeg/jcomapi.c \
	jpeg/jutils.c \
	jpeg/jdapimin.c \
	jpeg/jdapistd.c \
	jpeg/jcapistd.c \
	jpeg/jcapimin.c \
	jpeg/jcparam.c \
	jpeg/jdatadst.c \
	jpeg/jmemmgr.c \
	jpeg/jdinput.c \
	jpeg/jdmaster.c \
	jpeg/jcinit.c \
	jpeg/jcmarker.c \
	jpeg/jmemnobs.c \
	jpeg/jquant1.c \
	jpeg/jquant2.c \
	jpeg/jdmerge.c \
	jpeg/jdmainct.c \
	jpeg/jdcolor.c \
	jpeg/jdsample.c \
	jpeg/jdpostct.c \
	jpeg/jddctmgr.c \
	jpeg/jdarith.c \
	jpeg/jdhuff.c \
	jpeg/jdcoefct.c \
	jpeg/jcmaster.c \
	jpeg/jccolor.c \
	jpeg/jcsample.c \
	jpeg/jcdctmgr.c \
	jpeg/jcarith.c \
	jpeg/jchuff.c \
	jpeg/jcprepct.c \
	jpeg/jccoefct.c \
	jpeg/jcmainct.c \
	jpeg/jaricom.c \
	jpeg/jfdctflt.c \
	jpeg/jidctint.c \
	jpeg/jfdctfst.c \
	jpeg/jfdctint.c \
	jpeg/jidctfst.c \
	jpeg/jidctflt.c \
	
PNG_SRC := \
	png/png.c \
  	png/pngerror.c \
  	png/pngget.c \
  	png/pngmem.c \
  	png/pngpread.c \
  	png/pngread.c \
  	png/pngrio.c \
  	png/pngrtran.c \
  	png/pngrutil.c \
  	png/pngset.c \
  	png/pngtrans.c \
  	png/pngwio.c \
  	png/pngwrite.c \
  	png/pngwtran.c \
  	png/pngwutil.c \
  
TIFF_SRC := \
	tiff/tif_open.c \
	tiff/tif_close.c \
	tiff/tif_dir.c \
	tiff/tif_aux.c \
	tiff/tif_getimage.c \
	tiff/tif_strip.c \
	tiff/tif_tile.c \
	tiff/tif_dirwrite.c \
	tiff/tif_write.c \
	tiff/tif_read.c \
	tiff/tif_error.c \
	tiff/tif_compress.c \
	tiff/tif_swab.c \
	tiff/tif_dirread.c \
	tiff/tif_flush.c \
	tiff/tif_warning.c \
	tiff/tif_dirinfo.c \
	tiff/tif_color.c \
	tiff/tif_codec.c \
	tiff/tif_dumpmode.c \
	tiff/tif_lzw.c \
	tiff/tif_fax3.c \
	tiff/tif_jbig.c \
	tiff/tif_jpeg.c \
	tiff/tif_ojpeg.c \
	tiff/tif_packbits.c \
	tiff/tif_thunder.c \
	tiff/tif_next.c \
	tiff/tif_zip.c \
	tiff/tif_luv.c \
	tiff/tif_predict.c \
	tiff/tif_fax3sm.c \
  		
CXIMAGE_SRC := \
	CxImage/tif_xfile.cpp \
  	CxImage/ximabmp.cpp \
  	CxImage/ximadsp.cpp \
  	CxImage/ximaenc.cpp \
  	CxImage/ximaexif.cpp \
  	CxImage/ximage.cpp \
  	CxImage/ximagif.cpp \
  	CxImage/ximahist.cpp \
  	CxImage/ximaico.cpp \
  	CxImage/ximainfo.cpp \
  	CxImage/ximaint.cpp \
  	CxImage/ximajas.cpp \
  	CxImage/ximajbg.cpp \
  	CxImage/ximajpg.cpp \
  	CxImage/ximalpha.cpp \
  	CxImage/ximalyr.cpp \
  	CxImage/ximamng.cpp \
  	CxImage/ximapal.cpp \
  	CxImage/ximapcx.cpp \
  	CxImage/ximapng.cpp \
  	CxImage/ximasel.cpp \
  	CxImage/ximath.cpp \
  	CxImage/ximatif.cpp \
  	CxImage/ximatran.cpp \
  	CxImage/ximawbmp.cpp \
  	CxImage/ximawmf.cpp \
  	CxImage/ximawnd.cpp \
  	CxImage/xmemfile.cpp \
  	CxImage/ximatga.cpp \
    	
LOCAL_SRC_FILES := \
	$(ZLIB_SRC) \
	$(JASPER_SRC) \
	$(JPEG_SRC) \
	$(PNG_SRC) \
	$(TIFF_SRC) \
	$(CXIMAGE_SRC) \  	

LOCAL_CFLAGS := CXIMAGE_SUPPORT_EXIF \
    CXIMAGEJPG_SUPPORT_EXIF

NDK_MODULE_PATH := $(LOCAL_PATH)
#include $(PREBUILT_STATIC_LIBRARY)
include $(BUILD_SHARED_LIBRARY)