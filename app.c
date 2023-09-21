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
    char status[24]; // Collaborator *collaborators;
    struct tm created_at;
} Task;

// Functions declaration
int getChoise();
void addTask();
void displayTasks();
void displayTask();

// Constances

// Global variables
int tasks_length = 1, nextID = 1; // size of the tasks array // id for generate an ID automatically
Task *tasks;                      // ** pointer to tasks array ** //

// main
int main()
{
    int choise = 1;

    // allocate memory for the tasks pointer
    tasks = (Task *)calloc(tasks_length, (sizeof(Task)));
    if (!tasks)
    {
        // something to exit program
        printf("\n !!!!!!!!!!!!!! Server error !!!!!!!!!!!!!\n");
    };

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
            printf("\n\t\t\t How many tasks that you want to add ? : ");
            scanf("%d", &newTasks_number);
            addTask(newTasks_number);
            break;
        case 3:
            displayTasks();
            break;
        case 4:
            printf("Modifier une tache");
            break;
        case 5:
            printf("Supprimer une donnee par identifiant");
            break;
        case 6:
            printf("Rechercher les taches");
            break;
        case 7:
            printf("Statistiques");
            break;
        case 8:
            printf("Quitter");
            break;
        }
    }

    // Quit
    printf("\n\t A bientot.");

    // free pointer
    free(tasks);
    return 0;
}

// Functions definition

void displayTasks()
{
    int sortmethod;
    do
    {
        printf("\n\t L\'affichage par :\n"
               "\t\t\t 1 - Order alphabetique\n"
               "\t\t\t 2 - Par deadline\n"
               "\t\t\t 3 - Taches dont le deadline est dans 3 jours ou moins.\n"
               "---> Tapez votre choix : ");
        scanf("%d", &sortmethod);
        switch (sortmethod)
        {
        case 1:
            // if tasks is empty
            if (tasks_length - 1 == 0)
            {
                printf("\n\t\t\t\t No taches avilaible !\n");
                break;
            }

            // if not
            // sort by title
            for (int i = 0; i < tasks_length - 1; i++)
            {
                printf("\n\t\tid         : %d \n\t\ttitle      : %s \n\t\tdesc       : %s\n\t\tdeadline   : %d/%02d/%02d\n\t\tstatut     : %s\n\t\tcreated at : %d/%02d/%02d\n\t\t\t_______________________\n",
                       tasks[i].id, tasks[i].title, tasks[i].description,
                       tasks[i].deadline.tm_year, tasks[i].deadline.tm_mon, tasks[i].deadline.tm_mday,
                       tasks[i].status, tasks[i].created_at.tm_year, tasks[i].created_at.tm_mon, tasks[i].created_at.tm_mday);
            }

            break;
        case 2:
            printf("\n\t\t par deadline");
            break;
        case 3:
            printf("\n\t\t deadline est dans 3 jours ou moins.");
            break;

        default:
            printf("\n Triage choix Invalide");
            break;
        }
    } while (sortmethod < 1 || sortmethod > 3);
}

void addTask(int number)
{
    for(int i=0; i<number; i++){
        int year = 0, month = 0, day = 0;
        char title[40], description[200], status[24];
        struct tm deadline, created_at;

        // Input task arguments
        printf("\n\t\t Ajouter tache %d: \n \t\t\t Saisir titre : ", i);
        scanf_s("%39s", &title, sizeof(title)); // title      // add do while

        printf("\t\t\t Saisir description : ");
        scanf_s("%199s", &description, sizeof(description)); // description        // add do while

        printf("\t\t\t Saisir deadline (YYYY/mm/dd) : ");
        scanf("%d/%02d/%02d", &year, &month, &day); // deadline     // add do while
        deadline.tm_year = year;
        deadline.tm_mon = month;
        deadline.tm_mday = day;

        // you will need this is update
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
            } */

        strcpy(status, "A realiser");

        //
        time_t t = time(NULL);
        struct tm currentTime = *localtime(&t);
        created_at.tm_year = currentTime.tm_year + 1900;
        created_at.tm_mon = currentTime.tm_mon + 1;
        created_at.tm_mday = currentTime.tm_mday;

        // new Task struct
        /* Task newTask;
        newTask.id = nextID;
        strcpy(newTask.title, title);
        strcpy(newTask.description, description);
        newTask.deadline.tm_year = deadline.tm_year;
        newTask.deadline.tm_mon = deadline.tm_mon;
        newTask.deadline.tm_mday = deadline.tm_mday;
        strcpy(newTask.status, status);
        newTask.created_at.tm_year = created_at.tm_year;
        newTask.created_at.tm_mon = created_at.tm_mon;
        newTask.created_at.tm_mday = created_at.tm_mday; */

        // add new task to tasks array
        printf("--> id BEFORE = %d\n", tasks[tasks_length - 1].id);
        (tasks[tasks_length - 1]).id = nextID;
        printf("--> id AFTER = %d \n", tasks[tasks_length - 1].id);

        printf("title before affect = %s \n", tasks[tasks_length - 1].title);
        strcpy(tasks[tasks_length - 1].title, title);
        printf("title after affect = %s \n", tasks[tasks_length - 1].title);

        strcpy(tasks[tasks_length - 1].description, description);
        tasks[tasks_length - 1].deadline.tm_year = deadline.tm_year;
        tasks[tasks_length - 1].deadline.tm_mon = deadline.tm_mon;
        tasks[tasks_length - 1].deadline.tm_mday = deadline.tm_mday;
        strcpy(tasks[tasks_length - 1].status, status);
        tasks[tasks_length - 1].created_at.tm_year = created_at.tm_year;
        tasks[tasks_length - 1].created_at.tm_mon = created_at.tm_mon;
        tasks[tasks_length - 1].created_at.tm_mday = created_at.tm_mday;

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
    number == 1 ? printf("\n\t\t\tTask is added successfully.\n") : printf ("\n\t\t\tTask is added successfully.\n"); 
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

        scanf("%s\n", input);

        //fgets(input, sizeof(input), stdin); // get the input from user.

        // verify valide input
        if (! sscanf(input, "%d", &choise) || (choise < 1 || choise > 8))
            printf("\n\t\t-- Choix Invalide !! --");
        else
            break;
    };

    return choise;
}