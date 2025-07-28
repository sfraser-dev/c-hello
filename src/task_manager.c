#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <string.h>
#include <time.h>

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

void add_task(const char *desc, int priority, time_t deadline) {
    if (task_count >= MAX_TASKS) {
        printf("Task limit reached!\n");
        return;
    }
    tasks[task_count].id = task_count + 1;
    strncpy(tasks[task_count].description, desc, MAX_DESC - 1);
    tasks[task_count].description[MAX_DESC - 1] = '\0';
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
        time_str[strlen(time_str) - 1] = '\0'; // Remove newline
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
        printf("Error opening file for writing.\n");
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
    char command[10], desc[MAX_DESC];
    int id, priority;
    char date_str[20];
    struct tm tm = {0};
    time_t deadline;

    while (1) {
        printf("\nCommands: add (a), delete (d), list (l), complete (c), save (s), exit (e)\n");
        printf("Enter command: ");
        scanf("%9s", command);
        getchar(); // Clear newline
        char cmd = command[0];

        if (cmd == 'a') {
            printf("Description: ");
            fgets(desc, MAX_DESC, stdin);
            desc[strcspn(desc, "\n")] = '\0';

            printf("Priority (1-5): ");
            scanf("%d", &priority);
            getchar();

            printf("Deadline (YYMMDD): ");
            fgets(date_str, sizeof(date_str), stdin);
            date_str[strcspn(date_str, "\n")] = '\0';

            if (strptime(date_str, "%y%m%d", &tm) == NULL) {
                printf("Invalid date format (use YYMMDD).\n");
            } else {
                tm.tm_hour = 12; // Avoids midnight boundary issues
                deadline = mktime(&tm);
                add_task(desc, priority, deadline);
            }

        } else if (cmd == 'd') {
            printf("Task ID: ");
            scanf("%d", &id);
            getchar();
            delete_task(id);

        } else if (cmd == 'l') {
            list_tasks();

        } else if (cmd == 'c') {
            printf("Task ID: ");
            scanf("%d", &id);
            getchar();
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