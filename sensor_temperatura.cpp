#include<stdlib.h>
#include<stdio.h>

int main (void)
{
	
	char opcion;

	printf("Seleccione una opcion:\n");
	printf("A: Temperatura actual\n");
	printf("B: Temperatura del dia\n");
	printf("C: Temperatura de la semana\n");
	scanf_s("%c", &opcion);


	return 0;
}