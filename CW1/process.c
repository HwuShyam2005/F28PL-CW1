#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

// THE RGB VALUES OF A PIXEL.
struct Pixel
{
    uint16_t red;
    uint16_t green;
    uint16_t blue;
};

/*--------------------*/
/*AN IMAGE LOADED FROM A FILE*/
/*--------------------*/

/*QUESTION 1*/

struct Image
{
    int width;  // WIDTH OF THE IMAGE IN PIXELS
    int height; // HEIGHT OF THE IMAGE IN PIXELS
    struct Pixel *pixels;
    // POINTER TO AN ARRAY OF PIXEL WHICH REPRESENTS THE IMAGE DATA
};

/*--------------------*/
/*FREE IMAGE*/
/*--------------------*/

/*QUESTION 2A*/

// A FUNCTION TO FREE MEMORY ALLOCATED FOR IMAGE STRUCTURE
void free_image(struct Image *img)
{
    // CHECKING IF THE IMAGE POINTER IS NOT NULL
    if (img != NULL)
    {
        // FREE MEMORY WHICH IS ALLOCATED FOR PIXEL DATA IN IMAGE STRUCTURE
        free(img->pixels);
        // FREE MEMORY FOR IMAGE STRUCTURE ITSELF
        free(img);
    }
}

/*--------------------*/
/*LOAD IMAGE*/
/*--------------------*/

/*QUESTION 2B*/

// FUNCTION FOR LOADING A IMAGE WHICH RETURNS A POINTER TO LOADED IMAGE STRUCTURE
// IF ERROR OCCURS , IT WILL RETURN NULL
struct Image *load_image(const char *filename)
{
    // FILE OPENS IN BINARY MODE FOR CROSS-PLATFORM COMPACTABILITY
    FILE *f = fopen(filename, "rb");
    // CHECKS IF FILE CAN BE OPENED OR NOT
    if (f == NULL)
    {
        // PRINTS ERROR MESSAGE TO STDERR
        fprintf(stderr, "File %s could not be opened.\n", filename);
        // RETURNING NULL TO INDICATE AN ERROR IN LOADING IMAGE
        return NULL;
    }

    // ALLOCATING IMAGE OBJECT AND READING THE IMAGE FROM FILE
    struct Image *img = malloc(sizeof(struct Image));
    // CHECKING IF MEMORY ALLOCATION WAS SUCCESSFUL
    if (img == NULL)
    {
        // PRINTING ERROR MESSAGE TO STDERR
        fprintf(stderr, "Memory allocation failed.\n");
        // CLOSING FILE AND RETURNING NULL
        fclose(f);
        // RETURN NULL TO INDICATE ERROR IN MEMORY ALLOCATION
        return NULL;
    }

    // CHECKING THE FILE FORMATS

    // DECLARING AN ARRAY FOR STORING FORMAT READ FROM FILE
    // INCREASING SIZE FOR HANDILING HSHEX AND NULL TERMINATOR
    char format[6];
    // TRYING TO READ UPTO 5 CHARACTERS FROM FILE INTO FORMAT ARRAY
    // CHECKING IF READ OPERATION IS SUCCESSFUL AND FORMAT IS HSHEX
    if (fscanf(f, "%5s", format) != 1 || strcmp(format, "HSHEX") != 0)
    {
        // PRINTING AN ERROR MESSAGE TO STDERR
        fprintf(stderr, "Error: Invalid file format\n");
        // FREE MEMORY ALLOCATED FOR IMAGE STRUCTURE
        free(img);
        // CLOSING FILE BEFORE RETURNING NULL
        fclose(f);
        // RETURN NULL TO INDICATE ERROR IN FILE FORMAT
        return NULL;
    }

    // READING IMAGE DIMENSIONS
    if (fscanf(f, "%d %d", &img->width, &img->height) != 2 || img->width <= 0 || img->height <= 0)
    {
        // PRINTING ERROR MESSAGE TO STDERR IF READ OPERATION WASNT SUCCESSFUL
        // OR IF DIMENSIONS ARE NOT VALID
        fprintf(stderr, "Error reading image dimensions from %s.\n", filename);
        // FREE MEMORY ALLOCATED FOR IMAGE STRUCTURE
        free(img);
        // CLOSING FILE BEFORE RETURNING NULL
        fclose(f);
        // RETURN NULL TO INDICATE ERROR IN READING THE DIMENSIONS
        return NULL;
    }

    // ALLOCATING A MEMORY FOR IMAGE DATA
    img->pixels = malloc(sizeof(struct Pixel) * img->width * img->height);
    // CHECK IF MEMORY ALLOCATING FOR PIXEL DATA WAS SUCCESSFUL
    if (img->pixels == NULL)
    {
        // PRINT ERROR MESSAGE TO STDERR IF MEMORY ALLOCATION FAILS
        fprintf(stderr, "Error: Memory allocation failed.\n");
        // FREE THE MEMORY ALLOCATED FOR IMAGE STRUCTURE
        free(img);
        // CLOSING FILE BEFORE RETURNING NULL
        fclose(f);
        // RETURN NULL TO INDICATE ERROR IN MEMORY ALLOCATION
        return NULL;
    }

    // ALLOCATING MEMORY FOR IMAGE PIXEL DATA
    img->pixels = (struct Pixel *)malloc(sizeof(struct Pixel) * img->width * img->height);
    // CHECKING IF MEMORY ALLOCATION FOR PIXEL DATA WAS SUCCESSFUL
    if (img->pixels == NULL)
    {
        // USING PERROR FOR PRINTING ERROR MESSAGE
        perror("Error allocating memory for pixel data");
        // FREE THE MEMORY FOR ALLOCATING IMAGE STRUCTURE
        free_image(img);
        // CLOSING FILE BEFORE RETURNING NULL
        fclose(f);
        // RETURN NULL TO INDICATE AN ERROR IN MEMORY ALLOCATION
        return NULL;
    }

    // READING PIXEL DATA FROM THE FILE
    for (int i = 0; i < img->width * img->height; ++i)
    {
        // ATTEMPTING TO READ 3 HEXADECIMAL VALUES REPRESENTING RGB COMPONENTS FOR EACH PIXEL
        if (fscanf(f, "%hx %hx %hx", &img->pixels[i].red, &img->pixels[i].green, &img->pixels[i].blue) != 3)
        {
            // PRINTING ERROR MESSAGE TO STDERR
            fprintf(stderr, "Error reading pixel data.\n");
            // FREE MEMORY ALLOCATED FOR IMAGE STRUCTURE
            free_image(img);
            // CLOSING FILE BEFORE RETURNING NULL
            fclose(f);
            // RETURN NULL TO INDICATE AN ERROR IN READING THE PIXEL DATA
            return NULL;
        }
    }
    // CLOSE FILE AFTER SUCCESSFULLY READING PIXEL DATA
    fclose(f);
    // RETURN POINTER TO THE IMAGE STRUCTURE THATS LOADED
    return img;
}

/*--------------------*/
/*SAVE IMAGE*/
/*--------------------*/

/*QUESTION 2C*/

// SAVE THE IMAGE TO A FILE.
// RETURNS TRUE FOR SUCCESS AND FALSE FOR ERROR
bool save_image(const struct Image *img, const char *filename)
{
    // OPEN FILE IN BINARY MODE FOR CROSS PLATFORM COMPATIBILITY
    FILE *file = fopen(filename, "wb");
    // CHECK IF FILE COULD BE OPENED OR NOT
    if (file == NULL)
    {
        // PRINT ERROR TO STDERR
        fprintf(stderr, "Error opening file: %s\n", filename);
        // RETURN FALSE TO INDICATE ERROR IN OPENING THE FILE
        return false;
    }

    // WRITING HEADER INFORMATION TO THE FILE
    if (fprintf(file, "HSHEX %d %d ", img->width, img->height) < 0)
    {
        // PRINTING ERROR MESSAGE IF WRITING HEADER FAILS
        printf("Error writing header to %s\n", filename);
        // CLOSING FILE BEFORE RETURNING FALSE
        fclose(file);
        // RETURN FALSE TO INDICATE ERROR IN WRITING THE HEADE
        return false;
    }

    // WRITING PIXEL DATA FOR THE FILE
    for (int i = 0; i < img->width * img->height; ++i)
    {
        // WRITE RED COLOUR OF THE PIXEL IN HEXADECIMAL FORMAT
        if (fprintf(file, "%02hhx%02hhx ", img->pixels[i].red, img->pixels[i].red) < 0 ||
            // WRITE GREEN COLOUR OF THE PIXEL IN HEXADECIMAL FORMAT
            fprintf(file, "%02hhx%02hhx ", img->pixels[i].green, img->pixels[i].green) < 0 ||
            // WRITE BLUE COLOUR OF THE PIXEL IN HEXADECIMAL FORMAT
            fprintf(file, "%02hhx%02hhx ", img->pixels[i].blue, img->pixels[i].blue) < 0)
        {
            // PRINTING ERROR MESSAGE TO STDERR
            fprintf(stderr, "File %s could not be written.\n", filename);
            // CLOSE FILE BEFORE RETURNING FALSE
            fclose(file);
            // RETURN FALSE TO INDICATE ERROR IN WRITING PIXEL DATA
            return false;
        }
    }
    // CLOSE FILE AFTER SUCCESSFULLY WRITING PIXEL DATA
    fclose(file);
    // RETURN TRUE TO INDICATE SUCCESSFUL WRITING OF IMAGE DATA
    return true;
}

/*--------------------*/
/*DUPLICATE IMAGE*/
/*--------------------*/

/*QUESTION 2D*/

// DUPLICATE (COPY) AN IMAGE
struct Image *copy_image(const struct Image *source)
{
    // CHECKING IF THE SOURCE IMAGE IS VALID OR NOT
    if (source == NULL)
    {
        return NULL;
    }

    // ALLOCATING MEMORY FOR THE NEW IMAGE
    struct Image *copy = (struct Image *)malloc(sizeof(struct Image));
    // CHECKING IF MEMORY ALLOCATION WAS SUCCESSFUL OR NOT
    if (copy == NULL)
    {
        // PRINTING ERROR MESSAGE TO STDERR
        fprintf(stderr, "Memory allocation failed for the new image.\n");
        // RETURNING NULL
        return NULL;
    }

    // COPYING THE WIDTH AND HEIGHT
    copy->width = source->width;
    copy->height = source->height;

    // ALLOCATING THE MEMORY FOR THE PIXEL DATA
    copy->pixels = (struct Pixel *)malloc(sizeof(struct Pixel) * copy->width * copy->height);
    if (copy->pixels == NULL)
    {
        // PRINTING ERROR MESSAGE TO STDERR
        fprintf(stderr, "Memory allocation failed for pixel data.\n");
        // FREE MEMORY ALLOCATED FOR THE NEW IMAGE STRUCTURE
        free(copy);
        // RETURNING NULL
        return NULL;
    }

    // COPYING THE PIXEL DATAS FOR ALL RGB COLOURS
    for (int i = 0; i < copy->width * copy->height; ++i)
    {
        // FOR RED
        copy->pixels[i].red = source->pixels[i].red;
        // FOR GREEN
        copy->pixels[i].green = source->pixels[i].green;
        // FOR BLUE
        copy->pixels[i].blue = source->pixels[i].blue;
    }
    // RETURN THE DUPLICATED IMAGE
    return copy;
}

/*--------------------*/
/*PERSONALISED TASK 1*/
/*--------------------*/

/* NOISE */

// APPLY RANDOM NOISE TO AN IMAGE
struct Image *apply_NOISE(const struct Image *source, int noise_strength)
{
    // CHECKING IF THE SOURCE IMAGE IS VALID OR NOT
    if (source == NULL)
    {
        // PRINTING ERROR MESSAGE TO STDERR
        fprintf(stderr, "Error: Invalid source image.\n");
        // RETURNING NULL
        return NULL;
    }

    // ALLOCATING MEMORY FOR THE NEW IMAGE
    struct Image *result = (struct Image *)malloc(sizeof(struct Image));
    // CHECKING IF THE RESULT IS VALID OR NOT
    if (result == NULL)
    {
        // PRINTING ERROR MESSAGE TO STDERR
        fprintf(stderr, "Memory allocation failed for the new image.\n");
        // RETURNING NULL
        return NULL;
    }
    // SETTING WITDTH AND HEIGHT OF THE NEW IMAGE
    result->width = source->width;
    result->height = source->height;

    // ALLOCATING MEMORY FOR THE PIXEL DATA OF THE NEW IMAGE
    result->pixels = (struct Pixel *)malloc(sizeof(struct Pixel) * source->width * source->height);
    // CHECKING IF THE MEMORY ALLOCATION FOR PIXEL DATA WAS SUCCESSFUL OR NOT
    if (result->pixels == NULL)
    {
        // PRINTING ERROR MESSAGE TO STDERR
        fprintf(stderr, "Memory allocation failed for pixel data.\n");
        // FREE MEMORY ALLOCATED FOR NEW IMAGE STRUCTURE
        free_image(result);
        // RETURNING NULL
        return NULL;
    }

    // APPLYING RANDOM NOISE TO EACH THE COMPONENT OF EACH PIXEL
    for (int i = 0; i < source->width * source->height; ++i)
    {
        // ADDING RANDOM NOISE TO RED COMPONENT
        result->pixels[i].red = source->pixels[i].red + (rand() % (2 * noise_strength + 1) - noise_strength);
        // ADDING RANDOM NOISE TO GREEN COMPONENT
        result->pixels[i].green = source->pixels[i].green + (rand() % (2 * noise_strength + 1) - noise_strength);
        // ADDING RANDOM NOISE TO BLUE COMPONENT
        result->pixels[i].blue = source->pixels[i].blue + (rand() % (2 * noise_strength + 1) - noise_strength);

        // ENSURING VALUES STAYS WITHIN THE VALID RANGE(0-65535) FOR ALL RGB VALUES
        // FOR RED
        result->pixels[i].red = result->pixels[i].red > 65535 ? 65535 : (result->pixels[i].red < 0 ? 0 : result->pixels[i].red);
        // FOR GREEN
        result->pixels[i].green = result->pixels[i].green > 65535 ? 65535 : (result->pixels[i].green < 0 ? 0 : result->pixels[i].green);
        // FOR BLUE
        result->pixels[i].blue = result->pixels[i].blue > 65535 ? 65535 : (result->pixels[i].blue < 0 ? 0 : result->pixels[i].blue);
    }

    // RETURNING THE NEW IMAGE WITH APPLIED NOISE
    return result;
}

/*--------------------*/
/*PERSONALISED TASK 2*/
/*--------------------*/

/*HIST*/

// PRINTING THE HISTOGRAM OF AN IMAGE
bool apply_HIST(const struct Image *source)
{
    // CHECKING IF THE SOURCE IMAGE IS VALID OR NOT
    if (source == NULL)
    {
        // PRINTING ERROR MESSAGE TO STDERR
        fprintf(stderr, "Error: Invalid source image.\n");
        // RETURNING FALSE
        return false;
    }

    // ALLOCATING MEMORY FOR THE HISTOGRAM
    // WE WILL ASSUME IT AS 8-BIT VALUES , 0-255
    int histogram[256] = {0};

    // Computing the histogram
    for (int i = 0; i < source->width * source->height; ++i)
    {
        // Extracting the red, green, and blue components of each pixel
        uint16_t red_value = source->pixels[i].red;
        uint16_t green_value = source->pixels[i].green;
        uint16_t blue_value = source->pixels[i].blue;

        // Increases the corresponding histogram entry
        histogram[red_value / 256]++;
        histogram[green_value / 256]++;
        histogram[blue_value / 256]++;
    }

    // Printing the histogram
    for (int i = 0; i < 256; ++i)
    {
        // Format for printing
        // For each value (0-255) and pixels
        printf("Value %d: %d pixels\n", i, histogram[i]);
    }
    // RETURNING TRUE AFTER SUCCESSFULLY PRINTING THE VALUES
    return true;
}

/*--------------------*/
/*MAIN METHOD*/
/*--------------------*/

int main(int argc, char *argv[])
{
    /* Initialise the random number generator, using the time as the seed */
    srand(time(NULL));

    /* Check command-line arguments */
    if (argc != 4)
    {
        fprintf(stderr, "Usage: process INPUTFILE OUTPUTFILE\n");
        return 1;
    }

    /* Load the input image */
    struct Image *in_img = load_image(argv[1]);
    if (in_img == NULL)
    {
        return 1;
    }

    printf("Loaded !\n");

    /*EXTRACTING THE NOISE STRENGTH FROM COMMAND LINE */
    int noise_strength = atoi(argv[3]);

    /* APPLICATION OF FIRST PROCESS */
    struct Image *out_img = apply_NOISE(in_img, noise_strength);
    if (out_img == NULL)
    {
        fprintf(stderr, "First process failed.\n");
        free_image(in_img);
        return 1;
    }

    /* APPICATION OF SECOND PROCESS */
    if (!apply_HIST(out_img))
    {
        fprintf(stderr, "Second process failed.\n");
        free_image(in_img);
        free_image(out_img);
        return 1;
    }

    /* SAVING THE OUTPUT IMAGE */
    if (!save_image(out_img, argv[2]))
    {
        fprintf(stderr, "Saving image to %s failed.\n", argv[2]);
        free_image(in_img);
        free_image(out_img);
        return 1;
    }

    free_image(in_img);
    free_image(out_img);
    return 0;
}