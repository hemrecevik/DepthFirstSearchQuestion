#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define MAXROW 5

typedef struct _Row//HASH TABLOSUNUN BAÐLI LÝSTE KISMI
{

	int numara;
	struct _Row *sonraki;
}Row;

typedef struct _Table//HASH TABLOSUNUN DÝZÝ KISMI
{
	Row satirlar[MAXROW]; 
}Table;

Table tablo;

void baslangic_deger_atama()//HASH TABLOSUNDAKÝ DÝZÝ ELEMANARINA ÝLK ATAMA
{
	int i;
	for(i=0;i<MAXROW;i++)
	{
		tablo.satirlar[i].numara=i;
		tablo.satirlar[i].sonraki=NULL;
	}
}
void collision(Row *bilgi,Row *ilk_adres)//HASH TABLOSUNDAKÝ DÜÐÜMLERE KOMÞU EKLEME
{
	Row *gecici;
	gecici=ilk_adres;
	while(gecici->sonraki!=NULL)
	{
		gecici=gecici->sonraki;
	}
	gecici->sonraki=bilgi;
}


void Liste_Kontrol(int k_m[][MAXROW])//DÜÐÜMLERÝN KOMÞULARINI BULUP EKLE YE YOLLA
{	Row *bilgi;
	for(int i=0;i<MAXROW;i++)
	{
		for(int j=0;j<MAXROW;j++)
	 {
		if(k_m[i][j]==1)
   		{
   				bilgi=(Row *)malloc(sizeof(Row));
		if(bilgi==NULL)
		{
			printf("Bellek Dolu..");
			exit(0);	
		}
		bilgi->numara=j;
		bilgi->sonraki=NULL;
		collision(bilgi,&tablo.satirlar[i]);
   		}
  }
 }
 
}

void Tablo_Listele()//KOMÞULUK LÝSTESÝNÝ YAZDIR
{	
	Row *gecici;
	int i;
	printf(" A=0 B=1 C=2 D=3 E=4\n");
	for(i=0;i<MAXROW;i++)
	{
	
			printf(" %d -",tablo.satirlar[i].numara);
			gecici=tablo.satirlar[i].sonraki;
			while(gecici!=NULL)
			{
				printf(" %d ",gecici->numara);
				gecici=gecici->sonraki;
			}
			printf("\n");
	
	}
	
}
void Dugum_derecesi(int sayi)//DÜÐÜMÜN KAÇ KOMÞUSU OLDUÐUNU BULMA
{
		Row *gecici;
	int i,sayac=0;
	for(i=0;i<MAXROW;i++)
	{
			if(sayi==tablo.satirlar[i].numara){
			gecici=tablo.satirlar[i].sonraki;
			while(gecici!=NULL)
			{
				sayac++;
				gecici=gecici->sonraki;
			}
		}
		
	}
	printf("\n...Aradiginiz dugumun derecesi = %d ...",sayac);
}

void Complete_Graf()//DÜÐÜMLERÝN HER BÝRÝNÝN ARASINDA KENAR VAR MI BULMA
{
		Row *gecici;
	int i,sayac=0;
	for(i=0;i<MAXROW;i++)
	{
			gecici=tablo.satirlar[i].sonraki;
			while(gecici!=NULL)
			{
				sayac++;
				gecici=gecici->sonraki;
			}
		if(sayac!=4)break;
		sayac=0;
	}
	
	if(sayac==0)printf("\n...COMPLETE GRAF...");
	else printf("\n...COMPLETE GRAF DEGIL...");
}

void Kenar_Sayisi()//TOPLAM KENAR SAYISI
{
		Row *gecici;
	int i,sayac=0;
	for(i=0;i<MAXROW;i++)
	{
			gecici=tablo.satirlar[i].sonraki;
			while(gecici!=NULL)
			{
				sayac++;
				gecici=gecici->sonraki;
			}
	}
	
	printf("\n...Grafin Kenar Sayisi = %d ...",sayac/2);
}

char color[MAXROW],pred[MAXROW];
int time,d[MAXROW],f[MAXROW],stack[MAXROW],i=0;

void DFSVisit(int u);
//DFS ALGORÝTMASINA GÖRE DOLAÞMA
void DFS(){
	
	for(int i=0;i<MAXROW;i++)
	{
		color[i]='W';
		pred[i]=NULL;
	}
	time=0;
	
	for(int u=0;u<MAXROW;u++)
	{
		if(color[u]=='W')
		DFSVisit(u);
	}
}
void DFSVisit(int u){
	Row *gecici;
	color[u]='G';
	stack[i]=u;//YIÐIN A EKLEME
	i++;	
	d[u]=++time;//ULAÞILANLAR

	gecici=tablo.satirlar[u].sonraki;
	while(gecici!=NULL)
	{	
		if(color[gecici->numara]=='W')
		{	
			pred[gecici->numara]=u;
			DFSVisit(gecici->numara);
		}
		gecici=gecici->sonraki;
	}
	
	color[u]='B';
	i--;
	printf("%d ",stack[i]);//YIÐINDAN ÇIKARMA
	
	f[u]=++time;//ÝÞLENENLER
	
}




main()
{
	FILE *fp;
	int komsuluk_matrisi[MAXROW][MAXROW],sayi;
	fp=fopen("komsuluk_matrisi.txt","r");
	for(int i=0;i<MAXROW;i++)//DOSYADAN VERÝ OKUMA
	{
		for(int j=0;j<MAXROW;j++)
		{
			fscanf(fp,"%d ",&komsuluk_matrisi[i][j]);
		}
	}
	fclose(fp);
	baslangic_deger_atama();
	Liste_Kontrol(komsuluk_matrisi);
	
	printf(" Komsuluk Listesi..\n");
	Tablo_Listele();
	printf("Derecesini Ogrenmek Istediginiz Dugumu Giriniz..");
	scanf("%d",&sayi);
	Dugum_derecesi(sayi);
	Kenar_Sayisi();
	Complete_Graf();
	printf("\n...DFS Algoritmasina Gore Dolasma (Ilk Islenenden Son Islenene Dogru)...\n");
	DFS();
	printf("\n...Ulasma Zamanlari (d dizisi)...\n");
	for(int t=0;t<5;t++)
		printf("  %d.elemana %d.adimda ulasildi\n",t,d[t]);
	printf("\n...Isleme Zamanlari (f dizisi)...\n");
		for(int q=0;q<5;q++)
		printf("  %d.eleman %d.adimda islendi\n",q,f[q]);
	
}


