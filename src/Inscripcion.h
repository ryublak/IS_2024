#ifndef INSCRIPCION_H
#define INSCRIPCION_H

#include <string>
#include <sstream>
using namespace std;

class Inscripcion {
private:
    string correoEstudiante;   // Email del estudiante
    string identificadorPlan;  // ID del plan de convalidación
    string estadoInscripcion;  // Estado: Pendiente o Aprobada

public:
    Inscripcion(const string& correo, const string& idPlan, const string& estado = "Pendiente") {
        asignarCorreoEstudiante(correo);
        asignarIdPlan(idPlan);
        asignarEstado(estado);
    }

    // Observadores
    string obtenerCorreoEstudiante() const { return correoEstudiante; }
    string obtenerIdPlan() const { return identificadorPlan; }
    string obtenerEstado() const { return estadoInscripcion; }

    // Modificadores
    void asignarCorreoEstudiante(const string& correo) { correoEstudiante = correo; }
    void asignarIdPlan(const string& idPlan) { identificadorPlan = idPlan; }
    void asignarEstado(const string& estado) { estadoInscripcion = estado; }

    // Método para convertir la inscripción en cadena
    string convertirACadena() const {
        return correoEstudiante + ";" + identificadorPlan + ";" + estadoInscripcion;
    }

    // Método para crear una inscripción desde una cadena
    static Inscripcion crearDesdeCadena(const string& datos) {
        stringstream flujo(datos);
        string correo, idPlan, estado;

        getline(flujo, correo, ';');
        getline(flujo, idPlan, ';');
        getline(flujo, estado, ';');

        return Inscripcion(correo, idPlan, estado);
    }
};

#endif
