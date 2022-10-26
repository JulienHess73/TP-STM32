#include "algo_Huffman.h"

#define READ_BIT(REG,POS)	(REG & (1<<POS))>>POS

uint8_t texte[] =  "aaaabbbccd";
uint32_t tabCaractere[256] = {0};
uint32_t taille;
struct Noeud* arbreHuffman[256] = {0};
struct Noeud* racine;
struct Noeud* noeud_test;
uint32_t code = 0;
uint32_t tailleCode = 0;
uint8_t texteCompress[TAILLE_MAX_COMPRESS];
struct Entete* entete = {0};

void arbre_Huffman(void){

	occurence(texte,tabCaractere);
	taille = creerFeuille(arbreHuffman,tabCaractere);
	triArbre(arbreHuffman,taille);
	cree_racine(arbreHuffman,taille,racine);
	racine = arbreHuffman[0];
	parcourirArbre(racine);
	creerCode(racine,code,tailleCode);
	compression(texteCompress,racine,texte);
	entete = creeentete(texte,texteCompress);


}

int occurence(u_int8_t *texte, u_int32_t tabCaractere[256]){
    for(int i=0;i<strlen(texte);i++){
        tabCaractere[(int)texte[i]] += 1;
    }
    return 0;
}

uint32_t creerFeuille(struct Noeud *arbre[256],u_int32_t tabCaractere[256]){
	uint32_t j=0;
    struct Noeud* noeud;
    for(int i=0;i<256;i++){
        if(tabCaractere[i] != 0){
            noeud = malloc(sizeof(struct Noeud));
            noeud->c = (char)i;
            noeud->occurence = tabCaractere[i];
            noeud->code = 0;
            noeud->tailleCode = 0;
            noeud->gauche = NULL;
            noeud->droite = NULL;
            arbre[j] = noeud;
            j++;
        }
    }
    return j;
}

void afficheArbre(struct Noeud *arbre[256],uint32_t taille){
    struct Noeud noeud;
    for(int i=0;i<taille;i++){
        noeud = *arbre[i];
        if(noeud.c != '\0'){
        	printf("Adresse : %p,Cara: %c ,occu : %ld,code : %ld, taille : %ld, noeud gauche : %p, noeud droit : %p \n",arbre[i],noeud.c,noeud.occurence,noeud.code,noeud.tailleCode,noeud.gauche,noeud.droite);
        }
    }
    printf("\r\n");

}

void triArbre(struct Noeud* arbre[256], uint32_t taille){

	struct Noeud *noeud, *noeud1, *noeud_courant;

    for(int i=taille-1;i>0;i--){
        for(int j=0;j<i;j++){
        	noeud = arbre[j];
        	noeud1 = arbre[j+1];
        	if(noeud1->occurence < noeud->occurence){
        		noeud_courant = noeud;
        		arbre[j] = noeud1;
        		arbre[j+1] = noeud_courant;
        	}
        }
    }
}

void cree_racine(struct Noeud* arbre[256], uint32_t taille,struct Noeud* racine){
	struct Noeud *noeud, *noeud1, *newnoeud;
	uint8_t occu = 0;
	uint8_t i = taille;
	while(i != 1){
		triArbre(arbre,taille);
		afficheArbre(arbreHuffman,taille);
		noeud = arbre[0];
		noeud1 = arbre[1];
		occu = noeud->occurence + noeud1->occurence;
		newnoeud = malloc( sizeof(struct Noeud));
		newnoeud->c = '!';
		newnoeud->occurence = occu;
		newnoeud->code = 0;
		newnoeud->tailleCode = 0;
		newnoeud->gauche = noeud;
		newnoeud->droite = noeud1;
		arbre[0] = newnoeud;
		arbre[1] = 0;
		i--;
	}
	afficheArbre(arbreHuffman,taille);
}

void parcourirArbre(struct Noeud* ptrNoeud){
	if(ptrNoeud->droite==NULL && ptrNoeud->gauche==NULL){
		printf("je suis une feuille\r\n");
	}
	else{
		printf("Je suis un noeud : droite : %p, gauche : %p \r\n",ptrNoeud->droite,ptrNoeud->gauche);
		parcourirArbre(ptrNoeud->droite);
		parcourirArbre(ptrNoeud->gauche);
	}
}

void creerCode(struct Noeud* ptrNoeud,uint32_t code, uint32_t taille){
	if(ptrNoeud->droite==NULL && ptrNoeud->gauche==NULL){
		ptrNoeud->tailleCode=taille;
		ptrNoeud->code=code;
		printf("%c \t code : %d \t taille :%d \r\n",ptrNoeud->c, ptrNoeud->code, ptrNoeud->tailleCode);
	}
	else{
		creerCode(ptrNoeud->droite,code<<1,taille+1);
		creerCode(ptrNoeud->gauche,(code<<1)+1,taille+1);
	}
}

struct Noeud* getAdress(struct Noeud* ptrNoeud, uint8_t caractere){
	struct Noeud* noeud;
	if(ptrNoeud->droite==NULL && ptrNoeud->gauche==NULL){
		if(ptrNoeud->c == caractere){
			noeud = ptrNoeud;
			return noeud;
		}
		else{
			return NULL;
		}
	}
	else{
		noeud = getAdress(ptrNoeud->droite,caractere);
		if(noeud == NULL){
			return getAdress(ptrNoeud->gauche,caractere);
		}
	}
}

struct Entete* creeentete(uint8_t *texte, uint8_t texteCompress[TAILLE_MAX_COMPRESS])
{
	struct Entete* entete;
	struct Noeud* noeud;

	entete->taille_fichier = strlen(texteCompress);
	entete->taille_entete = sizeof(struct Entete);
	entete->nbr_total = strlen(texte);

	for(int i=0;i<taille;i++){
		noeud = getAdress(racine,texte[i]);
		entete->code_Huffman[i] = noeud->code;
		entete->code_ascii[i] = noeud->c;
		entete->taille_code[i] = noeud->tailleCode;

	}
	return entete;
}

void compression(uint8_t texteCompress[TAILLE_MAX_COMPRESS],struct Noeud* racine,uint8_t texte[taille]){
	uint8_t k=0,v=0;
		for(int i=0;i<taille;i++){
			noeud_test = getAdress(racine,texte[i]);

			v=0;
			for(int j=(noeud_test->tailleCode+k);j>k;j--){
				texteCompress[j] = READ_BIT(noeud_test->code,v);
				printf("%d\r",texteCompress[j]);
				v++;
			}
			k += noeud_test->tailleCode;
		}
		printf("\n");
}
