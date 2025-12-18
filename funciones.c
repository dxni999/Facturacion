#include <stdio.h>
#include <string.h>
#include "funciones.h"

void leerCadena(char *cadena, int n){
    fgets(cadena,n,stdin);
    int len = strlen(cadena) - 1;
    if(len >= 0 && cadena[len] == '\n') // ✅ MEJORADO: validación
        cadena[len]='\0';
}
//funcion para leer enteros con rango
int leerEnteroConRango(int min, int max){
    int num;
    int val;
    do{
        val = scanf("%d",&num);
        if (val != 1 || num < min || num > max)
        {
            printf("El dato ingresado no es valido\n");
            while(getchar() != '\n');
        }
    }while(val != 1 || num < min || num > max);
    while(getchar() != '\n');
    return num;
}

float leerFlotanteConRango(float min, float max){ // ✅ CORREGIDO: era "int"
    float num;
    int val;
    do{
        val = scanf("%f",&num);
        if (val != 1 || num < min || num > max)
        {
            printf("El dato ingresado no es valido\n");
            while(getchar() != '\n');
        }
    }while(val != 1 || num < min || num > max);
    while(getchar() != '\n');
    return num;
}

int menu(){
    printf("\n=== SISTEMA DE FACTURACION ===\n");
    printf("Seleccione una opcion:\n");
    printf("1. Registrar Cliente\n");
    printf("2. Mostrar Clientes\n");
    printf("3. Registrar Producto\n");
    printf("4. Mostrar Productos\n");
    printf("5. Editar Producto\n");
    printf("6. Crear Factura\n");
    printf("7. Mostrar Facturas\n");
    printf("8. Salir\n");
    printf(">> ");
    int opc = leerEnteroConRango(1,8);
    return opc;
}

// ============ FUNCIONES DE CLIENTE ============

void registrarCliente(){
    Cliente cliente;
    Cliente clientes[MAX_CLIENTES];
    int count = obtenerClientes(clientes);
    
    printf("Ingrese el ID del cliente (1-999): ");
    int idBuscado = leerEnteroConRango(1,999);
    
    // ✅ AGREGADO: Validar que el ID no exista
    for(int i = 0; i < count; i++){
        if(clientes[i].id == idBuscado){
            printf("ERROR: Ya existe un cliente con ese ID\n");
            return;
        }
    }
    
    cliente.id = idBuscado;
    printf("Ingrese el nombre del cliente: ");
    leerCadena(cliente.nombre,20);
    printf("Ingrese la direccion del cliente: ");
    leerCadena(cliente.direccion,50);
    guardarCliente(&cliente);
    printf("Cliente registrado exitosamente\n"); // ✅ AGREGADO: Feedback
}

void listarClientes(Cliente *clientes){
    int c = obtenerClientes(clientes);
    if(c == 0){ // ✅ AGREGADO: Validación
        printf("No hay clientes registrados\n");
        return;
    }
    printf("\n--- LISTA DE CLIENTES ---\n");
    printf("%-5s %-5s %-20s %-30s\n", "#", "ID", "Nombre", "Direccion");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < c; i++)
    {
        printf("%-5d %-5d %-20s %-30s\n",i,
                                    clientes[i].id,
                                    clientes[i].nombre,
                                    clientes[i].direccion);
    }
}

void guardarCliente(Cliente *cliente){
    Cliente clientes[MAX_CLIENTES];
    int count = obtenerClientes(clientes);
    
    // Agregar el nuevo cliente al arreglo
    clientes[count] = *cliente;
    count++;
    
    // Sobreescribir el archivo completo
    FILE *f;
    f = fopen("clientes.dat","wb");
    if (f==NULL)
    {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    fwrite(clientes,sizeof(Cliente),count,f);
    fclose(f);
}

int obtenerClientes(Cliente *clientes){
    FILE *f;
    f = fopen("clientes.dat","rb");
    if (f==NULL)
    {
        return 0; // ✅ MEJORADO: No mostrar error si no existe
    }
    int count = fread(clientes,sizeof(Cliente),MAX_CLIENTES,f); // ✅ CORREGIDO: era 5
    fclose(f);
    return count;
}

// ============ FUNCIONES DE PRODUCTO ============

void registrarProducto(){
    Producto producto;
    printf("Ingrese el nombre del producto: ");
    leerCadena(producto.nombre,50);
    printf("Ingrese el stock del producto: ");
    producto.stock=leerEnteroConRango(0,10000); // ✅ MEJORADO: aumentado rango
    printf("Ingrese el precio del producto: ");
    producto.precio = leerFlotanteConRango(0.01,100000); // ✅ MEJORADO: rango realista
    producto.activo=1;
    guardarProducto(&producto); // ✅ AGREGADO: ¡Faltaba guardar!
    printf("Producto registrado exitosamente\n"); // ✅ AGREGADO: Feedback
}

void listarProductos(Producto *productos){
    int c = obtenerProductos(productos);
    if(c == 0){ // ✅ AGREGADO: Validación
        printf("No hay productos registrados\n");
        return;
    }
    printf("\n--- LISTA DE PRODUCTOS ---\n");
    printf("%-5s %-30s %-10s %-10s %-10s\n", "#", "Nombre", "Stock", "Precio", "Estado");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < c; i++)
    {
        printf("%-5d %-30s %-10d $%-9.2f %-10s\n",i,
                                        productos[i].nombre,
                                        productos[i].stock,
                                        productos[i].precio,
                                        productos[i].activo ? "Activo" : "Inactivo"); // ✅ MEJORADO
    }
}

void guardarProducto(Producto *producto){
    FILE *f;
    f = fopen("productos.dat","ab");
    if (f==NULL)
    {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    fwrite(producto,sizeof(Producto),1,f);
    fclose(f);
}

int obtenerProductos(Producto *productos){
    FILE *f;
    f = fopen("productos.dat","rb");
    if (f==NULL)
    {
        return 0; // ✅ MEJORADO: No mostrar error si no existe
    }
    int count = fread(productos,sizeof(Producto),MAX_PRODUCTOS,f); // ✅ CORREGIDO: era 5
    fclose(f);
    return count;
}

// ✅ AGREGADO: Función completa nueva
void editarProducto(){
    Producto productos[MAX_PRODUCTOS];
    int count = obtenerProductos(productos);
    
    if(count == 0){
        printf("No hay productos registrados para editar\n");
        return;
    }
    
    listarProductos(productos);
    printf("\nSeleccione el numero de producto a editar (0-%d): ", count-1);
    int indice = leerEnteroConRango(0, count-1);
    
    printf("\n--- Editando: %s ---\n", productos[indice].nombre);
    printf("Nuevo stock (actual: %d): ", productos[indice].stock);
    productos[indice].stock = leerEnteroConRango(0, 10000);
    
    printf("Nuevo precio (actual: %.2f): ", productos[indice].precio);
    productos[indice].precio = leerFlotanteConRango(0.01, 100000);
    
    printf("Estado - 1=Activo / 0=Inactivo (actual: %s): ", 
           productos[indice].activo ? "Activo" : "Inactivo");
    productos[indice].activo = leerEnteroConRango(0, 1);
    
    // Reescribir todo el archivo con los cambios
    FILE *f = fopen("productos.dat", "wb");
    if(f != NULL){
        fwrite(productos, sizeof(Producto), count, f);
        fclose(f);
        printf("Producto actualizado exitosamente\n");
    } else {
        printf("Error al guardar los cambios\n");
    }
}

// ============ FUNCIONES DE FACTURA ============

// ✅ AGREGADO: Función completa nueva
void crearFactura(){
    Factura factura;
    Cliente clientes[MAX_CLIENTES];
    Producto productos[MAX_PRODUCTOS];
    
    int numClientes = obtenerClientes(clientes);
    int numProductos = obtenerProductos(productos);
    
    if(numClientes == 0){
        printf("No hay clientes registrados. Registre clientes primero\n");
        return;
    }
    
    if(numProductos == 0){
        printf("No hay productos registrados. Registre productos primero\n");
        return;
    }
    
    // Asignar ID de factura
    Factura facturas[MAX_FACTURAS];
    int numFacturas = obtenerFacturas(facturas);
    factura.id = numFacturas + 1;
    
    // Seleccionar cliente
    printf("\n--- CREAR NUEVA FACTURA ---\n");
    listarClientes(clientes);
    printf("\nSeleccione el numero de cliente (0-%d): ", numClientes-1);
    int idxCliente = leerEnteroConRango(0, numClientes-1);
    factura.cliente = clientes[idxCliente];
    
    // Agregar productos a la factura
    factura.numProd = 0;
    factura.total = 0;
    int continuar = 1;
    
    while(continuar == 1 && factura.numProd < MAX_ITEMS){
        printf("\n--- Productos Disponibles ---\n");
        listarProductos(productos);
        
        printf("\nSeleccione producto (0-%d): ", numProductos-1);
        int idxProd = leerEnteroConRango(0, numProductos-1);
        
        if(productos[idxProd].activo == 0){
            printf("ERROR: Este producto esta inactivo\n");
            continue;
        }
        
        printf("Cantidad (disponible: %d): ", productos[idxProd].stock);
        int cantidad = leerEnteroConRango(1, productos[idxProd].stock);
        
        // Agregar item a la factura
        factura.items[factura.numProd].producto = productos[idxProd];
        factura.items[factura.numProd].cantidad = cantidad;
        factura.items[factura.numProd].subtotal = cantidad * productos[idxProd].precio;
        factura.total += factura.items[factura.numProd].subtotal;
        factura.numProd++;
        
        // Actualizar stock del producto
        productos[idxProd].stock -= cantidad;
        
        if(factura.numProd < MAX_ITEMS){
            printf("\nAgregar otro producto? (1=Si / 2=No): ");
            continuar = leerEnteroConRango(1, 2);
        } else {
            printf("Limite de productos alcanzado\n");
            continuar = 2;
        }
    }
    
    // Actualizar archivo de productos con nuevo stock
    FILE *f = fopen("productos.dat", "wb");
    if(f != NULL){
        fwrite(productos, sizeof(Producto), numProductos, f);
        fclose(f);
    }
    
    // Guardar factura
    guardarFactura(&factura);
    
    // Mostrar resumen
    printf("\n=== FACTURA #%d ===\n", factura.id);
    printf("Cliente: %s\n", factura.cliente.nombre);
    printf("Direccion: %s\n\n", factura.cliente.direccion);
    printf("%-30s %-10s %-10s %-10s\n", "Producto", "Cantidad", "Precio", "Subtotal");
    printf("-----------------------------------------------------------------------\n");
    for(int i = 0; i < factura.numProd; i++){
        printf("%-30s %-10d $%-9.2f $%-9.2f\n", 
               factura.items[i].producto.nombre,
               factura.items[i].cantidad,
               factura.items[i].producto.precio,
               factura.items[i].subtotal);
    }
    printf("-----------------------------------------------------------------------\n");
    printf("TOTAL: $%.2f\n", factura.total);
    printf("\nFactura creada exitosamente\n");
}

// ✅ AGREGADO: Función completa nueva
void listarFacturas(Factura *facturas){
    int c = obtenerFacturas(facturas);
    if(c == 0){
        printf("No hay facturas registradas\n");
        return;
    }
    
    printf("\n--- LISTA DE FACTURAS ---\n");
    for(int i = 0; i < c; i++){
        printf("\n========================================\n");
        printf("FACTURA #%d\n", facturas[i].id);
        printf("Cliente: %s (ID: %d)\n", facturas[i].cliente.nombre, facturas[i].cliente.id);
        printf("Direccion: %s\n", facturas[i].cliente.direccion);
        printf("Productos: %d\n", facturas[i].numProd);
        printf("TOTAL: $%.2f\n", facturas[i].total);
        printf("----------------------------------------\n");
        printf("%-25s %-8s %-10s\n", "Producto", "Cant.", "Subtotal");
        for(int j = 0; j < facturas[i].numProd; j++){
            printf("%-25s %-8d $%-9.2f\n",
                   facturas[i].items[j].producto.nombre,
                   facturas[i].items[j].cantidad,
                   facturas[i].items[j].subtotal);
        }
    }
    printf("\n========================================\n");
}

// ✅ AGREGADO: Función completa nueva
void guardarFactura(Factura *factura){
    FILE *f;
    f = fopen("facturas.dat","ab");
    if (f==NULL)
    {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    fwrite(factura,sizeof(Factura),1,f);
    fclose(f);
}

// ✅ AGREGADO: Función completa nueva
int obtenerFacturas(Factura *facturas){
    FILE *f;
    f = fopen("facturas.dat","rb");
    if (f==NULL)
    {
        return 0;
    }
    int count = fread(facturas,sizeof(Factura),MAX_FACTURAS,f);
    fclose(f);
    return count;
}