#include<iostream>
#include<conio.h>//Usando kbhit 
#include "game.h"
#include "bomber_conf.cpp"
using namespace std;


int main()
{
	system("title Bomberman uwu");
	Mapa mapa;
	Jugador p1; 
	Menu m1;
	
	
	Enemigo_simple *p_enemigo[4];
	p_enemigo[0] = new Enemigo_simple(16, 37, 19, 1, 15);//(x,y,casancio,velocidad,energia) velocidad(1 muy rapido,2 medio, 3 muy lento, 4 tortuga)
	p_enemigo[1] = new Enemigo_simple(2, 37, 10, 2, 20);
	p_enemigo[2] = new Enemigo_simple(16, 2, 0, 3, 20);
	p_enemigo[3] = new Enemigo_simple(9,18,2,2,20);
	Boss *p_boss[1];
	p_boss[0] = new Boss(16, 19,4);
	
	
	

	
	p1.vida = m1.menuPri();
	system("cls");
	while (p1.vida == true)
	{
		p_enemigo[0]->colocar_enemigo(mapa.a,mapa.coordenadas,p1.p_coord[0],p1.p_coord[1]);
		p_enemigo[1]->colocar_enemigo(mapa.a,mapa.coordenadas,p1.p_coord[0],p1.p_coord[1]);
		p_enemigo[2]->colocar_enemigo(mapa.a,mapa.coordenadas,p1.p_coord[0],p1.p_coord[1]);
		p_enemigo[3]->colocar_enemigo(mapa.a,mapa.coordenadas,p1.p_coord[0],p1.p_coord[1]);
		
		if (p_enemigo[0]->vida == false  &&  p_enemigo[1]->vida == false && p_enemigo[2]->vida == false && p_enemigo[3]->vida == false) 
		{
			p_boss[0]->boss_escena = true;
			p_boss[0]->colocar_enemigo(mapa.a,mapa.coordenadas,p1.p_coord[0],p1.p_coord[1]);
		}
		
		
		
		p1.entrada_p(mapa.a,mapa.coordenadas);				
		
		
		mapa.imprime(p1.vida,p_boss[0]->boss_escena,p_boss[0]->cantidad_vida);
		
		if (p1.vida == false) 
			{
				mapa.sleep(1);
				system("cls");
				
				m1.perdiste();
				mapa.sleep(1);
			}
		if (p_enemigo[0]->vida == false  &&  p_enemigo[1]->vida == false && p_enemigo[2]->vida == false && p_enemigo[3]->vida == false && p_boss[0]->vida == false && p1.vida == true) 
		{
			cout<<"ganaste!!!!!! C: uwuwuwuwu ";
			mapa.sleep(1);
			
			system("cls");
		}
		
		system("cls");
		
	}
	m1.Fin_del_juego();
	
		
return 0;
}

