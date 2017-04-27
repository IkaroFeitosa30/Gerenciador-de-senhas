#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
	int tempo[3];
	char nomeorgao[50];
	int idade;
	char nome[150];
}No;
typedef struct orgao{
	char nomeOrg[50];
	int qtAt;
}Orgao;
struct heap{
	Orgao *orgs;
	No ***pessoas;
	int qtOrg;
	int *qtPOrg;
	int totalP;
}Heap;

int getEsq(int i){
	return (2*i)+1;
}
int getDir(int i){
	return (2*i)+2;
}
int getqtPOrg(int i){
	return Heap.qtPOrg[i];
}
int vIdade(int iArvore,int i){
	return Heap.pessoas[iArvore][i]->idade;
}
int *vTime(int iArvore,int i){
	return Heap.pessoas[iArvore][i]->tempo;
}
int compTime(int *time1,int *time2){
	if(time1[0]>time2[0])
		return 1;
	else if(time1[0]<time2[0])
		return 0;
	else{
		if(time1[1]>time2[1])
			return 1;
		else if(time1[1]<time2[1])
			return 0;
		else{
			if(time1[2]>time2[2])
				return 1;
			else if(time1[2]<time2[2])
				return 0;
		}
	}
	return 0;
}
void troca(int iArvore,int i, int p){
	No *aux = (No*)malloc(sizeof(No));
	aux = Heap.pessoas[iArvore][p];
	Heap.pessoas[iArvore][p] = Heap.pessoas[iArvore][i];
	Heap.pessoas[iArvore][i] = aux;
	
}
void remover(int iArvore){
	troca(iArvore,0,Heap.qtPOrg[iArvore]-1);
	free(Heap.pessoas[iArvore][Heap.qtPOrg[iArvore]-1]);
	Heap.pessoas[iArvore][Heap.qtPOrg[iArvore]-1] = NULL;
	Heap.qtPOrg[iArvore]--;
	Heap.totalP--;
}

void heapfy(int iArvore,int i){
		int p = i;
		int e=getEsq(i);
		int d=getDir(i);
		if(e<getqtPOrg(iArvore)){
			if(vIdade(iArvore,e)>=60){
				if(vIdade(iArvore,p)<60)
					p=e;
				else if(!compTime(vTime(iArvore,e),vTime(iArvore,p)))
					p=e;
			}
			else if(!compTime(vTime(iArvore,e),vTime(iArvore,p)))
				p=e;
					
		}
		if(d<getqtPOrg(iArvore)){
			if(vIdade(iArvore,d)>=60){
				if(vIdade(iArvore,p)<60)
					p=d;
				else if(!compTime(vTime(iArvore,d),vTime(iArvore,d)))
					p=d;
			}
			else if(!compTime(vTime(iArvore,d),vTime(iArvore,d)))
				p=d;
					
		}
		
		if(i!=p){
			troca(iArvore,i,p);
			heapfy(iArvore,p);
		}
		
			
}

void imprimir(FILE *arq,int iArvore){
	int i;
	fprintf(arq,"[%s] ",Heap.orgs[iArvore].nomeOrg);
	for(i=Heap.orgs[iArvore].qtAt;i>0;i--){
		if(Heap.pessoas[iArvore][0]!=NULL){
			if(i-1 == 0)
				fprintf(arq,"%s",Heap.pessoas[iArvore][0]->nome);
			else if(Heap.qtPOrg[iArvore] == 1)
				fprintf(arq,"%s",Heap.pessoas[iArvore][0]->nome);
			else
				fprintf(arq,"%s, ",Heap.pessoas[iArvore][0]->nome);
			remover(iArvore);
			heapfy(iArvore,0);
		}
	}
}

void addArvore(No* novo){
	int j;
	
	for(j=0;j<Heap.qtOrg;j++){
		int comp = strcmp(novo->nomeorgao,Heap.orgs[j].nomeOrg);
		
		if(comp==0){
			Heap.pessoas[j][getqtPOrg(j)]=novo;
			Heap.qtPOrg[j]++; // Incrementando a quantidade de pessoas no Orgão
			
			break;
		}
	}
	
}
void viewAll(){
	int i,j;
	for(i=0;i<Heap.qtOrg;i++){
		printf("\n%s's:\n",Heap.orgs[i].nomeOrg);
		for(j=0;j<Heap.totalP;j++){
			if(Heap.pessoas[i][j]!=NULL)
				printf("%s\n",Heap.pessoas[i][j]->nome);
			else
				break;
		}
	}
}



int main(int argc, char *argv[]){
		
	if(argc>1){
		FILE *arq;
		arq= fopen(argv[1],"r");
	
		if(arq!=NULL){
			
			fscanf(arq,"%d",&Heap.qtOrg);
			Heap.qtPOrg=(int*)malloc(sizeof(int)*Heap.qtOrg);
			int i;
			for(i =0;i<Heap.qtOrg;i++){
				Heap.qtPOrg[i] = 0;
			}
			
			Heap.orgs=(Orgao*)malloc(sizeof(Orgao)*Heap.qtOrg);
			Heap.qtPOrg = (int*)malloc(sizeof(int)*Heap.qtOrg);
			i=0;
			//1- lendo os orgãos
			while(i<Heap.qtOrg){
				
				Orgao novo;
				fscanf(arq,"%s %d",novo.nomeOrg,&novo.qtAt);
				
				
				Heap.orgs[i] = novo;
				
				Heap.qtPOrg[i] = 0;
				i++;
			}//end 1
			
			fscanf(arq,"%d",&Heap.totalP);
			//2- iniciando o ***pessoas com NULL
			Heap.pessoas=(No***)malloc(sizeof(No**)*Heap.qtOrg);
			int j;
			for(i=0;i<Heap.qtOrg;i++){
				Heap.pessoas[i] = (No**)malloc(sizeof(No*)*Heap.totalP);
			
				for(j=0;j<Heap.totalP;j++){
					Heap.pessoas[i][j] = NULL;
				}
					
			}//end 2
			
			//3- Lendo as pessoas
			for(i=0; i<Heap.totalP;i++){
				
				No *novo = (No*)malloc(sizeof(No));
				
				
				fscanf(arq,"\n%[^:]s",novo->nomeorgao);
				fscanf(arq,":%[^-]s",novo->nome);
				fscanf(arq,"-%d",&novo->idade);
				fscanf(arq,"-%d:%d:%d",&novo->tempo[0],&novo->tempo[1],&novo->tempo[2]);
				
							
				addArvore(novo);
				//printf("%s\n",novo->nomeorgao);
				//printf("%s:%s-%d-%d:%d:%d\n",novo->nomeorgao,novo->nome,novo->idade,novo->tempo[0],novo->tempo[1],novo->tempo[2]);
				
				
			}
			//end 3
			
			
			//Heapfy
			for(i=0;i<Heap.qtOrg;i++){
				for(j=(Heap.qtPOrg[i]-2)/2;j>=0;j--)
					heapfy(i,j);
			}
			
			
			//viewAll();
			//SAIDA
			arq = fopen(argv[2],"w");
			
			if(arq!=NULL){
				while(Heap.totalP>0){
					for(i=0;i<Heap.qtOrg;i++){
						if(Heap.qtPOrg[i]>0){
							imprimir(arq,i);
							if(Heap.qtPOrg[i+1]>0)
								fprintf(arq,"\n");
						}
					}
				
				}
			}else
				printf("\n ARQUIVO NÃO FOI CRIADO");
			
			
			
			
			
		}
		
		fclose(arq);
	}
	
	
	
	
	return 0;
}
