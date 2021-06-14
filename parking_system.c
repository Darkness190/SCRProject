#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int car_detected = 0;
char *plate_number[8];
int sufficient_funds = -1;
int slots_occ = 0;
int enough_slots = 0;
int initialized = 0;

void start_camera_function()
{
	
	if(initialized == 0)
	{
		srand(time(NULL));
		initialized = 1;
	}

	printf("--- start_camera_function ---\n");
	printf("(start_camera_function) Czy podjechał samochód?\n");
	scanf("%d", &car_detected);
	printf("(start_camera_function) Zapisuję %d do car_detected\n", car_detected);
}

void get_plate_data_from_image(int plate_image, int *plate_number)
{
	if(car_detected) 
	{
		printf("--- get_plate_data_from_image ---\n");
		printf("(get_plate_data_from_image) Podaj odczytaną rejestrację:\n");
		scanf("%s", plate_number);
		printf("(get_plate_data_from_image) Zapisuję %d do plate_number\n", *plate_number);
		car_detected = 0;
		
		sufficient_funds = rand() % 2;
		printf("(get_plate_data_from_image) Wylosowałem %d do sufficient_funds\n", sufficient_funds);
	}
}

void check_slots_function(int *slot_available, int *slot_unavailable)
{
	if(sufficient_funds) 
	{
		printf("--- check_slots_function ---\n");
		printf("(check_slots_function) Zajętych miejsc: (%d/5)\n", slots_occ);
		if(slots_occ < 5) 
		{
			enough_slots = 1;
			printf("(check_slots_function) Otwieram bramę\n");
		}
		else 
		{
			enough_slots = 0;
		}
		
	}
}

void display_wallet_info_function(int *message)
{
	if(!sufficient_funds) 
	{
		printf("--- display_wallet_info_function ---\n");
		printf("(display_wallet_info_function) Wyślę info o braku środków na wyświetlaczu\n");
	}
}

void display_parking_address(int data, int *address)
{
	if(!enough_slots)
	{
		printf("--- display_parking_address ---\n");
		printf("(display_parking_address) Wyślę info o najbliższym parkingu na wyświetlaczu\n");	
	}
	
}

void close_entry_gate_and_increment(int *close_entry_gate)
{
	printf("--- close_entry_gate_and_increment ---\n");
	printf("(close_entry_gate_and_increment) Zamykam bramę i inkrementuję liczbę zajętych miejsc\n");
	slots_occ++;
}


