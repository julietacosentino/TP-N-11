#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Para std::max y std::min
#include <limits>    // Para std::numeric_limits
using namespace std;

// Clase Alumno
class Alumno {
private:
    string nombre;
    int edad;
    double nota1;
    double nota2;
    double nota3;
    string estado;

    void actualizarEstado() {
        double promedio = calcularPromedio();
        estado = (promedio >= 7.0) ? "Aprobado" : "Desaprobado";
    }

public:
    Alumno(const string& nombre, int edad, double nota1, double nota2, double nota3)
        : nombre(nombre), edad(edad), nota1(nota1), nota2(nota2), nota3(nota3) {
        actualizarEstado();
    }

    string getNombre() const { return nombre; }
    int getEdad() const { return edad; }
    double getNota1() const { return nota1; }
    double getNota2() const { return nota2; }
    double getNota3() const { return nota3; }
    string getEstado() const { return estado; }

    double calcularPromedio() const {
        return (nota1 + nota2 + nota3) / 3.0;
    }

    double calcularNotaMaxima() const {
        return max({nota1, nota2, nota3});
    }

    double calcularNotaMinima() const {
        return min({nota1, nota2, nota3});
    }
};

// Buscar alumno por nombre
Alumno* buscarAlumnoPorNombre(vector<Alumno>& alumnos, const string& nombre) {
    auto it = find_if(alumnos.begin(), alumnos.end(), [&nombre](const Alumno& a) {
        return a.getNombre() == nombre;
    });
    return (it != alumnos.end()) ? &(*it) : nullptr;
}

// Calcular el promedio general
double calcularPromedioGeneral(const vector<Alumno>& alumnos) {
    if (alumnos.empty()) return 0.0;

    double sumaPromedios = 0.0;
    for (const auto& alumno : alumnos) {
        sumaPromedios += alumno.calcularPromedio();
    }
    return sumaPromedios / alumnos.size();
}

// Función para leer un número con control de errores
template<typename T>
T leerNumero(const string& mensaje) {
    T numero;
    while (true) {
        cout << mensaje;
        cin >> numero;
        if (cin.fail()) {
            cin.clear(); // Limpiar el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar el resto de la línea
            cout << "Entrada no válida. Intente de nuevo." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar el resto de la línea
            break;
        }
    }
    return numero;
}

// Función para leer una cadena con espacios
string leerCadena(const string& mensaje) {
    string cadena;
    cout << mensaje;
    getline(cin, cadena);
    return cadena;
}

int main() {
    vector<Alumno> alumnos;

    int numAlumnos = leerNumero<int>("Ingrese el número de alumnos: ");

    for (int i = 0; i < numAlumnos; ++i) {
        string nombre = leerCadena("Ingrese el nombre del alumno: ");
        int edad = leerNumero<int>("Ingrese la edad del alumno: ");
        double nota1 = leerNumero<double>("Ingrese la nota 1 del alumno: ");
        double nota2 = leerNumero<double>("Ingrese la nota 2 del alumno: ");
        double nota3 = leerNumero<double>("Ingrese la nota 3 del alumno: ");

        alumnos.emplace_back(nombre, edad, nota1, nota2, nota3);
    }

    cout << "\nDatos de los alumnos:\n";
    for (const auto& alumno : alumnos) {
        cout << "Nombre: " << alumno.getNombre() << '\n'
             << "Edad: " << alumno.getEdad() << '\n'
             << "Nota 1: " << alumno.getNota1() << '\n'
             << "Nota 2: " << alumno.getNota2() << '\n'
             << "Nota 3: " << alumno.getNota3() << '\n'
             << "Promedio: " << alumno.calcularPromedio() << '\n'
             << "Estado: " << alumno.getEstado() << '\n'
             << "Nota más alta: " << alumno.calcularNotaMaxima() << '\n'
             << "Nota más baja: " << alumno.calcularNotaMinima() << "\n\n";
    }

    string nombreBusqueda = leerCadena("Ingrese el nombre del alumno a buscar: ");

    Alumno* alumnoEncontrado = buscarAlumnoPorNombre(alumnos, nombreBusqueda);
    if (alumnoEncontrado) {
        cout << "Alumno encontrado:\n"
             << "Nombre: " << alumnoEncontrado->getNombre() << '\n'
             << "Edad: " << alumnoEncontrado->getEdad() << '\n'
             << "Promedio: " << alumnoEncontrado->calcularPromedio() << '\n'
             << "Estado: " << alumnoEncontrado->getEstado() << '\n';
    } else {
        cout << "Alumno no encontrado.\n";
    }

    double promedioGeneral = calcularPromedioGeneral(alumnos);
    cout << "\nPromedio general de todos los alumnos: " << promedioGeneral << endl;

    return 0;
}