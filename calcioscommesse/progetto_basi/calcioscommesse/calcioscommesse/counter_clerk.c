#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"

#pragma warning(disable : 4996)

void add_customer(MYSQL* conn)
{
	MYSQL_STMT* add_customer_stmt;
	MYSQL_BIND param[8];


	char fiscal_code[20];
	char name[48], surname[48];
	char s_byear[16], s_number[16];
	char country[36], city[48], street[48];


	printf("\nFiscal code: ");
	fflush(stdout);
	fgets(fiscal_code, 20, stdin);
	fiscal_code[strlen(fiscal_code) - 1] = '\0';

	printf("\nName: ");
	fflush(stdout);
	fgets(name, 48, stdin);
	name[strlen(name) - 1] = '\0';

	printf("\nSurname: ");
	fflush(stdout);
	fgets(surname, 48, stdin);
	surname[strlen(surname) - 1] = '\0';

	printf("\nYear of birth[1900-2003]: ");
	fflush(stdout);
	fgets(s_byear, 16, stdin);

	printf("\nCountry of residence: ");
	fflush(stdout);
	fgets(country, 36, stdin);
	country[strlen(country) - 1] = '\0';

	printf("\nCity of residence: ");
	fflush(stdout);
	fgets(city, 48, stdin);
	city[strlen(city) - 1] = '\0';

	printf("\nStreet of residence: ");
	fflush(stdout);
	fgets(street, 48, stdin);
	street[strlen(street) - 1] = '\0';

	printf("\nHouse number[>=0]: ");
	fflush(stdout);
	fgets(s_number, 16, stdin);


	int byear = atoi(s_byear);
	int number = atoi(s_number);

	if (!setup_prepared_stmt(&add_customer_stmt, "call aggiungi_cliente(?, ?, ?, ?, ?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, add_customer_stmt, "Unable to initialize customer insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = fiscal_code;
	param[0].buffer_length = strlen(fiscal_code);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = name;
	param[1].buffer_length = strlen(name);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[2].buffer = surname;
	param[2].buffer_length = strlen(surname);

	param[3].buffer_type = MYSQL_TYPE_LONG;
	param[3].buffer = &byear;
	param[3].buffer_length = sizeof(byear);

	param[4].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[4].buffer = country;
	param[4].buffer_length = strlen(country);

	param[5].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[5].buffer = city;
	param[5].buffer_length = strlen(city);

	param[6].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[6].buffer = street;
	param[6].buffer_length = strlen(street);

	param[7].buffer_type = MYSQL_TYPE_LONG;
	param[7].buffer = &number;
	param[7].buffer_length = sizeof(number);


	if (mysql_stmt_bind_param(add_customer_stmt, param) != 0) {
		finish_with_stmt_error(conn, add_customer_stmt, "Could not bind parameters for customer insertion\n", true);
	}
	if (mysql_stmt_execute(add_customer_stmt) != 0) {
		char optionserr[2] = { '1','2' };
		char er;
		print_stmt_error(add_customer_stmt, "An error occurred while adding the customer, what do you want to do?\n\t1)Try again;\n\t2)Quit\n");
		er = multiChoice("Select your answer: ", optionserr, 2);
		switch (er)
		{
		case '1':
			add_customer(conn);
			break;
		case '2':
			return;
		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
		}
	}
	else {
		printf("\nCustomer correctly added\n");
		fflush(stdout);
		system("PAUSE");
		mysql_stmt_close(add_customer_stmt);
	}
}

void update_customer(MYSQL* conn)
{
	MYSQL_STMT* update_customer_stmt;
	MYSQL_BIND param[8];


	char fiscal_code[20];
	char name[48], surname[48];
	char s_byear[16], s_number[16];
	char country[36], city[48], street[48];


	printf("\nFiscal code of the customer you are trying to update: ");
	fflush(stdout);
	fgets(fiscal_code, 20, stdin);
	fiscal_code[strlen(fiscal_code) - 1] = '\0';

	printf("\nNew Name: ");
	fflush(stdout);
	fgets(name, 48, stdin);
	name[strlen(name) - 1] = '\0';

	printf("\nNew Surname: ");
	fflush(stdout);
	fgets(surname, 48, stdin);
	surname[strlen(surname) - 1] = '\0';

	printf("\nNew Year of birth[1900-2003]: ");
	fflush(stdout);
	fgets(s_byear, 16, stdin);

	printf("\nNew Country of residence: ");
	fflush(stdout);
	fgets(country, 36, stdin);
	country[strlen(country) - 1] = '\0';

	printf("\nNew City of residence: ");
	fflush(stdout);
	fgets(city, 48, stdin);
	city[strlen(city) - 1] = '\0';

	printf("\nNew Street of residence: ");
	fflush(stdout);
	fgets(street, 48, stdin);
	street[strlen(street) - 1] = '\0';

	printf("\nNew House number: ");
	fflush(stdout);
	fgets(s_number, 16, stdin);


	int byear = atoi(s_byear);
	int number = atoi(s_number);

	if (!setup_prepared_stmt(&update_customer_stmt, "call modifica_cliente(?, ?, ?, ?, ?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, update_customer_stmt, "Unable to initialize customer update statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = fiscal_code;
	param[0].buffer_length = strlen(fiscal_code);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = name;
	param[1].buffer_length = strlen(name);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[2].buffer = surname;
	param[2].buffer_length = strlen(surname);

	param[3].buffer_type = MYSQL_TYPE_LONG;
	param[3].buffer = &byear;
	param[3].buffer_length = sizeof(byear);

	param[4].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[4].buffer = country;
	param[4].buffer_length = strlen(country);

	param[5].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[5].buffer = city;
	param[5].buffer_length = strlen(city);

	param[6].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[6].buffer = street;
	param[6].buffer_length = strlen(street);

	param[7].buffer_type = MYSQL_TYPE_LONG;
	param[7].buffer = &number;
	param[7].buffer_length = sizeof(number);


	if (mysql_stmt_bind_param(update_customer_stmt, param) != 0) {
		finish_with_stmt_error(conn, update_customer_stmt, "Could not bind parameters for customer update\n", true);
	}
	if (mysql_stmt_execute(update_customer_stmt) != 0) {
		char optionserr[2] = { '1','2' };
		char er;
		print_stmt_error(update_customer_stmt, "An error occurred while updating the customer, what do you want to do?\n\t1)Try again;\n\t2)Quit\n");
		er = multiChoice("Select your answer: ", optionserr, 2);
		switch (er)
		{
		case '1':
			update_customer(conn);
			break;
		case '2':
			return;
		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
		}
	}
	else {
		printf("\nCustomer correctly updated\n");
		fflush(stdout);
		system("PAUSE");
		mysql_stmt_close(update_customer_stmt);
	}
}

void add_bet(MYSQL* conn)
{
	MYSQL_STMT* add_bet_stmt;
	MYSQL_BIND param[6];

	char options[5] = { '1','2','3','4','5' };
	char r;


	char customer[20];
	char tournament[20], random_code[16];
	char s_match[16], s_amount[16];
	int result;

	static char charset[] = "abcdefghijklmnopqrstuvwxyz0123456789";

	for (int n = 0;n < 15;n++) {
			int key = rand() % (int)(sizeof(charset) - 1);
			random_code[n] = charset[key];
	}

	random_code[15] = '\0';

	printf("\nGenerated code: %s", random_code);



	printf("\nFiscal code of the customer who is betting: ");
	fflush(stdout);
	fgets(customer, 20, stdin);
	customer[strlen(customer) - 1] = '\0';

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

	printf("\nWho will win?");
	printf("\n1)Noone");
	printf("\n2)Team 1");
	printf("\n3)Team 2\n");
	r = multiChoice("Select the answer", options, 2);

	switch (r)
	{
	case '1':
		result = 0;
		break;
	case '2':
		result = 1;
		break;
	case '3':
		result = 2;
		break;
	default:
		fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
		abort();
	}

	printf("\nBet amount ( >0): ");
	fflush(stdout);
	fgets(s_amount, 16, stdin);

	int match = atoi(s_match);
	double amount = atof(s_amount);

	if (!setup_prepared_stmt(&add_bet_stmt, "call aggiungi_scommessa_cliente(?, ?, ?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, add_bet_stmt, "Unable to initialize bet insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &match;
	param[0].buffer_length = sizeof(match);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = tournament;
	param[1].buffer_length = strlen(tournament);

	param[2].buffer_type = MYSQL_TYPE_LONG;
	param[2].buffer = &result;
	param[2].buffer_length = sizeof(result);

	param[3].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[3].buffer = random_code;
	param[3].buffer_length = strlen(random_code);

	param[4].buffer_type = MYSQL_TYPE_DOUBLE;
	param[4].buffer = &amount;
	param[4].buffer_length = sizeof(amount);

	param[5].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[5].buffer = customer;
	param[5].buffer_length = strlen(customer);



	if (mysql_stmt_bind_param(add_bet_stmt, param) != 0) {
		finish_with_stmt_error(conn, add_bet_stmt, "Could not bind parameters for bet insertion\n", true);
	}
	if (mysql_stmt_execute(add_bet_stmt) != 0) {
		char optionserr[2] = { '1','2' };
		char er;
		print_stmt_error(add_bet_stmt, "An error occurred while adding the bet, what do you want to do?\n\t1)Try again;\n\t2)Quit\n");
		er = multiChoice("Select your answer: ", optionserr, 2);
		switch (er)
		{
		case '1':
			add_bet(conn);
			break;
		case '2':
			return;
		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
		}
	}
	else {
		printf("\nBet correctly added\n");
		fflush(stdout);
		system("PAUSE");
		mysql_stmt_close(add_bet_stmt);
	}
}

void find_highest_multiplier(MYSQL* conn)
{
	MYSQL_STMT* find_highest_mult_stmt;


	if (!setup_prepared_stmt(&find_highest_mult_stmt, "call trova_moltiplicatore_maggiore()", conn)) {
		finish_with_stmt_error(conn, find_highest_mult_stmt, "Unable to initialize bet multiplier search query statement\n", false);
	}


	if (mysql_stmt_execute(find_highest_mult_stmt) != 0) {
		char optionserr[2] = { '1','2' };
		char er;
		print_stmt_error(find_highest_mult_stmt, "An error occurred while trying to find the match and bet multiplier, what do you want to do?\n\t1)Try again;\n\t2)Quit\n");
		er = multiChoice("Select your answer: ", optionserr, 2);
		switch (er)
		{
		case '1':
			find_highest_multiplier(conn);
			break;
		case '2':
			return;
		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
		}
	}
	else {



		dump_result_set(conn, find_highest_mult_stmt, "Bet Infos:\n");
		system("PAUSE");
		if (mysql_stmt_next_result(find_highest_mult_stmt) > 0) {
			finish_with_stmt_error(conn, find_highest_mult_stmt, "Unexpected contidion\n", true);
			system("PAUSE");
		}
	}

	mysql_stmt_close(find_highest_mult_stmt);

}

void find_matches(MYSQL* conn)
{
	MYSQL_STMT* find_matches_stmt;


	if (!setup_prepared_stmt(&find_matches_stmt, "call trova_partite_future()", conn)) {
		finish_with_stmt_error(conn, find_matches_stmt, "Unable to initialize match search query statement\n", false);
	}


	if (mysql_stmt_execute(find_matches_stmt) != 0) {
		char optionserr[2] = { '1','2' };
		char er;
		print_stmt_error(find_matches_stmt, "An error occurred while trying to find the match, what do you want to do?\n\t1)Try again;\n\t2)Quit\n");
		er = multiChoice("Select your answer: ", optionserr, 2);
		switch (er)
		{
		case '1':
			find_matches(conn);
			break;
		case '2':
			return;
		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
		}
	}
	else {



		dump_result_set(conn, find_matches_stmt, "Match Infos:\n");
		system("PAUSE");
		if (mysql_stmt_next_result(find_matches_stmt) > 0) {
			finish_with_stmt_error(conn, find_matches_stmt, "Unexpected contidion\n", true);
			system("PAUSE");
		}
	}

	mysql_stmt_close(find_matches_stmt);

}

void find_more_bets(MYSQL* conn)
{
	MYSQL_STMT* find_bets_stmt;
	int status;


	if (!setup_prepared_stmt(&find_bets_stmt, "call trova_partita_piu_scommessa()", conn)) {
		finish_with_stmt_error(conn, find_bets_stmt, "Unable to initialize match search query statement\n", false);
	}


	if (mysql_stmt_execute(find_bets_stmt) != 0) {
		char optionserr[2] = { '1','2' };
		char er;
		print_stmt_error(find_bets_stmt, "An error occurred while trying to find the player, what do you want to do?\n\t1)Try again;\n\t2)Quit\n");
		er = multiChoice("Select your answer: ", optionserr, 2);
		switch (er)
		{
		case '1':
			find_more_bets(conn);
			break;
		case '2':
			return;
		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
		}
	}
	else {


		do {
			dump_result_set(conn, find_bets_stmt, "");

			// more results? -1 = no, >0 = error, 0 = yes (keep looking)
			status = mysql_stmt_next_result(find_bets_stmt);
			if (status > 0)
				finish_with_stmt_error(conn, find_bets_stmt, "Unexpected condition", true);
		} while (status == 0);
		
	}
	system("pause");
	mysql_stmt_close(find_bets_stmt);
}

void find_turn_teams(MYSQL* conn)
{
	MYSQL_STMT* find_turn_matches_stmt;
	MYSQL_BIND param[1];

	char options[5] = { '1','2','3','4','5' };
	char r;

	char tournament[20];

	printf("\nWich tournament stage are you looking for?");
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

	if (!setup_prepared_stmt(&find_turn_matches_stmt, "call trova_sq_per_turno(?)", conn)) {
		finish_with_stmt_error(conn, find_turn_matches_stmt, "Unable to initialize matches search query statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = tournament;
	param[0].buffer_length = strlen(tournament);

	if (mysql_stmt_bind_param(find_turn_matches_stmt, param) != 0) {
		finish_with_stmt_error(conn, find_turn_matches_stmt, "Could not bind parameters for matches search query\n", true);
	}

	if (mysql_stmt_execute(find_turn_matches_stmt) != 0) {
		char optionserr[2] = { '1','2' };
		char er;
		print_stmt_error(find_turn_matches_stmt, "An error occurred while trying to find the player, what do you want to do?\n\t1)Try again;\n\t2)Quit\n");
		er = multiChoice("Select your answer: ", optionserr, 2);
		switch (er)
		{
		case '1':
			find_turn_teams(conn);
			break;
		case '2':
			return;
		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
		}
	}
	else {



		dump_result_set(conn, find_turn_matches_stmt, "Matches Infos:\n");
		system("PAUSE");
		if (mysql_stmt_next_result(find_turn_matches_stmt) > 0) {
			finish_with_stmt_error(conn, find_turn_matches_stmt, "Unexpected contidion\n", true);
			system("PAUSE");
		}
	}

	mysql_stmt_close(find_turn_matches_stmt);
}

void find_goal_beast(MYSQL* conn)
{
	MYSQL_STMT* find_goal_beast_stmt;
	int status;


	if (!setup_prepared_stmt(&find_goal_beast_stmt, "call trova_capocannoniere()", conn)) {
		finish_with_stmt_error(conn, find_goal_beast, "Unable to initialize player search query statement\n", false);
	}




	if (mysql_stmt_execute(find_goal_beast_stmt) != 0) {
		char optionserr[2] = { '1','2' };
		char er;
		print_stmt_error(find_goal_beast_stmt, "An error occurred while trying to find the player, what do you want to do?\n\t1)Try again;\n\t2)Quit\n");
		er = multiChoice("Select your answer: ", optionserr, 2);
		switch (er)
		{
		case '1':
			find_goal_beast(conn);
			break;
		case '2':
			return;
		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
		}
	}
	else {

		do {			
				dump_result_set(conn, find_goal_beast_stmt, "");
			
			// more results? -1 = no, >0 = error, 0 = yes (keep looking)
			status = mysql_stmt_next_result(find_goal_beast_stmt);
			if (status > 0)
				finish_with_stmt_error(conn, find_goal_beast_stmt, "Unexpected condition", true);
		} while (status == 0);

	}
	system("pause");
	mysql_stmt_close(find_goal_beast_stmt);
}

void find_rich_customer(MYSQL* conn)
{
	MYSQL_STMT* find_rich_customer_stmt;


	if (!setup_prepared_stmt(&find_rich_customer_stmt, "call trova_cliente_ricco()", conn)) {
		finish_with_stmt_error(conn, find_goal_beast, "Unable to initialize customer search query statement\n", false);
	}


	if (mysql_stmt_execute(find_rich_customer_stmt) != 0) {
		char optionserr[2] = { '1','2' };
		char er;
		print_stmt_error(find_rich_customer_stmt, "An error occurred while trying to find the customer, what do you want to do?\n\t1)Try again;\n\t2)Quit\n");
		er = multiChoice("Select your answer: ", optionserr, 2);
		switch (er)
		{
		case '1':
			find_rich_customer(conn);
			break;
		case '2':
			return;
		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
		}
	}
	else {



		dump_result_set(conn, find_rich_customer_stmt, "Customer and bet infos:\n");
		system("PAUSE");
		if (mysql_stmt_next_result(find_rich_customer_stmt) > 0) {
			finish_with_stmt_error(conn, find_rich_customer_stmt, "Unexpected contidion\n", true);
			system("PAUSE");
		}
	}

	mysql_stmt_close(find_rich_customer_stmt);
}

void find_highest_goaln_match(MYSQL* conn)
{
	MYSQL_STMT* find_moregoals_stmt;
	int status;

	if (!setup_prepared_stmt(&find_moregoals_stmt, "call trova_piu_goal()", conn)) {
		finish_with_stmt_error(conn, find_goal_beast, "Unable to initialize match search query statement\n", false);
	}


	if (mysql_stmt_execute(find_moregoals_stmt) != 0) {
		char optionserr[2] = { '1','2' };
		char er;
		print_stmt_error(find_moregoals_stmt, "An error occurred while trying to find the match, what do you want to do?\n\t1)Try again;\n\t2)Quit\n");
		er = multiChoice("Select your answer: ", optionserr, 2);
		switch (er)
		{
		case '1':
			find_highest_goaln_match(conn);
			break;
		case '2':
			return;
		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
		}
	}
	else {

		do {
			dump_result_set(conn, find_moregoals_stmt, "");

			// more results? -1 = no, >0 = error, 0 = yes (keep looking)
			status = mysql_stmt_next_result(find_moregoals_stmt);
			if (status > 0)
				finish_with_stmt_error(conn, find_moregoals_stmt, "Unexpected condition", true);
		} while (status == 0);

	}
	system("pause");
	mysql_stmt_close(find_moregoals_stmt);
}

void find_referee_presences(MYSQL* conn)
{
	MYSQL_STMT* find_referee_presences_stmt;
	MYSQL_BIND param[1];

	char referee[48];

	printf("\nReferee name: ");
	fflush(stdout);
	fgets(referee, 48, stdin);
	referee[strlen(referee) - 1] = '\0';

	if (!setup_prepared_stmt(&find_referee_presences_stmt, "call trova_presenze_arbitro(?)", conn)) {
		finish_with_stmt_error(conn, find_referee_presences_stmt, "Unable to initialize referee search query statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = referee;
	param[0].buffer_length = strlen(referee);

	if (mysql_stmt_bind_param(find_referee_presences_stmt, param) != 0) {
		finish_with_stmt_error(conn, find_referee_presences_stmt, "Could not bind parameters for referee search query\n", true);
	}

	if (mysql_stmt_execute(find_referee_presences_stmt) != 0) {
		char optionserr[2] = { '1','2' };
		char er;
		print_stmt_error(find_referee_presences_stmt, "An error occurred while trying to find the referee, what do you want to do?\n\t1)Try again;\n\t2)Quit\n");
		er = multiChoice("Select your answer: ", optionserr, 2);
		switch (er)
		{
		case '1':
			find_referee_presences(conn);
			break;
		case '2':
			return;
		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
		}
	}
	else {


		printf("%s presences: \n", referee);
		dump_result_set(conn, find_referee_presences_stmt, "");
		system("PAUSE");
		if (mysql_stmt_next_result(find_referee_presences_stmt) > 0) {
			finish_with_stmt_error(conn, find_referee_presences_stmt, "Unexpected contidion\n", true);
			system("PAUSE");
		}
	}

	mysql_stmt_close(find_referee_presences_stmt);

}

void less_important_functions(MYSQL* conn)
{
	char options[5] = { '1','2','3','4','5' };
	char op;
	printf("\033[2J\033[H");
	printf("1) Find the player who scored more goals\n");
	printf("2) Find the customer with the highest bet for a match\n");
	printf("3) Find the match with the highest number of goals\n");
	printf("4) Find the number of presences of a referee\n");
	printf("5) Go back\n");

	op = multiChoice("Select an option", options, 5);

	switch (op)
	{
	case '1':
		find_goal_beast(conn);
		break;
	case '2':
		find_rich_customer(conn);
		break;
	case '3':
		find_highest_goaln_match(conn);
		break;
	case '4':
		find_referee_presences(conn);
		break;
	case '5':
		return;

	default:
		fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
		abort();

	}

}

void important_funtions(MYSQL* conn)
{
	char options[9] = { '1','2','3','4','5','6','7','8','9' };
	char op;
	while (true) {
		printf("\033[2J\033[H");
		printf("*** What should I do for you? ***\n\n");
		printf("1) Add a customer\n");
		printf("2) Modify a customer data\n");
		printf("3) Add someones bet\n");
		printf("4) Find the match with the highest multiplier for a bet\n");
		printf("5) Find the matches not already played that someone can bet on\n");
		printf("6) Find the match with the highest numer of bets on it\n");
		printf("7) Find all the teams playing a game turn\n");
		printf("8) Other, less important stuff\n");
		printf("9) Quit\n");

		op = multiChoice("Select an option", options, 9);

		switch (op) {
		case '1':
			add_customer(conn);
			break;

		case '2':
			update_customer(conn);
			break;

		case '3':
			add_bet(conn);
			break;

		case '4':
			find_highest_multiplier(conn);
			break;

		case '5':
			find_matches(conn);
			break;

		case '6':
			find_more_bets(conn);
			break;

		case '7':
			find_turn_teams(conn);
			break;

		case '8':
			less_important_functions(conn);
			break;

		case '9':
			return;

		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
		}
	}


}



void run_as_counter_clerk(MYSQL* conn)
{

	printf("Switching to counter clerk role...\n");

	if (!parse_config("users/addetto_sportelli.json", &conf)) {
		fprintf(stderr, "Unable to load counter clerk configuration\n");
		exit(EXIT_FAILURE);
	}

	if (mysql_change_user(conn, conf.db_username, conf.db_password, conf.database)) {
		fprintf(stderr, "mysql_change_user() failed\n");
		exit(EXIT_FAILURE);
	}

	important_funtions(conn);
}


