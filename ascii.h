#ifndef ASCII_H
#define ASCII_H

#include "color.h" // Include your color library
#include <iostream>
#include <windows.h>  // For Sleep and clearing the console
using namespace std;


// Function to play a sound at the beginning
void playSound() {
    // Replace the path with the location of your .wav file
    PlaySound(TEXT("sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void playwelcomesound() {
    // Replace the path with the location of your .wav file
    PlaySound(TEXT("welcome.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
// Function to print text character by character with a delay
void printCharByChar(const string& text, const string& color = RESET) {
    for (char ch : text) {
        cout << color << ch << RESET;  // Apply color to each character
        Sleep(50);  // Add a delay between characters for effect
    }
    cout << endl;
    Sleep(500);  // Pause after finishing the text
}

// Function to display a welcome animation with the bridge and airplane
void displayWelcome() {
    // Bridge and airplane ASCII art
    string art = R"(
         @\_______/@
        @|XXXXXXXX |
       @ |X||    X |
      @  |X||    X |
     @   |XXXXXXXX |
    @    |X||    X |             V
   @     |X||   .X |                                               |
  @      |X||.  .X |                      V                  --====|====--
 @      |%XXXXXXXX%||                                              |
@       |X||  . . X||                                          .-"""""-. 
        |X||   .. X||                                        .'_________'. 
        |X||  .   X||                                       /_/_|__|__|_\_\
        |X|| .    X||                                      ;'-._       _.-';
       |XXXXXXXXXXXX||                ,--------------------|    `-. .-'    |--------------------,
       |XXXXXXXXXXXX||                 ``""--..__    ___   ;       '       ;   ___    __..--""```   
       |XX|        X||                           `"-// \\.._\             /_..// \\-"`         
       |XX|        X||                              \\_//    '._       _.'    \\_// 
       |XX|        X||                               `"`        ``---``        `"` 
       |XX|======= X||==========================+|==============================================+
    )";

    system("cls");
    // Print the art in bold cyan for a soothing look
    cout << BOLD_CYAN << art << RESET << endl;

    // Tagline after the art
    cout << string(BOLD_WHITE) + BG_BLUE + "======================================================================================================================================" + RESET << endl;
    cout << BOLD_YELLOW << "\n\t\tFlight Path Visualizer - SkyNav AI" << RESET << endl;
    cout << BOLD_GREEN << "\t\t\t\t\t\t\t\tWhere every journey is a masterpiece of connectivity.\n" << RESET << endl;
    cout << BOLD_RED << "\tM.AKASH WARIS     HABIB AHMED    ABDULLAH NOMAN" << RESET << endl;
    cout << string(BOLD_WHITE) + BG_BLUE + "======================================================================================================================================" + RESET << endl;
    Sleep(2000); // Pause for 2 seconds to let the user absorb the welcome screen
}

// Function to display the ASCII art title with a delay effect
void printAsciiArtWithDelay() {
    string asciiArt = R"(
 

 _      _____ _     ____  ____  _      _____   _____  ____    ____  _  _____  _ _      ____  _       ____  _ 
/ \  /|/  __// \   /   _\/  _ \/ \__/|/  __/  /__ __\/  _ \  / ___\/ |/ /\  \/// \  /|/  _ \/ \ |\  /  _ \/ \
| |  |||  \  | |   |  /  | / \|| |\/|||  \      / \  | / \|  |    \|   /  \  / | |\ ||| / \|| | //  | / \|| |
| |/\|||  /_ | |_/\|  \_ | \_/|| |  |||  /_     | |  | \_/|  \___ ||   \  / /  | | \||| |-||| \//   | |-||| |
\_/  \|\____\\____/\____/\____/\_/  \|\____\    \_/  \____/  \____/\_|\_\/_/   \_/  \|\_/ \|\__/    \_/ \|\_/
                                                                                                             

                                                                                                             
)";
    // Print the title in bold yellow
    for (char ch : asciiArt) {
        cout << BOLD_YELLOW  <<ch << RESET;
        Sleep(10); // Add delay between characters
    }
    Sleep(500); // Final delay after printing the ASCII art
}


void displayGoodbyeScreen() {
    system("cls"); // Clear the screen before starting the goodbye animation
    string goodbyeArt = R"(
  ____  ___   ___  ____    ______   _______ 
 / ___|/ _ \ / _ \|  _ \  | __ ) \ / / ____|
| |  _| | | | | | | | | | |  _ \\ V /|  _|  
| |_| | |_| | |_| | |_| | | |_) || | | |___ 
 \____|\___/ \___/|____/  |____/ |_| |_____|
    )";

    // Print the goodbye message with colors
    for (char ch : goodbyeArt) {
        if (ch == '\n') {
            cout << endl;
            continue;
        }
        cout << BOLD_RED << ch << RESET;
        Sleep(20); // Slight delay for a typewriter effect
    }

    Sleep(1000); // Keep the message visible for a while
    cout << "\n\t\tThank you for using SkyNav AI!" << endl;
    Sleep(1000);

    system("cls"); // Clear the screen as the goodbye animation ends
}
#endif