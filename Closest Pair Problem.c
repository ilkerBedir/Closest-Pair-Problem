#include <stdio.h>
#include<conio.h>
#include<math.h>
#include<float.h>


struct nokta{//noktayý struct olarak aldým.
	int x;//x eksenindeki deger
	int y;//y eksenindeki deger
};
float min=FLT_MAX;//uzaklik için gerekli olan min degeri için en büyük float deger
struct nokta ikili[2];//en yakin noktayi tutmak için olusturdugum dizi;
struct nokta *ikili_degis(int x1,int y1,int x2,int y2);//bulunan mine göre nokta degistirme fonksiyonu
float min_bulma(struct nokta dizi[100],int bas,int bit,float min);//noktalar arasýnda min degeri bulan
int min_kiyaslama(float a,float b);//min kýyaslama fonksiyonu
float uzaklik_bulma(int x1,int y1,int x2,int y2);//2 nokta arasýnda uzaklik bulan fonksiyon
float arada_kalan(struct nokta dizi[100],int bas,int bit,int medyan,float min){//bulunan min degerlerine göre medyanýn 2 tarafýný kontrol eden
	int i;//döngü indisi
	struct nokta dsol[6];//medyan ile medyan-min degerleri arasýnda kalan noktalar için bir dizi
	struct nokta dsag[6];//medyan ile medyan+min degerleri arasýnda kalan noktalar için bir dizi
	float top,cik;//top=[medyan].x+min ;cik=[medyan].x-min
	int k=0;//dizi indisi
	int j=0;//dizi indisi
	int a,b;//dizi indisleri
	float uz;//uzaklik degerleri için tutulan degisken
	top=dizi[medyan].x+min;//iki bölgelerin karþýlaþtýrýlmasý sonucu bulunan min degeri ile farklý bölgelerdeki nokta kontrolü için degisken
	cik=dizi[medyan].x-min;
	for(i=bas;i<bit+1;i++){
	if(dizi[medyan].x>=dizi[i].x && dizi[i].x>=cik){//medyan ve medyan- min bölgesi
		dsol[j]=dizi[i];//bu bölgede olan noktalarý yeni bir diziye atadým
		j++;//dizi arttýrma indisim
	}
	else if(dizi[medyan].x<dizi[i].x && dizi[i].x<=top) {//medyan ve medyan+min bölgesinde kalan bölge
		dsag[k]=dizi[i];//bu bölgede olan noktalarý yeni bir diziye atadým
		k++;//dizi arttýrma indisim
	}
    }
    for(a=0;a<j;a++){//burdaki döngü ile 2 farklý bolgede kalan noktalarýn uzakliklarini min ile kýyaslýyorum küçük ise min ve noktalarý degistiriyorum
    	for(b=0;b<k;b++){
    		uz=uzaklik_bulma(dsol[a].x,dsol[a].y,dsag[b].x,dsag[b].y);//uzaklik buluyorum
    		if(min_kiyaslama(min,uz)==1){//min ile buldugum uzakligi kýyaslýyorum
    		min=uz;//eger kucukse min degerimi degistiriyorum
    		ikili_degis(dsol[a].x,dsol[a].y,dsag[b].x,dsag[b].y);//burada nokta degistiriyorum
	}
}
}
return min;//min degerini döndürüyorum
}
float en_kisa_ikili(struct nokta dizi[100],int bas,int bit,float min ){//burada en kücük noktalarý bulmak için olusturdugum recursive fonksiyon
	int medyan;//dizinin medyan degeri
	float mn;//min kontrolü için bir min degeri
	medyan=((bit-bas)/2)+bas;//medyani (son-ilk)/2+ilk diye buluyorum
	if(bas<bit-2){//dizinin nokta sayýsý 3 ten küçük olana kadar diziye medyanlar ile ayýrýyorum.
	    min=en_kisa_ikili(dizi,bas,medyan,min);//medyanýn sol tarafi;medyan dahil
	    min=en_kisa_ikili(dizi,medyan+1,bit,min);//medyanin sag tarafi
    }
    mn=min_bulma(dizi,bas,bit,min);//bölgelein kendi aralarýnda en kýsa noktasýný buluyorum
    if(min_kiyaslama(mn,min)==1){//bu noktayý min ile kýyaslýyorum eger minden kücükse mini degistiriyorum,degilse degistirmiyorum
    if(bit-bas>2){//burada ise medyanýn ayýrdýgý 2 farklý bölgeye bakýyorum
    min=arada_kalan(dizi,bas,bit,medyan,min);
    }
    return min; //min donduruyorum
}
else{
	min=mn;
	if(bit-bas>2){//burada ise medyanýn ayýrdýgý 2 farklý bölgeye bakýyorum
	min=arada_kalan(dizi,bas,bit,medyan,min);
   }
	return min;//min döndüruyorum
}
}
float min_bulma(struct nokta dizi[100],int bas,int bit,float min){//burada noktalar arasýndaki uzakliklarý kontrol ediyorum.brute force ile
	float uz;//uzaklik degiskenim
	int i,j;//döngü indislerim
	if(bit-bas==1){//eger medyanlarý bölerek oluþturdugumuz bölgede sadece 2 nokta varsa,bu 2 nokta o bölge için min degeri olacak
		uz=uzaklik_bulma(dizi[bas].x,dizi[bas].y,dizi[bit].x,dizi[bit].y);//bu 2 noktanýn uzaklýgýný buluyorum
		if(min_kiyaslama(min,uz)==1){//o sýrada var olan min ile kýyaslýyorum,eger uz min den kücük ise 
		ikili_degis(dizi[bas].x,dizi[bas].y,dizi[bit].x,dizi[bit].y);//noktalarý güncelliyorum
		min=uz;//min degerini guncelliyorum
	}
	}
	else if(bit-bas==2){//burada ise 3 noktalý bölgeler için uzaklýk kontrolü yapýyorum
			for(i=bas;i<bit+1;i++){
			for(j=i+1;j<bit+1;j++){
				uz=uzaklik_bulma(dizi[i].x,dizi[i].y,dizi[j].x,dizi[j].y);//noktalar arasýnda uzaklýk buluyorum
				if(min_kiyaslama(min,uz)==1){//uz minden küçük ise mini güncelliyorum
				min=uz;//guncelleme
		        ikili_degis(dizi[i].x,dizi[i].y,dizi[j].x,dizi[j].y);//burada nokta degistiriyorum
	}
			}
		}
	}
		return min;//min degeri döndürüyorum
}
struct nokta *ikili_degis(int x1,int y1,int x2,int y2){//iki nokta alýyorum ve bunlarý ikili[2] diziye atýyorum ve bu diziyi döndürüyorum
	ikili[0].x=x1;
	ikili[0].y=y1;
	ikili[1].x=x2;
	ikili[1].y=y2;
	return ikili;
}
int min_kiyaslama(float a,float b){//burada aslýnda uzaklik kýyaslýyorum
 	if(a>=b){
		return 1;//b
	}
	else{
		return 0;//a
	}
}
float uzaklik_bulma(int x1,int y1,int x2,int y2){//iki nokta arasýnda uzaklýk buluyorum ve uzaklik döndürüyorum
	float uzaklik;
	uzaklik=sqrt(abs((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
	return uzaklik;
}
void merge_conqueror(struct nokta dizi[100], int baslangic, int orta, int bitis)//burada böldükleri dizileri kontrol ediyorum ve degistiriyorum
{
    int i, j,k;//dizi indislerim 
    struct nokta dsol[orta-baslangic+1], dsag[ bitis-orta];//gecici dizilerim
    for (i = 0; i < (orta-baslangic+1); i++){//gecici dizilere dizideki elemanlarý atýyorum
        dsol[i] = dizi[baslangic + i];
    }
    for (j = 0; j < bitis-orta; j++){//gecici dizilere dizideki elemanlarý atýyorum
        dsag[j] = dizi[orta + 1+ j];
}
    i = 0; //indisleri sýfýrlýyorum
    j = 0;
    k=baslangic;
    while (i < (orta-baslangic+1) && j < bitis-orta )// burada iki geçiçi dizinin noktalarýnýn x degerlerini konntorl ediyorum ve dizimin sýralamasýný güncelliyorum
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
      while (i < (orta-baslangic+1) || j <  bitis-orta )//eger bir tane nokta kaldýysa onu diziye atýyoruz
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
void merge_sort_divide(struct nokta dizi[], int baslangic, int bitis)//dizimi sýralamak için merge sort kullandým,merge sortu kullanmamýn nedeni ise 3 durumda da ayný karmasýklýgý kullanmasý(n.log(n))
{    
    int orta;//diziyi bölecegim icin olusturdugum indis
    orta = baslangic+(bitis-baslangic)/2;//orta indisi bulma 
    if (baslangic < bitis)//bitis ve baslangic ayný olana kadar yasni tek eleman olana kadar recursive yapýyorum bölüyorum
    {
        merge_sort_divide(dizi, baslangic, orta);//recursive
        merge_sort_divide(dizi, orta+1, bitis);
    }
     merge_conqueror(dizi, baslangic, orta, bitis);//burada böldükleri dizileri kontrol ediyorum ve degistiriyorum
     
}

int main(){

int i,n;//i index,n dizi uzunlugu
struct nokta nokta_dizi[100];//noktalarýn olusturdugu dizi
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
for(i=0;i<sayac;i++){//sýralý dizi yazdýrma
	printf("%d .nci noktanin x koordinati=%d   ",i,nokta_dizi[i].x);
	printf("%d .nci noktanin y koordinati=%d \n",i,nokta_dizi[i].y);
}
merge_sort_divide(nokta_dizi,0,sayac-1);//diziyi sýralama
printf("Siralanmamis noktalar=\n");
for(i=0;i<sayac;i++){//sýralý dizi yazdýrma
	printf("%d .nci noktanin x koordinati=%d   ",i,nokta_dizi[i].x);
	printf("%d .nci noktanin y koordinati=%d",i,nokta_dizi[i].y);
	printf("\n");	
}
if(n<=3){//eger eleman sayisi 3 ve 3ten küçükse bruteforce direkt yönlensin
min=min_bulma(nokta_dizi,0,sayac-1,min);
printf("uzaklik= %.4f\n",min);
printf("noktalar=");
for(i=0;i<2;i++){
	printf("( %d ",ikili[i].x);
	printf(",");
	printf("%d )\t ",ikili[i].y);
}
}
else{//eger degilse recursive fonksiyonuna yönelsin
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
