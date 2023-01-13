#ifndef NodeHuffman_H_INCLUDED
#define NodeHuffman_H_INCLUDED

class NodeHuffman {
    private:
        char content;
        long frequence;
        NodeHuffman *left, *right;

    public:
        NodeHuffman(char content, long fequence);
        virtual ~NodeHuffman();

        char getContent();
        void setContent(char content);
        long getFrequence();
        void setFrequence(long fequence);
        NodeHuffman *getLeft();
        NodeHuffman *getRight();
        void setLeft(NodeHuffman *left);
        void setRight(NodeHuffman *right);
        int isLeaf();
};

#endif // NodeHuffman_H_INCLUDED