#include "Archivo_jpeg.h"
#include "ProcesadorImagen.h"
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

void mostrarMenu() {
    std::cout << "\nMenú de opciones:" << std::endl;
    std::cout << "1. Invertir colores" << std::endl;
    std::cout << "2. Binarizar imagen" << std::endl;
    std::cout << "3. Aplicar efecto espejo" << std::endl;
    std::cout << "4. Aplicar kernel de convolución" << std::endl;
    std::cout << "5. Sumar 2 imagenes" << std::endl;
    std::cout << "6. Rotar" << std::endl;

    std::cout << "0. Salir" << std::endl;
    std::cout << "Seleccione una opción: ";
}

void ejecutarYCompararFunciones(const std::string& nombreFuncion, 
                                void (*funcNormal)(Archivo_jpeg&),
                                void (*funcOpenMP)(Archivo_jpeg&),
                                Archivo_jpeg& archivo) {
    std::cout << "\nEjecutando " << nombreFuncion << "..." << std::endl;

    // Crear copias de la imagen original para cada procesamiento
    Archivo_jpeg archivoNormal = archivo;
    Archivo_jpeg archivoOpenMP = archivo;

    // Ejecutar y medir tiempo de la versión normal
    auto inicioNormal = std::chrono::high_resolution_clock::now();
    funcNormal(archivoNormal);
    auto finNormal = std::chrono::high_resolution_clock::now();
    double tiempoNormal = std::chrono::duration<double, std::milli>(finNormal - inicioNormal).count();

    // Ejecutar y medir tiempo de la versión OpenMP
    auto inicioOpenMP = std::chrono::high_resolution_clock::now();
    funcOpenMP(archivoOpenMP);
    auto finOpenMP = std::chrono::high_resolution_clock::now();
    double tiempoOpenMP = std::chrono::duration<double, std::milli>(finOpenMP - inicioOpenMP).count();

    // Mostrar resultados
    std::cout << std::endl <<"---[TIEMPOS]------------------------------" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Tiempo de ejecución normal: " << tiempoNormal << " ms" << std::endl;
    std::cout << "Tiempo de ejecución con OpenMP: " << tiempoOpenMP << " ms" << std::endl;
    double speedup = tiempoNormal / tiempoOpenMP;
    std::cout << "Acelareacion: " << speedup << "x" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
}

int main() {
    std::string nombreArchivo;
    std::cout << "Ingrese el nombre del archivo JPEG: ";
    std::cin >> nombreArchivo;

    Archivo_jpeg archivo(nombreArchivo);
    if (!archivo.abrirArchivo()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }

    int opcion;
    do {
        mostrarMenu();
        std::cin >> opcion;

        switch(opcion) {
            case 1:
                ejecutarYCompararFunciones("Inversión de colores", 
                    ProcesadorImagen::invertirColores, 
                    ProcesadorImagen::invertirColoresOpenMP, 
                    archivo);
                break;
            case 2:
                ejecutarYCompararFunciones("Binarización de imagen", 
                    ProcesadorImagen::binarizarImagen, 
                    ProcesadorImagen::binarizarImagenOpenMP, 
                    archivo);
                break;
            case 3:
                ejecutarYCompararFunciones("Efecto espejo", 
                    ProcesadorImagen::espejoImagen, 
                    ProcesadorImagen::espejoImagenOpenMP, 
                    archivo);
                break;
            case 4:
                ejecutarYCompararFunciones("Aplicación de kernel de convolución", 
                    ProcesadorImagen::aplicarKernelConvolucion, 
                    ProcesadorImagen::aplicarKernelConvolucionOpenMP, 
                    archivo);
                break;
            case 5:
                std::string nombreArchivo2;
                std::cout << "Ingrese el nombre del archivo 2 JPEG: ";
                std::cin >> nombreArchivo;

                Archivo_jpeg archivo2(nombreArchivo2);
                if (!archivo2.abrirArchivo()) {
                    std::cerr << "No se pudo abrir el archivo." << std::endl;
                    return 1;
                }
                ejecutarYCompararFunciones("Sumar 2 imagenes", 
                    ProcesadorImagen::invertirColores, 
                    ProcesadorImagen::invertirColoresOpenMP, 
                    archivo);
                break;
            case 6:
                ejecutarYCompararFunciones("Rotar", 
                    ProcesadorImagen::invertirColores, 
                    ProcesadorImagen::invertirColoresOpenMP, 
                    archivo);
                break;

            case 0:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
        }
    } while (opcion != 0);

    return 0;
}