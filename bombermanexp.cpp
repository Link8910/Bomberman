#include<iostream>
#include<conio.h>//Usando kbhit 
#include "game.h"
#include "bomber_conf.cpp"
using namespace std;


int main()
{
	Mapa mapa;
	Jugador p1;
	Enemigo e1(16, 37, 19, 1, 15), e2(2, 37, 10, 2, 20), e3(16, 2, 0, 3, 20), e4(9,18,2,2,20);  //(x,y,casancio,velocidad,energia) velocidad(1 muy rapido,2 medio, 3 muy lento, 4 tortuga)
	mapa.crear_mapa();
	Menu m1;
	
	p1.vida = m1.menuPri();
	system("cls");
	while (p1.vida == true)
	{
		e1.colocar_enemigo(mapa.a,mapa.coordenadas,p1.p_coord[0],p1.p_coord[1]); 
		e2.colocar_enemigo(mapa.a,mapa.coordenadas,p1.p_coord[0],p1.p_coord[1]);
		e3.colocar_enemigo(mapa.a,mapa.coordenadas,p1.p_coord[0],p1.p_coord[1]);
		e4.colocar_enemigo(mapa.a,mapa.coordenadas,p1.p_coord[0],p1.p_coord[1]);
		p1.entrada_p(mapa.a,mapa.coordenadas);				
		mapa.imprime(p1.vida);
		//mapa.sleep(1);
		if (p1.vida == false) 
			{
				mapa.sleep(1);
				system("cls");
				
				m1.perdiste();
				mapa.sleep(1);
			}
		system("cls");
	}
	m1.Fin_del_juego();
	
		
return 0;
}

