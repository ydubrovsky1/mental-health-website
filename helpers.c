#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double average = round((image[i][j].rgbtRed +  image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
        
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
     for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double red = round(image[i][j].rgbtRed * .393 + image[i][j].rgbtGreen * .769 + image[i][j].rgbtBlue *.189);
            if (red > 255)
            {
                red = 255;
            }
            
            double green = round(image[i][j].rgbtRed * .349 + image[i][j].rgbtGreen * .686 + image[i][j].rgbtBlue *.168);
            if (green > 255)
            {
                green = 255;
            }
            
            double blue = round(image[i][j].rgbtRed * .272 + image[i][j].rgbtGreen * .534 + image[i][j].rgbtBlue *.131);
            if (blue > 255)
            {
                blue = 255;
            }
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE flipped[height][width];
    for(int i = 0; i < height; i++)
    {
            for (int j = 0; j < width; j++)
            {
                flipped[i][j] = image[i][width - 1 - j];
            }
            for (int j = 0; j < width; j++)
            {
                image[i][j] = flipped[i][j];
            }
        
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurred[height][width];
    //blur all the middle pixels
    for(int i = 1; i < (height - 1); i++)
    {
            for (int j = 1; j < (width - 1); j++)
            {
                double red = 0; 
                double green = 0;
                double blue = 0;
                for (int a = -1; a < 2; a++)
                {
                    for (int b = -1; b < 2; b++)
                    {
                        red += image[i + a][j + b].rgbtRed;
                        green += image[i + a][j + b].rgbtGreen;
                        blue += image[i + a][j + b].rgbtBlue;
                    }
                }
                blurred[i][j].rgbtRed = round(red / 9);
                blurred[i][j].rgbtGreen = round(green / 9);
                blurred[i][j].rgbtBlue = round(blue / 9);
            }
    }
    //blur pixel top and bottom row middle
    for (int j = 1; j < (width - 1); j++)
    {
        int red = 0; 
        int green = 0;
        int blue = 0;
        int red1 = 0;
        int green1 = 0;
        int blue1 = 0;
        for (int b = -1; b < 2; b++)
        {
            red += image[0][j + b].rgbtRed + image[1][j+b].rgbtRed;
            green += image[0][j + b].rgbtGreen + image[1][j+b].rgbtGreen;
            blue += image[0][j + b].rgbtBlue + image[1][j+b].rgbtBlue;
            red1 += image[height - 1][j + b].rgbtRed + image[height - 2][j+b].rgbtRed;
            green1 += image[height - 1][j + b].rgbtGreen + image[height - 2][j+b].rgbtGreen;
            blue1 += image[height - 1][j + b].rgbtBlue + image[height - 2][j+b].rgbtBlue;
            
        }
        
        blurred[0][j].rgbtRed = round(red / 6);
        blurred[0][j].rgbtGreen = round(green / 6);
        blurred[0][j].rgbtBlue = round(blue / 6);
        blurred[height - 1][j].rgbtRed = round(red1 / 6);
        blurred[height - 1][j].rgbtGreen = round(green1 / 6);
        blurred[height - 1][j].rgbtBlue = round(blue1 / 6);
        
    }
    
    //blur pixels left and right edge middle
     for (int i = 1; i < (height - 1); i++)
    {
        int red = 0; 
        int green = 0;
        int blue = 0;
        int red1 = 0;
        int green1 = 0;
        int blue1 = 0;
        for (int b = -1; b < 2; b++)
        {
            red += image[i + b][0].rgbtRed + image[i + b][1].rgbtRed;
            green += image[i + b][0].rgbtGreen + image[i + b][1].rgbtGreen;
            blue += image[i + b][0].rgbtBlue + image[i + b][1].rgbtBlue;
            red1 += image[i + b][width - 1].rgbtRed + image[i + b][width - 2].rgbtRed;
            green1 += image[i + b][width - 1].rgbtGreen + image[i + b][width - 2].rgbtGreen;
            blue1 += image[i + b][width - 1].rgbtBlue + image[i + b][width - 2].rgbtBlue;
            
        }
        
        blurred[i][0].rgbtRed = round(red / 6);
        blurred[i][0].rgbtGreen = round(green / 6);
        blurred[i][0].rgbtBlue = round(blue / 6);
        blurred[i][width - 1].rgbtRed = round(red1 / 6);
        blurred[i][width - 1].rgbtGreen = round(green1 / 6);
        blurred[i][width - 1].rgbtBlue = round(blue1 / 6);
        
    }
    
    //blur corner pixels
    blurred[0][0].rgbtRed = (image[0][0].rgbtRed + image[0][1].rgbtRed + image[1][0].rgbtRed + image[1][1].rgbtRed)/4;
    blurred[0][0].rgbtGreen = (image[0][0].rgbtGreen + image[0][1].rgbtGreen + image[1][0].rgbtGreen + image[1][1].rgbtGreen)/4;
    blurred[0][0].rgbtBlue = (image[0][0].rgbtBlue + image[0][1].rgbtBlue + image[1][0].rgbtBlue + image[1][1].rgbtBlue)/4;
    
    
    blurred[0][width - 1].rgbtRed = (image[0][width - 1].rgbtRed + image[0][width - 2].rgbtRed + image[1][width - 1].rgbtRed + image[1][width - 2].rgbtRed)/4;
    blurred[0][width - 1].rgbtGreen = (image[0][width - 1].rgbtGreen + image[0][width - 2].rgbtGreen + image[1][width - 1].rgbtGreen + image[1][width - 2].rgbtGreen)/4;
    blurred[0][width - 1].rgbtBlue = (image[0][width - 1].rgbtBlue + image[0][width - 2].rgbtBlue + image[1][width - 1].rgbtBlue + image[1][width - 2].rgbtBlue)/4;
    
    blurred[height - 1][ width - 1].rgbtRed = (image[height - 1][width - 1].rgbtRed + image[height - 2][width - 1].rgbtRed + image[height - 1][width - 2].rgbtRed + image[height - 2][width - 2].rgbtRed)/4;
    blurred[height - 1][width - 1].rgbtGreen = (image[height - 1][width - 1].rgbtGreen + image[height - 2][width - 1].rgbtGreen + image[height - 1][width - 2].rgbtGreen + image[height - 2][width - 2].rgbtGreen)/4;
    blurred[height - 1][width - 1].rgbtBlue = (image[height - 1][width - 1].rgbtBlue + image[height - 2][width - 1].rgbtBlue + image[height - 1][width - 2].rgbtBlue + image[height - 2][width - 2].rgbtBlue)/4;
    
    blurred[height - 1][0].rgbtRed = (image[height - 1][0].rgbtRed + image[height - 2][0].rgbtRed + image[height - 1][1].rgbtRed + image[height - 2][1].rgbtRed)/4;
    blurred[height - 1][0].rgbtGreen = (image[height - 1][0].rgbtGreen + image[height - 2][0].rgbtGreen + image[height - 1][1].rgbtGreen + image[height - 2][1].rgbtGreen)/4;
    blurred[height - 1][0].rgbtBlue = (image[height - 1][0].rgbtBlue + image[height - 2][0].rgbtBlue + image[height - 1][1].rgbtBlue + image[height - 2][1].rgbtBlue)/4;
    
    //print blurred array to image array
     for(int i = 1; i < (height - 1); i++)
    {
        for (int j = 1; j < (width - 1); j++)
        {
            image[i][j] = blurred[i][j]; 
        }
    }        
}
