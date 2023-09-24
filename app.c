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

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

/* Structs */
typedef struct
{
    int id;
    char title[40];
    char description[200];
    struct tm deadline;
    char status[24];
    struct tm created_at;
} Task;

/* Functions declaration */
int saveTasks();
int isNumber();
int getIntInput();
int getChoise();
int isIn_STR();
int addTask();
int updateTask();
int displayTask();
int displayTasks();
void sortByTitle();
void sortByDeadline();
void searchByTitle();
int searchByID();
int deleteTask();
int getDoneTasksNumber();
void displayDoneTasks();
void displayNonDoneTasks();
void seeder();

/* Constances */

/* Global variables */
int tasks_length = 5; // size of the tasks array
int nextID = 5;       // generate an ID automatically
Task *tasks;          // ** pointer to tasks array ** //

/* main */
int main()
{
    int choise = 1;

    // allocate memory for the tasks pointer
    tasks = (Task *)calloc(tasks_length, (sizeof(Task)));
    if (!tasks)
    {
        // something to exit program
        printf("\n\033[31m !!!!!!!!!!!!!! Server error !!!!!!!!!!!!! \033[0m\n");
    };

    // Data for testing
    seeder();

    while (choise != 8)
    {
        choise = getChoise();
        switch (choise)
        {
        case 1: // Add one (Done)
        {
            if (addTask(1))
            {
                printf("\n\t\t\033[32mTache est ajoutee avec succes.\033[0m\n");
            }
            else
                printf("\033[31m\n\t\t\t-- Erreur lors de l\'ajout de la tache !! --\n\033[0m\n");
            break;
        }

        case 2: // Add many
        {
            int newTasks_number;
            while (1)
            {
                printf("\n\t Combien de taches vous voulez ajouter ? : ");
                newTasks_number = getIntInput();
                if (newTasks_number < 1)
                    printf("\033[31m\n\t\t\t-- Nombre Invalide !! --\033[0m\n");
                else
                    break;
            }

            if (addTask(newTasks_number))
            {
                printf("\n\t\t\033[32mTaches sont ajoutees avec succes.\033[0m\n");
            }
            else
                printf("\033[31m\n\t\t\t-- Erreur lors de l\'ajout des taches !! --\n\033[0m\n");

            break;
        } // end case 2

        case 3: // Display (Done)
        {
            // if tasks is empty
            if (tasks_length - 1 == 0)
            {
                printf("\n\t\t\033[33m No taches availible !\033[0m\n");
                break;
            }

            // if is not
            int sortmethod;
            printf("\n\t L\'affichage par :\n"
                   "\t\t 1 - Order alphabetique\n"
                   "\t\t 2 - Par deadline\n"
                   "\t\t 3 - Taches dont le deadline est dans 3 jours ou moins.\n"
                   "\t\t 0 - Menu principale.\n");
            while (1)
            {
                printf("\n\t\t\t --> Tapez votre choix [0-3] : ");
                sortmethod = getIntInput();
                if (sortmethod >= 0 && sortmethod <= 3)
                    break;
                else
                    printf("\033[31m\n\t\t\t-- Choix Invalide !! --\033[0m\n");
            }

            if (sortmethod == 0)
                break;

            switch (sortmethod)
            {
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
        } // end case 3

        case 4: // Update (Done)
        {
            // get Id and search for task match it.
            int _id;
            printf("\n\t\tSaisir l\'identifiant : ");
            _id = getIntInput();
            int index = searchByID(_id);
            if (index == -1) // task not found
                printf("\n\t\t\033[33mNo tache avec cet identifiant.!!\033[0m\n");
            else
            {
                int arg_number;
                printf("\n\t\t Choisir critere : \n"
                       "\t\t\t 1. Description.\n"
                       "\t\t\t 2. Statut.\n"
                       "\t\t\t 3. Deadline\n"
                       "\t\t\t 0. Menu principale\n");
                while (1)
                {
                    printf("\t\t\t --> : ");
                    arg_number = getIntInput();
                    if (!(arg_number >= 0 && arg_number <= 3))
                    {
                        printf("\033[31m\n\t\t\t-- Choix Invalide !! --\033[0m\n");
                    }
                    else
                    {
                        break;
                    }
                }

                if (arg_number == 0)
                    break; // go menu

                if (updateTask(index, arg_number))
                    displayTask(tasks[index]);
                else
                    printf("\n\t\t\033[31m Erreur !! .\033[0m\n");
            }
            break;
        }

        case 5: // Delete (Done)
        {
            // get Id and search for task with that id.
            int _id;
            printf("\n\t\tSaisir l\'identifiant : ");
            _id = getIntInput();
            int index = searchByID(_id);
            if (index == -1) // task not found
                printf("\n\t\t\033[33mNo tache avec cet identifiant.!!\033[0m\n");

            else // task exist
            {
                displayTask(tasks[index]);
                char confirm;
                printf("\n\t\t\033[33mVoulez-vous vraiment supprimer cette tache ? (y/n) : \033[0m");
                scanf("%c", &confirm);

                // delete confirm
                if (confirm != 'y' && confirm != 'Y')
                {
                    printf("\n\t\t\033[34mL\'opration est annulee avec succes.\033[0m\n");
                    break;
                }
                if (deleteTask(index))
                {
                    printf("\n\t\t\033[32mTache supprimes avec succes.\033[0m\n");
                }
                else
                    printf("\n\t\t\033[31m Erreur !! .\033[0m\n");
            }
            break;
        } // end case 5

        case 6: // Search (Done)
        {
            int searchArg;
            printf("\n\tChoisir critere de recherche :"
                   "\n\t\t 1. Rechercher par identifiant."
                   "\n\t\t 2. Rechercher par titre."
                   "\n\t\t 0. Menu principale.\n");
            while (1)
            {
                printf("\n\t\t--> : ");
                searchArg = getIntInput();
                if (searchArg >= 0 && searchArg <= 2)
                    break;
                else
                    printf("\033[31m\n\t\t\t-- Choix invalide !! -- \033[0m\n");
            }

            if (searchArg == 0)
                break;

            switch (searchArg)
            {
            case 1: // Search by ID
            {
                int search_id;
                printf("\t\tSaisir l\'identifiant : ");
                search_id = getIntInput();

                int index = searchByID(search_id);
                index != -1 ? displayTask(tasks[index]) : printf("\n\t\t\033[33mNo tache avec cet identifiant.!!\033[0m\n");
                break;

            } // end case 6_1

            case 2: // Search by Title
            {
                char search_title[20];
                while (1)
                {
                    printf("\t\t Saisir titre : ");
                    fflush(stdin);
                    fgets(search_title, sizeof(search_title), stdin);
                    int len = strlen(search_title);
                    if (len > 1)
                    {
                        if (search_title[len - 1] == '\n')
                            search_title[len - 1] = '\0';
                        break;
                    }
                    else
                        printf("\033[31m\n\t\t\t-- Titre invalide !! -- \033[0m\n");
                }

                searchByTitle(search_title);

                break;
            } // end case 6_2
            }

            break;
        } // End case 6

        case 7: // Statistics (Done)
        {
            int display_choise;
            printf("\n\tNombre total des taches : %d"
                   "\n\tTaches completes   : %d :)"
                   "\n\tTaches incompletes : %d :( \n"
                   "\n\t\t1. Afficher taches completes."
                   "\n\t\t2. Afficher taches incompletes."
                   "\n\t\t0. Menu Principal.\n",
                   tasks_length - 1, getDoneTasksNumber(), tasks_length - 1 - getDoneTasksNumber());

            while (1)
            {
                printf("\n\tSaisir votre choix -> : ");
                display_choise = getIntInput();
                if (display_choise >= 0 && display_choise <= 2)
                    break;
                printf("\033[31m\n\t\t\t-- Choix invalide !! -- \033[0m\n");
            }

            if (display_choise == 0)
                break; // go Menu

            switch (display_choise)
            {
            case 1:
                displayDoneTasks();
                break;

            case 2:
                displayNonDoneTasks();
                break;
            }

            break;
        } // end case 7

        case 8: // Exit (Done)
        {
            if (saveTasks())
            {
                printf("\n\033[32m \t--> Les donnees enregistrees avec succes <--\033[0m\n");
                printf("\n\033[34m\t***** A bientot. *****\033[0m\n\n");
                break;
            }
            else{
                choise = 0;
                printf("\n\t\033[33mLes donnees ne sont pas enregistrees !!!\n \033[0m");
            }
        }
        } // end switch
    }

    // free pointer
    free(tasks);

    return 0;
}

/* Functions definition */
// done
void seeder()
{
    char str[13];
    time_t t = time(NULL);
    struct tm currentTime = *localtime(&t);

    // task 1
    Task task1 = {
        .id = 1,
        .title = "task : a week up",
        .description = "description task 3",

        .deadline.tm_year = 2023 - 1900,
        .deadline.tm_mon = 9 - 1,
        .deadline.tm_mday = 22,

        .deadline.tm_hour = 17,
        .deadline.tm_min = 35,
        .deadline.tm_sec = 25,

        .status = "A realiser",

        .created_at.tm_year = 2023 - 1900,
        .created_at.tm_mon = 9 - 1,
        .created_at.tm_mday = 21,

        .created_at.tm_hour = 12,
        .created_at.tm_min = 35,
        .created_at.tm_sec = 25};
    tasks[0] = task1;

    // task 2
    Task task2 = {
        .id = 2,
        .title = "task : C have breakfast",
        .description = "description task 2",

        .deadline.tm_year = 2023 - 1900,
        .deadline.tm_mon = 9 - 1,
        .deadline.tm_mday = 24,

        .deadline.tm_hour = 12,
        .deadline.tm_min = 35,
        .deadline.tm_sec = 25,

        .status = "finalisee",

        .created_at.tm_year = 2023 - 1900,
        .created_at.tm_mon = 9 - 1,
        .created_at.tm_mday = 21,

        .created_at.tm_hour = 9,
        .created_at.tm_min = 45,
        .created_at.tm_sec = 25};
    tasks[1] = task2;

    // task3
    Task task3 = {
        .id = 3,
        .title = "task : A morning training",
        .description = "description task 4",

        .deadline.tm_year = 2023 - 1900,
        .deadline.tm_mon = 10 - 1,
        .deadline.tm_mday = 7,

        .deadline.tm_hour = 12,
        .deadline.tm_min = 35,
        .deadline.tm_sec = 25,

        .status = "finalisee",

        .created_at.tm_year = 2023 - 1900,
        .created_at.tm_mon = 9 - 1,
        .created_at.tm_mday = 29,

        .created_at.tm_hour = 22,
        .created_at.tm_min = 45,
        .created_at.tm_sec = 35,
    };
    tasks[2] = task3;

    // task 4
    Task task4 = {
        .id = 4,
        .title = "task : c kassi kasaka",
        .description = "description task 1",

        .deadline.tm_year = 2023 - 1900,
        .deadline.tm_mon = 9 - 1,
        .deadline.tm_mday = 23,

        .deadline.tm_hour = 12,
        .deadline.tm_min = 35,
        .deadline.tm_sec = 25,

        .status = "A realiser",

        .created_at.tm_year = 2023 - 1900,
        .created_at.tm_mon = 9 - 1,
        .created_at.tm_mday = 21,

        .created_at.tm_hour = 23,
        .created_at.tm_min = 45,
        .created_at.tm_sec = 55};
    tasks[3] = task4;
}

// done
void displayDoneTasks()
{
    for (int i = 0; i < tasks_length - 1; i++)
    {
        if (stricmp(tasks[i].status, "finalisee") == 0)
            displayTask(tasks[i]);
    }
}

// done
void displayNonDoneTasks()
{
    for (int i = 0; i < tasks_length - 1; i++)
    {
        if (stricmp(tasks[i].status, "finalisee") != 0)
            displayTask(tasks[i]);
    }
}

// done
int getDoneTasksNumber()
{
    int number = 0;
    for (int i = 0; i < tasks_length - 1; i++)
    {
        if (stricmp(tasks[i].status, "finalisee") == 0)
            number++;
    }
    return number;
}

// done
int deleteTask(int index)
{
    for (int i = index + 1; i < tasks_length; i++)
    {
        memcpy(&tasks[i - 1], &tasks[i], sizeof(Task));
    }

    tasks_length--;

    tasks = (Task *)realloc(tasks, tasks_length * sizeof(Task));
    if (!tasks)
    {
        printf("\n\033[31m !!!!!!!!!!!!!! Server error !!!!!!!!!!!!! \033[0m\n");
        return 0;
    }
    return 1;
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
void searchByTitle(char search_title[20])
{
    int matched = 0;
    for (int i = 0; i < tasks_length - 1; i++)
    {
        if (isIn_STR(tasks[i].title, search_title))
        {
            displayTask(tasks[i]);
            matched++;
        }
    }
    if (matched == 0)
        printf("\n\t\t\033[33mNo tache avec ce titre.\033[0m");
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
}

// done
int displayTasks(int max_deadline_days)
{
    int count = 0;
    for (int i = 0; i < tasks_length - 1; i++)
    {
        count++;
        if (max_deadline_days == 0)
        {
            displayTask(tasks[i]);
            continue;
        }

        time_t current_t = time(NULL);
        time_t inDead = mktime(&tasks[i].deadline);
        long long int deadAfter = inDead - current_t;

        if (deadAfter <= (max_deadline_days * 24 * 3600))
            displayTask(tasks[i]);
    }
    return count;
}

// done
int displayTask(Task task)
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
int updateTask(int index, int arg_number)
{
    switch (arg_number)
    {
    case 1: // Update description (Done)
    {
        char newDescription[200];

        while (1)
        {
            printf("\n\t\t Saisir la nouvelle description  : ");
            fflush(stdin);
            fgets(newDescription, sizeof(newDescription), stdin);
            int len = strlen(newDescription);
            if (len > 4)
            {
                if (newDescription[len - 1] == '\n')
                    newDescription[len - 1] = '\0';
                break;
            }
            else
                printf("\033[31m\n\t\t\t-- Description Invalide !! --\033[0m\n");
        }

        strcpy(tasks[index].description, newDescription);
        printf("\n\t\033[32mDescription modifie avec succese.\033[0m\n");
        break;
    } // end case 4_1

    case 2: // Update status (Done)
    {
        int status_number;
        printf("\n\t\tStatut : "
               "\n\t\t\t 1. A realisee."
               "\n\t\t\t 2. En cours de realisation."
               "\n\t\t\t 3. Finalisee."
               "\n\t\t\t 0. Menu principale.");

        while (1)
        {
            printf("\n\t\t--> : ");
            status_number = getIntInput();
            if (!(status_number >= 0 && status_number <= 3))
                printf("\033[31m\n\t\t\t-- Choix invalide !! -- \033[0m\n");
            else
                break;
        }

        if (status_number == 0)
            break; // go Menu

        switch (status_number)
        {
        case 1:
            strcpy(tasks[index].status, "A realiser");
            break;

        case 2:
            strcpy(tasks[index].status, "En cours de realisation");
            break;

        case 3:
            strcpy(tasks[index].status, "Finalisee");
            break;
        }

        printf("\n\t\033[32mStatut modifie avec succese.\033[0m\n");
        break;

    } // end case 4_2

    case 3: // Update deadline (Done)
    {

        char input[11];
        int year, month, day;
        time_t t = time(NULL);
        struct tm currentTime = *localtime(&t);

        // deadline year month and day

        while (1)
        {
            printf("\n\t\t Saisir deadline (DD/MM/YYYY) : ");
            fflush(stdin);
            fgets(input, sizeof(input), stdin);
            int len = strlen(input);
            if (input[len - 1] == '\n')
                input[len - 1] = '\0';
            if (sscanf(input, "%02d/%02d/%04d", &day, &month, &year) != 3 || year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
            {
                printf("\033[31m\n\t\t\t-- Date invalide !! -- \033[0m\n");
            }
            else
                break;
        }

        tasks[index].deadline.tm_year = year - 1900;
        tasks[index].deadline.tm_mon = month - 1;
        tasks[index].deadline.tm_mday = day;
        tasks[index].deadline.tm_hour = currentTime.tm_hour;
        tasks[index].deadline.tm_min = currentTime.tm_min;
        tasks[index].deadline.tm_sec = currentTime.tm_sec;

        printf("\n\t\033[32mDeadline modifie avec succesee.\033[0m\n");
        break;
    } // end case 4_3

    } /* end Update switch */
}

// done
int addTask(int number)
{
    for (int i = 0; i < number; i++)
    {
        int year = 0, month = 0, day = 0;
        char title[40], description[200], status[24], input[11];
        time_t t = time(NULL);
        struct tm deadline, created_at, currentTime = *localtime(&t);

        printf("\n\t L\'ajoute de tache (%d)", i + 1);

        // title
        while (1)
        {
            printf("\n\t\t Saisir titre : ");
            fflush(stdin);
            fgets(title, sizeof(title), stdin);
            if (strlen(title) > 4)
            {
                if (title[strlen(title) - 1] == '\n')
                    title[strlen(title) - 1] = '\0';
                break;
            }
            else
                printf("\033[31m\n\t\t\t-- Titre invalide !! -- \033[0m\n");
        }

        // description
        while (1)
        {
            printf("\t\t Saisir description : ");
            fflush(stdin);
            fgets(description, sizeof(description), stdin);
            int len = strlen(description);
            if (len > 4)
            {
                if (description[len - 1] == '\n')
                    description[len - 1] = '\0';
                break;
            }
            else
                printf("\033[31m\n\t\t\t-- Description Invalide !! --\033[0m\n");
        }

        // deadline year month and day
        while (1)
        {
            printf("\t\t Saisir deadline (DD/MM/YYYY) : ");
            fflush(stdin);
            fgets(input, sizeof(input), stdin);
            int len = strlen(input);
            if (input[len - 1] == '\n')
                input[len - 1] = '\0';
            if (sscanf(input, "%02d/%02d/%04d", &day, &month, &year) != 3 || year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
            {
                printf("\033[31m\n\t\t\t-- Date Invalide !! --\033[0m\n");
            }
            else
            {
                deadline.tm_year = year - 1900;
                deadline.tm_mon = month - 1;
                deadline.tm_mday = day;
                deadline.tm_hour = currentTime.tm_hour;
                deadline.tm_min = currentTime.tm_min;
                deadline.tm_sec = currentTime.tm_sec;
                break;
            }
        }

        strcpy(status, "A realiser");

        // Created at
        created_at.tm_year = currentTime.tm_year;
        created_at.tm_mon = currentTime.tm_mon;
        created_at.tm_mday = currentTime.tm_mday;
        created_at.tm_hour = currentTime.tm_hour;
        created_at.tm_min = currentTime.tm_min;
        created_at.tm_sec = currentTime.tm_sec;

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
            printf("\n\033[31m !!!!!!!!!!!!!! Server error !!!!!!!!!!!!! \033[31m\n");
            return 0;
        }
    }
    return 1;
}

// done
int isIn_STR(char str1[], char str2[])
{
    int itIs = 0;
    for (int i = 0; i < strlen(str1); i++)
    {
        if (str1[i] == str2[0])
        {
            int k = i + 1;
            itIs = 1;
            for (int j = 1; j < strlen(str2); j++)
            {
                if (str2[j] != str1[k])
                {
                    itIs = 0;
                    break;
                }
                k++;
            }
            if (itIs)
                return itIs;
        }
    }
    return itIs;
}

// done
int getChoise()
{
    int choise = 0;
    while (1)
    {
        printf("\n"
               "\t==============================================\n\t"
               "|          \033[36mMenu d\'application\033[0m                |\n"
               "\t==============================================\n\t"
               "|\t[1] Ajouter une tache                |\n\t"
               "|\t[2] Ajouter plusieur taches          |\n\t"
               "|\t[3] Afficher la list de taches       |\n\t"
               "|\t[4] Modifier une tache               |\n\t"
               "|\t[5] Supprimer une tache              |\n\t"
               "|\t[6] Rechercher les taches            |\n\t"
               "|\t[7] Statistiques                     |\n\t"
               "|\t[\033[33m8\033[0m] \033[33mQuitter\033[0m                          |\n"
               "\t==============================================\n\t"
               "\n\tTapez votre choix [1-8] : ");

        // get the input from user.
        choise = getIntInput();
        if (choise != -1 && choise >= 1 && choise <= 8)
        {
            break;
        }
        else
        {
            printf("\033[31m\n\t\t\t-- Choix Invalide !! --\033[0m\n");
        }
    };

    return choise;
}

// done
int getIntInput()
{
    char input[10];
    int choise;
    fflush(stdin);
    fgets(input, sizeof(input), stdin);
    int len = strlen(input);
    if (input[len - 1] == '\n')
        input[len - 1] = '\0';
    if (!isNumber(input))
        return -1;

    // verify valide input
    if (sscanf(input, "%d", &choise) && choise >= 0)
        return choise;
    else
        return -1;
}

// done
int isNumber(char string[])
{
    for (int i = 0; i < strlen(string); i++)
    {
        if (!isdigit(string[i]))
            return 0;
    }
    return 1;
}

// doing
int saveTasks()
{
    FILE *myFile;
    fopen_s(&myFile, "C:/Users/Youcode/Desktop/SAS/YouCode_Projet-Fin-SAS/Tasks.dat", "w");
    if (myFile == NULL)
    {
        printf("\n\t\033[31mErreur: fichier tasks.dat n\'ouvrir pas !! \n\033[0m");
        return 0;
    }
    for (int i = 0; i < tasks_length - 1; i++)
    {
        char task__str[300];

        sprintf(task__str, "%d, %s, %s, %d/%d/%d %d:%d:%d, %s, %d/%d/%d %d:%d:%d\n",
                tasks[i].id,
                tasks[i].title,
                tasks[i].description,
                tasks[i].deadline.tm_mday, tasks[i].deadline.tm_mon, tasks[i].deadline.tm_year, tasks[i].deadline.tm_hour, tasks[i].deadline.tm_min, tasks[i].deadline.tm_sec,
                tasks[i].status,
                tasks[i].created_at.tm_mday, tasks[i].created_at.tm_mon, tasks[i].created_at.tm_year, tasks[i].created_at.tm_hour, tasks[i].created_at.tm_min, tasks[i].created_at.tm_sec);

        {
            if (!fwrite(task__str, sizeof(char), strlen(task__str), myFile))
            {
                printf("\n\t\033[31m Erreur lors de l\'enregistrement dans le fichier .\033[0m\n");
                return 0;
            }
        }
    }
    fclose(myFile);
    return 1;
}
