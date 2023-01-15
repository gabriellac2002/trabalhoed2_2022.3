#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include "string.h"

#include "../Headers/NodeAvp.h"
#include "../Headers/ArvoreVP.h"



using namespace std;

//construtor
ArvoreVP::ArvoreVP()
{
    this->raiz = NULL;
}

//destrutor
ArvoreVP::~ArvoreVP()
{
    this->raiz = libera(raiz);
}

//getters and setters
void ArvoreVP::setRaiz(NodeAvp* raiz)
{
    this->raiz = raiz;
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

void ArvoreVP::insere(ProductReview *pr, int* comparacoes)
{
    string concatenacao = pr->getUserId() + pr->getProductId(); // concatena o userId com o productId
    NodeAvp* p = new NodeAvp(concatenacao, 1); //manda concatenacao como id e a posicao do productReview

    //inserção usando busca binaria
    NodeAvp* raiz = insereAux(getRaiz(), p, comparacoes);
    repair(raiz,p); // conserta os erros
    
}

NodeAvp* ArvoreVP::insereAux(NodeAvp* raiz, NodeAvp* no, int* comparacoes)
{
    //caso a arvore esteja vazia
    if(raiz == NULL)
    {
       (*comparacoes)++; // compara uma vez
       return raiz; //retorna raiz
    }
    else
    {
        //Caso contrario, faz uma busca binaria recursiva pela arvore para inserir o No no lugar certo
        //caso a raiz seja maior
        if(raiz->getId() > no->getId())
        {
            (*comparacoes)++;
            raiz->setLeft(insereAux(raiz->getLeft(), no, comparacoes));
            raiz->getLeft()->setParent(raiz);
        }
        else
        {
            //caso a raiz seja menor
            (*comparacoes)++;
            raiz->setRigth(insereAux(raiz->getRigth(), no, comparacoes));
            raiz->getRigth()->setParent(raiz);
        }

        return raiz;
    }
}

void ArvoreVP::repair(NodeAvp* node1, NodeAvp* node2)
{
    //node1 -> raiz local
    //node2 -> no inserido/no local

    NodeAvp* pai = NULL; //cria o pai auxiliar
    NodeAvp* avo = NULL; // criz o avo auxilar

    //enquanto node2 for diferente de node1,node2 for diferente de preto e o pai de node2 for vermelho
    while((node2 !=  node1) && (node2->getColor() != 0) && (node2->getParent()->getColor() == 1))
    {
        pai = node2->getParent(); //pai vira o pai de node2
        avo = node2->getParent()->getParent(); //avo vira pai do pai de node2

        //Caso : 1
        //pai do no conflitante está a esquerda do avo de pai
        if(pai == avo->getLeft())
        {
            NodeAvp* tio = avo->getRigth();

            //se tio for diferente de null e for vermelho 
            if(tio != NULL && tio->getColor() == 1)
            {
                avo->setColor(1); // avo vira vermelho
                pai->setColor(0); // pai vira preto
                tio->setColor(0); // tio vira preto
                node2 = avo;
            }
            else
            {
                // o no conflitante esta a direita de seu pai entao rotaciona para a esquerda
                if(node2 == pai->getRigth())
                {
                    rotateLeft(pai);
                    node2 = pai;
                    pai = node2->getParent();
                }

                //o no conflitante esta a esquerda de seu pai entao rotaciona para a direita
                rotateRight(avo);

                //ajuste de cores
                int corAux = pai->getColor();
                pai->setColor(avo->getColor());
                avo->setColor(corAux);

                node1 = pai;
            }
        }
        else
        {
            // Caso : 2
            // pai do no conflitante é o filho da direita de seu avo

            NodeAvp* tio = avo->getLeft();

            // o tio do no conflitante tambem e vermelho
            if((tio != NULL) && (tio->getColor() == 1))
            {
                avo->setColor(1);
                pai->setColor(0);
                tio->setColor(0);
                node2 = avo;
            }
            else
            {
                // o no conflitante esta a esquerda de seu pai entao rotaciona para a direita
                if(node2 == pai->getLeft())
                {
                    rotateRight(pai);
                    node2 = pai;
                    pai = node2->getParent();
                }

                // o no conflitante esta a direita de seu pai entao rotaciona para a esquerda
                rotateLeft(avo);

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
    if(this->raiz == NULL)
        cout << "Arvore vazia!" << endl;
    else{
        NodeAvp* p = this->raiz;
        printAux(p);
    }
        
}

void ArvoreVP::printAux(NodeAvp* p)
{
    printAux(p->getLeft());
    cout << "---------- No --------" << endl;
    cout << "ID: " << p->getId() << endl;
    cout << "----------------------" << endl;
    printAux(p->getLeft());
}

ProductReview* ArvoreVP::busca(string userId, string productId, int *comparacoes)
{
    string id = userId + productId; //concatena as strings para buscar o id
    NodeAvp* raizAux = this->raiz;
    if(raizAux != NULL) //se raiz for diferente de null
    {
        NodeAvp* no = buscaAux(raizAux, id, comparacoes); //no recebe o no com o id compativel
        if(no != NULL) //se no for diferenre de null
        {
            int pos = no->getEndMemory(); //pos recebe a posicao no binario
            // return returnRegister(,pos);
        }
        else
        {
            //caso não seja encontrado
            cout << " == ID NÃO ENCONTRADO ==" << endl;
            return NULL;
        }
    }
}

//faz uma busca binaria
NodeAvp* ArvoreVP::buscaAux(NodeAvp * node, string id, int* comparacoes)
{
    //caso o no seja nulo ou com o valor compativel
    if(node == NULL || node->getId() == id)
    {
        (*comparacoes)++;
        return node;
    }

    //caso o id seja maior que o atual
    if( id > node->getId())
    {
        (*comparacoes)++;
        return buscaAux(node->getRigth(), id, comparacoes);
    } 
    else 
    {
        //caso o id seja menor que o atual
        (*comparacoes)++;
        return buscaAux(node->getLeft(), id, comparacoes);
    }
}

