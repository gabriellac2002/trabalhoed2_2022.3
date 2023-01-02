#ifndef BTreeNode_H_INCLUDED
#define BTreeNode_H_INCLUDED

using namespace std;

class BTreeNode
{
    private:
        int *keys; //Um array de chaves
        int t; // Grau minimo (define a faixa de nº de chaves)

        BTreeNode **C; //Uma matriz de ponteiros filhos
        int n; //Número atual de chaves
        bool leaf; //É verdadeiro quando o nó é folha. Caso contrário, é falso

    public:
        BTreeNode(int _t, bool _leaf); //Construtor
        
        //Uma função para percorrer todos os nós em uma subárvore com raiz enraizada com este nó
        void traverse();

        //Uma função para pesquisar uma chave na subárvore com raiz enraizada com este nó
        BTreeNode *search(int k); //retorna NULL se a chave não for encontrada
};

#endif // BTreeNode_H_INCLUDED