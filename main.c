/*
 * Simple BBB on-board LED flashing program
 * This program uses all USR LED's and can be executed in three ways
 *  - on
 *  - off
 *  - flash
 *  - status
 *
 * Author: Christian Loera
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// The path to the four LED's
#define PATH "/sys/class/leds/beaglebone:green:usr"

// Functions for LED's
void writeLED(char file[], char value[], int led);
void commands(int cmd, int led);
void removeTrigger(int led);

int main(int argc, char* argv[]) {
    int bw, cmd;    // bw = bitwise; cmd = command
    printf("\n====================================\n");
    printf("Starting the LED Program\n");
    printf("USER LED: usr0 [1], usr1 [2], usr2  [4], usr3   [8]\n");
    printf("Commands: ON   [1], OFF  [2], FLASH [3], STATUS [4]\n");
    printf("Exit: 0\n");
    printf("====================================\n");
    printf("Enter USER LED then command >> ");
    scanf("%i", &bw);

    // Loop until the user wants to exit (0)
    while(bw != 0) {
        scanf("%i", &cmd);
        printf("\n");
        while(getchar() != '\n');

        // Checking which LED the user wants to be used
        if((bw & 1) == 1) { commands(cmd, 0); }
        if((bw & 2) == 2) { commands(cmd, 1); }
        if((bw & 4) == 4) { commands(cmd, 2); }
        if((bw & 8) == 8) { commands(cmd, 3); }
        printf("\nEnter USER LED then command >> ");
        scanf("%i", &bw);
    }

    // Turning OFF all the LED's
    printf("\n");
    int i = 0;
    for(i; i < 4; i++) {
        removeTrigger(i);
        commands(2, i);
    }

    printf("\nFinished the LED Program\n");
    exit(0);
}

void writeLED(char file[], char value[], int led) {
    FILE *fp;
    char fn[255];
    sprintf(fn, PATH "%i%s", led, file);
    fp = fopen(fn, "w+");
    fprintf(fp, "%s", value);
    fclose(fp);
}

void commands(int cmd, int led) {
    /*
     * cmd: 1 --> on
     * cmd: 2 --> off
     * cmd: 3 --> flash
     * cmd: 4 --> status
     */
    if(cmd == 1) {
        removeTrigger(led);
        printf("Turning usr%d ON\n", led);
        writeLED("/brightness", "1", led);
    } else if(cmd == 2) {
        removeTrigger(led);
        printf("Turning usr%d OFF\n", led);
        writeLED("/brightness", "0", led);
    } else if(cmd == 3) {
        printf("Flashing usr%d\n", led);
        writeLED("/trigger", "timer", led);
        writeLED("/delay_on", "500", led);
        writeLED("/delay_off", "500", led);
    } else if(cmd == 4) {
        FILE *fp;
        char name[100];
        char line[20];
        sprintf(name, PATH "%i%s", led, "/trigger");
        fp = fopen(name, "rt");
        printf("\n");
        while(fgets(line, sizeof(line), fp) != NULL) { printf("%s", line); }
        fclose(fp);
        printf("\n");
    } else { printf("\nInvalid Command\n"); }
}

void removeTrigger(int led) {
    // Remove the trigger from the LED
    writeLED("/trigger", "none", led);
}
