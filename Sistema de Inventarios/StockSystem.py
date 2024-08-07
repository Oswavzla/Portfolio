import json
import os
import msvcrt

class Inventario:
    def __init__(self):
        self.datos = {}

    def guardar(self):
        with open('inventario.json', 'w') as archivo:
            json.dump(self.datos, archivo)
        print("Datos del inventario guardados correctamente en el archivo.")

    def cargar(self):
        try:
            with open('inventario.json', 'r') as archivo:
                self.datos = json.load(archivo)
            print("Datos del inventario cargados correctamente desde el archivo.")
        except FileNotFoundError:
            print("El archivo de inventario no existe. Se creará uno nuevo para guardar los datos.")


    def mostrar_articulos(self, inventario):
        print("Tabla de Artículos en Inventario:")
        print("----------------------------------------------")
        print("|   Código   |        Nombre       | Cantidad |    Costo   |")
        print("----------------------------------------------")
        for codigo, info in inventario.items():
            nombre_corto = info['nombre'][:15] + "..." if len(info['nombre']) > 15 else info['nombre']
            print(f"| {codigo:<10} | {nombre_corto:<19} | {info['cantidad']:<8} | ${info['costo']:<9.2f} |")
        print("----------------------------------------------")

    def agregar_articulo(self, codigo, nombre, cantidad, costo):
        if codigo in self.datos:
            print("Error: Ya existe un artículo con ese código.")
        else:
            self.datos[codigo] = {'nombre': nombre, 'cantidad': cantidad, 'costo': costo}
            print(f"Artículo '{nombre}' creado con éxito.")
            self.guardar()   

    def modificar_articulo(self):
        while True:
            os.system("cls")
            self.mostrar_articulos(self.datos)
            codigo = input("Ingrese el código del artículo que desea modificar: ")
            if codigo.strip() == '':
                input("Error: El código del artículo no puede estar vacío. Intente nuevamente.")
                os.system("cls")
            else:
                break  # Salir del bucle si el código del artículo es válido
        
        if codigo not in self.datos:
            print("Error: El artículo no existe en el inventario.")
            decision = input("¿Desea volver al Menú Principal? (S/N): ")
            if decision.lower() == "s" :
                return  # Salir al Menú Principal
            else:
                return self.modificar_articulo()  # Volver a ingresar el código

        while True:
            os.system("cls")
            print("1. Modificar")
            print("2. Eliminar")
            seleccion = input("Ingrese el número de la opción que desea ejecutar: ")

            if seleccion == "1":  # Modificar el nombre del artículo
                while True:
                    nuevo_nombre = input("Ingrese el nuevo nombre del artículo: ")
                    if nuevo_nombre.strip() == '':
                        print("Error: El nuevo nombre del artículo no puede estar vacío. Intente nuevamente.")
                        os.system("cls")
                    else:
                        break  # Salir del bucle si el nuevo nombre del artículo es válido
                self.datos[codigo]['nombre'] = nuevo_nombre
                input(f"Nombre del artículo modificado correctamente a '{nuevo_nombre}'.")
                self.guardar()
                break  # Salir del bucle principal
                
            elif seleccion == "2":  # Eliminar el artículo
                confirmacion = input("¿Está seguro que desea eliminar el artículo? (S/N): ")
                if confirmacion.lower() == "s":
                    del self.datos[codigo]  # Eliminar el artículo del inventario
                    print(f"El artículo con código {codigo} ha sido eliminado del inventario.")
                    self.guardar()
                    break  # Salir del bucle principal
                else:
                    input("Operación de eliminación cancelada.")
                    break  # Salir del bucle principal

            else:
                input("Opción no válida. Por favor, ingrese un número válido.")

    def entrada_inventario(self, codigo_articulo, cantidad_entrada, costo_por_unidad):
        self.datos[codigo_articulo]['cantidad'] += cantidad_entrada
        self.datos[codigo_articulo]['costo'] = costo_por_unidad  # Actualizar el costo por unidad con el valor ingresado
        print(f"{cantidad_entrada} unidades del artículo '{self.datos[codigo_articulo]['nombre']}' han sido ingresadas al inventario.")
        self.guardar()

    def salida_inventario(self):
        os.system('cls')
        while True:
            self.mostrar_articulos(self.datos)
            codigo = input("Ingrese el código del artículo del que quiere registrar salida de inventario: ")
            if codigo.strip() == '':
                input("Error: El código del artículo no puede estar vacío. Intente nuevamente.")
                os.system("cls")
            else:
                break 
        if codigo not in self.datos:
            print(f"Error: El artículo con código {codigo} no existe en el inventario.")
            decision = input("¿Desea ir al Menú Principal? (s/n): ")
            if decision.lower() == "s":
                return  # Salir al Menú Principal
            else:
                return self.salida_inventario()  # Volver a ingresar el código

        while True:
            cantidad_salida = input("Ingrese la cantidad de salida del artículo: ")
            if not cantidad_salida.isdigit() or cantidad_salida.strip() == '':
                input("Error: La cantidad de salida debe ser un número entero. Intente nuevamente.")
                os.system("cls")
                self.mostrar_articulos(self.datos)

            else:
                cantidad_salida = int(cantidad_salida)
                break  # Salir del bucle si la cantidad de salida es válida

        if cantidad_salida > self.datos[codigo]['cantidad']:
            print(f"Error: La cantidad de salida ({cantidad_salida}) es mayor a la existencia ({self.datos[codigo]['cantidad']}).")
            input("Presione Enter para continuar")
            return self.salida_inventario()  # Volver al inicio de salida de inventario

        else:
            self.datos[codigo]['cantidad'] -= cantidad_salida
            print(f"Salida de {cantidad_salida} unidades del artículo '{self.datos[codigo]['nombre']}' registrada correctamente. Quedan {self.datos[codigo]['cantidad']} unidades.")
            self.guardar()

            respuesta = input("¿Se ingresó toda la salida? (S/N): ")
            if respuesta.upper() == "S":
                return  # Salir al Menú Principal
            else:
                return self.salida_inventario()  # Volver al inicio de salida de inventario

class Proveedor:
    def __init__(self):
        self.proveedores = {}

    def guardar(self):
        with open('proveedores.json', 'w') as archivo:
            json.dump(self.proveedores, archivo)
        print("Datos de proveedores guardados correctamente en el archivo.")

    def cargar(self):
        try:
            with open('proveedores.json', 'r') as archivo:
                self.proveedores = json.load(archivo)
            print("Datos de proveedores cargados correctamente desde el archivo.")
        except FileNotFoundError:
            print("El archivo de proveedores no existe. Se creará uno nuevo para guardar los datos.")

    def mostrar_proveedores(self):
        print("Listado de Proveedores:")
        print("----------------------------------")
        print("|     RIF    |        Nombre      |   Contacto  |")
        print("----------------------------------")
        for rif, proveedor in self.proveedores.items():
            nombre_corto = proveedor['nombre'][:15] + "..." if len(proveedor['nombre']) > 15 else proveedor['nombre']
            contacto_corto = proveedor['contacto'][:15] + "..." if len(proveedor['contacto']) > 15 else proveedor['contacto']
            print(f"| {rif:<10} | {nombre_corto:<18} | {contacto_corto:<11} |")
        print("----------------------------------")

    def agregar_proveedor(self, rif, nombre, contacto):
        if rif in self.proveedores:
            print("Error: Ya existe un proveedor con ese RIF.")
        else:
            self.proveedores[rif] = {'nombre': nombre, 'contacto': contacto}
            print(f"Proveedor '{nombre}' creado con éxito.")
            self.guardar()

    def modificar_proveedor(self):
        while True:
            os.system('cls')
            self.mostrar_proveedores()
            rif = input("Ingrese el RIF del proveedor que desea modificar: ")
            if rif.strip() == '':
                input("Error: El RIF no puede estar vacío. Intente nuevamente.")
                os.system("cls")
            elif not rif.isdigit():
                input("Error: El RIF debe ser un valor numérico. Intente nuevamente.")
                os.system("cls")
            else:
                break  # Salir del bucle si el RIF es válido

        if rif not in self.proveedores:
            print("Error: El proveedor no existe.")
            decision = input("¿Desea ir al Menú Principal? (S): ")
            if decision.lower() == "s":
                return  # Salir al Menú Principal
            else:
                return self.modificar_proveedor()  # Volver a ingresar el RIF

        while True:
            nuevo_nombre = input("Ingrese el nuevo nombre del proveedor: ")
            if nuevo_nombre.strip() == '':
                input("Error: El nuevo nombre del proveedor no puede estar vacío. Intente nuevamente.")
                os.system("cls")
            else:
                break  # Salir del bucle si el nuevo nombre del proveedor es válido

        while True:
            nuevo_contacto = input("Ingrese el nuevo número de contacto del proveedor: ")
            if not nuevo_contacto.isdigit():
                input("Error: El número de contacto debe ser un valor numérico. Intente nuevamente.")
                os.system("cls")
            elif nuevo_contacto.strip() == '':
                input("Error: El número de contacto no puede estar vacío. Intente nuevamente.")
                os.system("cls")
            else:
                break  # Salir del bucle si el nuevo número de contacto es válido

        self.proveedores[rif]['nombre'] = nuevo_nombre
        self.proveedores[rif]['contacto'] = nuevo_contacto
        self.guardar()

        print(f"Datos del proveedor con RIF {rif} modificados correctamente.")

class Compra:
    def __init__(self, proveedor, inventario):
        self.proveedor = proveedor
        self.inventario = inventario

    def ingresar_compra(self):
        while True:
            os.system('cls')

            while True:
                self.proveedor.mostrar_proveedores()    
                rif = input("Ingrese el RIF del proveedor: ")
                if not rif.isdigit():
                    input("Error: El RIF debe ser un valor numérico. Intente nuevamente.")
                    os.system("cls")
                elif rif.strip() == '':
                    input("Error: El RIF no puede estar vacío. Intente nuevamente.")
                    os.system("cls")
                else:
                    break 

            if rif not in self.proveedor.proveedores:
                print("Error: El proveedor con el RIF ingresado no se encuentra en la lista.")
                print("Seleccione una opción:")
                print("1. Agregar un nuevo proveedor")
                print("2. Volver al Menú Modificar Inventarios")

                opcion_prov = input("Ingrese el número de la opción que desea ejecutar: ")
                os.system("cls")
                if opcion_prov == "1":
                    while True:
                        nombre_proveedor = input("Ingrese el nombre del proveedor: ")
                        if nombre_proveedor.strip() == '':
                            input("Error: El nombre del proveedor no puede estar vacío. Intente nuevamente.")
                            os.system("cls")
                        else:
                            break  # Salir del bucle para el nombre
                                
                    while True:
                        contacto_proveedor = input("Ingrese el número de contacto del proveedor: ")
                        if not contacto_proveedor.isdigit():
                            input("Error: El número de contacto debe ser un valor numérico. Intente nuevamente.")
                            os.system("cls")
                        elif contacto_proveedor.strip() == '':
                            input("Error: El número de contacto no puede estar vacío. Intente nuevamente.")
                            os.system("cls")
                        else:
                            self.proveedor.agregar_proveedor(rif, nombre_proveedor, contacto_proveedor)
                            break  # Salir del bucle para el contacto
                    input("Proveedor agregado exitosamente.")

                elif opcion_prov == "2":
                    return  # Regresar al Menú Modificar Inventarios
                else:
                    print("Opción no válida. Por favor, ingrese un número válido.")
                    input("Presione Enter para continuar")
                    continue  # Volver al inicio del bucle

            while True:
                os.system('cls')
                while True:
                    self.inventario.mostrar_articulos(self.inventario.datos)
                    codigo_articulo = input("Ingrese el código del artículo: ")
                    if codigo_articulo.strip() == '':
                        input("Error: El código del artículo no puede estar vacío. Intente nuevamente.")
                        os.system("cls")
                    else:
                        break  # Salir del bucle si el código del artículo es válido

                
                if codigo_articulo not in self.inventario.datos:
                    print("Error: El artículo con el código ingresado no se encuentra en el inventario.")
                    print("Seleccione una opción:")
                    print("1. Agregar un nuevo artículo")
                    print("2. Volver a ingresar el código")
                    
                    opcion_articulo = input("Ingrese el número de la opción que desea ejecutar: ")
                    os.system("cls")
                    if opcion_articulo == "1":
                        while True:
                            nombre_articulo = input("Ingrese el nombre del nuevo artículo: ")
                            if nombre_articulo.strip() == '':
                                input("Error: El nombre del artículo no puede estar vacío. Intente nuevamente.")
                                os.system("cls")
                            else:
                                self.inventario.agregar_articulo(codigo_articulo, nombre_articulo, cantidad=0, costo=0)
                                input("")
                                os.system("cls")
                                break  # Salir del bucle si el nombre del artículo es válido 

                    elif opcion_articulo == "2":
                        continue  # Volver a ingresar el código del artículo
                    
                    else:
                        print("Opción no válida. Por favor, ingrese un número válido.")
                        input("Presione Enter para continuar")
                        os.system("cls")
                        continue

                while True:
                    cantidad_entrada = input("Ingrese la cantidad de entrada del artículo: ")
                    if not cantidad_entrada.isdigit() or int(cantidad_entrada) <= 0:
                        input("Error: La cantidad de entrada debe ser un número entero positivo. Intente nuevamente.")
                        os.system("cls")
                    else:
                        cantidad_entrada = int(cantidad_entrada)
                        break  # Salir del bucle si la cantidad es válida

                while True:
                    costo_por_unidad = input("Ingrese el costo por unidad del artículo: ")
                    if costo_por_unidad.strip() == '' or not costo_por_unidad.replace('.', '', 1).isdigit() or float(costo_por_unidad) <= 0:
                        input("Error: El costo por unidad debe ser un número positivo. Intente nuevamente.")
                        os.system("cls")
                    else:
                        costo_por_unidad = float(costo_por_unidad)
                        break  # Salir del bucle si el costo por unidad es válido


                self.inventario.entrada_inventario(codigo_articulo, cantidad_entrada, costo_por_unidad)

                respuesta = input("¿Desea agregar otro artículo en la misma compra? (s/n): ")
                if respuesta.lower() != "s":
                    return  # Salir al menú principal

class Menu:
    def __init__(self):
        self.inventario = Inventario()
        self.proveedor = Proveedor()
        self.compra = Compra(self.proveedor, self.inventario)
        self.inventario.cargar()
        self.proveedor.cargar()
        self.manager = UserManager()

    def leer_json_funcion(self):
        with open('function_data.json', 'r') as file:
            function_data = json.load(file)
            return function_data.get('function_result')


    def mostrar_menu_principal(self):
        while True:
            os.system('cls')
            
            print("\n========= MENÚ PRINCIPAL =========")
            print("1. Modificar Inventario")
            print("2. Visualizar Inventario")
            print("3. Modificar Usuario")
            print("4. Cerrar Sesión")
            opcion = input("Ingrese el número de la opción que desea ejecutar: ")

            if opcion == "1":
                
                os.system('cls')
                if(self.leer_json_funcion() == True):
                    self.mostrar_menu_modificar_inventario()

                else:
                    print("No tiene Aptitudes de Administrador")
                    input("Presione Enter para Continuar")

            elif opcion == "2":
                os.system('cls')
                self.inventario.mostrar_articulos(self.inventario.datos)
                input("Presione Enter para continuar")

            elif opcion == "3":
                os.system('cls')
                if(self.leer_json_funcion() == True):
                    print("Opción de Modificar Usuario seleccionada.")

                    username_actual = "nombre_usuario_actual"  # Asigna aquí el nombre de usuario en sesión

                    manager.modificar_usuario(username_actual)  # Llama a la función de modificar usuario del UserManager

                else:
                    print("No tiene Aptitudes de Administrador")
                    input("Presione Enter para Continuar")
                

            elif opcion == "4":
                os.system('cls')
                print("Cerrando sesión. ¡Hasta luego!")
                break
            else:
                print("Opción no válida. Por favor, ingrese un número válido.")

    def mostrar_menu_modificar_inventario(self):
        

        while True:
            os.system('cls')
            print("\n========= MENÚ MODIFICAR INVENTARIO =========")
            print("1. Crear Artículo")
            print("2. Crear Proveedor")
            print("3. Ingresar Compra")
            print("4. Salida de Inventario")
            print("5. Modificar/Eliminar Artículo")
            print("6. Modificar Proveedor")
            print("7. Volver al Menú Principal")
            opcion = input("Ingrese el número de la opción que desea ejecutar: ")

            if opcion == "1":
                while True:  # Bucle para permitir la creación de múltiples artículos
                    os.system('cls')
                    codigo = input("Ingrese el código del artículo: ")
                    if codigo in self.inventario.datos:
                        print("Error: Ya existe un artículo con ese código.")
                        respuesta = input("¿Desea volver al Menú Principal? (s/n): ")
                        if respuesta.lower() == "s":
                            break  # Salir del bucle y volver al menú principal
                        else:
                            continue  # Volver a pedir el código del artículo
                    elif codigo == '':
                        input("Error: El código del artículo no puede estar vacío. Intente nuevamente.")
                        os.system("cls")
                    else:
                        while True:
                            nombre = input("Ingrese el nombre del artículo: ")
                            if nombre == '':
                                input("Error: El nombre del artículo no puede estar vacío. Intente nuevamente.")
                                os.system("cls")
                            else:
                                self.inventario.agregar_articulo(codigo, nombre, cantidad=0, costo=0)
                                break
                            
                        respuesta = input("¿Desea crear otro artículo? (s/n): ")
                        if respuesta.lower() != "s":
                            break  # Salir del bucle y volver al menú principal

            elif opcion == "2":
                while True:
                    os.system('cls')
                    rif = input("Ingrese el RIF del proveedor: ")
                    if rif in self.proveedor.proveedores:
                        print("Error: Ya existe un proveedor con ese RIF.")
                        respuesta = input("¿Desea volver al Menú Principal? (s/n): ")
                        if respuesta.lower() == "s":
                            break  # Salir del bucle y volver al menú principal
                        else:
                            os.system("cls")
                            continue  # Volver a pedir el RIF del proveedor
                    elif not rif.isdigit():
                        input("Error: El RIF debe ser un valor numérico. Intente nuevamente.")
                        os.system("cls")
                    else:
                        while True:
                            nombre = input("Ingrese el nombre del proveedor: ")
                            if nombre.strip() == '':
                                input("Error: El nombre del proveedor no puede estar vacío. Intente nuevamente.")
                                os.system("cls")
                            else:
                                break  # Salir del bucle para el nombre
                                
                        while True:
                            contacto = input("Ingrese el número de contacto del proveedor: ")
                            if not contacto.isdigit():
                                input("Error: El número de contacto debe ser un valor numérico. Intente nuevamente.")
                                os.system("cls")
                            elif contacto.strip() == '':
                                input("Error: El número de contacto no puede estar vacío. Intente nuevamente.")
                                os.system("cls")
                            else:
                                self.proveedor.agregar_proveedor(rif, nombre, contacto)
                                break  # Salir del bucle para el contacto
                        respuesta = input("¿Desea crear otro proveedor? (s/n): ")
                        if respuesta.lower() != "s":
                            break  # Salir del bucle y volver al menú principal

            elif opcion == "3":
                os.system('cls')
                self.compra.ingresar_compra() 

            elif opcion == "4":
                os.system('cls')
                self.inventario.salida_inventario()

            elif opcion == "5":
                os.system('cls')
                self.inventario.modificar_articulo()

            elif opcion == "6":
                os.system('cls')
                self.proveedor.modificar_proveedor()

            elif opcion == "7":
                os.system('cls')
                break

            else:
                print("Opción no válida. Por favor, ingrese un número válido.")

class User:
    def __init__(self, username, password, admin=False):
        self.username = username
        self.password = password
        self.admin = admin

class UserManager:
    def __init__(self):
        self.users = []
        self.active_user = None
        self.type_user = None

    def get_active_user_admin(self):
        for user in self.users:
            if user.username == self.active_user:
                return user.admin
        return False 

    def type_user_function(self):
        # Lógica de la función type_user_function
        result = self.type_user
        
        # Guardar la llamada de la función en el archivo JSON
        function_data = {
            'function_result': result
        }

        with open('function_data.json', 'w') as file:
            json.dump(function_data, file)

        print("Función llamada y resultado guardado exitosamente en el archivo JSON.")
        
        return result
        
    def save_users(self):
        with open('users.json', 'w') as f:
            json.dump([vars(user) for user in self.users], f)

    def load_users(self):
        try:
            with open('users.json', 'r') as f:
                users_json = json.load(f)
                self.users = [User(user['username'], user['password'], user['admin']) for user in users_json]
        except FileNotFoundError:
            pass

    def create_user(self):
        username_exists = True
        while username_exists:
            while True:
                username = input("Ingrese el nombre de usuario: ")
                if username.strip() == '':
                    input("Error: El nombre de usuario no puede estar vacío. Intente nuevamente.")
                    os.system("cls")
                else:
                    break  # Salir del bucle si el nombre de usuario es válido
            username_exists = any(user.username == username for user in self.users)
            if username_exists:
                input("El nombre de usuario ya existe. Intente con otro.")
                os.system("cls")

        password = asterisk("Ingrese la contraseña: ")
        self.users.append(User(username, password, admin=False))
        self.save_users()
        print("Usuario creado exitosamente.")

    def login(self):
        username = input("Ingrese su nombre de usuario: ")
        password = asterisk("Ingrese su contraseña: ")
        user = next((u for u in self.users if u.username == username and u.password == password), None)
        if user is not None:
            print("Inicio de sesión exitoso.")
            self.active_user = username
            self.type_user = self.get_active_user_admin()
            self.type_user_function()
            menu.mostrar_menu_principal()  # Abrir el menú principal después del inicio de sesión exitoso
        else:
            print("Error en la autenticación. Verifique sus credenciales.")

    def modificar_usuario(self, nombre_usuario_actual):
        nombre_usuario = input("Ingrese el nombre de usuario que desea modificar: ")
        usuario = next((user for user in self.users if user.username == nombre_usuario), None)
        nombre_usuario_actual = self.active_user
        if usuario is None:  # Usuario no encontrado
            print("Error: El usuario no existe.")
            decision = input("¿Desea volver al Menú Principal? (S/N): ")
            os.system("cls")
            if decision.lower() == "s":
                return  # Volver al Menú Principal
            else:
                return self.modificar_usuario(nombre_usuario_actual)  # Volver al inicio de la modificación de usuario

        if usuario.admin:  # El usuario a modificar es administrador
            if usuario.username == nombre_usuario_actual:  # Usuario en sesión
                print("Error: No puedes modificar tu propio rol de administrador.")
                decision = input("¿Desea volver al Menú Principal? (S/N): ")
                if decision.lower() == "s":
                    return  # Volver al Menú Principal
                else:
                    return self.modificar_usuario(nombre_usuario_actual)  # Volver al inicio de la modificación de usuario

            else:  # Usuario no es el que está en sesión
                usuario.admin = False  # Quitar rol de administrador
                print(f"El usuario {usuario.username} ya no es administrador.")
                input("Presione Enter para Continuar")
                os.system("cls")
                self.save_users()

        else:  # El usuario a modificar no es administrador
            usuario.admin = True  # Convertir en administrador
            print(f"El usuario {usuario.username} ahora es administrador.")
            input("Presione Enter para Continuar")
            os.system("cls")
            self.save_users()
    
def asterisk(prompt):
    password = ""
    print(prompt, end="", flush=True)
    while True:
        char = msvcrt.getch().decode("utf-8")
        if char == "\r":
            print()
            break
        elif char == "\x08":
            if password:
                password = password[:-1]
                print("\b \b", end="", flush=True)
        else:
            password += char
            print("*", end="", flush=True)

    return password

# Resto del código para la ejecución del menú principal y la aplicación

if __name__ == "__main__":
    menu = Menu()
    manager = UserManager()
    manager.load_users()

    # Verificar si hay usuarios existentes al cargar los datos
    if not manager.users:
        # Si no hay usuarios, se crea un usuario administrador predeterminado
        manager.users.append(User("admin", "admin_password", admin=True))
        manager.save_users()
    else:
        print("Usuarios encontrados en el sistema.")

    while True:
        os.system("cls")
        print("Bienvenido al Sistema de Inventario\n")
        print("Opciones:")
        print("1. Crear usuario no administrador")
        print("2. Iniciar sesión")
        print("3. Salir de aplicacion")
        option = input("¿Qué desea hacer?: ")
        os.system("cls")

        if option == "1":
            manager.create_user()
        elif option == "2":
            manager.login()
        elif option == "3":
            confirmacion = input("Seguro quiere salir? (S/N): ")
            if confirmacion.upper() == "S":
                break
        else:
            print("Opción no válida. Intente de nuevo.")
