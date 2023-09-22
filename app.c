/* Task Management Application
 *
 * Description:
 * This application provides a menu-driven interface for managing tasks.
 * Users can add, read, modify, delete, and search for tasks.
 * The application allows sorting tasks and provides statistics on tasks.
 *
 * Features:
 * - Add new tasks with unique identifiers, titles, descriptions, deadlines, collaborators, and statuse.
 * - Display a list of all tasks, sorted alphabetically or by deadline.
 * - Show tasks with deadlines within the next three days.
 * - Modify task details, including descriptions, statuses, and deadlines.
 * - Delete tasks by their unique identifiers.
 * - Search for tasks.
 * - View statistics, including the total number of tasks, completed and incomplete tasks, and days until task deadlines.
 *
 * Author: AIT TAMGHART Abdelghani
 * Date: 20/09/2023
 * ___________
 * [1] Ajouter une tache\n\t"
[2] Ajouter plusieur taches\n\t"
[3] Afficher la list de taches\n\t"
[4] Modifier une tache\n\t"
[5] Supprimer une donnee par identifiant\n\t"
[6] Rechercher les taches\n\t"
[7] Statistiques\n\t"
[8] Quitter\n\t"
 */

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structs
/* typedef struct
{
    char fname[20];
    char lname[20];
    char email[30];
} Collaborator; */

typedef struct
{
    int id;
    char title[40];
    char description[200];
    struct tm deadline;
    char status[24];
    struct tm created_at;
} Task;

// Functions declaration
int getIntInput();
int getChoise();
void addTask(int number);
int searchByID();
void displayTasks(int max_deadline);
void displayTask(Task task);
void sortByTitle();
void sortByDeadline();

void seeder();

// Constances

// Global variables
int tasks_length = 5; // size of the tasks array
int nextID = 5;       // id for generate an ID automatically
Task *tasks;          // ** pointer to tasks array ** //

// main
int main()
{
    // DATA TEST

    int choise = 1;

    // allocate memory for the tasks pointer
    tasks = (Task *)calloc(tasks_length, (sizeof(Task)));
    if (!tasks)
    {
        // something to exit program
        printf("\n !!!!!!!!!!!!!! Server error !!!!!!!!!!!!!\n");
    };

    seeder(); // data fir testing

    while (choise != 8)
    {
        choise = getChoise();
        switch (choise)
        {
        case 1:
            // Add one
            addTask(1);
            break;

        case 2:
            int newTasks_number;
            do
            {
                printf("\n\t\t\t How many tasks that you want to add ? : ");
                scanf("%d", &newTasks_number);
            } while (newTasks_number <= 0);

            // Add many
            addTask(newTasks_number);
            break;

        case 3:
            // if tasks is empty
            if (tasks_length - 1 == 0)
            {
                printf("\n\t\t\t\t No taches availible !\n");
            }

            // if is not
            int sortmethod;
            printf("\n\t L\'affichage par :\n"
                   "\t\t\t 1 - Order alphabetique\n"
                   "\t\t\t 2 - Par deadline\n"
                   "\t\t\t 3 - Taches dont le deadline est dans 3 jours ou moins.\n"
                   "\t\t\t 0 - Menu principale.\n");
            while (1)
            {
                printf("\n\t\t\t --> Tapez votre choix [1-3] : ");
                scanf("%d", &sortmethod);
                if (sortmethod >= 0 && sortmethod <= 3)
                    break;
                else
                    printf("\n !! choix invalide !!! \n");
            }

            switch (sortmethod)
            {
            case 0:
                printf("\t** menu principale !!\n");
                break;
            case 1:
                // sort by title
                sortByTitle();
                displayTasks(0);
                break;

            case 2:
                // sort by deadline
                sortByDeadline();
                displayTasks(0);
                break;

            case 3:
                // dead line de 3 jours ou moin
                displayTasks(3);
                break;
            }
            break;
        case 4:
            printf("Modifier une tache");
            break;

        case 5:
            printf("Supprimer une donnee par identifiant");
            break;

        case 6:
        {
            // switch search byId / byTitle 

            int search_id;
            while (1)
            {
                // get the input from user.
                printf("\n\t\tSaisir l\'identifiant : ");
                search_id = getIntInput();
                // verify valide input
                if (search_id < 1)
                    printf("\n\t\t-- Saisie Invalide !! --\n");
                else
                    break;
            }

            int index = searchByID(search_id);
            index != -1 ? displayTask(tasks[index]) : printf("No tache avec ce identifiant !\n");

            break;
        }
        case 7:
        {
            printf("Statistiques");
            break;
        }
        case 8:
        {
            printf("Quitter");
            break;
        }
        }
    }

    // free pointer
    free(tasks);

    // Quit
    printf("\n\t A bientot.");

    return 0;
}

// Functions definition

// done
void seeder()
{
    char str[13];
    time_t t = time(NULL);
    struct tm currentTime = *localtime(&t);

    // task 1
    tasks[0].id = 3;
    strcpy(tasks[0].title, "task : a week up");
    strcpy(tasks[0].description, "description task 3");

    tasks[0].deadline.tm_year = 2023 - 1900;
    tasks[0].deadline.tm_mon = 9 - 1;
    tasks[0].deadline.tm_mday = 22;

    tasks[0].deadline.tm_hour = 17;
    tasks[0].deadline.tm_min = 35;
    tasks[0].deadline.tm_sec = 25;

    strcpy(tasks[0].status, "A realiser");

    tasks[0].created_at.tm_year = 2023 - 1900;
    tasks[0].created_at.tm_mon = 9 - 1;
    tasks[0].created_at.tm_mday = 21;

    tasks[0].created_at.tm_hour = 12;
    tasks[0].created_at.tm_min = 35;
    tasks[0].created_at.tm_sec = 25;

    // task 2
    tasks[1].id = 2;
    strcpy(tasks[1].title, "task : C have breakfast");
    strcpy(tasks[1].description, "description task 2");

    tasks[1].deadline.tm_year = 2023 - 1900;
    tasks[1].deadline.tm_mon = 9 - 1;
    tasks[1].deadline.tm_mday = 24;

    tasks[1].deadline.tm_hour = 12;
    tasks[1].deadline.tm_min = 35;
    tasks[1].deadline.tm_sec = 25;

    strcpy(tasks[1].status, "En cours de realisation");

    tasks[1].created_at.tm_year = 2023 - 1900;
    tasks[1].created_at.tm_mon = 9 - 1;
    tasks[1].created_at.tm_mday = 21;

    tasks[1].created_at.tm_hour = 9;
    tasks[1].created_at.tm_min = 45;
    tasks[1].created_at.tm_sec = 25;

    // task3
    tasks[2].id = 4;
    strcpy(tasks[2].title, "task : A morning training");
    strcpy(tasks[2].description, "description task 4");

    tasks[2].deadline.tm_year = 2023 - 1900;
    tasks[2].deadline.tm_mon = 10 - 1;
    tasks[2].deadline.tm_mday = 7;

    tasks[2].deadline.tm_hour = 12;
    tasks[2].deadline.tm_min = 35;
    tasks[2].deadline.tm_sec = 25;

    strcpy(tasks[2].status, "Finisee");

    tasks[2].created_at.tm_year = 2023 - 1900;
    tasks[2].created_at.tm_mon = 9 - 1;
    tasks[2].created_at.tm_mday = 29;

    tasks[2].created_at.tm_hour = 22;
    tasks[2].created_at.tm_min = 45;
    tasks[2].created_at.tm_sec = 35;

    // task 4
    tasks[3].id = 1;
    strcpy(tasks[3].title, "task : c kassi kasaka");
    strcpy(tasks[3].description, "description task 1");

    tasks[3].deadline.tm_year = 2023 - 1900;
    tasks[3].deadline.tm_mon = 9 - 1;
    tasks[3].deadline.tm_mday = 23;

    tasks[3].deadline.tm_hour = 12;
    tasks[3].deadline.tm_min = 35;
    tasks[3].deadline.tm_sec = 25;

    strcpy(tasks[3].status, "A realiser");

    tasks[3].created_at.tm_year = 2023 - 1900;
    tasks[3].created_at.tm_mon = 9 - 1;
    tasks[3].created_at.tm_mday = 21;

    tasks[3].created_at.tm_hour = 23;
    tasks[3].created_at.tm_min = 45;
    tasks[3].created_at.tm_sec = 55;
}

// done
int searchByID(int id)
{
    for (int i = 0; i < tasks_length - 1; i++)
    {
        if (tasks[i].id == id)
            return i;
    }
    return -1;
}

// done
void sortByDeadline()
{
    int min_pos;
    Task taskTMP;
    time_t current_t = time(NULL);

    for (int i = 0; i < tasks_length - 2; i++)
    {
        // task[i] deadAfter
        long long int i_deadAfter = mktime(&tasks[i].deadline) - current_t;

        min_pos = i + 1;

        for (int j = i + 1; j < tasks_length - 1; j++)
        {
            long long int j_deadAfter = mktime(&tasks[j].deadline) - current_t;
            if (j_deadAfter < (mktime(&tasks[min_pos].deadline) - current_t))
            {
                min_pos = j;
            }
        }

        if (i_deadAfter > (mktime(&tasks[min_pos].deadline) - current_t))
        {
            memcpy(&taskTMP, &tasks[i], sizeof(Task));
            memcpy(&tasks[i], &tasks[min_pos], sizeof(Task));
            memcpy(&tasks[min_pos], &taskTMP, sizeof(Task));
        }
    }
}

// done
void sortByTitle()
{
    int min_pos;
    Task taskTMP;
    for (int i = 0; i < tasks_length - 2; i++)
    {
        min_pos = i + 1;
        for (int j = i + 1; j < tasks_length - 1; j++)
        {
            if (strcmp(tasks[j].title, tasks[min_pos].title) < 0)
            {
                min_pos = j;
            }
        }
        if (strcmp(tasks[i].title, tasks[min_pos].title) > 0)
        {
            memcpy(&taskTMP, &tasks[i], sizeof(Task));
            memcpy(&tasks[i], &tasks[min_pos], sizeof(Task));
            memcpy(&tasks[min_pos], &taskTMP, sizeof(Task));
        }
    }

    /*
    for (int i = 0; i < 9; i++)
    {
        min_pos = i + 1;
        for (int j = i + 1; j < 10; j++)
        {
            if (myArray[j] < myArray[min_pos])
            {
                min_pos = j;
            }
        }
        // change the first element that loop(i) starts with, with value of min if its less
        printf("\n ******* i = %d : min = %d\n", i, myArray[min_pos]);
        if (myArray[i] > myArray[min_pos])
        {
            myArray[i] = myArray[i] + myArray[min_pos];
            myArray[min_pos] = myArray[i] - myArray[min_pos];
            myArray[i] = myArray[i] - myArray[min_pos];
        }
    }
     */
}

// doing
void displayTask(Task task)
{
    char deadlineSTR[40], createdAtSTR[40];
    int day, hour, min;

    // Format date
    strftime(deadlineSTR, 40, "%m/%d/%Y %H:%M:%S", &(task.deadline));
    strftime(createdAtSTR, 40, "%m/%d/%Y %H:%M:%S", &(task.created_at));

    // deadAfter
    time_t current_t = time(NULL);
    time_t inDead = mktime(&task.deadline);

    long long int deadAfter = inDead - current_t;

    // Time representation
    day = (int)(deadAfter / (3600 * 24));
    hour = (int)((deadAfter % (3600 * 24)) / 3600);
    min = (int)((deadAfter % (3600)) / 60);

    printf("\n\t\tid         : %d"
           "\n\t\ttitle      : %s"
           "\n\t\tdesc       : %s"
           "\n\t\tstatut     : %s"
           "\n\t\tdeadline   : %s"
           "\n\t\tcreated at : %s"
           "\n\t\tdead after : %d jours %d heurs %d min"
           "\n\t\t\t_______________________\n",
           task.id, task.title, task.description,
           task.status, deadlineSTR, createdAtSTR, day, hour, min);
}

// done
void displayTasks(int max_deadline_days)
{
    for (int i = 0; i < tasks_length - 1; i++)
    {
        char deadlineSTR[40], createdAtSTR[40];
        int day, hour, min;

        // Format date
        strftime(deadlineSTR, 40, "%m/%d/%Y %H:%M:%S", &(tasks[i].deadline));
        strftime(createdAtSTR, 40, "%m/%d/%Y %H:%M:%S", &(tasks[i].created_at));

        // deadAfter
        time_t current_t = time(NULL);
        time_t inDead = mktime(&tasks[i].deadline);

        long long int deadAfter = inDead - current_t;

        // Time representation
        day = (int)(deadAfter / (3600 * 24));
        hour = (int)((deadAfter % (3600 * 24)) / 3600);
        min = (int)((deadAfter % (3600)) / 60);

        if (max_deadline_days == 0)
        {
            printf("\n\t\tid         : %d"
                   "\n\t\ttitle      : %s"
                   "\n\t\tdesc       : %s"
                   "\n\t\tstatut     : %s"
                   "\n\t\tdeadline   : %s"
                   "\n\t\tcreated at : %s"
                   "\n\t\tdead after : %d jours %d heurs %d min"
                   "\n\t\t\t_______________________\n",
                   tasks[i].id, tasks[i].title, tasks[i].description,
                   tasks[i].status, deadlineSTR, createdAtSTR, day, hour, min);
        }
        else if (deadAfter <= (max_deadline_days * 24 * 3600))
        {
            printf("\n\t\tid         : %d"
                   "\n\t\ttitle      : %s"
                   "\n\t\tdesc       : %s"
                   "\n\t\tstatut     : %s"
                   "\n\t\tdeadline   : %s"
                   "\n\t\tcreated at : %s"
                   "\n\t\tdead after : %d jours %d heurs %d min"
                   "\n\t\t\t_______________________\n",
                   tasks[i].id, tasks[i].title, tasks[i].description,
                   tasks[i].status, deadlineSTR, createdAtSTR, day,
                   hour, min);
        }
    }
}

// handle input
void addTask(int number)
{
    for (int i = 0; i < number; i++)
    {
        int year = 0, month = 0, day = 0;
        char title[40], description[200], status[24];
        struct tm deadline, created_at;

        // title
        do
        {
            printf("\n\t\t Ajouter tache %d: \n \t\t\t Saisir titre : ", i + 1);
            fgets(title, sizeof(title), stdin);
            if (strlen(title) > 0)
                title[strlen(title) - 1] = '\0';
            else
                printf("title invalide !");
        } while (strlen(title) <= 4);

        // description
        do
        {
            printf("\t\t\t Saisir description : ");
            fgets(description, sizeof(description), stdin);
            int len = strlen(description);
            if (len > 4)
                description[len - 1] = '\0';
            else
                printf("description invalide !");
        } while (strlen(description) <= 4);

        // deadline year month and day
        printf("\t\t\t Saisir deadline (YYYY/mm/dd) : ");
        scanf("%d/%02d/%02d", &year, &month, &day); // add do while
        deadline.tm_year = year - 1900;
        deadline.tm_mon = month - 1;
        deadline.tm_mday = day;

        // status 'to do' by default
        strcpy(status, "A realiser");

        // created_at
        time_t t = time(NULL);
        struct tm currentTime = *localtime(&t);
        created_at.tm_year = currentTime.tm_year;
        created_at.tm_mon = currentTime.tm_mon;
        created_at.tm_mday = currentTime.tm_mday;
        created_at.tm_hour = currentTime.tm_hour;
        created_at.tm_min = currentTime.tm_min;
        created_at.tm_sec = currentTime.tm_sec;

        // deadline hour min and second
        deadline.tm_hour = currentTime.tm_hour;
        deadline.tm_min = currentTime.tm_min;
        deadline.tm_sec = currentTime.tm_sec;

        // add new task to tasks array
        tasks[tasks_length - 1].id = nextID; // ID

        strcpy(tasks[tasks_length - 1].title, title); // Title

        strcpy(tasks[tasks_length - 1].description, description); // Description

        tasks[tasks_length - 1].deadline.tm_year = deadline.tm_year; // deadline
        tasks[tasks_length - 1].deadline.tm_mon = deadline.tm_mon;
        tasks[tasks_length - 1].deadline.tm_mday = deadline.tm_mday;
        tasks[tasks_length - 1].deadline.tm_hour = deadline.tm_hour;
        tasks[tasks_length - 1].deadline.tm_min = deadline.tm_min;
        tasks[tasks_length - 1].deadline.tm_sec = deadline.tm_sec;

        strcpy(tasks[tasks_length - 1].status, status); // status

        tasks[tasks_length - 1].created_at.tm_year = created_at.tm_year; // created at
        tasks[tasks_length - 1].created_at.tm_mon = created_at.tm_mon;
        tasks[tasks_length - 1].created_at.tm_mday = created_at.tm_mday;
        tasks[tasks_length - 1].created_at.tm_hour = created_at.tm_hour;
        tasks[tasks_length - 1].created_at.tm_min = created_at.tm_min;
        tasks[tasks_length - 1].created_at.tm_sec = created_at.tm_sec;

        // Increment id
        nextID++;

        // increment length
        tasks_length++;

        // add memory to array pointer
        tasks = (Task *)realloc(tasks, tasks_length * sizeof(Task));
        if (!tasks)
        {
            printf("\n !!!!!!!!!!!!!! Server error !!!!!!!!!!!!!\n");
            // quit
        }
    }

    // message
    number == 1 ? printf("\n\t\t\tTask is added successfully.\n") : printf("\n\t\t\tTasks is added successfully.\n");
}

// handle input
int getChoise()
{
    char input[20];
    int choise = 0;

    while (1)
    {
        printf("\n\n\t===============================================\n\t"
               "\tMenu d\'application\n\t"
               "===============================================\n\t"
               "\t[1] Ajouter une tache\n\t"
               "\t[2] Ajouter plusieur taches\n\t"
               "\t[3] Afficher la list de taches\n\t"
               "\t[4] Modifier une tache\n\t"
               "\t[5] Supprimer une donnee par identifiant\n\t"
               "\t[6] Rechercher les taches\n\t"
               "\t[7] Statistiques\n\t"
               "\t[8] Quitter\n\t"
               "===============================================\n\t"
               "\n\tTapez votre choix [0-8] : ");

        // get the input from user.
        choise = getIntInput();
        if (choise != 404 && choise >= 1 && choise <= 8)
        {
            break;
        }
        else
        {
            printf("\n\t\t-- Saisie Invalide !! --");
        }

        /* fgets(input, sizeof(input), stdin);
        int len = strlen(input);
        if (input[len - 1] == '\n')
            input[len - 1] = '\0';

        // verify valide input
        if (!sscanf(input, "%d", &choise) || (choise < 1 || choise > 8))
            printf("\n\t\t-- Choix Invalide !! --");
        else
            break; */
    };

    return choise;
}

// done
int getIntInput()
{
    char input[10];
    int choise;
    fgets(input, sizeof(input), stdin);
    int len = strlen(input);
    if (input[len - 1] == '\n')
        input[len - 1] = '\0';

    // verify valide input
    if (sscanf(input, "%d", &choise))
        return choise;
    else
        return 404;
}

// some things to return to
/*
            printf("\t\t\t Statut : \n"
                    "\t\t\t\t   1. A realiser\n"
                    "\t\t\t\t   2. En cours de realisation\n"
                    "\t\t\t\t   3. Finalisee\n"
                    "\t\t\t\t   \t\tChoisir statut : "
                    );

            scanf("%d", &status_number);   // add do while
            // add do while

            switch (status_number)
            {
            case 1:
                strcpy(status, "A realiser");
                printf("\n --> Statut : %s", status);
                break;

            case 2:
                strcpy(status, "En cours de realisation");
                printf("\n --> Statut : %s", status);
                break;

            case 3:
                strcpy(status, "Finalisee");
                printf("\n --> Statut : %s", status);
                break;

            default :
                printf("default switch status number");
            }
            __________________________________________________________

Task newTask;
        newTask.id = nextID;
        strcpy(newTask.title, title);
        strcpy(newTask.description, description);
        newTask.deadline.tm_year = deadline.tm_year;
        newTask.deadline.tm_mon = deadline.tm_mon;
        newTask.deadline.tm_mday = deadline.tm_mday;
        strcpy(newTask.status, status);
        newTask.created_at.tm_year = created_at.tm_year;
        newTask.created_at.tm_mon = created_at.tm_mon;
        newTask.created_at.tm_mday = created_at.tm_mday;


*/