#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            if (sepiaRed > 255) sepiaRed = 255;
            if (sepiaGreen > 255) sepiaGreen = 255;
            if (sepiaBlue > 255) sepiaBlue = 255;

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width / 2; ++j)
        {
            RGBTRIPLE   tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buf[height][width];
	
	for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int pixels = 0;

			int	boxRow[3] = {i - 1, i, i + 1};
			int	boxCol[3] = {j - 1, j, j + 1};

			for (int r = 0; r < 3; ++r)
			{
				for (int c = 0; c < 3; ++c)
				{
					int curRow = boxRow[r];
					int curCol = boxCol[c];
					if (curRow >=0 && curCol >= 0 && curRow < height && curCol < width)
					{
						sumRed += image[curRow][curCol].rgbtRed;
						sumGreen += image[curRow][curCol].rgbtGreen;
						sumBlue += image[curRow][curCol].rgbtBlue;
						++pixels;
					}
				}
			}
			buf[i][j].rgbtRed = round((float) sumRed / pixels);
            buf[i][j].rgbtGreen = round((float) sumGreen / pixels);
            buf[i][j].rgbtBlue = round((float) sumBlue / pixels);
        }
    }

	for (int i = 0; i < height; ++i)
    {
    for (int j = 0; j < width; ++j)
        {
            image[i][j] = buf[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buf[height][width];
	
	int	Gx[3][3] =
	{
		{-1, 0, 1},
		{-2, 0, 1},
		{-1, 0, 1}
	};

	int	Gy[3][3] =
	{
		{-1, -2, -1},
		{ 0,  0,  0},
		{ 1,  2,  1}
	};

	for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
			float GxRed = 0, GxGreen = 0, GxBlue = 0;
         	float GyRed = 0, GyGreen = 0, GyBlue = 0;

			int	boxRow[3] = {i - 1, i, i + 1};
			int	boxCol[3] = {j - 1, j, j + 1};

			for (int r = 0; r < 3; ++r)
			{
				for (int c = 0; c < 3; ++c)
				{
					int curRow = boxRow[r];
					int curCol = boxCol[c];

					if (curRow >=0 && curCol >= 0 && curRow < height && curCol < width)
					{
						GxRed += Gx[r][c] * image[curRow][curCol].rgbtRed;
						GxGreen += Gx[r][c] * image[curRow][curCol].rgbtGreen;
						GxBlue += Gx[r][c] * image[curRow][curCol].rgbtBlue;

						GyRed += Gy[r][c] * image[curRow][curCol].rgbtRed;
						GyGreen += Gy[r][c] * image[curRow][curCol].rgbtGreen;
						GyBlue += Gy[r][c] * image[curRow][curCol].rgbtBlue;
					
					}
				}
			}
			int resRed = round(sqrt(GxRed * GxRed + GyRed * GyRed));
            int resGreen = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
            int resBlue = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));

            buf[i][j].rgbtRed = resRed > 255 ? 255 : resRed;
            buf[i][j].rgbtGreen = resGreen > 255 ? 255 : resGreen;
            buf[i][j].rgbtBlue = resBlue > 255 ? 255 : resBlue;
        }
    }

	for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            image[i][j] = buf[i][j];
        }
    }
}
