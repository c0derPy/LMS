#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Se definen los codigos de operacion a usar por la LMS

// Operaciones de entrada/salida
#define READ 10
#define WRITE 11

// Operaciones de cargar/almacenar
#define LOAD 20
#define STORE 21

// Operaciones aritmeticas
#define ADD 30
#define SUBSTRACT 31
#define DIVIDE 32
#define MULTIPLY 33

// Operaciones de transferencia de control
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42

// Terminar Programa
#define HALT 43

// Tamaño de la memoria
#define MEMORY_SIZE 100

// Ver instrucciones almacenadas en la memoria
void show_memory();
// Vaciado de memoria
void empty_memory();
// Iniciar la carga de instrucciones en memoria de simpletron
void load_program();
// Leer programa desde un archivo
void load_from_file(char *argv[]);
// Memoria de Simpletron
int memory[MEMORY_SIZE] = {+0000};

int main(int argc, char *argv[]){
		
	// Mensaje de Bienvenida
	printf("\t\t** Welcome to simpletron! **\n");
	printf("\t\t** Please enter your program one instruction **\n");
	printf("\t\t** (or data word) at a time. I will type the **\n");
	printf("\t\t** location number and a question mark (?).  **\n");
	printf("\t\t** you then type the word for that location. **\n");
	printf("\t\t** Type the sentinel -99999 to stop entering **\n");
	printf("\t\t** your program. **\n\n");

	// Representa el registro de accumulator
	int accumulator = 0;
	// Lleva el control de la posicion en memoria(array) de la instruccion
	int instructionCounter = 0;
	// Indica la Operacion en el momento de ejecucion 
	int operationCode = 0;
	// Indica posicion en memoria de la instruccion actual
	int operand = 0;
	// Las instrucciones no se ejecutan desde la memoria si no que se transfieren a esta variable
	int instructionRegister = 0;
		
	if(argc > 0) {
		// Cargar programa en memoria desde un archivo de texto
		load_from_file(argv);	
	}else{
		//Cargar programa en memoria desde el programa	
		load_program();
	}

	
	// Ejecutar programa
	while(operationCode != HALT){
		instructionRegister = memory[instructionCounter];	
		operationCode = instructionRegister / 100;
		operand = instructionRegister % 100;
		int i;
		switch(operationCode){
			// Entrada
			case READ:
				printf("Ingrese dato:");
				scanf("%d", &memory[operand]);			
				break;
			// Aritmetica
			case LOAD:
				accumulator = memory[operand];			
				break;
			case ADD:
				accumulator += memory[operand];				
				break;
			case SUBSTRACT:
				accumulator -= memory[operand];
				break;
			case MULTIPLY:
				accumulator *= memory[operand];
				break;
			case DIVIDE:
				if(memory[operand] != 0){
					accumulator /= memory[operand];						
				}else{
					printf("** Attempt to divide by zero **\n");
					printf("** Simpletron execution abnormally terminated **\n");
					operationCode = HALT;	
				}
				break;
			// Transferencias de control
			case BRANCH:
				instructionCounter = operand;
				continue;
				break;
			case BRANCHNEG:
				if(accumulator < 0){
					instructionCounter = operand;
					//Para que no cambie el valor de instructionCounter
					//al aumentarle 1 al final del bucle					
					continue; 
				}
				break;
			case BRANCHZERO:
				if(accumulator == 0){
					instructionCounter = operand;
					continue;
				}				
				break;
			// Almacenar y escribir
			case STORE:
				memory[operand] = accumulator;
				break;
			case WRITE:
				printf("Imprimir: %d\n", memory[operand]);
				break;
			case HALT:	
				printf("** Simpletron execution terminated **\n\n");	
				printf("REGISTERS: \n");
				printf("accumulator: %d\n", accumulator);
				printf("instructionCounter: %d\n", instructionCounter);
				printf("instructionRegister: %d\n", instructionRegister);
				printf("operationCode: %d\n", operationCode);
				printf("operand: %d\n\n", operand);
				show_memory();
				empty_memory();		
				break;
		}
	
		++instructionCounter;
	}	

	return 0;		
}

void load_program(){

	int i = 0, codigo;

	printf("%d ? ", i);
	scanf("%d", &codigo);	
	//Termino cuando se ingrese el centinela -99999
	while(codigo != -99999){
		// El codigo debe estar dentro de este rango
		if(codigo >= -9999 && codigo <= 9999){
			memory[i] = codigo;	
			i++;
			printf("%d ? ", i);
			scanf("%d", &codigo);					
		}else{
			printf("Instruccion (codigo) no valido, vuelva a ingresar el codigo!\n");	
			printf("%d ? ", i);
			scanf("%d", &codigo);		
		}		
	}

	printf("** Program loading completed **\n");
	printf("** Program execution begins **\n\n");	
}

void show_memory(){
	printf("MEMORY: \n");
	int i;
	for(i = 1; i <= MEMORY_SIZE; i++){
		if(memory[i-1] == 0){
			printf("000%d \t", memory[i]);
		}else{
			printf("%d \t", memory[i]);
		}
					
		if(i % 10 == 0){
			printf("\n");
		}
	}
}

void empty_memory(){
	int i;
	for(i = 0; i < MEMORY_SIZE; i++){
		memory[i] = 0;	
	}
}

void load_from_file(char *argv[]){
	FILE* file_code;
	char file_name[100] = argv[1];
	char line[5];
	int code;
	int i = 0;	

	file_code = fopen(file_name, "rt");

	//Si el archivo esta vacio termino el programa
	if(file_code == NULL){
		printf("Simpletron execution terminated file code is empty");
		exit(1);
	}
	// Leo el archivo mientras no llegue al final
	while(!feof(file_code)){
		fgets(line, 5, file_code); // Guardo la linea en la var line
		if(!feof(file_code)){
			//Implementar carga en memoria	
			code = atoi(line); // Parseo a entero el char
			if(code >= -9999 && code <= 9999 && code != 0){				
				memory[i] = code;
				//printf("%d - ", code);				
				i++;
			}
			
		}
	}		
	fclose(file_code);

}





