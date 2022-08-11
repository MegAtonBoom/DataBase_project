#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "defines.h"

#pragma warning(disable : 4996)


void update_tournament(MYSQL* conn)
{
	MYSQL_STMT* update_tournament_stmt;
	MYSQL_BIND param[1];

	char options[3] = { '1','2','3'};
	char r;
	char tournament[20];


	printf("The system can calculate the teams of the next tournament stage\n but only if all the matches were already played.\n ");
	printf("Choose the tournament stage to calculate: \n\t1)Last 8\n\t2)Last 4\n\t3)Finals\n");
	r = multiChoice("Select the answer: ", options, 3);

	switch (r)
	{
	case '1':
		strcpy(tournament, "quarti");
		break;
	case '2':
		strcpy(tournament, "semifinale");
		break;
	case '3':
		strcpy(tournament, "finale");
		break;
	default:
		fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
		abort();

	}


	if (!setup_prepared_stmt(&update_tournament_stmt, "call aggiorna_tornero(?)", conn)) {
		finish_with_stmt_error(conn, update_tournament_stmt, "Unable to initialize the tournament update statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = tournament;
	param[0].buffer_length = strlen(tournament);


	if (mysql_stmt_bind_param(update_tournament_stmt, param) != 0) {
		finish_with_stmt_error(conn, update_tournament_stmt, "Could not bind parameters for tournament update procedure\n", true);
	}
	if (mysql_stmt_execute(update_tournament_stmt) != 0) {
		char optionserr[2] = { '1','2' };
		char er;
		print_stmt_error(update_tournament_stmt, "An error occurred while updating the tournament, what do you want to do?\n\t1)Try again;\n\t2)Quit\n");
		er = multiChoice("Select your answer: ", optionserr, 2);
		switch (er)
		{
		case '1':
			update_tournament(conn);
			break;
		case '2': 
			return;
		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
		}
	}
	else {
		printf("\nTournament correctly updated\n");
		fflush(stdout);
		system("PAUSE");
		mysql_stmt_close(update_tournament_stmt);
	}

}

void add_referee(MYSQL* conn)
{
	MYSQL_STMT* add_referee_stmt;
	MYSQL_BIND param[6];


	char name[48];
	char s_presences[16], s_number[16];
	char country[36];
	char city[48];
	char street[48];

	printf("\nName: ");
	fflush(stdout);
	fgets(name, 48, stdin);
	name[strlen(name) - 1] = '\0';

	printf("\nNumber of presences in past matches: ");
	fflush(stdout);
	fgets(s_presences, 16, stdin);

	printf("\nCountry: ");
	fflush(stdout);
	fgets(country, 36, stdin);
	country[strlen(country) - 1] = '\0';

	printf("\nCity: ");
	fflush(stdout);
	fgets(city, 48, stdin);
	city[strlen(city) - 1] = '\0';

	printf("\nStreet: ");
	fflush(stdout);
	fgets(street, 48, stdin);
	street[strlen(street) - 1] = '\0';

	printf("\nHouse number [>=0]: ");
	fflush(stdout);
	fgets(s_number, 16, stdin);

	int presences = atoi(s_presences);
	int number = atoi(s_number);


	if (!setup_prepared_stmt(&add_referee_stmt, "call aggiungi_arbitro(?, ?, ?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, add_referee_stmt, "Unable to initialize referee insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = name;
	param[0].buffer_length = strlen(name);

	param[1].buffer_type = MYSQL_TYPE_LONG;
	param[1].buffer = &presences;
	param[1].buffer_length = sizeof(presences);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[2].buffer = country;
	param[2].buffer_length = strlen(country);

	param[3].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[3].buffer = city;
	param[3].buffer_length = strlen(city);

	param[4].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[4].buffer = street;
	param[4].buffer_length = strlen(street);

	param[5].buffer_type = MYSQL_TYPE_LONG;
	param[5].buffer = &number;
	param[5].buffer_length = sizeof(number);

	if (mysql_stmt_bind_param(add_referee_stmt, param) != 0) {
		finish_with_stmt_error(conn, add_referee_stmt, "Could not bind parameters for referee insertion\n", true);
	}
	if (mysql_stmt_execute(add_referee_stmt) != 0) {
		char optionserr[2] = { '1','2' };
		char er;
		print_stmt_error(add_referee_stmt, "An error occurred trying to add the referee, what do you want to do?\n\t1)Try again;\n\t2)Quit\n");
		er = multiChoice("Select your answer: ", optionserr, 2);
		switch (er)
		{
		case '1':
			add_referee(conn);
			break;
		case '2':
			return;
		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
		}
	}
	else {
		printf("Referee correctly added\n");
		fflush(stdout);
		system("PAUSE");
		mysql_stmt_close(add_referee_stmt);
	}

}

void add_player(MYSQL* conn)
{
	MYSQL_STMT* add_player_stmt;
	MYSQL_BIND param[7];


	char name[48];
	char s_jersey[16], s_number[16];
	char country[36];
	char city[48];
	char street[48];
	char team[48];

	printf("\nName: ");
	fflush(stdout);
	fgets(name, 48, stdin);
	name[strlen(name) - 1] = '\0';

	printf("\nJersey number: ");
	fflush(stdout);
	fgets(s_jersey, 16, stdin);

	printf("\nCountry: ");
	fflush(stdout);
	fgets(country, 36, stdin);
	country[strlen(country) - 1] = '\0';

	printf("\nCity: ");
	fflush(stdout);
	fgets(city, 48, stdin);
	city[strlen(city) - 1] = '\0';

	printf("\nStreet: ");
	fflush(stdout);
	fgets(street, 48, stdin);
	street[strlen(street) - 1] = '\0';

	printf("\nHouse number [>=0]: ");
	fflush(stdout);
	fgets(s_number, 16, stdin);

	printf("\nTeam: ");
	fflush(stdout);
	fgets(team, 48, stdin);
	team[strlen(team) - 1] = '\0';

	int jersey = atoi(s_jersey);
	int number = atoi(s_number);


	if (!setup_prepared_stmt(&add_player_stmt, "call aggiungi_giocatore(?, ?, ?, ?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, add_referee, "Unable to initialize player insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = name;
	param[0].buffer_length = strlen(name);

	param[1].buffer_type = MYSQL_TYPE_LONG;
	param[1].buffer = &jersey;
	param[1].buffer_length = sizeof(jersey);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[2].buffer = country;
	param[2].buffer_length = strlen(country);

	param[3].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[3].buffer = city;
	param[3].buffer_length = strlen(city);

	param[4].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[4].buffer = street;
	param[4].buffer_length = strlen(street);

	param[5].buffer_type = MYSQL_TYPE_LONG;
	param[5].buffer = &number;
	param[5].buffer_length = sizeof(number);

	param[6].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[6].buffer = team;
	param[6].buffer_length = strlen(team);

	if (mysql_stmt_bind_param(add_player_stmt, param) != 0) {
		finish_with_stmt_error(conn, add_player_stmt, "Could not bind parameters for player insertion\n", true);
	}
	if (mysql_stmt_execute(add_player_stmt) != 0) {
		char optionserr[2] = { '1','2' };
		char er;
		print_stmt_error(add_player_stmt, "An error occurred while trying to add the player, what do you want to do?\n\t1)Try again;\n\t2)Quit\n");
		er = multiChoice("Select your answer: ", optionserr, 2);
		switch (er)
		{
		case '1':
			add_player(conn);
			break;
		case '2':
			return;
		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
		}
	}
	else {
		printf("\nPlayer correctly added\n");
		fflush(stdout);
		system("PAUSE");
		mysql_stmt_close(add_player_stmt);
	}
}

void add_goal(MYSQL* conn)
{
	MYSQL_STMT* add_goal_stmt;
	MYSQL_BIND param[6];

	char options[5] = { '1','2','3','4','5'};
	char r;



	char s_match[16], s_minute[16], s_r_minute[16];
	char tournament[20];
	signed char penalty;
	char player[48];
	int r_minute = 0;


	printf("\nMatch number: ");
	fflush(stdout);
	fgets(s_match, 16, stdin);

	printf("\nWich tournament stage this goal was scored?");
	printf("\n1)Qualifications");
	printf("\n2)Last 16");
	printf("\n3)Last 8");
	printf("\n4)Last 4");
	printf("\n5)Finals\n");
	r = multiChoice("Select the answer", options, 5);

	switch (r)
	{
	case '1':
		strcpy(tournament, "qualificazione");
		break;
	case '2':
		strcpy(tournament, "ottavi");
		break;
	case '3':
		strcpy(tournament, "quarti");
		break;
	case '4':
		strcpy(tournament, "semifinale");
		break;
	case '5':
		strcpy(tournament, "finale");
		break;
	default:
		fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
		abort();
	}

	printf("\nPlayer name: ");
	fflush(stdout);
	fgets(player, 48, stdin);
	player[strlen(player) - 1] = '\0';

	printf("\nMinute of score, exluding injury time: ");
	fflush(stdout);
	fgets(s_minute, 16, stdin);

	int match = atoi(s_match);
	int minute = atoi(s_minute);
	if (minute == 45 || minute == 90 || minute == 105 || minute == 120)
	{
		printf("\nMinute of injury time when the goal was scored (starting from 0): ");
		fflush(stdout);
		fgets(s_r_minute, 16, stdin);
		r_minute = atoi(s_r_minute);
	}

	printf("The goal was scored on a penalty?\n\t1)Yes\n\t2)No\n ");
	r = multiChoice("Select the answer: ", options, 2);

	switch (r)
	{
	case '1':
		penalty = 1;
		break;
	case '2':
		penalty = 0;
		break;
	default:
		fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
		abort();

	}

	if (!setup_prepared_stmt(&add_goal_stmt, "call aggiungi_goal(?, ?, ?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, add_goal_stmt, "Unable to initialize goal insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &match;
	param[0].buffer_length = sizeof(match);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = tournament;
	param[1].buffer_length = strlen(tournament);

	param[2].buffer_type = MYSQL_TYPE_LONG;
	param[2].buffer = &minute;
	param[2].buffer_length = sizeof(minute);

	param[3].buffer_type = MYSQL_TYPE_TINY;
	param[3].buffer = &penalty;
	param[3].buffer_length = sizeof(penalty);

	param[4].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[4].buffer = player;
	param[4].buffer_length = strlen(player);

	param[5].buffer_type = MYSQL_TYPE_LONG;
	param[5].buffer = &r_minute;
	param[5].buffer_length = sizeof(r_minute);


	if (mysql_stmt_bind_param(add_goal_stmt, param) != 0) {
		finish_with_stmt_error(conn, add_goal_stmt, "Could not bind parameters for goal insertion\n", true);
	}
	if (mysql_stmt_execute(add_goal_stmt) != 0) {
		char optionserr[2] = { '1','2' };
		char er;
		print_stmt_error(add_goal_stmt, "An error occurred while adding the goal, what do you want to do?\n\t1)Try again;\n\t2)Quit\n");
		er = multiChoice("Select your answer: ", optionserr, 2);
		switch (er)
		{
		case '1':
			add_goal(conn);
			break;
		case '2':
			return;
		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
		}
	}
	else {
		printf("\nGoal correctly added\n");
		fflush(stdout);
		system("PAUSE");
		mysql_stmt_close(add_goal_stmt);
	}
}

void add_match_and_bets(MYSQL* conn)
{
	MYSQL_STMT* add_match_stmt;
	MYSQL_BIND param[10];
	

	char options[5] = { '1','2','3','4','5'};
	char r;



	char s_match[16];
	char tournament[20];
	char team1[48], team2[48];
	char referee[48];
	char city[48];
	char year[16], month[16], day[16], hour[16], minute[16];
	char v_mult1[16], v_mult2[16], v_multp[16];




	printf("\nMatch number: ");
	fflush(stdout);
	fgets(s_match, 16, stdin);

	printf("\nWich tournament stage this match is?");
	printf("\n1)Qualifications");
	printf("\n2)Last 16");
	printf("\n3)Last 8");
	printf("\n4)Last 4");
	printf("\n5)Finals\n");
	r = multiChoice("Select the answer", options, 5);

	switch (r)
	{
	case '1':
		strcpy(tournament, "qualificazione");
		break;
	case '2':
		strcpy(tournament, "ottavi");
		break;
	case '3':
		strcpy(tournament, "quarti");
		break;
	case '4':
		strcpy(tournament, "semifinale");
		break;
	case '5':
		strcpy(tournament, "finale");
		break;
	default:
		fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
		abort();
	}


	printf("\nTeam 1 name: ");
	fflush(stdout);
	fgets(team1, 48, stdin);
	team1[strlen(team1) - 1] = '\0';

	printf("\nTeam 2 name: ");
	fflush(stdout);
	fgets(team2, 48, stdin);
	team2[strlen(team2) - 1] = '\0';

	printf("\nReferee name: ");
	fflush(stdout);
	fgets(referee, 48, stdin);
	referee[strlen(referee) - 1] = '\0';

	printf("\nCity where the match is played: ");
	fflush(stdout);
	fgets(city, 48, stdin);
	city[strlen(city) - 1] = '\0';


	MYSQL_TIME date;
	memset(&date, 0, sizeof(date));

	printf("\nYear[Ex. 2022] of the match: ");
	fflush(stdout);
	fgets(year, 16, stdin);

	date.year = atoi(year);

	printf("\nMonth[1-12] of the match: ");
	fflush(stdout);
	fgets(month, 16, stdin);

	date.month = atoi(month);
	while (date.month < 1 || date.month > 12)
	{
		printf("\nWrong data! Month[1-12] of the match:");
		fflush(stdout);
		fgets(month, 16, stdin);
		date.month = atoi(month);

	}

	printf("\nDay[1-31] of the match: ");
	fflush(stdout);
	fgets(day, 16, stdin);

	date.day = atoi(day);
	while (date.day < 1 || date.day > 31)
	{
		printf("\nWrong data! Day[1-31] of the match: ");
		fflush(stdout);
		fgets(day, 16, stdin);
		date.day = atoi(day);

	}

	printf("\nHour[0-23] of the match: ");
	fflush(stdout);
	fgets(hour, 16, stdin);

	date.hour = atoi(hour);
	while (date.hour < 0 || date.hour > 23)
	{
		printf("\nWrong data! Hour[0-23] of the match: ");
		fflush(stdout);
		fgets(hour, 16, stdin);
		date.hour = atoi(hour);

	}


	printf("\nMinute[0-59] of the match: ");
	fflush(stdout);
	fgets(minute, 16, stdin);
	date.minute = atoi(minute);
	while (date.minute < 0 || date.minute > 59)
	{
		printf("\nWrong data! Minute[0-59] of the match: ");
		fflush(stdout);
		fgets(minute, 16, stdin);
		date.minute = atoi(minute);

	}


	printf("\n In team 1 (%s) wins, what should be the bet multiplier?[>1]: ", team1);
	fflush(stdout);
	fgets(v_mult1, 16, stdin);

	printf("\n In team 2 (%s) wins, what should be the bet multiplier?[>1]: ", team2);
	fflush(stdout);
	fgets(v_mult2, 16, stdin);

	double multp;
	if (strcmp(tournament, "qualificazione") == 0)
	{
		printf("\n If noone wins, what should be the bet multiplier[>1]: ");
		fflush(stdout);
		fgets(v_multp, 16, stdin);
		multp = atof(v_multp);
	}

	double mult1 = atof(v_mult1);
	double mult2 = atof(v_mult2);
	
	int match = atoi(s_match);

	


	if (!setup_prepared_stmt(&add_match_stmt, "call aggiungi_partita_e_scommesse(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, add_match_stmt, "Unable to initialize match and bets insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &match;
	param[0].buffer_length = sizeof(match);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = tournament;
	param[1].buffer_length = strlen(tournament);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[2].buffer = team1;
	param[2].buffer_length = strlen(team1);

	param[3].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[3].buffer = team2;
	param[3].buffer_length = strlen(team2);

	param[4].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[4].buffer = referee;
	param[4].buffer_length = strlen(referee);

	param[5].buffer_type = MYSQL_TYPE_TIMESTAMP;
	param[5].buffer = &date;
	param[5].buffer_length = sizeof(date);

	param[6].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[6].buffer = city;
	param[6].buffer_length = strlen(city);

	param[7].buffer_type = MYSQL_TYPE_DOUBLE;
	param[7].buffer = &mult1;
	param[7].buffer_length = sizeof(mult1);

	param[8].buffer_type = MYSQL_TYPE_DOUBLE;
	param[8].buffer = &mult2;
	param[8].buffer_length = sizeof(mult2);

	param[9].buffer_type = MYSQL_TYPE_DOUBLE;
	param[9].buffer = &multp;
	param[9].buffer_length = sizeof(multp);


	if (mysql_stmt_bind_param(add_match_stmt, param) != 0) {
		finish_with_stmt_error(conn, add_match_stmt, "Could not bind parameters for match and bets insertion\n", true);
	}
	if (mysql_stmt_execute(add_match_stmt) != 0) {
		char optionserr[2] = { '1','2' };
		char er;
		print_stmt_error(add_match_stmt, "An error occurred while adding the match and/or the bets, what do you want to do?\n\t1)Try again;\n\t2)Quit\n");
		er = multiChoice("Select your answer: ", optionserr, 2);
		switch (er)
		{
		case '1':
			add_match_and_bets(conn);
			break;
		case '2':
			return;
		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
		}
	}
	else {
		printf("\nMatch and bets correctly added\n");
		fflush(stdout);
		system("PAUSE");
		mysql_stmt_close(add_match_stmt);
	}

	
}

void add_team(MYSQL* conn)
{
	MYSQL_STMT* add_team_stmt;
	MYSQL_BIND param[2];


	char name[48];
	char coach[48];

	printf("\nName: ");
	fflush(stdout);
	fgets(name, 48, stdin);
	name[strlen(name) - 1] = '\0';

	printf("\nCoach name: ");
	fflush(stdout);
	fgets(coach, 48, stdin);
	coach[strlen(coach) - 1] = '\0';


	if (!setup_prepared_stmt(&add_team_stmt, "call aggiungi_squadra(?, ?)", conn)) {
		finish_with_stmt_error(conn, add_team_stmt, "Unable to initialize team insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = name;
	param[0].buffer_length = strlen(name);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = coach;
	param[1].buffer_length = strlen(coach);



	if (mysql_stmt_bind_param(add_team_stmt, param) != 0) {
		finish_with_stmt_error(conn, add_team_stmt, "Could not bind parameters for team insertion\n", true);
	}
	if (mysql_stmt_execute(add_team_stmt) != 0) {
		char optionserr[2] = { '1','2' };
		char er;
		print_stmt_error(add_team_stmt, "An error occurred while adding the team, what do you want to do?\n\t1)Try again;\n\t2)Quit\n");
		er = multiChoice("Select your answer: ", optionserr, 2);
		switch (er)
		{
		case '1':
			add_team(conn);
			break;
		case '2':
			return;
		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
		}
	}
	else {
		printf("\nTeam correctly added\n");
		fflush(stdout);
		system("PAUSE");
		mysql_stmt_close(add_team_stmt);
	}
}

void add_to_qualifications(MYSQL* conn)
{
	MYSQL_STMT* add_team_qor16_stmt;
	MYSQL_BIND param[2];

	char options[2] = { '1','2' };
	char r;

	char tournament[20];
	char team[48];



	printf("\nTeam name: ");
	fflush(stdout);
	fgets(team, 48, stdin);
	team[strlen(team) - 1] = '\0';

	printf("You want to insert the team in qualifications or in last 16?\n\t1)Qualifications\n\t2)Last 16\n ");
	r = multiChoice("Select the answer: ", options, 2);

	switch (r)
	{
	case '1':
		strcpy(tournament, "qualificazione");
		break;
	case '2':
		strcpy(tournament, "ottavi");
		break;
	default:
		fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
		abort();

	}

	if (!setup_prepared_stmt(&add_team_qor16_stmt, "call aggiungi_partecipazione(?, ?)", conn)) {
		finish_with_stmt_error(conn, add_team_qor16_stmt, "Unable to initialize the team insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = tournament;
	param[0].buffer_length = strlen(tournament);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = team;
	param[1].buffer_length = strlen(team);



	if (mysql_stmt_bind_param(add_team_qor16_stmt, param) != 0) {
		finish_with_stmt_error(conn, add_team_qor16_stmt, "Could not bind parameters for team insertion\n", true);
	}
	if (mysql_stmt_execute(add_team_qor16_stmt) != 0) {
		char optionserr[2] = { '1','2' };
		char er;
		print_stmt_error(add_team_qor16_stmt, "An error occurred while trying to add the team, what do you want to do?\n\t1)Try again;\n\t2)Quit\n");
		er = multiChoice("Select your answer: ", optionserr, 2);
		switch (er)
		{
		case '1':
			add_to_qualifications(conn);
			break;
		case '2':
			return;
		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
		}
	}
	else {
		printf("\nTeam correctly added\n");
		fflush(stdout);
		system("PAUSE");
		mysql_stmt_close(add_team_qor16_stmt);
	}
}

void add_user(MYSQL* conn)
{
	MYSQL_STMT* create_user;
	MYSQL_BIND param[5];

	char options[2] = { '1','2' };
	char r;

	char name[48];
	char surname[48];
	char username[48];
	char password[48];
	char role[20];

	printf("\nName: ");
	fflush(stdout);
	fgets(name, 48, stdin);
	name[strlen(name) - 1] = '\0';

	printf("\nSurname: ");
	fflush(stdout);
	fgets(surname, 48, stdin);
	surname[strlen(surname) - 1] = '\0';

	printf("\nUsername: ");
	fflush(stdout);
	fgets(username, 48, stdin);
	username[strlen(username) - 1] = '\0';

	printf("\nPassword: ");
	fflush(stdout);
	insertPassword(password);

	printf("\nAssign the role:\n\t1)Amministratore\n\t2)Addetto sportelli");
	fflush(stdout);

	r = multiChoice("Select role: ", options, 2);
	switch (r)
	{
	case '1': 
		strcpy(role, "amministratore");
		break;
	case '2':
		strcpy(role, "addetto_sportelli");
		break;
	default: 
		fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
		abort();
	}

	if (!setup_prepared_stmt(&create_user, "call aggiungi_utente(?, ?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, create_user, "Unable to initialize user insertion statement\n", false);
	}


	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = name;
	param[0].buffer_length = strlen(name);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = surname;
	param[1].buffer_length = strlen(surname);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[2].buffer = username;
	param[2].buffer_length = strlen(username);

	param[3].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[3].buffer = password;
	param[3].buffer_length = strlen(password);

	param[4].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[4].buffer = role;
	param[4].buffer_length = strlen(role);


	if (mysql_stmt_bind_param(create_user, param) != 0) {
		finish_with_stmt_error(conn, create_user, "Could not bind parameters for user insertion\n", true);
	}
	if (mysql_stmt_execute(create_user) != 0) {
		char optionserr[2] = { '1','2' };
		char er;
		print_stmt_error(create_user, "An error occurred while trying to add the user, what do you want to do?\n\t1)Try again;\n\t2)Quit\n");
		er = multiChoice("Select your answer: ", optionserr, 2);
		switch (er)
		{
		case '1':
			add_user(conn);
			break;
		case '2':
			return;
		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
		}
	}
	else {
		printf("User correctly added\n");
		fflush(stdout);
		system("PAUSE");
		mysql_stmt_close(create_user);
	}
	
}

void run_as_administrator(MYSQL* conn)
{

	char options[9] = { '1','2','3','4','5','6','7','8','9'};
	char op;

	printf("Switching to counter administrator...\n");

	if (!parse_config("users/amministratore.json", &conf)) {
		fprintf(stderr, "Unable to load administrator configuration\n");
		exit(EXIT_FAILURE);
	}

	if (mysql_change_user(conn, conf.db_username, conf.db_password, conf.database)) {
		fprintf(stderr, "mysql_change_user() failed\n");
		exit(EXIT_FAILURE);
	}
	while (true) {
		printf("\033[2J\033[H");
		printf("1) Update the tournament\n");
		printf("2) Add a referee\n");
		printf("3) Add a player\n");
		printf("4) Add a goal\n");
		printf("5) Add a new match and its bets\n");
		printf("6) Add a team\n");
		printf("7) Add a team to the qualifications or last 16\n");
		printf("8) Add a new user\n");
		printf("9) Quit\n");

		op = multiChoice("Select an option", options, 9);

		switch (op)
		{
		case '1':
			update_tournament(conn);
			break;
		case '2':
			add_referee(conn);
			break;
		case '3':
			add_player(conn);
			break;
		case '4':
			add_goal(conn);
			break;
		case '5':
			add_match_and_bets(conn);
			break;
		case '6':
			add_team(conn);
			break;
		case '7':
			add_to_qualifications(conn);
			break;
		case '8':
			add_user(conn);
			break;
		case '9':
			return;

		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();

		}
	}
	
}
