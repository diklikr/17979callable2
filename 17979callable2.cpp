// callables_2 17979.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#define LOG(x) std::cout << x << std::endl

// Estructura que representa un ítem
struct Item {
    std::string SKU;
    std::string nombre;
    std::string fecha; // formato: "YYYY-MM-DD"
    int precioCentavos;
    int stock;
};

// Funciones de comparación ascendente
bool ordenarPorNombreAsc(const Item& a, const Item& b) { return a.nombre < b.nombre; }
bool ordenarPorPrecioAsc(const Item& a, const Item& b) { return a.precioCentavos < b.precioCentavos; }
bool ordenarPorStockAsc(const Item& a, const Item& b) { return a.stock < b.stock; }
bool ordenarPorFechaAsc(const Item& a, const Item& b) { return a.fecha < b.fecha; }
bool ordenarPorSKUAsc(const Item& a, const Item& b) { return a.SKU < b.SKU; }

// Funciones de comparación descendente
bool ordenarPorNombreDesc(const Item& a, const Item& b) { return a.nombre > b.nombre; }
bool ordenarPorPrecioDesc(const Item& a, const Item& b) { return a.precioCentavos > b.precioCentavos; }
bool ordenarPorStockDesc(const Item& a, const Item& b) { return a.stock > b.stock; }
bool ordenarPorFechaDesc(const Item& a, const Item& b) { return a.fecha > b.fecha; }
bool ordenarPorSKUDesc(const Item& a, const Item& b) { return a.SKU > b.SKU; }

std::vector<Item> baseDatos = {
           {"A101", "Mouse Inalámbrico", "2024-10-01", 1599, 15},
           {"B202", "Teclado Mecánico", "2024-09-15", 5499, 10},
           {"C303", "Monitor 24\"", "2024-07-01", 28999, 5},
           {"D404", "Cable HDMI", "2025-01-20", 799, 50},
           {"E505", "Laptop i7", "2023-12-11", 99999, 3}
};

int sumar(int a, int b)
{
    return a + b;
}
int restaAB(int a, int b)
{
    return a - b;
}
int restaBA(int a, int b)
{
    return b - a;
}
int filtroRandom(char* data)
{
    for (size_t i = 0; data[i] != '\0'; i++)
    {
        data[i] = data[i] + 1;
    }
    LOG("dato nuevo: " << data);

    //prueba de filtro
   /* char data[] = "Hola Mundo";
    filtroRandom(data);*/

    return 0;
}
int filtroMayus(char* data)
{
    for (size_t i = 0; data[i] != '\0'; i++)
    {
        if (data[i] >= 'a' && data[i] <= 'z')
        {
            data[i] = data[i] - ('a' - 'A');
        }
    }
    LOG("dato nuevo: " << data);
    return 0;
}
int filtroMinus(char* data)
{
    for (size_t i = 0; data[i] != '\0'; i++)
    {
        if (data[i] >= 'A' && data[i] <= 'Z')
        {
            data[i] = data[i] + 32;
        }
    }
    LOG("dato nuevo: " << data);
    return 0;
}

struct vector2d
{
    float x, y;
    vector2d(float x, float y) : x(x), y(y) {}
};
//funcion de ordenamiento
bool ordenarPorMagnitud(const vector2d& a, const vector2d& b)
{
    return a.x + a.y < b.x + b.y;
}



int main(int argc, char** argv)
{
    int a = 5, b = 3;
    LOG("Valores iniciales: " << a << "," << b);

    int(*operacion)(int, int) = sumar;

    LOG("El resultado es: " << operacion(a, b));
    operacion = restaAB;
    LOG("El resultado es: " << operacion(a, b));


    struct Printer
    {
        void operator()(const char* message)
        {
            std::cout << "Printer::print : [date]" << message << std::endl;
        }
    };

    Printer printer;
    Printer printer2;

    printer("functor 1");
    printer2("functor 2");

    struct Counter
    {
        int count = 0;
        int operator()()
        {
            count++;
            return count;
        }
    };

    Counter counter1;
    Counter counter2;
    counter1(); counter2();
    counter1(); counter2();
    counter1();

    LOG("Counter1: " << counter1.count);
    LOG("Counter2: " << counter2.count);

    //imprimir items
    std::vector<Item> baseDatos = {
        {"A101", "Mouse Inalámbrico", "2024-10-01", 1599, 15},
        {"B202", "Teclado Mecánico", "2024-09-15", 5499, 10},
        {"C303", "Monitor 24\"", "2024-07-01", 28999, 5},
        {"D404", "Cable HDMI", "2025-01-20", 799, 50},
        {"E505", "Laptop i7", "2023-12-11", 99999, 3}
    };

    // Comparador por defecto (ninguno)
    bool (*comparador)(const Item&, const Item&) = nullptr;

    // Analizar argumentos
    if (argc > 1) {
        std::string orden = argv[1]; // Ejemplo: orden=nombre, orden=precio-desc

        // Mapear argumentos a funciones
        if (orden == "orden=nombre") comparador = ordenarPorNombreAsc;
        else if (orden == "orden=precio") comparador = ordenarPorPrecioAsc;
        else if (orden == "orden=stock") comparador = ordenarPorStockAsc;
        else if (orden == "orden=fecha") comparador = ordenarPorFechaAsc;
        else if (orden == "orden=sku") comparador = ordenarPorSKUAsc;

        else if (orden == "orden=nombre-desc") comparador = ordenarPorNombreDesc;
        else if (orden == "orden=precio-desc") comparador = ordenarPorPrecioDesc;
        else if (orden == "orden=stock-desc") comparador = ordenarPorStockDesc;
        else if (orden == "orden=fecha-desc") comparador = ordenarPorFechaDesc;
        else if (orden == "orden=sku-desc") comparador = ordenarPorSKUDesc;
        else {
            std::cerr << "Criterio desconocido. Usa uno de: \n"
                << "  orden=nombre[(-desc)]\n"
                << "  orden=precio[(-desc)]\n"
                << "  orden=stock[(-desc)]\n"
                << "  orden=fecha[(-desc)]\n"
                << "  orden=sku[(-desc)]\n";
            return 1;
        }

        // Ordenar si se definió criterio
        if (comparador) {
            std::sort(baseDatos.begin(), baseDatos.end(), comparador);
        }
    }

    // Imprimir la tabla
    



    vector2d v(3, 4);
    auto sumaVectorial = [v](vector2d)
        {
            return vector2d(v.x + v.x, v.y + v.y);
        };
    LOG("Vector1: " << v.x << ", " << v.y);
    vector2d u = sumaVectorial(vector2d(1, 2));
    LOG("Vector2: " << u.x << ", " << u.y);

    std::vector<vector2d> vectores2d;
    vectores2d.push_back(v);
    vectores2d.push_back(u);
    vectores2d.push_back(vector2d(-1, -1));
    vectores2d.push_back(vector2d(-3, -4));
    vectores2d.push_back(vector2d(2, 3));

    std::sort(vectores2d.begin(), vectores2d.end(), [](const vector2d& a, const vector2d& b)
        {
            float magA = sqrt(a.x * a.x + a.y * a.y);
            float magB = sqrt(b.x * b.x + b.y * b.y);
            return magA < magB;
        });
    for (const auto& vec : vectores2d)
    {
        LOG("Vector ordenando: " << vec.x << ", " << vec.y);
    }
    std::sort(vectores2d.begin(), vectores2d.end(), ordenarPorMagnitud);
    for (const auto& vec : vectores2d)
    {
        LOG("Vector ordenando naive: " << vec.x << ", " << vec.y);
    }

    ////part2


    if (argc <= 1)
    {
        LOG("No se proporcionaron params. Aqui termina el ejemplo");
    }
    else
    {
        int(*filterToApply)(char* data) = filtroRandom;
        for (size_t i = 0; i < argc; i++)
        {
            LOG("Parametro " << i << ": " << argv[i]);

            if (strcmp(argv[i], "f=mayus") == 0)
            {
                filterToApply = filtroMayus;
            }
            else if (strcmp(argv[i], "f=minus") == 0)
            {
                filterToApply = filtroMinus;
            }
        }
        filterToApply(argv[1]);
    }
    imprimirItems(baseDatos);

    return 0;
}

