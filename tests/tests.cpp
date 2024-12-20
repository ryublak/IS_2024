#include <gtest/gtest.h>
#include <vector>
#include "../src/Asignatura.h"
#include "../src/Inscripcion.h"
#include "../src/Plan_Convalidacion.h"
#include "../src/Usuario.h"
#include "../src/utilidades.h"
#include <fstream>

// TEST 1: Test de la clase Asignatura
TEST(AsignaturaTest, CreacionYFormato)
{
    Asignatura a("MAT123", "Matemáticas", 6);
    EXPECT_EQ(a.getCodigo(), "MAT123");
    EXPECT_EQ(a.getNombre(), "Matemáticas");
    EXPECT_EQ(a.getCreditos(), 6);

    a.setNombre("Álgebra");
    EXPECT_EQ(a.getNombre(), "Álgebra");

    EXPECT_EQ(a.formatear(), "MAT123;Álgebra;6");
}

TEST(AsignaturaTest, ParsearCadena)
{
    Asignatura b = Asignatura::parsear("FIS456;Física;4");
    EXPECT_EQ(b.getCodigo(), "FIS456");
    EXPECT_EQ(b.getNombre(), "Física");
    EXPECT_EQ(b.getCreditos(), 4);
}

// TEST 2: Test de la clase Inscripcion
TEST(InscripcionTest, CreacionYFormato)
{
    Inscripcion ins("correo@ejemplo.com", "PLAN001", "Pendiente");
    EXPECT_EQ(ins.obtenerCorreoEstudiante(), "correo@ejemplo.com");
    EXPECT_EQ(ins.obtenerIdPlan(), "PLAN001");
    EXPECT_EQ(ins.obtenerEstado(), "Pendiente");

    EXPECT_EQ(ins.convertirACadena(), "correo@ejemplo.com;PLAN001;Pendiente");
}

TEST(InscripcionTest, ParsearCadena)
{
    Inscripcion ins = Inscripcion::crearDesdeCadena("estudiante@uco.es;PLAN002;Aprobada");
    EXPECT_EQ(ins.obtenerCorreoEstudiante(), "estudiante@uco.es");
    EXPECT_EQ(ins.obtenerIdPlan(), "PLAN002");
    EXPECT_EQ(ins.obtenerEstado(), "Aprobada");
}

// TEST 3: Test de la clase Plan_Convalidacion
TEST(PlanConvalidacionTest, AgregarYEliminarAsignaturas)
{
    Plan_Convalidacion plan("PLAN001", "Ingeniería", "ETSI", "Universidad X");
    Asignatura a("MAT123", "Matemáticas", 6);

    plan.agregarAsignatura(a);
    EXPECT_TRUE(plan.contieneAsignatura("MAT123"));

    plan.eliminarAsignatura("MAT123");
    EXPECT_FALSE(plan.contieneAsignatura("MAT123"));
}

// TEST 4: Test de la clase Usuario
TEST(UsuarioTest, VerificarCredenciales)
{
    Usuario user("user@uco.es", "password123", "John", "Doe", Rol::ALUMNO);

    EXPECT_TRUE(user.verificar("user", "password123"));
    EXPECT_FALSE(user.verificar("user", "wrongpassword"));
}

// TEST 5: Test de cargar y guardar usuarios
TEST(UtilidadesTest, CargarUsuariosDesdeArchivo)
{
    // Crear archivo simulado
    std::string archivo = "usuarios_test.txt";
    std::ofstream salida(archivo);
    salida << "admin@uco.es;adminpass;Admin;User;Administrador\n";
    salida << "prof@uco.es;profpass;Prof;User;Profesor\n";
    salida.close();

    // Cargar usuarios desde el archivo
    std::vector<Usuario> usuarios = cargarUsuarios(archivo);

    // Verificar datos cargados
    ASSERT_EQ(usuarios.size(), 2);
    EXPECT_EQ(usuarios[0].obtenerEmail(), "admin@uco.es");
    EXPECT_EQ(usuarios[0].obtenerRol(), Rol::ADMINISTRADOR);
    EXPECT_EQ(usuarios[1].obtenerEmail(), "prof@uco.es");
    EXPECT_EQ(usuarios[1].obtenerRol(), Rol::PROFESOR);

    // Limpiar archivo
    std::remove(archivo.c_str());
}

// TEST 6: Test de registrar inscripciones
TEST(UtilidadesTest, RegistrarInscripcion)
{
    std::vector<Plan_Convalidacion> planes;
    std::vector<Inscripcion> inscripciones;

    // Crear plan de prueba
    Plan_Convalidacion plan("PLAN001", "Ingeniería", "ETSI", "Universidad X");
    planes.push_back(plan);

    // Registrar inscripción
    registrarInscripcion("student@uco.es", planes, inscripciones);

    // Verificar inscripción
    ASSERT_EQ(inscripciones.size(), 1);
    EXPECT_EQ(inscripciones[0].obtenerCorreoEstudiante(), "student@uco.es");
    EXPECT_EQ(inscripciones[0].obtenerIdPlan(), "PLAN001");
}

// Ejecutar todos los tests
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}