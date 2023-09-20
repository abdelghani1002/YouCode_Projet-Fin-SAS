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
    char status[24];
    // Collaborator *collaborators;
    struct tm created_at;
} Task;

// Functions declaration
int getChoise();

// Constances

// Global variables
int tasks_length = 1; // size of the tasks array
Task *tasks;          // ** pointer to tasks array ** //

// main
int main()
{
    int choise;
    tasks = (Task *)malloc(sizeof(Task) * tasks_length);  // allocate memory for the tasks pointer



    while(1){
        choise = getChoise();
        switch (choise)
        {
        case 1:
            printf("Ajouter une tache");
            break;
        case 2:
            printf("Ajouter plusieur taches");
            break;
        case 3:
            printf("Afficher la list de taches");
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




    free(tasks);
    return 0;
}




// Functions definition
int getChoise(){
    char input[20];
    int choise = 0;

    while(1){
        printf("\n\n\t===============================================\n\t"
                    "\tMenu d\'application\n\t"
                "===============================================\n\t"
                "[1] Ajouter une tache\n\t"
                "[2] Ajouter plusieur taches\n\t"
                "[3] Afficher la list de taches\n\t"
                "[4] Modifier une tache\n\t"
                "[5] Supprimer une donnee par identifiant\n\t"
                "[6] Rechercher les taches\n\t"
                "[7] Statistiques\n\t"
                "[8] Quitter\n\t"
                "===============================================\n\t"
                "\n\tTapez votre choix [0-8] : ");

        fgets(input, sizeof(input), stdin); // get the input from user.

        // verify valide input
        if( ! sscanf(input, "%d", &choise) || (choise < 1 || choise > 8)) 
            printf("\n\t\t-- Choix Invalide !! --"); 
        else
            break;
    };
    
    return choise;
}