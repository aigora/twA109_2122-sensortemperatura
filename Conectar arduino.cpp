#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "SerialClass.h"
#include "SerialClass.cpp"
#include <string.h>

#define MAX_BUFFER 200
#define PAUSA_MS 200

int menu(void);
int menu(void)
{
	int opcion = -1;

	printf("\n   Control de la temperatura en la habitación");
	printf("\n   ===========================================");
	printf("\n\t1 - Verificar sensores de temperatura");
	printf("\n\t2 - Monitorizar sensores de TEMPERATURA");
	printf("\n\t3 - Visualizar registro de temperatura");
	printf("\n\t4 - Activar ventiladores\n");
	
	printf("\n\t0 - Cerrar el programa");
	
	scanf_s("%d", &opcion);
	return opcion;
}

void verifica_sensores(Serial*, char*);
void verifica_sensores(Serial* Arduino, char* port)
{
	float temperatura;

	if (Arduino->IsConnected())
	{
		temperatura = leer_sensor_temperatura(Arduino);
		if (temperatura != -1)
			printf("\nTemperatura: %f\n", temperatura);
	}
	else
	{
		printf("\nNo se ha podido conectar con Arduino.\n");
		printf("Revise la conexión, el puerto %s y desactive el monitor serie del IDE de Arduino.\n", port);
	}
}

float leer_sensor_temperatura(Serial*);
float leer_sensor_temperatura(Serial*)
{
	float temperatura;
	int bytesRecibidos;
	char mensaje_recibido[MAX_BUFFER];

	bytesRecibidos = Enviar_y_Recibir(Arduino, "GET_TEMPERATURA\n", mensaje_recibido);

	if (bytesRecibidos <= 0)
		temperatura = -1;
	else
		temperatura = float_from_cadena(mensaje_recibido);
	return temperatura;
}

void monitorizar_sensor_temperatura(Serial*);
void monitorizar_sensor_temperatura(Serial* Arduino)
{
	float frecuencia, temperatura;
	char tecla;
	do
	{
		printf("Establezca frecuencia de muestreo (0,5 Hz - 2,0 Hz):");
		scanf_s("%f", &frecuencia);
	} while (frecuencia < 0.5 || frecuencia>2.0);

	printf("Pulse una tecla para finalizar la monitorización\n");
	do
	{
		if (Arduino->IsConnected())
		{
			temperatura = leer_sensor_temperatura(Arduino);
			if (temperatura != -1)
				printf("%.2f ", temperatura);
			else
				printf("XXX ");
		}
		else
			printf("\nNo se ha podido conectar con Arduino.\n");
		if ((1 / frecuencia) * 1000 > PAUSA_MS)
			Sleep((1 / frecuencia) * 1000 - PAUSA_MS);
	} while (_kbhit() == 0);
	tecla = _getch();
	return;
}

float float_from_cadena(char* cadena);
float float_from_cadena(char* cadena)
{
	float numero = 0;
	int i, divisor = 10, estado = 0;


	for (i = 0; cadena[i] != '\0' && estado != 3 && i < MAX_BUFFER; i++)
		switch (estado)
		{
		case 0:
			if (cadena[i] >= '0' && cadena[i] <= '9')
			{
				numero = cadena[i] - '0';
				estado = 1;
			}
			break;
		case 1:
			if (cadena[i] >= '0' && cadena[i] <= '9')
				numero = numero * 10 + cadena[i] - '0';
			else
				if (cadena[i] == '.' || cadena[i] == ',')
					estado = 2;
				else
					estado = 3;
			break;
		case 2: 
			if (cadena[i] >= '0' && cadena[i] <= '9')
			{
				numero = numero + (float)(cadena[i] - '0') / divisor;
				divisor *= 10;
			}
			else
				estado = 3;
			break;
		}
	return numero;
}

//void visualizar_registro_temperatura(Serial*);


//void activar_ventilador(Serial* Arduino);

int Enviar_y_Recibir(Serial*, const char*, char*);
int Enviar_y_Recibir(Serial* Arduino, const char* mensaje_enviar, char* mensaje_recibir)
{
	int bytes_recibidos = 0, total = 0;
	int intentos = 0, fin_linea = 0;


	Arduino->WriteData((char*)mensaje_enviar, strlen(mensaje_enviar));
	Sleep(PAUSA_MS);

	bytes_recibidos = Arduino->ReadData(mensaje_recibir, sizeof(char) * MAX_BUFFER - 1);

	while ((bytes_recibidos > 0 || intentos < 5) && fin_linea == 0)
	{
		if (bytes_recibidos > 0)
		{
			total += bytes_recibidos;
			if (mensaje_recibir[total - 1] == 13 || mensaje_recibir[total - 1] == 10)
				fin_linea = 1;
		}
		else
			intentos++;
		Sleep(PAUSA_MS);
		bytes_recibidos = Arduino->ReadData(mensaje_recibir + total, sizeof(char) * MAX_BUFFER - 1);
	}
	if (total > 0)
		mensaje_recibir[total - 1] = '\0';

	return total;
}



int main(void)
{
	Serial* Arduino;
	char puerto[] = "COM6"; // Puerto serie al que está conectado Arduino
	int opcion_menu;


	setlocale(LC_ALL, "es-ES");
	Arduino = new Serial((char*)puerto);
	do
	
	{
 		opcion_menu = menu();
 		switch (opcion_menu)
 		{
 			case 1:
 				printf("Mostrando datos:\n");
				verifica_sensores(Arduino,puerto);
 			break;
 			case 2:
 				printf("Mostrando datos:\n");
				monitorizar_sensor_temperatura(Arduino);
 			case 3:
 				printf("Mostrando datos:\n");
 				visualizar_registro_temperatura(Arduino);
 			break;
 			case 4:
 				printf("Mostrando datos:\n");
 				activar_ventilador(Arduino);
 			break;
 			case 0:
 				printf("Fin del programa.");
 			break;
 			default: printf("\nOpción incorrecta\n");			
 		}
 	} while (opcion_menu != 5);	

	while (opcion_menu<1 || opcion_menu>4)
	{
		printf("Introduzca una opción válida:")
		scanf("%d", &opcion_menu);
	}
	
	return 0;
}
