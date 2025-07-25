// callables_2 17979.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#define LOG(x) std::cout << x << std::endl
#define API_ENDPOINT "http://monsterballgo.com/api/inventario"

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
           {"A101", "Mouse Inalambrico", "2024-10-01", 1599, 15},
           {"B202", "Teclado Mecanico", "2024-09-15", 5499, 10},
           {"C303", "Monitor 24", "2024-07-01", 28999, 5},
           {"D404", "Cable HDMI", "2025-01-20", 799, 50},
           {"E505", "Laptop i7", "2023-12-11", 99999, 3},
           { "F606", "Webcam Full HD",    "2024-11-05", 3499, 20 },
           {"G707", "Disco SSD 1TB",     "2025-03-12", 64999, 8},
           {"H808", "Auriculares Gamer", "2024-08-19", 4599, 12},
           {"I909", "Silla Ergonomica",  "2024-06-30", 89999, 4},
           {"J010", "Router WiFi 6",     "2024-09-01", 12999, 9}
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

void imprimirItems(const std::vector<Item>& items) {
    std::cout << std::left
        << std::setw(10) << "SKU"
        << std::setw(20) << "Nombre"
        << std::setw(12) << "Fecha"
        << std::setw(10) << "Precio"
        << std::setw(8) << "Stock"
        << "\n";

    for (const auto& item : items) {
        std::cout << std::left
            << std::setw(10) << item.SKU
            << std::setw(20) << item.nombre
            << std::setw(12) << item.fecha
            << std::setw(10) << std::fixed << std::setprecision(2) << (item.precioCentavos / 100.0)
            << std::setw(8) << item.stock
            << "\n";
    }
}
void exportarCSV(const std::vector<Item>& items, const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Error al abrir archivo para exportar.\n";
        return;
    }

    out << "SKU,Nombre,Fecha,Precio,Stock\n";
    for (const auto& item : items) {
        out << "\"" << item.SKU << "\","
            << "\"" << item.nombre << "\","
            << item.fecha << ","
            << std::fixed << std::setprecision(2) << item.precioCentavos / 100.0 << ","
            << item.stock << "\n";
    }

    std::cout << "Inventario exportado como " << filename << "\n";
}
size_t writefunction(void* ptr, size_t size, size_t nmemb, void* userdata)
{
    std::cout << "Recibiendo data..." << std::endl;
    size_t totalSize = size * nmemb;
    std::string* str = static_cast<std::string*>(userdata);
    str->append(static_cast<char*>(ptr), totalSize);
    return totalSize;
}
std::vector<Item> obtenerInventarioDesdeAPI()
{
    std::vector<Item> inventario;
    CURL* curl = curl_easy_init();
    CURLcode res;
    std::string response;

    if (!curl) {
        std::cerr << "Error al inicializar CURL\n";
        return inventario;
    }

    curl_easy_setopt(curl, CURLOPT_URL, API_ENDPOINT);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        std::cerr << "Error en la petición: " << curl_easy_strerror(res) << "\n";
        return inventario;
    }

    try {
        json j = json::parse(response);
        if (!j.contains("inventario")) {
            std::cerr << "JSON inválido.\n";
            return inventario;
        }

        for (const auto& obj : j["inventario"]) {
            Item item;
            item.SKU = obj.value("sku", "");
            item.nombre = obj.value("name", "");
            item.fecha = obj.value("date", "");
            item.precioCentavos = obj.value("price", 0);
            item.stock = obj.value("stock", 0);
            inventario.push_back(item);
        }

    }
    catch (const json::exception& e) {
        std::cerr << "Error al parsear JSON: " << e.what() << "\n";
    }

    return inventario;
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

    imprimirItems(baseDatos);
    
    
    bool (*comparador)(const Item&, const Item&) = nullptr;
    while (true) {
        // Mostrar menú de ordenamiento
        std::cout << "Selecciona el criterio de ordenamiento:\n";
        std::cout << "1. Nombre Ascendente\n";
        std::cout << "2. Nombre Descendente\n";
        std::cout << "3. Precio Ascendente\n";
        std::cout << "4. Precio Descendente\n";
        std::cout << "5. Stock Ascendente\n";
        std::cout << "6. Stock Descendente\n";
        std::cout << "7. Fecha Ascendente\n";
        std::cout << "8. Fecha Descendente\n";
        std::cout << "9. SKU Ascendente\n";
        std::cout << "10. SKU Descendente\n";
        std::cout << "Opcion: ";

        int opcion;
        std::cin >> opcion;

        if (opcion == 0) {
            std::cout << "Saliendo...\n";
            break;
        }

        switch (opcion) {
        case 1: comparador = ordenarPorNombreAsc; break;
        case 2: comparador = ordenarPorNombreDesc; break;
        case 3: comparador = ordenarPorPrecioAsc; break;
        case 4: comparador = ordenarPorPrecioDesc; break;
        case 5: comparador = ordenarPorStockAsc; break;
        case 6: comparador = ordenarPorStockDesc; break;
        case 7: comparador = ordenarPorFechaAsc; break;
        case 8: comparador = ordenarPorFechaDesc; break;
        case 9: comparador = ordenarPorSKUAsc; break;
        case 10: comparador = ordenarPorSKUDesc; break;
        default:
            std::cerr << "Opción no válida. Mostrando sin ordenar.\n";
            break;
        }

        // Ordenar si se definió criterio
        if (comparador) {
            std::sort(baseDatos.begin(), baseDatos.end(), comparador);
        }
        imprimirItems(baseDatos);
    }
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
    std::cout << "¿Deseas cargar inventario desde la API remota? (s/n): ";
    char respuesta;
    std::cin >> respuesta;
    if (respuesta == 's' || respuesta == 'S') {
        baseDatos = obtenerInventarioDesdeAPI();
    }
    
        std::cout << "¿Deseas exportar el inventario a CSV? (s/n): ";
        std::cin >> respuesta;
    if (respuesta == 's' || respuesta == 'S') {
        exportarCSV(baseDatos, "inventario.csv");
    }
   


    return 0;
}

