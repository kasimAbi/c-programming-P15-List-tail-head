#pragma once

#ifndef header_h
#define header_h

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>


#define GROESSE 40

struct Telefonnummern		// struktur für telefonnummern.
{
	char festnetz[GROESSE];
	char handy[GROESSE];
	char dienstnummer[GROESSE];
};

struct Telefon		
{
	char nachname[GROESSE];
	char vorname[GROESSE];
	struct Telefonnummern meine_telefonnummern;		// gekapselte struktur. greift auf telefonnummern zu
};

struct Knoten
{
	Telefon *telefon;		// gekapselte struktur. greift auf telefon zu.
	Knoten *next;			// auf die nächste telefonliste
};

struct ListHead
{
	// gekapselte strukturen. greifen auf knoten zu.
	Knoten *head;		// zeigt die erste addresse
	Knoten *tail;		// zeigt die letzte addresse
};

ListHead *ListCreate(void);		// funktionsprototypen
void hinzufuegen(ListHead*);
void element_loeschen(ListHead*);
void element_suchen(ListHead*);
void anzahl_ausgeben(ListHead*);
void elemente_ausgeben(ListHead*);

void eingeben(Telefon*);
int vergleichen(Telefon*, Telefon*);
Knoten* suchen(ListHead*);
void ausgeben(Telefon*);

int pruefen_ob_zahl(char[GROESSE]);
int pruefen_ob_zeichen(char[GROESSE]);
float pruefen_komma_zahl(char[GROESSE]);

#endif // !header.h