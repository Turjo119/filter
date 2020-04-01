#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // For each row
    for (int i = 0; i < height; i++)
    {
        // For each pixel
        for (int j = 0; j < width; j++)
        {
            // Find average of three RGB values
            float avg = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            // Round avg to nearest integer and set it for each pixel

            image[i][j].rgbtRed = round (avg);
            image[i][j].rgbtGreen = round (avg);
            image[i][j].rgbtBlue = round (avg);

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    // For each row
    for (int i = 0; i < height; i++)
    {
        // For each pixel
        for (int j = 0; j < width; j++)
        {
            // Calculate Sepia values
            float sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;

            float sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;

            float sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            // Place sepia values
            if (sepiaRed <= 255)
            {
                image[i][j].rgbtRed = round (sepiaRed);
            }

            else
            {
                image[i][j].rgbtRed = 255;
            }

            if (sepiaGreen <= 255)
            {
                image[i][j].rgbtGreen = round (sepiaGreen);
            }

            else
            {
               image[i][j].rgbtGreen = 255;
            }

            if (sepiaBlue <= 255)
            {
                image[i][j].rgbtBlue = round (sepiaBlue);
            }

            else
            {
                image[i][j].rgbtBlue = 255;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    // For each row
    for (int i = 0; i < height; i++)
    {
        // For each pixel
        for (int j = 0; j < width / 2; j++)
        {
            // Temporary variables
            float temp0 = 0;
            float temp1 = 0;
            float temp2 = 0;

            // For red
            temp0 = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][(width - 1) - j].rgbtRed;
            image[i][(width - 1) - j].rgbtRed = temp0;

            // For green
            temp1 = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][(width - 1) - j].rgbtGreen;
            image[i][(width - 1) - j].rgbtGreen = temp1;

            // For blue
            temp2 = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][(width - 1) - j].rgbtBlue;
            image[i][(width - 1) - j].rgbtBlue = temp2;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create copy of original image
    RGBTRIPLE copy[height][width];
    // Copy each pixel to copy
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            copy[x][y].rgbtRed = image[x][y].rgbtRed;
            copy[x][y].rgbtGreen = image[x][y].rgbtGreen;
            copy[x][y].rgbtBlue = image[x][y].rgbtBlue;
        }
    }

    // Caculate the RGB values
    float sumRed = 0;
    float sumGreen = 0;
    float sumBlue = 0;

        // For each row
    for (int i = 0; i < height; i++)
    {
        // For each pixel
        for (int j = 0; j < width; j++)
        {
            // For 3x3 cases, skip first and last row
            if ((i == !0) || (i== !(height - 1)))
            {
                // Skip left and right column
                if ((j == !0) || (j == !(width - 1)))
                    {
                        for (int k = i - 1; k < i + 2; k++ )
                            {
                                for (int l = j - 1; l < j + 2; l++ )
                                    {
                                        sumRed = sumRed + copy[k][l].rgbtRed;
                                        sumGreen = sumGreen+ copy[k][l].rgbtGreen;
                                        sumBlue = sumBlue + copy[k][l].rgbtBlue;
                                    }
                            }
                    image[i][j].rgbtRed = round (sumRed / 9.0);
                    image[i][j].rgbtGreen = round (sumGreen / 9.0);
                    image[i][j].rgbtBlue = round (sumBlue / 9.0);
                }
            }

            // Else for corner cases
            else if (i == 0)
            {
                // For top left corner and right corner
                if (j == 0)
                {
                    sumRed = copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed;
                    sumGreen = copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen;
                    sumBlue = copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue;
                }
                else if ( j == width - 1)
                {
                    sumRed = copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed;
                    sumGreen = copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen;
                    sumBlue = copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue;
                }

                    image[i][j].rgbtRed = round (sumRed / 4.0);
                    image[i][j].rgbtGreen = round (sumGreen / 4.0);
                    image[i][j].rgbtBlue = round (sumBlue / 4.0);
            }

            // For corner cases
            else if (i == height - 1)
            {
               // For bottom left corner and right corner
                if (j == 0)
                {
                    sumRed = copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed;
                    sumGreen = copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen;
                    sumBlue = copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue;
                }
                else if ( j == width - 1)
                {
                    sumRed = copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed;
                    sumGreen = copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen;
                    sumBlue = copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue;
                }

                    image[i][j].rgbtRed = round (sumRed / 4.0);
                    image[i][j].rgbtGreen = round (sumGreen / 4.0);
                    image[i][j].rgbtBlue = round (sumBlue / 4.0);
            }

                }
            }

        }




    return;
}
