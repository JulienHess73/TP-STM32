#include <stdio.h>
#include <stdlib.h>

#define TAILLE_MAX_COMPRESS 	500

struct Noeud{
	uint8_t c;
	uint32_t occurence;
	uint32_t code;
	uint32_t tailleCode;
	struct Noeud *gauche, *droite;
};

struct Entete{
	uint16_t taille_entete;
	uint16_t taille_fichier;
	uint16_t nbr_total;
	uint8_t code_ascii[256];
	uint8_t code_Huffman[256];
	uint8_t taille_code[256];
};

extern uint32_t taille;

int occurence(uint8_t *texte, uint32_t tabCaractere[256]);
uint32_t creerFeuille(struct Noeud *arbre[256],uint32_t tabCaractere[256]);
void afficheArbre(struct Noeud *arbre[256], uint32_t taille);
void arbre_Huffman(void);
void triArbre(struct Noeud* arbre[256], uint32_t taille);
void cree_racine(struct Noeud* arbre[256], uint32_t taille,struct Noeud* racine);
void parcourirArbre(struct Noeud* ptrNoeud);
void creerCode(struct Noeud* ptrNoeud,uint32_t code, uint32_t taille);
struct Noeud* getAdress(struct Noeud* ptrNoeud, uint8_t caractere);
struct Entete* creeentete(uint8_t *texte, uint8_t texteCompress[TAILLE_MAX_COMPRESS]);
void compression(uint8_t texteCompress[TAILLE_MAX_COMPRESS],struct Noeud* racine,uint8_t texte[taille]);
