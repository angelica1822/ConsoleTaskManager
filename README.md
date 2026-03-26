# ConsoleTaskManager

![C++](https://img.shields.io/badge/C++-17%2B-blue)
![CMake](https://img.shields.io/badge/CMake-3.10%2B-brightgreen)

Aplicación de consola simple para administrar tareas con guardado automático de datos en archivo.

## Características

- 📝 Agregar tareas con nombre y descripción
- ✅ Marcar tareas como completadas
- 🗑️	Eliminar tareas
- 💾	Autoguardado en archivo tasks.txt
- 🖥️ Interfaz de consola con menú interactivo

##Instalación

1.Clona el repositorio:
```bash
git clone https://github.com/yourusername/task-manager.git
```

2. Compila el proyecto con CMake::
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

3. Ejecuta el programa:
```bash
./TaskManager
```

## Uso
Menú principal:
```
=== Gestor de tareas ===
1. Mostrar tareas
2. Agregar tarea
3. Marcar tarea como completada
4. Eliminar tarea
5. Salir

```
Ejemplo de uso:
4.	Selecciona “Agregar tarea”
5.	Ingresa el nombre y la descripción
6.	Consulta la lista de tareas
7.	Los cambios se guardan automáticamente


## Estructura del proyecto
```
.
├── CMakeLists.txt
├── src
│   └── main.cpp
├── tasks.txt (создается автоматически)
└── README.md
```

## Desarrollo

Requisitos
•	Compilador C++ con soporte para C++11 o superior
•	CMake 3.10+
Compilación para desarrollo

```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
```
