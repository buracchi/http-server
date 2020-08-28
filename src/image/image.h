#pragma once

typedef enum {
	JPEG
} FORMAT;

int print_image();

void set_quality_factor(float factor);

void convert_to_format(FORMAT format);

void resisze(unsigned width, unsigned height);

void scale(float factor);

void posterize(unsigned color);
