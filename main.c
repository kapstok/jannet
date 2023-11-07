#include <stdio.h>
#include <stdlib.h>

#define ubyte char

void printLogo() {
  printf("    _____                   __    __            __\n");
  printf("   |     \\                 |  \\  |  \\          |  \\\n");
  printf("    \\▓▓▓▓▓ ______  _______ | ▓▓\\ | ▓▓ ______  _| ▓▓_\n");
  printf("      | ▓▓|      \\|       \\| ▓▓▓\\| ▓▓/      \\|   ▓▓ \\\n");
  printf(" __   | ▓▓ \\▓▓▓▓▓▓\\ ▓▓▓▓▓▓▓\\ ▓▓▓▓\\ ▓▓  ▓▓▓▓▓▓\\\\▓▓▓▓▓▓\n");
  printf("|  \\  | ▓▓/      ▓▓ ▓▓  | ▓▓ ▓▓\\▓▓ ▓▓ ▓▓    ▓▓ | ▓▓ __\n");
  printf("| ▓▓__| ▓▓  ▓▓▓▓▓▓▓ ▓▓  | ▓▓ ▓▓ \\▓▓▓▓ ▓▓▓▓▓▓▓▓ | ▓▓|  \\\n");
  printf(" \\▓▓    ▓▓\\▓▓    ▓▓ ▓▓  | ▓▓ ▓▓  \\▓▓▓\\▓▓     \\  \\▓▓  ▓▓\n");
  printf("  \\▓▓▓▓▓▓  \\▓▓▓▓▓▓▓\\▓▓   \\▓▓\\▓▓   \\▓▓ \\▓▓▓▓▓▓▓   \\▓▓▓▓\n");
}

int get_port() {
    char buffer[10];
    int port;
    int inputValid;

    do {
        printf("Voer poort in: ");
        fflush(stdout);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            // Handle EOF or error (e.g., when the user presses Ctrl+D)
            printf("Error reading input. Exiting.\n");
        }

        inputValid = sscanf(buffer, "%d", &port);
    } while (inputValid <= 0);

    return port;
}

char get_choice(char* prompt, char* choices) {
    char choice;
    ubyte inputValid = 0;

    do {
      printf(prompt);
      fflush(stdout);

      if (fgets(&choice, sizeof(&choice), stdin) == NULL) {
        // Handle EOF or error (e.g., when the user presses Ctrl+D)
        printf("Error reading input. Exiting.\n");
      }

      for (int i = 0; i < sizeof(choices); i++) {
        if (choices[i] == choice) {
          inputValid = 1;
          break;
        }
      }
    } while(!inputValid);

    return choice;
}

int main() {
  printf("\n---------------   .:: Welkom op het ::.   ---------------\n\n");
  printLogo();
  printf("\n---------------------------------------------------------\n\n");

  int port = get_port();
  ubyte listen = get_choice("Wil je [l]uisteren of [v]ersturen?", "lv") == 'l' ? 1 : 0;

  if (listen) {
    printf("Luisteren dus!\n");
  } else {
    printf("Versturen dus!\n");
  }
  fflush(stdout);
}