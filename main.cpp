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
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

// The path to the four LED's
#define PATH "/sys/class/leds/beaglebone:green:usr"

// Functions for LED's
void writeLED(char* file, char* value, int led);
void commands(int cmd, int led);
void removeTrigger(int led);

int main(int argc, char* argv[]) {
    int bw, cmd;    // bw = bitwise; cmd = command
    cout << "\n====================================\n";
    cout << "Starting the LED Program\n";
    cout << "USER LED: usr0 [1], usr1 [2], usr2  [4], usr3   [8]\n";
    cout << "Commands: ON   [1], OFF  [2], FLASH [3], STATUS [4]\n";
    cout << "Exit: 0\n";
    cout << "====================================\n";
    cout << "Enter USER LED then command >> ";
    cin >> bw;

    // Loop until the user wants to exit (0)
    while(bw != 0) {
        cin >> cmd; 
        cout << endl;

        // Checking which LED the user wants to be used
        if((bw & 1) == 1) { commands(cmd, 0); }
        if((bw & 2) == 2) { commands(cmd, 1); }
        if((bw & 4) == 4) { commands(cmd, 2); }
        if((bw & 8) == 8) { commands(cmd, 3); }
        cout << "\nEnter USER LED then command >> ";
        cin >> bw;
    }

    // Turning OFF all the LED's
    cout << endl;
    for(int i = 0; i < 4; i++) {
        removeTrigger(i);
        commands(2, i);
    }

    cout << "\nFinished the LED Program\n";
    return 0;
}

void writeLED(char* file, char* value, int led) {
    FILE *fp;
    char fn[255];
    snprintf(fn, sizeof(fn), PATH "%i%s", led, file);
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
       cout << "Turning LED " << led << " ON\n";
       writeLED("/brightness", "1", led);
    } else if(cmd == 2) {
       removeTrigger(led);
       cout << "Turning LED " << led << " OFF\n";
       writeLED("/brightness", "0", led);
    } else if(cmd == 3) {
       cout << "Flashing LED " << led << "\n";
       writeLED("/trigger", "timer", led);
       writeLED("/delay_on", "500", led);
       writeLED("/delay_off", "500", led);
    } else if(cmd == 4) {
       char name[100];
       std::fstream fs;
       sprintf(name, PATH "%i%s", led, "/trigger");
       fs.open(name, std::fstream::in);
       string line;
       while(getline(fs, line)) { cout << line; }
       fs.close();
       cout << endl;
    } else { cout << "\nInvalid Command\n"; }
}

void removeTrigger(int led) {
    // Remove the trigger from the LED
    writeLED("/trigger", "none", led);
}
