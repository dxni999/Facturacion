#include <stdio.h>
#include "funciones.h"

int main (int argc, char *argv[]) {

    int opc1, opc2;
    
    // Eliminar archivo de clientes al iniciar el programa
    remove("clientes.dat");

    do{
        opc1 = menu();

        switch (opc1)
        {
        case 1:
            registrarCliente();
            break;
        case 2:{
            Cliente clientes[MAX_CLIENTES]; 
            listarClientes(clientes);
            break;
        }
        case 3:
            registrarProducto();
            break;
        case 4:{
            Producto productos[MAX_PRODUCTOS];  
            listarProductos(productos);
            break;
        }
        case 5: 
            editarProducto();
            break;
        case 6: 
            crearFactura();
            break;
        case 7:{ 
            Factura facturas[MAX_FACTURAS];
            listarFacturas(facturas);
            break;
        }
        case 8: 
            printf("\nGracias por usar el sistema. Hasta pronto!\n");
            remove("clientes.dat");
            return 0;
        default:
            printf("Opcion no valida\n"); 
            break;
        }
        
        printf("\nDesea seleccionar otra opcion? (1.-Si / 2.-No): ");
        opc2 = leerEnteroConRango(1,2);
        
    }while(opc2 == 1);
    
    printf("\nGracias por usar el sistema. Hasta pronto!\n"); 
    remove("clientes.dat");

    return 0;
}
