#ifndef ARCHIVO_JPEG_H
#define ARCHIVO_JPEG_H

#include <string>
#include <vector>
#include <jpeglib.h>

class Archivo_jpeg {
private:
    std::string nombreArchivo;
    int ancho;
    int alto;
    int numComponentes;
    std::vector<unsigned char> datosImagen;
    std::string informacionCabecera;

    std::string obtenerNombreSinExtension() const;

public:
    Archivo_jpeg(const std::string& nombre);
    Archivo_jpeg(const Archivo_jpeg& otro); // Constructor de copia
    ~Archivo_jpeg();

    bool abrirArchivo();
    bool guardarImagen(const std::string& postfijo);
    const std::vector<unsigned char>& obtenerDatosImagen() const;
    void actualizarDatosImagen(const std::vector<unsigned char>& nuevosDatos);
    int obtenerAncho() const { return ancho; }
    int obtenerAlto() const { return alto; }
    int obtenerNumComponentes() const { return numComponentes; }
    std::string obtenerNombreArchivo() const { return nombreArchivo; }
    
    std::string verDatosCabecera() const;
    std::vector<std::vector<std::vector<int>>> verSegmentoMatrizPixeles(int x1, int y1, int x2, int y2) const;
};

#endif // ARCHIVO_JPEG_H