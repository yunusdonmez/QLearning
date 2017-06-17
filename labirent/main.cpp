#include <iostream>
#include <stdio.h>
#include<graphics.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
class olustur
{
    int kordx=225;
    int kordy=25;
public:
    int odaSayisi()
    {
        FILE *dosya=fopen("input.txt","r");
        char sayi[100];
        int sayac=0;
        fscanf(dosya,"%d",&sayi);
        while(fgets(sayi,100,dosya))
            sayac++;
        fclose(dosya);
        return sayac;
    }
    void rOlustur(int **rmatris,int boyut,int hedef)
    {
        FILE *dosya=fopen("input.txt","r");

        int sayac=0;
        int sayi;
        for(int i=0; i<boyut; i++)
        {
            for(int j=0; j<boyut; j++)
            {
                rmatris[i][j]=-1;
            }
        }
        while(1)
        {
            if(sayac==boyut)
                break;
            fscanf(dosya,"%d",&sayi);
            char a=fgetc(dosya);
            rmatris[sayac][sayi]=0;
            if(sayi==hedef)
                rmatris[sayac][sayi]=100;
            if(a=='\n')
            {
                sayac++;
            }

        }
        printf("\ndosya sonuna ulasildi %d\n\n",sayac);
        rmatris[hedef][hedef]=100;
        fclose(dosya);

    }
    int renBuyuk(int dizi[], int boyut)
    {
        int tmp[boyut];
        int indis=0;
        for(int i=0; i<boyut; i++)
        {
            tmp[i]=-1;
        }
        for(int i=0; i<boyut; i++)
        {
            if(dizi[i]==0 || dizi[i]==100)
            {
                tmp[indis]=i;
                indis++;
            }
        }
        return tmp[rand()%(indis)];
    }
    double qenBuyuk(int rdizi[],double qdizi[], int boyut)
    {
        double enb=0;
        int indis=0;
        int tmp[boyut];
        for(int i=0; i<boyut; i++)
        {
            tmp[i]=-1;
        }
        for(int i=0; i<boyut; i++)
        {
            if(rdizi[i]!=-1)
            {
                tmp[indis]=i;
                indis++;
            }
        }
        enb=qdizi[tmp[0]];
        for(int i=0; i<indis; i++)
        {
            if(enb<qdizi[tmp[i]])
                enb=qdizi[tmp[i]];
        }
        return enb;

    }
    void qOlustur(int **rmatris,int boyut,int giris,int cikis,int iterasyon)
    {
        int durum=giris;
        int iterasyon2=iterasyon;
        double **qmatris;
        qmatris=(double**)malloc(boyut*sizeof(double));
        for(int i=0; i<boyut; i++)                          ///matrisi boyutlandırma
            qmatris[i]=(double*)malloc(boyut*sizeof(double));

        for(int i=0; i<boyut; i++)
        {
            for(int j=0; j<boyut; j++)
            {
                qmatris[i][j]=0;
            }
        }
        do
        {
            int hedef=renBuyuk(rmatris[durum],boyut);
            qmatris[durum][hedef]=(double)rmatris[durum][hedef]+0.8*qenBuyuk(rmatris[hedef],qmatris[hedef],boyut);
            if(durum==cikis)
            {
                iterasyon--;
                printf("%d. iterasyon\n",iterasyon);
                durum=giris;
                continue;
            }
            durum=hedef;
        }while(iterasyon!=0);
        qYazdir(qmatris,boyut,iterasyon2);
        pathBul(qmatris,boyut,giris,cikis);
    }
    int okuGiris()
    {
        char x;
        int i=0;
        char a[20];
        int sayi=0,kontrol=0;
        outtextxy(20,25,"Giris kutusunu girin:");
        bar(220,20,300,50);
        a[0]='\0';
        do
        {
            do
            {
                x=getch();
                while((a[0]=='\0' && x==13 )|| (a[0]=='\0' && x==8))
                {
                    MessageBoxA(NULL,"Lutfen once bir sayi giriniz","",MB_OK);
                    x=getch();
                    kontrol=0;
                }
                kontrol++;
                if(x==13 || x==8)  ///enter ile backspace tu?u için döngüyü durdurma
                    break;
                if((x>57 || x<48 ) )
                {
                    MessageBoxA(NULL,"Lutfen sayi giriniz","",MB_OK);///uyary verme
                }
            }while(x>57 || x<48); ///girilen de?erin sayy oldu?unu kontrol etme
            if(x==8) ///sayy silmek
            {
                a[i-1]='\0';
                i--;
                bar(220,20,300,50);
            }
            else if(x!=13)  ///yedek diziye (a dizisine) de?er atamak
            {
                a[i]=x;
                a[i+1]='\0';
                i++;
            }
            outtextxy(kordx,kordy,a);///girilen sayyyy ekrana yazdyrma
        }while(x!=13);
        for(i=0; i<strlen(a); i++)
            sayi=sayi*10+a[i]-48;
        return sayi;
    }
    int okuCikis()
    {
        kordy+=50;
        char x;
        int i=0;
        char a[20];
        int sayi=0,kontrol=0;
        outtextxy(20,80,"Cikis kutusunu girin:");
        bar(220,70,300,100);
        a[0]='\0';
        do
        {
            do
            {
                x=getch();
                while((a[0]=='\0' && x==13 )|| (a[0]=='\0' && x==8))
                {
                    MessageBoxA(NULL,"Lutfen once bir sayi giriniz","",MB_OK);
                    x=getch();
                    kontrol=0;
                }
                kontrol++;
                if(x==13 || x==8)  ///enter ile backspace tu?u için döngüyü durdurma
                    break;
                if((x>57 || x<48 ) )
                {
                    MessageBoxA(NULL,"Lutfen sayi giriniz","",MB_OK);///uyary verme
                }
            }while(x>57 || x<48); ///girilen de?erin sayy oldu?unu kontrol etme

            if(x==8) ///sayy silmek
            {
                a[i-1]='\0';
                i--;
                bar(220,70,300,100);
            }
            else if(x!=13)  ///yedek diziye (a dizisine) de?er atamak
            {
                a[i]=x;
                a[i+1]='\0';
                i++;
            }
            outtextxy(kordx,kordy,a);///girilen sayyyy ekrana yazdyrma
        }while(x!=13);
        for(i=0; i<strlen(a); i++)
            sayi=sayi*10+a[i]-48;
        kordy-=50;
        return sayi;
    }
    int okuIterasyon()
    {
        kordx+=630;
        kordy+=23;
        char x;
        int i=0;
        char a[20];
        int sayi=0,kontrol=0;
        outtextxy(600,50,"Iterasyon sayisini girin:");
        bar(950,40,850,70);
        a[0]='\0';
        do
        {
            do
            {
                x=getch();
                while((a[0]=='\0' && x==13 )|| (a[0]=='\0' && x==8))
                {
                    MessageBoxA(NULL,"Lutfen once bir sayi giriniz","",MB_OK);
                    x=getch();
                    kontrol=0;
                }
                kontrol++;
                if(x==13 || x==8)  ///enter ile backspace tu?u için döngüyü durdurma
                    break;
                if((x>57 || x<48 ) )
                {
                    MessageBoxA(NULL,"Lutfen sayi giriniz","",MB_OK);///uyary verme
                }
            }while(x>57 || x<48); ///girilen de?erin sayy oldu?unu kontrol etme
            if(x==8) ///sayy silmek
            {
                a[i-1]='\0';
                i--;
                bar(950,40,850,70);
            }
            else if(x!=13)  ///yedek diziye (a dizisine) de?er atamak
            {
                a[i]=x;
                a[i+1]='\0';
                i++;
            }
            outtextxy(kordx,kordy,a);///girilen sayyyy ekrana yazdyrma
        }while(x!=13);
        for(i=0; i<strlen(a); i++)
            sayi=sayi*10+a[i]-48;
        return sayi;
    }
    void ciz(int **rmatris,int boyut,int cikis,int giris)
    {
        int x=100;
        int y=120;
        int aralik=600;
        setcolor(BLACK);
        for(int i=0; i<boyut*boyut; i++)
        {
            for(int j=0; j<boyut*boyut; j++)
            {
                if(rmatris[i][j]==-1)
                {
                    if((i-j)==-1 &&  j%boyut!=0) //dikey
                    {
                        line(x+(j%boyut)*(aralik/boyut),y+(i/boyut)*(aralik/boyut),x+(j%boyut)*(aralik/boyut),y+(j/boyut)*(aralik/boyut)+(aralik/boyut));
                    }
                    if(i-j==-1*boyut)//yatay
                    {
                        line(x+(j%boyut)*(aralik/boyut),y+(j/boyut)*(aralik/boyut),x+(j%boyut)*(aralik/boyut)+(aralik/boyut),y+(j/boyut)*(aralik/boyut));
                    }
                }
            }
        }//dış çerçeve
        line(x,y,x+aralik,y);//yatay
        line(x,y+aralik,x+aralik,y+aralik);
        line(x,y,x,y+aralik);
        line(x+aralik,y+aralik,x+aralik,y);//dikey
        setcolor(3);
        if(giris%boyut==0)
        {
            line(x,y+(giris/boyut)*(aralik/boyut)+5,x,y+(giris/boyut)*(aralik/boyut)+(aralik/boyut)-5);
        }
        else if(giris%boyut==boyut-1)
        {
            line(x+boyut*(aralik/boyut),y+(giris/boyut)*(aralik/boyut)+5,x+boyut*(aralik/boyut),y+(giris/boyut)*(aralik/boyut)+(aralik/boyut)-5);
        }
        else if(giris/boyut==0 && giris%boyut<boyut)
        {
            line(x+giris*(aralik/boyut)+5,y,x+giris*(aralik/boyut)+aralik/boyut-5,y);
        }
        else if(giris/boyut==(boyut-1) && giris%boyut<boyut)
        {
            line(x+(giris%boyut)*(aralik/boyut),y+aralik,x+(giris%boyut)*(aralik/boyut)+aralik/boyut,y+aralik);
        }
        if(cikis%boyut==0)
        {
            line(x,y+(cikis/boyut)*(aralik/boyut)+5,x,y+(cikis/boyut)*(aralik/boyut)+(aralik/boyut)-5);
        }
        else if(cikis%boyut==boyut-1)
        {
            line(x+boyut*(aralik/boyut),y+(cikis/boyut)*(aralik/boyut)+5,x+boyut*(aralik/boyut),y+(cikis/boyut)*(aralik/boyut)+(aralik/boyut)-5);
        }
        else if(cikis/boyut==0 && cikis%boyut<boyut)
        {
            line(x+cikis*(aralik/boyut),y,x+cikis*(aralik/boyut)+aralik/boyut,y);
        }
        else if(cikis/boyut==(boyut-1) && cikis%boyut<boyut)
        {
            line(x+(cikis%boyut)*(aralik/boyut),y+aralik,x+(cikis%boyut)*(aralik/boyut)+aralik/boyut,y+aralik);
        }
    }
    void rYazdir(int **rmatris,int boyut)
    {
        FILE *dosya2=fopen("outR.txt","w");
        for(int i=0; i<boyut; i++)
        {
            for(int j=0; j<boyut; j++)
            {
                fprintf(dosya2,"%3d ",rmatris[i][j]);
            }
            fprintf (dosya2,"\n");
        }
        fclose(dosya2);
    }
    void qYazdir(double **qmatris,int boyut,int iterasyon)
    {
        FILE *dosya3=fopen("outQ.txt","w");
        fprintf(dosya3,"İterasyon Sayisi:%d\n",iterasyon);
        for(int i=0; i<boyut; i++)
        {
            for(int j=0; j<boyut; j++)
            {
                fprintf(dosya3,"%.02lf ",qmatris[i][j]);
            }
            fprintf (dosya3,"\n");
        }
        fclose(dosya3);
    }
    void pathBul(double **qmatris,int boyut,int giris,int cikis)
    {
        FILE *dosya4=fopen("outPath.txt","w");
        double enb=0;
        int durum=giris;
        int indis=giris;
        int boyutKok=sqrt(boyut);
        int x=100;
        int y=120;
        int aralik=600;
        while(1)
        {
            for(int j=0; j<boyut; j++)
            {
                if(qmatris[durum][j]>enb)
                {
                    enb=qmatris[durum][j];
                    indis=j;
                }
            }
            enb=0;
            setcolor(RED);
            if(fabs(durum-indis)==1)
            {

                circle(x+(giris%boyutKok)*(aralik/boyutKok)+(aralik/boyutKok)/2,y+(giris/boyutKok)*(aralik/boyutKok)+(aralik/boyutKok)/2,(aralik/boyutKok)/12);
                circle(x+(cikis%boyutKok)*(aralik/boyutKok)+(aralik/boyutKok)/2,y+(cikis/boyutKok)*(aralik/boyutKok)+(aralik/boyutKok)/2,(aralik/boyutKok)/12);
                circle(x+(cikis%boyutKok)*(aralik/boyutKok)+(aralik/boyutKok)/2,y+(cikis/boyutKok)*(aralik/boyutKok)+(aralik/boyutKok)/2,(aralik/boyutKok)/16);
                circle(x+(cikis%boyutKok)*(aralik/boyutKok)+(aralik/boyutKok)/2,y+(cikis/boyutKok)*(aralik/boyutKok)+(aralik/boyutKok)/2,(aralik/boyutKok)/24);
                line(x+(durum%boyutKok)*(aralik/boyutKok)+(aralik/boyutKok)/2,y+(durum/boyutKok)*(aralik/boyutKok)+(aralik/boyutKok)/2,x+(indis%boyutKok)*(aralik/boyutKok)+(aralik/boyutKok)/2,y+(durum/boyutKok)*(aralik/boyutKok)+(aralik/boyutKok)/2);
            }
            else
            {
                line(x+(indis%boyutKok)*(aralik/boyutKok)+(aralik/boyutKok)/2,y+(durum/boyutKok)*(aralik/boyutKok)+(aralik/boyutKok)/2,x+(indis%boyutKok)*(aralik/boyutKok)+(aralik/boyutKok)/2,y+(indis/boyutKok)*(aralik/boyutKok)+(aralik/boyutKok)/2);
            }
            fprintf(dosya4,"%d ",durum);
            durum=indis;
            if(cikis==durum)
                break;
        }
        fprintf(dosya4,"%d ",cikis);
        fclose(dosya4);
    }

};
int main()
{
    initwindow( 1250, 800);
    setbkcolor(3);
    setlinestyle(8,8,4);
    cleardevice();
    setcolor(BLACK);
    olustur labirent;
    srand(time(NULL));
    int boyut;
    boyut=labirent.odaSayisi();
    printf("%d",boyut);
    int giris,cikis,iterasyon;
    do
    {
        giris=labirent.okuGiris();
        if(giris>boyut-1)
        {
            MessageBoxA(NULL,"Girilen deger cok yuksek","",MB_OK);
        }
    }while(giris>boyut-1);
    do
    {
        cikis=labirent.okuCikis();
        if(cikis>boyut-1)
        {
            MessageBoxA(NULL,"Girilen deger cok yuksek","",MB_OK);
        }
    }while(cikis>boyut-1);

    iterasyon=labirent.okuIterasyon();

    int **rmatris;
    rmatris=(int**)malloc(boyut*sizeof(int));
    for(int i=0; i<boyut; i++)                          ///matrisi boyutlandırma
        rmatris[i]=(int*)malloc(boyut*sizeof(int));

    labirent.rOlustur(rmatris,boyut,cikis);
    labirent.rYazdir(rmatris,boyut);
    labirent.ciz(rmatris,sqrt(boyut),cikis,giris);
    labirent.qOlustur(rmatris,boyut,giris,cikis,iterasyon);
    getch();
    closegraph();
    return 0;
}
