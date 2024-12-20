#include "utilidades.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Rol convertirTextoARol(const string& rolStr) {
    return rolStr == "Administrador" ? Rol::ADMINISTRADOR :
           rolStr == "Profesor"      ? Rol::PROFESOR :
                                       Rol::ALUMNO;
}

vector<Usuario> cargarUsuarios(const string& archivo) {
    vector<Usuario> listaUsuarios;
    ifstream entrada(archivo);

    string linea, email, password, nombre, apellidos, rolStr;
    while (getline(entrada, linea)) {
        stringstream flujo(linea);
        getline(flujo, email, ';');
        getline(flujo, password, ';');
        getline(flujo, nombre, ';');
        getline(flujo, apellidos, ';');
        getline(flujo, rolStr, ';');

        listaUsuarios.emplace_back(email, password, nombre, apellidos, convertirTextoARol(rolStr));
    }
    return listaUsuarios;
}

vector<Plan_Convalidacion> cargarPlanes(const string& archivo) {
    vector<Plan_Convalidacion> planes;
    ifstream entrada(archivo);
    if (!entrada.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << archivo << "\n";
        return planes;
    }

    string linea;
    string id, titulacion, centro, universidad;
    vector<Asignatura> asignaturas;

    while (getline(entrada, linea)) {
        if (linea == "[Plan]") {
            asignaturas.clear(); // Limpiar asignaturas previas
            id = titulacion = centro = universidad = "";
        } else if (linea == "[Asignaturas]") {
            string codigo, nombre;
            int creditos;

            while (getline(entrada, linea) && linea != "---") {
                stringstream ss(linea);
                getline(ss, codigo, ';');
                getline(ss, nombre, ';');
                ss >> creditos;
                asignaturas.emplace_back(codigo, nombre, creditos);
            }

            Plan_Convalidacion plan(id, titulacion, centro, universidad);
            for (const auto& asignatura : asignaturas) {
                plan.agregarAsignatura(asignatura);
            }
            planes.push_back(plan);
        } else if (linea.find("ID=") == 0) {
            id = linea.substr(3);
        } else if (linea.find("Titulacion=") == 0) {
            titulacion = linea.substr(10);
        } else if (linea.find("Centro=") == 0) {
            centro = linea.substr(7);
        } else if (linea.find("Universidad=") == 0) {
            universidad = linea.substr(12);
        }
    }

    entrada.close();
    return planes;
}

void guardarPlanes(const vector<Plan_Convalidacion>& planes, const string& archivo) {
    ofstream salida(archivo);
    if (!salida.is_open()) {
        cerr << "Error: No se pudo abrir el archivo para guardar los planes.\n";
        return;
    }

    for (const auto& plan : planes) {
        salida << "[Plan]\n";
        salida << "ID=" << plan.obtenerIdentificador() << "\n";
        salida << "Titulacion=" << plan.obtenerTitulacion() << "\n";
        salida << "Centro=" << plan.obtenerCentro() << "\n";
        salida << "Universidad=" << plan.obtenerUniversidad() << "\n";

        salida << "[Asignaturas]\n";
        const auto& asignaturas = plan.obtenerAsignaturas();
        for (const auto& asignatura : asignaturas) {
            salida << asignatura.getCodigo() << ";"
                   << asignatura.getNombre() << ";"
                   << asignatura.getCreditos() << "\n";
        }
        salida << "---\n";
    }

    salida.close();
    cout << "Planes guardados correctamente en " << archivo << ".\n";
}

vector<Inscripcion> cargarInscripciones(const string& archivo) {
    vector<Inscripcion> inscripciones;
    ifstream entrada(archivo);
    string linea;

    while (getline(entrada, linea)) {
        inscripciones.push_back(Inscripcion::crearDesdeCadena(linea));
    }
    return inscripciones;
}

void guardarInscripciones(const vector<Inscripcion>& inscripciones, const string& archivo) {
    ofstream salida(archivo);
    for (const auto& insc : inscripciones) {
        salida << insc.convertirACadena() << endl;
    }
}

void crearNuevoPlan(vector<Plan_Convalidacion>& planes) {
    string id, titulo, centro, universidad;
    cout << "ID del plan: "; cin >> id;
    cout << "Titulación: "; cin.ignore(); getline(cin, titulo);
    cout << "Centro: "; getline(cin, centro);
    cout << "Universidad: "; getline(cin, universidad);

    Plan_Convalidacion nuevoPlan(id, titulo, centro, universidad);

    char agregar;
    do {
        string codigo, nombre;
        int creditos;

        cout << "Código de asignatura: "; cin >> codigo;
        cout << "Nombre de asignatura: "; cin.ignore(); getline(cin, nombre);
        cout << "Créditos: "; cin >> creditos;

        nuevoPlan.agregarAsignatura(Asignatura(codigo, nombre, creditos));
        cout << "¿Desea agregar otra asignatura? (s/n): ";
        cin >> agregar;
    } while (agregar == 's' || agregar == 'S');

    planes.push_back(nuevoPlan);
    cout << "Plan creado con éxito.\n";
}

void mostrarPlanes(const vector<Plan_Convalidacion>& planes) {
    if (planes.empty()) {
        cout << "\nNo hay planes de convalidación disponibles.\n";
        return;
    }

    cout << "\n===== LISTA DE PLANES DE CONVALIDACIÓN =====\n";
    for (const auto& plan : planes) {
        cout << "ID del Plan: " << plan.obtenerIdentificador() << endl;
        cout << "Titulación: " << plan.obtenerTitulacion() << endl;
        cout << "Centro: " << plan.obtenerCentro() << endl;
        cout << "Universidad: " << plan.obtenerUniversidad() << endl;

        // Mostrar asignaturas asociadas al plan
        const auto& asignaturas = plan.obtenerAsignaturas();
        if (asignaturas.empty()) {
            cout << "  No hay asignaturas asociadas a este plan.\n";
        } else {
            cout << "  · Asignaturas asociadas:" << endl;
            for (const auto& asignatura : asignaturas) {
                cout << "    -->  Código: " << asignatura.getCodigo()
                     << ", Nombre: " << asignatura.getNombre()
                     << ", Créditos: " << asignatura.getCreditos() << endl;
            }
        }
        cout << "-------------------------------------------\n";
    }
}

void registrarInscripcion(const string& correoEstudiante,
                          vector<Plan_Convalidacion>& planes,
                          vector<Inscripcion>& inscripciones) {
    cout << "Planes disponibles:\n";
    for (size_t i = 0; i < planes.size(); i++) {
        cout << i + 1 << ". " << planes[i].obtenerTitulacion() << " - " << planes[i].obtenerIdentificador() << "\n";
    }

    int seleccion;
    cout << "Seleccione un plan (número): ";
    cin >> seleccion;

    if (seleccion > 0 && seleccion <= planes.size()) {
        const auto& planSeleccionado = planes[seleccion - 1];
        for (const auto& insc : inscripciones) {
            if (insc.obtenerCorreoEstudiante() == correoEstudiante &&
                insc.obtenerIdPlan() == planSeleccionado.obtenerIdentificador()) {
                cout << "Ya existe una inscripción para este plan.\n";
                return;
            }
        }

        inscripciones.emplace_back(correoEstudiante, planSeleccionado.obtenerIdentificador());
        cout << "Inscripción exitosa.\n";
    } else {
        cout << "Selección inválida.\n";
    }
}

void consultarInscripciones(const string& correoEstudiante, const vector<Inscripcion>& inscripciones) {
    cout << "Sus inscripciones:\n";
    for (const auto& insc : inscripciones) {
        if (insc.obtenerCorreoEstudiante() == correoEstudiante or correoEstudiante=="") {
            cout << "Plan ID: " << insc.obtenerIdPlan()
                 << ", Estado: " << insc.obtenerEstado() << endl;
        }
    }
}

void ejecutarMenu(Usuario* usuarioActivo, vector<Plan_Convalidacion>& planes, vector<Inscripcion>& inscripciones) {
    int opcion;
    do {
        if (usuarioActivo->obtenerRol() == Rol::ADMINISTRADOR) mostrarMenuAdministrador();
        else if (usuarioActivo->obtenerRol() == Rol::PROFESOR) mostrarMenuProfesor();
        else mostrarMenuAlumno();

        cin >> opcion;

        if (usuarioActivo->obtenerRol() == Rol::ADMINISTRADOR) {
            if (opcion == 1) crearNuevoPlan(planes);
            else if (opcion == 2) mostrarPlanes(planes);
        }
        else if (usuarioActivo->obtenerRol() == Rol::ALUMNO) {
            if (opcion == 1) registrarInscripcion(usuarioActivo->obtenerEmail(), planes, inscripciones);
            else if (opcion == 2) consultarInscripciones(usuarioActivo->obtenerEmail(), inscripciones);
        }
        else if (usuarioActivo->obtenerRol() == Rol::PROFESOR) {
        	if (opcion == 1) registrarInscripcion(usuarioActivo->obtenerEmail(), planes, inscripciones);
			else if (opcion == 2) consultarInscripciones("", inscripciones);
        }
    } while (opcion != 3);
}

void mostrarMenuAdministrador() {
    cout << "\n===== MENÚ ADMINISTRADOR =====\n";
    cout << "1. Crear plan de convalidación\n";
    cout << "2. Crear destino para profesores\n";
    cout << "3. Modificar o eliminar plan de convalidación\n";
    cout << "4. Modificar o eliminar destino para profesores\n";
    cout << "5. Salir\n";
}

void mostrarMenuProfesor() {
    cout << "\n===== MENÚ PROFESOR =====\n";
    cout << "1. Introducir datos y ver destinos\n";
    cout << "2. Ver solicitudes\n";
    cout << "3. Salir\n";
}

void mostrarMenuAlumno() {
    cout << "\n===== MENÚ ALUMNO =====\n";
    cout << "1. Realizar inscripción de convalidación\n";
    cout << "2. Ver mis solicitudes\n";
    cout << "3. Salir\n";
}
