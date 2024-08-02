/* 
 *  Name: [Ken DENG]
 *  UID: [205452321]
 */

#include <stdlib.h>
#include <omp.h>

#include "utils.h"
#include "parallel.h"



/*
 *  PHASE 1: compute the mean pixel value
 *  This code is buggy! Find the bug and speed it up.
 */
void mean_pixel_parallel(const uint8_t img[][NUM_CHANNELS], int num_rows, int num_cols, double mean[NUM_CHANNELS]) {
    int row, col;
    long count = 0;

    double mean_0 = 0;
    double mean_1 = 0;
    double mean_2 = 0;

    #pragma omp parallel for reduction(+:count, mean_0, mean_1, mean_2)
    for (row = 0; row < num_rows; row++)
    {
        size_t rowTimesNumcol = row*num_cols;
        for (col = 0; col < num_cols; col++)
        {
            size_t rowTimesNumcolAddCol = rowTimesNumcol + col;
            mean_0 += img[rowTimesNumcolAddCol][0];
            mean_1 += img[rowTimesNumcolAddCol][1];
            mean_2 += img[rowTimesNumcolAddCol][2];
            count += 1;
        }
    }

    mean[0] = mean_0;
    mean[1] = mean_1;
    mean[2] = mean_2;

    mean[0] /= count;
    mean[1] /= count;
    mean[2] /= count;
}



/*
 *  PHASE 2: convert image to grayscale and record the max grayscale value along with the number of times it appears
 *  This code is NOT buggy, just sequential. Speed it up.
 */
void grayscale_parallel(const uint8_t img[][NUM_CHANNELS], int num_rows, int num_cols, uint32_t grayscale_img[][NUM_CHANNELS], uint8_t *max_gray, uint32_t *max_count) {
    int row, col;
    *max_gray = 0;
    *max_count = 0;
    uint8_t local_max_gray = 0;

    #pragma omp parallel for private(row, col) reduction(max:local_max_gray)
    for (row = 0; row < num_rows; row++)
    {
        size_t rowTimesNumcol = row*num_cols;

        for (col = 0; col < num_cols; col++) 
        {
            size_t rowTimesNumcolAddCol = rowTimesNumcol + col;
            uint32_t grayscaleImg = 0;
            //grayscale_img[rowTimesNumcolAddCol][0/1/2]
            grayscaleImg += img[rowTimesNumcolAddCol][0];
            grayscaleImg += img[rowTimesNumcolAddCol][1];
            grayscaleImg += img[rowTimesNumcolAddCol][2];
            grayscaleImg /= NUM_CHANNELS;

            grayscale_img[rowTimesNumcolAddCol][0] = grayscaleImg;
            grayscale_img[rowTimesNumcolAddCol][1] = grayscaleImg;
            grayscale_img[rowTimesNumcolAddCol][2] = grayscaleImg;
            /////////////////////////////////////////////////////////////
            //*max_gray
            if (grayscaleImg > local_max_gray)
            {
                local_max_gray = (uint8_t)grayscaleImg;
            }
        }
    }

    uint32_t count = 0;
    // Count occurrences of the maximum value
    #pragma omp parallel for collapse(2) reduction(+:count)
    for (row = 0; row < num_rows; row++)
    {
        for (col = 0; col < num_cols; col++)
        {
            if (grayscale_img[row*num_cols + col][0] == local_max_gray) 
            {
            count += 3;
            }
        }  
    }

    *max_count = count;
    *max_gray = local_max_gray;
}



/*
 *  PHASE 3: perform convolution on image
 *  This code is NOT buggy, just sequential. Speed it up.
 */
void convolution_parallel(const uint8_t padded_img[][NUM_CHANNELS], int num_rows, int num_cols, const uint32_t kernel[], int kernel_size, uint32_t convolved_img[][NUM_CHANNELS]) {
    int row, col, kernel_row, kernel_col;
    int kernel_norm, i;
    int conv_rows, conv_cols;

    // compute kernel normalization factor
    int kernalSizeSquared = kernel_size*kernel_size;
    kernel_norm = 0;
    #pragma omp parallel for reduction(+:kernel_norm)
    for(i = 0; i < kernalSizeSquared; i++) {
        kernel_norm += kernel[i];
    }

    // compute dimensions of convolved image
    conv_rows = num_rows - kernel_size + 1;
    conv_cols = num_cols - kernel_size + 1;

    // perform convolution
    #pragma omp parallel for private(row, col, kernel_col, kernel_row)
    for (row = 0; row < conv_rows; row++) 
    {
        size_t rowTimesConvcol = row*conv_cols;
        for (col = 0; col < conv_cols; col++) 
        {
            size_t rowTimesConvcolAddCol = rowTimesConvcol + col;

            uint32_t convolved_img0 = 0;
            uint32_t convolved_img1 = 0;
            uint32_t convolved_img2 = 0;

            for (kernel_col = 0; kernel_col < kernel_size; kernel_col++) 
            {
                for (kernel_row = 0; kernel_row < kernel_size; kernel_row++) 
                {
                    size_t idxPadding = (row+kernel_row)*num_cols + col+kernel_col;
                    size_t idxKernel = kernel_row*kernel_size + kernel_col;

                    convolved_img0 += padded_img[idxPadding][0] * kernel[idxKernel];
                    convolved_img1 += padded_img[idxPadding][1] * kernel[idxKernel];
                    convolved_img2 += padded_img[idxPadding][2] * kernel[idxKernel];
                }
            }
            
            convolved_img[rowTimesConvcolAddCol][0] = convolved_img0 / kernel_norm;
            convolved_img[rowTimesConvcolAddCol][1] = convolved_img1 / kernel_norm;
            convolved_img[rowTimesConvcolAddCol][2] = convolved_img2 / kernel_norm;
        }
    }
}