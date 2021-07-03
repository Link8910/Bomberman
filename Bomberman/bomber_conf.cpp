#include "game.h"
#include <conio.h>
#include <iostream>

using namespace std;


Jugador::Jugador()
	{
		alcance = 5;//2-0;3-1;4-2
		vida = false;
		_flama = false;
		contador_bomba = 0;
		contador_flama = 0;
		bomba_activado = false;

		p_coord[0] = 0;
		p_coord[1] = 0;
		b_coord[0] = 0;
		b_coord[1] = 0;

	}
	
	
char Jugador::colocar_posiciones(char a[18][39])
	{
		if (a[p_coord[0]][p_coord[1]] == 'x') vida = false;
		if (p_coord[0] == b_coord[0] and p_coord[1] == b_coord[1] and bomba_activado == true)
		{
			a[p_coord[0]][p_coord[1]] = '8';

		}

		else
		{
			a[p_coord[0]][p_coord[1]] = '*';

		}
}

char Jugador::borrar_posiciones(char a[18][39])
	{
		if (a[p_coord[0]][p_coord[1]] == '8' and bomba_activado == true)
		{
			a[p_coord[0]][p_coord[1]] = 'O';

		}

		else
		{
			a[p_coord[0]][p_coord[1]] = 176;

		}
	}
	
char Jugador::colocar_bomba()
	{
		b_coord[0] = p_coord[0];
		b_coord[1] = p_coord[1];
	}
	
bool Jugador::pasos(int p_y, int p_x, int coordenadas[24][6][2])
	{
		for (int i = 0; i < 24; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				if (coordenadas[i][j][0] == p_x and coordenadas[i][j][1] == p_y)

					return false;


				if (p_y == -1 or p_y == 18 or p_x == -1 or p_x == 39)
					return false;

			}
		}
		return true;
	}
	
	
int Jugador::flama(char a[18][39], int coordenadas[24][6][2])

	{

		if (contador_flama == 1)
		{
			bool up = true;
			bool down = true;
			bool right = true;
			bool left = true;
			for (int i; i < alcance; i++)
			{
				if (pasos(b_coord[0] + i, b_coord[1], coordenadas) == false)
				{
					down = false;
				}
				if (down == true and pasos(b_coord[0] + i, b_coord[1], coordenadas) == true)
				{
					a[b_coord[0] + i][b_coord[1]] = 'x';
				}



				if (pasos(b_coord[0] - i, b_coord[1], coordenadas) == false)
				{
					up = false;
				}
				if (up == true and pasos(b_coord[0] - i, b_coord[1], coordenadas) == true)
				{
					a[b_coord[0] - i][b_coord[1]] = 'x';
				}


				if (pasos(b_coord[0], b_coord[1] - i, coordenadas) == false)
				{
					left = false;
				}
				if (left == true and pasos(b_coord[0], b_coord[1] - i, coordenadas) == true)
				{
					a[b_coord[0]][b_coord[1] - i] = 'x';
				}



				if (pasos(b_coord[0], b_coord[1] + i, coordenadas) == false)
				{
					right = false;
				}
				if (right == true and pasos(b_coord[0], b_coord[1] + i, coordenadas) == true)
				{
					a[b_coord[0]][b_coord[1] + i] = 'x';
				}



			}

		}


		if (contador_flama >= 7)
		{
			for (int i = 0; i < alcance ; i++)//
			{
				if (pasos(temp_b_coord[0], temp_b_coord[1] + i, coordenadas) == false) break;

				if (pasos(temp_b_coord[0], temp_b_coord[1] + i, coordenadas) == true) a[temp_b_coord[0]][temp_b_coord[1] + i] = 176;

			}
			for (int i = 0; i < alcance ; i++)//
			{

				if (pasos(temp_b_coord[0], temp_b_coord[1] - i, coordenadas) == false) break;

				if (pasos(temp_b_coord[0], temp_b_coord[1] - i, coordenadas) == true) a[temp_b_coord[0]][temp_b_coord[1] - i] = 176;

			}
			for (int i = 0; i < alcance; i++)
			{

				if (pasos(temp_b_coord[0] - i, temp_b_coord[1], coordenadas) == false) break;

				if (pasos(temp_b_coord[0] - i, temp_b_coord[1], coordenadas) == true) a[temp_b_coord[0] - i][temp_b_coord[1]] = 176;

			}
			for (int i = 0; i < alcance; i++)
			{

				if (pasos(temp_b_coord[0] + i, temp_b_coord[1], coordenadas) == false) break;

				if (pasos(temp_b_coord[0] + i, temp_b_coord[1], coordenadas) == true) a[temp_b_coord[0] + i][temp_b_coord[1]] = 176;

			}

			contador_flama = 0;

			_flama = false;
		}

	}
	
	
char Jugador::Bomba_explosion(char a[18][39], int coordenadas[24][6][2])
	{

		if (bomba_activado == true)
		{
			contador_bomba++;

			if (contador_bomba == 20)//5 con sleep; 20 sin sleep.
			{
				a[b_coord[0]][b_coord[1]] = 176;

				_flama = true;
				bomba_activado = false;

				contador_bomba = 0;
			}
		}


		if (_flama)
		{
			if (contador_flama == 0)
			{
				temp_b_coord[0] = b_coord[0];
				temp_b_coord[1] = b_coord[1];
			}

			contador_flama++;
			flama(a, coordenadas);
		}
	}


char Jugador::muerto(char a[18][39], int x, int y)
	{
		if (a[x][y] == 'x' or a[x][y] == 'ç')
		{
			vida = false;
		}
	}
	
char Jugador::entrada_p(char a[18][39], int coordenadas[24][6][2])
	{
		
		if (kbhit())
		{
			borrar_posiciones(a);
			char tecla = getch();
			if (tecla == 'a')
				p_coord[1]--;
			if (pasos(p_coord[0], p_coord[1], coordenadas) == false)
			{
				p_coord[1]++;
			}
			if (tecla == 'd')
				p_coord[1]++;
			if (pasos(p_coord[0], p_coord[1], coordenadas) == false)
			{
				p_coord[1]--;
			}
			if (tecla == 'w')
				p_coord[0]--;
			if (pasos(p_coord[0], p_coord[1], coordenadas) == false)
			{
				p_coord[0]++;
			}
			if (tecla == 's')
				p_coord[0]++;
			if (pasos(p_coord[0], p_coord[1], coordenadas) == false)
			{
				p_coord[0]--;
			}
			if (bomba_activado == false and tecla == ' ')
			{
				bomba_activado = true;
				colocar_bomba();
			}

			colocar_posiciones(a);
		}
		Bomba_explosion(a, coordenadas);
		muerto(a, p_coord[0], p_coord[1]);


	}
	
Mapa::Mapa()
{
	segundos = 75;
	contador = 0;
}	
void Mapa::reloj(bool &vida)
	{		
		int minutos = segundos /60;	
		if (contador %10 == 0)
		{
			segundos--;
		}
		if (segundos%60 > 9)   cout<<"\t"<<minutos<<":"<<segundos%60<<endl;
		else cout<<"\t"<<minutos<<":"<<"0"<<segundos%60<<endl;	
		contador ++;
		if (minutos == 0 and segundos == 0) (vida ) = false;
	}
char Mapa::crear_mapa()
	{
		int x[3] = { 3,4,5 };
		int y[2] = { 2,3 };
		int indice_x = 0;

		for (int i = 0; i < 18; i++)
		{
			for (int j = 0; j < 39; j++)
			{
				a[i][j] = 176;
			}
		}
		for (int i = 0; i < 24; i++)
		{

			for (int j = 0; j < 6; j++)
			{
				if (j < 3)
				{
					coordenadas[i][j][0] = x[indice_x];
					coordenadas[i][j][1] = y[0];
					a[coordenadas[i][j][1]][coordenadas[i][j][0]] = 219;

				}
				if (j >= 3)
				{
					coordenadas[i][j][0] = x[indice_x];
					coordenadas[i][j][1] = y[1];
					a[coordenadas[i][j][1]][coordenadas[i][j][0]] = 219;
				}
				indice_x++;
				if (indice_x >= 3)
				{
					indice_x = 0;
				}

			}
			x[0] = x[0] + 6; x[1] = x[1] + 6; x[2] = x[2] + 6;
			if (i == 5 or i == 11 or i == 17 or i == 23)
			{
				x[0] = 3; x[1] = 4; x[2] = 5;
				y[0] = y[0] + 4; y[1] = y[1] + 4;
			}
		}
		
	}
	
	
void Mapa::imprime(bool &vida)
	{
		this->reloj(vida);
		for (int i =0 ; i < 1; i++)
		{
			cout<<"\t";
			for (int j = 0; j <43;j++)
			{
				cout<<(char)219;
			}
			cout<<endl;
		}
		
		for (int alto = 0; alto < 18; alto++)
		{
			cout<<"\t";
			for (int ancho = 0; ancho < 39; ancho++)
			{
				if (ancho== 0) cout <<char(219)<<char(219) <<a[alto][ancho];
				else if (ancho== 38)cout  <<a[alto][ancho]<<char(219)<<char(219);
				else cout << a[alto][ancho];
			}
			cout << endl;
		}
		for (int i =0 ; i < 1; i++)
		{
			cout<<"\t";
			for (int j = 0; j <43;j++)
			{
				cout<<(char)219;
			}
			cout<<endl;
		}
	}

void Mapa::sleep(int a)
	{
		for (int i = 0; i < (4500) / a; i++)
		{
			for (int j = 0; j < 100000; j++);

		}
	}
void Mapa::imprimir_coordenas_fijas()
	{
		for (int i = 0; i < 24; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				cout << coordenadas[i][j][0] << "    " << coordenadas[i][j][1] << endl;
			}
		}
	}
	
Enemigo::Enemigo(int x, int y, int cansancio, int velocidad, int energia)
	{
		vida = true;

		temp_velocidad = 0;
		e_coord[0] = x;//16
		e_coord[1] = y;//37
		this->velocidad = velocidad;
		this->cansancio = cansancio;
		this->energia = energia;
	}

char Enemigo::seguir_player(int x, int y, int coordenadas[24][6][2])
	{

		if (temp_velocidad == velocidad) //Con sleep 1, sin sleep 3
		{

			if (e_coord[0] > x)
			{
				e_coord[0]--;
				if (pasos(e_coord[0], e_coord[1], coordenadas) == false) e_coord[0]++;
			}
			if (e_coord[1] > y)
			{
				e_coord[1]--;
				if (pasos(e_coord[0], e_coord[1], coordenadas) == false) e_coord[1]++;
			}
			if (e_coord[0] < x)
			{
				e_coord[0]++;
				if (pasos(e_coord[0], e_coord[1], coordenadas) == false) e_coord[0]--;
			}

			if (e_coord[1] < y)
			{
				e_coord[1]++;
				if (pasos(e_coord[0], e_coord[1], coordenadas) == false) e_coord[1]--;
			}
			temp_velocidad = 0;
		}
	}

char Enemigo::muerto(char a[18][39], int x, int y)
	{
		if (a[x][y] == 'x')
		{
			vida = false;
		}
	}
	
char Enemigo::colocar_enemigo(char a[18][39], int coordenadas[24][6][2], int x, int y)
	{
		if (vida == true)
		{
			if (cansancio < energia)
			{

				if (a[e_coord[0]][e_coord[1]] == 'O') a[e_coord[0]][e_coord[1]] = 'O';
				if (a[e_coord[0]][e_coord[1]] == 'x') a[e_coord[0]][e_coord[1]] = 'x';
				else a[e_coord[0]][e_coord[1]] = 176;

				seguir_player(x, y, coordenadas);
				temp_velocidad++;
				muerto(a, e_coord[0], e_coord[1]);

				if (a[e_coord[0]][e_coord[1]] == 'O') a[e_coord[0]][e_coord[1]] = 'O';
				if (a[e_coord[0]][e_coord[1]] == 'x') a[e_coord[0]][e_coord[1]] = 'x';
				else a[e_coord[0]][e_coord[1]] = 'ç';


			}
			if (cansancio == 30) cansancio = 0;

			cansancio++;
		}
	}

bool Menu::menuPri(){
		bool ingame = true;
		while(ingame){
			system("cls");
		
		cout << "      ____   " << endl;	
		cout << "     /   )                /                                  " << endl;
		cout << "    /__ /-----__---_--_---/__----__---__--- _--_----__----__-    " << endl;
		cout << "   /    )   /   ) / /  ) /   ) /___) /   ) / /  ) /   ) /   )" << endl;
		cout << "  /____/   (___/ / /  / (___/ (___  /     / /  / (___( /   /   " << endl;
	
		
		
		cout << endl;
		cout << "\t\t\t 1. Jugar" << endl;
		cout << "\t\t\t 2. Opciones" << endl;
		cout << "\t\t\t 3. About" << endl;
		cout << "\t\t\t 4. Salir" << endl;
		cout << "\t\t      ¿Que desea hacer? " ;cin >> choice;
		switch (choice) {
			case 1:
				return true;
				break;
			case 2:
				menuOp();
				break;	
				
			case 3:
				menuAb();
				break;
			case 4:
				ingame = false;
				return false;
				break;
			default:
			cout << "Opcion fuera de rango";
			break;
		}
	}
}

void Menu::menuOp(){
	system("cls");
	cout << "Esta opcion sera implementada en el juego completo..." << endl;
			cout << "\nPatch 1.89..." << endl << "Volumen\n" << "Controles\n ";
			system("pause>nul");
}

void Menu::menuAb(){
	system("cls");
	cout << "          Hecho por: " << endl;
				cout << "\n      Alfredo Fernando Turpo Huillcara " << endl << "      Justo Alfredo Perez Choque" << endl << "      Josue Miguel Sebastian Castro Palomino";
				system("pause>nul");
}

void Menu::perdiste(){
	cout<< " *********** \n";
	cout<<"** Perdiste **" << endl;
	cout<< " *********** \n";
	
	
}

void Menu::Fin_del_juego()
{
	cout<<"    _____                        "<<endl;    
	cout<<"    /    '   ,                /         /   "<<endl;
	cout<<"   /__           __       __ /    __   /"<<endl;
	cout<<"  /        /   /   )     /   /   /___) /      "<<endl;
	cout<<"_/________/___/___/_____(___/___(___ _/______"<<endl;
	cout<<"                                             "<<endl;
	cout<<"                                             "<<endl;
	cout<<"       ,                         "<<endl;
	cout<<"      /   /   /  /___) /   ) /   )"<<endl;
	cout<<" ____/___(___(__(___ _(___/_(___/_"<<endl;
	cout<<"    /                    /       "<<endl; 
	cout<<"(_ /                 (_ /   "<<endl;
}



