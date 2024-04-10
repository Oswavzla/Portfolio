import sys
import msvcrt 
import os
import getpass

str_input = ""
while True:
    c = sys.stdin.read(1)
    if c == " ":
        break
    str_input += c

class user():
    nUsers = 0
    def __init__(self,name,password):
        self.name = name
        self.password = password
        self.online = False
        self.fails = 3
        self.admin = False
        user.nUsers += 1
    def asterisk(self):
        password = ""
        print("\tContraseña: ", end="", flush=True)  # Print the initial prompt
        while True:
            char = msvcrt.getch().decode("utf-8")
            if char == "\r":  # Enter key pressed
                print()  # Print a newline after user input
                break
            elif char == "\x08":  # Backspace key pressed
                if password:
                    password = password[:-1]
                    print("\b \b", end="", flush=True)  # Erase the last character
            else:
                password += char
                print("*", end="", flush=True)  # Print an asterisk

        return password

    def conect(self):
        print()
        print("\t\tINICIAR SESION")
        print()
        myName = input("\tUsuario: ")
        myPass = self.asterisk()
        if myPass == self.password and myName==self.name:
            print()
            print("\t\tBienvenido al Sistema!")
            msvcrt.getch()
            self.online = True
        else:
            self.fails -= 1
            if self.fails > 0:
                print()
                print("\tNombre de usuario o Contraseña Incorrectos.")
                print()
                print("\t\tIntentos Restantes: ",self.fails)
                msvcrt.getch()
                os.system("cls")
                self.conect()
            else:
                print("\tDemasiados intentos fallidos")
                os.system("cls")
                print()
                print("\t\tError al iniciar sesion.")
                print("\t\t\tAdios!")
                msvcrt.getch()
    def disconect(self):
        if self.online:
            os.system("cls")
            checkOut = input("\tPresione 's' para cerrar sesion y 'n' para continuar en el sistema: ")
            if checkOut == 's':
                os.system("cls")
                print("\t\tSesion cerrada con exito.")
                print("\t\t\tAdios!")
                self.online = False
                msvcrt.getch()
            elif checkOut == 'n':
                print("\tSe mantuvo abierta la sesion.")
                msvcrt.getch()
                os.system("cls")
                self.disconect()
            else:
                print("\tError en la entrada...")
                msvcrt.getch()
                os.system("cls")
                self.disconect()
        else:
            msvcrt.getch()     
user1 = user('estudiante','1234')
user2 = user('vago','4321')


#Call functions


user1.conect()
user1.disconect()
#user2.conect()
