#include <iostream>
#include <windows.h> // BIBLIOTECA DO TEMPORIZADOR USADO LÁ NA MAIN

using namespace std;

int L=0, C=0; // VARIAVEL GLOBAL


struct Quadrado{
    bool preta;
    bool ocupado;
    string jogador; // JOGADOR: X == 1 /// JOGADOR: O == 2
};

void  ConfiguracaoInicialTabuleiro(Quadrado matriz[][8]){

     for(int i=0; i<8; i++){ //VERIFICAR SE A CASA É PRETA
         for(int j=0; j<8; j++){
            if((i%2 == 0 && j%2==0) || (i%2 != 0 && j%2!=0)){ // VERIFICAR SE A CASA É |||PRETA|||
                matriz[i][j].preta =true; // SE FOR PRETA RECEBERÁ "VERDADEIRO" INDICANDO QUE PODE SER OCUPADA
            }
            else
            {
                matriz[i][j].preta = false;
            }
        }
    }

    for(int i=0; i<8; i++){ //APÓS VERIFICAR SE A CASA É PRETA, DEFININDO OS JOGADORES NO TABULEIRO
         for(int j=0; j<8; j++){
            if(matriz[i][j].preta == true){
                if(i<3){
                    matriz[i][j].jogador = " x ";
                }
                else if(i>4){
                    matriz[i][j].jogador = " o ";
                }
                else
                    matriz[i][j].jogador = "   ";

            }
         }
    }


    for(int i=0; i<8; i++){ //APÓS VERIFICAR SE A CASA É PRETA e DEFININDO OS JGDRS NO TABULEIRO,VERIFICAR SE A CASA ESCOLHIDA ESTÁ DISPONIVEL
         for(int j=0; j<8; j++){
            if((matriz[i][j].preta == true && matriz[i][j].jogador== " x ") || matriz[i][j].preta == true && matriz[i][j].jogador== " o "){
                matriz[i][j].ocupado=true; // SE A CASA ESTIVER OCUPADA VAI RECEBER "VERDADEIRO"
            }
            else if (matriz[i][j].preta == true) {
                matriz[i][j].ocupado=false;
            }
        }
    }

}

void imprimirTabuleiro(Quadrado matriz[][8]){ // FUNÇÃO USADA PARA VIZUALIZAÇÃO GRAFICA DO TABULEIRO


     int i,k,j,l, p=0; //i PERCORRER SUBLINHA, k PERCORRER LINHA, j "COLUNA", l LINHA FINAL, p CONTADOR PARA OS NUMEROS ANTES DO TABULERO

     for(j=0; j<8; j++){ // LINHA

        cout<<"     ";//5 ESPAÇOS - ESPAÇAMENTO ENTRE A MARGEM E O TABULEIRO

        for(k=0; k<8; k++){  // !!!! COLUNA !!! ----- >  LINHA |---|---|---|---|---|---|---|---

            cout<<"|---";

            if(k==7){
                cout<<"|"; // COLUNA FINAL DA LINHA
            }
        } // FIM DO LAÇO K

        cout<<endl;
        cout<<"   "<<p<<" "; //p ESTÁ SENDO USADO PARA EXIBIR A NUMERAÇÃO ANTES DO TABULEIRO

        for(i=0; i<8; i++){ // !!!! COLUNA SECUNDARIA !!!!!! --->  SUBLINHA  |---|   |---|   |---|   |---|   |
			if (matriz[j][i].preta == true){
				cout<<"|"<<matriz[j][i].jogador;
				if(i==7){
                    cout<<"|"; // COLUNA FINAL DA LINHA
                }

			}
            else if(matriz[j][i].preta==false){  //ESPAÇOS BRANCOS
                cout<<"||||";
                if(i==7){
                    cout<<"|"; // COLUNA FINAL DA LINHA
                }
            }

        }//FIM DO LAÇO I

        //ULTIMA LINHA DA TABULEIRO
        cout<<endl;
        if(j==7){
            cout<<"     "; //5 - ESPAÇAMENTO ENTRE A MARGEM E O TABULERO
            for(l=0; l<8; l++){
                cout<<"|---";
                if(l==7){
                    cout<<"|"; // COLUNA DA LINHA FINAL
                }
            }
        }
        p++; // CONTADOR UTILIZADO PARA MOSTRAR OS NUMEROS ANTES DO TABUELEIRO
    } // FINAL DO LAÇO J

} // FIM DA FUNÇÃO imprimirTabuleiro

void ComerPecas(int LA, int CA, int LP, int CP, Quadrado matriz[][8], int jogador,int &cont1, int &cont2){

    bool achou=false;

     int novalinha,novacoluna;

    if (jogador==2){
        //SAINDO DA ESQUERDA INFERIOR /
        if(matriz[LA][CA].jogador  == " o " && matriz[LA-1][CA+1].jogador  == " x " && matriz[LA-2][CA+2].jogador  == "   "){
            if(matriz[LP][CP].jogador == matriz[LA-2][CA+2].jogador ){
                L=LA-1;
                C=CA+1;
                matriz[LA][CA].jogador ="   ";
                matriz[L][C].jogador="   ";
                matriz[LP][CP].jogador =" o ";
                cont1--;
                achou=true;
            }
        }
        else if(matriz[LA][CA].jogador == " o " && matriz[LA-1][CA+1].jogador == "   " && LA-1==LP && CA+1== CP){ // PARA PULAR SÓ UMA CASA
            if(matriz[LP][CP].jogador == matriz[LA-1][CA+1].jogador){
                matriz[LA][CA].jogador="   ";
                matriz[LP][CP].jogador=" o ";
                achou=false;

            }
        }

        //SAINDO DA DIREIRA INFERIOR \

        else if(matriz[LA][CA].jogador  == " o " && matriz[LA-1][CA-1].jogador  == " x " && matriz[LA-2][CA-2].jogador  == "   "){
           if(matriz[LP][CP].jogador == matriz[LA-2][CA-2].jogador){
                L=LA-1;
                C=CA-1;
                matriz[LA][CA].jogador="   ";
                matriz[L][C].jogador="   ";
                matriz[LP][CP].jogador=" o ";
                cont1--;
                achou = true;

           }
        }

        else if(matriz[LA][CA].jogador == " o " && matriz[LA-1][CA-1].jogador == "   "&& LA-1==LP && CA-1== CP){ // PARA PULAR SÓ UMA CASA
            if(matriz[LP][CP].jogador == matriz[LA-1][CA-1].jogador){
                matriz[LA][CA].jogador="   ";
                matriz[LP][CP].jogador=" o ";
                achou=false;
            }
        }
        if(achou==true){
            cout<<endl<<"ACHEI MAIS UMA BORA COMER!"<<endl<<endl; // isso aqui é so pra testar se ta entrando nesse if
            LA=LP;
            CA=CP;
            if((matriz[LA][CA].jogador  == " o " && matriz[LA-1][CA-1].jogador  == " x " && matriz[LA-2][CA-2].jogador  == "   ")
           || (matriz[LA][CA].jogador  == " o " && matriz[LA-1][CA+1].jogador  == " x " && matriz[LA-2][CA+2].jogador  == "   ")){

            cout<<"informe a nova linha:"<<endl;
            cin>>novalinha;
            cout<<"informe a nova coluna:"<<endl;
            cin>>novacoluna;
            LP=novalinha;
            CP=novacoluna;
            achou=false;
            ComerPecas(LA, CA, LP, CP, matriz, jogador, cont1, cont2);
            }
        }
    }

    if(jogador==1){ //
        //SAINDO DA ESQUERDA SUPERIOR /

       if(matriz[LA][CA].jogador == " x " && matriz[LA+1][CA-1].jogador == " o " && matriz[LA+2][CA-2].jogador == "   "){//PARA COMER PEÇA
            if(LP==LA+2 && CP==CA-2){
                //matriz[LP][CP].jogador == matriz[LA+2][CA-2].jogador
                L=LA+1;
                C=CA-1;
                matriz[LA][CA].jogador="   ";
                matriz[L][C].jogador="   ";
                matriz[LP][CP].jogador=" x ";
                cont2--;
                achou = true;
            }
        }
         else if(matriz[LA][CA].jogador == " x " && matriz[LA+1][CA-1].jogador == "   "&& LA+1==LP && CA-1== CP){ // PARA PULAR SÓ UMA CASA
            if(matriz[LP][CP].jogador == matriz[LA+1][CA-1].jogador){
                matriz[LA][CA].jogador="   ";
                matriz[LP][CP].jogador=" x ";
                achou=false;
            }
        }

        //SAINDO DA DIREIRA SUPERIOR \

        else if(matriz[LA][CA].jogador == " x " && matriz[LA+1][CA+1].jogador  == " o " && matriz[LA+2][CA+2].jogador  == "   "){
            if(LP==LA+2 && CP==CA+2){
                //matriz[LP][CP].jogador  == matriz[LA+2][CA+2].jogador
                L=LA+1;
                C=CA+1;
                matriz[LA][CA].jogador ="   ";
                matriz[L][C].jogador="   ";
                matriz[LP][CP].jogador= " x ";
                cont2--;
                achou = true;
            }
        }
        else if(matriz[LA][CA].jogador == " x " && matriz[LA+1][CA+1].jogador == "   " && LA+1==LP && CA+1== CP){ // PARA PULAR SÓ UMA CASA
            if(matriz[LP][CP].jogador == matriz[LA+1][CA+1].jogador){
                matriz[LA][CA].jogador="   ";
                matriz[LP][CP].jogador=" x ";
                achou=false;

            }
        }

        if(achou==true){
            cout<<endl<<"ACHEI MAIS UMA BORA COMER!"<<endl<<endl; // isso aqui é so pra testar se ta entrando nesse if
            LA=LP;
            CA=CP;
            if((matriz[LA][CA].jogador == " x " && matriz[LA+1][CA-1].jogador == " o " && matriz[LA+2][CA-2].jogador == "   ")
                || (matriz[LA][CA].jogador == " x " && matriz[LA+1][CA+1].jogador == " o " && matriz[LA+2][CA+2].jogador == "   ")){

            cout<<"informe a nova linha:"<<endl;
            cin>>novalinha;
            cout<<"informe a nova coluna:"<<endl;
            cin>>novacoluna;
            LP=novalinha;
            CP=novacoluna;
            achou=false;
            ComerPecas(LA, CA, LP, CP, matriz, jogador, cont1, cont2);
            }
        }
    }

}

void VerificaDestinoValida(int &LP, int &CP,Quadrado matriz[][8] ){
       while (matriz [LP][CP].jogador != "   "){
                cout<<endl<<endl<<endl<<"destino invalido, tente novamente: "<<endl<<endl<<endl<<endl;
                cout<<"informe a linha que deseja colocar a peca: "<<endl;
                cin>>LP;
                cout<<"informe a coluna que deseja colocar a peca: "<<endl;
                cin>>CP;

       }
}

void VerificaPecaValida (int &LA, int &CA,Quadrado matriz[][8],int jogador){ //FUNÇÃO CRIADA PARA AVALIAR SE A PEÇA QUE O ATUAL JOGADOR ESTÁ TENTANDO MEXER É DELE, CASO NÃO SEJA ELE PODERÁ TENTAR UMA OVA VEZ!!!
    if(jogador==1){
        while (matriz [LA][CA].jogador != " x "){
            cout<<endl<<endl<<endl<<"Esta peca nao eh a sua, tente novamente: "<<endl<<endl<<endl<<endl;
            cout<<"Informe a linha que deseja colocar a peca: "<<endl;
            cin>>LA;
            cout<<"informe a coluna que deseja colocar a peca: "<<endl;
            cin>>CA;
        }
    }
    else {
        while (matriz [LA][CA].jogador != " o "){
            cout<<endl<<endl<<endl<<"Esta peca nao eh a sua, tente novamente: "<<endl<<endl<<endl<<endl;
            cout<<"Informe a linha que deseja colocar a peca: "<<endl;
            cin>>LA;
            cout<<"Informe a coluna que deseja colocar a peca: "<<endl;
            cin>>CA;
        }
    }

}

void VerificaOrigemValida (int &LA, int &CA,Quadrado matriz[][8]){ // FUNÇÃO CRIADA PARA VALIDA SE A ORIGEM DA PEÇA À SER MOVIDA É VALIDO!!!

        while (matriz [LA][CA].preta == false){ // SE PRETO FOR FALSO, ENTÃO O JOGADOR ESTÃO TENTANDO MEXER NAS CASAS BRANCAS
            cout<<endl<<endl<<endl<<"Origem invalida!! Tente novamente: "<<endl<<endl<<endl<<endl;
            cout<<"Informe a linha que deseja retirar a peca: "<<endl;
            cin>>LA;
            cout<<"Informe a coluna que deseja retirar a peca: "<<endl;
            cin>>CA;
        }
}

int main(){

    Quadrado matriz [8][8];
    int i, k, j, l, cont1=12, cont2=12, jogador =1;
    int PosAntLinha, PosPostLinha;
    char PosAntColuna, PosPostColuna;
    int opcao, ca,cp; //ca == coluna anterior --- cp == coluna posterior


    cout << "         _______     _______   __       ___    _______     _______ " << endl;
    cout << "        |  _ _  |   |   _   | |  |     |   |  |   _   |   |   ____|" << endl;
    cout << "        | |   |  |  |  | |  | |   |   |    |  |  | |  |  |   |     " << endl;
    cout << "        | |    |  | |  |_|  | |    |_|     |  |  |_|  |  |   |___  " << endl;
    cout << "        | |    |  | |       | |   _    _   |  |       |   |___   | " << endl;
    cout << "        | |__ |  |  |   _   | |  | |  | |  |  |   _   |   ____|   |" << endl;
    cout << "        |_______|   |__| |__| |__| |__| |__|  |__| |__|  |_______| " << endl;

    cout<<endl<<endl<<endl<<endl<<endl;
    cout<<"                                SEJA BEM VINDO!                         " <<endl<<endl;

    cout<<endl<<endl<<endl<<endl<<endl;

    cout<<"                                  loading...                             " <<endl<<endl<<endl;
    Sleep(5000);
    system("cls");//  TEMPORIZADOR para exibição de "DAMAS" E "SEJA BEM VINDO"


    cout << "         _______     _______   __       ___    _______     _______ " << endl;
    cout << "        |  _ _  |   |   _   | |  |     |   |  |   _   |   |   ____|" << endl;
    cout << "        | |   |  |  |  | |  | |   |   |    |  |  | |  |  |   |     " << endl;
    cout << "        | |    |  | |  |_|  | |    |_|     |  |  |_|  |  |   |___  " << endl;
    cout << "        | |    |  | |       | |   _    _   |  |       |   |___   | " << endl;
    cout << "        | |__ |  |  |   _   | |  | |  | |  |  |   _   |   ____|   |" << endl;
    cout << "        |_______|   |__| |__| |__| |__| |__|  |__| |__|  |_______| " << endl;
    cout<<endl<<endl<<endl<<endl;

        cout<<"Escolha uma das opcoes:"<<endl;
        cout<<" JOGAR           | 1 |"<<endl;
        cout<<" SAIR            | 2 |"<<endl;
        cin>>opcao;

        if(opcao != 1 && opcao != 2){
            cout<<"opcao invalida!! tente novamente"<<endl<<endl;
            cout<<"Escolha uma das opcoes:"<<endl;
            cout<<" JOGAR          | 1 |"<<endl;
            cout<<" SAIR           | 2 |"<<endl;
            cin>>opcao;
            cout<<endl<<endl<<endl;
        }

        if(opcao == 1){

            cout<<endl;
            cout<<"           JOGADOR 1, SUA PECA SERA: x"<<endl;
            cout<<"           JOGADOR 2, SUA PECA SERA: o" <<endl<<endl;

            ConfiguracaoInicialTabuleiro(matriz);
            cout<<"                 BOM JOGO!!!    "<<endl<<endl<<endl;
            cout<<"       a   b   c   d   e   f   g   h   "<<endl;
            imprimirTabuleiro(matriz);
            cout<<endl<<"       a   b   c   d   e   f   g   h   "<<endl<<endl<<endl;


        }
        else if(opcao == 2){
            cout<<endl<<endl;
            cout<<"ATE LOGO ^^ ";
            return 0;
        }


    while ((cont1!=0 && cont2>0)|| (cont1>0 && cont2!=0)){

        cout<<"VEZ DO JOGADOR "<<jogador<<endl<<endl;

        cout<<"Informe a linha que deseja retirar a peca: "<<endl;
        cin>>PosAntLinha;

        cout<<"Informe a coluna que deseja retirar a peca: "<<endl;
        cin>>PosAntColuna;

        switch(PosAntColuna){
        case'a':
            ca=0;
            break;
        case'b':
            ca=1;
            break;
        case'c':
            ca=2;
            break;
        case'd':
            ca=3;
            break;
        case'e':
            ca=4;
            break;
        case'f':
            ca=5;
            break;
        case'g':
            ca=6;
            break;
        case'h':
            ca=7;
            break;
        }


        VerificaOrigemValida(PosAntLinha, ca, matriz);
        VerificaPecaValida (PosAntLinha, ca, matriz,jogador);

        cout<<"Informe a linha que deseja colocar a peca: "<<endl;
        cin>>PosPostLinha;

        cout<<"Informe a coluna que deseja colocar a peca: "<<endl;
        cin>>PosPostColuna;

        switch(PosPostColuna){
        case'a':
            cp=0;
            break;
        case'b':
            cp=1;
            break;
        case'c':
            cp=2;
            break;
        case'd':
            cp=3;
            break;
        case'e':
            cp=4;
            break;
        case'f':
            cp=5;
            break;
        case'g':
            cp=6;
            break;
        case'h':
            cp=7;
            break;
        }


        VerificaDestinoValida(PosPostLinha, cp, matriz);


        ComerPecas(PosAntLinha, ca, PosPostLinha, cp,matriz,jogador,cont1,cont2);

        cout<<endl<<"       a   b   c   d   e   f   g   h   "<<endl;

        imprimirTabuleiro(matriz);

        cout<<endl<<"       a   b   c   d   e   f   g   h   "<<endl<<endl<<endl;

        cout<<endl;

        if(jogador==1){
            jogador=2;
        }
        else if(jogador==2){
            jogador=1;
        }

        if(cont1==0){

            cout<<endl<<endl;
            cout << "-------------------GAME OVER---------------------"<<endl;
            cout << "              JOGADOR 2 VENCEU!!!"<<endl;
            cout << "-------------------------------------------------"<<endl;

        }
        else if (cont2==0){

            cout<<endl<<endl;
            cout << "-------------------GAME OVER---------------------"<<endl;
            cout << "              JOGADOR 1 VENCEU!!!"<<endl;
            cout << "-------------------------------------------------"<<endl;
        }

    }

    return 0;
}

