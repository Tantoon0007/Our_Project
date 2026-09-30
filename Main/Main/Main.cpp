#define _CRT_SECURE_NO_WARNINGS
/*
Name                ID              what he did;            section

Mohamed Sayed       20240500        2,6,10                  S
Eyad Wael           20250100        3,7                     S
Abd El-Rahman Amr   20250368        4,8,12,16               S
Tony Samir Sobhy    20240132        1,5,13                  S

*/
#include <iostream>
using namespace std;
#include "Image_Class.h"

void applygrayscale(Image& image)
{
    for (int i = 0; i < image.width; ++i)
    {

        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; ++k)
            {
                avg += image(i, j, k);
            }

            avg /= image.channels;
            for (int k = 0; k < image.channels; ++k)
            {
                image(i, j, k) = avg;
            }
        }
    }
}

void blackandwhite(Image& image)
{

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = 0; // Initialize average value

            for (int k = 0; k < 3; ++k)
            {
                avg += image(i, j, k); // Accumulate pixel values
            }

            avg /= 3; // Calculate average

            avg = (avg < 128) ? 0 : 255;
            // Set all channels to the average value
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
}

void invert(Image& image)
{

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {

            for (int k = 0; k < 3; ++k)
            {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
}

void frame(Image& image)
{

    int size = 70;

    for (int y = 0; y < image.height; y++)
    {
        for (int x = 0; x < image.width; x++)
        {

            if (x < size || x >= image.width - size || y < size || y >= image.height - size)
            {
                image(x, y, 0) = 255;
                image(x, y, 1) = 0;
                image(x, y, 2) = 255;
            }
        }
    }
}

class Flipped_Image {
public:

    static void flip_Horizontally(Image& image) {
        for (int x = 0; x < image.width / 2; x++) {
            for (int y = 0; y < image.height; y++) {
                for (int z = 0; z < image.channels; z++) {
                    swap(image(x, y, z), image(image.width - 1 - x, y, z));
                }
            }
        }
    }

    static void flip_vertically(Image& image) {
        for (int x = 0; x < image.width; x++) {
            for (int y = 0; y < image.height / 2; y++) {
                for (int z = 0; z < image.channels; z++) {
                    swap(image(x, y, z), image(x, image.height - 1 - y, z));
                }
            }
        }
    }

    static void processflip(Image& image) {
        int choice;
        while (true) {
            cout << "=======================================\n";
            cout << "   Welcome to Image Flipper Program    \n";
            cout << "=======================================\n";
            cout << "Please select flip direction:\n";
            cout << "1. Horizontal Flip (Left to Right)\n";
            cout << "2. Vertical Flip (Top to Bottom)\n";
            cout << "---------------------------------------\n";
            cout << "Enter your choice (1 or 2): ";

            cin >> choice;

            switch (choice) {
            case 1:
                flip_Horizontally(image);
                cout << "\nImage Flipped Horizontally Successfully!\n";
                return;

            case 2:
                flip_vertically(image);
                cout << "\nImage Flipped Vertically Successfully!\n";
                return;

            default:
                cout << "\n[Error] Invalid choice! Please enter 1 or 2.\n\n";
            }
        }
    }
};

void rotate(Image& image)
{


    cout << "How do you want to rotate your image clockwise?\n";
    cout << "Choose a number from the following options!\n";
    cout << "1- 90 \n";
    cout << "2- 180 \n";
    cout << "3- 270 \n";
    int degree_choice;
    cin >> degree_choice;


    for (int r = 0; r < degree_choice; r++) {
        Image image2 = image;
        image.height = image2.width;
        image.width = image2.height;
        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                for (int k = 0; k < image.channels; ++k)
                {
                    image(i, j, k) = image2(j, image2.height - i - 1, k);
                }

            }
        }
    }
}

void applylightendarken(Image& image, int choice)
{
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            for (int k = 0; k < image.channels; ++k)
            {
                if (choice == 1)
                {
                    int newvalue = image(i, j, k) + ((255 - image(i, j, k)) * 0.5);
                    image(i, j, k) = min(255, newvalue);
                }
                else if (choice == 2)
                {
                    image(i, j, k) = image(i, j, k) * 0.5;
                }
            }
        }
    }
}

void resize(Image& image)
{

    int new_width = 100;
    int new_height = 100;

    Image resizedImage(new_width, new_height);

    for (int y = 0; y < new_height; y++)
    {
        for (int x = 0; x < new_width; x++)
        {
            int originalX = x * image.width / new_width;
            int originalY = y * image.height / new_height;

            for (int c = 0; c < image.channels; c++)
            {
                resizedImage(x, y, c) = image(originalX, originalY, c);
            }
        }
    }

    image = resizedImage;
}

void edges(Image& image)
{

    blackandwhite(image);
    Image image2 = image;

    for (int i = 1; i < image.width - 1; ++i)
    {
        for (int j = 1; j < image.height - 1; ++j)
        {
            if (image(i, j, 0) == 0 && (image2(i - 1, j, 0) != image2(i + 1, j, 0) || image2(i, j - 1, 0) != image2(i, j + 1, 0)))
            {
                image(i, j, 0) = 0;
                image(i, j, 1) = 0;
                image(i, j, 2) = 0;
            }
            else
            {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
        }
    }
}

void blur(Image& image)
{
    Image image2 = image;

    for (int i = 1; i < image.width - 1; ++i)
    {
        for (int j = 1; j < image.height - 1; ++j)
        {
            // unsigned int avg = 0;

            for (int k = 0; k < 3; ++k)
            {

                unsigned int avg = 0;
                avg = (image2(i, j, k) + image2(i + 1, j, k) + image2(i - 1, j, k) + image2(i, j + 1, k) + image2(i, j - 1, k) + image2(i - 1, j - 1, k) + image2(i + 1, j + 1, k) + image2(i - 1, j + 1, k) + image2(i + 1, j - 1, k)) / 9;

                image(i, j, k) = avg;
            }
        }
    }
}

void  natural_sunlight(Image& image) {

    /*
        either we
        reduce the blue
        or
        increase the red and green
    */

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {

            // if((image(i,j,0) + 40)>=255 || (image(i,j,1) + 40)>=255 ){
            //     image(i,j,0)=255;
            //     image(i,j,1)=255;
            //     continue;
            // }
            // else{
            //     image(i,j,0) += 40;
            //     image(i,j,1) += 40;

            if ((image(i, j, 2) - 40) <= 0) { //to ensure we don't go out of range
                image(i, j, 2) = 0;
                continue;
            }
            else {
                image(i, j, 2) -= 40;
            }
        }
    }

}

void infrared(Image& image)
{

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            image(i, j, 0) = 0;
        }
    }
    invert(image);
}



int main()
{
    string filename;
    cout << "Pls enter colored image name to use :";
    cin >> filename;
    Image image(filename);

    cout << "\n which filter do you want to apply? \n";
    cout << "1- grayscale\n";
    cout << "2- back and white\n";
    cout << "3- invert\n";
    cout << "4- frame\n";
    cout << "5- flip\n";
    cout << "6- rotate\n";
    cout << "7.lighten \n";
    cout << "77.darken \n";
    cout << "8.resize \n";
    cout << "10- Detect Image Edges\n";
    cout << "12- Blur Image\n";
    cout << "13- natural sunlight\n";
    cout << "16- infrared\n";
    int choice;
    cin >> choice;

    if (choice == 1)
    {
        applygrayscale(image);
    }

    else if (choice == 2)
    {
        blackandwhite(image);
    }

    else if (choice == 3)
    {
        invert(image);
    }

    else if (choice == 4)
    {
        frame(image);
    }

    else if (choice == 5)
    {
        if (image.width == 0 || image.height == 0) {
            cout << "Error loading image!\n";
            return 1;
        }

        Flipped_Image::processflip(image);
    }

    else if (choice == 6)
    {
        rotate(image);
    }

    else if (choice == 7)
    {
        applylightendarken(image, 1);
        cout << "lighten filter applied successfully \n";
    }

    else if (choice == 77)
    {
        applylightendarken(image, 2);
        cout << "darken filter applied successfully \n";
    }

    else if (choice == 8)
    {
        resize(image);
    }

    else if (choice == 10)
    {
        edges(image);
    }

    else if (choice == 12)
    {
        for (int i = 0; i < 50; i++)
        {
            cout << i << endl;
            blur(image);
        }
    }

    else if (choice == 13)
    {
        natural_sunlight(image);
    }

    else if (choice == 16)
    {
        infrared(image);
    }

    else
    {
        cout << "you entered an invalid choice \n";
        return 0;
    }

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga:\n";

    cin >> filename;
    image.saveImage(filename);
    cout << "Image saved successfully as " << filename << endl;

    return 0;
}