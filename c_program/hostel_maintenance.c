/*
 * Hostel Maintenance Portal - Data Structures Mini Project
 * Language: C
 * Data structure: Singly linked list
 *
 * Compile: gcc hostel_maintenance.c -o hostel_maintenance
 * Run:     ./hostel_maintenance       (Linux/macOS)
 *          hostel_maintenance.exe     (Windows)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CATEGORY_LEN 32
#define TITLE_LEN 80
#define DESC_LEN 240
#define STATUS_LEN 20
#define DATE_LEN 16
#define ROOM_LEN 16

typedef struct Complaint {
    int id;
    char room[ROOM_LEN];
    char category[CATEGORY_LEN];
    char title[TITLE_LEN];
    char description[DESC_LEN];
    char date[DATE_LEN];
    char status[STATUS_LEN];
    struct Complaint *next;
} Complaint;

static Complaint *head = NULL;
static int next_id = 1006;

void read_line(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) { }
    }
}

int read_int(const char *prompt) {
    char buffer[64], *end;
    long value;
    for (;;) {
        read_line(prompt, buffer, sizeof(buffer));
        value = strtol(buffer, &end, 10);
        while (isspace((unsigned char)*end)) end++;
        if (buffer[0] != '\0' && *end == '\0' && value >= 0 && value <= 2147483647L)
            return (int)value;
        puts("Please enter a valid non-negative number.");
    }
}

Complaint *find_by_id(int id) {
    Complaint *current = head;
    while (current != NULL) {
        if (current->id == id) return current;
        current = current->next;
    }
    return NULL;
}

void insert_complaint(void) {
    Complaint *node = malloc(sizeof(*node));
    if (node == NULL) {
        puts("Error: not enough memory to add complaint.");
        return;
    }
    node->id = next_id++;
    read_line("Room number: ", node->room, sizeof(node->room));
    read_line("Category (Electrical/Plumbing/Cleaning/Furniture/Other): ",
              node->category, sizeof(node->category));
    read_line("Complaint title: ", node->title, sizeof(node->title));
    read_line("Description: ", node->description, sizeof(node->description));
    read_line("Date (YYYY-MM-DD): ", node->date, sizeof(node->date));
    if (node->room[0] == '\0' || node->category[0] == '\0' ||
        node->title[0] == '\0' || node->description[0] == '\0') {
        puts("Required fields cannot be empty. Complaint was not saved.");
        free(node);
        next_id--;
        return;
    }
    strcpy(node->status, "Pending");
    node->next = NULL;

    if (head == NULL) {
        head = node;
    } else {
        Complaint *current = head;
        while (current->next != NULL) current = current->next;
        current->next = node;
    }
    printf("Complaint HC-%d added successfully.\n", node->id);
}

void display_complaints(void) {
    Complaint *current = head;
    if (current == NULL) {
        puts("No complaints found.");
        return;
    }
    printf("\n%-9s %-8s %-13s %-22s %-12s %-12s\n",
           "ID", "Room", "Category", "Title", "Date", "Status");
    puts("-------------------------------------------------------------------------------");
    while (current != NULL) {
        printf("HC-%-6d %-8s %-13.13s %-22.22s %-12.12s %-12s\n",
               current->id, current->room, current->category,
               current->title, current->date, current->status);
        current = current->next;
    }
}

void search_by_id(void) {
    int id = read_int("Enter complaint number (e.g. 1001): ");
    Complaint *c = find_by_id(id);
    if (c == NULL) {
        puts("Complaint not found.");
        return;
    }
    printf("\nID: HC-%d\nRoom: %s\nCategory: %s\nTitle: %s\nDescription: %s\nDate: %s\nStatus: %s\n",
           c->id, c->room, c->category, c->title, c->description, c->date, c->status);
}

void search_by_room(void) {
    char room[ROOM_LEN];
    int found = 0;
    read_line("Enter room number: ", room, sizeof(room));
    Complaint *current = head;
    while (current != NULL) {
        if (strcmp(current->room, room) == 0) {
            printf("HC-%d | Room %s | %s | %s | %s\n",
                   current->id, current->room, current->title,
                   current->category, current->status);
            found = 1;
        }
        current = current->next;
    }
    if (!found) puts("No complaints found for that room.");
}

void update_status(void) {
    int id = read_int("Enter complaint number to update: ");
    Complaint *c = find_by_id(id);
    if (c == NULL) {
        puts("Complaint not found.");
        return;
    }
    puts("1. Pending\n2. In Progress\n3. Resolved");
    int choice = read_int("Choose new status: ");
    switch (choice) {
        case 1: strcpy(c->status, "Pending"); break;
        case 2: strcpy(c->status, "In Progress"); break;
        case 3: strcpy(c->status, "Resolved"); break;
        default: puts("Invalid status choice."); return;
    }
    puts("Complaint status updated successfully.");
}

void free_all(void) {
    Complaint *current = head;
    while (current != NULL) {
        Complaint *next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}

void add_sample(const char *room, const char *category, const char *title,
                const char *description, const char *date, const char *status) {
    Complaint *node = malloc(sizeof(*node));
    if (node == NULL) return;
    node->id = next_id - 5;
    /* IDs are set in main for a short sample list. */
    strncpy(node->room, room, sizeof(node->room)-1);
    node->room[sizeof(node->room)-1] = '\0';
    strncpy(node->category, category, sizeof(node->category)-1);
    node->category[sizeof(node->category)-1] = '\0';
    strncpy(node->title, title, sizeof(node->title)-1);
    node->title[sizeof(node->title)-1] = '\0';
    strncpy(node->description, description, sizeof(node->description)-1);
    node->description[sizeof(node->description)-1] = '\0';
    strncpy(node->date, date, sizeof(node->date)-1);
    node->date[sizeof(node->date)-1] = '\0';
    strncpy(node->status, status, sizeof(node->status)-1);
    node->status[sizeof(node->status)-1] = '\0';
    node->next = NULL;
    if (head == NULL) head = node;
    else {
        Complaint *current = head;
        while (current->next != NULL) current = current->next;
        current->next = node;
    }
}

void load_samples(void) {
    add_sample("204", "Plumbing", "Bathroom tap leakage",
               "Water is leaking continuously from the bathroom tap.",
               "2026-10-07", "Pending");
    add_sample("108", "Electrical", "Room light not working",
               "The main light is flickering and sometimes turns off.",
               "2026-10-06", "In Progress");
    add_sample("312", "Furniture", "Broken study chair",
               "One leg of the study chair is loose.",
               "2026-10-05", "Resolved");
    add_sample("221", "Cleaning", "Common area cleaning",
               "The corridor near the room needs cleaning.",
               "2026-10-04", "Pending");
    add_sample("115", "Plumbing", "Wash basin drain blocked",
               "Water is draining very slowly from the wash basin.",
               "2026-10-03", "Resolved");
    int id = 1001;
    for (Complaint *c = head; c != NULL; c = c->next) c->id = id++;
    next_id = 1006;
}

int main(void) {
    load_samples();
    int choice;
    do {
        puts("\n===================================");
        puts("     HOSTEL MAINTENANCE PORTAL");
        puts("===================================");
        puts("1. Add new complaint");
        puts("2. Display all complaints");
        puts("3. Search by complaint ID");
        puts("4. Search by room number");
        puts("5. Update complaint status");
        puts("0. Exit");
        choice = read_int("Enter your choice: ");
        switch (choice) {
            case 1: insert_complaint(); break;
            case 2: display_complaints(); break;
            case 3: search_by_id(); break;
            case 4: search_by_room(); break;
            case 5: update_status(); break;
            case 0: free_all(); puts("All allocated memory released. Goodbye!"); break;
            default: puts("Invalid choice. Please choose 0-5.");
        }
    } while (choice != 0);
    return 0;
}
