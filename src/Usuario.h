#ifndef USUARIO_H
#define USUARIO_H

#include <string>
using std::string;

enum class Rol { ADMINISTRADOR, PROFESOR, ALUMNO };

class Usuario {
private:
    string email, password, nombre, apellidos;
    Rol rolUsuario;

public:
    Usuario(const string& e, const string& p, const string& n, const string& a, Rol r) {
        asignarEmail(e);
        asignarPassword(p);
        asignarNombre(n);
        asignarApellidos(a);
        asignarRol(r);
    }

    string obtenerEmail() const { return email; }
    string obtenerPassword() const { return password; }
    string obtenerNombre() const { return nombre; }
    string obtenerApellidos() const { return apellidos; }
    Rol obtenerRol() const { return rolUsuario; }

    void asignarEmail(const string& e) { email = e; }
    void asignarPassword(const string& p) { password = p; }
    void asignarNombre(const string& n) { nombre = n; }
    void asignarApellidos(const string& a) { apellidos = a; }
    void asignarRol(Rol r) { rolUsuario = r; }

    bool verificar(const string& u, const string& p) const {
        string correo = u + "@uco.es";
        return correo == email && p == password;
    }

    string obtenerCadena() const {
        string resultado = email + ";" + password + ";" + nombre + ";" + apellidos + ";";
        if (rolUsuario == Rol::ADMINISTRADOR) resultado += "Administrador";
        else if (rolUsuario == Rol::PROFESOR) resultado += "Profesor";
        else resultado += "Alumno";
        return resultado;
    }
};

#endif
