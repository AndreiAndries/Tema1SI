#include <iostream>
class nodeA{
    private:
    unsigned char* cryptedKey;
    unsigned char kPrim[256] = "a^dM!g?Ol$izEBlI";
    char modDeOperare[256];
    bool confirmareComunicare;
    char numeFisier[256];
    char text[256];

    public:

    nodeA(){
    }
    void seteazaText(char txt[]){
        strcpy(text,txt);
    } 

    char* getText(){
        return text;
    }

    void setModDeOperare(char mod[]){
        strcpy(modDeOperare,mod);
        std::cout<<"NOD A: "<<modDeOperare<<'\n';
    }

    void setConfirmareComunicare(bool confirmare){
       confirmareComunicare = confirmare;
    }
    

    char* getModDeOperare(){
        return modDeOperare;
    }

    bool getConfirmareComunicare(){
        return confirmareComunicare;
    }

    bool trimiteSemnal(){
        return true;
    }

    //--- primeste cheia criptata K de la KM
    void primesteCheia(unsigned char cheie[]){
        cryptedKey = cheie;
        std::cout<<"Nod A: cheie primita = "<<cheie<<"\n";
    }

    //--- primeste mesaj de la nodul B ca comunicarea poate incepe
    void primesteMesajDeConfirmare(bool mesaj){
        setConfirmareComunicare(mesaj);
        std::cout<<"Nod A: "<< confirmareComunicare << "\n";
    }

    unsigned char* getCryptedKey(){
        return cryptedKey;
    }

    void setNumeFisier(char nume[30]){
        strcpy(numeFisier,nume);
        std::cout<<"Nod A: "<<numeFisier<<"\n";
    }
    
    char* getNumeFisier(){
        return numeFisier;
    }

    char* encECB(char text[]){
        char textCriptat[256];
        unsigned char txt[256];
        unsigned char encOut[256];
        encOut[0] = '\0';
        for(int i = 0 ; i <= (strlen(text)-1)/16 ; ++i){
            txt[0] = '\0';
            for(int j = 0 ; j < 16 ; ++j){
                if(16*i+j<strlen(text)){
                    txt[j] = text[16*i+j];
                }else{
                    txt[j]=' ';
                }
            }
            AES_KEY encKey;
            AES_set_encrypt_key(cryptedKey,128,&encKey);
            AES_encrypt(txt,encOut,&encKey);
            strcat(textCriptat,reinterpret_cast<char*>(encOut));
            encOut[0]='\0';
        }
        char* p = textCriptat;
        return p;
    }

    
    void xorCalc (int lung,unsigned char *a, unsigned char *b, unsigned char *c){
        for (int i=0;i<lung;++i){
            c[i]=a[i]^b[i];
        }
    }

    char *encOFB(char text[], unsigned char key[], unsigned char vector[]){
        unsigned char *bloc=new unsigned char[256];
        unsigned char blocCurent[256];
        unsigned char text1[256];
        char* cipherfinal=new char[256];
        AES_KEY enc_key;
        AES_set_encrypt_key(key,128,&enc_key);
        AES_encrypt(vector, bloc,&enc_key);
        for (int i=0;i<=(strlen (text)-1)/16;++i){
            unsigned char * ciphertext1=new unsigned char [256];
            int val=16;
            ciphertext1[0]='\0';
            text1[0]='\0';
            for (int j=0;j<16;++j){
                if (16*i+j<strlen(text))
                    text1[j]=text[16*i+j];
                else{
                    val=j;
                    break;
                }
            }
            int min;
            if (strlen((char*)(bloc))>val)
                min=val;
            else
                min=strlen((char*)(bloc));
            xorCalc(min,bloc,text1,ciphertext1);
            strcat(cipherfinal,reinterpret_cast<char *>(ciphertext1));
            delete ciphertext1;
            if (i!=(strlen (text)-1)/16 ){
                AES_KEY enc_key1;
                AES_set_encrypt_key(key,128,&enc_key);
                for (int i=0;i<=strlen ((char*)(bloc));++i)
                    blocCurent[i]=bloc[i];
                bloc[0]='\0';
                delete bloc;
                bloc =new unsigned char[256];
                AES_encrypt(blocCurent, bloc,&enc_key);
            }else{
                delete bloc;
                bloc =new unsigned char[256];
            }
        }
        return cipherfinal;
    }

    void cripteaza(char numeleFisierului[],unsigned char vectorDeInitializare[256]){
        char* s;
        std::cout<<"Nod A : Incepe criptatrea{\n"<<modDeOperare<<"\n";
        std::string txt1;
        char* text1 = new char[1000];
        int nr=0;
        std::ifstream fin(numeleFisierului);
        if(fin.is_open()){
            while (fin>>txt1)
            {
                for(int i = 0 ;i<txt1.length();++i){
                    text1[nr++] = (char)txt1[i];
                }
                text1[nr++] = ' ';
            }
            fin.close();
        }
        strcpy(text1,text1+3);
        for(int i= 0 ; i<nr-2 ; ++i)
            std::cout<<text1[i];
        std::cout<<"\n";
        if(!strcmp(modDeOperare,"OFB")){
            std::cout<<"MOD OFB\n";
            //strcpy(s,encOFB(text,cryptedKey,vectorDeInitializare));
            std::cout<<encOFB(text1,cryptedKey,vectorDeInitializare);
        }else{
            s=encECB(text1);
        }
        seteazaText(s);
        std::cout<<"}gata criptarea\n";
    }
};