# Compilador
CXX = g++

# Flags de compilación
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -fopenmp

# Flags de enlazado
LDFLAGS = -fopenmp

# Librerías
LIBS = -ljpeg

# Nombre del ejecutable
TARGET = procesador_imagen

# Archivos fuente y objeto
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Archivos de cabecera
HEADERS = $(wildcard *.h)

# Regla por defecto
all: $(TARGET)

# Regla para compilar el ejecutable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS) $(LDFLAGS)

# Regla para compilar archivos objeto
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para limpiar archivos generados
clean:
	rm -f $(OBJECTS) $(TARGET)

# Regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Regla para recompilar todo
rebuild: clean all

# Regla para comprobar la versión de OpenMP
check-openmp:
	@echo "Checking OpenMP version..."
	@$(CXX) -fopenmp -dM -E - < /dev/null | grep -i openmp

# Phony targets
.PHONY: all clean run rebuild check-openmp