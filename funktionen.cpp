#include "header.h"

// liste erstellen
ListHead *ListCreate(void)
{
	// zeigergr��e vom Typ der struktur ListHead
	struct ListHead *kopf;
	// Spreicher f�r kopf dynamisch reservieren
	kopf = (ListHead*)malloc(sizeof(ListHead));
	// wenn speicher reserviert werden konnte
	if (kopf)
	{
		// head und tail mit 0 initialisieren
		kopf->head = kopf->tail = 0;
		return kopf;
	}
	// wenn kein speicher reserviert werden konnte
	return 0;
}


void hinzufuegen(ListHead* listenkopf)
{
	Telefon *kontakt;		
	Knoten *knoten, *aktuell, *vorgaenger;
	// speicherplatz f�r das einzuf�gende element dynamisch reservieren.
	kontakt = (Telefon*)malloc(sizeof(Telefon));
	if (!kontakt)
	{
		// fehlermeldung
		printf("Es konnte kein Speicherbereich reserviert werden!\n");
		return;
	}
	// Kontaktdaten vom Benutzer eingeben lassen (in eigener Funktion ausgelagert)
	eingeben(kontakt); 
	// speicherplatz dynamisch reservieren
	knoten = (Knoten*)malloc(sizeof(Knoten));
	if (!knoten)
	{	
		//fehlermeldung
		printf("es konnte kein speicherbereich reserviert werden!\n");
		free(kontakt); // Vorher reservierten Speicher f�r Kontakt freigeben, da dieser nicht mehr eingef�gt werden kann
		return;
	}

	// Telefonkontakt des einzuf�genden Knotens auf zuvor eingegebenen Kontakt setzen
	knoten->telefon = kontakt;

	// Fall 1: Liste war leer -> Knoten wird head und tail
	if (!(listenkopf->head))
	{
		listenkopf->head = listenkopf->tail = knoten;
		knoten->next = NULL;
		printf("erfolgreich eingetragen!\n");
		return;
	}

	// Fall 2: Knoten muss �ber aktuellem head einsortiert werden
	if (vergleichen(kontakt, listenkopf->head->telefon) < 0)
	{
		knoten->next = listenkopf->head;
		listenkopf->head = knoten;
		printf("erfolgreich eingetragen!\n");
		return;
	}

	// Fall 3: Knoten muss nach aktuellem tail einsortiert werden
	if (vergleichen(kontakt, listenkopf->tail->telefon) > 0)
	{
		listenkopf->tail->next = knoten;
		knoten->next = NULL;
		listenkopf->tail = knoten;
		printf("erfolgreich eingetragen!\n");
		return;
	}

	// Fall 4: Knoten muss zwischen head und tail einsortiert werden
	aktuell = vorgaenger = listenkopf->head;
	while (vergleichen(kontakt, aktuell->telefon) >= 0)
	{
		if (vergleichen(kontakt, aktuell->telefon) == 0)
		{
			free(knoten);
			free(kontakt);
			printf("dieser kontakt ist bereits in der telefonliste gespeichert!\n");
			return;
		}

		vorgaenger = aktuell;
		aktuell = aktuell->next;
	}

	knoten->next = aktuell;
	vorgaenger->next = knoten;

	printf("erfolgreich eingetragen!\n");
}

void element_loeschen(ListHead* listenkopf)
{
	Knoten *knoten, *aktuell, *vorgaenger;
	// aktuell und vorg�nger mit listenkopf->head gleichsetzen. bzw erste listenelement. wenn nciht vorhanden kriegen sie die werte 0.
	aktuell = vorgaenger = listenkopf->head;
	if (!aktuell)
	{
		printf("die telefonliste ist leer!\n");
		return;
	}

	knoten = suchen(listenkopf);
	if (!knoten)
	{
		printf("nicht gefunden.\n");
		return;
	}

	// Fall 1: zu l�schender Kontakt ist einziger Kontakt in der Liste (knoten = head = tail)
	if (aktuell == knoten && listenkopf->tail == knoten)
	{
		listenkopf->head = NULL;
		listenkopf->tail = NULL;
		free(knoten->telefon);
		free(knoten);
		printf("erfolgreich geloescht!\n");
		return;
	}

	// Fall 2: zu l�schender Kontakt ist head
	if (aktuell == knoten)
	{
		listenkopf->head = listenkopf->head->next;
		free(knoten->telefon);
		free(knoten);
		printf("erfolgreich geloescht!\n");
		return;
	}

	// Fall 3: zu l�schender Kontakt ist zwischen head und einschliesslich tail
	while (aktuell)
	{
		// pr�fen was man l�schen will
		if (aktuell == knoten) {
			// pr�ft ob der tail die zu l�schende stelle ist.
			if (listenkopf->tail == knoten)
			{
				// tail wird vorg�nger
				listenkopf->tail = vorgaenger;
				vorgaenger->next = NULL;
			}
			else
			{
				// damit nciht mehr auf das gel�schte element gezeigt wird.
				vorgaenger->next = aktuell->next;
			}
			// l�schen des ausgew�hlten listenelements
			free(knoten->telefon);
			free(knoten);

			printf("erfolgreich geloescht!\n");
			return;
		}
		// weil oben einer gel�scht wurde, muss die liste neu sortiert werden.
		vorgaenger = aktuell;
		aktuell = aktuell->next;
	}
}

void element_suchen(ListHead* listenkopf)
{
	Knoten* knoten;

	if (!(listenkopf->head))
	{
		printf("die telefonliste ist leer!\n");
		return;
	}

	knoten = suchen(listenkopf);
	if (!knoten)
	{
		printf("nicht gefunden.\n");
		return;
	}

	ausgeben(knoten->telefon);
}

void anzahl_ausgeben(ListHead* listenkopf)
{
	// erste listenelement wird auf knoten verkn�pft
	Knoten* knoten = listenkopf->head;
	int found = 0;

	if (!knoten)
	{
		printf("die telefonliste ist leer!\n");
		return;
	}
	while (knoten)
	{
		found++;
		// z�hlt hoch und nimmt die n�chste stelle vom knoten bis es die NULL erreicht. also tail
		knoten = knoten->next;
	}
	printf("in der telefonliste sind %i kontakte gespeichert!\n", found);
}

void elemente_ausgeben(ListHead* listenkopf)
{
	// das gleiche wie bei anzahl ausrechnen nur mit ausgeben.
	Knoten* knoten = listenkopf->head;

	if (!knoten)
	{
		printf("die telefonliste ist leer!\n");
		return;
	}

	while (knoten)
	{
		// jedes knoten ausgeben.
		ausgeben(knoten->telefon);
		knoten = knoten->next;
	}
}



Knoten* suchen(ListHead* listenkopf)
{
	char eingabe[GROESSE];
	Knoten *knoten, *aktuell = listenkopf->head;
	int found = 0;
	if (!aktuell)
	{
		return 0;
	}
	do
	{
		printf("bitte geben sie den nachnamen ein: ");
		fgets(eingabe, GROESSE, stdin);

		if (strlen(eingabe) > GROESSE)
		{
			printf("der nachname darf maximal %i zeichen lang sein!\n", GROESSE);
		}
	} while (strlen(eingabe) > GROESSE);

	while (aktuell)
	{
		if (!strcmp(eingabe, aktuell->telefon->nachname))
		{
			// wenn eingabe und nachname �bereinstimmen setzt das programm knoten auf aktuelle listenelement
			knoten = aktuell;
			// z�hlt hoch wenn �fter vorhanden ist.
			found++;
		}
		// n�chste stelle
		aktuell = aktuell->next;
	}

	switch (found)
	{
	case 0:
		// wenn ncihts gefudnen wurde
		return 0;
	case 1:
		// wenn einer �bereinstimmt
		return knoten;
		break;
	default:
		// wenn mehrere �bereinstimmen. anschlie�end �berpr�ft er dann anch den vornamen.
		aktuell = listenkopf->head;
		printf("es wurden %i Eintraege zu diesem nachnamen gefunden!\n", found);
		do
		{
			printf("bitte geben Sie einen vornamen ein: ");
			fgets(eingabe, GROESSE, stdin);

			if (strlen(eingabe) > GROESSE)
			{
				printf("der nachname darf maximal %i zeichen lang sein!\n", GROESSE);
			}
		} while (strlen(eingabe) > GROESSE);

		while (aktuell)
		{
			// wenn nachnamen gleich sind von dem was man bei nachnamen vorhin eingegeben hat und die von der aktuellen
			if (!strcmp(knoten->telefon->nachname, aktuell->telefon->nachname))
			{
				// wenn sie gleich sind dann gibt er aktuelles listenelement zur�ck.
				if (!strcmp(eingabe, aktuell->telefon->vorname))
				{
					return aktuell;
				}
			}
			// ansonsten nimmt aktuell das n�chste listenelement.
			aktuell = aktuell->next;
		}
		return 0;
	}
}

// zum daten eingeben f�r die kontakte
void eingeben(Telefon *kontakt)
{
	char eingabe[GROESSE];
	int index = 0;
	do		// do-while schleife
	{
		printf("bitte geben sie den nachnamen ein:\t");
		fgets(eingabe, GROESSE, stdin);
		index = pruefen_ob_zeichen(eingabe);
		if (index == 0)
		{
			printf("Es durfen keine zahlen vorhanden sein.\n");
		}
		if (strlen(eingabe) > GROESSE)		// guckt wie viele zeichen eingabe hat
		{
			printf("der nachname darf maximal %i zeichen lang sein!\n", GROESSE);		// fehlermeldung
			index = 0;
		}
	} while (index == 0);
	strcpy(kontakt->nachname, eingabe);		// f�gt die eingegebene zeichenkette in kontak- nachname ein.

	do				// das gleiche wie oben nur f�r vorname
	{
		printf("bitte geben sie den vornamen ein:\t");
		fgets(eingabe, GROESSE, stdin);
		index = pruefen_ob_zeichen(eingabe);
		if (index == 0)
		{
			printf("Es durfen keine zahlen vorhanden sein.\n");
		}
		if (strlen(eingabe) > GROESSE)
		{
			printf("der vorname darf maximal %i zeichen lang sein!\n", GROESSE);
		}
	} while (index == 0);
	strcpy(kontakt->vorname, eingabe);

	do			// f�r festnetz
	{
		printf("bitte geben sie die festnetznummer ein:\t");
		fgets(eingabe, GROESSE, stdin);

		if (!pruefen_ob_zahl(eingabe))
		{
			printf("die nummer darf nur aus positiven geraden zahlen bestehen.\n");		// fehlermeldung
		}
	} while (!pruefen_ob_zahl(eingabe));
	strcpy(kontakt->meine_telefonnummern.festnetz, eingabe);		// speichert die nummer als string zeichenkette bei festnetz

	do			// das gleiche wie oben f�r handynummer
	{
		printf("bitte geben sie die handynummer ein:\t");
		fgets(eingabe, GROESSE, stdin);

		if (!pruefen_ob_zahl(eingabe))
		{
			printf("die nummer darf nur aus positiven geraden zahlen bestehen.\n");
		}
	} while (!pruefen_ob_zahl(eingabe));
	strcpy(kontakt->meine_telefonnummern.handy, eingabe);

	do				// das geliche wie oben f�r dienstnummer
	{
		printf("bitte geben sie die dienstnummer ein:\t");
		fgets(eingabe, GROESSE, stdin);

		if (!pruefen_ob_zahl(eingabe))
		{
			printf("die nummer darf nur aus positiven geraden zahlen bestehen.\n");
		}
	} while (!pruefen_ob_zahl(eingabe));
	strcpy(kontakt->meine_telefonnummern.dienstnummer, eingabe);
}

int vergleichen(Telefon* kontakt1, Telefon* kontakt2)
{
	// strcmp = stringcompare. vergleicht und gibt 0 zur�ck wenn sie gleich sind
	int vergleich = strcmp(kontakt1->nachname, kontakt2->nachname);
	if (vergleich != 0)
	{
		return vergleich;
	}
	else
	{
		return strcmp(kontakt1->vorname, kontakt2->vorname);
	}
}

void ausgeben(Telefon *kontakt)
{
	printf("\n");
	printf("nachname:\t%s", kontakt->nachname);
	printf("vorname:\t%s", kontakt->vorname);
	printf("festnetz:\t%s", kontakt->meine_telefonnummern.festnetz);
	printf("handy:\t\t%s", kontakt->meine_telefonnummern.handy);
	printf("dienstnummer:\t%s", kontakt->meine_telefonnummern.dienstnummer);
}