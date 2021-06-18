#include <stdio.h>

char vetorProduto[3][20];
int vetorQtd [3];
char vetorPalavra[20];
char vetorProdutoAlterado[20];
int espacoUsadoNoVetor;
FILE* f;

void InserirProdutoArquivo (int indice)
{
    f = fopen("produtos.txt","a"); // tipo "a" adiciona no final o item append
    fwrite(&vetorProduto[indice], sizeof(vetorPalavra), 1 ,f);
    fwrite(&vetorQtd[indice], sizeof(int), 1 ,f);
    fclose(f);
}

void RecriarArquivoEItens()
{
    f = fopen("produtos.txt", "w"); //gravacao em branco tipo write
    for (int indice = 0; indice < 3; indice++)
    {
        if ( vetorProduto[indice][0] != '\0')
        {
            //printf("\nNome: %s", vetorProduto[indice]);
            //printf(" - Qtd: %d", vetorQtd[indice]);

            fwrite(&vetorProduto[indice], sizeof(vetorPalavra), 1, f );
            fwrite(&vetorQtd[indice], sizeof(int),1, f);
        }
    }
    fclose(f);
}

void CarregarArquivo()
{
    char nome[20];
    int qt=0;
    espacoUsadoNoVetor = 0;
    f = fopen("produtos.txt", "r"); //tipo leitura
    if( f != NULL )
    {
        for (int cont = 0; cont < 3; cont++)
        {
            if ( fread(&nome, sizeof(vetorPalavra), 1, f) >=20 ) // Se a leitura trouxe resultado
            {
                fread(&qt, sizeof(int), 1, f); // le a quantidade

                //printf("\nNome: %s", n);
                //printf(" - Qtd: %d", q);

                for (int letra = 0; letra < 20; letra++) // copia do Nome para o vetorProduto
                {
                    vetorProduto[cont][letra] = nome[letra];
                }
                vetorQtd[cont] = qt;
                espacoUsadoNoVetor++;  // contabiliza quantos foram lidos
            }
        }
        fclose (f);
    }
}

void AdicionarProdutos()
{
    //Pedindo ao usuario valores para vetorProduto
    if (espacoUsadoNoVetor == 0)
    {
        printf("\nNenhum produto na lista ainda!\n");
        for(int cont=0;cont<3;cont++)
        {
            printf("Digite o %d produto: ",cont+1);
            scanf("%s",vetorProduto[cont]);
            printf("Digite a quantidade: ");
            scanf("%d",&vetorQtd[cont]);
            espacoUsadoNoVetor++;
            InserirProdutoArquivo(cont);
        }
        printf("Adicionados na primeira entrada: %d produtos!",espacoUsadoNoVetor);

    }
    else
    {
        if (espacoUsadoNoVetor > 0)
        {
            for(int i=0;i<3;i++)
            {
                if (vetorProduto[i][0] == '\0')
                {
                    printf("Digite o produto: ");
                    scanf("%s",vetorProduto[i]);
                    printf("Digite a quantidade: ");
                    scanf("%d",&vetorQtd[i]);
                    espacoUsadoNoVetor++;
                    InserirProdutoArquivo(i);
                }
            }
        }
    }
}

void ListarProdutos()
{
    int exibidos=0;
    printf("\nListagem ----------------------------------------------------------------\n");

    for(int cont=0;cont<3;cont++)
    {
        if (vetorProduto[cont][0] != '\0')
        {
            printf("produto: %s, quantidade: %d \n",vetorProduto[cont],vetorQtd[cont]);
            exibidos++;
        }
    }

    if (exibidos==0)
        printf("\nNao existem produtos cadastrados.");
}

void ProcurarPorNome()
{
    int achou = 1;

    printf("Digite o produto que deseja procurar: ");
    scanf("%s",vetorPalavra);

    for(int i=0; i<3;i++)
    {
        achou =1;
        for (int cont=0;vetorPalavra[cont]!='\0';cont++)
        {
            if (vetorPalavra[cont] != vetorProduto[i][cont])
            {
                achou = 0;
                break;
            }
        }
        if (achou == 1)
        {
            printf("O produto existe na lista: %s, quantidade %d",vetorProduto[i],vetorQtd[i]);
            return;
        }
    }
    printf("O produto não existe na lista.");

}


void ProcurarPorLetra()
{
    int qtdiferentes = 0;

    printf("Digite o letra que deseja procurar os produtos: ");
    getchar();
    char letra = getchar();

    for(int i=0; i<3;i++)
    {
        if (letra != vetorProduto[i][0])
        {
            qtdiferentes++;
        }

        if (letra == vetorProduto[i][0])
        {
            printf("O produto existe na lista: %s, quantidade %d\n",vetorProduto[i],vetorQtd[i]);
        }
    }

    if (qtdiferentes == 3)
    {
        printf("Não existem produtos com essa letra na lista.");
    }
}


void AlterarDados()
{
    int achou = 1;
    int i = 0;
    int cont = 0;

    printf("Digite o produto que deseja alterar: ");
    scanf("%s",vetorPalavra);

    for(i=0; i<3;i++)
    {
        achou = 1;
        for (cont=0;vetorPalavra[cont]!='\0';cont++)
        {
            if (vetorPalavra[cont] != vetorProduto[i][cont])
            {
                achou = 0;
                break;
            }
        }

        if (vetorPalavra[cont]=='\0' && vetorProduto[i][cont]=='\0')
            break;
    }

    if (achou==0)
    {
        printf("\nO produto não existe.");
    }
    else
    {
        printf("\nDigite o novo produto a ser alterado: ");
        scanf("%s",vetorProduto[i]);
        printf("\nDigite a quantidade: ");
        scanf("%d",&vetorQtd[i]);
        RecriarArquivoEItens();
    }
}

void ExcluirDados()
{
    int achou = 1;
    int cont;
    int i;

    printf("Digite o produto que deseja excluir: ");
    scanf("%s",vetorPalavra);

    for(i=0; i<3;i++)
    {
        achou = 1;
        for (cont=0;vetorPalavra[cont]!='\0';cont++)
        {
            if (vetorPalavra[cont] != vetorProduto[i][cont])
            {
                achou = 0;
                break;
            }
        }

        if (vetorPalavra[cont]=='\0' && vetorProduto[i][cont]=='\0')
            break;
    }

    if (achou==0)
    {
        printf("\nO produto nao existe.");
    }
    else
    {
        vetorProduto[i][0]='\0';
        vetorQtd[i]=0;
        espacoUsadoNoVetor--;
        printf("Produto excluido, agora tem %d produtos!",espacoUsadoNoVetor);

        RecriarArquivoEItens();
    }
}

int main ()
{
    int opcao;
    int sair =0;
    espacoUsadoNoVetor = 0;

    CarregarArquivo();

    for ( ; ; )
	{
        system("cls");

        printf("\n--- MENU -----------------------------------------------------");
        printf("\nEscolha uma das opcoes abaixo: \n");
        printf("1-Entrada de Dados\n");
        printf("2-Listar produtos na tela\n");
        printf("3-Pesquisar um produto com o nome completo e mostrar na tela\n");
        printf("4-Pesquisar os produtos pela primeira letra e mostrar todos na tela\n");
        printf("5-Alterar Dados\n");
        printf("6-Excluir Dados\n");
        printf("7-Saida\n");
        scanf("%d",&opcao);

        switch (opcao)
        {
            case 1: //entrar com dados
            {
                if (espacoUsadoNoVetor <3)
                    AdicionarProdutos();
                else
                    printf("Nao cabem mais produtos nessa lista");
                break;
            }
            case 2: // lista de todos os dados na tela
            {
                ListarProdutos();
                break;
            }
            case 3: //pesquisar produto nome completo
            {
                ProcurarPorNome();
                break;
            }
            case 4: //pesquisar produto nome produdto pela primeira letra
            {
                ProcurarPorLetra();
                break;
            }
            case 5: // alterar dados
            {
                AlterarDados();
                break;
            }
            case 6:// excluir dados
            {
                ExcluirDados();
                break;
            }
            case 7: //se digitado opção 7 sair do programa
            {
                sair=1;
                break;
            }
            default:
            {
                printf("opcao invalida. Escolha novamente.\n");
            }
        }

        //se digitado opcao 7 sair do programa
        if (sair==1)
            break;

        printf("\n[Tecle qualquer tecla para continuar.]");
        getchar();
        char espera = getchar();

	}
}
