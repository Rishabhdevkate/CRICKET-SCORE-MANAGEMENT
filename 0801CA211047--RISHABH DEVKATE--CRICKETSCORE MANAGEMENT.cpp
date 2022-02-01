#include<stdio.h>
#include<stdlib.h>
int score, overs, balls, scoreT1, scoreT2, wickets, overLimit, format, totalBalls, wicket1, wicket2;
float RR1, RR2;

void scoreManager()
{
	int event, runs;
	char extraRuns;
	int choice;

	printf("\n\nWhat happned on last ball:\n\n"
	       "1. Run\n"
		   "2. Wicket\n"
		   "3. Wide Ball\n"
		   "4. No Ball\n"
		   "5. Dot Ball\n> ");

	scanf("%d", &event);

	switch (event)
	{
	case 1 :
		// Menu

		printf("\nRuns : Button\n"
			   "[1]  : Press 1\n"
			   "[2]  : Press 2\n"
			   "[3]  : Press 3\n"
			   "[4]  : Press 4\n"
			   "[6]  : Press 6\n"
			   "[C]  : Press 0\n> ");

		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			score++;
			break;
		case 2:
			score += 2;
			break;
		case 3:
			score += 3;
			break;
		case 4:
			score += 4;
			break;
		case 6:
			score += 6;
			break;

		default:
			printf("Enter run/runs: ");
			scanf("%d", &runs);
			score += runs;
			break;
		}

		balls++;		 // 1 ball has been taken
		totalBalls++;
		break;
	case 2 :
		/* Wicket*/  
		balls++;
		totalBalls++;
		wickets++;
		break;
	case 3 :
		/* Wide BAll */
		score++;
		break;
	case 4 :    
		 /* No Ball code */
        score++;
		printf("\nAny extra runs if yes, press 'Y/y' to adds runs: ");
		fflush(stdin);
		scanf("%c", &extraRuns);
		if(extraRuns == 'Y' || extraRuns == 'y')
		{
			printf("\n\nEnter run on 'No Ball': ");
			scanf("%d", &runs);
			score += runs;
		}
		break;
	case 5:
	       balls++;
		   totalBalls++;
		break;
	}

	if(balls == 6)
	{
		overs++;
		balls = 0;
	}

	printf("\n\nScore = %d || Wicket = %d || Balls = %d || Over = %d  || Current RR = %f\n\n",
			score, wickets, balls, overs, (float)score/totalBalls);

}

void decideFormat()
{

	printf("\n\nEnter the format of match"
		   "\nPress 1\t:\tT20"
		   "\nPress 2\t:\tODI"
		   "\nPress 3\t:\tTest"
		   "\nPress 4\t:\tT10\n> ");

	scanf("%d", &format);
	switch (format)
	{
	case 1:
		overLimit = 20;  
		break;
	case 2:
		overLimit = 50;
		break;
	case 3:
		overLimit = 90;
		break;
	case 4:
		overLimit = 10;
		break;
	}

}


int main()
{
	
	FILE *fp, *fp2;  
    fp = fopen("card.txt", "w");//opening file 
	fp2 = fopen("card.txt", "a"); // 



	char team1[10], team2[10];
	int  whichTeamBat;
	printf("\nEnter the name of the team1 => ");
	scanf("%s", team1);
    printf("\nThe name of the team1 = %s", team1);

	printf("\nEnter the name of the team2 => ");
	scanf("%s", team2);
    printf("\nThe name of the team1 = %s", team2);


	printf("\nWhich team is batting first? => ");

	while(1)
	{
		scanf("%d", &whichTeamBat);
		if(whichTeamBat == 1)
		{
			printf("\nTeam %s is batting.\nTeam %s is bowling.", team1, team2);
			break;
		}
		else if(whichTeamBat == 2)
		{
			printf("\nTeam %s is batting.\nTeam %s is bowling.", team2, team1);
			break;
		}
		printf("Wrong Input...Please enter correct input.\n");
	}

	// Taking format type

	decideFormat();

	// looping for first inning


	printf("---------------------- 1st Inning ----------------------");

	while (1)
	{
		scoreManager();
		if (wickets==10 || overLimit == overs)
			break;

	}

	printf("---------------------- Inning Over----------------------");
	printf("\n\nTarget = %d", score);


	// looping for second inning

	printf("\n\n---------------------- 2nd Inning ----------------------");

	if(whichTeamBat == 1)       // batting
	{
		scoreT1 = score;
		wicket1 = wickets;
		RR1 = (float)score/totalBalls;
	}	
	else
	{
		scoreT2 = score;
		wicket2 = wickets;
		RR2 = (float)score/totalBalls;
	}



	totalBalls=0;
	score = 0;
	wickets = 0;
	balls = 0;
	overs = 0;

	while (1)
	{
		scoreManager();
		if (wickets > 9 || overLimit == overs || score > scoreT1)
			break;

	}
	if(whichTeamBat == 1)       // whichTeam
	{
		scoreT2 = score;
		wicket2 = wickets;
		RR2 = (float)score/totalBalls;
	}
	else
    {
		scoreT1 = score;
		wicket1 = wickets;
		RR1 = (float)score/totalBalls;
	}	

	/// Deciding

    // wins by run

	if(whichTeamBat == 1 && (scoreT1 > scoreT2))
	{
		printf("%s wins the match by %d runs", team1, (scoreT1 - scoreT2));
		
	}
	else if(whichTeamBat == 2 && (scoreT1 < scoreT2))
	{
		printf("%s wins the match by %d runs", team2, (scoreT2 - scoreT1));
		

	}
	else
    {
        if (scoreT1<scoreT2)
		{
      		printf("%s wins the match by %d wicket", team2, (10-wickets));
		
		}
        else
		{
		
        	printf("%s wins the match by %d wicket", team1, (10-wickets));
		}
    }

	printf("\n\nTeam 1 : %s		%d/%d		%f\n\n"
		   "Team 2 : %s		%d/%d		%f\n"
		   "------------------------------\n\n", team1, scoreT1, wicket1, RR1, 
		   									 team2, scoreT2, wicket2, RR2);


	fprintf(fp, "Team Name		  runs/wic      RR"
				"\nTeam 1 : %s		%d/%d		%f\n\n"
				"Team 2 : %s		%d/%d		%f\n", team1, scoreT1, wicket1, RR1, 
		   									 team2, scoreT2, wicket2, RR2);//writing data into file  

		   
	fprintf(fp2, "------------------------------------------------\n\n");//writing data into file  
    fclose(fp);//closing file  

	// --------------------------------------------------------------

	if(whichTeamBat == 1 && (scoreT1 > scoreT2))
	{
		fprintf(fp2, "Team 1 : %s wins\n\n"
					 "------------------------------------------------\n"
					 "%s wins the match by %d runs", team1, team1, (scoreT1 - scoreT2));//writing data into file  
	}
	else if(whichTeamBat == 2 && (scoreT1 < scoreT2))
	{
		fprintf(fp2,"Team 2 : %s wins\n\n"
					"------------------------------------------------\n"
					"%s wins the match by %d runs", team2, team2, (scoreT2 - scoreT1));//writing data into file  
	}
	else
    {
        if (scoreT1<scoreT2)
		{
			fprintf(fp2, "Team 2 : %s wins\n\n"
						 "------------------------------------------------\n"
					 	 "%s wins the match by %d wicket", team2, team2, (10-wickets));//writing data into file  
		}
        else
		{
			fprintf(fp2, "Team 1 : %s wins\n\n"
					 	 "------------------------------------------------\n"
					     "%s wins the match by %d wicket", team1, team1, (10-wickets));//writing data into file  
		}
    }



}
