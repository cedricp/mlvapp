#ifndef _raw_processing_
#define _raw_processing_

#include "processing_object.h"
#include "filter/filter.h"

/* Intitialises a 'processing object' which is a structure 
 * that makes it easy to contol all the processing */
processingObject_t * initProcessingObject();
/* Opposite of the first fucntion */
void freeProcessingObject(processingObject_t * processing);


/* Set processing gamut */
void processingSetGamut(processingObject_t * processing, int gamut);
int processingGetGamut(processingObject_t * processing);
#define GAMUT_Rec709 0
#define GAMUT_Rec2020 1
#define GAMUT_ACES_AP0 2
#define GAMUT_AdobeRGB 3
#define GAMUT_ProPhotoRGB 4
#define GAMUT_XYZ 5
#define GAMUT_AlexaWideGamutRGB 6
#define GAMUT_SonySGamut3 7
#define GAMUT_BmdFilm 8


/* Tonemapping function, really this can be a tonemapping function, a log
 * function or any other gamma or transfer function */
void processingSetTonemappingFunction(processingObject_t * processing, int function);
int processingGetTonemappingFunction(processingObject_t * processing);
/* Set transfer funtion in old way */
void processingSetGammaAndTonemapping(processingObject_t * processing, double gamma, int tonemapping);
#define TONEMAP_None 0
#define TONEMAP_Reinhard 1
#define TONEMAP_Tangent 2
#define TONEMAP_AlexaLogC 3
#define TONEMAP_CineonLog 4
#define TONEMAP_SonySLog 5
#define TONEMAP_sRGB 6
#define TONEMAP_Rec709 7
#define TONEMAP_HLG 8
#define TONEMAP_BMDFilm 9
#define TONEMAP_Reinhard_3_5 10 /* Reinhard 3/5 */


/* Transfer funciton, the correct version of "Gamma" or "Log" */
int processingSetTransferFunction(processingObject_t * processing, char * function); /* Nonzero return value = Failure, transfer function unchanged */
char * processingGetTransferFunction(processingObject_t * processing); /* Read */


/* why does gradient have a gamma  */
void processingSetGamma(processingObject_t * processing, double gammaValue);
#define processingGetGamma(processing) (processing)->gamma_power
void processingSetGammaGradient(processingObject_t * processing, double gammaValue);



/* Set one of default image profiles */
void processingSetImageProfile(processingObject_t * processing, int imageProfile);
/* imageProfile argument options: */
#define PROFILE_STANDARD    0   /* Gamma Corrected */
#define PROFILE_TONEMAPPED  1   /* Gamma Corrected + Tonemapped */
#define PROFILE_FILM        2   /* Gamma Corrected + inverse tangent tonemap */
#define PROFILE_ALEXA_LOG   3   /* Alexa log (A form of Log-C) */
#define PROFILE_CINEON_LOG  4   /* Cineon Log */
#define PROFILE_SONY_LOG_3  5   /* Sony S-Log 3 */
#define PROFILE_LINEAR      6   /* Linear, idk who would want this */
#define PROFILE_SRGB        7	/* sRGB */
#define PROFILE_REC709      8	/* Rec. 709 (HDTV) */
#define PROFILE_BMDFILM     9   /* BMDFilm */



/* Process a RAW frame with settings from a processing object
 * - image must be debayered and RGB plz + thx! */
void applyProcessingObject( processingObject_t * processing, 
                            int imageX, int imageY, 
                            uint16_t * __restrict inputImage, 
                            uint16_t * __restrict outputImage,
                            int threads, int imageChanged, uint64_t frameIndex );

/* This is for EXR output, works exactly the same as applyprocessing object,
 * except output is float and ready for EXR export. */
void processingGetFloatOutputForEXR( processingObject_t * processing, 
                                     int imageX, int imageY, 
                                     uint16_t * inputImage, 
                                     float * outputImage,
                                     int threads, int imageChanged, uint64_t frameIndex );


/* Enable/disable the filter module (filter/filter.h) */
#define processingEnableFilters(processing) processing->filter_on = 1
#define processingDisableFilters(processing) processing->filter_on = 0

/* Enable/disable the LUT module (lut3d.h) */
#define processingEnableLut(processing) processing->lut_on = 1
#define processingDisableLut(processing) processing->lut_on = 0

/* Setup LUT strength */
void processingSetLutStrength(processingObject_t *processing, uint8_t strength);

/* Highlights/shadows, input: -1.0 to +1.0 (show as -100 to +100) */
void processingSetHighlights(processingObject_t * processing, double value);
void processingSetShadows(processingObject_t * processing, double value);



/* Set contrast(S-curve really) - important: precalculates values, 
 * so don't do it manually, we r OOPing so hard right now */
void processingSetContrast( processingObject_t * processing, 
                            double DCRange,  /* Dark contrast range: 0.0 to 1.0 */
                            double DCFactor, /* Dark contrast strength: 0.0 to 8.0(any range really) */
                            double LCRange,  /* Light contrast range */
                            double LCFactor, /* Light contrast strength */ 
                            double lighten   /* 0-1 (for good highlight rolloff) */ );
void processingSetDCRange(processingObject_t * processing, double DCRange);
void processingSetDCFactor(processingObject_t * processing, double DCFactor);
void processingSetLCRange(processingObject_t * processing, double LCRange);
void processingSetLCFactor(processingObject_t * processing, double LCFactor);
void processingSetLightening(processingObject_t * processing, double lighten); /* RANGE IS 0.0-0.6 */
/* For getting info about contrast */
#define processingGetDCRange(processing) (processing)->dark_contrast_range
#define processingGetDCFactor(processing) (processing)->dark_contrast_factor
#define processingGetLCRange(processing) (processing)->light_contrast_range
#define processingGetLCFactor(processing) (processing)->light_contrast_factor
#define processingGetLightening(processing) (processing)->lighten



/* Set sharpening, 0.0-1.0 range */
void processingSetSharpening(processingObject_t * processing, double sharpen);
#define processingGetSharpening(processing) (processing)->sharpen
/* Set direction bias... 0=equal, -1=horizontal, 1=vertical */
void processingSetSharpeningBias(processingObject_t * processing, double bias);
#define processingGetSharpeningBias(processing) (processing)->sharpen_bias
/* Set sharpen masking, 0..100 */
#define processingSetSharpenMasking(processing, value) (processing)->sh_masking = (value)


/* 3-way correction, range of saturation and hue is 0.0-1.0 (Currently not doing anything) */
void processingSet3WayCorrection( processingObject_t * processing,
                                  double highlightHue, double highlightSaturation,
                                  double midtoneHue, double midtoneSaturation,
                                  double shadowHue, double shadowSaturation );


/* Enable/disable highlight reconstruction */
#define processingEnableChromaSeparation(processing) (processing)->cs_zone.use_cs = 1
#define processingDisableChromaSeparation(processing) (processing)->cs_zone.use_cs = 0
#define processingUsesChromaSeparation(processing) (processing)->cs_zone.use_cs /* A checking function */


/* Chroma blur - to enable it, you MUST enable chroma separation too. */
#define processingSetChromaBlurRadius(processing, radius) (processing)->cs_zone.chroma_blur_radius = (radius)
#define processingGetChromaBlurRadius(processing) (processing)->cs_zone.chroma_blur_radius

/* Denoiser */
#define processingSetDenoiserWindow(processing, window) (processing)->denoiserWindow = (window)
#define processingGetDenoiserWindow(processing) (processing)->denoiserWindow
#define processingSetDenoiserStrength(processing, strength) (processing)->denoiserStrength = (strength)
#define processingGetDenoiserStrength(processing) (processing)->denoiserStrength

#define processingSetRbfDenoiserLuma(processing, strength) (processing)->rbfDenoiserLuma = (strength)
#define processingGetRbfDenoiserLuma(processing) (processing)->rbfDenoiserLuma
#define processingSetRbfDenoiserChroma(processing, strength) (processing)->rbfDenoiserChroma = (strength)
#define processingGetRbfDenoiserChroma(processing) (processing)->rbfDenoiserChroma
#define processingSetRbfDenoiserRange(processing, strength) (processing)->rbfDenoiserRange = (strength)
#define processingGetRbfDenoiserRange(processing) (processing)->rbfDenoiserRange

/* Grain */
#define processingSetGrainStrength(processing, strength) (processing)->grainStrength = (strength)
#define processingSetGrainLumaWeight(processing, strength) (processing)->grainLumaWeight = (strength)

/* Vignette */
void processingSetVignetteStrength(processingObject_t * processing, int8_t value);
void processingSetVignetteMask(processingObject_t * processing, uint16_t width, uint16_t height, float radius, float shape, float xStretch, float yStretch);

/* Gradient */
void processingSetGradientMask(processingObject_t * processing, uint16_t width, uint16_t height, float x1, float y1, float x2, float y2 );
void processingSetGradientExposure(processingObject_t * processing, double value);
#define processingGetGradientExposure(processing) (processing)->gradient_exposure_stops
#define processingSetGradientEnable(processing, value) (processing)->gradient_enable = (value)
#define processingIsGradientEnabled(processing) (processing)->gradient_enable
/* Gradient simple contrast */
void processingSetSimpleContrastGradient(processingObject_t * processing, double value);
#define processingGetSimpleContrastGradient(processing) (processing)->gradient_contrast
/* Calculate gradient contrast exposure LUT */
void processing_update_contrast_curve_gradient(processingObject_t * processing);


/* Enable/disable highlight reconstruction */
#define processingEnableHighlightReconstruction(processing) (processing)->highlight_reconstruction = 1
#define processingDisableHighlightReconstruction(processing) (processing)->highlight_reconstruction = 0

/* Enable/disable creative adjustments when log active */
#define processingAllowCreativeAdjustments(processing) (processing)->allow_creative_adjustments = 1
#define processingDontAllowCreativeAdjustments(processing) (processing)->allow_creative_adjustments = 0
#define processingGetAllowedCreativeAdjustments(processing) ((processing)->allow_creative_adjustments)

/* Toning */
void processingSetToning(processingObject_t * processing, uint8_t r, uint8_t g, uint8_t b, uint8_t strength);

/* Use or not use camera matrix - compatibility mode */
#define processingUseCamMatrix(processing) (processing)->use_cam_matrix = 1
#define processingUseCamMatrixDanne(processing) (processing)->use_cam_matrix = 2
#define processingDontUseCamMatrix(processing) (processing)->use_cam_matrix = 0
#define processingGetUsedCamMatrix(processing) ((processing)->use_cam_matrix)

/* EXR mode */
#define processingEnableExr(processing) (processing)->exr_mode = 1
#define processingDisableExr(processing) (processing)->exr_mode = 0

/* Set Camera RAW matrix (matrix A is for tungsten) */
void processingSetCamMatrix(processingObject_t * processing, double * camMatrix, double * camMatrixA);



/* Sets a processing object's Exposure: 0 = no adjustment */
void processingSetExposureStops(processingObject_t * processing, double exposureStops);
/* Gets a processing object's exposure value in stops */
#define processingGetExposureStops(processing) (processing)->exposure_stops

/* Set simple contrast */
void processingSetSimpleContrast(processingObject_t * processing, double value);
#define processingGetSimpleContrast(processing) (processing)->contrast
/* Set pivot */
void processingSetPivot(processingObject_t * processing, double value);
#define processingGetPivot(processing) (processing)->pivot
/* Calculate contrast exposure LUT */
void processing_update_contrast_curve(processingObject_t * processing);

/* Set clarity */
void processingSetClarity(processingObject_t * processing, double value);
#define processingGetClarity(processing) (processing)->clarity
/* Calculate contrast exposure LUT */
void processing_update_clarity_curve(processingObject_t * processing);

/* Set white balance by kelvin and/or tint value; Kelvin range: 2500-10000, tint -10 to +10 */
void processingSetWhiteBalance(processingObject_t * processing, double WBKelvin, double WBTint);
void processingSetWhiteBalanceKelvin(processingObject_t * processing, double WBKelvin);
void processingSetWhiteBalanceTint(processingObject_t * processing, double WBTint);
#define processingGetWhiteBalanceKelvin(processing) (processing)->kelvin
#define processingGetWhiteBalanceTint(processing) (processing)->wb_tint
void processingFindWhiteBalance(processingObject_t * processing,
                                int imageX, int imageY,
                                uint16_t * __restrict inputImage,
                                int posX, int posY,
                                int *wbTemp, int *wbTint, int mode);


/* Black/white level set */
void processingSetBlackLevel(processingObject_t * processing, float mlvBlackLevel, int mlvBitDepth);
void processingSetWhiteLevel(processingObject_t * processing, int mlvWhiteLevel, int mlvBitDepth);
void processingSetBlackAndWhiteLevel(processingObject_t * processing,
                                      float mlvBlackLevel, int mlvWhiteLevel, int mlvBitDepth );

/* Get black/white level */
#define processingGetBlackLevel(processing) (processing)->black_level
#define processingGetWhiteLevel(processing) (processing)->white_level

/* Saturation setting: 1.0 = no saturation added, 0.0 = black and white ... */
void processingSetSaturation(processingObject_t * processing, double saturationFactor);
/* Get saturation - I don't see the use but maybe useful */
#define processingGetSaturation(processing) (processing)->saturation

/* Vibrance setting: 1.0 = no vibrance added, 0.0 = black and white ... */
void processingSetVibrance(processingObject_t * processing, double vibranceFactor);
/* Get vibrance */
#define processingGetVibrance(processing) (processing)->vibrance

/* Enable/disable tonemapping - DEPRECATED!!! (made private) */
#define processingEnableTonemapping(processing) processing_enable_tonemapping(processing)
#define processingDisableTonemapping(processing) processing_disable_tonemapping(processing)

/* Set transformation */
void processingSetTransformation(processingObject_t * processing, int transformation);

/* Set gradation curve */
void processingSetGCurve(processingObject_t * processing, int num, float * pXin, float * pYin, uint8_t channel);

/* Set Hue vs. Luma curve */
void processingSetHueVsCurves(processingObject_t * processing, int num, float * pXin, float * pYin, uint8_t channel);

/* Set CA filter parameter */
#define processingSetCaDesaturate(processing, value) (processing)->ca_desaturate = (value)
#define processingSetCaRadius(processing, value) (processing)->ca_radius = (value)

/*
 *******************************************************************************
 * THE FOLLOWING FUNCTIONS ARE PRIVATE AND NO USE OUTSIDE OF raw_processing.c
 ******************************************************************************
 */

/* Private function */
void apply_processing_object(processingObject_t * processing,
                              int imageX, int imageY,
                              uint16_t * __restrict inputImage,
                              uint16_t * __restrict outputImage,
                              uint16_t * __restrict blurImage,
                              uint16_t * __restrict gradientMask,
                              float *vignetteMask);

/* Pass frame buffer and do the transform on it */
void get_frame_transformed(processingObject_t * processing, uint16_t * frame_buf , uint16_t imageX, uint16_t imageY);

/* Useful info:
 * http://www.magiclantern.fm/forum/index.php?topic=19270
 * Thanks a1ex & g3gg0 */

typedef struct {
    processingObject_t * processing;
    int imageX, imageY;
    uint16_t * inputImage;
    uint16_t * outputImage;
    uint16_t * blurImage;
    uint16_t * gradientMask;
    float * vignetteMask;
} apply_processing_parameters_t;

/* applyProcessingObject but with one argument for pthreading  */
void processing_object_thread(apply_processing_parameters_t * p);

/* Calculate shadow/hiughlight exposure LUT */
void processing_update_shadow_highlight_curve(processingObject_t * processing);

/* Adds contrast to a single pixel in a S-curvey way, 
 * input pixel must be 0.0 - 1.0 and a double float */
double add_contrast( double pixel,
                     double dark_contrast_range, 
                     double dark_contrast_factor, 
                     double light_contrast_range, 
                     double light_contrast_factor );

/* Enable/disable tonemapping */
void processing_enable_tonemapping(processingObject_t * processing);
void processing_disable_tonemapping(processingObject_t * processing);

/* Returns multipliers for white balance by (linearly) interpolating measured 
 * Canon values... stupidly simple, also range limited to 2500-10000 */
void get_kelvin_multipliers_rgb(double kelvin, double * multiplier_output);
void get_kelvin_multipliers_xyz(double T, double * RGB);

/* Calculates final_matrix, incorporating white balance, exposure and all the XYZ stuff */
void processing_update_matrices(processingObject_t * processing);
void processing_update_matrices_gradient(processingObject_t * processing);

/* Calculates green clip value, so highlight reconstruction can work */
void processing_update_highest_green(processingObject_t * processing);
void processing_update_highest_green_gradient(processingObject_t * processing);

/* Precalculates curve with contrast and colour correction */
void processing_update_curves(processingObject_t * processing);

/* Analyse dual iso frame to find highest green for highlight reconstruction */
void analyse_frame_highest_green(processingObject_t * processing,
                                  int imageX, int imageY,
                                  uint16_t * __restrict inputImage);

/* Pretty good function */
void hsv_to_rgb(double hue, double saturation, double value, double * rgb);

/* 3 way colour correction */
void colour_correct_3_way( double * rgb,
                           double h_hue, double h_sat,
                           double m_hue, double m_sat,
                           double s_hue, double s_sat );

/* Just a awful box blur right now */
void blur_image( uint16_t * __restrict in,
                 uint16_t * __restrict out,
                 int width, int height, int radius,
                 int do_r, int do_g, int do_b,
                 int start_y, int end_y );
/* JUst to be separate */
void convert_rgb_to_YCbCr(uint16_t * __restrict img, int32_t size, int32_t ** lut);
void convert_YCbCr_to_rgb(uint16_t * __restrict img, int32_t size, int32_t ** lut);

/* Tonemapping funtions */

/* Uncharted and Reinhard: http://filmicworlds.com/blog/filmic-tonemapping-operators/ */
double uncharted_tonemap(double x);
double UnchartedTonemap(double x);
double ReinhardTonemap(double x);
float ReinhardTonemap_f(float x);
/* Inverse tangent based tonemap - interesting... filmmic? */
double TangentTonemap(double x);
float TangentTonemap_f(float x);
/* Canon C-Log: http://learn.usa.canon.com/app/pdfs/white_papers/White_Paper_Clog_optoelectronic.pdf */
double CanonCLogTonemap(double x); /* Not working right */
float CanonCLogTonemap_f(float x);
/* Calculate Alexa Log curve (iso 800 version), from here: http://www.vocas.nl/webfm_send/964 */
double AlexaLogCTonemap(double x);
float AlexaLogCTonemap_f(float x);
/* Cineon Log, formula from here: http://www.magiclantern.fm/forum/index.php?topic=15801.msg158145#msg158145 */
double CineonLogTonemap(double x);
float CineonLogTonemap_f(float x);
/* Sony S-Log3, from here: https://www.sony.de/pro/support/attachment/1237494271390/1237494271406/technical-summary-for-s-gamut3-cine-s-log3-and-s-gamut3-s-log3.pdf */
double SonySLogTonemap(double x);
float SonySLogTonemap_f(float x);

/* Little image buffer 'class' for storing stuff that takes long to compute,
 * like blur (unused so far) */

#endif
