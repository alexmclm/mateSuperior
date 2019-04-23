#include <iostream>
#include <string>
#include <math.h>
using namespace std;

// Declaracion de estructuras

struct Binomica {
	double real;
	double imaginaria;
};

struct Polar {
	double modulo;
	double argumento;
};

// Declaracion de prototipos

void ImprimirBinomica(Binomica);
void ImprimirPolar(Polar);
void funcionEDT();
Polar binomicaAPolar(Binomica);
Binomica polarABinomica(Polar);
double moduloBinomica(Binomica);
double calcularArgumento(double, double);
double argumentoEnElPrimerGiro(double);

// Funcion principal

int main() {
	int opcion;

	do {
		system("cls");
		cout << endl << "\t**- Bienvenido a la plataforma NCOM del grupo K3011_9 de Matematica Superior 2019. -**" << endl << endl;
		cout << "Ingrese su criterio de consulta:" << endl << endl;
		cout << "1. Estructura, Datos y Transformaciones (EDT)" << endl;
		cout << "2. Operaciones Basicas (OB)" << endl;
		cout << "3. Operaciones Avanzadas (OA)" << endl;
		cout << "4. Suma Fasores (SF)" << endl;
		cout << "5. Salir" << endl << endl;

		cout << "Opcion: ";
		cin >> opcion;

		switch (opcion) {
			case 1:
				funcionEDT();
				break;							
			//case 2:		
			case 5:
				cout << endl << "Salida con exito.\n\n" << endl;
				break;
			default: cout<< endl << "Valor incorrecto. Vuelva a intentarlo\n\n"; break;
		}
		
		system("PAUSE()");
		
	} while (opcion != 5);
	
	return 0;
}

void funcionEDT() {
	system("cls"); // Borra el contenido de la pantalla
	int opcion;

	Binomica binom;
	Polar pol;

	cout << "Escriba '1' si quiere ingresar un numero complejo en forma binomica, o '2' en forma polar: ";
	cin >> opcion;

	switch(opcion) {
		case 1:
			cout << endl << "Ingrese la parte real del numero complejo: ";
			cin >> binom.real;
			cout << endl << "Ingrese la parte imaginaria del numero complejo: ";
			cin >> binom.imaginaria;
			ImprimirBinomica(binom); // Luego de ingresar las partes real e imaginaria se lo muestra con formato
			pol = binomicaAPolar(binom); // Se hace el calculo del pasaje y se lo muestra en polar	
			ImprimirPolar(pol); // Se lo muestra en forma polar
			break;
		case 2:
			cout << endl << "Ingrese el modulo del numero complejo: ";
			cin >> pol.modulo;
			if (pol.modulo < 0) {
				cout << endl << "El modulo debe ser positivo. Saliendo...\n\n";
				return;
			} else {
				cout << endl << "Ingrese el argumento del numero complejo: ";
				cin >> pol.argumento;
				ImprimirPolar(pol); // Luego de ingresar el modulo y argumento se lo muestra con formato
				cout << endl;
				binom = polarABinomica(pol); // Se hace el calculo del pasaje y se lo muestra en binomica
				ImprimirBinomica(binom);
			}
			break;
		default:	cout << endl << "Datos incorrectos. Saliendo...\n\n"; // Si no coincide con los criterios de busqueda
					return; break;
	}
	cout<<"\n\n";
}

// PASAJES
Binomica polarABinomica(Polar p) {
	Binomica binom;
	binom.real= p.modulo * cos(p.argumento);
	binom.imaginaria = p.modulo * sin(p.argumento);

	return binom;
}

Polar binomicaAPolar(Binomica b) {
	Polar pol;
	pol.modulo = moduloBinomica(b); // Calculo del modulo
	pol.argumento = argumentoEnElPrimerGiro(calcularArgumento(b.real, b.imaginaria));
	return pol;
}

//CALCULOS SOBRE POLARES
double calcularArgumento(double a, double b){
	double argumento = 0;
	if (a > 0 && b > 0) { // Se encuentra en el 1er C
		argumento = atan(b/a);
	}
	if (a < 0 && b < 0 || a < 0 && b > 0) { // Se encuentra en el 3er C
		argumento = atan(b/a) + M_PI;	
	}
	if (a < 0 && b == 0) { // Se encuentra en el semieje negativo de la parte real (tiene 180 grados)
		argumento = 2*M_PI;	
	}
	if (a > 0 && b < 0) { // Se encuentra en el 4to C
		argumento = atan(b/a) + 2*M_PI;	
	}
	if (a > 0 && b == 0) { // Se encuentra en el semieje positivo de la parte real (tiene angulo nulo)
	}
	if (a == 0 && b > 0) { // Se encuentra en el semieje positivo de la parte imaginaria (tiene angulo recto)
		argumento = M_PI / 2;
	}
	if (a == 0 && b < 0) { // Se encuentra en el semieje negativo de la parte imaginaria (tiene 270 grados)
		argumento = 3 * M_PI / 2;		
	}
	if (a == 0 && b == 0) { // No tiene angulo (no es un numero)
		argumento = NAN;	
	}
	return argumento;
}

double moduloBinomica(Binomica b){
	return sqrt(b.real*b.real + b.imaginaria*b.imaginaria);
}

double argumentoEnElPrimerGiro(double arg){
	while (arg > 2*M_PI) { // Si se pasa de mas se lo lleva al 1er giro positivo
		arg -= M_PI;
	}

	while (arg < 0) { // Si se pasa de menos tambien se lo lleva al 1er giro positivo, pero al reves que antes
		arg += M_PI;
	}
	return arg;
}


//Imprimir resultados
void ImprimirBinomica(Binomica b) {
	cout << endl << "Su representacion en forma binomica es: " << '(' << b.real << ',' << b.imaginaria << ')'; // (a,b)
}

void ImprimirPolar(Polar p) {
	cout << endl << "Su representacion en forma polar es: " << '[' << p.modulo << ';' << p.argumento << ']'; // [a;b]
}
