#include <iostream>
using namespace std;

/*
Vamos implementar o sistema de matrículas de uma escola. Neste sistema,
são armazenadas informações das turmas (nome da turma e série) e dos alunos
(nome e matrícula). Deve ser oferecido ao usuário um menu com as seguintes opções:


1 - Criar nova turma;
2 - Listar turmas;
3 - Inserir aluno em turma determinada;
4 - Inserir aluno na turma mais vaga;
5 - Listar alunos de turma determinada;
6 - Relatório completo;
0 - Sair.


Na opção 3, deve ser informada a série e o nome da turma desejada, sendo o aluno
inserido especificamente nesta turma. Na opção 4, deve ser informada a série do
aluno, sendo então o aluno inserido na turma da série correspondente que contenha
menos alunos. Na opção relatório completo, deve-se imprimir todas as turmas, com
seus respectivos alunos.


Os alunos devem ser mantidos em ordem alfabética em cada turma, e as turmas devem
ser ordenadas por série, e no caso de turmas da mesma série, ordenadas por ordem
alfabética do nome da turma.
*/

struct aluno
{
  aluno *ant;
  string nome;
  int matricula;
  aluno *prox;
};

struct turma
{
  turma *ant;
  aluno *inicio;
  string nome_turma;
  int serie;
  int tam;
  aluno *fim;
  turma *prox;
};

turma *inicializar()
{
  turma *aux = new turma;
  aux->inicio = NULL;
  aux->fim = NULL;
  aux->ant = NULL;
  aux->prox = NULL;
  aux->tam = 0;
  aux->serie = 0;
  aux->nome_turma = "";
  return aux;
}

bool criar_turma(turma* &t, string nome_turma, int serie)
{
  turma *novo = inicializar(), *aux;
  novo->nome_turma = nome_turma;
  novo->serie = serie;

  if(t->serie==0)
  {
    t = novo;
  }
  else
  {
    aux = t;
    if((to_string(novo->serie)+novo->nome_turma) < (to_string(aux->serie)+aux->nome_turma))
    {
      novo->prox = aux;
      aux->ant = novo;
      t = novo;
      return true;
    }
    while(aux->prox!=NULL && (to_string(novo->serie)+novo->nome_turma) > (to_string(aux->serie)+aux->nome_turma))
    {
      aux = aux->prox;
    }
    if(aux->prox==NULL && (to_string(novo->serie)+novo->nome_turma) > (to_string(aux->serie)+aux->nome_turma))
    {
      aux->prox = novo;
      novo->ant = aux;
      novo->prox = NULL;
    }
    else
    {
      aux->ant->prox = novo;
      novo->ant = aux->ant;
      novo->prox = aux;
      aux->ant = novo;
    }
  }
  return true;
}

void listar_turmas(turma *t)
{
  while(t!=NULL)
  {
    cout<<t->serie<<t->nome_turma<<endl;
    t = t->prox;
  }
}

bool inserir_aluno_em_turma_determinada(turma *t, int serie, string nome_turma, string nome_aluno, int matricula)
{
  aluno *novo = new aluno, *aux_aluno;
  turma *aux_turma = t;
  novo->ant = NULL;
  novo->nome = nome_aluno;
  novo->matricula = matricula;
  novo->prox = NULL;

  while(aux_turma->serie!=serie || aux_turma->nome_turma!=nome_turma)
  {
    aux_turma = aux_turma->prox;
  }

  aux_aluno = aux_turma->inicio;
  if(aux_turma->tam==0)
  {
    aux_turma->inicio = novo;
    aux_turma->fim = novo;
    aux_turma->tam++;
    return true;
  }
  while(aux_aluno->prox!=NULL && novo->nome > aux_aluno->nome)
  {
    aux_aluno = aux_aluno->prox;
  }
  if(aux_aluno->ant==NULL && novo->nome < aux_aluno->nome)
  {
    novo->prox = aux_aluno;
    aux_aluno->ant = novo;
    aux_turma->inicio = novo;
    aux_turma->tam++;
    return true;
  }
  if(aux_aluno->ant!=NULL && novo->nome < aux_aluno->nome)
  {
    novo->ant = aux_aluno->ant;
    novo->prox = aux_aluno;
    aux_aluno->ant->prox = novo;
    aux_aluno->ant = novo;
    aux_turma->tam++;
    return true;
  }
  if(aux_aluno->prox==NULL && novo->nome > aux_aluno->nome)
  {
    novo->ant = aux_aluno;
    aux_aluno->prox = novo;
    aux_turma->fim = novo;
    aux_turma->tam++;
    return true;
  }
  return false;
}

bool inserir_aluno_na_turma_mais_vaga(turma *t, int serie, string nome_aluno, int matricula)
{
  turma *aux_turma1 = t, *aux_turma2 = t;

  while(aux_turma1->serie!=serie)
  {
    aux_turma1 = aux_turma1->prox;
  }

  aux_turma2 = aux_turma1;
  while(aux_turma2->prox!=NULL && aux_turma2->prox->serie==serie)
  {
    aux_turma2 = aux_turma2->prox;
    if(aux_turma1->tam > aux_turma2->tam)
    {
      aux_turma1 = aux_turma2;
    }
  }

  string nome_turma = aux_turma1->nome_turma;
  inserir_aluno_em_turma_determinada(aux_turma1, serie, nome_turma, nome_aluno, matricula);
  return true;
}

void listar_alunos(turma *t, int serie, string nome_turma)
{
  turma *aux_turma = t;
  int cont = 0;

  while(aux_turma->serie!=serie || aux_turma->nome_turma!=nome_turma)
  {
    aux_turma = aux_turma->prox;
  }
  aluno *aux_aluno = aux_turma->inicio;
  while(aux_turma->tam != cont)
  {
    cout<<"aluno: "<<aux_aluno->nome<<" | matricula: "<<aux_aluno->matricula<<endl;
    aux_aluno = aux_aluno->prox;
    cont++;
  }
}

void relatorio_completo(turma *t)
{
  while(t!=NULL)
  {
    cout<<"--------------------------------------"<<endl;
    cout<<"               TURMA "<<t->serie<<t->nome_turma<<endl;
    cout<<"--------------------------------------"<<endl;
    listar_alunos(t, t->serie, t->nome_turma);
    t = t->prox;
  }
}

int menu()
{
  int opcao;

  cout<<"______________________________________"<<endl;
  cout<<endl;
  cout<<"                 MENU"<<endl;
  cout<<"______________________________________"<<endl;
  cout<<"1 - criar nova turma"<<endl;
  cout<<"2 - listar turmas"<<endl;
  cout<<"3 - inserir aluno em turma determinada"<<endl;
  cout<<"4 - inserir aluno na turma mais vaga"<<endl;
  cout<<"5 - listar alunos de turma determinada"<<endl;
  cout<<"6 - relatorio completo"<<endl;
  cout<<"0 - sair"<<endl;

  cout<<"--------------------------------------"<<endl;
  cout<<"escolha sua opcao: ";
  cin>>opcao;
  while(opcao<0||opcao>7)
  {
    cout<<"----[!]------------------------[!]----"<<endl;
    cout<<"opcao invalida, digite novamente: ";
    cin>>opcao;
  }
  return opcao;
}

int main()
{
  int aux = 1, serie, matricula;
  turma *t1;
  string nome_turma, nome_aluno;

  t1 = inicializar();

  while(aux!=0)
  {
    aux = menu();

    cout<<"--------------------------------------"<<endl;
    if(aux==1)
    {
      cout<<"              NOVA TURMA"<<endl;
      cout<<"--------------------------------------"<<endl;
      cout<<"serie: ";
      cin>>serie;
      setbuf(stdin, NULL);
      cout<<"nome da turma: ";
      getline(cin, nome_turma);
      setbuf(stdin, NULL);
      if(criar_turma(t1, nome_turma, serie))
      {
        cout<<"--------------------------------------"<<endl;
        cout<<"a turma "<<serie<<nome_turma<<" foi criada."<<endl;
      }
    }
    if(aux==2)
    {
      cout<<"             LISTA DE TURMAS"<<endl;
      cout<<"--------------------------------------"<<endl;
      listar_turmas(t1);
    }
    if(aux==3)
    {
      cout<<"        INSIRA O ALUNO NA TURMA"<<endl;
      cout<<"--------------------------------------"<<endl;
      setbuf(stdin, NULL);
      cout<<"nome do aluno: ";
      getline(cin, nome_aluno);
      setbuf(stdin, NULL);
      cout<<"matricula: ";
      cin>>matricula;
      cout<<"serie: ";
      cin>>serie;
      setbuf(stdin, NULL);
      cout<<"nome da turma: ";
      getline(cin, nome_turma);
      setbuf(stdin, NULL);
      cout<<"--------------------------------------"<<endl;
      cout<<"         ALUNOS DA TURMA: "<<serie<<nome_turma<<endl;
      cout<<"--------------------------------------"<<endl;
      if(inserir_aluno_em_turma_determinada(t1, serie, nome_turma, nome_aluno, matricula))
      {
        cout<<"o aluno: "<<nome_aluno<<" foi"<<endl;
        cout<<"inserido na turma: "<<serie<<nome_turma<<endl;
      }
    }
    if(aux==4)
    {
      cout<<"       INSIRA NA TURMA MAIS VAGA"<<endl;
      cout<<"--------------------------------------"<<endl;
      setbuf(stdin, NULL);
      cout<<"nome do aluno: ";
      getline(cin, nome_aluno);
      setbuf(stdin, NULL);
      cout<<"matricula: ";
      cin>>matricula;
      cout<<"serie: ";
      cin>>serie;
      if(inserir_aluno_na_turma_mais_vaga(t1, serie ,nome_aluno, matricula))
      {
        cout<<"--------------------------------------"<<endl;
        cout<<"o aluno: "<<nome_aluno<<" foi inserido"<<endl;
        cout<<"na turma mais vaga da serie: "<<serie<<endl;
      }
    }
    if(aux==5)
    {
      cout<<"INFORME A TURMA PARA LISTAR OS ALUNOS"<<endl;
      cout<<"--------------------------------------"<<endl;
      cout<<"serie: ";
      cin>>serie;
      setbuf(stdin, NULL);
      cout<<"nome da turma: ";
      getline(cin, nome_turma);
      setbuf(stdin, NULL);
      cout<<"--------------------------------------"<<endl;
      cout<<"               TURMA "<<serie<<nome_turma<<endl;
      cout<<"--------------------------------------"<<endl;
      listar_alunos(t1, serie, nome_turma);
    }
    if(aux==6)
    {
      relatorio_completo(t1);
    }
  }
}
