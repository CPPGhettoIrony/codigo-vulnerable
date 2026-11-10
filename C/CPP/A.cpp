#include <iostream>
#include <fstream>

#include "../inc/abin_E-S.h"

using std::ifstream, std::ofstream;

typename Abin<int>::nodo ultimo(const Abin<int>& A, typename Abin<int>::nodo n) {

    if(A.hijoDrcho(n) == A.NODO_NULO && A.hijoIzqdo(n) == A.NODO_NULO) return n; 
    if(A.hijoDrcho(n) == A.NODO_NULO) return ultimo(A, A.hijoIzqdo(n));
    return ultimo(A, A.hijoDrcho(n));

}

typename Abin<int>::nodo busqueda(const Abin<int>& A, typename Abin<int>::nodo n, int elemento) {

    if(n == A.NODO_NULO) return n;
    if(A.elemento(n) == elemento) return n;

    auto i = busqueda(A, A.hijoIzqdo(n), elemento);
    auto d = busqueda(A, A.hijoDrcho(n), elemento);

    if(i != A.NODO_NULO) return i;
    if(d != A.NODO_NULO) return d;

    return A.NODO_NULO;

}

void hundir(Abin<int>& A, typename Abin<int>::nodo n) {

    auto i = A.hijoIzqdo(n);
    auto d = A.hijoDrcho(n);

    if(i == A.NODO_NULO && d == A.NODO_NULO) return;

    typename Abin<int>::nodo h;

    if(d == A.NODO_NULO) h = i;
    else if(i == A.NODO_NULO) h = d;
    else h = (A.elemento(i)<A.elemento(d))?i:d;

    if(A.elemento(n) < A.elemento(h)) return;

    int tmp = A.elemento(n);
    A.elemento(n) = A.elemento(h);
    A.elemento(h) = tmp;
    hundir(A, h);

}

void eliminarApo(Abin<int>& A, int elemento){


    auto h = busqueda(A, A.raiz(), elemento);
    auto s = ultimo(A, A.raiz());

    if(A.hijoIzqdo(h) == A.NODO_NULO && A.hijoDrcho(h) == A.NODO_NULO) {
            if(A.hijoIzqdo(A.padre(h)) == h) A.eliminarHijoIzqdo(A.padre(h));
            else A.eliminarHijoDrcho(A.padre(h));
            return;
    }

    A.elemento(h) = A.elemento(s);
    
    if(A.hijoIzqdo(A.padre(s)) == s) A.eliminarHijoIzqdo(A.padre(s));
    else A.eliminarHijoDrcho(A.padre(s));

    hundir(A, h);

}

int main() {

    Abin<int> A;

    ifstream is;
    is.open("arboles/abin/apo_antes.dat");
    rellenarAbin(is,A);
    is.close();

    eliminarApo(A, 1);
    eliminarApo(A, 6);
    eliminarApo(A, 14);
    eliminarApo(A, 3);
    eliminarApo(A, 15);
    eliminarApo(A, 4);

    ofstream os;
    os.open("arboles/abin/apo_despues.dat");
    imprimirAbin(os,A,-1);
    os.close();

    system("treeview b arboles/abin/apo_antes.dat > /dev/null &");
    system("treeview b arboles/abin/apo_despues.dat > /dev/null &");

}