#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

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
      exit(EXIT_FAILURE);
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
      exit(EXIT_FAILURE);
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

// Address needs to be free'd.
char* get_address() {
  char* buffer = malloc(sizeof(char) * 512);

  scanf("%s", buffer);
  return buffer;
}

void send_http(char* buffer, int bufsize) {
  printf("Welke methode wil je aanroepen?\n");
  fflush(stdout);
  char method[10];
  if (fgets(method, sizeof(method) - 1, stdin) == NULL) {
    // Handle EOF or error (e.g., when the user presses Ctrl+D)
    printf("Error reading input. Exiting.\n");
    exit(EXIT_FAILURE);
  } else {
    // Remove the newline character if it exists
    size_t length = strlen(method);
    if (length > 0 && method[length - 1] == '\n') {
      method[length - 1] = ' ';
    }
  }
  strcat(buffer, method);

  printf("Wat is de URL (Protocol, hostname en port achterwege laten)?\n");
  fflush(stdout);
  char url[100];
  if (fgets(url, sizeof(url) - 1, stdin) == NULL) {
    // Handle EOF or error (e.g., when the user presses Ctrl+D)
    printf("Error reading input. Exiting.\n");
    exit(EXIT_FAILURE);
  } else {
    // Remove the newline character if it exists
    size_t length = strlen(url);
    if (length > 0 && url[length - 1] == '\n') {
      url[length - 1] = ' ';
    }
  }
  strcat(buffer, url);
  strcat(buffer, " HTTP/1.0\nHost: localhost\n\n\n");
}

void setup_client(const char* address, int port) {
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;

    ubyte sendHttp = get_choice("Wil je een [t]cp of [h]ttp bericht sturen?", "th") == 'h' ? 1:0;
    char* message = malloc(sizeof(char) * 512);
    if (sendHttp) {
      send_http(message, 512);
    } else {
      scanf("%s", message);
    }
    
    char buffer[1024] = { 0 };
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
 
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    printf("Adres: (%s)\n", address);
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }
 
    if ((status
         = connect(client_fd, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(client_fd, message, strlen(message), 0);
    // free(message);
    printf("Verzonden bericht:\n%s\n\n---\n\nBinnenkomend:\n", message);
    free(message);
    valread = read(client_fd, buffer, 1024 - 1); // subtract 1 for the null terminator at the end
    printf("%s\n", buffer);
 
    // closing the connected socket
    close(client_fd);
    return 0;
}

void setup_server(int port) {
  int server_fd, sock;
  int opt = 1;
  struct sockaddr_in address;
  socklen_t addrlen = sizeof(address);
  char buffer[1024] = { 0 };

  // Creating socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      perror("socket failed");
      exit(EXIT_FAILURE);
  }

  // Set port and options
  int optionsSet = setsockopt(
    server_fd, SOL_SOCKET,
    SO_REUSEADDR | SO_REUSEPORT,
    &opt, sizeof(opt)
  );
  if (optionsSet == -1) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  // Bind file descriptor to socket
  if (bind(server_fd, (struct sockaddr*) &address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }
  if ((sock = accept(server_fd, (struct sockaddr*) &address, &addrlen)) < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  // Listen, then send
  read(sock, buffer, 1024 - 1); // subtract 1 from buffer length for the null terminator at the end
  printf("Binnenkomend bericht: %s\n", buffer);
  const char* hello = "Hallo vanaf de server! 👋";
  send(sock, hello, strlen(hello), 0);
  printf("Hello message sent\n");

  close(sock);
  close(server_fd);
}

int main() {
  printf("\n---------------   .:: Welkom op het ::.   ---------------\n\n");
  printLogo();
  printf("\n---------------------------------------------------------\n\n");

  int port = get_port();
  ubyte isClient = get_choice("Wil je [c]lient of [s]erver zijn? ", "cs") == 'c' ? 1 : 0;

  if (isClient) {
    printf("Een client dus!\n");
    printf("Naar welk adres wil je toe verbinden? ");
  } else {
    printf("Een server dus!\n");
  }
  fflush(stdout);

  if (isClient) {
    char* address = get_address();
    setup_client(address, port);
    free(address);
  } else {
    setup_server(port);
  }
}