#include "helpers.h"
#include <math.h>

void average(int h, int w, RGBTRIPLE image[h][w], RGBTRIPLE temp_image[h][w], int current_h,
             int current_w);
void sobel(int h, int w, RGBTRIPLE image[h][w], RGBTRIPLE temp_image[h][w], int current_h,
           int current_w, int Gx[3][3], int Gy[3][3]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float gray;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            gray =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtBlue = gray;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_image[width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_image[j] = image[i][j];
        }
        for (int k = width - 1, x = 0; x < width; x++, k--)
        {
            image[i][x] = temp_image[k];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a copy of original image
    RGBTRIPLE temp_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_image[i][j] = image[i][j];
        }
    }

    // blur the image pixel by pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average(height, width, image, temp_image, i, j);
        }
    }
    return;
}

void average(int h, int w, RGBTRIPLE image[h][w], RGBTRIPLE temp_image[h][w], int current_h,
             int current_w)
{
    float temp_Red = 0, temp_Green = 0, temp_Blue = 0;
    int box = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if ((current_h - 1 + i) < 0 || (current_h - 1 + i) > (h - 1) ||
                (current_w - 1 + j) < 0 || (current_w - 1 + j) > (w - 1))
            {
                continue;
            }
            temp_Red += temp_image[current_h - 1 + i][current_w - 1 + j].rgbtRed;
            temp_Green += temp_image[current_h - 1 + i][current_w - 1 + j].rgbtGreen;
            temp_Blue += temp_image[current_h - 1 + i][current_w - 1 + j].rgbtBlue;
            box++;
        }
    }
    image[current_h][current_w].rgbtRed = round(temp_Red / box);
    image[current_h][current_w].rgbtGreen = round(temp_Green / box);
    image[current_h][current_w].rgbtBlue = round(temp_Blue / box);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // create a copy of original image
    RGBTRIPLE temp_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_image[i][j] = image[i][j];
        }
    }

    // create convolutional matrix for applying sobel operator
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}},
        Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // detect edges pixel by pixel, i = current height, j = current width
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sobel(height, width, image, temp_image, i, j, Gx, Gy);
        }
    }
    return;
}

void sobel(int h, int w, RGBTRIPLE image[h][w], RGBTRIPLE temp_image[h][w], int current_h,
           int current_w, int Gx[3][3], int Gy[3][3])
{
    int Gx_Red = 0, Gy_Red = 0, Gx_Green = 0, Gy_Green = 0, Gx_Blue = 0, Gy_Blue = 0;

    // caculate each channel's Gx and Gy for the current pixel
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if ((current_h - 1 + i) < 0 || (current_h - 1 + i) > (h - 1) ||
                (current_w - 1 + j) < 0 || (current_w - 1 + j) > (w - 1))
            {
                continue;
            }
            Gx_Red += temp_image[current_h - 1 + i][current_w - 1 + j].rgbtRed * Gx[i][j];
            Gy_Red += temp_image[current_h - 1 + i][current_w - 1 + j].rgbtRed * Gy[i][j];
            Gx_Green += temp_image[current_h - 1 + i][current_w - 1 + j].rgbtGreen * Gx[i][j];
            Gy_Green += temp_image[current_h - 1 + i][current_w - 1 + j].rgbtGreen * Gy[i][j];
            Gx_Blue += temp_image[current_h - 1 + i][current_w - 1 + j].rgbtBlue * Gx[i][j];
            Gy_Blue += temp_image[current_h - 1 + i][current_w - 1 + j].rgbtBlue * Gy[i][j];
        }
    }

    /* G = round(square root of Gx^2 + Gy^2)
    and capped to 255 if >255 since a BYTE can only count to 255 */
    
    float G_Red = round(sqrtf(Gx_Red * Gx_Red + Gy_Red * Gy_Red));
    if (G_Red > 255)
        G_Red = 255;
    float G_Green = round(sqrtf(Gx_Green * Gx_Green + Gy_Green * Gy_Green));
    if (G_Green > 255)
        G_Green = 255;
    float G_Blue = round(sqrtf(Gx_Blue * Gx_Blue + Gy_Blue * Gy_Blue));
    if (G_Blue > 255)
        G_Blue = 255;
    image[current_h][current_w].rgbtRed = G_Red;
    image[current_h][current_w].rgbtGreen = G_Green;
    image[current_h][current_w].rgbtBlue = G_Blue;
}
