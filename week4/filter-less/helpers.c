#include "helpers.h"
#include <math.h>

void average(int h, int w, RGBTRIPLE image[h][w], RGBTRIPLE temp_image[h][w], int current_h,
             int current_w);

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                             .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                               .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                              .131 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
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
    RGBTRIPLE temp_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_image[i][j] = image[i][j];
        }
    }
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
