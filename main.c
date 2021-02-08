/**************************

 Online C Compiler.
 Code, Compile, Run and Debug C program online.
 Write your code in this editor and press "Run" button to compile and execute it.

 ***************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void initializeTheBoard(char **, int, int);
void printScreen(char **, int, int);
void play(char **, int *);
int canMove(char **, int, int, int, int, int);
int pawnMove(char **, int, int, int, int, int);
int bishopMove(char **, int, int, int, int);
int knightMove(char **, int, int, int, int);
int rockMove(char **, int, int, int, int);
int queenMove(char **, int, int, int, int);
int kingMove(char **, int, int, int, int);
int destinationCheck(char, int);
int isGameOver(char **, int, int);

#define HEIGTH 8
#define WIDTH 8

int main() {
	char **arr;
	int i = 0, turn = 0, gameOver = 0;

	//hafýzadan alan al
	arr = malloc(sizeof(char *) * HEIGTH);
	for (; i < HEIGTH; i++) {
		arr[i] = malloc(sizeof(char) * WIDTH);
	}
	//tahtaya ilk halini ver
	initializeTheBoard(arr, HEIGTH, WIDTH);

	do {
		printScreen(arr, HEIGTH, WIDTH);
		play(arr, &turn);
	} while ((gameOver = isGameOver(arr, HEIGTH, WIDTH)) == 0);

	printf("%d player wins!", gameOver);
	//hafizayi geri býrak
	for (i = 0; i < 5; i++) {
		free(arr[i]);
	}
	free(arr);

	return 0;
}

//kullanýcýlarýn ikisinin de sah tasý mevcut mu
//eger oyleyse return 0
//eger 0. oyuncunun tasi yoksa 1 dondur
//eger 1. oyuncunun tasi yoksa 2 dondur
int isGameOver(char ** arr, int nRows, int nCols) {
	return 0;
}

//hareket edilecek hedef noktasindaki tas kimin
//eger siranin kendisindeki oyuncunun ise 0
//degilse 1 dondur
int destinationCheck(char destPiece, int turn) {
	//turn 0 ise
	if ((destPiece >= 'A' && destPiece <= 'Z') && turn == 0) {
		return 0;
	}
	//turn 1 ise
	if ((destPiece >= 'a' && destPiece <= 'z') && turn == 1) {
		return 0;
	}
	return 1;
}

//piyon hareketi. hareket gecerliyse 1 degilse 0 dondurur
int pawnMove(char **arr, int sRow, int sCol, int eRow, int eCol, int direction) {
	//hareket duz ise ilgili alan bos mu?
	if (eRow == sRow + direction && sCol == eCol) {
		if (arr[eRow][eCol] == ' ') {
			return 1;
		}
	}
	//hareket capraz ise hedef alan bos olmamalý
	else if (eRow == sRow + direction
			&& ((sCol == eCol + 1) || (sCol == eCol - 1))) {

		if (arr[eRow][eCol] != ' ') {
			return 1;
		}
	}
	//buraya ulastýysa yukaridaki returnlere ulasamamistir o yuzden 0 dondur
	return 0;
}

//fil hareketi. hareket gecerliyse 1 degilse 0 dondurur
int bishopMove(char **arr, int sRow, int sCol, int eRow, int eCol) {
	int i, j, correct = 0;
	if (sRow > eRow && sCol > eCol) {
		for (i = 1; i < 8; i++)
			if (sRow == eRow + i && sCol == eCol + i) {
				correct = 1;
				for (j = 1; j < i; j++)
					if (arr[eRow + j][eCol + j] != ' ') {
						return 1;
					}
			}
		if (correct == 0)
			return 1;
	} else if (sRow > eRow && sCol < eCol) {
		for (i = 1; i < 8; i++)
			if (sRow == eRow + i && sCol == eCol - i) {
				correct = 1;
				for (j = 1; j < i; j++)
					if (arr[eRow + j][eCol - j] != ' ') {
						return 1;
					}
			}
		if (correct == 0)
			return 1;
	} else if (sRow < eRow && sCol > eCol) {
		for (i = 1; i < 8; i++)
			if (sRow == eRow - i && sCol == eCol + i) {
				correct = 1;
				for (j = 1; j < i; j++)
					if (arr[eRow - j][eCol + j] != ' ') {
						return 1;
					}
			}
		if (correct == 0)
			return 1;
	} else if (sRow < eRow && sCol < eCol) {
		for (i = 1; i < 8; i++)
			if (sRow == eRow - i && sCol == eCol - i) {
				correct = 1;
				for (j = 1; j < i; j++)
					if (arr[eRow - j][eCol - j] != ' ') {
						return 1;
					}
			}
		if (correct == 0)
			return 1;
	} else
		return 1;
	return 0;
}

//at hareketi. hareket gecerliyse 1 degilse 0 dondurur
int knightMove(char **arr, int eRow, int eCol, int sRow, int sCol){
	if ((sRow == eRow + 2 && sCol == eCol + 1)
			|| (sRow == eRow + 2 && sCol == eCol - 1)
			|| (sRow == eRow - 2 && sCol == eCol + 1)
			|| (sRow == eRow - 2 && sCol == eCol - 1)
			|| (sRow == eRow + 1 && sCol == eCol + 2) ||
			(sRow == eRow + 1 && sCol == eCol - 2)
			|| (sRow == eRow - 1 && sCol == eCol + 2)
			|| (sRow == eRow - 1 && sCol == eCol - 2)){
		if (arr[eRow][eCol] != ' ') {
			return 1;
		}
		return 0;
	}
	return 1;
}

//kale hareketi. hareket gecerliyse 1 degilse 0 dondurur
int rockMove(char **arr, int eRow, int eCol, int sRow, int sCol) {
	int i;
	if (sRow == eRow) {
		if (sCol > eCol) {
			for (i = eCol + 1; i < sCol; i++)
				if (arr[eRow][i] != ' ') {
					return 1;
				}
		} else {
			for (i = eCol - 1; i > sCol; i--)
				if (arr[eRow][i] != ' ') {
					return 1;
				}
		}
	} else if (sCol == eCol) {
		if (sRow > eRow) {
			for (i = eRow + 1; i < sRow; i++)
				if (arr[i][eCol] != ' ') {
					return 1;
				}
		} else {
			for (i = eRow - 1; i > sRow; i--)
				if (arr[i][eCol] != ' ') {
					return 1;
				}
		}
	} else
		return 1;
	return 0;
}

//vezir hareketi. hareket gecerliyse 1 degilse 0 dondurur
int queenMove(char **arr, int eRow, int eCol, int sRow, int sCol) {
	int i, j, correct = 0;
	if (sRow == eRow) {
		if (sCol > eCol) {
			for (i = eCol + 1; i < sCol; i++)
				if (arr[eRow][i] != ' ') {
					return 1;
				}
		} else {
			for (i = eCol - 1; i > sCol; i--)
				if (arr[eRow][i] != ' ') {
					return 1;
				}
		}
	} else if (sCol == eCol) {
		if (sRow > eRow) {
			for (i = eRow + 1; i < sRow; i++)
				if (arr[i][eCol] != ' ') {
					return 1;
				}
		} else {
			for (i = eRow - 1; i > sRow; i--)
				if (arr[i][eCol] != ' ') {
					return 1;
				}
		}
	} else if (sRow > eRow && sCol > eCol) {
		for (i = 1; i < 8; i++)
			if (sRow == eRow + i && sCol == eCol + i) {
				correct = 1;
				for (j = 1; j < i; j++)
					if (arr[eRow + j][eCol + j] != ' ') {
						return 1;
					}
			}
		if (correct == 0)
			return 1;
	} else if (sRow > eRow && sCol < eCol) {
		for (i = 1; i < 8; i++)
			if (sRow == eRow + i && sCol == eCol - i) {
				correct = 1;
				for (j = 1; j < i; j++)
					if (arr[eRow + j][eCol - j] != ' ') {
						return 1;
					}
			}
		if (correct == 0)
			return 1;
	} else if (sRow < eRow && sCol > eCol) {
		for (i = 1; i < 8; i++)
			if (sRow == eRow - i && sCol == eCol + i) {
				correct = 1;
				for (j = 1; j < i; j++)
					if (arr[eRow - j][eCol + j] != ' ') {
						return 1;
					}
			}
		if (correct == 0)
			return 1;
	} else if (sRow < eRow && sCol < eCol) {
		for (i = 1; i < 8; i++)
			if (sRow == eRow - i && sCol == eCol - i) {
				correct = 1;
				for (j = 1; j < i; j++)
					if (arr[eRow - j][eCol - j] != ' ') {
						return 1;
					}
			}
		if (correct == 0)
			return 1;
	} else
		return 1;
	return 0;
}

//þah hareketi. hareket gecerliyse 1 degilse 0 dondurur
int kingMove(char **arr, int eRow, int eCol, int sRow, int sCol) {
	if ((sRow == eRow + 1 && sCol == eCol)
			|| (sRow == eRow + 1 && sCol == eCol + 1)
			|| (sRow == eRow + 1 && sCol == eCol - 1)
			|| (sRow == eRow && sCol == eCol + 1)
			|| (sRow == eRow && sCol == eCol - 1)
			|| (sRow == eRow - 1 && sCol == eCol)
			|| (sRow == eRow - 1 && sCol == eCol + 1)
			|| (sRow == eRow - 1 && sCol == eCol - 1)) {
		if (arr[eRow][eCol] != ' ') {
			return 1;
		}
		return 0;
	}
	return 1;
}

//tasýn cinsine göre her tasi kontrol et fonksiyonlarýný yaz
//destinationCheck fonksiyonu yukarýda yazýlmýs ve hedef olarak gideceginiz
//noktadaki tasin kimin olduðuna bakar. Eðer sýranýn kendindeki oyuncunun tasý
//ise 0 dondurur. Deðilse 1 dondurur. Boylece hem hareket fonksyionunda
//gelen deger 1 hem de destinationCheck fonksiyonundan donen deger 1 ise
//canMove fonksiyonu 1 dondurur. && ile bu durum kontrol edilebilir
int canMove(char **arr, int turn, int sRow, int sCol, int eRow, int eCol) {
	char piece = arr[sRow][sCol];

	if (piece == 'P' || piece == 'p') {
		return pawnMove(arr, sRow, sCol, eRow, eCol, 1)
				&& destinationCheck(arr[eRow][eCol], turn);
	}
	//buradan sonrasý her tas icin fonksiyon yazacaksýnýz
	//fil hareketi icin yaz
	else if (piece == 'F' || piece == 'f') {
		return bishopMove(arr, sRow, sCol, eRow, eCol)
				&& destinationCheck(arr[eRow][eCol], turn);
	}
	//at hareketi icin yaz
	else if (piece == 'A' || piece == 'a') {
		return knightMove(arr, sRow, sCol, eRow, eCol)
				&& destinationCheck(arr[eRow][eCol], turn);	
	}
	//kale icin yaz
	else if (piece == 'K' || piece == 'k') {
		return rockMove(arr, sRow, sCol, eRow, eCol)
				&& destinationCheck(arr[eRow][eCol], turn);	
	}
	//vezir icin yaz
	else if (piece == 'V' || piece == 'v') {
		return queenMove(arr, sRow, sCol, eRow, eCol)
				&& destinationCheck(arr[eRow][eCol], turn);	
	}
	//sah icin yaz
	else if (piece == 'S' || piece == 's') {
		return kingMove(arr, sRow, sCol, eRow, eCol)
				&& destinationCheck(arr[eRow][eCol], turn);
	}
}

void play(char **arr, int *turn) {
	char *sMove, *eMove;
	int sRow, sCol, eRow, eCol;
	sMove = malloc(sizeof(char) * 3);
	eMove = malloc(sizeof(char) * 3);
	do {
		printf("%d. player turn: ", *turn + 1);
		scanf("%2s %2s", sMove, eMove);
		fflush(stdin);
		sRow = (int) (sMove[0] - 'A');
		sCol = (int) (sMove[1] - '1');
		eRow = (int) (eMove[0] - 'A');
		eCol = (int) (eMove[1] - '1');
		if ((sRow >= 0 && sRow <= 7) && (sCol >= 0 && sCol <= 7)
				&& (eCol >= 0 && eCol <= 7) && (eRow >= 0 && eRow <= 7)) {
			char piece = arr[sRow][sCol];
			//secilen tas sýrasý gelen kullanýcýnýn mý
			if ((*turn == 0 && (piece >= 'A' && piece <= 'Z'))
					|| (*turn == 1 && (piece >= 'a' && piece <= 'z'))) {
				//secilen tas hedef konuma gidebilir mi
				if (canMove(arr, *turn, sRow, sCol, eRow, eCol) == 1) {
					arr[eRow][eCol] = piece;
					arr[sRow][sCol] = ' ';
					*turn = (*turn + 1) % 2;
					break;
				}
				//eger gidemiyorsa illegal move
				else {
					printf("Illegal move. Try again.\n");
				}

			}
			//secilen tas kullanýcýnýn degil
			else {
				printf("It's your opponent's piece\n");
			}
		}
		//istenen konumlar aralýkta girilmemis
		else {
			printf("Your move is out of boundary\n");
		}
	} while (1); //dogru hareket yapýlana kadar devam eder. Dogru hareket yapýldýysa
				 //yukarýdaki break bu while kosulunu kýrar ve cýkýlýr.
}
//dizi iceriklerini ekrana yaz.
//her bir tas bir karenin icine girsin diye
//bir kac duzenleme yapildi
void printScreen(char ** arr, int nRows, int nCols) {

	//ekraný her seferinde silip tekrar yazmak isterseniz.
	//aþagýdaki komutu aciniz
	system("@cls||clear");

	int i, j;

	printf("%s", " |");
	for (j = 0; j < nCols;) {
		printf("  %d  |", ++j);
	}

	printf("\n--");

	for (j = 0; j < nCols; j++) {
		printf("%s", "------");
	}

	printf("\n");

	for (i = 0; i < nRows; i++) {
		printf("%c|", 'A' + i);

		for (j = 0; j < nCols; j++) {
			printf("  %c  |", arr[i][j]);
		}

		printf("\n--");

		for (j = 0; j < nCols; j++) {
			printf("%s", "------");
		}
		printf("\n");
	}
}
void initializeTheBoard(char **arr, int nRows, int nCols) {
	int i, j;
	for (i = 0; i < nRows - 2; i++) {
		for (j = 0; j < nCols; j++) {
			if (i == 0) {
				if (j == 0 || j == nCols - 1) {
					arr[i][j] = 'K';
				} else if (j == 1 || j == nCols - 2) {
					arr[i][j] = 'A';
				} else if (j == 2 || j == nCols - 3) {
					arr[i][j] = 'F';
				} else if (j == 3) {
					arr[i][j] = 'V';
				} else {
					arr[i][j] = 'S';
				}
			} else if (i == 1) {
				arr[i][j] = 'P';
			} else {
				arr[i][j] = ' ';
			}
		}
	}
	//last 2 rows for opponent
	for (i = nRows - 2; i < nRows; i++) {
		for (j = 0; j < nCols; j++) {
			//add 32 to lower the opponent's character
			arr[i][j] = arr[nRows - i - 1][j] + 32;
		}
	}
}

