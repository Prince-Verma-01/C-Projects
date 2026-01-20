#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#ifdef _WIN32
/* map POSIX sleep(seconds) to WinAPI Sleep(milliseconds) */
#ifndef sleep
#define sleep(x) Sleep((x) * 1000)
#endif
#endif
#define MAX_QUES_LEN 300
#define MAX_OPTION_LEN 300
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"

typedef  struct
{	
	char text[MAX_QUES_LEN];
	char option[4][MAX_OPTION_LEN];
	char correct_option;
	int timeout;
	int prize_money;
} Question;

int money=0;
int i;

// Function prototypes
int read_question(char *file_name, Question** question);
void print_question(Question question, int qnum, int total);
int verify_admin();
void admin_menu(Question** questions, int *no_of_questions);
void add_question(Question** questions, int *no_of_questions);
void delete_question(Question** questions, int *no_of_questions);
void update_question(Question* questions, int no_of_questions);
void display_all_questions(Question* questions, int no_of_questions);
void save_questions(Question* questions, int no_of_questions);
void student_mode(Question* questions, int no_of_questions);
void read_line(char *buffer, int size);
void trim_newline(char *str);
	int main()
	{
		Question* questions = NULL;
		int no_of_questions = read_question("ques.txt", &questions);
		int user_type;
		char buffer[10];
		
		printf("\n");
		printf("====================================\n");
		printf("  Kaun Banega Crorepati - KBC 2025  \n");
		printf("====================================\n");
		printf("\n");
		printf("Select your role:\n");
		printf("1. Admin (Manage Questions)\n");
		printf("2. Student (Play Quiz)\n");
		printf("3. Exit\n");
		printf("Enter your choice: ");
		read_line(buffer, 10);
		user_type = atoi(buffer);
		
		switch(user_type)
		{
			case 1:
				if(verify_admin())
                
				{
					admin_menu(&questions, &no_of_questions);
				}
				else
				{
					printf("\nInvalid credentials!\n");
				}
				break;
			case 2:
				if(no_of_questions <= 0)
				{
					printf("\nNo questions available. Please contact admin.\n");
				}
				else
				{
					student_mode(questions, no_of_questions);
				}
				break;
			case 3:
				printf("\nThank you for using KBC!\n");
				break;
			default:
				printf("\nInvalid choice!\n");
		}
		
		if(questions != NULL)
		{
			free(questions);
		}
		return 0;
	}
	void print_question(Question question, int qnum, int total){		  
			  int choice;
			  char ch;
			  char buffer[10];
			  
			  printf("\n");
			  printf("===== Question %d of %d =====\n", qnum, total);
			  printf("%s", question.text);
			  printf("A) %s", question.option[0]);
			  printf("B) %s", question.option[1]);
			  printf("C) %s", question.option[2]);
			  printf("D) %s", question.option[3]);
			  
			  printf("\nPress 1: for previous Question\n");
			  printf("Press 2: for next Question\n");
			  printf("Press 3: to Enter Answer\n");
			  printf("Enter your choice: ");
			    read_line(buffer, 10);
			    choice = atoi(buffer);
			    
			  switch(choice)
			  {
			  	case 1:
			  		if(i==0)
			  		{
			  			printf("\nNo previous question available\n");
						sleep(1);
						return;
					}
			  		i=i-2;
			  		return;
			  	case 2:
			  		return;
			  	case 3:
			  		printf("\nEnter the correct option (A/B/C/D): ");
			    	read_line(buffer, 10);
			    	ch = buffer[0];
			    	ch = (ch >= 'a' && ch <= 'd') ? (ch - 32) : ch;
			    	break;
			  	default:
			  		printf("Invalid choice, try again...\n");
			  		sleep(1);
			  		print_question(question, qnum, total);
			  		return;
			  }
			    
			    if(ch==question.correct_option)
			    {
			    	money=money+ question.prize_money;
			    	printf("\nCorrect Answer! Prize money: %d\n", question.prize_money);
			    	printf("Total Prize Money: %d\n", money);
			    	sleep(1);
					return;
				}	
				else
				{
					printf("\nWrong Answer!\n");
					printf("Correct Option was: %c\n", question.correct_option);
					printf("Final Prize Money Earned: %d\n", money);
					sleep(2);
					exit(0);
				}
			  sleep(question.timeout);
			  
 
	}
		int read_question(char *file_name, Question** question)
		{
			char str[MAX_QUES_LEN];
			int i,j;
			char option[10];
			char number[10];
			char prize_money[10];
			
			FILE *ptr=fopen(file_name,"r");
			if(ptr==NULL)
			{
				printf("Unable to open the question bank\n");
				return 0;
			}
			// file is ready
			
			int no_of_lines=0;
			
			while(fgets(str,MAX_QUES_LEN,ptr))
			{
				no_of_lines++;
			}
			int no_of_questions=no_of_lines/8;
			if(no_of_questions<=0){
				printf("No questions found in file\n");
				fclose(ptr);
				return 0;
			}
			
			// allocate the space
			
			*question = (Question*) malloc(no_of_questions*sizeof(Question));
			if(*question == NULL){
				printf("Memory allocation failed\n");
				fclose(ptr);
				return 0;
			}
			rewind(ptr); // start from beginning
			
			 for(i=0;i<no_of_questions;i++){
			 	fgets((*question)[i].text,MAX_QUES_LEN,ptr);
			 	
				for(j=0;j<4;j++)
			 	{
			 			fgets((*question)[i].option[j],MAX_OPTION_LEN,ptr);
				}
				
				fgets(option,10,ptr);
				(*question)[i].correct_option=option[0]; // first character assign
				
				fgets(number,10,ptr);
				(*question)[i].timeout=atoi(number);
				
				fgets(prize_money,10,ptr);
				(*question)[i].prize_money =atoi(prize_money);
				
			 }
			 fclose(ptr);
			 return no_of_questions;
			
		}

		// ===== UTILITY FUNCTIONS =====
		void trim_newline(char *str)
		{
			int len = strlen(str);
			if(len > 0 && str[len-1] == '\n')
			{
				str[len-1] = '\0';
			}
		}

		void read_line(char *buffer, int size)
		{
			fgets(buffer, size, stdin);
			trim_newline(buffer);
		}

		// ===== ADMIN FUNCTIONS =====
		int verify_admin()
		{
			char username[50], password[50];
			
			printf("\n========== ADMIN LOGIN ==========\n");
			printf("Enter username: ");
			read_line(username, 50);
			
			printf("Enter password: ");
			read_line(password, 50);
			
			if(strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0)
			{
				printf("\n=== Login Successful ===\n");
				sleep(1);
				return 1;
			}
			return 0;
		}

		void admin_menu(Question** questions, int *no_of_questions)
		{
			int choice;
			char buffer[10];
			
			while(1)
			{
				printf("\n");
				printf("========== ADMIN MENU ==========\n");
				printf("1. Add Question\n");
				printf("2. Delete Question\n");
				printf("3. Update Question\n");
				printf("4. View All Questions\n");
				printf("5. Change Prize Money\n");
				printf("6. Save and Exit\n");
				printf("================================\n");
				printf("Enter your choice: ");
				read_line(buffer, 10);
				choice = atoi(buffer);
				
				switch(choice)
				{
					case 1:
						add_question(questions, no_of_questions);
						break;
					case 2:
						delete_question(questions, no_of_questions);
						break;
					case 3:
						update_question(*questions, *no_of_questions);
						break;
					case 4:
						display_all_questions(*questions, *no_of_questions);
						break;
					case 5:
						update_question(*questions, *no_of_questions);
						break;
					case 6:
						save_questions(*questions, *no_of_questions);
						printf("\nQuestions saved successfully!\n");
						return;
					default:
						printf("\nInvalid choice! Try again.\n");
				}
			}
		}

		void add_question(Question** questions, int *no_of_questions)
		{
			Question* temp = (Question*) realloc(*questions, (*no_of_questions + 1) * sizeof(Question));
			if(temp == NULL)
			{
				printf("\nMemory allocation failed!\n");
				return;
			}
			*questions = temp;
			
			int idx = *no_of_questions;
			char buffer[20];
			
			printf("\n========== ADD NEW QUESTION ==========\n");
			printf("Enter question text: ");
			read_line((*questions)[idx].text, MAX_QUES_LEN);
			
			printf("Enter Option A: ");
			read_line((*questions)[idx].option[0], MAX_OPTION_LEN);
			
			printf("Enter Option B: ");
			read_line((*questions)[idx].option[1], MAX_OPTION_LEN);
			
			printf("Enter Option C: ");
			read_line((*questions)[idx].option[2], MAX_OPTION_LEN);
			
			printf("Enter Option D: ");
			read_line((*questions)[idx].option[3], MAX_OPTION_LEN);
			
			printf("Enter correct option (A/B/C/D): ");
			char ans[10];
			read_line(ans, 10);
			(*questions)[idx].correct_option = ans[0];
			
			printf("Enter timeout (seconds): ");
			read_line(buffer, 20);
			(*questions)[idx].timeout = atoi(buffer);
			
			printf("Enter prize money: ");
			read_line(buffer, 20);
			(*questions)[idx].prize_money = atoi(buffer);
			
			(*no_of_questions)++;
			printf("\nQuestion added successfully!\n");
		}

		void delete_question(Question** questions, int *no_of_questions)
		{
			if(*no_of_questions <= 0)
			{
				printf("\nNo questions to delete!\n");
				return;
			}
			
			display_all_questions(*questions, *no_of_questions);
			
			int qnum;
			char buffer[10];
			printf("\nEnter question number to delete (1 to %d): ", *no_of_questions);
			read_line(buffer, 10);
			qnum = atoi(buffer);
			
			if(qnum < 1 || qnum > *no_of_questions)
			{
				printf("\nInvalid question number!\n");
				return;
			}
			
			qnum--; // Convert to 0-indexed
			
			for(int j = qnum; j < *no_of_questions - 1; j++)
			{
				(*questions)[j] = (*questions)[j+1];
			}
			
			(*no_of_questions)--;
			printf("\nQuestion deleted successfully!\n");
		}

		void update_question(Question* questions, int no_of_questions)
		{
			if(no_of_questions <= 0)
			{
				printf("\nNo questions to update!\n");
				return;
			}
			
			display_all_questions(questions, no_of_questions);
			
			int qnum;
			char buffer[10];
			printf("\nEnter question number to update (1 to %d): ", no_of_questions);
			read_line(buffer, 10);
			qnum = atoi(buffer);
			
			if(qnum < 1 || qnum > no_of_questions)
			{
				printf("\nInvalid question number!\n");
				return;
			}
			
			qnum--; // Convert to 0-indexed
			
			int update_choice;
			char buffer2[10];
			printf("\n========== UPDATE OPTIONS ==========\n");
			printf("1. Update Question Text\n");
			printf("2. Update Options\n");
			printf("3. Update Correct Answer\n");
			printf("4. Update Prize Money\n");
			printf("5. Update All\n");
			printf("====================================\n");
			printf("Enter your choice: ");
			read_line(buffer2, 10);
			update_choice = atoi(buffer2);
			
			switch(update_choice)
			{
				case 1:
					printf("Enter new question text: ");
					read_line(questions[qnum].text, MAX_QUES_LEN);
					break;
				case 2:
					printf("Enter new Option A: ");
					read_line(questions[qnum].option[0], MAX_OPTION_LEN);
					printf("Enter new Option B: ");
					read_line(questions[qnum].option[1], MAX_OPTION_LEN);
					printf("Enter new Option C: ");
					read_line(questions[qnum].option[2], MAX_OPTION_LEN);
					printf("Enter new Option D: ");
					read_line(questions[qnum].option[3], MAX_OPTION_LEN);
					break;
				case 3:
					printf("Enter new correct option (A/B/C/D): ");
					char ans[10];
					read_line(ans, 10);
					questions[qnum].correct_option = ans[0];
					break;
				case 4:
					printf("Enter new prize money: ");
					char buffer3[20];
					read_line(buffer3, 20);
					questions[qnum].prize_money = atoi(buffer3);
					break;
				case 5:
					printf("Enter new question text: ");
					read_line(questions[qnum].text, MAX_QUES_LEN);
					printf("Enter new Option A: ");
					read_line(questions[qnum].option[0], MAX_OPTION_LEN);
					printf("Enter new Option B: ");
					read_line(questions[qnum].option[1], MAX_OPTION_LEN);
					printf("Enter new Option C: ");
					read_line(questions[qnum].option[2], MAX_OPTION_LEN);
					printf("Enter new Option D: ");
					read_line(questions[qnum].option[3], MAX_OPTION_LEN);
					printf("Enter new correct option (A/B/C/D): ");
					char ans2[10];
					read_line(ans2, 10);
					questions[qnum].correct_option = ans2[0];
					printf("Enter new prize money: ");
					char buffer4[20];
					read_line(buffer4, 20);
					questions[qnum].prize_money = atoi(buffer4);
					break;
				default:
					printf("\nInvalid choice!\n");
			}
			printf("\nQuestion updated successfully!\n");
		}

		void display_all_questions(Question* questions, int no_of_questions)
		{
			if(no_of_questions <= 0)
			{
				printf("\nNo questions available!\n");
				return;
			}
			
			printf("\n========== ALL QUESTIONS ==========\n");
			for(int i = 0; i < no_of_questions; i++)
			{
				printf("\nQuestion %d: %s", i+1, questions[i].text);
				printf("A) %s", questions[i].option[0]);
				printf("B) %s", questions[i].option[1]);
				printf("C) %s", questions[i].option[2]);
				printf("D) %s", questions[i].option[3]);
				printf("Correct: %c | Prize: %d\n", questions[i].correct_option, questions[i].prize_money);
			}
			printf("===================================\n");
		}

		void save_questions(Question* questions, int no_of_questions)
		{
			FILE *ptr = fopen("ques.txt", "w");
			if(ptr == NULL)
			{
				printf("\nError: Cannot save questions!\n");
				return;
			}
			
			for(int i = 0; i < no_of_questions; i++)
			{
				fprintf(ptr, "%s\n", questions[i].text);
				fprintf(ptr, "%s\n", questions[i].option[0]);
				fprintf(ptr, "%s\n", questions[i].option[1]);
				fprintf(ptr, "%s\n", questions[i].option[2]);
				fprintf(ptr, "%s\n", questions[i].option[3]);
				fprintf(ptr, "%c\n", questions[i].correct_option);
				fprintf(ptr, "%d\n", questions[i].timeout);
				fprintf(ptr, "%d\n", questions[i].prize_money);
			}
			
			fclose(ptr);
		}

		void student_mode(Question* questions, int no_of_questions)
		{
			money = 0;
			printf("\n");
			printf("====================================\n");
			printf("  Welcome to KBC Quiz!\n");
			printf("  Total Questions: %d\n", no_of_questions);
			printf("====================================\n\n");
			sleep(1);
			
			for(i=0;i<no_of_questions;i++)
			{
				print_question(questions[i], i+1, no_of_questions);
			}
			
			printf("\n========== Quiz Complete! ==========\n");
			printf("Final Prize Money: %d\n", money);
			printf("====================================\n");
		}
