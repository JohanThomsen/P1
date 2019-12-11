/* Navn: Jonas Zacho Poulsen
Email: jzpo19@student.aau.dk
Gruppe: A404
Studieretning: Software */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LGT 5
#define TOTAL_MATCHES 182
#define TOTAL_TEAMS 14

typedef struct
{
  char weekday[MAX_NAME_LGT];
  char date[MAX_NAME_LGT];
  char time[MAX_NAME_LGT];
  char first_team[MAX_NAME_LGT];
  char second_team[MAX_NAME_LGT];
  int first_result;
  int second_result;
  int audience_number;
} match;

typedef struct
{
  char name[MAX_NAME_LGT];
  int points;
  int goals_by_team;
  int goals_against_team;
} team;

void points_goals_and_read (FILE *ifp,char *current_string, match *match_array,char **teams, team *team_array);
int cmpfunc (const void * a, const void * b);
void sort_scoreboard (team *team_array, char **teams);
void print_scoreboard(char **teams, team *team_array);

int main(void)
{
    FILE *ifp = fopen("kampe-2018-2019.txt", "r");
    match match_array[TOTAL_MATCHES];
    team team_array[TOTAL_TEAMS];

    char *current_string = (char*)calloc(100, sizeof(char));

    points_goals_and_read(ifp,current_string, match_array, teams, team_array);

    sort_scoreboard(team_array, teams);

    print_scoreboard(teams, team_array);

    free(current_string);

    fclose(ifp);
   
    return 0;
}

void points_goals_and_read (FILE *ifp,char *current_string, match *match_array,char **teams, team *team_array)
{ 
  int i = 0, j = 0;

  /* reading the file and inserting the information into seperate structs in the match_array */
  
  if (ifp != NULL)
  {
    current_string = fgets(current_string, 100, ifp);
    
    while (current_string != NULL)
    {
      sscanf(current_string,
      " %[a-zA-Z]"
      " %[0-9/0-9]"
      " %[0-9.0-9]"
      " %[a-zA-Z]"
      " - %[a-zA-Z]"
      " %d"
      " - %d"
      " %d",
      match_array[i].weekday,
      match_array[i].date,
      match_array[i].time,
      match_array[i].first_team,
      match_array[i].second_team,
      &match_array[i].first_result,
      &match_array[i].second_result,
      &match_array[i].audience_number
      );

       /* Counts points and goals scored for teams */
       for(j = 0; j < 14; j++)
       {
         if (strcmp(match_array[i].first_team, teams[j]) == 0)
         {
	   team_array[j].goals_by_team+=match_array[i].first_result;
	   team_array[j].goals_against_team+=match_array[i].second_result;
		  
           if (match_array[i].first_result == match_array[i].second_result)
           {
             team_array[j].points  += 1;
	   }

           else if (match_array[i].first_result > match_array[i].second_result)
	   {
             team_array[j].points += 3;
	     strcpy(team_array[j].name,match_array[i].first_team);
           }
         }		

	 else if (strcmp(match_array[i].second_team, teams[j]) == 0)
         {		  
           team_array[j].goals_by_team+=match_array[i].second_result;
	   team_array[j].goals_against_team+=match_array[i].first_result;
		  
           if (match_array[i].first_result == match_array[i].second_result)
           {
             team_array[j].points  += 1;
	   }

	   else if (match_array[i].first_result < match_array[i].second_result)
           {
             team_array[j].points += 3;
	   }
	 }	    
       }
       current_string = fgets(current_string, 100, ifp);
       i++;        
    }  
  }
}

/* I compare points in the array */
int cmpfunc (const void * a, const void * b) 
{
  team *teamA =(team*) a;
  team *teamB =(team*) b;

  if (teamA->points > teamB->points)
  {
    return 0;
  }  
}

/* I sort the team array from my cmpfunc  */
void sort_scoreboard(team *team_array, char **teams)
{
  qsort(team_array, 14, sizeof(team), cmpfunc);
}

void print_scoreboard(char **teams, team *team_array)
{
  int i;
  
    printf("\nTeam name   |   Points   |   Scored by   |   Scored against\n");
    
    for (i = 0; i < 14; i++)
    {
      printf("%6s %13d %14d %17d\n", team_array[i].name, team_array[i].points, team_array[i].goals_by_team, team_array[i].goals_against_team);
    }
}
