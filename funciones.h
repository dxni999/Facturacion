// Definir límites máximos
    #define MAX_CLIENTES 100
    #define MAX_PRODUCTOS 100
    #define MAX_FACTURAS 50
    #define MAX_ITEMS 10

    typedef struct{
        char nombre[20];
        int id;
        char direccion[50];
    }Cliente;

    typedef struct{
        char nombre[50];
        int stock;
        float precio;
        int activo;
    }Producto;

    typedef struct{
        int cantidad;
        Producto producto;
        float subtotal;
    }Item;

    typedef struct{
        Cliente cliente;
        int numProd;
        Item items[MAX_ITEMS];
        int id;
        float total;
    }Factura;

    // Funciones de entrada
    void leerCadena(char *cadena, int n);
    int leerEnteroConRango(int min, int max);
    float leerFlotanteConRango(float min, float max); 

    // Menú
    int menu();

    // Funciones de Cliente
    void registrarCliente();
    void listarClientes(Cliente *clientes);
    void guardarCliente(Cliente *cliente);
    int obtenerClientes(Cliente *clientes);

    // Funciones de Producto
    void registrarProducto();
    void listarProductos(Producto *productos);
    void guardarProducto(Producto *producto);
    int obtenerProductos(Producto *productos);
    void editarProducto(); 
    // Funciones de Factura
    void crearFactura(); 
void listarFacturas(Factura *facturas); 
void guardarFactura(Factura *factura); 
int obtenerFacturas(Factura *facturas); 