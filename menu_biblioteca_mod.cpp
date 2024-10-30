#include <iostream>
#include <cstdio>
#include <limits>
#include <cstring>

using namespace std;

FILE *dados_livro;
FILE * dados_livroAux;

struct reg_emprestimo
{
    char dt_emprestimo[11];
    char dt_devolucao[11];
    char usuario [50];
};

struct cad_livro
{
    int cod_catalog;
    int n_pag;
    char area [50];
    char titulo[100];
    char editora[50];
    char autor[50];
    struct reg_emprestimo emprest;
};

struct cad_livro cad;

void cadastrarLivro()
{
    char opc ;

    cout << "Deseja fazer o cadastro de um novo livro ? ('S/N') " << endl;
        cin >> opc;
    while(opc=='S')
    {
        cout << "################Cadastro de novo livro###############"<< endl;
        cout << "Digite o codigo de catalogaçao :" << endl;
        cin >> cad.cod_catalog;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Digite a area da ciencia :" << endl;
        cin.get(cad.area, 50);
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Digite o titulo :" << endl;
        cin.get(cad.titulo,100);
        cin.ignore(numeric_limits<streamsize>:: max(), '\n');
        cout << "Digite qual o autor(es) :" << endl;
        cin.get(cad.autor,50);
        cin.ignore(numeric_limits<streamsize> :: max(), '\n');
        cout << "Digite qual a editora " << endl;
        cin.get(cad.editora,50);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Digite o número de paginas :" << endl;
        cin >> cad.n_pag;

        dados_livro=fopen("dados_livro.dat", "ab");
        if (dados_livro==NULL)
        dados_livro=fopen("dados_livro.dat", "wb");
        if(fwrite(&cad,sizeof(cad_livro),1,dados_livro)==1){
             cout << "livro cadastrado com sucesso !";
             cin.get();
        } else {
            cout << "Dados nao foram salvos com sucesso ";
            cin.get();
        }
        fclose (dados_livro);
        cout << "dados salvos no arquivo com sucesso!";
        cin.get();
        cout << "Deseja cadastrar um novo livro? ('S/N') ";
        cin >> opc;
    }
        

}
void listar (){

    dados_livro= fopen ("dados_livro.dat", "rb");
    if (dados_livro != NULL){
        fread(&cad,sizeof(cad_livro),1,dados_livro);
        while (!feof(dados_livro)){ 
            cout<<"Titulo :" << cad.titulo << endl;
            cout<<"Autor :" << cad.autor<< endl;
            cout<<"Area :" << cad.area<< endl;
            cout<<"Numero de paginas :"<< cad.n_pag<< endl;
            cout<<"Editora" << cad.editora<< endl;
            cout<<"Codigo de catalogacao :"<< cad.cod_catalog<< endl;
            cout << "______________________________________________"<< endl;
            fread(&cad,sizeof(cad_livro),1,dados_livro);
        }
        fclose(dados_livro);
        cin.ignore();
        cin.get();
        }else {
        cout << "Erro ao abrir o arquivo !";
        cin.ignore();
        cin.get();
    }
}
void alterar(){
    int cod=0;
    int opc;

    dados_livro= fopen ("dados_livro.dat", "rb+");
    if (dados_livro != NULL){
        cout << "Digite o código do livro que deseja alterar: ";
        cin>> cod;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        int pos = -1;
        
        while (!feof(dados_livro)){
            fread(&cad,sizeof(cad_livro),1,dados_livro);
            pos++;
            if (cod == cad.cod_catalog ){

                while (opc !=6){ 
                    cout << "Qual dado do livro deseja alterar ?"<<endl;
                    cout << "1-Area da ciencia"<<endl;
                    cout << "2-Titulo"<<endl;
                    cout << "3-Autor"<<endl;
                    cout << "4-Editora"<<endl;
                    cout << "5-Numero de paginas"<<endl;
                    cout << "6-Retornar"<< endl;
                    cout <<"#############"<<endl;
                    cin >> opc;
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    
                    switch (opc)
                    {
                    case 1:
                        cout << "Digite a area da ciencia :" << endl;
                        cin.get(cad.area, 50);
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                            break;
                    case 2:
                        cout << "Digite o titulo :" << endl;
                        cin.get(cad.titulo,100);
                        cin.ignore(numeric_limits<streamsize>:: max(), '\n');
                            break;
                    case 3:
                        cout << "Digite qual o autor(es) :" << endl;
                        cin.get(cad.autor,50);
                        cin.ignore(numeric_limits<streamsize> :: max(), '\n');
                            break;
                    case 4:
                        cout << "Digite qual a editora " << endl;
                        cin.get(cad.editora,50);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                    case 5:
                        cout << "Digite o número de paginas :" << endl;
                        cin >> cad.n_pag;
                            break;
                    case 6:
                        
                        break;
                    
                    default:
                        break;
                    }

                }
                    fseek(dados_livro,sizeof(struct cad_livro)*pos, SEEK_SET);

                    if (fwrite(&cad,sizeof(cad_livro),1,dados_livro)== 1){
                        cout << " Dados so livro alterado com sucesso !";
                        cin.ignore();
                        break;
                    }else {
                        cout << "Erro ao alterar o livro";
                        cin.ignore();
                        break;
                    }            
            }
        cout << "\e[2J" << "\e[0;0H";
        system("cls");
        }fclose(dados_livro);

    }else
    cout << "Erro ao acessar arquivo";
}  
void emprestarLivro()
{
    int pos;
    dados_livro=fopen("dados_livro.dat", "rb+");
    if (dados_livro != NULL){
        int codigo;
        cout << "Digite o codigo do livro que deseja pegar emprestado :";
        cin>> codigo;
        cin.ignore(numeric_limits<streamsize> :: max(), '\n');
        pos = -1;
        while(!feof(dados_livro)){
            fread(&cad,sizeof(cad_livro),1,dados_livro);
            pos++;
            if(cad.cod_catalog==codigo){
                fseek(dados_livro,sizeof(struct cad_livro)*pos, SEEK_SET);
                cout << "por favor informe a data de emprestimo :";
                cin.get(cad.emprest.dt_emprestimo,11);
                cin.ignore(numeric_limits<streamsize> :: max(), '\n');
                cout << "agora informe a data de devolucao :";
                cin.get(cad.emprest.dt_devolucao,11);
                cin.ignore(numeric_limits<streamsize> :: max(), '\n');
                cout << " Por favor informe o usuario :";
                cin.get(cad.emprest.usuario,50);
                cin.ignore(numeric_limits<streamsize> :: max(), '\n');
                fwrite(&cad,sizeof(cad_livro),1,dados_livro);
               break;
            }
        }fclose(dados_livro);
        cout << "Livro emprestado !";
        
    }else {
        cout << "Erro ao abrir o arquivo !";
        cin.ignore();
        cin.get();
    }
}
void devolverLivro()
{
    int codigo;
    int pos = -1;
    dados_livro = fopen ("dados_livro.dat", "rb+");
    if (dados_livro != NULL){
        cout << "Digite o codigo do livro a ser devolvido :";
        cin >> codigo;
        if(!strcmp(cad.emprest.dt_emprestimo,"")==0){
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pos = -1;

            while (!feof(dados_livro)){ 
                fread(&cad,sizeof(cad_livro),1,dados_livro);
                pos++;
                if(cad.cod_catalog==codigo){
                    fseek(dados_livro,sizeof(struct cad_livro)*pos, SEEK_SET);
                    strcpy(cad.emprest.dt_emprestimo, "");
                    strcpy(cad.emprest.dt_devolucao,"");
                    strcpy(cad.emprest.usuario,"");
                    fwrite(&cad,sizeof(cad_livro),1,dados_livro);
                    break;
                }
            } fclose (dados_livro);
            cout << "Livro devolvido !";
        }else{
            cout << "Este livro nao está emprestado ! "<< endl;
            cout << "verifique se o codigo que digitou esta correto !"<< endl;
        }
    } else {
        cout << "Erro ao abrir o banco de dados!";
        cin.ignore();
        cin.get();
    }
}

void pesquisarLivro()
{   
    int cod;
    dados_livro=fopen("dados_livro.dat", "rb");
    if (dados_livro != NULL){
        cout<< "Digite o codigo do livro consultado :";
        cin >> cod;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        while (!feof(dados_livro)){ 
            fread(&cad,sizeof(cad_livro),1,dados_livro);
                if(cad.cod_catalog==cod){  
                cout << "Dados do livro -> ";
                cout<<"Titulo :" << cad.titulo << endl;
                cout<<"Autor :" << cad.autor << endl;
                cout<<"Area :" << cad.area << endl;
                cout<<"Numero de paginas :"<< cad.n_pag << endl;
                cout<<"Editora :" << cad.editora << endl;
                cout<<"Codigo de catalogacao :"<< cad.cod_catalog << endl;
                cin.get();
                break;
            }
        }fclose(dados_livro);

    } else {
    cout << "Erro ao abrir o banco de dados!";
    cin.ignore();
    cin.get();
    }
}
void excluir (){
    int cod;
    cout << " #####Excluir registro de livro ######"<< endl;
    cout << "Digite o codigo do livro que deseja excluir :";
    cin >> cod;
    if (cad.cod_catalog== cod){ 
        dados_livroAux= fopen ("dados_livro.dat" ,"rb");
        dados_livro=fopen("dados_livroAux.dat", "wb");
        fread(&cad,sizeof(cad_livro),1,dados_livro);
        while (!feof(dados_livro))
        {
            if (cad.cod_catalog != cod){
                fwrite(&cad, sizeof(struct cad_livro), 1, dados_livroAux);
            }
            fread(&cad,sizeof(cad_livro),1,dados_livro);
        }
        fclose (dados_livroAux);
        fclose (dados_livro);
        remove ("dados_livro.dat"); 
        rename ("dados_livroAux", "dados_livro");
        cout << "LIVRO EXCLUIDO !";
        cin.ignore();
        listar();
    }else 
    cout << "codigo invalido!";
    cin.ignore();
}
void livrosDisponives (){
    dados_livro=fopen("dados_livro.dat", "rb");
    if (dados_livro != NULL){
        fread(&cad,sizeof(cad_livro),1,dados_livro);
        while (!feof(dados_livro)){

            if(strcmp (cad.emprest.dt_emprestimo,"")==0){  
                cout << "Dados do livro -> ";
                cout<<"Titulo :" << cad.titulo << endl;
                cout<<"Autor :" << cad.autor << endl;
                cout<<"Area :" << cad.area << endl;
                cout<<"Numero de paginas :"<< cad.n_pag << endl;
                cout<<"Editora" << cad.editora << endl;
                cout<<"Codigo de catalogacao :"<< cad.cod_catalog << endl;
                cout << "-------------------------------------"<< endl;
            }
            fread(&cad,sizeof(cad_livro),1,dados_livro);
        }
        fclose(dados_livro);
        cin.ignore();
        cin.get();
    } else {
    cout << "Erro ao abrir o banco de dados!";
    }
}
int main(){ 
    int opcao = 0;

    while (opcao != 9)
    {   
        cout << "\e[2J" << "\e[0;0H";
        system("cls");

        cout << "*******SISTEMA****DE*****BIBLIOTECA*******" << endl;

        cout << "Selecione a opcao desdejada abaixo :" << endl;

        cout << "1 - Cadastro " << endl;

        cout << "2 - Alteracao" << endl;

        cout << "3 - Exclusao" << endl;

        cout << "4 - Emprestimo" << endl;

        cout << "5 - Devolucao" << endl;

        cout << "6 - Consulta de livro" << endl;

        cout << "7- livros disponiveis" << endl;

        cout << "8- listagem geral de livros"<< endl;;

        cout << "9 - Sair" << endl;

        cout << " Digite a opcao desejada : ";
        cin >> opcao;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcao)
        { 
        case 1:
        
            cadastrarLivro();
            break;
        
        case 2:
        
            alterar();
            break;
        
        case 3:
        
            excluir();
            break;
        
        case 4:
        
            emprestarLivro();
            break;
        
        case 5:
        
            devolverLivro();
            break;
        
        case 6:
        
            pesquisarLivro();
            break;
        
        case 7:
        
            livrosDisponives();
            break;
        
        case 8:
        
            listar();
            break;
        
        case 9 :

            cout << "Saindo do programa...";
            

            break;

        default:

            cout << " opcao invalida !";
            break;
        
        
        }
        
    }
}