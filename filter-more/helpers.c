#include <math.h>
#include "helpers.h"

const int Gx[3][3] = {
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
};

const int Gy[3][3] = {
    {-1, -2, -1},
    {0, 0, 0},
    {1, 2, 1}
};

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0f);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurredImage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avgRed = 0;
            int avgGreen = 0;
            int avgBlue = 0;
            int pixelCount = 0;

            for (int k = i - 1; k < (i - 1) + 3; k++)
            {
                for (int l = j - 1; l < (j - 1) + 3; l++)
                {
                    if (k < 0 || k > height - 1)
                    {
                        continue;
                    }
                    if (l < 0 || l > width - 1)
                    {
                        continue;
                    }

                    avgRed += image[k][l].rgbtRed;
                    avgGreen += image[k][l].rgbtGreen;
                    avgBlue += image[k][l].rgbtBlue;
                    pixelCount++;
                }
            }

            blurredImage[i][j].rgbtRed = round(avgRed / (float) pixelCount);
            blurredImage[i][j].rgbtGreen = round(avgGreen / (float) pixelCount);
            blurredImage[i][j].rgbtBlue = round(avgBlue / (float) pixelCount);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blurredImage[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE sobelImage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Gx_red = 0, Gx_green = 0, Gx_blue = 0;
            int Gy_red = 0, Gy_green = 0, Gy_blue = 0;

            for (int k = i - 1, kernelRow = 0; k < (i - 1) + 3; k++, kernelRow++)
            {
                for (int l = j - 1, kernelColumn = 0; l < (j - 1) + 3; l++, kernelColumn++)
                {
                    if (k < 0 || k > height - 1)
                    {
                        continue;
                    }
                    if (l < 0 || l > width - 1)
                    {
                        continue;
                    }

                    Gx_red += image[k][l].rgbtRed * Gx[kernelRow][kernelColumn];
                    Gx_green += image[k][l].rgbtGreen * Gx[kernelRow][kernelColumn];
                    Gx_blue += image[k][l].rgbtBlue * Gx[kernelRow][kernelColumn];

                    Gy_red += image[k][l].rgbtRed * Gy[kernelRow][kernelColumn];
                    Gy_green += image[k][l].rgbtGreen * Gy[kernelRow][kernelColumn];
                    Gy_blue += image[k][l].rgbtBlue * Gy[kernelRow][kernelColumn];
                }
            }

            int sobelRed = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            if (sobelRed > 255)
            {
                sobelRed = 255;
            }
            int sobelGreen = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            if (sobelGreen > 255)
            {
                sobelGreen = 255;
            }
            int sobelBlue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));
            if (sobelBlue > 255)
            {
                sobelBlue = 255;
            }

            sobelImage[i][j].rgbtRed = sobelRed;
            sobelImage[i][j].rgbtGreen = sobelGreen;
            sobelImage[i][j].rgbtBlue = sobelBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = sobelImage[i][j];
        }
    }
    return;
}
