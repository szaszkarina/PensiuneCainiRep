#include <iostream>

using namespace std;

int numarAnimal = 1;//CODUL DE INREGISTRARE AL CAINELUI

struct data
{
    int zi;
    int luna;
    int an;

    void print()
    {
        cout<<zi<<"."<<luna<<"."<<an;
    }
};

struct nodProgramare //ARBORE BINAR, FIU STANGA SI FIU DREAPTA
{
    int numarAnimal;

    data dataInceput;
    data dataSfarsit;

    nodProgramare *fiuStanga;
    nodProgramare *fiuDreapta;

    void print()
    {
        dataInceput.print();
        cout<<" - ";
        dataSfarsit.print();
        cout<<" animalul " << numarAnimal;
    }
};

struct nodPadoc
{
    int numar;

    nodPadoc *urmator;

    nodProgramare *programPadoc;
};

struct nodAnimal
{
    int numar;
    char nume[20];
    int inaltime;
    int kg;
    int grMancareZi;
    char rasa[60];

    nodAnimal *urmator;
};

void adaugarePadoc(nodPadoc *&lista, int numarPadoc)
{
    nodPadoc *aux;

    if(lista == NULL)
    {
        lista = new nodPadoc;
        lista->numar = numarPadoc;
        lista->programPadoc = NULL;
        lista->urmator = NULL;
    }
    else
    {
        aux = lista;

        while(aux->urmator != NULL)
            aux = aux->urmator;

        aux->urmator = new nodPadoc;
        aux = aux->urmator;
        aux->numar = numarPadoc;
        aux->programPadoc = NULL;
        aux->urmator = NULL;
    }
}

void afisareProgramPadoc(nodProgramare *program)
{
    if(program != NULL)
    {
        afisareProgramPadoc(program->fiuStanga);
        program->print();
        cout<<endl;
        afisareProgramPadoc(program->fiuDreapta); //AFISEZ CE E PE STANGA APOI RADACINA SI APOI DREAPA-INORDINE
    }
}

void afisareListaPadocuri(nodPadoc *lista)
{
    nodPadoc *aux = lista;

    cout<<"Lista padocuri: "<<endl;

    while(aux != NULL)
    {
        cout<<"Padocul " << aux->numar<<" ocupat in: "<<endl;
        afisareProgramPadoc(aux->programPadoc);
        aux = aux->urmator;
    }
}

// 0 - date egale; 1 - data1 < data2; (-1) - data1 > data2
int comparareDate(data data1, data data2)
{
    if(data1.zi == data2.zi && data1.luna == data2.luna && data1.an == data2.an)
        return 0;

    if(data1.an < data2.an)
        return 1;
    else if(data1.an > data2.an)
        return -1;
    else
    {
        if(data1.luna < data2.luna)
            return 1;
        else if(data1.luna > data2.luna)
            return -1;
        else
        {
            if(data1.zi < data2.zi)
                return 1;
            else if(data1.zi > data2.zi)
                return -1;
            else
                return 0;
        }
    }
}
//FUNCTIE CE COMPARA DACA AVEM DOUA DATE LA FEL

bool verificarePadocDisponibil(nodProgramare *program, data dataInceput, data dataSfarsit) //PRIMESTE RADACINA ARBORELUI
{
    if(program == NULL)
        return true;

    if(comparareDate(dataSfarsit, program->dataInceput) == 1)
        return verificarePadocDisponibil(program->fiuStanga, dataInceput, dataSfarsit);
    else if(comparareDate(dataInceput, program->dataSfarsit) == -1)
        return verificarePadocDisponibil(program->fiuDreapta, dataInceput, dataSfarsit);
    else
        return false;
}

void adaugareProgramarePadoc(nodProgramare *&program, nodProgramare *programareNoua)
{
    if(program == NULL)
        program = programareNoua;
    else
    {
        nodProgramare *aux = program;

        while(true)
        {
            //daca dataSfarsit<dataInceput mergi pe stanga
            if(comparareDate(programareNoua->dataSfarsit, aux->dataInceput) == 1)
            {
                if(aux->fiuStanga == NULL)
                {
                    aux->fiuStanga = programareNoua;
                    break;
                }
                else
                    aux = aux->fiuStanga;
            }
            //daca dataInceput>dataSfarsit mergi pe drepata(comparare in X)
            else if(comparareDate(programareNoua->dataInceput, program->dataSfarsit) == -1)
            {
                if(aux->fiuDreapta == NULL)
                {
                    aux->fiuDreapta = programareNoua;
                    break;
                }
                else
                    aux = aux->fiuDreapta;
            }
        }
    }
}

nodPadoc* cautarePadocDisponibil(nodPadoc *lista, data dataInceput, data dataSfarsit)
{
    nodPadoc *aux = lista;//aux e nodPadoc in lista si contine un arbore

    while(aux != NULL)//parcurgere lista padocuri
    {
        if(verificarePadocDisponibil(aux->programPadoc, dataInceput, dataSfarsit) == true)//acum i se atribuie arborele
            return aux;

        aux = aux->urmator;
    }

    return NULL;
}

void adaugareAnimal(nodAnimal *&lista, nodAnimal *animalNou)
{
    nodAnimal *aux = lista;

    if(lista == NULL)
        lista = animalNou;
    else
    {
        while(aux->urmator != NULL)
            aux = aux->urmator;

        aux->urmator = animalNou;
    }
}

void citireAnimalNou(nodAnimal *&listaAnimale, nodPadoc *listaPadocuri)
{
    nodPadoc *padocDispobibil;// tot un nod
    data *dataInceput, *dataFinal;

    dataInceput = new data;
    cout<<"Incepand din data:"<<endl<<"zi: ";
    cin>>dataInceput->zi;
    cout<<"luna: ";
    cin>>dataInceput->luna;
    cout<<"an: ";
    cin>>dataInceput->an;

    dataFinal = new data;
    cout<<"Pana in data:"<<endl<<"zi: ";
    cin>>dataFinal->zi;
    cout<<"luna: ";
    cin>>dataFinal->luna;
    cout<<"an: ";
    cin>>dataFinal->an;

    padocDispobibil = cautarePadocDisponibil(listaPadocuri, *dataInceput, *dataFinal);// Daca exista padoc disponibil va avea adresa acelui nod
                                                                                        //Daca nu exista padoc disponibil e null

    if(padocDispobibil != NULL)
    {
        cout<<"Padocul " << padocDispobibil->numar << " este disponibil"<<endl;

        nodAnimal *animalNou = new nodAnimal;
        animalNou->numar = numarAnimal++;
        cout<<"Nume animal = ";
        cin.get();
        cin.getline(animalNou->nume, 20, '\n');
        cout<<"Greutate = ";
        cin>>animalNou->kg;
        cout<<"Inaltime = ";
        cin>>animalNou->inaltime;
        cout<<"Gr mancare / zi = ";
        cin>>animalNou->grMancareZi;
        cout<<"Rasa= ";
        cin.get();
        cin.getline(animalNou->rasa, 60, '\n');
        animalNou->urmator = NULL;

        adaugareAnimal(listaAnimale, animalNou);

        nodProgramare *programareNoua = new nodProgramare;
        programareNoua->numarAnimal = animalNou->numar;
        programareNoua->dataInceput = *dataInceput;
        programareNoua->dataSfarsit = *dataFinal;
        programareNoua->fiuStanga = NULL;
        programareNoua->fiuDreapta = NULL;

        adaugareProgramarePadoc(padocDispobibil->programPadoc, programareNoua);// ii transmitem arborele nodului
    }
    else
        cout<<"Nu exista padocuri disbonibile! ";
}

void afisareListaAnimale(nodAnimal *lista)
{
    nodAnimal *aux = lista;

    cout<<"Lista animale: "<<endl;

    while(aux != NULL)
    {
        cout<<"Animal " << aux->numar << ", nume " << aux->nume << ", inaltime " << aux->inaltime<< ", greutate " << aux->kg << ", mancare/zi " << aux->grMancareZi <<" gr"<< ", rasa "<<aux->rasa<<endl;
        aux = aux->urmator;
    }
}

int main()
{
    nodPadoc *listaPadocuri = NULL;
    nodAnimal *listaAnimale = NULL;

    int i, comanda;

    for(i = 1; i < 13; i++) // FOR PENTRU NUMAR PADOCURI!
        adaugarePadoc(listaPadocuri, i);

    while(true)
    {
        cout<<endl<<endl;
        cout<<"1 - Afisare lista padocuri"<<endl;
        cout<<"2 - Afisare lista animale"<<endl;
        cout<<"3 - Adaugare animal nou"<<endl;
        cout<<"4 - Inchidere program"<<endl;
        cout<<"Comanda = ";
        cin>>comanda;

        if(comanda == 1)
            afisareListaPadocuri(listaPadocuri);
        else if(comanda == 2)
            afisareListaAnimale(listaAnimale);
        else if(comanda == 3)
            citireAnimalNou(listaAnimale, listaPadocuri);
        else if(comanda == 4)
            break;
    }

    return 0;
}
