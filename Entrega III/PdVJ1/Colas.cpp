#include <iostream>
using namespace std;

struct Nodo{
	char letra;
	Nodo *siguienteNodo;
};

/*

Nuevamente vamos a modificar lo contenido en la pila por eso pasamos por 
referencia los extremos de la cola y, luego pasamos el valor a almacenar en un
nuevo nodo.

*/

void InsertarNodo(Nodo *&primero, Nodo *&ultimo, char letra)
{
	Nodo *nueva_letra = new Nodo();//reservamos la memoria para el nuevo nodo
	nueva_letra->letra = letra;//le almacenamos su valor
	nueva_letra->siguienteNodo = NULL;//le indicamos que no tiene otro nodo despues de él
	//si no es el primer nodo que insertamos en la cola...
	if (primero == NULL)
	{
		//esto se ejecuta una sola vez
		primero = nueva_letra;//el primero será el que creamos anteriomente
	}
	else
	{
		//como no es el primer nodo, vamos a decir que el siguiente del último es el que creamos
		ultimo->siguienteNodo = nueva_letra;//
	}
	//y finalmente, siempre el que creamos actualmente es el último
	ultimo = nueva_letra;
}

/*
	
	Igual que las pilas, necesito alterar los extremos y "recordar" la letra que
	quité para operar con ella

*/

void QuitarNodo(Nodo *&primero, Nodo *&ultimo, char &letra)
{
	//salvamos el valor del primer nodo
	letra = primero->letra;
	//creamos un auxiliar para dejar de reservar luego el espacio de memoria
	Nodo *aux = primero;
	//Si ´primero es igual a último significa que está vacío
	if (primero == ultimo)
	{
		primero = NULL;
		ultimo = NULL;
	}
	else//si no esá vacío quitamos siempre el primero
	{
		primero = primero->siguienteNodo;//ahora el primero es el que le sigue
	}
	delete aux;//dejo de reservar ese espacio de memoria, se la libero al sistema
	/*
	
	si no crean el auxiliar y por ende no lo "deletean" debe funcionar igual
	pero si no realizan esto van a dejar espacios de memoria reservados "de gusto"
	que el sistema puede aprovechar en otra cosa
	
	*/
}

//int main(int argc, char *argv[]) {
//	char valorObtenido;//Aquí contenemos el valor que sale de la cola
//	//La cola requiere que recordemos los dos extremos de la cola, el primero y el último
//	//iniciamos la cola vacía
//	Nodo *primero = NULL;
//	Nodo *ultimo = NULL;
//	//Insertamos un nodo pasando tres argumentos:
//	//El primer nodo, el último nodo y finalmente el valor del nuevo nodo a crear
//	InsertarNodo(primero, ultimo, 'U');
//	InsertarNodo(primero, ultimo, 'N');
//	InsertarNodo(primero, ultimo, 'L');
//	//Vamos a quitar los elementos de la cola del mismo modo que con la pila
//	while(primero != NULL)
//	{
//		QuitarNodo(primero, ultimo, valorObtenido);
//		cout<<valorObtenido;
//	}
//	/*
//	Fíjense que la cola está vacía si la recorro de nuevo porque los elementos
//	se van quitando (por ende no muestra nada):
//	*/
//	while(primero != NULL)
//	{
//		QuitarNodo(primero, ultimo, valorObtenido);
//		cout<<valorObtenido;
//	}
//	return 0;
//}

