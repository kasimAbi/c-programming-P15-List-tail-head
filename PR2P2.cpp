#include "header.h"

int main(void)
{
	int wahl = 0;
	char eingabe[GROESSE];
	ListHead *listenkopf = ListCreate();		// liste erstellen. listenkopf ist dann meine liste.

	while (wahl != 6)
	{
		// menü
		printf("was moechten sie tun?\n (1) ein neues element sortiert in die liste einfuegen.\n (2) ein bestimmtes listenelement loeschen.\n");
		printf(" (3) nach den nutzerdaten eines bestimmten listenelements suchen.\n (4) die anzahl der listenelemente anzeigen.\n");
		printf(" (5) die nutzerdaten aller listenelemente anzeigen.\n (6) programm beenden.\nihre wahl lautet:\t");
		fgets(eingabe, GROESSE, stdin);
		wahl = pruefen_ob_zahl(eingabe);
		switch (wahl)		// wählt aus was gewählt wurde.
		{
		case 1:			// funktionsaufrufe wenn wahl x zahl hat.
			hinzufuegen(listenkopf);
			break;
		case 2: 
			element_loeschen(listenkopf);
			break;
		case 3:
			element_suchen(listenkopf);
			break;
		case 4:
			anzahl_ausgeben(listenkopf);
			break;
		case 5:
			elemente_ausgeben(listenkopf);
			break;
		case 6:
			// beendet programm
			printf("Das Programm wird nun beenden.\n");
			break;
		default:
			system("cls");
			printf("Sie haben etwas falsches eingegeben.\n\n");		// fehlerausgabe.
		}
		fgets(eingabe, GROESSE, stdin);			// programm zum stehen bringen.
		system("cls");		// löschen von kommando zeile
	}
	return 0;
}