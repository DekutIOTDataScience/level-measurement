#include "mbed.h"
#include "hcsr04.h"
#include "SDFileSystem.h"
#include  "FATFileSystem.h"
#include "DS3231.h"
//#include <stdio.h>

SDFileSystem sd(D11, D12, D13, D10, "sd");
HCSR04 sensor(D4, D3);
//Serial pc(USBTX, USBRX);
DS3231 rtc(D14,D15);
FILE *fp;                                   // File pointer declear



int dw,d,M,y,h,m,s;  //VARIABLES FOR TIME AND YEAR


//global variable
long distance; 

   

void sd_write(){
 
 
   
   
 //END OF CODE USED FOR OBTAINING TIME
    sensor.start();
    wait_ms(100); 
    long distance=sensor.get_dist_cm();
     printf("distance is %dcm\n", distance);
     wait_ms(1000);
    // SD card logger
       fp = fopen("/sd/mylogger.txt", "a");            // File open for "a"ppend
    if (fp == NULL) {                               // Error!
           // pc.printf("Unable to write the file\r\n");
        } 
    else {
    rtc.readDateTime(&dw,&d,&M,&y,&h,&m,&s);
    //pc.printf("%02d/%02d/%4d\n",d,M,y);
    //pc.printf("%02d:%02d:%02d",h,m,s);
    //pc.printf(",");
    
    fprintf(fp, "%02d/%02d/%4d\n",d,M,y);
    fprintf(fp, ",");
    fprintf(fp, "%02d:%02d:%02d",h,m,s);
    fprintf(fp, ",");
    //pc.printf("%dcm ",distance);          // Append data to SD card.
    fprintf(fp, "%dcm\r\n",distance);        // Serial monitor.
        }
    fclose(fp);                                     // Cloce file.
    //pc.printf("File successfully written!\r\n");    // Serial monitor.

        
     
    }

 int main() {
    //pc.baud(115200);
    
    
   while (1){
         
    sd_write();     
   wait(298.9);
}
}
