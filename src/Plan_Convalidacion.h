#ifndef PLAN_CONVALIDACION_H
#define PLAN_CONVALIDACION_H

#include <vector>
#include <string>
#include <sstream>
#include "Asignatura.h"
using namespace std;

class Plan_Convalidacion {
private:
    string identificador, nombreTitulacion, nombreCentro, nombreUniversidad;
    vector<Asignatura> listaAsignaturas;

public:
    Plan_Convalidacion(const string& id, const string& titulacion, const string& centro, const string& universidad) {
        asignarIdentificador(id);
        asignarTitulacion(titulacion);
        asignarCentro(centro);
        asignarUniversidad(universidad);
    }

    string obtenerIdentificador() const { return identificador; }
    string obtenerTitulacion() const { return nombreTitulacion; }
    string obtenerCentro() const { return nombreCentro; }
    string obtenerUniversidad() const { return nombreUniversidad; }
    const vector<Asignatura>& obtenerAsignaturas() const { return listaAsignaturas; }

    void asignarIdentificador(const string& id) { identificador = id; }
    void asignarTitulacion(const string& titulacion) { nombreTitulacion = titulacion; }
    void asignarCentro(const string& centro) { nombreCentro = centro; }
    void asignarUniversidad(const string& universidad) { nombreUniversidad = universidad; }
    void agregarAsignatura(const Asignatura& asignatura) { listaAsignaturas.push_back(asignatura); }

    void eliminarAsignatura(const string& codigo) {
        for (size_t i = 0; i < listaAsignaturas.size(); ++i) {
            if (listaAsignaturas[i].getCodigo() == codigo) {
                listaAsignaturas.erase(listaAsignaturas.begin() + i);
                return;
            }
        }
    }

    string serializar() const {
        stringstream resultado;
        resultado << identificador << ";" << nombreTitulacion << ";"
                  << nombreCentro << ";" << nombreUniversidad;
        for (const auto& asignatura : listaAsignaturas) {
        	string aux = "";
        	asignatura.parsear(aux);
            resultado << "\n" << aux;
        }
        return resultado.str();
    }

    static Plan_Convalidacion deserializar(const string& datos) {
        stringstream flujo(datos);
        string id, titulacion, centro, universidad, asignaturaLinea;

        getline(flujo, id, ';');
        getline(flujo, titulacion, ';');
        getline(flujo, centro, ';');
        getline(flujo, universidad, '\n');

        Plan_Convalidacion nuevoPlan(id, titulacion, centro, universidad);

        while (getline(flujo, asignaturaLinea)) {
            nuevoPlan.agregarAsignatura(Asignatura::parsear(asignaturaLinea));
        }

        return nuevoPlan;
    }

    bool contieneAsignatura(const string& codigo) const {
        for (const auto& asignatura : listaAsignaturas) {
            if (asignatura.getCodigo() == codigo) return true;
        }
        return false;
    }
};

#endif
