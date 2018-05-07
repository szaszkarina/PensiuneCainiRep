#include <iostream>

using namespace std;

int numarAnimal = 1;

struct nodPadoc
{
    int numar;
    int numarAnimal;
    bool ocupat;

    nodPadoc *urmator;
};

struct nodAnimal
{
    int numar;
    char nume[20];
    int inaltime;
    int kg;
    int grMancareZi;

    nodAnimal *urmator;
};

void adaugarePadoc(nodPadoc *&lista, int numarPadoc)
{
    nodPadoc *aux;

    if(lista == NULL)
    {
        lista = new nodPadoc;
        lista->numar = numarPadoc;
        lista->numarAnimal = -1;
        lista->ocupat = false;
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
        aux->numarAnimal = -1;
        aux->ocupat = false;
        aux->urmator = NULL;
    }
}

void afisareListaPadocuri(nodPadoc *lista)
{
    nodPadoc *aux = lista;

    cout<<"Lista padocuri: "<<endl;

    while(aux != NULL)
    {
        cout<<"Padoc " << aux->numar << " ocupat " << aux->ocupat<<" animal " << aux->numarAnimal<<endl;
        aux = aux->urmator;
    }
}

nodPadoc* cautarePadocDisponibil(nodPadoc *lista)
{
    nodPadoc *aux = lista;

    while(aux != NULL)
    {
        if(aux->ocupat == false)
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
    nodPadoc *padocDispobibil;

    padocDispobibil = cautarePadocDisponibil(listaPadocuri);

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
        animalNou->urmator = NULL;

        adaugareAnimal(listaAnimale, animalNou);

        padocDispobibil->numarAnimal = animalNou->numar;
        padocDispobibil->ocupat = true;
    }
    else
    {
        cout<<"Nu exista padocuri disbonibile! ";
    }
}

void afisareListaAnimale(nodAnimal *lista)
{
    nodAnimal *aux = lista;

    cout<<"Lista animale: "<<endl;

    while(aux != NULL)
    {
        cout<<"Animal " << aux->numar << ", nume " << aux->nume << ", inaltime " << aux->inaltime<< ", greutate " << aux->kg << ", mancare/zi " << aux->grMancareZi <<" gr"<<endl;
        aux = aux->urmator;
    }
}

void eliberarePadoc(nodPadoc *lista)
{
    nodPadoc *aux = lista;
    int numarPadoc;

    cout<<"Numar padoc = ";
    cin>>numarPadoc;

    while(aux != NULL)
    {
        if(aux->numar == numarPadoc)
        {
            aux->ocupat = false;
            aux->numarAnimal = -1;
            break;
        }
        aux=aux->urmator;
    }

}

int main()
{
    nodPadoc *listaPadocuri = NULL;
    nodAnimal *listaAnimale = NULL;

    int i, comanda;

    for(i = 0; i < 15; i++)
        adaugarePadoc(listaPadocuri, i);

    while(true)
    {
        cout<<endl<<endl;
        cout<<"1 - Afisare lista padocuri"<<endl;
        cout<<"2 - Afisare lista animale"<<endl;
        cout<<"3 - Adaugare animal nou"<<endl;
        cout<<"4 - Eliberare padoc"<<endl;
        cout<<"5 - Inchidere program"<<endl;
        cout<<"Comanda = ";
        cin>>comanda;

        if(comanda == 1)
            afisareListaPadocuri(listaPadocuri);
        else if(comanda == 2)
            afisareListaAnimale(listaAnimale);
        else if(comanda == 3)
            citireAnimalNou(listaAnimale, listaPadocuri);
        else if(comanda == 4)
            eliberarePadoc(listaPadocuri);
        else if(comanda == 5)
            break;
    }

    return 0;
}
