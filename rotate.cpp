#include <cmath>
#include <iostream> // Include this for std::cerr
#include <vector>
#include "Archivo_jpeg.h"

void rotate90(Archivo_jpeg& jpeg) {
    int h = jpeg.obtenerAlto(); // Use getter method
    int w = jpeg.obtenerAncho(); // Use getter method
    int numComponentes = jpeg.obtenerNumComponentes(); // Use getter method
    
    std::vector<unsigned char> original = jpeg.obtenerDatosImagen();
    std::vector<unsigned char> rotated(w * h * numComponentes);
    
    // Rotate the image 90 degrees clockwise
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            for (int c = 0; c < numComponentes; ++c) {
                rotated[(x * h + (h - y - 1)) * numComponentes + c] =
                    original[(y * w + x) * numComponentes + c];
            }
        }
    }

    jpeg.actualizarDatosImagen(rotated); // Update the image data
}

int main() {
    Archivo_jpeg jpeg("imagen.jpg");
    if (!jpeg.abrirArchivo()) {
        std::cerr << "Error al abrir el archivo de imagen." << std::endl;
        return 1;
    }

    rotate90(jpeg);
    jpeg.guardarImagen("_rotated");

    std::cout << "Imagen rotada guardada con éxito." << std::endl;
    return 0;
}
