#include <stdio.h>
#include "print.h"

void Display_Welcome_Message() {
    /*
    Shows initial message
    */

   printf("\n           _                                                   "
           "\n          (_)                                                  \n"
           " _ __ ___  _ _ __   ___  _____      _____  ___ _ __   ___ _ __ \n"
           "| '_ ` _ \\| | '_ \\ / _ \\/ __\\ \\ /\\ / / _ \\/ _ \\ '_ \\ / _ \\ '__|\n"
           "| | | | | | | | | |  __/\\__ \\\\ V  V /  __/  __/ |_) |  __/ |   \n"
           "|_| |_| |_|_|_| |_|\\___||___/ \\_/\\_/ \\___|\\___| .__/ \\___|_|   \n"
           "                                              | |              \n"
           "                                              |_|              \n\n");

    printf("Welcome to Minesweeper. Fork me at: https://github.com/apieceofCAKE/minesweeper_game\n");
}