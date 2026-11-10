#include <iostream>
#include <fstream>

#include "../inc/agen_E-S.h"

using std::ifstream, std::ofstream;

template <typename T>
void podaRec(Agen<T>& A, typename Agen<T>::nodo n, T elemento) {

    if(A.hijoIzqdo(n) == A.NODO_NULO) {
        A.eliminarHijoIzqdo(A.padre(n));
        return;
    } 

    for(auto hijo = A.hijoIzqdo(n); hijo != A.NODO_NULO; hijo = A.hermDrcho(hijo))
        podaRec(A, hijo, elemento);

    
    if(A.elemento(n) != elemento) A.eliminarHijoIzqdo(A.padre(n));

}

template <typename T>
bool prosperoRec(const Agen<T>& A, typename Agen<T>::nodo n, T elemento) {

    if(n == A.NODO_NULO) return true;

    if(A.elemento(n) < elemento) return false;

    return (A.hermDrcho(n) == A.NODO_NULO)?
                prosperoRec(A, A.hijoIzqdo(n), elemento):
                (prosperoRec(A, A.hijoIzqdo(n), elemento) && prosperoRec(A, A.hermDrcho(n), elemento));


}

template <typename T>
bool prospero(const Agen<T>& A, typename Agen<T>::nodo n) {

    for(auto p = n; p != A.raiz(); p = A.padre(p)) 
        if(A.elemento(n)<A.elemento(p))
            return false;

    if(n == A.raiz() || A.hijoIzqdo(n) == A.NODO_NULO) return false;

    return prosperoRec(A, A.hijoIzqdo(n), A.elemento(n));

}

template <typename T>
inline void procesarRec(Agen<T>& A, typename Agen<T>::nodo n) {

    if(n == A.NODO_NULO) return;

    if(prospero(A, n)) podaRec(A, n, A.elemento(n));

    procesarRec(A, A.hermDrcho(n));
    procesarRec(A, A.hijoIzqdo(n));

}

template <typename T>
inline void procesar(Agen<T>& A) {
    procesarRec(A, A.raiz());
}

int main() {

    Agen<int> A;

    ifstream is;
    is.open("arboles/agen/poda_esp_antes.dat");
    rellenarAgen(is,A);
    is.close();

    procesar(A);

    ofstream os;
    os.open("arboles/agen/poda_esp_despues.dat");
    imprimirAgen(os,A,-1);
    os.close();

    system("treeview g arboles/agen/poda_esp_antes.dat > /dev/null &");
    system("treeview g arboles/agen/poda_esp_despues.dat > /dev/null &");

}