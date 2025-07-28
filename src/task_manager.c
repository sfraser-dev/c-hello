#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_TASKS 100
#define MAX_DESC 256
#define FILENAME "tasks.txt"

typedef struct {
    int id;
    char description[MAX_DESC];
    int priority; // 1 (low) to 5 (high)
    time_t deadline;
    int completed;
} Task;

Task tasks[MAX_TASKS];
int task_count = 0;

void trim_newline(char *s) {
    s[strcspn(s, "\n")] = '\0';
}

void add_task(const char *desc, int priority, time_t deadline) {
    if (task_count >= MAX_TASKS) {
        printf("Task limit reached!\n");
        return;
    }
    tasks[task_count].id = task_count + 1;
    snprintf(tasks[task_count].description, MAX_DESC, "%s", desc);
    tasks[task_count].priority = (priority < 1 || priority > 5) ? 3 : priority;
    tasks[task_count].deadline = deadline;
    tasks[task_count].completed = 0;
    task_count++;
    printf("Task added: %s\n", desc);
}

void delete_task(int id) {
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].id == id) {
            for (int j = i; j < task_count - 1; j++) {
                tasks[j] = tasks[j + 1];
                tasks[j].id = j + 1;
            }
            task_count--;
            printf("Task %d deleted.\n", id);
            return;
        }
    }
    printf("Task %d not found.\n", id);
}

void list_tasks() {
    if (task_count == 0) {
        printf("No tasks.\n");
        return;
    }
    for (int i = 0; i < task_count; i++) {
        char time_str[26];
        ctime_r(&tasks[i].deadline, time_str);
        trim_newline(time_str);
        printf("ID: %d, Desc: %s, Priority: %d, Deadline: %s, %s\n",
               tasks[i].id, tasks[i].description, tasks[i].priority, time_str,
               tasks[i].completed ? "Completed" : "Pending");
    }
}

void mark_completed(int id) {
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].id == id) {
            tasks[i].completed = 1;
            printf("Task %d marked as completed.\n", id);
            return;
        }
    }
    printf("Task %d not found.\n", id);
}

void save_tasks() {
    FILE *fp = fopen(FILENAME, "w");
    if (!fp) {
        perror("Error opening file for writing");
        return;
    }
    for (int i = 0; i < task_count; i++) {
        fprintf(fp, "%d|%s|%d|%ld|%d\n",
                tasks[i].id, tasks[i].description, tasks[i].priority,
                tasks[i].deadline, tasks[i].completed);
    }
    fclose(fp);
    printf("Tasks saved.\n");
}

void load_tasks() {
    FILE *fp = fopen(FILENAME, "r");
    if (!fp) {
        printf("No task file found.\n");
        return;
    }
    char line[512];
    task_count = 0;
    while (fgets(line, sizeof(line), fp) && task_count < MAX_TASKS) {
        if (sscanf(line, "%d|%255[^|]|%d|%ld|%d",
                   &tasks[task_count].id, tasks[task_count].description,
                   &tasks[task_count].priority, &tasks[task_count].deadline,
                   &tasks[task_count].completed) == 5) {
            task_count++;
        }
    }
    fclose(fp);
    printf("Tasks loaded.\n");
}

int main() {
    load_tasks();
    char command[20], desc[MAX_DESC];
    int id, priority;
    char date_str[20];
    struct tm tm;

    while (1) {
        printf("\nCommands: add (a), delete (d), list (l), complete (c), save (s), exit (e)\n");
        printf("Enter command: ");
        if (!fgets(command, sizeof(command), stdin)) {
            printf("Error reading command.\n");
            continue;
        }
        trim_newline(command);
        char cmd = command[0];

        if (cmd == 'a') {
            printf("Description: ");
            if (!fgets(desc, sizeof(desc), stdin)) {
                printf("Error reading description.\n");
                continue;
            }
            desc[MAX_DESC - 1] = '\0';
            trim_newline(desc);

            printf("Priority (1-5): ");
            if (scanf("%d", &priority) != 1) {
                printf("Invalid priority.\n");
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n'); // clear input

            printf("Deadline (YYMMDD): ");
            if (!fgets(date_str, sizeof(date_str), stdin)) {
                printf("Error reading deadline.\n");
                continue;
            }
            trim_newline(date_str);
            memset(&tm, 0, sizeof(struct tm));
            tm.tm_isdst = -1;

            if (strptime(date_str, "%y%m%d", &tm) == NULL) {
                printf("Invalid date format (use YYMMDD).\n");
            } else {
                tm.tm_hour = 12; // midday to avoid DST edge cases
                time_t deadline = mktime(&tm);
                if (deadline == -1) {
                    printf("Invalid date.\n");
                } else {
                    add_task(desc, priority, deadline);
                }
            }

        } else if (cmd == 'd') {
            printf("Task ID: ");
            if (scanf("%d", &id) != 1) {
                printf("Invalid ID.\n");
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n');
            delete_task(id);

        } else if (cmd == 'l') {
            list_tasks();

        } else if (cmd == 'c') {
            printf("Task ID: ");
            if (scanf("%d", &id) != 1) {
                printf("Invalid ID.\n");
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n');
            mark_completed(id);

        } else if (cmd == 's') {
            save_tasks();

        } else if (cmd == 'e') {
            save_tasks();
            break;

        } else {
            printf("Unknown command.\n");
        }
    }

    return 0;
}