iftFImage *IntegralImage(iftImage *img);
float IntegralValue(iftFImage *int_img, iftVoxel center, int width, int height,
        float weight);
iftFImage *FeatureExtraction1(iftImage *img);
iftFImage *FeatureExtraction2(iftFImage *int_img);
void AppendFeatures(iftMImage **mimg, iftFImage *feat);

/* Create iftVoxel */

iftVoxel iftVoxelCreate(int x, int y, int z) {
	iftVoxel voxel;
	voxel.x = x;
	voxel.y = y;
	voxel.z = z;
	return voxel;
}

/* Set iftVoxel values */

void iftVoxelSetValues(iftVoxel * voxel, int x, int y, int z) {
	voxel->x = x;
	voxel->y = y;
	voxel->z = z;
}

/* Get index from image */

int iftImageGetIndex(int x, int y, int z, iftImage * img) {
	return iftGetVoxelIndex(img, iftVoxelCreate(x, y, z));
}

int iftFImageGetIndex(int x, int y, int z, iftFImage * img) {
	return iftGetVoxelIndex(img, iftVoxelCreate(x, y, z));
}

/* Get pixel value from image */

int iftImageGetPixelValue(int x, int y, int z, iftImage * img) {
	return img->val[iftImageGetIndex(x, y, z, img)];
}

double iftFImageGetPixelValue(int x, int y, int z, iftFImage* img) {
	return img->val[iftFImageGetIndex(x, y, z, img)];
}

/* Set pixel value from image */

void iftImageSetPixelValue(int value, int x, int y, int z, iftImage * img) {
	img->val[iftImageGetIndex(x, y, z, img)] = value;
}

void iftFImageSetPixelValue(double value, int x, int y, int z, iftFImage * img) {
	img->val[iftFImageGetIndex(x, y, z, img)] = value;
}

/* Extract edge features from an image */

iftFImage *FeatureExtractionEdge(iftFImage *int_img, int direction, int size) {
	iftFImage *feat = iftCreateFImage(int_img->xsize, int_img->ysize,
	        int_img->zsize);
	iftVoxel first_region_center, second_region_center;
	double featureValue;

	for (int z = 0; z < int_img->zsize; z++) {
		for (int y = 0; y < int_img->ysize; y++) {
			for (int x = 0; x < int_img->xsize; x++) {
				if (direction == 0) {
					// Apply horizontal filter.
					iftVoxelSetValues(&first_region_center, x + size / 2,
					        y + size / 2, z);
					iftVoxelSetValues(&second_region_center, x + size / 2,
					        y + 3 * size / 2, z);

				} else {
					// Apply vertical filter.
					iftVoxelSetValues(&first_region_center, x + size / 2,
					        y + size / 2, z);
					iftVoxelSetValues(&second_region_center, x + 3 * size / 2,
					        y + size / 2, z);
				}

				featureValue = IntegralValue(int_img, first_region_center, size,
				        size, 1)
				        + IntegralValue(int_img, second_region_center, size,
				                size, -1);

				iftFImageSetPixelValue(featureValue, x, y, z, feat);
			}
		}
	}

	return (feat);
}

iftFImage *FeatureExtractionLine(iftFImage *int_img, int direction, int size) {
	iftFImage *feat = iftCreateFImage(int_img->xsize, int_img->ysize,
	        int_img->zsize);
	iftVoxel first_region_center, second_region_center, third_region_center;
	double featureValue;

	for (int z = 0; z < int_img->zsize; z++) {
		for (int y = 0; y < int_img->ysize; y++) {
			for (int x = 0; x < int_img->xsize; x++) {
				if (direction == 0) {
					// Apply horizontal filter.
					iftVoxelSetValues(&first_region_center, x + size / 2,
					        y + size / 4, z);
					iftVoxelSetValues(&second_region_center, x + size / 2,
					        y + size, z);
					iftVoxelSetValues(&third_region_center, x + size / 2,
					        y + 7 * size / 4, z);

					featureValue = IntegralValue(int_img, first_region_center,
					        size, size / 2, 1)
					        + IntegralValue(int_img, second_region_center, size,
					                size, -1)
					        + IntegralValue(int_img, third_region_center, size,
					                size / 2, 1);
				} else {
					// Apply vertical filter.
					iftVoxelSetValues(&first_region_center, x + size / 4,
					        y + size / 2, z);
					iftVoxelSetValues(&second_region_center, x + size,
					        y + size / 2, z);
					iftVoxelSetValues(&third_region_center, x + 7 * size / 4,
					        y + size / 2, z);

					featureValue = IntegralValue(int_img, first_region_center,
					        size / 2, size, 1)
					        + IntegralValue(int_img, second_region_center, size,
					                size, -1)
					        + IntegralValue(int_img, third_region_center,
					                size / 2, size, 1);
				}

				iftFImageSetPixelValue(featureValue, x, y, z, feat);
			}
		}
	}

	return (feat);
}

iftFImage *FeatureExtractionCenterSurround(iftFImage *int_img, int size) {
	iftFImage *feat = iftCreateFImage(int_img->xsize, int_img->ysize,
	        int_img->zsize);
	iftVoxel center;
	double featureValue;

	for (int z = 0; z < int_img->zsize; z++) {
		for (int y = 0; y < int_img->ysize; y++) {
			for (int x = 0; x < int_img->xsize; x++) {
				// Apply horizontal filter.
				iftVoxelSetValues(&center, x + size / 2, y + size / 2, z);

				featureValue = IntegralValue(int_img, center, size, size, 1)
				        + IntegralValue(int_img, center, size / 2, size / 2,
				                -2);

				iftFImageSetPixelValue(featureValue, x, y, z, feat);
			}
		}
	}

	return (feat);
}

/* Compute the integral image of an input image */

iftFImage *IntegralImage(iftImage *img) {
	iftFImage *int_img = iftCreateFImage(img->xsize, img->ysize, img->zsize);

	// Compute integral image.
	double integralValue = 0;
	for (int z = 0; z < img->zsize; z++) {
		for (int y = 0; y < img->ysize; y++) {
			for (int x = 0; x < img->xsize; x++) {
				if (x == 0 || y == 0) {
					if (x == 0) {
						if (y == 0) {
							// x = 0  and y = 0
							integralValue = iftImageGetPixelValue(x, y, z, img);
						} else {
							// x = 0 and y != 0
							integralValue = iftImageGetPixelValue(x, y, z, img)
							        + iftFImageGetPixelValue(x, y - 1, z,
							                int_img);
						}
					} else {
						// x != 0  and y = 0
						integralValue = iftImageGetPixelValue(x, y, z, img)
						        + iftFImageGetPixelValue(x - 1, y, z, int_img);
					}
				} else {
					// x != 0  and y != 0
					integralValue = iftImageGetPixelValue(x, y, z, img)
					        + iftFImageGetPixelValue(x - 1, y, z, int_img)
					        + iftFImageGetPixelValue(x, y - 1, z, int_img)
					        - iftFImageGetPixelValue(x - 1, y - 1, z, int_img);
				}

				iftFImageSetPixelValue(integralValue, x, y, z, int_img);
			}
		}
	}

	return int_img;
}

/* Compute the integral value inside a region of width x height pixels
 around a center, and return its multiplication by a weight */

float IntegralValue(iftFImage *int_img, iftVoxel center, int width, int height,
        float weight) {
	// Get region limits for references.
	int limit_x_inferior = center.x - width / 2;
	int limit_y_inferior = center.y - height / 2;
	int limit_x_superior = center.x + width / 2;
	int limit_y_superior = center.y + height / 2;

	// Fix references to image limits.
	if (limit_x_inferior < 0) {
		limit_x_inferior = 0;
	}

	if (limit_y_inferior < 0) {
		limit_y_inferior = 0;
	}

	if (limit_x_inferior >= int_img->xsize) {
		limit_x_inferior = int_img->xsize - 1;
	}

	if (limit_y_inferior >= int_img->ysize) {
		limit_y_inferior = int_img->ysize - 1;
	}

	if (limit_x_superior < 0) {
		limit_x_superior = 0;
	}

	if (limit_y_superior < 0) {
		limit_y_superior = 0;
	}

	if (limit_x_superior >= int_img->xsize) {
		limit_x_superior = int_img->xsize - 1;
	}

	if (limit_y_superior >= int_img->ysize) {
		limit_y_superior = int_img->ysize - 1;
	}

	// Compute integral value.
	/*
	 * A  _____  B
	 *   |     |
	 *   |_____|
	 * C         D
	 *
	 * int_value = D -B -C +A
	 */
	float int_value = iftFImageGetPixelValue(limit_x_superior, limit_y_superior,
	        center.z, int_img)
	        - iftFImageGetPixelValue(limit_x_superior, limit_y_inferior,
	                center.z, int_img)
	        - iftFImageGetPixelValue(limit_x_inferior, limit_y_superior,
	                center.z, int_img)
	        + iftFImageGetPixelValue(limit_x_inferior, limit_y_inferior,
	                center.z, int_img);

	int_value = int_value * weight;

	return (int_value);
}

/* Normalize and save features extracted. */
void iftWriteFImageP5(iftFImage *img, const char *filename) {
	iftImage *featConverted = iftCreateImage(img->xsize, img->ysize,
	        img->zsize);
	float max_value = iftFMaximumValue(img);
	float min_value = iftFMinimumValue(img);
	float range_value = max_value - min_value;
	float normalize_value;

	for (int z = 0; z < img->zsize; z++) {
		for (int y = 0; y < img->ysize; y++) {
			for (int x = 0; x < img->xsize; x++) {
				normalize_value = (iftFImageGetPixelValue(x, y, z, img)
				        - min_value) / range_value;
				iftImageSetPixelValue(normalize_value * 255, x, y, z,
				        featConverted);
			}
		}
	}

	iftWriteImageP5(featConverted, filename);
}

/* Extract features from an image according to a given descriptor */

iftFImage *FeatureExtraction1(iftImage *img) {
	// Compute integral image.
	iftFImage *int_img = IntegralImage(img);
	int size = 9; // Filter size.

//	// Write feature.
//	iftFImage *feat = FeatureExtractionEdge(int_img, 0, size);
//	iftWriteFImageP5(feat, "./edge_horizontal.pgm");
//	feat = FeatureExtractionEdge(int_img, 1, size);
//	iftWriteFImageP5(feat, "./edge_vertical.pgm");
//	feat = FeatureExtractionLine(int_img, 0, size);
//	iftWriteFImageP5(feat, "./line_horizontal.pgm");
//	feat = FeatureExtractionLine(int_img, 1, size);
//	iftWriteFImageP5(feat, "./line_vertical.pgm");
//	feat = FeatureExtractionCenterSurround(int_img, size);
//	iftWriteFImageP5(feat, "./center_surround.pgm");
//	exit(0);

//	iftFImage *feat = FeatureExtractionEdge(int_img, 0, size);
//	iftFImage *feat = FeatureExtractionEdge(int_img, 1, size);
//	iftFImage *feat = FeatureExtractionLine(int_img, 0, size);
//	iftFImage *feat = FeatureExtractionLine(int_img, 1, size);
	iftFImage *feat = FeatureExtractionCenterSurround(int_img, size);

	return (feat);
}

/* Extract features from an integral image according to a given
 descriptor */

iftFImage *FeatureExtraction2(iftFImage *int_img) {
	int size = 5; // Filter size.

//	iftFImage *feat = FeatureExtractionEdge(int_img, 0, size);
//	iftFImage *feat = FeatureExtractionEdge(int_img, 1, size);
//	iftFImage *feat = FeatureExtractionLine(int_img, 0, size);
//	iftFImage *feat = FeatureExtractionLine(int_img, 1, size);
	iftFImage *feat = FeatureExtractionCenterSurround(int_img, size);

	return (feat);
}

/* Append feature as a new band in the multiband feature image */

void AppendFeatures(iftMImage **mimg, iftFImage *feat) {
	if (*mimg == NULL) {
		*mimg = iftCreateMImage(feat->xsize, feat->ysize, feat->zsize, 1);
		for (int p = 0; p < (*mimg)->n; p++)
			(*mimg)->band[0].val[p] = feat->val[p];
	} else {
		iftMImage *aux = iftCreateMImage((*mimg)->xsize, (*mimg)->ysize,
		        (*mimg)->zsize, (*mimg)->m + 1);
		for (int p = 0; p < (*mimg)->n; p++) {
			for (int b = 0; b < (*mimg)->m; b++) {
				aux->band[b].val[p] = (*mimg)->band[b].val[p];
			}
			aux->band[(*mimg)->m].val[p] = feat->val[p];
		}
		iftDestroyMImage(mimg);
		(*mimg) = aux;
	}
}

