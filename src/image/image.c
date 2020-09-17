#include "image.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <jpeglib.h>

struct image {
    int height;
    int width;
    int components;
    J_COLOR_SPACE color_space;
    JSAMPLE* buffer;
};

struct jpeg_property {
    void (*jpeg_set_property)(j_compress_ptr, void*);
    void* arg;
};

static struct image* decompress(const char*);
static void compress(struct image*, const char*, const struct jpeg_property*);
static void jpeg_set_property_quality(j_compress_ptr, void*);

extern int print_image() {
    struct image* image;
    image = decompress(RESOURCES_PATH "/images/800px-Felis_silvestris_silvestris.jpg");
    struct jpeg_property* property = (struct jpeg_property*) malloc(sizeof(struct jpeg_property) * 2);
    property[0].jpeg_set_property = jpeg_set_property_quality;
    property[0].arg = (void*)5;
    property[1].jpeg_set_property = NULL;
    compress(image, RESOURCES_PATH "/images/output.jpg", property);
    free(property);
    free(image->buffer);
    free(image);
	return printf("Image!\n");
}

static void jpeg_set_property_quality(j_compress_ptr cinfo, void* quality) {
    jpeg_set_quality(cinfo, (int)(long)quality, TRUE);
}

static void compress(struct image* image, const char* out_filename, const struct jpeg_property* property) {

	/* Allocate and initialize JPEG compression object */

	struct jpeg_error_mgr jerr;				/* JPEG error handler. We just use the standard error handler. */
	struct jpeg_compress_struct cinfo;		/* JPEG compression parameters and pointers to working space.  We refer to it as a "JPEG object". */
	cinfo.err = jpeg_std_error(&jerr);		/* Set up the error handler. */
	jpeg_create_compress(&cinfo);			/* Initialize the JPEG compression object. */

	/* Specify data destination (eg, a file) */

	FILE* out_file;
	if ((out_file = fopen(out_filename, "wb")) == NULL) {
		fprintf(stderr, "can't open %s\n", out_filename);
		exit(EXIT_FAILURE);
	}
	jpeg_stdio_dest(&cinfo, out_file);

	/* Set parameters for compression */

	cinfo.image_width = image->width;		    /* Image width and height, in pixels */
	cinfo.image_height = image->height;
	cinfo.input_components = image->components; /* Number of color components per pixel */
	cinfo.in_color_space = image->color_space;  /* Colorspace of input image */
	jpeg_set_defaults(&cinfo);				    /* Use the library's routine to set default compression parameters. */

    while (property->jpeg_set_property) {
        property->jpeg_set_property(&cinfo, property->arg);
        property++;
    }
	//jpeg_set_quality(&cinfo, quality, TRUE      /* limit to baseline-JPEG values */);

	/* Start compressor */

    jpeg_start_compress(&cinfo, TRUE);      /* Pass TRUE unless you are very sure of what you're doing. */

    /* Compress */

	JSAMPROW row_pointer[1];				/* pointer to JSAMPLE row[s] */
    int row_stride;                         /* physical row width in image buffer */

	row_stride = image->width * 3;			/* JSAMPLEs per row in image_buffer (RGB) */

    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = &(image->buffer)[cinfo.next_scanline * row_stride];
        (void)jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    /* Finish compression */

    jpeg_finish_compress(&cinfo);
    fclose(out_file);

    /* Release JPEG compression object */

    jpeg_destroy_compress(&cinfo);

}

static struct image* decompress(const char* in_filename) {

    /* Allocate and initialize return image */

    struct image* result;
    result = malloc(sizeof(struct image));

    /* Allocate and initialize JPEG decompression object */

    struct jpeg_error_mgr jerr;				/* JPEG error handler. We just use the standard error handler. */
    struct jpeg_decompress_struct cinfo;	/* JPEG compression parameters and pointers to working space.  We refer to it as a "JPEG object". */
    cinfo.err = jpeg_std_error(&jerr);		/* Set up the error handler. */
    jpeg_create_decompress(&cinfo);			/* Initialize the JPEG compression object. */


    /* Specify data destination (eg, a file) */

    FILE* in_file;
    if ((in_file = fopen(in_filename, "rb")) == NULL) {
        fprintf(stderr, "can't open %s\n", in_filename);
        exit(EXIT_FAILURE);
    }
    jpeg_stdio_src(&cinfo, in_file);

    /* Read file parameters */

    (void)jpeg_read_header(&cinfo, TRUE);
    
    /* Set parameters for decompression */

    /* Start decompressor */

    (void)jpeg_start_decompress(&cinfo);

    JSAMPARRAY buffer;            /* Output row buffer */
    int row_stride;               /* physical row width in output buffer */

    row_stride = cinfo.output_width * cinfo.output_components;  /* JSAMPLEs per row in output buffer */
    buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, row_stride, 1);  /* One-row-high sample array that will go away when done with image */
    
    /* Deompress */

    result->width = cinfo.output_width;
    result->height = cinfo.output_height;
    result->components = cinfo.output_components;
    result->color_space = cinfo.out_color_space;
    result->buffer = (JSAMPLE*)malloc(
        sizeof(JSAMPLE) *
        cinfo.output_components *
        cinfo.output_width *
        cinfo.output_height
    );

    while (cinfo.output_scanline < cinfo.output_height) {
        (void)jpeg_read_scanlines(&cinfo, buffer, 1);
        memcpy(
            &(result->buffer)[(cinfo.output_scanline - 1) * row_stride],
            buffer[0],
            row_stride
        );
    }

    /* Finish compression */

    (void)jpeg_finish_decompress(&cinfo);
    fclose(in_file);

    /* Release JPEG compression object */

    jpeg_destroy_decompress(&cinfo);
   
    return result;
}
