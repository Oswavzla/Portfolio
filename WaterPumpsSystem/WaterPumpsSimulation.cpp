/*Programa que simula el sistema de bombeo de etileno de la empresa Pequiven*/

#include<iostream>
#include<fstream>
#include<windows.h>
#include<locale.h>

using namespace std;

main()
{
	setlocale(LC_ALL,"spanish");
	
	string bomba1,v_succ101,v_desc201,SW201;      //Bomba 1, v�lvula de succi�n 101, v�lvula de descarga 201, switch de flujo 201.
	double TP201=0;                                 //Transmisor de presi�n 201 (Bomba1).
	string bomba2,v_succ102,v_desc202,SW202;      //Bomba 2, v�lvula de succi�n 102, v�lvula de descarga 202, switch de flujo 202.
	double TP202=0;                                  //Transmisor de presi�n 202 (Bomba2).
	string bomba3,v_succ103,v_desc203,SW203;      //Bomba 3, v�lvula de succi�n 103, v�lvula de descarga 203, switch de flujo 203.
	double TP203=0;                                   //Transmisor de presi�n 203 (Bomba3).
	int rotacion;                                        //Variable donde se ingresa el tiempo de rotaci�n.
	double caudal1=0,caudal2=0,caudal3=0;                   //Caudales de etileno (expresados en Gal/min).
	double caudal1_seg=0, caudal2_seg=0, caudal3_seg=0;  //Caudales de etileno (Expresados en Gal/seg para poder sumarlos al acumulado).
	double galones_acum=0;                                //Galones acumulados.
	int caso=0;                                           //Indica cu�l de los casos hay que tomar dependiendo del estado de las bombas (ENCENDIDA/APAGADA).
	int caso_1encendida;                                  //Indica cu�l de los casos hay que tomar dependiendo del estado de las bombas (ENCENDIDA/APAGADA) (Caso especial, cuando solo una bomba esta encendida).
	int caso_apagadas;
	int ciclos=0;                                         //Contabiliza cuantas veces se repite los ciclos de rotacion.
	int lector=0;
	int tiempo;
	string old_succ101,old_desc201,old_succ102,old_desc202,old_succ103,old_desc203;  //lectura anterior del texto.
	int old_rotacion;																 //Lectuta anterior de la rotaci�n.
	string pantalla="ON";
	
	inicio:
	
	ifstream leer("C:\\Users\\User\\Documents\\Programas C++\\Simulacion de sistemas de control\\Parcial III.txt");
	
	leer>>v_succ101>>v_desc201>>v_succ102>>v_desc202>>v_succ103>>v_desc203>>rotacion;

	
	//En caso de que el programa lea un texto diferente al anterior, se cambian las condiciones de la bomba (Encendido/Apagado de la bomba, Switch de flujo).
	//En caso contrario, se mantienen las mismas condiciones de la bomba (Encendido/Apagado de la bomba, Switch de flujo).
	
	
	if(old_succ101!=v_succ101 or old_desc201!=v_desc201 or old_succ102!=v_succ102 or old_desc202!=v_desc202 or old_succ103!=v_succ103 or old_desc203!=v_desc203 or old_rotacion!=rotacion)
	{
		lector=0;
		ciclos=0;
		tiempo=rotacion;
	}
	
	old_succ101=v_succ101;
	old_desc201=v_desc201;
	old_succ102=v_succ102;
	old_desc202=v_desc202;
	old_succ103=v_succ103;
	old_desc203=v_desc203;
	old_rotacion=rotacion;
	
	
	//Solo se cambian el estado de las v�lvulas cuando el programa lea un texto diferente al anterior y adem�s cuando se haya concluido el tiempo de rotaci�n
	
	if(lector==0)
	{
		
		//Validaci�n de los datos le�dos del texto
	
		if(v_succ101=="ABIERTA" or v_succ101=="abierta" or v_succ101=="Abierta")
		{
			v_succ101="ABIERTA";
		} 
	 
		if(v_succ101=="CERRADA" or v_succ101=="cerrada" or v_succ101=="Cerrada")
		{
			v_succ101="CERRADA";
		} 
	
		if(v_desc201=="ABIERTA" or v_desc201=="abierta" or v_desc201=="Abierta")
		{
			v_desc201="ABIERTA";
		}
	
		if(v_desc201=="CERRADA" or v_desc201=="cerrada" or v_desc201=="Cerrada")
		{
			v_desc201="CERRADA";
		}
	
	
		if(v_succ102=="ABIERTA" or v_succ102=="abierta" or v_succ102=="Abierta")
		{
			v_succ102="ABIERTA";
		}
	 
		if(v_succ102=="CERRADA" or v_succ102=="cerrada" or v_succ102=="Cerrada")
		{
			v_succ102="CERRADA";
		}	 
	
		if(v_desc202=="ABIERTA" or v_desc202=="abierta" or v_desc202=="Abierta")
		{
			v_desc202="ABIERTA";
		}
	
		if(v_desc202=="CERRADA" or v_desc202=="cerrada" or v_desc202=="Cerrada")
		{
			v_desc202="CERRADA";
		}
	
		
		if(v_succ103=="ABIERTA" or v_succ103=="abierta" or v_succ103=="Abierta")
		{
			v_succ103="ABIERTA";
		}
	 
		if(v_succ103=="CERRADA" or v_succ103=="cerrada" or v_succ103=="Cerrada")
		{
			v_succ103="CERRADA";
		} 
	
		if(v_desc203=="ABIERTA" or v_desc203=="abierta" or v_desc203=="Abierta")
		{
			v_desc203="ABIERTA";
		}
	
		if(v_desc203=="CERRADA" or v_desc203=="cerrada" or v_desc203=="Cerrada")
		{
			v_desc203="CERRADA";
		}
		
		//Condiciones iniciales del Switch de flujo (SW201) encendido/apagado de la bomba 1.
	
		if(v_succ101=="CERRADA")
		{
			SW201="OFF";
			bomba1="APAGADA";
			pantalla="ON";
		}
	
		if(v_succ101=="ABIERTA")
		{
			SW201="ON";
			
			if(caso_apagadas==0)
			{
				bomba1="ENCENDIDA";
			}
			
			pantalla="ON";
		}
	
		//Condiciones iniciales del Switch de flujo (SW201) y del encendido/apagado de la bomba 2.	
	
		if(v_succ102=="CERRADA")
		{
			SW202="OFF";
			bomba2="APAGADA";
			pantalla="ON";
		}
	
		if(v_succ102=="ABIERTA")
		{
			SW202="ON";
			
			if(caso_apagadas==0)
			{
				bomba2="ENCENDIDA";
			}
			
			pantalla="ON";
		}
	
		//Condiciones iniciales del Switch de flujo (SW201) y del encendido/apagado de la bomba 3.
	
		if(v_succ103=="CERRADA")
		{
			SW203="OFF";
			bomba3="APAGADA";
			pantalla="ON";
		}
	
		if(v_succ103=="ABIERTA")
		{
			SW203="ON";
			
			if(caso_apagadas==0)
			{
				bomba3="ENCENDIDA";
			}
			
			pantalla="ON";
		}
	
	}	
		repetir:
			
			caso=0;
			caso_1encendida=0;
			caso_apagadas=0;
			
		
		//Validamos cual de los casos de Encendido/Apagado de la bomba tenemos.
	
		//Evaluamos en el caso de que se abran las 3 v�lvulas de succi�n, el programa autom�ticamente apaga una bomba.
	
		if(bomba1=="ENCENDIDA" and bomba2=="ENCENDIDA" and bomba3=="ENCENDIDA")
		{
			bomba1="ENCENDIDA";
			bomba2="ENCENDIDA";
			bomba3="APAGADA";
			caso=1;	
		}
	
		//Evaluamos los casos en que 2 bombas est�n prendidas.
	
		if(bomba1=="ENCENDIDA" and bomba2=="ENCENDIDA" and bomba3=="APAGADA")
		{
			caso=1;
		}
	
		if(bomba1=="APAGADA" and bomba2=="ENCENDIDA" and bomba3=="ENCENDIDA")
		{
			caso=2;
		}
	
		if(bomba1=="ENCENDIDA" and bomba2=="APAGADA" and bomba3=="ENCENDIDA")
		{
			caso=3;
		}
	
	//Evaluamos los casos en que 1 sola bomba est� prendida.
	
		if(bomba1=="ENCENDIDA" and bomba2=="APAGADA" and bomba3=="APAGADA")
		{
			caso_1encendida=1;
		}
	
		if(bomba1=="APAGADA" and bomba2=="ENCENDIDA" and bomba3=="APAGADA")
		{
			caso_1encendida=2;
		}
	
		if(bomba1=="APAGADA" and bomba2=="APAGADA" and bomba3=="ENCENDIDA")
		{
			caso_1encendida=3;
		}
		
		if(bomba1=="APAGADA" and bomba2=="APAGADA" and bomba3=="APAGADA")
		{
			caso_apagadas=1;
		}

		
	//Presentamos los valores en pantalla.
	
	if(pantalla=="ON")
	{
		system("cls");
		
		cout<<"Tiempo establecido para la rotaci�n de las bombas = "<<rotacion<<" segundos"<<endl<<endl;
		cout<<"Siguiente rotaci�n en = "<<tiempo<<" segundos"<<endl<<endl;
		cout<<"       Bomba 1                               Bomba 2                                       Bomba 3"<<endl<<endl;
		cout<<"Estado = "<<bomba1<<"                        Estado = "<<bomba2<<"                                Estado = "<<bomba3<<""<<endl;
		cout<<"Switch de flujo = "<<SW201<<"                   Switch de flujo = "<<SW202<<"                           Switch de flujo = "<<SW203<<""<<endl;
		cout<<"Presi�n = "<<TP201<<" psi                         Presi�n = "<<TP202<<" psi                                 Presi�n = "<<TP203<<" psi"<<endl;
		cout<<"Gal/min = "<<caudal1<<"                             Gal/min = "<<caudal2<<"                                     Gal/min = "<<caudal3<<""<<endl<<endl<<endl;
		cout<<"Total de galones acumulados = "<<galones_acum<<" Gal"<<endl<<endl<<endl<<endl;
		cout<<"Importante-----> Los galones van aumentando cada segundo, dependiendo de las v�lvulas de succi�n y descarga."<<endl;
		cout<<"Importante-----> Si la bomba est� apagada, y tiene una presi�n mayor a los 50 psi, la bomba no se prender�"<<endl;
		cout<<"hasta que se abra la v�lvula de descarga, y pueda disminuir la presi�n."<<endl;
		cout<<"Importante-----> Si se encuentra trabajando solo una bomba, y las otras est�n apagadas (presi�n>50/Switch de flujo= OFF)"<<endl;
		cout<<"no habr� rotaci�n."<<endl;
		pantalla="OFF";
	}
	
	Sleep(1000);
	
	if(tiempo<=0)
	{
		tiempo=rotacion;
	}

	//Simulamos el caso 1.
	
	if(caso==1)
	{
		
		
		//Validamos si se cumple el tiempo de rotaci�n, para rotar las bombas (Caso en el que las 3 bombas no presentan fallas).
		
		if(rotacion==ciclos and v_succ103=="ABIERTA" and TP203<50)
		{	
			bomba1="APAGADA";
			caudal1=0;
			caudal1_seg=0;
			bomba3="ENCENDIDA";
			ciclos=0;
			pantalla="ON";
			goto repetir;
		}
		
		//En caso de que la bomba 3 tenga una presi�n mayor a 50 psi, o el Switch de flujo= OFF, hacemos la rotacion con las 2 bombas operativas.
		
		//Cuando el programa detecta que la bomba 3 tiene una falla(presi�n>50 o Switch de flujo= OFF), se apaga directamente la bomba 1.
		
		//Rotaci�n a la bomba 2.
		
		if(TP203>50 or SW203=="OFF")
		{
			bomba1="APAGADA";
			caudal1=0;
			caudal1_seg=0;
			ciclos=0;
			pantalla="ON";
			goto repetir;
		}
		
			if(ciclos>rotacion)
		{
			ciclos=0;
		}
		
		//Simulaci�n del Switch de flujo (SW201) de la bomba 1 
	
		if(SW201=="OFF" and v_succ101=="ABIERTA")
		{
			SW201="ON";
			pantalla="ON";
		}
	
		if(SW201=="ON" and v_succ101=="CERRADA")
		{
			SW201="OFF";
			pantalla="ON";
		}
	
	
		//Simulaci�n del Switch de flujo (SW202) de la bomba 2 
	
		if(SW202=="OFF" and v_succ102=="ABIERTA")
		{
			SW202="ON";
			pantalla="ON";
		}
	
		if(SW202=="ON" and v_succ102=="CERRADA")
		{
			SW202="OFF";
			pantalla="ON";
		}
		
		//Simulaci�n de presi�n (TP201) de la bomba 1.
	
		if(bomba1=="ENCENDIDA" and v_desc201=="ABIERTA")
		{
			if(TP201<33)
			{
				TP201=TP201+1;
				pantalla="ON";
			}
		
		if(TP201>33)
			{
				TP201=TP201-1;
				pantalla="ON";
			}
		}
	
		if(bomba1=="ENCENDIDA" and v_desc201=="CERRADA" and TP201<=50)
		{
			TP201=TP201+1;
			pantalla="ON";
		}
	
		if(bomba1=="APAGADA" and v_desc201=="ABIERTA")
		{
			TP201=TP201-1;
			pantalla="ON";
		}
	
	
	
	
		//Simulaci�n de presi�n (TP202) de la bomba 2.
	
		if(bomba2=="ENCENDIDA" and v_desc202=="ABIERTA")
		{
			if(TP202<33)
			{
				TP202=TP202+1;
				pantalla="ON";
			}
		
			if(TP202>33)
			{
				TP202=TP202-1;
				pantalla="ON";
			}
		}
	
		if(bomba2=="ENCENDIDA" and v_desc202=="CERRADA" and TP202<=50)
		{
			TP202=TP202+1;
			pantalla="ON";
		}
	
		if(bomba2=="APAGADA" and v_desc202=="ABIERTA")
		{
			TP202=TP202-1;
			pantalla="ON";
		}	
		
		//Cuando se produce la rotaci�n, cuando la bomba 3 se apaga, y se tiene la v�lvula de descarga abierta, la presi�n disminuye a cero y el caudal cae a 0.
	
		if(bomba3=="APAGADA" and v_desc203=="ABIERTA")
			{
				TP203=TP203-1;
				caudal3=0;
				caudal3_seg=0;
				pantalla="ON";
			}
		
		//Validamos que la presi�n no sea negativa.
		
		if(TP201<0)
		{
			TP201=0;
		}
		
		if(TP202<0)
		{
			TP202=0;
		}
		
		if(TP203<0)
		{
			TP203=0;
		}
	
		//Simulaci�n del caudal de la bomba 1.
	
		if(bomba1=="ENCENDIDA" and v_succ101=="ABIERTA" and v_desc201=="ABIERTA")
		{
			caudal1=40;
			caudal1_seg=caudal1/60;
			pantalla="ON";
		}
	
		else
		{
			caudal1=0;
			caudal1_seg=0;
			pantalla="ON";
		}
	
	
   		//Simulaci�n del caudal de la bomba 2.
	
		if(bomba2=="ENCENDIDA" and v_succ102=="ABIERTA" and v_desc202=="ABIERTA")
		{
			caudal2=40;
			caudal2_seg=caudal2/60;
			pantalla="ON";
		}	
	
			else
		{
			caudal2=0;
			caudal2_seg=0;
			pantalla="ON";
		}
		
		//Sumas de lo acumulado en las bombas operatvas.
	
		galones_acum=galones_acum+caudal1_seg+caudal2_seg;
	
	
		//Simulaci�n del encendido/apagado de la bomba 1.
	
		if(bomba1=="ENCENDIDA" and TP201>50)
		{
			bomba1="APAGADA";
			caudal1_seg=0;
			
			if(TP203<50 and SW203=="ON")
			{
				bomba3="ENCENDIDA";	
			}
			
			pantalla="ON";
		}
	
		if(bomba1=="APAGADA" and TP201<20 and SW201=="ON" and ciclos!=0)
		{
			bomba1="ENCENDIDA";
			pantalla="ON";
		}
		
		
	
	
		//Simulaci�n del encendido/apagado de la bomba 2.
	
		if(bomba2=="ENCENDIDA" and TP202>50)
		{
			bomba2="APAGADA";
			caudal2=0;
			caudal2_seg=0;
			
			if(TP203<50 and SW203=="ON")
			{
				bomba3="ENCENDIDA";	
			}
			
			pantalla="ON";
		}
	
		if(bomba2=="APAGADA" and TP202<20 and SW202=="ON")
		{
			bomba2="ENCENDIDA";
			pantalla="ON";                      
		}

		ciclos=ciclos+1;
		tiempo=tiempo-1;
		lector=1;
		goto inicio;
	}



	//Simulamos el caso 2.
	
	if(caso==2)
	{
		
		//Validamos si se cumple el tiempo de rotaci�n, para rotar las bombas (Caso en el que las 3 bombas no presentan fallas)
		
		if(rotacion==ciclos and v_succ101=="ABIERTA" and TP201<50)
		{
			bomba2="APAGADA";
			caudal2=0;
			caudal2_seg=0;
			bomba1="ENCENDIDA";
			ciclos=0;
			pantalla="ON";
			goto repetir;
		}
		
		//En caso de que la bomba 1 tenga una presi�n mayor a 50 psi, o el Switch de flujo= OFF, hacemos la rotacion con las 2 bombas operativas.
		
		//Cuando el programa detecta que la bomba 1 tiene una falla(presi�n>50 o Switch de flujo= OFF), se apaga directamente la bomba 2.
		
		//Rotaci�n a la bomba 3.
		
		if(TP201>50 or SW201=="OFF")
		{
			bomba2="APAGADA";
			caudal2=0;
			caudal2_seg=0;
			ciclos=0;
			pantalla="ON";
			goto repetir;
		}
		
			if(ciclos>rotacion)
		{
			ciclos=0;
		}
		
		//Simulaci�n del Switch de flujo (SW202) de la bomba 2 
	
		if(SW202=="OFF" and v_succ102=="ABIERTA")
		{
			SW202="ON";
			pantalla="ON";
		}
	
		if(SW202=="ON" and v_succ102=="CERRADA")
		{
			SW202="OFF";
			pantalla="ON";
		}
	

	
		//Simulaci�n del Switch de flujo (SW203) de la bomba 3 
	
		if(SW203=="OFF" and v_succ103=="ABIERTA")
		{
			SW203="ON";
			pantalla="ON";
		}
	
		if(SW203=="ON" and v_succ103=="CERRADA")
		{
			SW203="OFF";
			pantalla="ON";
		}
		
		
		//Simulaci�n de presi�n (TP202) de la bomba 2.
	
		if(bomba2=="ENCENDIDA" and v_desc202=="ABIERTA")
		{
			if(TP202<33)
			{
				TP202=TP202+1;
				pantalla="ON";
			}
		
			if(TP202>33)
			{
				TP202=TP202-1;
				pantalla="ON";
			}
		}
	
		if(bomba2=="ENCENDIDA" and v_desc202=="CERRADA" and TP202<=50)
		{
			TP202=TP202+1;
			pantalla="ON";
		}
	
		if(bomba2=="APAGADA" and v_desc202=="ABIERTA")
		{
			TP202=TP202-1;
			pantalla="ON";
		}
	
	
		//Simulaci�n de presi�n (TP203) de la bomba 3.
	
		if(bomba3=="ENCENDIDA" and v_desc203=="ABIERTA")
		{
			if(TP203<33)
			{
				TP203=TP203+1;
				pantalla="ON";
			}
		
			if(TP203>33)
			{
				TP203=TP203-1;
				pantalla="ON";
			}
		}
	
		if(bomba3=="ENCENDIDA" and v_desc203=="CERRADA" and TP203<=50)
		{
			TP203=TP203+1;
			pantalla="ON";
		}
	
		if(bomba3=="APAGADA" and v_desc203=="ABIERTA")
		{
			TP203=TP203-1;
			pantalla="ON";
		}
		
		//Cuando se produce la rotaci�n, cuando la bomba 1 se apaga, y se tiene la v�lvula de descarga abierta, la presi�n disminuye a cero y el caudal cae a 0.
	
		if(bomba1=="APAGADA" and v_desc201=="ABIERTA")
		{
			TP201=TP201-1;
			caudal1=0;
			caudal1_seg=0;
			pantalla="ON";
		}
		
		//Validamos que la presi�n no sea negativa.
		
		if(TP201<0)
		{
			TP201=0;
		}
		
		if(TP202<0)
		{
			TP202=0;
		}
		
		if(TP203<0)
		{
			TP203=0;
		}
	
		
		//Simulaci�n del caudal de la bomba 2.
	
		if(bomba2=="ENCENDIDA" and v_succ102=="ABIERTA" and v_desc202=="ABIERTA")
		{
			caudal2=40;
			caudal2_seg=caudal2/60;
			pantalla="ON";
		}	
	
		else
		{
			caudal2=0;
			caudal2_seg=0;
			pantalla="ON";
		}
	
	
		//Simulaci�n del caudal de la bomba 3.
	
		if( bomba3=="ENCENDIDA" and v_succ103=="ABIERTA" and v_desc203=="ABIERTA")
		{
			caudal3=40;
			caudal3_seg=caudal3/60;
			pantalla="ON";
		}	
	
			else
		{
			caudal3=0;
			caudal3_seg=0;
			pantalla="ON";
		}
	
	
		//Sumas de lo acumulado en las bombas operatvas.
	
		galones_acum=galones_acum+caudal2_seg+caudal3_seg;
		
		
		//Simulaci�n del encendido/apagado de la bomba 2.
	
		if(bomba2=="ENCENDIDA" and TP202>50)
		{
			bomba2="APAGADA";
			caudal2_seg=0;
			
				if(TP201<50 and SW201=="ON")
			{
				bomba1="ENCENDIDA";	
			}
			
			pantalla="ON";
		}
	
		if(bomba2=="APAGADA" and TP202<20 and SW202=="ON" and ciclos!=0)
		{
			bomba2="ENCENDIDA";
			pantalla="ON";
		}
	
	
	
		//Simulaci�n del encendido/apagado de la bomba 3.
	
		if(bomba3=="ENCENDIDA" and TP203>50)
		{
			bomba3="APAGADA";
			caudal3_seg=0;
			
				if(TP201<50 and SW201=="ON") 
			{
				bomba1="ENCENDIDA";	
			}
		
			pantalla="ON";
		}
	
		if(bomba3=="APAGADA" and TP203<20 and SW203=="ON")
		{
			bomba3="ENCENDIDA";
			pantalla="ON";
		}
		
		ciclos=ciclos+1;
		tiempo=tiempo-1;
		goto inicio;
	}


	//Simulamos el caso 3.
	
	if(caso==3)
	{
		
		//Validamos si se cumple el tiempo de rotaci�n, para rotar las bombas (Caso en el que las 3 bombas no presentan fallas).
		
		if(rotacion==ciclos and v_succ102=="ABIERTA" and TP202<50)
		{
			bomba3="APAGADA";
			caudal3=0;
			caudal3_seg=0;
			bomba2="ENCENDIDA";
			ciclos=0;
			pantalla="ON";
			goto repetir;
		}
		
		//En caso de que la bomba 2 tenga una presi�n mayor a 50 psi, o no el Switch de flujo= OFF, hacemos la rotacion con las 2 bombas operativas.
		
		//Cuando el programa detecta que la bomba 2 tiene una falla(presi�n>50 o Switch de flujo= OFF), se apaga directamente la bomba 3.
		
		//Rotaci�n a la bomba 1.
		
		if(TP202>50 or SW202=="OFF")
		{
			bomba3="APAGADA";
			caudal3=0;
			caudal3_seg=0;
			ciclos=0;
			pantalla="ON";
			goto repetir;
		}
		
		if(ciclos>rotacion)
		{
			ciclos=0;
		}
		
		
		//Simulaci�n del Switch de flujo (SW201) de la bomba 1 
	
		if(SW201=="OFF" and v_succ101=="ABIERTA")
		{
			SW201="ON";
			pantalla="ON";
		}
	
		if(SW201=="ON" and v_succ101=="CERRADA")
		{
			SW201="OFF";
			pantalla="ON";
		}
		
		//Simulaci�n del Switch de flujo (SW203) de la bomba 3 
	
		if(SW203=="OFF" and v_succ103=="ABIERTA")
		{
			SW203="ON";
			pantalla="ON";
		}
	
		if(SW203=="ON" and v_succ103=="CERRADA")
		{
			SW203="OFF";
			pantalla="ON";
		}
	
	
		//Simulaci�n de presi�n (TP201) de la bomba 1.
	
		if(bomba1=="ENCENDIDA" and v_desc201=="ABIERTA")
		{
			if(TP201<33)
			{
				TP201=TP201+1;
				pantalla="ON";
			}
		
			if(TP201>33)
			{
				TP201=TP201-1;
				pantalla="ON";
			}
		}
	
		if(bomba1=="ENCENDIDA" and v_desc201=="CERRADA" and TP201<=50)
		{
			TP201=TP201+1;
			pantalla="ON";
		}	
	
		if(bomba1=="APAGADA" and v_desc201=="ABIERTA")
		{
			TP201=TP201-1;
			pantalla="ON";
		}
		
		
		//Simulaci�n de presi�n (TP203) de la bomba 3.
	
		if(bomba3=="ENCENDIDA" and v_desc203=="ABIERTA")
		{
			if(TP203<33)
			{
				TP203=TP203+1;
				pantalla="ON";
			}
		
			if(TP203>33)
			{
				TP203=TP203-1;
				pantalla="ON";
			}
		}
	
		if(bomba3=="ENCENDIDA" and v_desc203=="CERRADA" and TP203<=50)
		{
			TP203=TP203+1;
			pantalla="ON";
		}
	
		if(bomba3=="APAGADA" and v_desc203=="ABIERTA")
		{
			TP203=TP203-1;
			pantalla="ON";
		}
		
		//Cuando se produce la rotaci�n, cuando la bomba 2 se apaga, y se tiene la v�lvula de descarga abierta, la presi�n disminuye a cero y el caudal cae a 0.
	
		if(bomba2=="APAGADA" and v_desc202=="ABIERTA")
		{
			TP202=TP202-1;
			caudal2=0;
			caudal2_seg=0;
			pantalla="ON";
		}
		
		//Validamos que la presi�n no sea negativa.
		
		if(TP201<0)
		{
			TP201=0;
		}
		
		if(TP202<0)
		{
			TP202=0;
		}
		
		if(TP203<0)
		{
			TP203=0;
		}
		
		
		//Simulaci�n del caudal de la bomba 1.
	
		if(bomba1=="ENCENDIDA" and v_succ101=="ABIERTA" and v_desc201=="ABIERTA")
		{
			caudal1=40;
			caudal1_seg=caudal1/60;
			pantalla="ON";
		}
	
		else
		{
			caudal1=0;
			caudal1_seg=0;
			pantalla="ON";
		}
		
		
		//Simulaci�n del caudal de la bomba 3.
	
		if(bomba3=="ENCENDIDA" and v_succ103=="ABIERTA" and v_desc203=="ABIERTA")
		{
			caudal3=40;
			caudal3_seg=caudal3/60;
			pantalla="ON";
		}	
	
		else
		{
			caudal3=0;
			caudal3_seg=0;
			pantalla="ON";
		}
	
	
		//Sumas de lo acumulado en las bombas operatvas.
	
		galones_acum=galones_acum+caudal1_seg+caudal3_seg;
	
	
		
		//Simulaci�n del encendido/apagado de la bomba 1.
	
		if(bomba1=="ENCENDIDA" and TP201>50)
		{
			bomba1="APAGADA";
			caudal1_seg=0;
			
				if(TP202<50 and SW202=="ON")
			{
				bomba2="ENCENDIDA";	
			}
			
			pantalla="ON";
		}
	
		if(bomba1=="APAGADA" and TP201<20 and SW201=="ON")
		{
			bomba1="ENCENDIDA";
			pantalla="ON";
		}
		
		
		//Simulaci�n del encendido/apagado de la bomba 3.
	
		if(bomba3=="ENCENDIDA" and TP203>50)
		{
			bomba3="APAGADA";
			caudal3_seg=0;
			
				if(TP202<50 and SW202=="ON")
			{
				bomba2="ENCENDIDA";	
			}
			
			pantalla="ON";
		}
	
		if(bomba3=="APAGADA" and TP203<20 and SW203=="ON" and ciclos!=0)
		{
			bomba3="ENCENDIDA";
			pantalla="ON";
		}
	
		ciclos=ciclos+1;
		tiempo=tiempo-1;
		goto inicio;
	}
	



	//Simulamos el caso de que solo la bomba 1 est� prendida.
	
	if(caso_1encendida==1)
	{	
		//Rotaci�n a la bomba 2.
	
		if(rotacion==ciclos and TP202<50)
		{
			if(v_succ102=="ABIERTA")
			{
				bomba1="APAGADA";
				caudal1=0;
				caudal1_seg=0;
				bomba2="ENCENDIDA";
				ciclos=0;
				pantalla="ON";
				goto repetir;
			}
		}
		
		//Rotaci�n a la bomba 3.
	
		if(rotacion==ciclos and TP203<50)
		{
			if(v_succ103=="ABIERTA")
			{
				bomba1="APAGADA";
				caudal1=0;
				caudal1_seg=0;
				bomba3="ENCENDIDA";
				ciclos=0;
				pantalla="ON";
				goto repetir;	
			}
		}
		
		
		
		//Simulaci�n del Switch de flujo (SW201) de la bomba 1 
	
		if(SW201=="OFF" and v_succ101=="ABIERTA")
		{
			SW201="ON";
			pantalla="ON";
		}
	
		if(SW201=="ON" and v_succ101=="CERRADA")
		{
			SW201="OFF";
			pantalla="ON";
		}
		
		
		//Simulaci�n de presi�n (TP201) de la bomba 1.
	
		if(bomba1=="ENCENDIDA" and v_desc201=="ABIERTA")
		{
			if(TP201<33)
			{
				TP201=TP201+1;
				pantalla="ON";
			}
		
			if(TP201>33)
			{
				TP201=TP201-1;
				pantalla="ON";
			}
		}
	
		if(bomba1=="ENCENDIDA" and v_desc201=="CERRADA")
		{
			TP201=TP201+1;
			pantalla="ON";
		}
	
		if(bomba1=="APAGADA" and v_desc201=="ABIERTA")
		{
			TP201=TP201-1;
			pantalla="ON";
		}
		
		//En caso de que las otras dos bombas se encuentren apagadas y con sus v�lvulas de descarga abiertas, la presi�n disminuye.
		
		if(bomba2=="APAGADA" and v_desc202=="ABIERTA")
		{
			TP202=TP202-1;
			pantalla="ON";
		}
		
		if(bomba3=="APAGADA" and v_desc203=="ABIERTA")
		{
			TP203=TP203-1;
			pantalla="ON";
		}
		
		//Validamos que la presi�n no sea negativa.
		
		if(TP201<0)
		{
			TP201=0;
		}
		
		if(TP202<0)
		{
			TP202=0;
		}
		
		if(TP203<0)
		{
			TP203=0;
		}
		
		//Simulaci�n del caudal de la bomba 1.
	
		if(bomba1=="ENCENDIDA" and v_succ101=="ABIERTA" and v_desc201=="ABIERTA")
		{
			caudal1=40;
			caudal1_seg=caudal1/60;
			pantalla="ON";
		}
	
		else
		{
			caudal1=0;
			caudal1_seg=0;
			pantalla="ON";
		}
		
		//Sumas de lo acumulado en las bombas operatvas.
	
		galones_acum=galones_acum+caudal1_seg;
		
		
		//Simulaci�n del encendido/apagado de la bomba 1.
	
		if(bomba1=="ENCENDIDA" and TP201>50)
		{
			bomba1="APAGADA";
			caudal1_seg=0;
			pantalla="ON";
		}
	
		if(bomba1=="APAGADA" and TP201<20 and SW201=="ON" and ciclos!=0)
		{
			bomba1="ENCENDIDA";
			pantalla="ON";
		}
		
		//En caso de que la bomba 1 se apague por superar la presi�n de 50 psi, si las otras bombas se encuentran operativas, se prender�n autom�ticamente si sus presiones son iferiores a 20 psi y si Switch de flujo= ON.
		
		if(bomba1=="APAGADA" and TP201>50)
		{
			//Prendemos la bomba 2.
			
			if(bomba2=="APAGADA" and TP202<50 and SW202=="ON")
			{
				bomba2="ENCENDIDA";
			}
			
			//Prendemos la bomba 3.
			
			if(bomba3=="APAGADA" and TP203<50 and SW203=="ON")
			{
				bomba3="ENCENDIDA";	
			}
		}
		
		//Cuando se recuperan las bombas, vuelven a prenderse (Presi�n<20 y Switch de flujo= OFF).
		
		
		if(bomba2=="APAGADA" and TP202<20 and SW202=="ON")
		{
			bomba2="ENCENDIDA";
			pantalla="ON";
			
		}
		
		if(bomba3=="APAGADA" and TP203<20 and SW203=="ON")
		{
			bomba3="ENCENDIDA";
			pantalla="ON";
		}
		
		
		
		
		ciclos=ciclos+1;		
		tiempo=tiempo-1;
		lector=1;
		goto inicio;
		
	}

	
	//Simulamos el caso de que solo la bomba 2 est� prendida.
	
	if(caso_1encendida==2)
	{
		
		//Rotaci�n a la bomba 1.
	
		if(rotacion==ciclos and TP201<50)
		{
			if(v_succ101=="ABIERTA")
			{
				bomba2="APAGADA";
				caudal2=0;
				caudal2_seg=0;
				bomba1="ENCENDIDA";
				ciclos=0;
				pantalla="ON";
				goto repetir;	
			}
		}
		
		//Rotaci�n a la bomba 3.
	
		if(rotacion==ciclos and TP203<50)
		{
			if(v_succ103=="ABIERTA")
			{
				bomba2="APAGADA";
				caudal2=0;
				caudal2_seg=0;
				bomba3="ENCENDIDA";
				ciclos=0;
				pantalla="ON";
				goto repetir;	
			}
		}
		
		
		//Simulaci�n del Switch de flujo (SW202) de la bomba 2 
	
		if(SW202=="OFF" and v_succ102=="ABIERTA")
		{
			SW202="ON";
			pantalla="ON";
		}
	
		if(SW202=="ON" and v_succ102=="CERRADA")
		{
			SW202="OFF";
			pantalla="ON";
		}
		
		
		//Simulaci�n de presi�n (TP202) de la bomba 2.
	
		if(bomba2=="ENCENDIDA" and v_desc202=="ABIERTA")
		{
			if(TP202<33)
			{
				TP202=TP202+1;
				pantalla="ON";
			}
		
			if(TP202>33)
			{
				TP202=TP202-1;
				pantalla="ON";
			}
		}
	
		if(bomba2=="ENCENDIDA" and v_desc202=="CERRADA")
		{
			TP202=TP202+1;
			pantalla="ON";
		}
	
		if(bomba2=="APAGADA" and v_desc202=="ABIERTA")
		{
			TP202=TP202-1;
			pantalla="ON";
		}
		
		//En caso de que las otras dos bombas se encuentren apagadas y con sus v�lvulas de descarga abiertas, la presi�n disminuye.
		
		if(bomba1=="APAGADA" and v_desc201=="ABIERTA")
		{
			TP201=TP201-1;
			pantalla="ON";
		}
		
		if(bomba3=="APAGADA" and v_desc203=="ABIERTA")
		{
			TP203=TP203-1;
			pantalla="ON";
		}
		
		//Validamos que la presi�n no sea negativa.
		
		if(TP201<0)
		{
			TP201=0;
		}
		
		if(TP202<0)
		{
			TP202=0;
		}
		
		if(TP203<0)
		{
			TP203=0;
		}
		
		
		 //Simulaci�n del caudal de la bomba 2.
	
		if(bomba2=="ENCENDIDA" and v_succ102=="ABIERTA" and v_desc202=="ABIERTA")
		{
			caudal2=40;
			caudal2_seg=caudal2/60;
			pantalla="ON";
		}	
	
			else
		{
			caudal2=0;
			caudal2_seg=0;
			pantalla="ON";
		}
		
		//Sumas de lo acumulado en las bombas operatvas.
	
		galones_acum=galones_acum+caudal2_seg;
		
		
		//Simulaci�n del encendido/apagado de la bomba 2.
	
		if(bomba2=="ENCENDIDA" and TP202>50)
		{
			bomba2="APAGADA";
			caudal2_seg=0;
			pantalla="ON";
		}
	
		if(bomba2=="APAGADA" and TP202<20 and SW202=="ON" and ciclos!=0)
		{
			bomba2="ENCENDIDA";
			pantalla="ON";
		}
		
		//En caso de que la bomba 2 se apague por superar la presi�n de 50 psi, si las otras bombas se encuentran operativas, se prender�n autom�ticamente si sus presiones son iferiores a 20 psi y si Switch de flujo= ON.
		
		if(bomba2=="APAGADA" and TP202>50)
		{
			//Prendemos la bomba 1.
			
			if(bomba1=="APAGADA" and TP201<50 and SW201=="ON")
			{
				bomba1="ENCENDIDA";
			}
			
			//Prendemos la bomba 3.
			
			if(bomba3=="APAGADA" and TP203<50 and SW203=="ON")
			{
				bomba3="ENCENDIDA";
			}
		}
		
		//Cuando se recuperan las bombas, vuelven a prenderse (Presi�n<20 y Switch de flujo= OFF).
		
		
		if(bomba1=="APAGADA" and TP201<20 and SW201=="ON")
		{
			bomba1="ENCENDIDA";
			pantalla="ON";
			
		}
		
		if(bomba3=="APAGADA" and TP203<20 and SW203=="ON")
		{
			bomba3="ENCENDIDA";
			pantalla="ON";
		}
		
		ciclos=ciclos+1;
		tiempo=tiempo-1;
		lector=1;
		goto inicio;
	}

	
	
	//Simulamos el caso de que solo la bomba 3 est� prendida.
	
	if(caso_1encendida==3)
	{
		
		//Rotaci�n a la bomba 1.
	
		if(rotacion==ciclos and TP201<50)
		{
			if(v_succ101=="ABIERTA")
			{
				bomba3="APAGADA";
				caudal3=0;
				caudal3_seg=0;
				bomba1="ENCENDIDA";
				ciclos=0;
				pantalla="ON";
				goto repetir;	
			}
		}
		
		//Rotaci�n a la bomba 2.
	
		if(rotacion==ciclos and TP202<50)
		{
			if(v_succ102=="ABIERTA")
			{
				bomba3="APAGADA";
				caudal3=0;
				caudal3_seg=0;
				bomba2="ENCENDIDA";
				ciclos=0;
				pantalla="ON";
				goto repetir;	
			}
		}
		
		
		
		
		//Simulaci�n del Switch de flujo (SW203) de la bomba 3 
	
		if(SW203=="OFF" and v_succ103=="ABIERTA")
		{
			SW203="ON";
			pantalla="ON";
		}
	
		if(SW203=="ON" and v_succ103=="CERRADA")
		{
			SW203="OFF";
			pantalla="ON";
		}
		
		
		//Simulaci�n de presi�n (TP203) de la bomba 3.
	
		if(bomba3=="ENCENDIDA" and v_desc203=="ABIERTA")
		{
			if(TP203<33)
			{
				TP203=TP203+1;
				pantalla="ON";
			}
		
			if(TP203>33)
			{
				TP203=TP203-1;
				pantalla="ON";
			}
		}
	
		if(bomba3=="ENCENDIDA" and v_desc203=="CERRADA")
		{
			TP203=TP203+1;
			pantalla="ON";
		}
	
		if(bomba3=="APAGADA" and v_desc203=="ABIERTA")
		{
			TP203=TP203-1;
			pantalla="ON";
		}
		
		//En caso de que las otras dos bombas se encuentren apagadas y con sus v�lvulas de descarga abiertas, la presi�n disminuye.
		
		if(bomba1=="APAGADA" and v_desc201=="ABIERTA")
		{
			TP201=TP201-1;
			pantalla="ON";
		}
		
		if(bomba2=="APAGADA" and v_desc202=="ABIERTA")
		{
			TP202=TP202-1;
			pantalla="ON";
		}
		
		//Validamos que la presi�n no sea negativa.
		
		if(TP201<0)
		{
			TP201=0;
		}
		
		if(TP202<0)
		{
			TP202=0;
		}
		
		if(TP203<0)
		{
			TP203=0;
		}
		
		
		//Simulaci�n del caudal de la bomba 3.
	
		if(bomba3=="ENCENDIDA" and v_succ103=="ABIERTA" and v_desc203=="ABIERTA")
		{
			caudal3=40;
			caudal3_seg=caudal3/60;
			pantalla="ON";
		}	
	
		else
		{
			caudal3=0;
			caudal3_seg=0;
			pantalla="ON";
		}
	
	
		//Sumas de lo acumulado en las bombas operatvas.
	
		galones_acum=galones_acum+caudal3_seg;
		
		
		//Simulaci�n del encendido/apagado de la bomba 3.
	
		if(bomba3=="ENCENDIDA" and TP203>50)
		{
			bomba3="APAGADA";
			caudal3_seg=0;
			pantalla="ON";
		}
	
		if(bomba3=="APAGADA" and TP203<20 and SW203=="ON" and ciclos!=0)
		{
			bomba3="ENCENDIDA";
			pantalla="ON";
		}
		
		//En caso de que la bomba 3 se apague por superar la presi�n de 50 psi, si las otras bombas se encuentran operativas, se prender�n autom�ticamente si sus presiones son iferiores a 20 psi y si Switch de flujo= ON.
		
		if(bomba3=="APAGADA" and TP203>50)
		{
			//Prendemos la bomba 1.
			
			if(bomba1=="APAGADA" and TP201<50 and SW201=="ON")
			{
				bomba1="ENCENDIDA";
				pantalla="ON";
			}
			
			//Prendemos la bomba 2.
			
			if(bomba2=="APAGADA" and TP202<50 and SW202=="ON")
			{
				bomba2="ENCENDIDA";
				pantalla="ON";
			}
		}
		
		
		//Cuando se recuperan las bombas, vuelven a prenderse (Presi�n<20 y Switch de flujo= OFF).
		
		
		if(bomba1=="APAGADA" and TP201<20 and SW201=="ON")
		{
			bomba1="ENCENDIDA";
			pantalla="ON";
			
		}
		
		if(bomba2=="APAGADA" and TP202<20 and SW202=="ON")
		{
			bomba2="ENCENDIDA";
			pantalla="ON";
			
		}

		ciclos=ciclos+1;
		tiempo=tiempo-1;
		lector=1;
		goto inicio;
	}
	
	
	//Simulamos el caso especial en el que las 3 bombas se apaguen por superar los 50 psi o por tener el Switch de flujo= OFF

	if(caso_apagadas=1)
	{
		//Simulamos las presiones de las 3 bombas apagadas.
		
		if(bomba1=="APAGADA" and v_desc201=="ABIERTA" and TP201>0)
		{
			TP201=TP201-1;
			pantalla="ON";
		}
		
		if(bomba2=="APAGADA" and v_desc202=="ABIERTA" and TP202>0)
		{
			TP202=TP202-1;
			pantalla="ON";
		}
		
		if(bomba3=="APAGADA" and v_desc203=="ABIERTA" and TP203>0)
		{
			TP203=TP203-1;
			pantalla="ON";
		}
		
		//Simulamos el caso en el que una de las 3 bombas llegue a estar por debajo de los 20 psi, para poder prenderla.
		
		if(bomba1=="APAGADA" and TP201<20 and SW201=="ON")
		{
			bomba1="ENCENDIDA";
			pantalla="ON";
			goto inicio;
		}		
		
		if(bomba2=="APAGADA" and TP202<20 and SW202=="ON")
		{
			bomba2="ENCENDIDA";
			goto inicio;
		}
		
		if(bomba3=="APAGADA" and TP203<20 and SW203=="ON")
		{
			bomba3="ENCENDIDA";
			pantalla="ON";
			lector=1;
			goto inicio;
		}

	}
		
	goto inicio;
}	
