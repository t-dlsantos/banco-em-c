#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include <string.h>

// COR DA LETRA
enum
{
    BLACK,        // 0
    BLUE,         // 1
    GREEN,        // 2
    CYAN,         // 3
    RED,          // 4
    MAGENTA,      // 5
    BROWN,        // 6
    LIGHTGRAY,    // 7
    DARKGRAY,     // 8
    LIGHTBLUE,    // 9
    LIGHTGREEN,   // 10
    LIGHTCYAN,    // 11
    LIGHTRED,     // 12
    LIGHTMAGENTA, // 13
    YELLOW,       // 14
    WHITE         // 15
};

// COR DO FUNDO
enum
{
    _BLACK = 0,          // 0
    _BLUE = 16,          // 1
    _GREEN = 32,         // 2
    _CYAN = 48,          // 3
    _RED = 64,           // 4
    _MAGENTA = 80,       // 5
    _BROWN = 96,         // 6
    _LIGHTGRAY = 112,    // 7
    _DARKGRAY = 128,     // 8
    _LIGHTBLUE = 144,    // 9
    _LIGHTGREEN = 160,   // 10
    _LIGHTCYAN = 176,    // 11
    _LIGHTRED = 192,     // 12
    _LIGHTMAGENTA = 208, // 13
    _YELLOW = 224,       // 14
    _WHITE = 240         // 15
};

typedef struct
{
    long long int cpf;
    int codigo;
    int senha;
    int data_nasc;
    int idade;
    char estado_civil[11];
    char nome[25];
    char sexo[20];
    float saldo;
} Cadastro;

Cadastro cliente;
FILE *leit;
FILE *cad;

void retangulo(int horizontal_inicial, int vertical_inicial, int larg, int alt);
void inicio();
void textColor(int letra, int fundo);
void linhaCol(int lin, int col);
void moveXY(int x, int y);
void box(int lin1, int col1, int lin2, int col2);
int ops(int x);
int fazerCad();
int acessarConta();
int menu(int lin1, int col1, int qtd, char lista[3][40]);
int aleatorios();
int posicaoregistro(int codigo);
float acessarsaldo(int posi);
void alterar(int posi, float novoval);

int main()
{
    system("MODE CON cols=100 lines=20");

    inicio();

    return 0;
}

void inicio()
{
    int opc;
    char entrada[5][40] = {"Fazer Cadastro", "Acessar Conta", "Sair"};

    while (opc != 3)
    {
        system("cls");
        retangulo(22, 1, 51, 2);
        moveXY(37, 2);
        printf("Bem-vindo ao Banco SN");
        opc = menu(5, 38, 3, entrada);
        textColor(WHITE, _BLACK);

        switch (opc)
        {
        case 1:
            fazerCad();
            break;

        case 2:
            acessarConta();
            break;
        }
    }
}

void textColor(int letra, int fundo)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letra + fundo);
}

void linhaCol(int lin, int col)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){col - 1, lin - 1}); // coorddenada na tela
}

int menu(int lin1, int col1, int qtd, char lista[3][40])
{
    int opc = 1, lin2, col2, linha, i, tamMaxItem, tecla;

    // calcula as coordenadas
    tamMaxItem = strlen(lista[0]);

    // tamanho maximo do item
    for (i = 1; i < qtd; i++)
    {
        if (strlen(lista[i]) > tamMaxItem)
        {
            tamMaxItem = strlen(lista[i]);
        }
    }

    lin2 = lin1 + (qtd * 2 + 2);
    col2 = col1 + tamMaxItem + 4;

    // caixa
    textColor(WHITE, _BLACK);
    setlocale(LC_ALL, "C");
    box(lin1, col1, lin2, col2);
    setlocale(LC_ALL, "");

    // la?o das opc?es
    while (1)
    {
        linha = lin1 + 2;
        for (i = 0; i < qtd; i++)
        {
            if (i + 1 == opc)
            {
                textColor(LIGHTCYAN, _BLACK);
            }
            else
            {
                textColor(WHITE, _BLACK);
            }
            linhaCol(linha, col1 + 2);
            printf("%s", lista[i]);
            linha += 2;
        }

        // Aguarda tecla
        linhaCol(1, 1);
        tecla = getch();
        linhaCol(22, 1);

        // Op??o
        if (tecla == 13)
        { // ENTER
            break;
        }
        else if (tecla == 72)
        { // Seta para cima
            if (opc > 1)
                opc--;
        }
        else if (tecla == 80)
        { // seta para baixo
            if (opc < qtd)
                opc++;
        }
    }
    return opc;
}

void retangulo(int horizontal_inicial, int vertical_inicial, int larg, int alt)
{
    int horizontal, vertical;
    setlocale(LC_ALL, "C");
    textColor(LIGHTCYAN, _BLACK);

    // Linhas horizontais
    for (horizontal = horizontal_inicial; horizontal < horizontal_inicial + larg; horizontal++)
    {
        moveXY(horizontal, vertical_inicial);
        printf("%c", 205); // Imprime o caracter especial com retorno 206

        moveXY(horizontal, vertical_inicial + alt);
        printf("%c", 205);
    }

    // Linhas verticais
    for (vertical = vertical_inicial; vertical < vertical_inicial + alt; vertical++)
    {
        moveXY(horizontal_inicial, vertical);
        printf("%c", 186); // Imprime o Caracter Especial com retorno 186

        moveXY(horizontal_inicial + larg, vertical);
        printf("%c", 186);
    }
    // Cantos
    moveXY(horizontal_inicial, vertical_inicial);
    printf("%c", 201); // Imprime o caracter especial com retorno 201

    moveXY(horizontal_inicial, vertical_inicial + alt);
    printf("%c", 200); // Imprime o caracter especial com retorno 200

    moveXY(horizontal_inicial + larg, vertical_inicial);
    printf("%c", 187); // Imprime o caracter especial com retorno 187

    moveXY(horizontal_inicial + larg, vertical_inicial + alt);
    printf("%c", 188); // Imprime o caracter especial com retorno 188

    textColor(WHITE, _BLACK);
}

void moveXY(int x, int y)
{
    HANDLE h;
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(h, dwPos);
}

void box(int lin1, int col1, int lin2, int col2)
{
    int i, j, tamlin, tamcol;

    // achar o tamanho do box
    tamlin = lin2 - lin1;
    tamcol = col2 - col1;

    // Monta o caixa
    for (i = col1; i <= col2; i++)
    { // linhas
        linhaCol(lin1, i);
        printf("%c", 196);
        linhaCol(lin2, i);
        printf("%c", 196);
    }

    for (i = lin1; i <= lin2; i++)
    { // colunas
        linhaCol(i, col1);
        printf("%c", 179);
        linhaCol(i, col2);
        printf("%c", 179);
    }
    for (i = lin1 + 1; i < lin2; i++)
    {
        for (j = col1 + 1; j < col2; j++)
        {
            linhaCol(i, j);
            printf(" ");
        }
    }

    // Posi??o dos cantos
    linhaCol(lin1, col1);
    printf("%c", 218);
    linhaCol(lin1, col2);
    printf("%c", 191);
    linhaCol(lin2, col1);
    printf("%c", 192);
    linhaCol(lin2, col2);
    printf("%c", 217);
}

int ops(int x)
{
    int i = 2, j = 3, k = 4;
    int operacao, conta;
    int ver2, ver1, versaque = 0, verdeposito = 0, vertransferencia = 0, ver0, ver3, ver4;
    char operacoes[5][40] = {"Ver Saldo", "Saque", "Deposito", "Transferencia", "Extrato"};
    char listaresp[2][40] = {"Outra Operacao", "Sair"};
    float dep[100], saq[100], trans[100];
    float saldo, saque = 0.0, deposito = 0.0, transferencia = 0.0;
    char digitado[50];
    char c;
    int cont = 0;
    int transf;
    int config;
    float saldtr;

    do
    {
        operacao = menu(4, 39, 5, operacoes);

        linhaCol(3, 25);
        textColor(WHITE, _BLACK);

        switch (operacao)
        {
        case 1:
            system("cls");
            retangulo(25, 0, 42, 10);
            moveXY(26, 1);
            printf("Seu saldo eh de: R$%.2f\n", acessarsaldo(x));
            saldo = acessarsaldo(x);
            break;

        case 2:
            do
            {
                system("cls");
                retangulo(25, 0, 42, 10);
                moveXY(26, 1);
                printf("Digite a quantidade que deseja sacar: ");

                cont = 0;
                digitado[0] = '\0';
                i = 0;

                moveXY(26, 2);
                do
                {
                    c = getch();

                    if (isdigit(c) != 0)
                    {
                        digitado[i] = c;
                        i++;
                        printf("%c", c);

                        if (digitado[0] == 32)
                        {
                            digitado[0] = '\0';
                            i--;
                            printf("\b \b");
                        }
                    }

                    if (c == 8 && i)
                    {
                        digitado[i] = '\0';
                        i--;
                        printf("\b \b");

                        if (i == 0)
                        {
                            digitado[0] = '\0';
                        }
                    }

                    if (c == 13 && digitado[0] != 0)
                    {
                        cont++;
                    }

                } while (cont != 1 && i < 40);

                digitado[i] = '\0';
                saque = atof(digitado);

                if (saldo < saque)
                {
                    moveXY(26, 3);
                    printf("Saldo Insuficiente");
                    getch();
                }
                else
                {
                    system("cls");
                    retangulo(25, 0, 42, 10);
                    moveXY(26, 1);
                    printf("Operacao realizada com sucesso!");
                    moveXY(26, 2);
                    printf("Voce sacou %.2f", saque);
                    saldo -= saque;
                    saq[versaque] = saque;
                    versaque++;
                    moveXY(26, 3);

                    alterar(x, saldo);
                    acessarsaldo(x);

                    printf("Seu novo saldo \x82 de: %.2f", acessarsaldo(x));
                }
            } while (saque <= 0);
            break;

        case 3:
            moveXY(26, 2);
            do
            {
                system("cls");
                retangulo(25, 0, 42, 10);
                moveXY(26, 1);
                printf("Digite a quantidade a ser depositada: ");

                cont = 0;
                digitado[0] = '\0';
                i = 0;

                moveXY(26, 2);
                do
                {
                    c = getch();

                    if (isdigit(c) != 0)
                    {
                        digitado[i] = c;
                        i++;
                        printf("%c", c);

                        if (digitado[0] == 32)
                        {
                            digitado[0] = '\0';
                            i--;
                            printf("\b \b");
                        }
                    }

                    if (c == 8 && i)
                    {
                        digitado[i] = '\0';
                        i--;
                        printf("\b \b");

                        if (i == 0)
                        {
                            digitado[0] = '\0';
                        }
                    }

                    if (c == 13 && digitado[0] != 0)
                    {
                        cont++;
                    }

                } while (cont != 1 && i < 40);

                digitado[i] = '\0';
                deposito = atof(digitado);

                if (deposito <= 0)
                {
                    moveXY(26, 3);
                    printf("Insira um valor valido!");
                    getch();
                }
                else
                {
                    system("cls");
                    retangulo(25, 0, 42, 10);
                    moveXY(26, 1);
                    printf("Operacao realizada com sucesso!");
                    moveXY(26, 2);
                    printf("Voce depositou R$%.2f", deposito);
                    saldo += deposito;
                    dep[verdeposito] = deposito;
                    verdeposito++;
                    moveXY(26, 3);

                    alterar(x, saldo);
                    acessarsaldo(x);

                    printf("Seu novo saldo \x82 de: R$%.2f", acessarsaldo(x));
                }
            } while (deposito <= 0);
            break;

        case 4:
            do
            {
                do
                {
                    system("cls");
                    retangulo(25, 0, 42, 10);
                    moveXY(26, 1);
                    printf("Digite o codigo da conta: ");

                    cont = 0;
                    digitado[0] = '\0';
                    i = 0;
                    do
                    {
                        c = getch();

                        if (isdigit(c) != 0)
                        {
                            digitado[i] = c;
                            i++;
                            printf("%c", c);

                            if (digitado[0] == 32)
                            {
                                digitado[0] = '\0';
                                i--;
                                printf("\b \b");
                            }
                        }

                        if (c == 8 && i)
                        {
                            digitado[i] = '\0';
                            i--;
                            printf("\b \b");

                            if (i == 0)
                            {
                                digitado[0] = '\0';
                            }
                        }

                        if (c == 13 && digitado[1] != 0)
                        {
                            cont++;
                        }

                    } while (cont != 1 && i < 5);

                    digitado[i] = '\0';
                    conta = atoi(digitado);

                    cont = 0;
                    transf = posicaoregistro(conta);
                    if (transf != 20)
                    {
                        break;
                    }
                    else if (transf == 20)
                        ;
                    {
                        moveXY(26, 2);
                        printf("CODIGO NAO CADASTRO NA BASE DE DADOS");
                        moveXY(27, 9);
                        printf("Digite a tecla <ENTER> para continuar");
                        getch();
                        cont = 1;
                    }
                } while (cont == 1);

                moveXY(26, 2);
                printf("Insira a quantia: ");

                cont = 0;
                digitado[0] = '\0';
                i = 0;

                do
                {
                    c = getch();

                    if (isdigit(c) != 0)
                    {
                        digitado[i] = c;
                        i++;
                        printf("%c", c);

                        if (digitado[0] == 32)
                        {
                            digitado[0] = '\0';
                            i--;
                            printf("\b \b");
                        }
                    }

                    if (c == 8 && i)
                    {
                        digitado[i] = '\0';
                        i--;
                        printf("\b \b");

                        if (i == 0)
                        {
                            digitado[0] = '\0';
                        }
                    }

                    if (c == 13 && digitado[0] != 0)
                    {
                        cont++;
                    }

                } while (cont != 1 && i < 40);

                digitado[i] = '\0';
                transferencia = atof(digitado);

                if (transferencia <= 0)
                {
                    moveXY(26, 3);
                    printf("Insira um valor valido!\n\n");
                    getch();
                }
                else
                {
                    if (saldo < transferencia)
                    {
                        moveXY(26, 3);
                        printf("Saldo Insuficiente\n");
                        getch();
                    }
                    else
                    {
                        system("cls");
                        retangulo(25, 0, 42, 10);
                        moveXY(26, 1);
                        printf("Operacao realizada com sucesso!");
                        moveXY(26, 2);
                        printf("Voce transferiu %.2f para a conta %d", transferencia, conta);
                        saldo -= transferencia;
                        trans[vertransferencia] = transferencia;
                        vertransferencia++;

                        saldtr = acessarsaldo(transf);
                        saldtr += transferencia;
                        alterar(transf, saldtr);

                        alterar(x, saldo);
                        acessarsaldo(x);

                        moveXY(26, 3);
                        printf("Seu novo saldo \x82 de: R$%.2f\n", acessarsaldo(x));
                    }
                }
            } while (transferencia <= 0);
            break;

        case 5:
            moveXY(26, 2);
            system("cls");
            retangulo(25, 0, 42, 10);
            for (ver0 = 0; ver0 < versaque; ver0++)
            {
                moveXY(26, i);
                printf("Saque de R$%.2f\n", saq[ver0]);
                i++;
                j++;
                k++;
            }
            for (ver3 = 0; ver3 < verdeposito; ver3++)
            {
                moveXY(26, j);
                printf("Deposito de R$%.2f\n", dep[ver3]);
                i++;
                j++;
                k++;
            }
            for (ver4 = 0; ver4 < vertransferencia; ver4++)
            {
                moveXY(26, k);
                printf("Transferencia de R$%.2f", trans[ver4]);
                i++;
                j++;
                k++;
            }
            break;
        }

        ver2 = menu(12, 37, 2, listaresp);
        if (ver2 == 1)
        {
            ver1 = 0;
            system("cls");
        }
        else
        {
            ver1++;
        }
    } while (ver1 == 0);
}

int fazerCad()
{
    char vali[2][40] = {"Sim", "Nao"};
    char digitado[50];
    char c;
    char estadoCiv[5][40] = {"Solteiro(a)", "Casado(a)", "Divorcidado(a)", "Viuvo(a)", "Outro"};
    char sex[2][40] = {"Masculino", "Feminino"};
    int sx;
    int estdC;
    int i = 0;
    int numero = 0;
    int cont = 0;
    int conf;

    do
    {
        system("cls");
        retangulo(22, 3, 52, 10);
        moveXY(23, 4);
        printf("Digite seu nome: ");
        moveXY(23, 5);

        cont = 0;
        digitado[0] = '\0';
        i = 0;

        do
        {
            c = getch();

            if (isalpha(c) != 0 || c == 32)
            {
                digitado[i] = c;
                i++;
                printf("%c", c);

                if (digitado[0] == 32)
                {
                    digitado[0] = '\0';
                    i--;
                    printf("\b \b");
                }
            }

            if (c == 8 && i != 0)
            {
                digitado[i] = '\0';
                i--;
                printf("\b \b");
                if (i == 0)
                {
                    digitado[0] = '\0';
                }
            }

            if (c == 13 && digitado[1] != 0)
            {
                cont++;
            }

        } while (cont != 1 && i < 40);

        digitado[i] = '\0';

        strcpy(cliente.nome, digitado);

        moveXY(23, 7);
        printf("Essa informacao esta correta?");
        conf = menu(7, 58, 2, vali);
    } while (conf == 2);

    do
    {
        system("cls");
        retangulo(22, 3, 52, 10);
        moveXY(23, 4);
        printf("Insira sua idade: ");
        moveXY(23, 5);

        cont = 0;
        digitado[0] = '\0';
        i = 0;

        do
        {
            c = getch();

            if (isdigit(c) != 0)
            {
                digitado[i] = c;
                i++;
                printf("%c", c);

                if (digitado[0] == 32)
                {
                    digitado[0] = '\0';
                    i--;
                    printf("\b \b");
                }
            }

            if (c == 8 && i)
            {
                digitado[i] = '\0';
                i--;
                printf("\b \b");

                if (i == 0)
                {
                    digitado[0] = '\0';
                }
            }

            if (digitado[0] != 0)
            {
                cont++;
            }

        } while (i < 2);

        digitado[i] = '\0';
        cliente.idade = atoi(digitado);

        if (cliente.idade < 18)
        {
            moveXY(35, 11);
            printf("Apenas maiores de 18 anos!!\n");
            getch();
            return 0;
        }
        else
        {
            moveXY(23, 7);
            printf("Essa informacao esta correta?");
            conf = menu(7, 58, 2, vali);
        }

    } while (conf == 2 || cliente.idade < 18);

    do
    {
        system("cls");
        retangulo(22, 3, 52, 10);
        moveXY(23,5);
		printf("(FORMATO: ddmmaaaa)");
        moveXY(23, 4);
        printf("Insira sua data de nascimento: ");

        cont = 0;
        digitado[0] = '\0';
        i = 0;

        do
        {
            c = getch();

            if (isdigit(c) != 0)
            {
                digitado[i] = c;
                i++;
                printf("%c", c);

                if (digitado[0] == 32)
                {
                    digitado[0] = '\0';
                    i--;
                    printf("\b \b");
                }
            }

            if (c == 8 && i)
            {
                digitado[i] = '\0';
                i--;
                printf("\b \b");

                if (i == 0)
                {
                    digitado[0] = '\0';
                }
            }

            if (digitado[0] != 0)
            {
                cont++;
            }

        } while (i < 8);

        digitado[i] = '\0';
        cliente.data_nasc = atoi(digitado);

        moveXY(23, 7);
        printf("Essa informacao esta correta?");
        conf = menu(7, 58, 2, vali);
    } while (conf == 2);

    system("cls");
    retangulo(22, 1, 52, 14);
    moveXY(23, 2);
    printf("Insira seu estado civil: ");

    estdC = menu(3, 50, 5, estadoCiv);

    switch (estdC)
    {
    case 1:
        strcpy(cliente.estado_civil, "Solteiro(a)");
        break;
    case 2:
        strcpy(cliente.estado_civil, "Casado(a)");
        break;
    case 3:
        strcpy(cliente.estado_civil, "Divorciado(a)");
        break;
    case 4:
        strcpy(cliente.estado_civil, "Viuvo(a)");
        break;
    case 5:
        system("cls");
        retangulo(22, 3, 52, 10);
        moveXY(23, 4);
        printf("Insira seu estado civil: ");
        moveXY(23, 5);

        cont = 0;
        digitado[0] = '\0';
        i = 0;

        do
        {
            c = getch();

            if (isalpha(c) != 0 || c == 32)
            {
                digitado[i] = c;
                i++;
                printf("%c", c);

                if (digitado[0] == 32)
                {
                    digitado[0] = '\0';
                    i--;
                    printf("\b \b");
                }
            }

            if (c == 8 && i != 0)
            {
                digitado[i] = '\0';
                i--;
                printf("\b \b");
                if (i == 0)
                {
                    digitado[0] = '\0';
                }
            }

            if (c == 13 && digitado[0] != 0)
            {
                cont++;
            }

        } while (cont != 1 && i < 10);

        digitado[i] = '\0';
        strcpy(cliente.estado_civil, digitado);
        break;
    }

    do
    {
        system("cls");
        retangulo(22, 3, 52, 10);
        moveXY(23, 4);
        printf("Insira seu cpf: ");
        moveXY(23, 5);

        cont = 0;
        digitado[0] = '\0';
        i = 0;

        do
        {
            c = getch();

            if (isdigit(c) != 0)
            {
                digitado[i] = c;
                i++;
                printf("%c", c);

                if (digitado[0] == 32)
                {
                    digitado[0] = '\0';
                    i--;
                    printf("\b \b");
                }
            }

            if (c == 8 && i)
            {
                digitado[i] = '\0';
                i--;
                printf("\b \b");

                if (i == 0)
                {
                    digitado[0] = '\0';
                }
            }

            if (digitado[0] != 0)
            {
                cont++;
            }

        } while (i < 11);

        digitado[i] = '\0';
        cliente.cpf = atoi(digitado);

        moveXY(23, 7);
        printf("Essa informacao esta correta?");
        conf = menu(7, 58, 2, vali);
    } while (conf == 2);

    system("cls");
    retangulo(22, 3, 52, 10);
    moveXY(23, 4);
    printf("Insira seu sexo: ");

    sx = menu(5, 50, 2, sex);

    switch (sx)
    {
    case 1:
        strcpy(cliente.sexo, "Masculino(a)");
        break;
    case 2:
        strcpy(cliente.sexo, "Feminino(a)");
        break;
    }

    do
    {
        system("cls");
        retangulo(22, 3, 52, 10);
        moveXY(23, 4);
        printf("Digite uma senha numerica(MAXIMO 8 CARACTERES): ");
        moveXY(23, 5);

        cont = 0;
        digitado[0] = '\0';
        i = 0;

        do
        {
            c = getch();

            if (isdigit(c) != 0)
            {
                digitado[i] = c;
                i++;
                printf("%c", c);

                if (digitado[0] == 32)
                {
                    digitado[0] = '\0';
                    i--;
                    printf("\b \b");
                }
            }

            if (c == 8 && i)
            {
                digitado[i] = '\0';
                i--;
                printf("\b \b");

                if (i == 0)
                {
                    digitado[0] = '\0';
                }
            }

            if (c == 13 && digitado[0] != 0)
            {
                cont++;
            }

        } while (cont != 1 && i < 8);

        digitado[i] = '\0';
        cliente.senha = atoi(digitado);

        moveXY(23, 7);
        printf("Essa informacao esta correta?");
        conf = menu(7, 58, 2, vali);
    } while (conf == 2);

    cliente.saldo = 0;
    cliente.codigo = aleatorios();

    system("cls");
    retangulo(22, 3, 52, 10);
    moveXY(23, 4);
    printf("Codigo da sua conta: %d\n", cliente.codigo);
    moveXY(23, 6);
    printf("Seu cadastro foi realizado com sucesso!!\n\n");

    cad = fopen("Clientes", "ab+");
    fwrite(&cliente, sizeof(Cadastro), 1, cad);
    fclose(cad);

    moveXY(23, 7);
    printf("Pressione <ENTER> para confirmar");
    getch();
}

int acessarConta()
{
	int codigodig, senhadig;
    char digitado[50];
    char c;
    int i = 0;
    int numero = 0;
    int cont = 0;

    int x;

    do
    {
        system("cls");
        retangulo(22, 3, 52, 10);
        moveXY(23, 4);
        printf("Digite seu codigo: ");

        cont = 0;
        digitado[0] = '\0';
        i = 0;

        do
        {
            c = getch();

            if (isdigit(c) != 0)
            {
                digitado[i] = c;
                i++;
                printf("%c", c);

                if (digitado[0] == 32)
                {
                    digitado[0] = '\0';
                    i--;
                    printf("\b \b");
                }
            }

            if (c == 8 && i)
            {
                digitado[i] = '\0';
                i--;
                printf("\b \b");

                if (i == 0)
                {
                    digitado[0] = '\0';
                }
            }

            if (c == 13 && digitado[0] != 0)
            {
                cont++;
            }

        } while (cont != 1);

        digitado[i] = '\0';
        codigodig = atoi(digitado);

        moveXY(23, 5);
        printf("Digite sua senha: ");

        cont = 0;
        digitado[0] = '\0';
        i = 0;

        do
        {
            c = getch();

            if (isdigit(c) != 0)
            {
                digitado[i] = c;
                i++;
                printf("%c", c);

                if (digitado[0] == 32)
                {
                    digitado[0] = '\0';
                    i--;
                    printf("\b \b");
                }
            }

            if (c == 8 && i)
            {
                digitado[i] = '\0';
                i--;
                printf("\b \b");

                if (i == 0)
                {
                    digitado[0] = '\0';
                }
            }

            if (c == 13 && digitado[0] != 0)
            {
                cont++;
            }

        } while (cont != 1 && i < 8);

        digitado[i] = '\0';
        senhadig = atoi(digitado);

        cad = fopen("Clientes", "rb");

        if (!cad)
        {
            moveXY(23, 7);
            printf("Nenhum usuario cadastrado!!");
            getch();
            return 0;
        }
        else
        {
            while (fread(&cliente, sizeof(Cadastro), 1, cad))
            {
                if (cliente.codigo == codigodig && cliente.senha == senhadig)
                {
                    system("cls");
                    retangulo(22, 0, 50, 2);
                    moveXY(35, 1);
                    printf("Bem-vindo(a) novamente");
                    x = posicaoregistro(codigodig);
                    // printf("%d", x);
                    ops(x);
                    break;
                }
            }
            if (cliente.codigo != codigodig && cliente.senha != senhadig)
            {
                moveXY(23, 7);
                printf("Codigo/Senha Incorreto!!\n");
                getch();
            }
        }

    } while (cliente.codigo != codigodig || cliente.senha != senhadig || !cad);
    fclose(cad);
}

int aleatorios()
{
    int i, aleatorio;
    srand(time(NULL));

    for (i = 1; i <= 10; i++)
        aleatorio = rand();
}

int posicaoregistro(int codigo)
{ // com o codigo que a pessoa digitar iremos buscar a posi??o do registro no arquivo bin

    int k;
    int codigovet, n, nReg;
    size_t fSize;

    Cadastro *vCadastro; // vetor para cadastrar cada registro em um vetor[n]
    leit = fopen("Clientes", "rb");

    fseek(leit, 0L, SEEK_END);         // posiciona o vetor de abertura do arquivo no final deste
    fSize = ftell(leit);               // calcula o tamanho total do arquivo
    nReg = (fSize / sizeof(Cadastro)); // divide pelo tamanho de um Cadastro
    // printf("Tamanho do arquivo: %d(Bytes)\n", fSize);
    // printf("Numero de registros: %d\n\n",nReg);
    vCadastro = (Cadastro *)malloc(fSize);

    fseek(leit, 0L, SEEK_SET);
    n = 0;

    while (fread(&cliente, sizeof(Cadastro), 1, leit) > 0)
    {
        vCadastro[n] = cliente;
        n++;
    }

    for (n = 0; n < nReg; n++)
    {
        codigovet = vCadastro[n].codigo;
        // printf("%i\n", vCadastro[n].codigo);
        if (codigovet == codigo)
        {
            // printf("%d\n\n", n);
            return n;
            break;
        }
    }
    if (codigovet != codigo)
    {
        k = 20;
        return k;
    }
}

float acessarsaldo(int posi)
{
    leit = fopen("Clientes", "rb");
    fseek(leit, posi * sizeof(Cadastro), SEEK_SET);
    fread(&cliente, sizeof(Cadastro), 1, leit);
    return cliente.saldo;
    fclose(leit);
}

void alterar(int posi, float novoval)
{
    int nReg;
    size_t fSize;

    Cadastro *vCadastro; // vetor para cadastrar cada registro em um vetor vCadastro[n]
    leit = fopen("Clientes", "rb");

    fseek(leit, 0L, SEEK_END);
    fSize = ftell(leit);
    nReg = (fSize / sizeof(Cadastro));
    vCadastro = (Cadastro *)malloc(fSize);

    fseek(leit, posi * sizeof(Cadastro), SEEK_SET);

    while (fread(&cliente, sizeof(Cadastro), 1, leit) > 0)
    {
        vCadastro[posi] = cliente;
        break;
    }

    leit = fopen("Clientes", "rb+");
    fseek(leit, posi * sizeof(Cadastro), SEEK_SET);

    cliente.saldo = novoval;
    cliente.codigo = vCadastro[posi].codigo;
    cliente.senha = vCadastro[posi].senha;
    strcpy(cliente.nome, vCadastro[posi].nome);
    cliente.data_nasc = vCadastro[posi].data_nasc;
    cliente.idade = vCadastro[posi].idade;
    cliente.cpf = vCadastro[posi].cpf;
    strcpy(cliente.estado_civil, vCadastro[posi].estado_civil);
    strcpy(cliente.sexo, vCadastro[posi].sexo);

    fwrite(&cliente, sizeof(Cadastro), 1, leit);
    fclose(leit);
}
