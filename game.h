#ifndef GAME_H
#define GAME_H

class Menu{
	public:
		bool ingame ;
		int choice;
		bool menuPri();
		void menuOp();
		void menuAb();
		void perdiste();
		void Fin_del_juego();
};

class Jugador
{
public:
	bool vida;


	int alcance;
	int p_coord[2];
	int b_coord[2];
	int temp_b_coord[2];
	int contador_bomba;
	int contador_flama;
	bool _flama;
	bool bomba_activado;
	
	Jugador();
	char colocar_posiciones(char[18][39]);
	char borrar_posiciones(char[18][39]);
	char colocar_bomba();
	bool pasos(int, int ,int coordenadas [24][6][2]);
	int flama(char a[18][39], int coordenadas[24][6][2]);
	char Bomba_explosion(char a[18][39], int coordenadas[24][6][2]);
	char muerto(char a[18][39], int x, int y);
	char entrada_p(char a[18][39], int coordenadas[24][6][2]);
};

class Enemigo :public Jugador{


public:

	int e_coord[2];
	int temp_e_coord[2];
	int velocidad;
	int temp_velocidad;
	int cansancio;
	int energia;
	char seguir_player(int,int,int);
	Enemigo(int, int, int , int , int );
	char seguir_player(int x, int y, int coordenadas[24][6][2]);
	char muerto(char a[18][39], int , int );
	char colocar_enemigo(char a[18][39], int coordenadas[24][6][2], int , int );
};

class Mapa
{
public:
	char a[18][39];
	int coordenadas[24][6][2];
	int segundos;
	int contador;
	Mapa();
	void reloj(bool &);
	char crear_mapa();
	void imprime(bool &);
	void sleep(int a);
	void imprimir_coordenas_fijas();
};


#endif
