#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <chrono>
#include <time.h>
#include "string.h"

#include "../Headers/NodeAvp.h"
#include "../Headers/ArvoreVP.h"



using namespace std;

//construtor
ArvoreVP::ArvoreVP()
{
    this->raiz = NULL;
    this->tempo = 0;
    this->comparacoes = 0;
}

//destrutor
ArvoreVP::~ArvoreVP()
{
    this->raiz = libera(raiz);
}

//getters and setters
void ArvoreVP::setRaiz(NodeAvp* p)
{
    this->raiz = p;
}

NodeAvp* ArvoreVP::getRaiz()
{
    return this->raiz;
}

NodeAvp* ArvoreVP::libera(NodeAvp* node)
{
    if(node != NULL)
    {
        node->setLeft(libera(node->getLeft()));
        node->setRigth(libera(node->getRigth()));
        node = NULL;
    }

    return node; 
}

// função de rotação a esquerda
void ArvoreVP::rotateLeft(NodeAvp* node)
{
    NodeAvp* p_rigth = node->getRigth(); //pega o nó a direita do nó passado e armazena em p_rigth
    node->setRigth(p_rigth->getLeft()); // pega o nó a direita e setta ele como o nó a esquerda de p_rigth

    if(node->getRigth() != NULL) //se o nó a direita do node for diferente de null
        node->getRigth()->setParent(node); //o nó a direita do node recebe o node como pai
    p_rigth->setParent(node->getParent()); //p_rigth recebe o mesmo pai de node como pai

    if(node->getParent() == NULL) //se o pai do node for null
        raiz = p_rigth; //raiz recebe p_rigth
    else if( node == node->getParent()->getLeft()) // se node for igual ao no a esquerda do pai de node
        node->getParent()->setLeft(p_rigth); // o nó a esquerda do pai do node recebe p_rigth
    else
        node->getParent()->setRigth(p_rigth); //o nó a direita do pai de node recebe p_rigth
    
    p_rigth->setLeft(node); //p_rigth recebe node como o no a esquerda
    node->setParent(p_rigth); //node recebe p_rigth como pai
}

//funçãp de rotscionar a direita
void ArvoreVP::rotateRight(NodeAvp* node)
{
    NodeAvp* p_left = node->getLeft(); //p_left recebe o nó a esquerda do node
    node->setLeft(p_left->getRigth()); //o nó a esquerda do node recebe o nó direito do p_left

    if(node->getLeft() != NULL) //se o nó a esquerda for diferente de null
        node->getLeft()->setParent(node); //o nó a esquerda do node recebe node como pai
    p_left->setParent(node->getParent()); //p_left recebe o mesmo pai de node

    if(node->getParent() == NULL) // se o pai de node for nulo
        raiz = p_left; //raiz recebe p_left
    else if(node == node->getParent()->getLeft()) // se node for igual ao nó a esquerda do pai de node
        node->getParent()->setLeft(p_left); //o pai de node recebe p_left como nó direito
    else
        node->getParent()->setRigth(p_left); // o pai de node recebe p_left como nó esquerdo
    
    p_left->setRigth(node); //node vira o nó direito de p_left
    node->setParent(p_left); //o pai de node vira p_left
}

void ArvoreVP::insere(ProductReview *pr)
{
    
    clock_t tempoInicio, tempoFim;
    tempoInicio = clock();
    // cout << "entrei no insere" << endl;
    string concatenacao = pr->getUserId() + pr->getProductId(); // concatena o userId com o productId
    // cout << "concatenei" << endl;
    NodeAvp* p = new NodeAvp(concatenacao); //manda concatenacao como id e a posicao do productReview
    p->setProduct(pr); //insere o produto no nó correspondente
    // cout << "criei um novo no" << endl;

    //inserção usando busca binaria
    cout << "1" <<endl;
    NodeAvp* no_aux = insereAux(getRaiz(), p);
    cout << "em teoria eu inseri o novo no" << endl;
    // cout << "printei" << endl;
    repair(no_aux,p); // conserta os erros
    // cout << "em teoria eu consertei" << endl;
    count ++;
    tempoFim = clock();
    float tempoTotal = float(tempoFim - tempoInicio) / float(CLOCKS_PER_SEC);
    this->tempo = this->tempo + tempoTotal;
    
}

NodeAvp* ArvoreVP::insereAux(NodeAvp* p, NodeAvp* no)
{
    // cout<<"entrei no insereAux"<<endl;
    //caso a arvore esteja vazia
    if(raiz == NULL)
    {
        // cout << "raiz nula" << endl;
       comparacoes ++; // compara uma vez
       setRaiz(no); // raiz recebe o no
        //    cout << getRaiz()->getColor()<< endl;
       return no; //retorna raiz
    }
    else if(p == NULL)
    {
        comparacoes ++;
        p = no;
        return p;
    }
    else
    {
        //Caso contrario, faz uma busca binaria recursiva pela arvore para inserir o No no lugar certo
        //caso a raiz seja maior
        if(p->getId() > no->getId())
        {
            // cout << "raiz maior" << endl;
            comparacoes ++;
            //  cout << "3" <<endl;
            p->setLeft(insereAux(p->getLeft(), no));
            //  cout << "2" <<endl;
            p->getLeft()->setParent(p);
        }
        else
        {
            // cout << "4" <<endl;
            //caso a raiz seja menor
            comparacoes ++;
            // cout << "raiz menor" << endl;
            p->setRigth(insereAux(p->getRigth(), no));
            // cout << "entrei na recurssao" << endl;
            p->getRigth()->setParent(p);
            // cout << "ganhei um pai" << endl;
            // cout << "5" <<endl;
        }

        // cout << "sai do if" << endl;
        return p;
    }
}

void ArvoreVP::repair(NodeAvp* node1, NodeAvp* node2)
{
    //node1 -> raiz local
    //node2 -> no inserido/no local

    NodeAvp* pai = NULL; //cria o pai auxiliar
    NodeAvp* avo = NULL; // criz o avo auxilar

    // cout << "entrei no repair" << endl;
    //enquanto node2 for diferente de node1,node2 for diferente de preto e o pai de node2 for vermelho
    while((node2 !=  node1) && (node2->getColor() != 0) && (node2->getParent()->getColor() == 1))
    {
        pai = node2->getParent(); //pai vira o pai de node2
        avo = node2->getParent()->getParent(); //avo vira pai do pai de node2
        // cout << "entrei no while" << endl;
        //Caso : 1
        //pai do no conflitante está a esquerda do avo de pai
        if(pai == avo->getLeft())
        {
            // cout << "entrei no primeiro if" << endl;
            NodeAvp* tio = avo->getRigth();

            //se tio for diferente de null e for vermelho 
            if(tio != NULL && tio->getColor() == 1)
            {
                avo->setColor(1); // avo vira vermelho
                pai->setColor(0); // pai vira preto
                tio->setColor(0); // tio vira preto
                node2 = avo;
                // cout << "o avo vira vermelho e os filhos preto" << endl;
            }
            else
            {
                // o no conflitante esta a direita de seu pai entao rotaciona para a esquerda
                if(node2 == pai->getRigth())
                {
                    rotateLeft(pai);
                    node2 = pai;
                    pai = node2->getParent();
                    // cout << "rotacionou a esquerda" << endl;
                }

                //o no conflitante esta a esquerda de seu pai entao rotaciona para a direita
                rotateRight(avo);
                // cout << "rotacionou a direita" << endl;


                //ajuste de cores
                int corAux = pai->getColor();
                pai->setColor(avo->getColor());
                avo->setColor(corAux);
                // cout << "ajustou as cores" << endl;

                node1 = pai;
            }
        }
        else
        {
            // cout << "caso 2" << endl;
            // Caso : 2
            // pai do no conflitante é o filho da direita de seu avo

            NodeAvp* tio = avo->getLeft();

            // o tio do no conflitante tambem e vermelho
            if((tio != NULL) && (tio->getColor() == 1))
            {
                // cout << "avo vira vermelho " << endl;
                avo->setColor(1);
                pai->setColor(0);
                tio->setColor(0);
                node2 = avo;
            }
            else
            {
                // cout << "bla" << endl;
                // o no conflitante esta a esquerda de seu pai entao rotaciona para a direita
                if(node2 == pai->getLeft())
                {
                    // cout << "rotaciona a direita" << endl;
                    rotateRight(pai);
                    node2 = pai;
                    pai = node2->getParent();
                }

                // o no conflitante esta a direita de seu pai entao rotaciona para a esquerda
                rotateLeft(avo);
                // cout << "rotacionou a esquerda" << endl;

                //ajuste de cores
                int corAux = pai->getColor();
                pai->setColor(avo->getColor());
                avo->setColor(corAux);

                node2 = pai;
            }  
           
        }
    }

    node1->setColor(0);
}

void ArvoreVP::print()
{
    // cout << "entrei no print" << endl;
    if(this->raiz == NULL)
        cout << "Arvore vazia!" << endl;
    else{
        // cout << "entrei no else" << endl;
        NodeAvp* p = this->raiz;
        // cout << "prestes a entrar no print aux" << endl;
        printAux(p);
        cout << "sai do print aux" << endl;
    }
        
}

void ArvoreVP::printAux(NodeAvp* p)
{
    cout << "entrou no printAux" << endl;


    if(p->getLeft() != NULL)
        printAux(p->getLeft());
    else
    {
        cout << "---------- No --------" << endl;
        cout << "ID: " << p->getId() << endl;
        cout << "----------------------" << endl;
        cout << "COR: " << p->getColor() << endl;
        cout << "----------------------" << endl;
    }
    if(p->getRigth() != NULL)
        printAux(p->getRigth());
    cout << "bla" << endl;
}

ProductReview* ArvoreVP::busca(string userId, string productId)
{
    comparacoes = 0;
    tempo = 0;

    clock_t tempoInicio, tempoFim;
    tempoInicio = clock();

    string id = userId + productId; //concatena as strings para buscar o id
    NodeAvp* raizAux = this->raiz;
    if(raizAux != NULL) //se raiz for diferente de null
    {
        NodeAvp* no = buscaAux(raizAux, id); //no recebe o no com o id compativel
        if(no != NULL) //se no for diferenre de null
        {
            
            tempoFim = clock();
            float tempoTotal = float(tempoFim - tempoInicio) / float(CLOCKS_PER_SEC);
            this->tempo = this->tempo + tempoTotal;
            return no->getProduct();
        }
        else
        {
           
            //caso não seja encontrado
            cout << " == ID NÃO ENCONTRADO ==" << endl;
            tempoFim = clock();
            float tempoTotal = float(tempoFim - tempoInicio) / float(CLOCKS_PER_SEC);
            this->tempo = this->tempo + tempoTotal;
            return NULL;
        }
    }
}

//faz uma busca binaria
NodeAvp* ArvoreVP::buscaAux(NodeAvp * node, string id)
{
    //caso o no seja nulo ou com o valor compativel
    if(node == NULL || node->getId() == id)
    {
        comparacoes ++;
        return node;
    }

    //caso o id seja maior que o atual
    if( id > node->getId())
    {
        comparacoes ++;
        return buscaAux(node->getRigth(), id);
    } 
    else 
    {
        //caso o id seja menor que o atual
        comparacoes ++;
        return buscaAux(node->getLeft(), id);
    }
}

