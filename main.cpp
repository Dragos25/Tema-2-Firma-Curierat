///PROBLEMA 22
///FIRMA DE CURIERAT

#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <typeinfo>
#include <math.h>

using namespace std;

ifstream col("in_colete");
ifstream veh("in_vehicule");

int timp_curent=0;

class colet
{
private:
    int masa;
    int volum;
    bool rece;
    int lx,ly; ///locatie ridicare
    int dx,dy; ///locatie livrare
    int tr; ///timp ridicare
    int tl; ///timp maxim livrare
public:
    friend std::istream & operator >> (std::istream &in, colet &c)
    {
        in>>c.masa;
        in>>c.volum;
        string temp;
        in>>temp;
        if(temp=="rece") c.rece=true;
        else c.rece=false;
        in>>c.lx>>c.ly;
        in>>c.dx>>c.dy;
        in>>c.tr>>c.tl;
        return in;
    }
    friend std::ostream & operator << (std::ostream &out, const colet &c)
    {
    out<<"Masa:"<<c.masa<<endl;
    out<<"Volum:"<<c.volum<<endl;
    if(c.rece==true) out<<"Rece"<<endl;
    else out<<"Cald"<<endl;
    out<<"Locatie initiala: "<<c.lx<<" "<<c.ly<<endl;
    out<<"Destinatie: "<<c.dx<< " "<<c.dy<<endl;
    out<<"Ora ridicare: "<<c.tr<<endl;
    out<<"Ora livrare max: "<<c.tl<<endl;
    return out;
    }

    colet operator =(const colet &c)
    {
        masa=c.masa;
        volum=c.volum;
        rece=c.rece;
        lx=c.lx;
        ly=c.ly;
        dx=c.dx;
        dy=c.dy;
        tr=c.tr;
        tl=c.tl;
        return *this;
    }

    int getmasa(){return masa;}
    int getvolum(){return volum;}
    int getlx(){return lx;}
    int getly(){return ly;}
    int getdx(){return dx;}
    int getdy(){return dy;}
    int get_timpr(){return tr;}
    int get_timpliv(){return tl;}
    bool gettemp(){return rece;}
    int getdist(){return sqrt((lx-dx)*(lx-dx)+(ly-dy)*(ly-dy)); }


    ~colet()
    {
        masa=0;
        volum=0;
        lx=0;
        ly=0;
        dx=0;
        dy=0;
        tr=0;
        tl=0;
        rece=0;

    }
friend class vehicul;
friend class scuter;
friend class masina;
friend class duba;
};



class vehicul
{

protected:
    string nume;

    int viteza;
    int masa;
    int masaocupata;
    int volum;
    int volumocupat;
    int px, py;
    colet c[100];
    int nr_c;
public:
    vehicul()
    {
        masa=0;
        masaocupata=0;
        volum=0;
        volumocupat=0;
        px=-1;
        py=-1;
        nr_c=-1;
    }

    vehicul(int m, int v=0, int ppx=-1, int ppy=-1)
    {
        masaocupata=0;
        volumocupat=0;
        masa=m;
        volum=v;
        px=ppx;
        py=ppy;
        nr_c=-1;
    }
    friend istream &operator >>(istream &in, vehicul &v)
    {
        in>>v.masa;
        in>>v.volum;
        in>>v.px;
        in>>v.py;
        return in;
    }

   friend ostream &operator <<(ostream &out, const vehicul &v)
    {
        out<<"Viteza:"<<v.viteza<<endl;
        out<<"Masa maxima :"<<v.masa<<endl;
        out<<"Volum maxim: "<<v.volum<<endl;
        out<<"Coordonata x:"<<v.px<<endl;
        out<<"Coordonata y:"<<v.py<<endl;
        return out;
    }

    vehicul operator =(const vehicul &v)
    {
        nume=v.nume;
        masa=v.masa;
        masaocupata=v.masaocupata;
        volum=v.volum;
        volumocupat=v.volumocupat;
        px=v.px;
        py=v.py;
        nr_c=v.nr_c;
        for(int i=0;i<=nr_c;i++)
            c[i]=v.c[i];
        return *this;
    }

    virtual void afisare()
    {
        cout<<this;
    }

    virtual int deplasare_timp(int x, int y){}
    virtual int deplasare_distanta(int x, int y){}
    void actualizez_locatie(int x, int y)
    {
        px=x;
        py=y;
    }
    int incape(colet x)
    {
      if(x.masa+masaocupata>masa || x.volum+volumocupat>volum) return -1;
      return 1;
    }

    void adaug_colet(colet x)
    {

        masaocupata+=x.masa;
        volumocupat+=x.volum;
        nr_c++;
        c[nr_c]=x;
    }

    void afisez_colete()
    {
        for(int i=0;i<=nr_c;i++)
            cout<<c[i]<<endl;
    }

    int timp_liv_colete()
    {
        int t=0;
        for(int i=0;i<nr_c;i++){
            int dist_colet=c[i].getdist();
            t=t+deplasare_timp(c->lx,c->ly)+dist_colet/(viteza*0.27);}
        return t;
    }

    void livrez_colete()
    {
        for(int i=0;i<=nr_c;i++){
            int dist_colet=c[i].getdist();
            if(deplasare_timp(c->lx,c->ly)+dist_colet/(viteza*0.27)<=timp_curent)
            {
                cout<<"Un colet a fost livrat!"<<endl;
                cout<<c[i]<<endl;
                actualizez_locatie(c[i].dx, c[i].dy);
                for(int j=i;j<nr_c;j++)
                    c[j]=c[j+1];
                nr_c--;
            }


        }
    }

    void sortez_colete_urgenta()
    {
        if(nr_c==-1)
        {
            return;
        }
        for(int i=0;i<nr_c;i++)
            for(int j=i;j<=nr_c;j++)
                if(c[i].tl>c[j].tl)
        {
            colet aux=c[i];
            c[i]=c[j];
            c[j]=aux;
        }
    }

    void sortez_colete_apropiat()
    {
        if(nr_c==-1) return;
        for(int i=0;i<nr_c;i++)
            for(int j=i;j<=nr_c;j++)
                if(deplasare_distanta(c[i].dx,c[i].dy) > deplasare_distanta(c[j].dx,c[i].dy) )
        {
            colet aux=c[i];
            c[i]=c[j];
            c[j]=aux;
        }
    }

    void sortez_colete_ordine()
    {
        if(nr_c==-1) return;
        for(int i=0;i<nr_c;i++)
            for(int j=i;j<=nr_c;j++)
                if( c[i].tr > c[j].tr)
        {
            colet aux=c[i];
            c[i]=c[j];
            c[j]=aux;
        }

    }
    int getvolumg(){return volumocupat;}
    int getmasag(){return masaocupata;}
    int getvolum(){return volum;}
    int getmasa(){return masa;}
    int getX(){return px;}
    int getY(){return py;}
    int getviteza(){return viteza;}

    virtual ~vehicul()
    {

    }
};



class scuter:public vehicul
{
    public:
    scuter()
    {
        nume="scuter";
        viteza=20;

    }
    scuter(int m, int v=-1, int ppx=-1, int ppy=-1):vehicul(m,v,ppx,ppy)
    {

        viteza=20;


    }



    void afisare()
    {
        cout<<*this;
    }
    int deplasare_timp(int x, int y)
    {
        float vms=viteza*0.27;
        float dist=sqrt((px-x)*(px-x)+(py-y)*(py-y));
        int timp=dist/vms;
        return timp;
    }

    int deplasare_distanta(int x, int y)
    {
        float vms=viteza*0.27;
        float dist=sqrt((px-x)*(px-x)+(py-y)*(py-y));
        return dist;
    }

    ~scuter()
    {

    }
};

class masina:public vehicul
{
    public:
    masina()
    {
        nume="masina";
        viteza=10;
    }
    masina(int m, int v=-1, int ppx=-1, int ppy=-1):vehicul(m,v,ppx,ppy)
    {
        viteza=10;
    }

    void afisare()
    {
        cout<<*this;
    }

    int deplasare_timp(int x, int y)
    {
        float vms=viteza*0.27;
        float dist=abs(px-x)+abs(py-y);
        int timp=dist/vms;
        return timp;
    }
    int deplasare_distanta(int x, int y)
    {

        float vms=viteza*0.27;
        float dist=abs(px-x)+abs(py-y);
        return dist;
    }

    ~masina()
    {

    }
};

class duba:public vehicul
{
private:
    bool rece;
    public:
    duba()
    {
        nume="duba";
        viteza=5;
    }
    duba(int m, int v=0, int ppx=-1, int ppy=-1):vehicul(m,v,ppx,ppy)
    {
        viteza=5;
    }
   friend istream &operator >>(istream &in, duba &v)
    {
        in>>v.masa;
        in>>v.volum;
        in>>v.px;
        in>>v.py;
        int k;
        in>>k;
        if(k==0) v.rece=false;
        else v.rece=true;
        return in;
    }
    friend ostream &operator <<(ostream &out, duba &v)
    {
        const vehicul baza(v);
        out<<baza;
        if(v.rece==true) out<<"Poate transporta rece"<<endl;
        else out<<"Nu poate transporta rece"<<endl;
        return out;
    }
    void afisare()
    {
        cout<<*this;

    }
    int deplasare_timp(int x, int y)            ///calcul timp pentru deplasarea vehiculului pana la destinatie
    {

        float vms=viteza*0.27;
        float dist=abs(px-x)+abs(py-y);
        int timp=dist/vms;
        return timp;
    }
    int deplasare_distanta(int x, int y)        ///calcul distanta de la vehicul la o locatie
    {

        float vms=viteza*0.27;
        float dist=abs(px-x)+abs(py-y);
        return dist;
    }

    duba operator =(const duba &v)
    {
        nume=v.nume;
        masa=v.masa;
        masaocupata=v.masaocupata;
        volum=v.volum;
        volumocupat=v.volumocupat;
        px=v.px;
        py=v.py;
        nr_c=v.nr_c;
        for(int i=0;i<=nr_c;i++)
            c[i]=v.c[i];
        rece=v.rece;
        return *this;
    }

    ~duba()
    {
    }
};

int cmp(void* arg1, void* arg2)         ///sortare colete dupa timpul de livrare final
{
    colet *a=(colet*)arg1;
    colet *b=(colet*)arg2;
    return a->get_timpr()-b->get_timpr();
}

void distribui_colet_apropiat(vehicul*v[], int nr_v, colet c)           ///distribuire colet catre cel mai apropiat vehicul
{


    int cont=-1;
    int distaux=9999999;
    for(int i=0;i<nr_v;i++){
        int dist=v[i]->deplasare_distanta(c.getlx(),c.getly());
        if(dist<distaux && v[i]->incape(c)==1)
            {
                if(c.gettemp()==false){
                    cont=i;
                    distaux=dist;
                }
                else
                    if(typeid(*v[i])==typeid(duba))
                {
                    cont=i;
                    distaux=dist;
                }
            }}




    if(cont==-1) cout<<"Coletul: "<<endl<<c<<"nu poate fi alocat!"<<endl;
    else
    v[cont]->adaug_colet(c);



}

void distribui_colet_incarcat(vehicul*v[], int nr_v, colet c)       ///distribuire colet catre cel mai putin incarcat vehicul
{
    int masamin=99999;
    int cont=-1;
    for(int i=0;i<nr_v;i++)
    {
        int aux=v[i]->getmasag();
        if(aux<masamin && v[i]->incape(c)==1)
            {
                if(c.gettemp()==false){
                    cont=i;
                    masamin=aux;
                }
                else
                    if(typeid(*v[i])==typeid(duba))
                {
                    cont=i;
                    masamin=aux;
                }

            }}

    if(cont==-1) cout<<"Coletul: "<<endl<<c<<"nu poate fi alocat!"<<endl;
    else
    v[cont]->adaug_colet(c);

    }

void distribui_colet_repede(vehicul*v[], int nr_v, colet c)     ///distribuire colet dupa cat de repede ajunge la destinatie
{
    int timp=99999;
    int cont=-1;
    for(int i=0;i<nr_v;i++)
    {
        int aux=v[i]->timp_liv_colete()+v[i]->deplasare_timp(c.getlx(),c.getly());
        if(aux<timp && v[i]->incape(c))
            if(c.gettemp()==false){
                    cont=i;
                    timp=aux;
                }
            else
                if(typeid(*v[i])==typeid(duba))
                {
                    cont=i;
                    timp=aux;
                }

        }
    if(cont==-1) cout<<"Coletul: "<<endl<<c<<"nu poate fi alocat!"<<endl;
    else
    v[cont]->adaug_colet(c);
}

void manager(colet c[],int nr_c, vehicul *v[], int nr_v)
{
    int i;
    for(int i=0;i<nr_c;i++)
    {
        for(int j=0;j<nr_v;j++)
            v[j]->livrez_colete();
        cout<<c[i]<<endl;
        cout<<"Cum doriti sa alocati coletul? "<<endl;
        cout<<"1 - Catre cel mai apropiat vehicul "<<endl;
        cout<<"2 - Catre vehicului cel mai putin incarcat "<<endl;
        cout<<"3 - Cea mai rapida livrare "<<endl;
        int dec;

        while(1)
        {
            while(1)
            {
                cin>>dec;
                if(dec==1 || dec==2 || dec==3) break;
            }

            switch (dec)
            {
                case 1: distribui_colet_apropiat(v,nr_v,c[i]);break;
                case 2: distribui_colet_incarcat(v,nr_v,c[i]);break;
                case 3: distribui_colet_repede(v,nr_v,c[i]);break;

            }

             if(dec==1 || dec==2 || dec==3) break;
        }
        timp_curent = c[i].get_timpr();
        cout<<"Doriti sa schimbati strategia de livrare? da/nu";
        string aleg;
        cin>>aleg;
        if(aleg=="DA" || aleg=="da")
        {
            while(1)
            {
                int indice;
                cout<<"Pentru ce vehicul doriti sa schimbati strategia? n<"<<nr_v<<endl;
                do
                {
                    cin>>indice;
                }while(indice<0 || indice>=nr_v+1);
                cout<<"Vehiculul "<<indice<<" are coletele: "<<endl;
                v[indice]->afisez_colete();
                cout<<"Ce strategie doriti sa aplicati?"<<endl;
                cout<<"1 - Cel mai urgent primul"<<endl;
                cout<<"2 - Coletul cel mai apropiat de poz curenta"<<endl;
                cout<<"3 - First come first served"<<endl;
                int str;
                do
                {
                    cin>>str;
                }while(str<1 || str>3);
                switch(str)
                {
                    case 1: v[i]->sortez_colete_urgenta();break;
                    case 2: v[i]->sortez_colete_apropiat();break;
                    case 3: v[i]->sortez_colete_ordine();break;
                }
                string aleg;
                cout<<endl<<"Doriti sa mai faceti si alte modificari? da/nu";
                cin>>aleg;
                if(aleg!="DA" && aleg!="da") break;

            }
        }
        cout<<endl<<"VEHICULE:"<<endl;
        for(int i=0;i<nr_v;i++){
                timp_curent+=v[i]->timp_liv_colete();
                v[i]->livrez_colete();
            }


    }

    cout<<"VEHICULE:"<<endl;
    for(int i=0;i<nr_v;i++){
        cout<<"Vehiculul "<<i<<" :"<<endl;
        v[i]->afisez_colete();}
}



void generare_intrare()
{
    int i=1;
    ofstream f("in_colete");
    ofstream g("in_vehicule");
    cout<<"PT COLETE"<<endl;
    while(1)
    {
        int m,v;
        cout<<"masa: ";
        cin>>m;
        cout<<"volum: ";
        cin>>v;
        string temp;
        cout<<"temperatura:   cald/rece";
        cin>>temp;
        int xinit, yinit;
        cout<<"xinit  yinit: ";
        cin>>xinit>>yinit;
        int xdest, ydest;
        cout<<"xdest   ydest:";
        cin>>xdest>>ydest;
        int timprid, timpliv;
        cout<<"timprid   timpliv";
        cin>>timprid>>timpliv;
        string text;
        try
        {
            if(m<0) throw 1;
            if(v<0) throw 1;
            if(temp!="cald" && temp!="rece") throw 1;
            if(xinit<0) throw 1;
            if(yinit<0) throw 1;
            if(xdest<0) throw 1;
            if(ydest<0) throw 1;
            if(timprid<0) throw 1;
            if(timpliv<0) throw 1;
            if(timpliv<timprid) throw 1;
            f<<m<<" "<<v<<" "<<temp<<" "<<xinit<<" "<<yinit<<" "<<xdest<<" "<<ydest<<" "<<timprid<<" "<<timpliv<<endl;

        }

        catch(int x)
        {
            cout<<"Datele despre un colet sunt nevalide\n";
        }
        cout<<endl<<"Doriti sa mai cititi si alte colete?\n DA  NU";
        cin>>text;
        if(text!="DA" && text!="da") break;


    }
    cout<<"VEHICULE:"<<endl;
    while(1)
    {
        string tip;
        cout<<"Tipul de vehicul:(scuter  masina  duba) ";
        cin>>tip;
        int m,v,x,y;
        string temp;
        cout<<"masa: ";
        cin>>m;
        cout<<endl<<"volum: ";
        cin>>v;
        cout<<endl<<"x  y: ";
        cin>>x>>y;
        if(tip=="duba")
        {
            cout<<"Poate transporta rece? da/nu";
            cin>>temp;
        }
        try
        {
            if(tip!="masina" && tip!="duba" && tip!="scuter") throw 1;
            if(m<0) throw 1;
            if(v<0) throw 1;
            if(x<0) throw 1;
            if(y<0) throw 1;
            if(tip=="duba")
                if(temp!="da" && temp!="nu") throw 1;
            g<<tip<<" "<<m<<" "<<v<<" "<<x<<" "<<y;
            if(tip=="duba")
                if(temp=="da") g<<" "<<1;
                else g<<0;
            g<<endl;
        }
        catch(int x)
        {
            cout<<"Datele despre vehicul sunt nevalide!"<<endl;
        }
        string text;
        cout<<"Mai doriti sa cititi si alte vehicule? DA/NU";
        cin>>text;
        if(text!="DA" && text!="da") break;
    }
    f.close();
    g.close();
}




int main()
{
    //generare_intrare();   ///pentru crearea propriilor date, un exemplu deja facut este in modelul de intrare
    colet c[100];
    int nr_c=-1;
    while(!col.eof())
        col>>c[++nr_c];

    qsort(c, (size_t)nr_c, sizeof(*c), (int(*)(const void*, const void*))cmp);

    int nr_v=-1;
    vehicul *v[100];
    while(!veh.eof())
    {
        string tip;
        veh>>tip;
        if(tip=="scuter")
        {
            scuter *s=new scuter;
            veh>>*s;
            v[++nr_v]=(scuter*)s;
        }
        else if(tip=="masina")
        {
            masina *m=new masina;
            veh>>*m;
            v[++nr_v]=m;
        }
        else
        {
            duba *d=new duba;
            veh>>*d;
            v[++nr_v]=d;

        }
    }

    manager(c,nr_c,v,nr_v);
    for(int i=0;i<nr_v;i++)
        delete v[i];
    cout<<endl<<endl;
    delete[] v;

    return 0;
}
