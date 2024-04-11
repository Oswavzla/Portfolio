import json
import os  # Importar el módulo os

# Estructuras de datos iniciales
inventario = {}
proveedores = {}


# Función para guardar el inventario en un archivo
def guardar_inventario():
    with open('inventario.json', 'w') as archivo:
        json.dump(inventario, archivo)
    print("Datos del inventario guardados correctamente en el archivo.")

# Función para cargar el inventario desde un archivo
def cargar_inventario():
    try:
        with open('inventario.json', 'r') as archivo:
            inventario_actualizado = json.load(archivo)
            inventario.clear()
            inventario.update(inventario_actualizado)
        print("Datos del inventario cargados correctamente desde el archivo.")
    except FileNotFoundError:
        print("El archivo de inventario no existe. Se creará uno nuevo para guardar los datos.")

# Función para guardar los proveedores en un archivo
def guardar_proveedores():
    with open('proveedores.json', 'w') as archivo:
        json.dump(proveedores, archivo)
    print("Datos de los proveedores guardados correctamente en el archivo.")

# Función para cargar los proveedores desde un archivo
def cargar_proveedores():
    try:
        with open('proveedores.json', 'r') as archivo:
            proveedores_actualizados = json.load(archivo)
            proveedores.clear()
            proveedores.update(proveedores_actualizados)
        print("Datos de los proveedores cargados correctamente desde el archivo.")
    except FileNotFoundError:
        print("El archivo de proveedores no existe. Se creará uno nuevo para guardar los datos.")

# Funciones del menú
def mostrar_menu_principal():
    os.system('cls')  # Limpiar pantalla en sistemas Windows
    print("\nMenú Principal:")
    print("1- Modificar inventario")
    print("2- Visualizar inventario")
    print("3- Cerrar la sesión")

def mostrar_menu_modificar_inventario():
        os.system('cls')  # Limpiar pantalla en sistemas Windows
        print("\nMenú Modificar Inventario:")
        print("1. Crear Artículo")
        print("2. Crear Proveedor")
        print("3. Ingresar Compra")
        print("4. Salida de Inventario")
        print("5. Modificar Artículo")
        print("6. Modificar Proveedor")  
        print("7. Volver al Menú Principal")

# Funciones de modificación de inventario
def crear_articulo():
    while True:
        codigo = input("Ingrese el código del artículo: ").strip()
        if codigo in inventario:
            print("Error: Ya existe un artículo con ese código.")
        else:
            nombre = input("Ingrese el nombre del artículo: ").strip()
            inventario[codigo] = {'nombre': nombre, 'cantidad': 0, 'costo': 0}
            print(f"Artículo '{nombre}' creado con éxito.")

        continuar = input("¿Desea agregar otro artículo (s/n)? ")
        if continuar.lower() != 's':
            break

def modificar_articulo():
    mostrar_tabla_codigos_articulos()
    codigo = input("Ingrese el código del artículo a modificar: ").strip()
    if codigo not in inventario:
        print("Error: El artículo no existe.")
        return
    nuevo_nombre = input("Ingrese el nuevo nombre para el artículo: ").strip()
    inventario[codigo]['nombre'] = nuevo_nombre
    print(f"Nombre del artículo modificado correctamente a '{nuevo_nombre}'.")

# Funciones de modificación de proveedores

def crear_proveedor():
    while True:
        rif = input("Ingrese el RIF del proveedor: ").strip()
        if rif in proveedores:
            print("Error: Ya existe un proveedor con ese RIF.")
        else:
            nombre = input("Ingrese el nombre del proveedor: ").strip()
            contacto = input("Ingrese el número de contacto del proveedor: ").strip()
            proveedores[rif] = {'nombre': nombre, 'contacto': contacto}
            print(f"Proveedor '{nombre}' creado con éxito.")
        
        continuar = input("¿Desea agregar otro proveedor (s/n)? ")
        if continuar.lower() != 's':
            break

def modificar_proveedor():
    mostrar_tabla_codigos_proveedores()
    rif = input("Ingrese el RIF del proveedor a modificar: ").strip()
    if rif not in proveedores:
        print("Error: El proveedor no existe.")
        return
    nuevo_nombre = input("Ingrese el nuevo nombre del proveedor: ").strip()
    nuevo_contacto = input("Ingrese el nuevo contacto del proveedor: ").strip()
    proveedores[rif]['nombre'] = nuevo_nombre
    proveedores[rif]['contacto'] = nuevo_contacto
    print(f"Información del proveedor modificada correctamente: Nombre - {nuevo_nombre}, Contacto - {nuevo_contacto}.")

#Mostras tablas de informacion
    
def mostrar_tabla_codigos_articulos():
    print("Tabla de Códigos de Artículos:")
    print("------------------------------")
    print("| Código |    Nombre   | Cantidad |")
    print("------------------------------")
    for codigo, info in inventario.items():
        print(f"| {codigo} | {info['nombre']} | {info['cantidad']} |")
    print("------------------------------")

def mostrar_tabla_codigos_proveedores():
    print("Tabla de Códigos de Proveedores:")
    print("------------------------------")
    print("|   RIF   |    Nombre    | Contacto |")
    print("------------------------------")
    for rif, info in proveedores.items():
        print(f"| {rif} | {info['nombre']} | {info['contacto']} |")
    print("------------------------------")

#Ingreso de compra
    
def ingresar_compra():
    mostrar_tabla_codigos_proveedores()
    rif = input("Ingrese el RIF del proveedor: ").strip()
    if rif not in proveedores:
        print("Error: Proveedor no existe. Debe crearlo primero.")
        crear_proveedor()
        return
  
    while True:
        mostrar_tabla_codigos_articulos()
        codigo = input("Ingrese el código del artículo: ").strip()
        if codigo not in inventario:
            print("Error: Artículo no existe. Debe crearlo primero.")
            crear_articulo()
            continue
        
        cantidad = int(input("Ingrese la cantidad de ingreso: ").strip())
        costo = float(input("Ingrese el costo por unidad: ").strip())
        inventario[codigo]['cantidad'] += cantidad
        inventario[codigo]['costo'] = costo
        print(f"Compra ingresada correctamente. {cantidad} unidades del artículo {inventario[codigo]['nombre']}.")

        continuar = input("¿Desea agregar otro artículo a la compra (s/n)? ")
        if continuar.lower() != 's':
            break

#Salida de inventario 
        
def salida_inventario():
    while True:
        mostrar_tabla_codigos_articulos()
        codigo = input("Ingrese el código del artículo para salida: ").strip()
        if codigo not in inventario:
            print("Error: El artículo no existe.")
            continue
        cantidad = int(input(f"Ingrese la cantidad de salida para {inventario[codigo]['nombre']}: ").strip())
        if cantidad > inventario[codigo]['cantidad']:
            print("Error: Cantidad de salida mayor a la existencia.")
            continue
        inventario[codigo]['cantidad'] -= cantidad
        print(f"Salida de {cantidad} unidades del artículo '{inventario[codigo]['nombre']}' registrada correctamente. Quedan {inventario[codigo]['cantidad']} unidades.")

        continuar = input("¿Desea hacer la salida de otro artículo (s/n)? ")
        if continuar.lower() != 's':
            break

#Visualizar Inventario 
        
def visualizar_inventario():
    print("\nInventario Actual:")
    for codigo, info in inventario.items():
        print(f"Código: {codigo}, Nombre: {info['nombre']}, Cantidad: {info['cantidad']}, Costo: {info['costo']}")
    
    input("\nPresione Enter para regresar al menú principal...")
    


#Ejecucion de Menu de Modificar Inventario
        
def ejecutar_menu_modificar_inventario():
    while True:
        mostrar_menu_modificar_inventario()
        guardar_inventario()  # Guardar el inventario después de realizar modificaciones
        guardar_proveedores()  # Guardar los proveedores después de realizar modificaciones
        opcion = input("Seleccione una opción: ")
        if opcion == "1":
            os.system('cls')  # Limpiar pantalla en sistemas Windows
            crear_articulo()

        elif opcion == "2":
            os.system('cls')  # Limpiar pantalla en sistemas Windows
            crear_proveedor()
        elif opcion == "3":
            os.system('cls')  # Limpiar pantalla en sistemas Windows
            ingresar_compra()

        elif opcion == "4":
            os.system('cls')  # Limpiar pantalla en sistemas Windows
            salida_inventario()

        elif opcion == "5":
            os.system('cls')  # Limpiar pantalla en sistemas Windows
            modificar_articulo()

        elif opcion == "6":
            os.system('cls')  # Limpiar pantalla en sistemas Windows
            modificar_proveedor()

        elif opcion == "7":   
            os.system('cls')  # Limpiar pantalla en sistemas Windows 
            break

        else:
            os.system('cls')  # Limpiar pantalla en sistemas Windows
            print("Opción inválida. Por favor, seleccione una opción válida.")


# Función para ejecutar el menú principal
def ejecutar_menu_principal():
    cargar_inventario()  # Cargar el inventario al iniciar el programa
    cargar_proveedores() # Cargar los proveedores al iniciar el programa
    while True:
        mostrar_menu_principal()
        opcion = input("Seleccione una opción: ").strip()
        if opcion == "1":
            ejecutar_menu_modificar_inventario()
            guardar_inventario()  # Guardar el inventario después de realizar modificaciones
            guardar_proveedores()  # Guardar los proveedores después de realizar modificaciones
        elif opcion == "2":
            visualizar_inventario()
        elif opcion == "3":
            guardar_inventario()  # Guardar el inventario al cerrar la sesión
            guardar_proveedores()  # Guardar los proveedores al cerrar la sesión
            print("Cerrando sesión...")
            break
        else:
            print("Opción no válida. Intente nuevamente.")

# Ejecutar el programa
ejecutar_menu_principal()

if __name__ == "__main__":
    ejecutar_aplicacion()
