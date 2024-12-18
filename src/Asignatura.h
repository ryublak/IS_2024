#ifndef ASIGNATURA_H
#define ASIGNATURA_H

#include <string>
#include <sstream>
using namespace std;

class Asignatura {
private:
    string codigo;
    string nombre;
    int creditos;

public:
    Asignatura() {}

    Asignatura(const string& cod, const string& nom, int cred) {
        setCodigo(cod);
        setNombre(nom);
        setCreditos(cred);
    }

    // Observadores
    string getCodigo() const { return codigo; }
    string getNombre() const { return nombre; }
    int getCreditos() const { return creditos; }

    // Modificadores
    void setCodigo(const string& cod) { codigo = cod; }
    void setNombre(const string& nom) { nombre = nom; }
    void setCreditos(int cred) { creditos = cred; }

    // Método que devuelve la asignatura como una cadena
    string formatear() const {
        stringstream resultado;
        resultado << getCodigo() << ";" << getNombre() << ";" << getCreditos();
        return resultado.str();
    }

    // Método que crea una asignatura a partir de una cadena
    static Asignatura parsear(const string& datos) {
        stringstream flujo(datos);
        string cod, nom;
        int cred = 0;

        getline(flujo, cod, ';');
        getline(flujo, nom, ';');
        flujo >> cred;

        Asignatura nueva;
        nueva.setCodigo(cod);
        nueva.setNombre(nom);
        nueva.setCreditos(cred);
        return nueva;
    }

    // Método adicional: Verifica si la asignatura tiene más de 6 créditos
    bool esAltoCredito() const {
        return getCreditos() > 6;
    }
};
#endif
