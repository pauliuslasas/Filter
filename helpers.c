#include "helpers.h"
#include <math.h>



// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            float gray = image[i][k].rgbtBlue + image[i][k].rgbtRed + image[i][k].rgbtGreen;
            gray = round(gray / 3);

            image[i][k].rgbtRed = gray;
            image[i][k].rgbtGreen = gray;
            image[i][k].rgbtBlue = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            float sepiaRed = round(0.393 * image[i][k].rgbtRed + 0.769 * image[i][k].rgbtGreen + 0.189 * image[i][k].rgbtBlue);
            float sepiaGreen = round(0.349 * image[i][k].rgbtRed + 0.686 * image[i][k].rgbtGreen + 0.168 * image[i][k].rgbtBlue);
            float sepiaBlue = round(0.272 * image[i][k].rgbtRed + 0.534 * image[i][k].rgbtGreen + 0.131 * image[i][k].rgbtBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][k].rgbtRed = sepiaRed;
            image[i][k].rgbtGreen = sepiaGreen;
            image[i][k].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    int swap[3];

    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width / 2; k++)
        {

            swap[0] = image[i][k].rgbtRed;
            swap[1] = image[i][k].rgbtGreen;
            swap[2] = image[i][k].rgbtBlue;


            image[i][k].rgbtRed = image[i][width - k - 1].rgbtRed;
            image[i][k].rgbtGreen = image[i][width - k - 1].rgbtGreen;
            image[i][k].rgbtBlue = image[i][width - k - 1].rgbtBlue;

            image[i][width - k - 1].rgbtRed = swap[0];
            image[i][width - k - 1].rgbtGreen = swap[1];
            image[i][width - k - 1].rgbtBlue = swap[2];

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{


    RGBTRIPLE copy[height][width];




    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            int red = 0;
            int green = 0;
            int blue = 0;
            float count = 0;

            for (int m = -1; m < 2; m++)
            {
                for (int n = -1; n < 2; n++)
                {
                    if (i + m < 0 || i + m > height - 1 || k + n < 0 || k + n > width - 1)
                    {
                        continue;
                    }

                    red += image[i + m][k + n].rgbtRed;
                    green += image[i + m][k + n].rgbtGreen;
                    blue += image[i + m][k + n].rgbtBlue;
                    count++;
                }
            }

            copy[i][k].rgbtRed = round(red / count);
            copy[i][k].rgbtGreen = round(green / count);
            copy[i][k].rgbtBlue = round(blue / count);

        }
    }



    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            image[i][k].rgbtRed = copy[i][k].rgbtRed;
            image[i][k].rgbtGreen = copy[i][k].rgbtGreen;
            image[i][k].rgbtBlue = copy[i][k].rgbtBlue;
        }
    }
    return;
}
