#ifndef UTILIDADES_H
#define UTILIDADES_H

#include "Usuario.h"
#include "Plan_Convalidacion.h"
#include "Inscripcion.h"
#include <vector>
#include <string>

using namespace std;

// Conversión de cadena a Rol
Rol convertirTextoARol(const string& rolStr);

// Cargar y guardar usuarios
vector<Usuario> cargarUsuarios(const string& archivo);

// Cargar y guardar planes de convalidación
vector<Plan_Convalidacion> cargarPlanes(const string& archivo);
void guardarPlanes(const vector<Plan_Convalidacion>& planes, const string& archivo);

// Cargar y guardar inscripciones
vector<Inscripcion> cargarInscripciones(const string& archivo);
void guardarInscripciones(const vector<Inscripcion>& inscripciones, const string& archivo);

// Funciones para la gestión de planes
void crearNuevoPlan(vector<Plan_Convalidacion>& planes);
void mostrarPlanes(const vector<Plan_Convalidacion>& planes);

// Funciones para la gestión de inscripciones
void registrarInscripcion(const string& correoEstudiante,
                          vector<Plan_Convalidacion>& planes,
                          vector<Inscripcion>& inscripciones);

void consultarInscripciones(const string& correoEstudiante,
                            const vector<Inscripcion>& inscripciones);

// Funciones para mostrar menús
void mostrarMenuAdministrador();
void mostrarMenuProfesor();
void mostrarMenuAlumno();

// Función principal para ejecutar el menú
void ejecutarMenu(Usuario* usuarioActivo,
                  vector<Plan_Convalidacion>& planes,
                  vector<Inscripcion>& inscripciones);

#endif
