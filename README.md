# HostelCare — Hostel Maintenance Portal

A second-year student mini-project for hostel complaint management.

## Features
- Dashboard with total, pending, and resolved complaint counts
- Raise a complaint with room number, category, title, and description
- Search and filter complaint records
- Update complaint status
- Responsive layout for desktop and mobile
- Browser demo data persists in localStorage

## Files
- `web/index.html` — self-contained website (HTML, CSS, JavaScript)
- `c_program/hostel_maintenance.c` — standalone C implementation using a singly linked list

## Run the website
Open `web/index.html` in a modern browser. No server or package installation is needed.

The website stores demo records in the current browser's localStorage. The profile menu contains Student and Warden/Admin demo views, plus reset controls for sample data. These are presentation-only role views, not secure authentication or separate accounts. It does not execute the C program or synchronize data with it. Resolved complaints can be removed from the browser demo; a real hostel system should normally archive them for records instead of deleting them.

## Compile and run the C program

### Linux / macOS
```bash
cd c_program
gcc -std=c11 -Wall -Wextra -pedantic hostel_maintenance.c -o hostel_maintenance
./hostel_maintenance
```

### Windows (MinGW GCC)
```bat
cd c_program
gcc -std=c11 -Wall -Wextra -pedantic hostel_maintenance.c -o hostel_maintenance.exe
hostel_maintenance.exe
```

## Data structures used
- `struct Complaint` stores each complaint record.
- A singly linked list dynamically stores complaints.
- Search and status update traverse the linked list.
- `malloc()` allocates each complaint node; `free()` releases all nodes on exit.

## Scope note
The website and C console program are separate runnable parts. The browser uses JavaScript for the UI; the required complaint-management data structure is implemented independently in C.
