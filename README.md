# Procesador de Imágenes JPEG con OpenMP

Este programa es un procesador de imágenes JPEG que permite realizar varias operaciones de manipulación de imágenes, incluyendo inversión de colores, binarización, efecto espejo y aplicación de kernel de convolución. Además, incluye versiones paralelas de estas operaciones utilizando OpenMP para mejorar el rendimiento en sistemas con múltiples núcleos.

## Requisitos

- C++ 11 o superior
- Biblioteca libjpeg
- OpenMP

## Instalación de Librerías

### En sistemas basados en Debian/Ubuntu:

```bash
sudo apt-get update
sudo apt-get install libjpeg-dev
sudo apt-get install libomp-dev
```

### En sistemas basados en Red Hat/Fedora:

```bash
sudo dnf install libjpeg-devel
sudo dnf install libomp-devel
```

### En macOS (usando Homebrew):

```bash
brew install libjpeg
brew install libomp
```

## Compilación

Para compilar el programa con soporte para OpenMP, usa el siguiente comando:

```bash
make
```

Asegúrate de que tu Makefile incluya las flags necesarias para OpenMP, por ejemplo:

```makefile
CXXFLAGS += -fopenmp
LDFLAGS += -fopenmp
```

## Uso del Programa

Para ejecutar el programa:

```bash
./procesador_imagen
```

Sigue las instrucciones en pantalla para seleccionar una imagen JPEG y aplicar las diferentes operaciones de procesamiento, incluyendo las versiones paralelas con OpenMP.

## OpenMP en el Procesamiento de Imágenes

OpenMP (Open Multi-Processing) es una API que soporta programación multiproceso de memoria compartida en múltiples plataformas. Se utiliza para paralelizar secciones de código, permitiendo que se ejecuten simultáneamente en varios núcleos de procesador.

### Uso de OpenMP en las Funciones de Procesamiento

1. **Inversión de Colores (OpenMP)**
   ```cpp
   #pragma omp parallel for
   for (int i = 0; i < tamanio; ++i) {
       datosModificados[i] = 255 - datosOriginales[i];
   }
   ```
   Se usa un simple `parallel for` porque cada píxel puede ser procesado independientemente.

2. **Binarización (OpenMP)**
   ```cpp
   #pragma omp parallel for collapse(2)
   for (int y = 0; y < alto; ++y) {
       for (int x = 0; x < ancho; ++x) {
           // ... procesamiento ...
       }
   }
   ```
   Se utiliza `collapse(2)` para paralelizar ambos bucles, ya que cada píxel puede ser procesado independientemente.

3. **Efecto Espejo (OpenMP)**
   ```cpp
   #pragma omp parallel for
   for (int y = 0; y < alto; ++y) {
       // ... procesamiento ...
   }
   ```
   Se paraleliza solo el bucle exterior porque cada fila puede ser procesada independientemente.

4. **Aplicación de Kernel de Convolución (OpenMP)**
   ```cpp
   #pragma omp parallel for collapse(2)
   for (int y = 1; y < alto - 1; ++y) {
       for (int x = 1; x < ancho - 1; ++x) {
           // ... procesamiento ...
       }
   }
   ```
   Se usa `collapse(2)` para paralelizar ambos bucles, ya que cada píxel puede ser procesado independientemente, excepto en los bordes.

La elección de estas directivas OpenMP se basa en la naturaleza de cada operación y la independencia de los datos procesados, buscando maximizar el paralelismo sin introducir condiciones de carrera.

## Notas Adicionales

- Todas las operaciones crean una nueva imagen, dejando la original sin modificar.
- Los tiempos de procesamiento se registran en un archivo "tiempos_procesamiento.txt".
- Las imágenes procesadas se guardan con un sufijo que indica la operación realizada.
- Se debe crear una caprpeta para las imagens resultado: ./img/resultado/
- Las versiones con OpenMP se guardan con el sufijo adicional "_omp".


## Licencia

[MIT License](https://opensource.org/licenses/MIT)
