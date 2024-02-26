// DS4Talker 

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <ncurses.h>

#define AVATAR '*'
#define EMPTY_SPACE ' '
#define MAXWORDS 100
#define WORDLENGTH 11
#define DEBUGM 1  // set to 0 to disable debug output
// ds4rd-real.exe -d 054c:05c4 -D DS4_BT -t -b -j -bt | ./DS4Talker wordlist.txt
// gcc -o DS4Talker DS4Talker.c -lncurses
// Reads words from the file into WL and trims the whitespace off of the end
// DO NOT MODIFY THIS FUNCTION
int read_words(char* WL[MAXWORDS], char* file_name);
// modifies str to trim white space off the right side
// DO NOT MODIFY THIS FUNCTION
void trimws(char* str);
void draw_cursor(int x, int y, char use);

int main(int argc, char* argv[]) {
    char* wordlist[MAXWORDS];
    int wordCount;
    int i;
    int time, timenew, triangle, circle, xbutton, square, joyPressR, joyPressL, options, share, R2, L2, R1, L1, Lj1, Lj2, Rj1, Rj2;
    int y = 0, x = 0;
    int rowCount = 22; //the row where the sentence will be displayed
    int lengthOfLast = 0;
    int lengthOfSentence = 0;
    int capitalizeNext = 0;

    char undoBuffer[WORDLENGTH];  //buffer to store the last added word for undo

    wordCount = read_words(wordlist, argv[1]);

    if (DEBUGM) {
        printf("Read %d words from %s \n", wordCount, argv[1]);
        for (i = 0; i < wordCount; i++) {
            printf("%s,", wordlist[i]);
        }
        printf("\n");
    }
	
	// most of your code goes here. Do not forget to include the ncurses library

    initscr();
    refresh();

    //load words
    for (i = 0; i < wordCount; i++) {
        mvprintw(y, x * 15, "%15s", wordlist[i]);
        refresh();
        x++;

        if (x > 4) {
            y++;
            x = 0;
        }
    }

    while (1) {
        scanf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
              &time, &triangle, &circle, &xbutton, &square, &joyPressR, &joyPressL, &options, &share, &R2, &L2, &R1, &L1, &Lj1, &Lj2, &Rj1, &Rj2);

        //delay
        if (time - timenew < 150) {
            continue;
        }

        draw_cursor(x, y, EMPTY_SPACE);

        if (Rj1 > 100 && x < wordCount - 1) {
            x++;
        }
        if (Rj1 < -100 && x > 0) {
            x--;
        }
        if (Rj2 > 100 && y < wordCount - 1) {
            y++;
        }
        if (Rj2 < -100 && y > 0) {
            y--;
        }

        timenew = time;

        draw_cursor(x, y, AVATAR);

        //triangle button press
        if (triangle == 1) {
            int indexToUse = y * 5 + x;
            if (indexToUse >= 0 && indexToUse < wordCount) {
                lengthOfLast = strlen(wordlist[indexToUse]) + 1;
                char toAdd[WORDLENGTH];
                strcpy(toAdd, wordlist[indexToUse]);
                if (capitalizeNext) {
                    toAdd[0] -= 0x20;
                }
                if (lengthOfSentence + lengthOfLast + 1 < 80) { // +1 for space
                    mvprintw(rowCount, lengthOfSentence, "%s ", toAdd);
                    lengthOfSentence += lengthOfLast + 1; // +1 for space

                    //copy the word to the undo buffer
                    strcpy(undoBuffer, wordlist[indexToUse]);
                } 
            }
            refresh();
        }

        //x button press for undo
        if (xbutton == 1) {
            if (lengthOfSentence > 0) {
                //clear the last word
                mvprintw(rowCount, lengthOfSentence - lengthOfLast - 1, "%*s", lengthOfLast, "");
                lengthOfSentence -= lengthOfLast + 1; // -1 for space
            }
            refresh();
        }

        //square button press
        else if (square == 1) {
            int indexToUse = y * 5 + x;
            if (indexToUse >= 0 && indexToUse < wordCount) {
                lengthOfLast = strlen(wordlist[indexToUse]);
                char toAdd[WORDLENGTH];
                strcpy(toAdd, wordlist[indexToUse]);
                if (capitalizeNext) {
                    toAdd[0] -= 0x20;
                }
                if (lengthOfSentence + lengthOfLast < 80) {
                    mvprintw(rowCount, lengthOfSentence, "%s", toAdd);
                    lengthOfSentence += lengthOfLast;
                } 
            }
            refresh();
        }

        //circle button for capitalization
        else if (circle == 1) {
            if (capitalizeNext) {
                capitalizeNext = 0;
                mvprintw(rowCount + 1, 0, "    ");
            } else {
                capitalizeNext = 1;
                mvprintw(rowCount + 1, 0, "CAP");
            }
            refresh();
        }

        //right joystick button press to reset the sentence
        else if (joyPressR == 1) {
            lengthOfSentence = 0; // reset the sentence length
            mvprintw(rowCount, 0, "%*s", 80, ""); // lear the sentence
        }

        draw_cursor(x, y, AVATAR);
    }

    for (i = 0; i < wordCount; i++) {
        free(wordlist[i]);
    }


    endwin();
    return 0;
}

// DO NOT MODIFY THIS FUNCTION!
void trimws(char* str) {
    int length = strlen(str);
    int x;
    if (length == 0) return;
    x = length - 1;
    while (isspace(str[x]) && (x >= 0)) {
        str[x] = '\0';
        x -= 1;
    }
}
// DO NOT MODIFY THIS FUNCTION!
int read_words(char* WL[MAXWORDS], char* file_name) {
    int numread = 0;
    char line[WORDLENGTH];
    char *p;
    FILE* fp = fopen(file_name, "r");
    while (!feof(fp)) {
        p = fgets(line, WORDLENGTH, fp);
        if (p != NULL) {
            trimws(line);
            WL[numread] = (char *)malloc(strlen(line) + 1);
            strcpy(WL[numread], line);
            numread++;
        }
    }
    fclose(fp);
    return numread;
}

void draw_cursor(int x, int y, char use) {
    mvaddch(y, x * 15, use);
    refresh();
}
