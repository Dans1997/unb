#include <bits/stdc++.h>

using namespace std;

string defaultStr = "";

struct Sector { 
	unsigned char byte[512]; // 512 bytes/sector
}; 

struct Cluster {
	Sector sector[4]; // 4 sector/cluster
};

struct Track { 
	Sector sector[60];  // 60 sector/track
}; 

struct Cylinder { 
	Track track[5]; // 5 track/cylinder
};

struct HardDrive {
	const int minSeek = 1; // minimum seek time: 1ms  
	const int medSeek = 4; // seek time: 4ms
	const int medLat = 6; // latency time: 6ms
	const int medTrans = 12; // transference time: 12ms 

	Cylinder cylinder[10]; // 10 cylinders
};

struct FATList {
	char filename[100];
	unsigned int first_sector;
};

struct FATEnt {
	unsigned int used;
	unsigned int eof;
	unsigned int next;
};

int get_option () {
	int tmp;
	printf("> ");
	scanf(" %d", &tmp);
	return tmp;
}

void clear_screen () {
	system("clear || cls");
}

void print_menu () {
	printf("1 - Escrever Arquivo\n");
	printf("2 - Ler Arquivo\n");
	printf("3 - Apagar Arquivo\n");
	printf("4 - Mostrar Tabela FAT\n");
	printf("5 - Sair\n");
}

void print_error_message (string msg, bool* error) {
	if (*error == true) {
		*error = false;
		printf("\033[1;31m %s \033[0m", msg.c_str()); 
	}
}

void print_continue () {}

string get_filename () {
	auto msg = "Nome de arquivo inválido ou muito grande";
	auto tmp_invalid = false;
	auto tmp = defaultStr;
	auto error = false;

	do {
		getchar();
		clear_screen();
		print_error_message(msg, &error);
		printf("Digite o nome do arquivo .txt:\n");
		printf(" - Não digite a extensão.\n");
		printf(" - Nome tem que ser alpha-numérico.\n");
		printf(" - Máximo de 100 caracteres.\n");
		printf("> ");
		scanf(" %[^\n]", &tmp);

		auto isAlphaNum = count_if(begin(tmp), end(tmp), [](char c){ return !(isalnum(c));}) == -1;

		if (not isAlphaNum or tmp.size() > 100) {
			tmp_invalid = error = true;
		}
	} while (tmp_invalid);

	return tmp + ".txt";
}

// vector<Cluster> get_clusters (ifstream* fs) {
// 	vector<Cluster> fcluster;
// 	return fcluster;
// }

void iniciate_writing () {
	auto error = false;
	auto msg = "Houve algum erro ao tentar manipular o arquivo, verifique se o mesmo se encontra na mesma pasta em que executou o programa.";
	auto filename = get_filename();

	try {
		ifstream fs;
		fs.open(filename, ios::binary);
		auto file_size = (int) fs.tellg();
		printf("file size: %d", file_size);
		fs.close();
	} catch (...) {
		error = true;
		print_error_message(msg, &error);
		print_continue();
	}
}

void iniciate_reading () {

}

void iniciate_erasing () {

}

void iniciate_show () {

}

int main () {
	auto msg    = "Número inválido";
	auto error  = false;
	auto option = 0;
	enum options {
		Write = 1,
		Read,
		Erase,
		Show_FAT,
		Leave
	};

	do {
		clear_screen();
		print_error_message(msg, &error);
		print_menu();
		option = get_option();

		switch (option) {
			case Write:
				iniciate_writing();
				break;
			case Read:
				iniciate_reading();
				break;
			case Erase:
				iniciate_erasing();
				break;
			case Show_FAT:
				iniciate_show();
				break;
			case Leave:
				break;
			default:
				error = true;
				break;
		}
	} while (option != Leave);
}