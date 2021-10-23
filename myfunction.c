
#include "stdlib.h"

#define min(A, B) (A < B ? A : B)
#define max(A, B) (A > B ? A : B)
#define multby9(X) (((X)<<3)+(X))
#define multbyminus1(X) ((X)*(-1))
#define Location_calculation(X, Y, Z) ((X*Y)+Z)
typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} pixel;

#define size (m*n*sizeof(pixel))

void Blur_image(Image *image) {
    pixel *pixelsImg = malloc(size);
    pixel *pointerToData = (pixel *) image->data;

    //copy data to pixel image
    memcpy(pixelsImg, pointerToData, size);

    int i, j;
    int m_minus2 = m - 2;
    int n_minus2 = n - 2;
    int placeInArry=0;
    int sumOfRed, sumOfGreen, sumOfBlue;
    pixel current_pixel;
    pixel *pixel1, *pixel2, *pixel3, *pixel4, *pixel5;
    pixel *pixel6, *pixel7, *pixel8, *pixel9;
    if (m % 2 == 0) {
        for (i = 1; i <= m_minus2; ++i) {
            //calc the first 9 pixel
            pixel1 = &pixelsImg[placeInArry];
            pixel2 = pixel1 + 1;
            pixel3 = pixel1 + 2;
            pixel4 = pixel1 + m;
            pixel5 = pixel4 + 1;
            pixel6 = pixel4 + 2;
            pixel7 = pixel4 + m;
            pixel8 = pixel7 + 1;
            pixel9 = pixel7 + 2;
            for (j = 1; j < n_minus2; j += 2) {
                //first pixel
                //calc sum of the pixel
                sumOfRed = pixel1->red + pixel2->red + pixel3->red + pixel4->red +
                           pixel5->red + pixel6->red + pixel7->red + pixel8->red + pixel9->red;
                sumOfGreen = pixel1->green + pixel2->green + pixel3->green + pixel4->green +
                             pixel5->green + pixel6->green + pixel7->green + pixel8->green + pixel9->green;
                sumOfBlue = pixel1->blue + pixel2->blue + pixel3->blue + pixel4->blue +
                            pixel5->blue + pixel6->blue + pixel7->blue + pixel8->blue + pixel9->blue;

                // divide by kernel's weight
                sumOfRed = sumOfRed / 9;
                sumOfGreen = sumOfGreen / 9;
                sumOfBlue = sumOfBlue / 9;


                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(sumOfRed, 0), 255));
                current_pixel.green = (unsigned char) (min(max(sumOfGreen, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(sumOfBlue, 0), 255));
                pointerToData[Location_calculation(i, n, j)] = current_pixel;

                //second pixel
                //moving to the next pixel
                pixel1 = pixel2;
                pixel2 = pixel3;
                ++pixel3;
                pixel4 = pixel5;
                pixel5 = pixel6;
                ++pixel6;
                pixel7 = pixel8;
                pixel8 = pixel9;
                ++pixel9;

                //calc sum of the pixel
                sumOfRed = pixel1->red + pixel2->red + pixel3->red + pixel4->red +
                           pixel5->red + pixel6->red + pixel7->red + pixel8->red + pixel9->red;
                sumOfGreen = pixel1->green + pixel2->green + pixel3->green + pixel4->green +
                             pixel5->green + pixel6->green + pixel7->green + pixel8->green + pixel9->green;
                sumOfBlue = pixel1->blue + pixel2->blue + pixel3->blue + pixel4->blue +
                            pixel5->blue + pixel6->blue + pixel7->blue + pixel8->blue + pixel9->blue;

                // divide by kernel's weight
                sumOfRed = sumOfRed / 9;
                sumOfGreen = sumOfGreen / 9;
                sumOfBlue = sumOfBlue / 9;


                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(sumOfRed, 0), 255));
                current_pixel.green = (unsigned char) (min(max(sumOfGreen, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(sumOfBlue, 0), 255));
                pointerToData[Location_calculation(i, n, j + 1)] = current_pixel;
                //moving to the next pixel
                pixel1 = pixel2;
                pixel2 = pixel3;
                ++pixel3;
                pixel4 = pixel5;
                pixel5 = pixel6;
                ++pixel6;
                pixel7 = pixel8;
                pixel8 = pixel9;
                ++pixel9;

            }
            placeInArry+=n;
        }
    } else {
        for (i = 1; i <= m_minus2; ++i) {
            pixel1 = &pixelsImg[placeInArry];
            pixel2 = pixel1 + 1;
            pixel3 = pixel1 + 2;
            pixel4 = pixel1 + m;
            pixel5 = pixel4 + 1;
            pixel6 = pixel4 + 2;
            pixel7 = pixel4 + m;
            pixel8 = pixel7 + 1;
            pixel9 = pixel7 + 2;
            for (j = 1; j <= n_minus2; ++j) {


                //calc sum of the pixel
                sumOfRed = pixel1->red + pixel2->red + pixel3->red + pixel4->red +
                           pixel5->red + pixel6->red + pixel7->red + pixel8->red + pixel9->red;
                sumOfGreen = pixel1->green + pixel2->green + pixel3->green + pixel4->green +
                             pixel5->green + pixel6->green + pixel7->green + pixel8->green + pixel9->green;
                sumOfBlue = pixel1->blue + pixel2->blue + pixel3->blue + pixel4->blue +
                            pixel5->blue + pixel6->blue + pixel7->blue + pixel8->blue + pixel9->blue;

                // divide by kernel's weight
                sumOfRed = sumOfRed / 9;
                sumOfGreen = sumOfGreen / 9;
                sumOfBlue = sumOfBlue / 9;


                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(sumOfRed, 0), 255));
                current_pixel.green = (unsigned char) (min(max(sumOfGreen, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(sumOfBlue, 0), 255));
                pointerToData[Location_calculation(i, n, j)] = current_pixel;
                //moving to the next pixel
                pixel1 = pixel2;
                pixel2 = pixel3;
                ++pixel3;
                pixel4 = pixel5;
                pixel5 = pixel6;
                ++pixel6;
                pixel7 = pixel8;
                pixel8 = pixel9;
                ++pixel9;

            }
        }
    }
    free(pixelsImg);
}

void sharpen_image(Image *image) {
    pixel *pixelsImg = malloc(size);
    pixel *pointerToData = (pixel *) image->data;

    //copy data to pixel image
    memcpy(pixelsImg, pointerToData, size);
    int i, j;
    int m_minus2 = m - 2;
    int n_minus2 = n - 2;
    int placeInArry=0;
    int sumOfRed, sumOfGreen, sumOfBlue;
    pixel current_pixel;
    pixel *pixel1, *pixel2, *pixel3, *pixel4, *pixel5;
    pixel *pixel6, *pixel7, *pixel8, *pixel9;

    if (m % 2 == 0) {
        for (i = 1; i <= m_minus2; ++i) {
            //find the first 9 pixel
            pixel1 = &pixelsImg[placeInArry];
            pixel2 = pixel1 + 1;
            pixel3 = pixel1 + 2;
            pixel4 = pixel1 + m;
            pixel5 = pixel4 + 1;
            pixel6 = pixel4 + 2;
            pixel7 = pixel4 + m;
            pixel8 = pixel7 + 1;
            pixel9 = pixel7 + 2;
            for (j = 1; j < n_minus2; j += 2) {
                //first pixel
                //calc sum of the pixel
                sumOfRed = multby9(pixel5->red) + multbyminus1(
                        pixel1->red + pixel2->red + pixel3->red + pixel4->red + pixel6->red + pixel7->red +
                        pixel8->red + pixel9->red);
                sumOfGreen = multby9(pixel5->green) + multbyminus1(
                        pixel1->green + pixel2->green + pixel3->green + pixel4->green + pixel6->green + pixel7->green +
                        pixel8->green + pixel9->green);
                sumOfBlue = multby9(pixel5->blue) + multbyminus1(
                        pixel1->blue + pixel2->blue + pixel3->blue + pixel4->blue + pixel6->blue + pixel7->blue +
                        pixel8->blue + pixel9->blue);



                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(sumOfRed, 0), 255));
                current_pixel.green = (unsigned char) (min(max(sumOfGreen, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(sumOfBlue, 0), 255));
                pointerToData[Location_calculation(i, n, j)] = current_pixel;

                //second pixel
                //moving to next pixel
                pixel1 = pixel2;
                pixel2 = pixel3;
                ++pixel3;
                pixel4 = pixel5;
                pixel5 = pixel6;
                ++pixel6;
                pixel7 = pixel8;
                pixel8 = pixel9;
                ++pixel9;


                //calc sum of the pixel
                sumOfRed = multby9(pixel5->red) + multbyminus1(
                        pixel1->red + pixel2->red + pixel3->red + pixel4->red + pixel6->red + pixel7->red +
                        pixel8->red + pixel9->red);
                sumOfGreen = multby9(pixel5->green) + multbyminus1(
                        pixel1->green + pixel2->green + pixel3->green + pixel4->green + pixel6->green + pixel7->green +
                        pixel8->green + pixel9->green);
                sumOfBlue = multby9(pixel5->blue) + multbyminus1(
                        pixel1->blue + pixel2->blue + pixel3->blue + pixel4->blue + pixel6->blue + pixel7->blue +
                        pixel8->blue + pixel9->blue);


                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(sumOfRed, 0), 255));
                current_pixel.green = (unsigned char) (min(max(sumOfGreen, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(sumOfBlue, 0), 255));
                pointerToData[Location_calculation(i, n, j + 1)] = current_pixel;
                //moving to next pixel
                pixel1 = pixel2;
                pixel2 = pixel3;
                ++pixel3;
                pixel4 = pixel5;
                pixel5 = pixel6;
                ++pixel6;
                pixel7 = pixel8;
                pixel8 = pixel9;
                ++pixel9;
            }
            placeInArry+=n;
        }

    } else {
        for (i = 1; i <= m_minus2; ++i) {
            //calc the first 9 pixel
            pixel1 = &pixelsImg[placeInArry];
            pixel2 = pixel1 + 1;
            pixel3 = pixel1 + 2;
            pixel4 = pixel1 + m;
            pixel5 = pixel4 + 1;
            pixel6 = pixel4 + 2;
            pixel7 = pixel4 + m;
            pixel8 = pixel7 + 1;
            pixel9 = pixel7 + 2;
            for (j = 1; j <= n_minus2; ++j) {
                //calc sum of the pixel
                sumOfRed = multby9(pixel5->red) + multbyminus1(
                        pixel1->red + pixel2->red + pixel3->red + pixel4->red + pixel6->red + pixel7->red +
                        pixel8->red + pixel9->red);
                sumOfGreen = multby9(pixel5->green) + multbyminus1(
                        pixel1->green + pixel2->green + pixel3->green + pixel4->green + pixel6->green + pixel7->green +
                        pixel8->green + pixel9->green);
                sumOfBlue = multby9(pixel5->blue) + multbyminus1(
                        pixel1->blue + pixel2->blue + pixel3->blue + pixel4->blue + pixel6->blue + pixel7->blue +
                        pixel8->blue + pixel9->blue);


                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(sumOfRed, 0), 255));
                current_pixel.green = (unsigned char) (min(max(sumOfGreen, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(sumOfBlue, 0), 255));
                pointerToData[Location_calculation(i, n, j)] = current_pixel;
                //moving to next pixel
                pixel1 = pixel2;
                pixel2 = pixel3;
                ++pixel3;
                pixel4 = pixel5;
                pixel5 = pixel6;
                ++pixel6;
                pixel7 = pixel8;
                pixel8 = pixel9;
                ++pixel9;
            }

            placeInArry+=n;
        }
    }
}

void blur_and_filter(Image *image) {
    pixel *pixelsImg = malloc(size);
    pixel *pointerToData = (pixel *) image->data;
    //copy data to pixel image
    memcpy(pixelsImg, pointerToData, size);

    int i, j;
    int m_minus2 = m - 2;
    int n_minus2 = n - 2;
    int placeInArry=0;
    int sumOfRed, sumOfGreen, sumOfBlue;
    pixel current_pixel;
    pixel *pixel1, *pixel2, *pixel3, *pixel4, *pixel5;
    pixel *pixel6, *pixel7, *pixel8, *pixel9;
    pixel *min_pixel;
    pixel *max_pixel;
    int min_intensity;
    int max_intensity;
    int sum;
    for (i = 1; i <= m_minus2; ++i) {
        pixel1 = &pixelsImg[placeInArry];
        pixel2 = pixel1 + 1;
        pixel3 = pixel1 + 2;
        pixel4 = pixel1 + m;
        pixel5 = pixel4 + 1;
        pixel6 = pixel4 + 2;
        pixel7 = pixel4 + m;
        pixel8 = pixel7 + 1;
        pixel9 = pixel7 + 2;
        for (j = 1; j <= n_minus2; ++j) {
            //find min and max pixel
            sum = pixel1->red + pixel1->green + pixel1->blue;
            min_intensity = sum;
            max_intensity = sum;
            min_pixel = pixel1;
            max_pixel = pixel1;


            sum = pixel2->red + pixel2->green + pixel2->blue;
            if (sum <= min_intensity) {
                min_intensity = sum;
                min_pixel = pixel2;
            } else if (sum > max_intensity) {
                max_intensity = sum;
                max_pixel = pixel2;
            }



            sum = pixel3->red + pixel3->green + pixel3->blue;
            if (sum <= min_intensity) {
                min_intensity = sum;
                min_pixel = pixel3;
            } else if (sum > max_intensity) {
                max_intensity = sum;
                max_pixel = pixel3;
            }



            sum = pixel4->red + pixel4->green + pixel4->blue;
            if (sum <= min_intensity) {
                min_intensity = sum;
                min_pixel = pixel4;
            } else if (sum > max_intensity) {
                max_intensity = sum;
                max_pixel = pixel4;
            }


            sum = pixel5->red + pixel5->green + pixel5->blue;
            if (sum <= min_intensity) {
                min_intensity = sum;
                min_pixel = pixel5;
            } else if (sum > max_intensity) {
                max_intensity = sum;
                max_pixel = pixel5;
            }


            sum = pixel6->red + pixel6->green + pixel6->blue;
            if (sum <= min_intensity) {
                min_intensity = sum;
                min_pixel = pixel6;
            } else if (sum > max_intensity) {
                max_intensity = sum;
                max_pixel = pixel6;
            }


            sum = pixel7->red + pixel7->green + pixel7->blue;
            if (sum <= min_intensity) {
                min_intensity = sum;
                min_pixel = pixel7;
            } else if (sum > max_intensity) {
                max_intensity = sum;
                max_pixel = pixel7;
            }


            sum = pixel8->red + pixel8->green + pixel8->blue;
            if (sum <= min_intensity) {
                min_intensity = sum;
                min_pixel = pixel8;
            } else if (sum > max_intensity) {
                max_intensity = sum;
                max_pixel = pixel8;
            }


            sum = pixel9->red + pixel9->green + pixel9->blue;
            if (sum <= min_intensity) {
                min_intensity = sum;
                min_pixel = pixel9;
            } else if (sum > max_intensity) {
                max_intensity = sum;
                max_pixel = pixel9;
            }


            //calc sum of the pixel
            sumOfRed = pixel1->red + pixel2->red + pixel3->red + pixel4->red +
                       pixel5->red + pixel6->red + pixel7->red + pixel8->red + pixel9->red - min_pixel->red -
                       max_pixel->red;
            sumOfGreen = pixel1->green + pixel2->green + pixel3->green + pixel4->green +
                         pixel5->green + pixel6->green + pixel7->green + pixel8->green + pixel9->green -
                         min_pixel->green - max_pixel->green;
            sumOfBlue = pixel1->blue + pixel2->blue + pixel3->blue + pixel4->blue +
                        pixel5->blue + pixel6->blue + pixel7->blue + pixel8->blue + pixel9->blue - min_pixel->blue -
                        max_pixel->blue;

            // divide by kernel's weight
            sumOfRed = sumOfRed / 7;
            sumOfGreen = sumOfGreen / 7;
            sumOfBlue = sumOfBlue / 7;


            // truncate each pixel's color values to match the range [0,255]
            current_pixel.red = (unsigned char) (min(max(sumOfRed, 0), 255));
            current_pixel.green = (unsigned char) (min(max(sumOfGreen, 0), 255));
            current_pixel.blue = (unsigned char) (min(max(sumOfBlue, 0), 255));
            pointerToData[Location_calculation(i, n, j)] = current_pixel;
            //moving to next pixel
            pixel1 = pixel2;
            pixel2 = pixel3;
            ++pixel3;
            pixel4 = pixel5;
            pixel5 = pixel6;
            ++pixel6;
            pixel7 = pixel8;
            pixel8 = pixel9;
            ++pixel9;
        }
        placeInArry+=n;
    }

}


void myfunction(Image *image, char *srcImgpName, char *blurRsltImgName, char *sharpRsltImgName,
                char *filteredBlurRsltImgName, char *filteredSharpRsltImgName, char flag) {

    if (flag == '1') {
        // blur image
        Blur_image(image);

        // write result image to file
        writeBMP(image, srcImgpName, blurRsltImgName);

        // sharpen the resulting image
        sharpen_image(image);

        // write result image to file
        writeBMP(image, srcImgpName, sharpRsltImgName);

    } else {

        // apply extermum filtered kernel to blur image
        blur_and_filter(image);

        // write result image to file
        writeBMP(image, srcImgpName, filteredBlurRsltImgName);

        // sharpen the resulting image
        sharpen_image(image);

        // write result image to file
        writeBMP(image, srcImgpName, filteredSharpRsltImgName);

    }
}
