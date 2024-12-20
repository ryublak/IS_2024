#include <iostream>
#include <vector>
#include <string>
#include "./src/utilidades.h"

using namespace std;

int main() {
    vector<Usuario> listaUsuarios = cargarUsuarios("usuarios.txt");
    vector<Plan_Convalidacion> listaPlanes = cargarPlanes("planes_convalidacion.txt");
    vector<Inscripcion> listaInscripciones = cargarInscripciones("inscripciones.txt");

    string nombreUsuario, contrasenaUsuario;
    bool accesoConcedido = false;
    Usuario* usuarioActual = nullptr;

    cout << "****************************************" << endl;
    cout << "*          BIENVENIDO AL SISTEMA       *" << endl;
    cout << "*             GESTOR SICUE             *" << endl;
    cout << "****************************************" << endl;

    // Proceso de autenticación
    while (!accesoConcedido) {
        cout << "\n------------- INICIO DE SESIÓN ------------\n";
        cout << "Nombre de usuario: ";
        cin >> nombreUsuario;
        cout << "Contraseña: ";
        cin >> contrasenaUsuario;

        for (auto& usuario : listaUsuarios) {
            if (usuario.verificar(nombreUsuario, contrasenaUsuario)) {
                usuarioActual = &usuario;
                accesoConcedido = true;
                break;
            }
        }

        if (!accesoConcedido) {
            cout << "¡Error! Usuario o contraseña incorrectos. Por favor, inténtelo nuevamente.\n";
        }
    }

    // Confirmación del inicio de sesión
    if (usuarioActual != nullptr) {
        cout << "\n========================================" << endl;
        cout << " Acceso autorizado: " << usuarioActual->obtenerNombre() << " "
             << usuarioActual->obtenerApellidos() << endl;

        string rolStr;
        if (usuarioActual->obtenerRol() == Rol::ADMINISTRADOR) {
            rolStr = "Administrador";
        } else if (usuarioActual->obtenerRol() == Rol::PROFESOR) {
            rolStr = "Profesor";
        } else if (usuarioActual->obtenerRol() == Rol::ALUMNO) {
            rolStr = "Alumno";
        }
        cout << " Rol: " << rolStr << endl;
        cout << "========================================" << endl;

        ejecutarMenu(usuarioActual, listaPlanes, listaInscripciones);
    }

    // Guardar los cambios en los archivos
    cout << "\nGuardando cambios en los archivos..." << endl;
    guardarPlanes(listaPlanes, "planes_convalidacion.txt");
    guardarInscripciones(listaInscripciones, "inscripciones.txt");
    cout << "Cambios guardados exitosamente. ¡Hasta la próxima!" << endl;

    return 0;
}
