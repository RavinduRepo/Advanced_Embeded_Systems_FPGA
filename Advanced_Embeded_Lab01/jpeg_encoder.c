/*************************************************************************************
 * CO503 Advanced Embedded Systems
 *
 * Date			: 16-08-2016
 * Author 		: Isuru Nawinne
 * Edited by	: Ravindu Pathirage
 *
 * Description	: Compress and convert a BMP image file into JPEG format
 *
 *************************************************************************************/

#include "application/jpeg_encoding.h"
#include "application/bmp_extract.h"
#include <io.h>
#include <system.h>  // Contains LED_OUT_BASE definition from your BSP
#define NO_OF_FILES 7


void convert_picture(const char *jtag_input);


int main()
{
	char jtag_input[20] = "image3.bmp";

	// Print that welcome message. Programmers looove welcome messages! ;)
	printf("CO503 JPEG Encoder \n\n");

	while(1) {
		printf("Input file: ");
		scanf("%s", jtag_input); // Ask for the input BMP file

		// Check if the filename ends in '.bmp'
		if(strcmp(&jtag_input[strlen(jtag_input) - 4], ".bmp") == 0) {

			convert_picture(jtag_input); // See function at the bottom

		}
		printf("\n\n");
	}

	return 0;
}

/*
 * Convert a BMP picture of name <jtag_input> into JPEG.
 */
void convert_picture(const char *jtag_input)
{
	char file_name[80] = "/mnt/host/files/";
	char destination[80] = "/mnt/host/files/";
	Bmp_data pic_data;

	strcat(file_name, jtag_input);
	strcat(destination, jtag_input);

	// Replace the '.bmp' with '.jpg'
	strcpy(&destination[strlen(destination) - 3], "jpg");

    // [CODE ADDITION 1]: Turn ON all LEDs to indicate "Processing Started/Busy"
    IOWR_8DIRECT(LED_OUT_BASE, 0, 0xFF); 
    if(bmp_extract(file_name, &pic_data) == 0) {
        
        // This takes time (Processing...)
        jpeg_encode(destination, pic_data.bitmap, pic_data.header->BMPHeight, pic_data.header->BMPWidth, 90);
        
        // [CODE ADDITION 2]: Turn OFF LEDs (or set to 0x00) to indicate "Done"
        IOWR_8DIRECT(LED_OUT_BASE, 0, 0x00);
        
    } else {
        // [Optional]: Blink LEDs or set a specific pattern for "Error"
        IOWR_8DIRECT(LED_OUT_BASE, 0, 0xAA); 
    }
}
