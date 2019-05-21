#include <iostream>
#include <stdlib.h>
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
// Funciones OB
void ingresoDeDatosBinomica(Binomica&);
void ingresoDeDatosPolar(Polar&);
void ingresoDeDatosOB(Binomica&, Binomica&);
Binomica sumarBinomica(Binomica, Binomica);
void suma();
Binomica restarBinomica(Binomica, Binomica);
void resta();
Polar productoPolar(Polar, Polar);
void producto();
Polar cocientePolar(Polar, Polar);
void cociente();
void funcionOB();

// Funciones Potencia
void potenciaDeBinomica();
//double calculoPotencia(double,int);
//double combinatorio (int, int);
void funcionOA();
void radicacion();

// Funcion principal

int main() {
	int opcion;

	do {
		system("cls");
		cout << "\n" << "\t**- Bienvenido a la plataforma NCOM del grupo K3011_9 de Matematica Superior 2019. -**" << "\n" << "\n";
		cout << "Ingrese su criterio de consulta:" << "\n" << "\n";
		cout << "1. Estructura, Datos y Transformaciones (EDT)" << "\n";
		cout << "2. Operaciones Basicas (OB)" << "\n";
		cout << "3. Operaciones Avanzadas (OA)" << "\n";
		cout << "4. Suma Fasores (SF)" << "\n";
		cout << "5. Salir" << "\n" << "\n";

		cout << "Opcion: ";
		cin >> opcion;

		switch (opcion) {
			case 1:
				funcionEDT();
				break;
			case 2:
				funcionOB();
				break;
			case 3:
				funcionOA();
				break;
				//case 4
			case 5:
				cout << "\n" << "Salida con exito.\n\n" << "\n";
				break;
			default:
				cout<< "\n" << "Valor incorrecto. Vuelva a intentarlo\n\n";
				break;
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
			cout << "\n" << "Ingrese la parte real del numero complejo: ";
			cin >> binom.real;
			cout << "\n" << "Ingrese la parte imaginaria del numero complejo: ";
			cin >> binom.imaginaria;
			ImprimirBinomica(binom); // Luego de ingresar las partes real e imaginaria se lo muestra con formato
			pol = binomicaAPolar(binom); // Se hace el calculo del pasaje y se lo muestra en polar
			ImprimirPolar(pol); // Se lo muestra en forma polar
			break;
		case 2:
			cout << "\n" << "Ingrese el modulo del numero complejo: ";
			cin >> pol.modulo;
			if (pol.modulo < 0) {
				cout << "\n" << "El modulo debe ser positivo. Saliendo...\n\n";
				return;
			} else {
				cout << "\n" << "Ingrese el argumento del numero complejo: ";
				cin >> pol.argumento;
				ImprimirPolar(pol); // Luego de ingresar el modulo y argumento se lo muestra con formato
				cout << "\n";
				binom = polarABinomica(pol); // Se hace el calculo del pasaje y se lo muestra en binomica
				ImprimirBinomica(binom);
			}
			break;
		default:
			cout << "\n" << "Datos incorrectos. Saliendo . . .\n"; // Si no coincide con los criterios de busqueda
			return;
			break;
	}
	cout << "\n\n";
}

// Pasajes
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

// Calculos sobre polares
double calcularArgumento(double a, double b) {
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

double moduloBinomica(Binomica b) {
	return sqrt(b.real*b.real + b.imaginaria*b.imaginaria);
}

double argumentoEnElPrimerGiro(double arg) {
	while (arg > 2*M_PI) { // Si se pasa de mas se lo lleva al 1er giro positivo
		arg -= M_PI;
	}

	while (arg < 0) { // Si se pasa de menos tambien se lo lleva al 1er giro positivo, pero al reves que antes
		arg += M_PI;
	}
	return arg;
}


// Imprimir resultados
void ImprimirBinomica(Binomica b) {
	cout << "\n" << "Su representacion en forma binomica es: " << '(' << b.real << ',' << b.imaginaria << ')' << "\n"; // (a,b)
}

void ImprimirPolar(Polar p) {
	cout << "\n" << "Su representacion en forma polar es: " << '[' << p.modulo << ';' << p.argumento << ']' << "\n"; // [a;b]
}

// Ingreso de datos
void ingresoDeDatosBinomica(Binomica &b) {
	cout << "\n" << "Ingrese la parte real numero complejo: ";
	cin >> b.real;
	cout << "\n" << "Ingrese la parte imaginaria del numero complejo: ";
	cin >> b.imaginaria;
}

void ingresoDeDatosPolar(Polar &p) {
	cout << "\n" << "Ingrese el modulo del numero complejo: ";
	cin >> p.modulo;

	if (p.modulo < 0) {
		cout << "\n" << "El modulo debe ser positivo" << "\n";
		while (p.modulo < 0) {
			cout << "\n" << "Ingrese el modulo del numero complejo: ";
			cin >> p.modulo;
		}
	}

	cout << "\n" << "Ingrese el argumento del numero complejo: ";
	cin >> p.argumento;
}

void ingresoDeDatosOB(Binomica &b1, Binomica &b2) {
	Polar p1, p2;
	int modoC1 = 0, modoC2 = 0;

	do {
		cout << "\n" << "Complejo 1:" << "\n";
		cout << "\n" << "Escriba '1' si quiere ingresar un numero complejo en forma binomica, o '2' en forma polar: ";
		cin >> modoC1;

		switch (modoC1) {
			case 1:
				ingresoDeDatosBinomica(b1);
				break;

			case 2:
				ingresoDeDatosPolar(p1);
				b1 = polarABinomica(p1);
				break;
		}
	} while (modoC1 != 1 && modoC1 != 2);

	do {
		cout << "\n" << "Complejo 2:" << "\n";
		cout << "\n" << "Escriba '1' si quiere ingresar un numero complejo en forma binomica, o '2' en forma polar: ";
		cin >> modoC2;

		switch(modoC2) {
			case 1:
				ingresoDeDatosBinomica(b2);
				break;
			case 2:
				ingresoDeDatosPolar(p2);
				b2 = polarABinomica(p2);
				break;
		}
	} while (modoC2 != 1 && modoC2 != 2);

	return;
}

// Sumar
Binomica sumarBinomica(Binomica b1, Binomica b2) {
	Binomica suma;

	suma.real = b1.real + b2.real;
	suma.imaginaria = b1.imaginaria + b2.imaginaria;

	return suma;
}

void suma() {
	Binomica b1, b2;
	Binomica resultadoB;
	Polar resultadoP;

	ingresoDeDatosOB(b1, b2);
	resultadoB = sumarBinomica(b1, b2);
	resultadoP = binomicaAPolar(resultadoB);

	cout << "\n" << "Resultado: " << "\n";
	ImprimirBinomica(resultadoB);
	ImprimirPolar(resultadoP);

	return;
}

// Restar
Binomica restarBinomica(Binomica b1, Binomica b2) {
	Binomica resta;

	resta.real = b1.real - b2.real;
	resta.imaginaria = b1.imaginaria - b2.imaginaria;

	return resta;
}

void resta() {
	Binomica b1, b2;
	Binomica resultadoB;
	Polar resultadoP;

	ingresoDeDatosOB(b1, b2);
	resultadoB = restarBinomica(b1, b2);
	resultadoP = binomicaAPolar(resultadoB);

	cout << "\n" << "Resultado: " << "\n";
	ImprimirBinomica(resultadoB);
	ImprimirPolar(resultadoP);

	return;
}

// Multiplicar
Polar productoPolar(Polar p1, Polar p2) {
	Polar producto;

	producto.modulo = p1.modulo * p2.modulo;
	producto.argumento = p1.argumento + p2.argumento;
	producto.argumento = argumentoEnElPrimerGiro(producto.argumento);

	return producto;
}

void producto() {
	Binomica b1, b2;
	Polar p1, p2;
	Binomica resultadoB;
	Polar resultadoP;

	ingresoDeDatosOB(b1,b2);
	p1 = binomicaAPolar (b1);
	p2 = binomicaAPolar(b2);

	resultadoP = productoPolar(p1,p2);
	resultadoB = polarABinomica (resultadoP);

	cout << "\n" << "Resultado: " << "\n";
	ImprimirBinomica(resultadoB);
	ImprimirPolar(resultadoP);

	return;
}

// Dividir
Polar cocientePolar(Polar p1, Polar p2) {
	Polar cociente;

	if (p2.modulo != 0) {
		cociente.modulo = p1.modulo / p2.modulo;
		cociente.argumento = p1.argumento - p2.argumento;
		cociente.argumento = argumentoEnElPrimerGiro(cociente.argumento);

		return cociente;
	} else {
		cout << "\n" << "Cociente no valido" << "\n";
		cociente.modulo = NAN;
		cociente.argumento = p1.argumento - p2.argumento;
	}
}

void cociente() {
	Binomica b1, b2;
	Polar p1, p2;
	Binomica resultadoB;
	Polar resultadoP;

	ingresoDeDatosOB(b1,b2);
	p1 = binomicaAPolar (b1);
	p2 = binomicaAPolar(b2);

	resultadoP = cocientePolar(p1,p2);
	resultadoB = polarABinomica (resultadoP);

	cout << "\n" << "Resultado: " << "\n";
	ImprimirBinomica (resultadoB);
	ImprimirPolar (resultadoP);

	return;
}

void funcionOB() {
	system("cls");

	int opcion = 0;

	cout << "\n" << "Ingrese el numero de la operacion que desee realizar: " << "\n";
	cout << "\n" << "1. Suma" << "\n";
	cout << "2. Resta" << "\n";
	cout << "3. Producto" << "\n";
	cout << "4. Cociente" << "\n";

	cout << "\n" << "Opcion: ";
	cin >> opcion;

	switch (opcion) {
		case 1:
			suma();
			break;
		case 2:
			resta();
			break;
		case 3:
			producto();
			break;
		case 4:
			cociente();
			break;
		default:
			cout << "\n" << "Datos incorrectos. Saliendo . . .\n\n"; // Si no coincide con los criterios de busqueda
			return;
			break;
	}

	return;
}

// Operaciones Avanzadas


/*
void potenciaDeBinomica(){
	system("cls");
	
	Binomica b1;
	Binomica pot; 
	int exponente;
	double xreal;
	double yimagin;
	int sgno;
	ingresoDeDatosBinomica(b1);
	
	cout <<"\n";
	cout << "Ingrese exponente al cual desea elevar al numero complejo"<< "\n";
	cin >> exponente;
	
	for(int i=0;i<= exponente; i++){
		sgno = (i%2 == 0) ? 1 : -1;
		
		pot.real += combinatorio(exponente, 2*i)*calculoPotencia(b1.real, exponente-2*i)*calculoPotencia(b1.imaginaria, 2*i)*sgno;
		if(exponente == 2*i)  break;
		pot.imaginaria += combinatorio(exponente, 2*i+1)*calculoPotencia(b1.real, exponente-(2*i+1))*calculoPotencia(b1.imaginaria, 2*i+1)*sgno;
		// ImprimirBinomica ()
	}
		ImprimirBinomica (pot);	
	
	return;
}
double calculoPotencia(double base,int expo){
	double resultado = 1;
	for (int i = 0; i<expo; i++){
		resultado *= base;
	}
	return resultado;
}

double combinatorio (int exp, int n){
	long num = 1;
	long den = 1;
	for (int i=exp; i>exp-n; i--){
		num *=i;
		
	}
	for (int i=2; i<=n; i++){
		den *= i;
	}
	return (double)num/den;
}

*/

void funcionOA(){
	system ("cls");
	int option;
	cout<< "Ingrese el numero de operacion que desee realizar " << "\n";
	cout<< "1. Potenciacion de un Complejo Binomico"<<"\n";
	cout<< "2. Raiz n-esima "<<endl;
	cout<< " \n" <<"opcion: ";
	
	cin >> option;

	switch (option){
		case (1):
			potenciaDeBinomica();
			break;
		case(2):
			radicacion();
			break;
			
		default:
			cout<<" datos incorrectos"<<endl;
			return;	
			break;	
	}
	return;
}

void potenciaDeBinomica(){
	system("cls");
	
	Binomica b1;
	Polar pot; 
	
	int exponente;
	double xreal;
	double yimagin;
	int sgno;
	
	ingresoDeDatosBinomica(b1);
	cout <<"\n";
	cout << "Ingrese exponente al cual desea elevar al numero complejo: ";
	cin >> exponente;

	pot = binomicaAPolar(b1);

//	operacionPotencia(pot.modulo,pot.argumento);
	pot.modulo = pow(pot.modulo,exponente);
	pot.argumento *= exponente;
	b1 = polarABinomica(pot);
	ImprimirBinomica(b1);	
	
	return;
}

void radicacion(){
	Binomica b1;
	Polar radica;
	double indiceIngresado;
	Polar W[(int)indiceIngresado];
	ingresoDeDatosBinomica(b1);
	cout <<"\n";
	cout << "Ingrese el indice de raiz con el cual desea operar: ";	
	cin >> indiceIngresado;
	
	radica = binomicaAPolar(b1);
	
	for (int i=0; i< indiceIngresado ; i++){
	//revisar por que me da 1 en el modulo, cosa que no deberia pasar
		W[i].modulo =pow(radica.modulo, (1/indiceIngresado));
		W[i].argumento = (radica.argumento + (2*i*M_PI))/(int)indiceIngresado;
		
	}
	for (int i=0; i< indiceIngresado ; i++){
		cout << "W"<< i <<" es: ["<< W[i].modulo << "," << W[i].argumento <<"]"<<endl;
	}
	return;
}

