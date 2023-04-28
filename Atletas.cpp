#include <iostream>
#include <malloc.h>
#include <cstring>
#include <algorithm>

using namespace std;

struct Times
{
    int contador = 0;
    double time[100];
    double promedio = 0;
};

struct corredor
{
    char nombre[50];
    int nasignado;
    Times estruc2;
    corredor *sig;
};

corredor *cab, *aux, *aux2;

int numero;

// Regustro de deportistas 

int registrar()
{

    if (cab == NULL)
    {

        cab = (struct corredor *)malloc(sizeof(struct corredor));

        cout << "Ingrese el nombre del deportista: ";
        cin >> cab->nombre;

        cout << "Ingrese el numero de la camiseta del deportista: ";
        cin >> cab->nasignado;
        cab->estruc2.time[100] = {0};
        for (int i = 0; i < 100; i++)
        {
            cab->estruc2.time[i] = 0;
        }
        cab->estruc2.contador = 0;

        cab->sig = NULL;
    }
    else
    {
        aux = (struct corredor *)malloc(sizeof(struct corredor));

        cout << "ingrese el nombre del deportista: ";
        cin >> aux->nombre;

        cout << "Ingrese el numero de la camiseta del deportista: ";
        cin >> aux->nasignado;
        aux->estruc2.time[100] = {0};
        for (int i = 0; i < 100; i++)
        {
            aux->estruc2.time[i] = 0;
        }
        aux->estruc2.contador = 0;

        aux->sig = NULL;
        aux2 = cab;

        while (aux2->sig != NULL)

        aux2 = aux2->sig;
        aux2->sig = aux;
        aux2 = aux = NULL;
        free(aux);
        free(aux2);
    }
    return 0;
}

int correr()
{
    double tiempo;
    double siguiente = 0;
    double resultado;
    aux = (struct corredor *)malloc(sizeof(struct corredor));

    aux->sig = NULL;
    aux2 = cab;
    int camisa;
    bool encontrado = false;
    cout << "Ingrese el numero de la camiseta: ";
    cin >> camisa;

    for (aux2 = cab; aux2 != NULL; aux2 = aux2->sig)
    {
        if (camisa == aux2->nasignado)
        {
            
            cout << "Ingrese el tiempo: ";
            cin >> tiempo;
            int contador = 0;
            contador += aux2->estruc2.contador;
            aux2->estruc2.time[contador] = tiempo;
            aux2->estruc2.contador++;
            encontrado = true;

            for (int i = 0; i < 100; i++)
            {
                double actual = aux2->estruc2.time[i];
                resultado = (actual + siguiente);
                siguiente = resultado;
            }
            if (aux2->estruc2.contador == 1)
            {
                double promedio = resultado;
                aux2->estruc2.promedio = promedio;

                aux2 = aux = NULL;
                cout << "Registro Exitoso";
                break;
            }else{
                int cantidad = 0;
                cantidad = aux2->estruc2.contador;

                double promedio = resultado/cantidad;
                aux2->estruc2.promedio = promedio;
                aux2 = aux = NULL;
                cout << "Registro Exitoso";
                break;
            }
        }
    }

    if (encontrado == false)
    {
        printf("No se encontro al deportista, por favor verifique su informacion");
    }
    return 0;
}

int mostrar()
{

    int i = 1;
    int j = 0;
    cout << " \t\t\tLista de participante " << endl;
    cout << "\n";
    cout << "\n";

    for (aux = cab; aux != NULL; aux = aux->sig)
    {
        cout << i++ << ".corredor  camisa #" << aux->nasignado << " Nombre: " << aux->nombre << "  Tiempo: " << aux->estruc2.promedio << endl;
        j++;
    }

    return 0;
}

void ordenar_FIFO_desc(struct corredor *inicio)
{
    struct corredor *actual = inicio;
    while (actual != NULL)
    {
        struct corredor *mayor = actual;
        struct corredor *sig = actual->sig;
        while (sig != NULL)
        {
            if (sig->estruc2.promedio > mayor->estruc2.promedio)
            {
                mayor = sig;
            }
            sig = sig->sig;
        }
        double temp = actual->estruc2.promedio;
        int tamp = actual->nasignado;
        char nom[20];
        memcpy(nom, actual->nombre, 20);

        actual->estruc2.promedio = mayor->estruc2.promedio;
        mayor->estruc2.promedio = temp;

        actual->nasignado = mayor->nasignado;
        mayor->nasignado = tamp;

        memcpy(actual->nombre, mayor->nombre, 20);
        memcpy(mayor->nombre, nom, 20);
        actual = actual->sig;
    }
}

int main()
{

    int opc = 0;
    do
    {
        cout << endl;
        cout << endl;
        cout << "<<  SISTEMA DE ATLETAS  >>" << endl;
        cout << endl;
        cout << "1.REGISTRAR DE DEPORTISTAS" << endl;
        cout << "2.REGISTRAR DEL TIEMPO DE LOS DEPORTISTAS" << endl;
        cout << "3.CALCULO Y INFORMACION DE LOS DEPORTISAS " << endl;
        cout << "4.SALIR" << endl;
        cin >> opc;

        switch (opc)
        {
        case 1:
            registrar();
            break;

        case 2:
            correr();

            break;
        case 3:
            ordenar_FIFO_desc(cab);
            mostrar();

            break;

        default:
            break;
        }

    } while (opc != 4);

    return 0;
}