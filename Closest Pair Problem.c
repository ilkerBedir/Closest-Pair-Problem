#include <stdio.h>
#include<conio.h>
#include<math.h>
#include<float.h>


struct nokta{//noktay� struct olarak ald�m.
	int x;//x eksenindeki deger
	int y;//y eksenindeki deger
};
float min=FLT_MAX;//uzaklik i�in gerekli olan min degeri i�in en b�y�k float deger
struct nokta ikili[2];//en yakin noktayi tutmak i�in olusturdugum dizi;
struct nokta *ikili_degis(int x1,int y1,int x2,int y2);//bulunan mine g�re nokta degistirme fonksiyonu
float min_bulma(struct nokta dizi[100],int bas,int bit,float min);//noktalar aras�nda min degeri bulan
int min_kiyaslama(float a,float b);//min k�yaslama fonksiyonu
float uzaklik_bulma(int x1,int y1,int x2,int y2);//2 nokta aras�nda uzaklik bulan fonksiyon
float arada_kalan(struct nokta dizi[100],int bas,int bit,int medyan,float min){//bulunan min degerlerine g�re medyan�n 2 taraf�n� kontrol eden
	int i;//d�ng� indisi
	struct nokta dsol[6];//medyan ile medyan-min degerleri aras�nda kalan noktalar i�in bir dizi
	struct nokta dsag[6];//medyan ile medyan+min degerleri aras�nda kalan noktalar i�in bir dizi
	float top,cik;//top=[medyan].x+min ;cik=[medyan].x-min
	int k=0;//dizi indisi
	int j=0;//dizi indisi
	int a,b;//dizi indisleri
	float uz;//uzaklik degerleri i�in tutulan degisken
	top=dizi[medyan].x+min;//iki b�lgelerin kar��la�t�r�lmas� sonucu bulunan min degeri ile farkl� b�lgelerdeki nokta kontrol� i�in degisken
	cik=dizi[medyan].x-min;
	for(i=bas;i<bit+1;i++){
	if(dizi[medyan].x>=dizi[i].x && dizi[i].x>=cik){//medyan ve medyan- min b�lgesi
		dsol[j]=dizi[i];//bu b�lgede olan noktalar� yeni bir diziye atad�m
		j++;//dizi artt�rma indisim
	}
	else if(dizi[medyan].x<dizi[i].x && dizi[i].x<=top) {//medyan ve medyan+min b�lgesinde kalan b�lge
		dsag[k]=dizi[i];//bu b�lgede olan noktalar� yeni bir diziye atad�m
		k++;//dizi artt�rma indisim
	}
    }
    for(a=0;a<j;a++){//burdaki d�ng� ile 2 farkl� bolgede kalan noktalar�n uzakliklarini min ile k�yasl�yorum k���k ise min ve noktalar� degistiriyorum
    	for(b=0;b<k;b++){
    		uz=uzaklik_bulma(dsol[a].x,dsol[a].y,dsag[b].x,dsag[b].y);//uzaklik buluyorum
    		if(min_kiyaslama(min,uz)==1){//min ile buldugum uzakligi k�yasl�yorum
    		min=uz;//eger kucukse min degerimi degistiriyorum
    		ikili_degis(dsol[a].x,dsol[a].y,dsag[b].x,dsag[b].y);//burada nokta degistiriyorum
	}
}
}
return min;//min degerini d�nd�r�yorum
}
float en_kisa_ikili(struct nokta dizi[100],int bas,int bit,float min ){//burada en k�c�k noktalar� bulmak i�in olusturdugum recursive fonksiyon
	int medyan;//dizinin medyan degeri
	float mn;//min kontrol� i�in bir min degeri
	medyan=((bit-bas)/2)+bas;//medyani (son-ilk)/2+ilk diye buluyorum
	if(bas<bit-2){//dizinin nokta say�s� 3 ten k���k olana kadar diziye medyanlar ile ay�r�yorum.
	    min=en_kisa_ikili(dizi,bas,medyan,min);//medyan�n sol tarafi;medyan dahil
	    min=en_kisa_ikili(dizi,medyan+1,bit,min);//medyanin sag tarafi
    }
    mn=min_bulma(dizi,bas,bit,min);//b�lgelein kendi aralar�nda en k�sa noktas�n� buluyorum
    if(min_kiyaslama(mn,min)==1){//bu noktay� min ile k�yasl�yorum eger minden k�c�kse mini degistiriyorum,degilse degistirmiyorum
    if(bit-bas>2){//burada ise medyan�n ay�rd�g� 2 farkl� b�lgeye bak�yorum
    min=arada_kalan(dizi,bas,bit,medyan,min);
    }
    return min; //min donduruyorum
}
else{
	min=mn;
	if(bit-bas>2){//burada ise medyan�n ay�rd�g� 2 farkl� b�lgeye bak�yorum
	min=arada_kalan(dizi,bas,bit,medyan,min);
   }
	return min;//min d�nd�ruyorum
}
}
float min_bulma(struct nokta dizi[100],int bas,int bit,float min){//burada noktalar aras�ndaki uzakliklar� kontrol ediyorum.brute force ile
	float uz;//uzaklik degiskenim
	int i,j;//d�ng� indislerim
	if(bit-bas==1){//eger medyanlar� b�lerek olu�turdugumuz b�lgede sadece 2 nokta varsa,bu 2 nokta o b�lge i�in min degeri olacak
		uz=uzaklik_bulma(dizi[bas].x,dizi[bas].y,dizi[bit].x,dizi[bit].y);//bu 2 noktan�n uzakl�g�n� buluyorum
		if(min_kiyaslama(min,uz)==1){//o s�rada var olan min ile k�yasl�yorum,eger uz min den k�c�k ise 
		ikili_degis(dizi[bas].x,dizi[bas].y,dizi[bit].x,dizi[bit].y);//noktalar� g�ncelliyorum
		min=uz;//min degerini guncelliyorum
	}
	}
	else if(bit-bas==2){//burada ise 3 noktal� b�lgeler i�in uzakl�k kontrol� yap�yorum
			for(i=bas;i<bit+1;i++){
			for(j=i+1;j<bit+1;j++){
				uz=uzaklik_bulma(dizi[i].x,dizi[i].y,dizi[j].x,dizi[j].y);//noktalar aras�nda uzakl�k buluyorum
				if(min_kiyaslama(min,uz)==1){//uz minden k���k ise mini g�ncelliyorum
				min=uz;//guncelleme
		        ikili_degis(dizi[i].x,dizi[i].y,dizi[j].x,dizi[j].y);//burada nokta degistiriyorum
	}
			}
		}
	}
		return min;//min degeri d�nd�r�yorum
}
struct nokta *ikili_degis(int x1,int y1,int x2,int y2){//iki nokta al�yorum ve bunlar� ikili[2] diziye at�yorum ve bu diziyi d�nd�r�yorum
	ikili[0].x=x1;
	ikili[0].y=y1;
	ikili[1].x=x2;
	ikili[1].y=y2;
	return ikili;
}
int min_kiyaslama(float a,float b){//burada asl�nda uzaklik k�yasl�yorum
 	if(a>=b){
		return 1;//b
	}
	else{
		return 0;//a
	}
}
float uzaklik_bulma(int x1,int y1,int x2,int y2){//iki nokta aras�nda uzakl�k buluyorum ve uzaklik d�nd�r�yorum
	float uzaklik;
	uzaklik=sqrt(abs((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
	return uzaklik;
}
void merge_conqueror(struct nokta dizi[100], int baslangic, int orta, int bitis)//burada b�ld�kleri dizileri kontrol ediyorum ve degistiriyorum
{
    int i, j,k;//dizi indislerim 
    struct nokta dsol[orta-baslangic+1], dsag[ bitis-orta];//gecici dizilerim
    for (i = 0; i < (orta-baslangic+1); i++){//gecici dizilere dizideki elemanlar� at�yorum
        dsol[i] = dizi[baslangic + i];
    }
    for (j = 0; j < bitis-orta; j++){//gecici dizilere dizideki elemanlar� at�yorum
        dsag[j] = dizi[orta + 1+ j];
}
    i = 0; //indisleri s�f�rl�yorum
    j = 0;
    k=baslangic;
    while (i < (orta-baslangic+1) && j < bitis-orta )// burada iki ge�i�i dizinin noktalar�n�n x degerlerini konntorl ediyorum ve dizimin s�ralamas�n� g�ncelliyorum
    {
        if (dsol[i].x <= dsag[j].x)//soldaki dizinin x'i sagdankinden kucukse soldaki dizinin indisi artar
        {
            dizi[k] = dsol[i];
            i++;
        }
        else
        {
            dizi[k] = dsag[j];//tam tersi
            j++;
        }
        k++;
    }
      while (i < (orta-baslangic+1) || j <  bitis-orta )//eger bir tane nokta kald�ysa onu diziye at�yoruz
    {
    	if(j<i){
    	dizi[k] = dsag[j];
        j++;
    }
    else{
    	dizi[k] = dsol[i];
        i++;
	}
	 k++;
    }
}	
void merge_sort_divide(struct nokta dizi[], int baslangic, int bitis)//dizimi s�ralamak i�in merge sort kulland�m,merge sortu kullanmam�n nedeni ise 3 durumda da ayn� karmas�kl�g� kullanmas�(n.log(n))
{    
    int orta;//diziyi b�lecegim icin olusturdugum indis
    orta = baslangic+(bitis-baslangic)/2;//orta indisi bulma 
    if (baslangic < bitis)//bitis ve baslangic ayn� olana kadar yasni tek eleman olana kadar recursive yap�yorum b�l�yorum
    {
        merge_sort_divide(dizi, baslangic, orta);//recursive
        merge_sort_divide(dizi, orta+1, bitis);
    }
     merge_conqueror(dizi, baslangic, orta, bitis);//burada b�ld�kleri dizileri kontrol ediyorum ve degistiriyorum
     
}

int main(){

int i,n;//i index,n dizi uzunlugu
struct nokta nokta_dizi[100];//noktalar�n olusturdugu dizi
FILE *f;
int sayac=0;
char ch;
f=fopen("Input.txt","r");
while(!feof(f)){
	ch=fgetc(f);
	if(ch== '\n'){
		sayac++;
	}
}
rewind(f);
for(i=0;i<sayac;i++){
	fscanf(f,"%d %d",&nokta_dizi[i].x,&nokta_dizi[i].y);
}
printf("Siralanmamis noktalar \n");
for(i=0;i<sayac;i++){//s�ral� dizi yazd�rma
	printf("%d .nci noktanin x koordinati=%d   ",i,nokta_dizi[i].x);
	printf("%d .nci noktanin y koordinati=%d \n",i,nokta_dizi[i].y);
}
merge_sort_divide(nokta_dizi,0,sayac-1);//diziyi s�ralama
printf("Siralanmamis noktalar=\n");
for(i=0;i<sayac;i++){//s�ral� dizi yazd�rma
	printf("%d .nci noktanin x koordinati=%d   ",i,nokta_dizi[i].x);
	printf("%d .nci noktanin y koordinati=%d",i,nokta_dizi[i].y);
	printf("\n");	
}
if(n<=3){//eger eleman sayisi 3 ve 3ten k���kse bruteforce direkt y�nlensin
min=min_bulma(nokta_dizi,0,sayac-1,min);
printf("uzaklik= %.4f\n",min);
printf("noktalar=");
for(i=0;i<2;i++){
	printf("( %d ",ikili[i].x);
	printf(",");
	printf("%d )\t ",ikili[i].y);
}
}
else{//eger degilse recursive fonksiyonuna y�nelsin
min=en_kisa_ikili(nokta_dizi,0,sayac-1,min );
printf("uzaklik= %.4f\n",min);
printf("noktalar=");
for(i=0;i<2;i++){
	printf("(%d",ikili[i].x);
	printf(",");
	printf("%d)\t ",ikili[i].y);
}
}
return 0;
}
