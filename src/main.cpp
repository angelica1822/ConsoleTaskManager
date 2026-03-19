#define NOMINMAX
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <windows.h>

using namespace std;

struct Task {
    string title;
    string description;
    bool completed;
};

void printTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "La lista de tareas está vacía.\n";
        return;
    }

    cout << "\nLista de tareas:\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". "
             << "[" << (tasks[i].completed ? "X" : " ") << "] "
             << tasks[i].title << "\n   "
             << tasks[i].description << "\n\n";
    }
}

vector<Task> loadTasksFromFile(const string& filename) {
    vector<Task> tasks;
    ifstream file(filename, ios::binary);

    if (file.is_open()) {
        if (file.get() != 0xEF || file.get() != 0xBB || file.get() != 0xBF) {
            file.seekg(0);
        }

        Task task;
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            
            task.title = line;
            
            if (!getline(file, line)) break;
            task.description = line;
            
            if (!getline(file, line)) break;
            task.completed = (line == "1");
            
            tasks.push_back(task);
            
            getline(file, line);
        }
        file.close();
    }
    return tasks;
}

void saveTasksToFile(const vector<Task>& tasks, const string& filename) {
    ofstream file(filename, ios::binary | ios::trunc);
    if (file.is_open()) {
        file << "\xEF\xBB\xBF";
        
        for (const auto& task : tasks) {
            file << task.title << "\n"
                 << task.description << "\n"
                 << (task.completed ? "1" : "0") << "\n\n";
        }
        file.close();
    }
    else {
        cerr << "Error al guardar las tareas!\n";
    }
}

void addTask(vector<Task>& tasks) {
    Task newTask;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Ingrese el nombre de la tarea: ";
    if (!getline(cin, newTask.title) || newTask.title.empty()) {
        cout << "Error: el nombre no puede estar vacío!\n";
        return;
    }

    cout << "Ingrese la descripción de la tarea: ";
    if (!getline(cin, newTask.description)) {
        cout << "Error al ingresar la descripción!\n";
        return;
    }

    newTask.completed = false;
    tasks.push_back(newTask);
    cout << "Tarea agregada correctamente!\n";
}

void markTaskCompleted(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "La lista de tareas está vacía.\n";
        return;
    }

    printTasks(tasks);
    cout << "Ingrese el número de la tarea a completar: ";
    size_t index;
    if (!(cin >> index)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: ingrese un número válido!\n";
        return;
    }

    if (index > 0 && index <= tasks.size()) {
        tasks[index - 1].completed = true;
        cout << "Tarea marcada como completada!\n";
    }
    else {
        cout << "Número de tarea inválido!\n";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void deleteTask(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "La lista de tareas está vacía.\n";
        return;
    }

    printTasks(tasks);
    cout << "Ingrese el número de la tarea a eliminar: ";
    size_t index;
    if (!(cin >> index)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: ingrese un número válido!\n";
        return;
    }

    if (index > 0 && index <= tasks.size()) {
        tasks.erase(tasks.begin() + index - 1);
        cout << "Tarea eliminada correctamente!\n";
    }
    else {
        cout << "Número de tarea inválido!\n";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    system("chcp 65001 > nul");

    const string filename = "tasks.txt";
    vector<Task> tasks = loadTasksFromFile(filename);
    int choice;

    do {
        cout << "\n=== GESTOR DE TAREAS ===\n"
             << "1. Mostrar tareas\n"
             << "2. Agregar tarea\n"
             << "3. Marcar tarea como completada\n"
             << "4. Eliminar tarea\n"
             << "5. Salir\n"
             << "Seleccione una opción: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error de entrada! Intente nuevamente.\n";
            continue;
        }

        switch (choice) {
            case 1:
                printTasks(tasks);
                break;
            case 2:
                addTask(tasks);
                saveTasksToFile(tasks, filename);
                break;
            case 3:
                markTaskCompleted(tasks);
                saveTasksToFile(tasks, filename);
                break;
            case 4:
                deleteTask(tasks);
                saveTasksToFile(tasks, filename);
                break;
            case 5:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción inválida! Intente nuevamente.\n";
        }
    } while (choice != 5);

    return 0;
}