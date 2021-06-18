#include <stdio.h>
#include <stdlib.h>

struct dados{
	char nome[31];
	char endereco[31];
	char dataNascimento[6];
	float salario;
	};

void Incluir(struct dados *pRegistro)
{
    FILE *arq;

    if((arq = fopen("Registro.txt","a"))==NULL)
    {
        printf("\nErro na abertura do arquivo \n");
        exit(0);
    }

    printf("Digite o nome: ");
    gets(pRegistro->nome);

    printf("Digite o endereco: ");
    gets(pRegistro->endereco);

    printf("Digite o dia e mes do aniversario - [dia com dois digitos]/[mes com dois digitos]: ");
    scanf("%s",&pRegistro-> dataNascimento);

    printf("Digite o salario: ");
    scanf("%f",&pRegistro-> salario);

    fwrite(pRegistro,sizeof(*pRegistro),1,arq);

    fclose(arq);
}

void ExibirPrintf(struct dados *pRegistro)
{
    printf("\nNome: %s\n", pRegistro->nome);
    printf("Endereco: %s\n",pRegistro->endereco);
    printf("Data de nascimento: %s\n",pRegistro->dataNascimento);
    printf("Salario: %.2f\n",pRegistro->salario);
}

void ListarTodosProdutosDoArq(struct dados *pRegistro)
{
    FILE *arq;
    if((arq = fopen("Registro.txt","r"))==NULL)
	{
        printf("\nErro na abertura do arquivo \n");
        exit(0);
	}

    for ( ; ; )
    {
        fread(pRegistro,sizeof(*pRegistro),1,arq);

        if(feof(arq))
        {
            close(arq);
            break;
        }

        if (pRegistro->nome[0] != '*' )
        {
            ExibirPrintf(pRegistro);
        }
    }

}


int PesquisarNome(struct dados *pRegistro)
{
    FILE *arq;
    if((arq = fopen("Registro.txt","r"))==NULL)
	{
        printf("\nErro na abertura do arquivo \n");
        exit(0);
	}

    int achou = 1;
    int i = 0;
    char vetorPalavra[31];

    printf("Digite o que deseja procurar: ");
    gets(vetorPalavra);


    for ( ; ; )
    {
        int cont;

        fread(pRegistro,sizeof(*pRegistro),1,arq);

        if(feof(arq))
        {

            break;
        }

        achou =1;
        for (cont=0;vetorPalavra[cont]!='\0';cont++)
        {
            if ((vetorPalavra[cont] != pRegistro->nome[cont]))
            {
                achou = 0;
                break;
            }
        }

        if (achou == 1)
        {
            fclose(arq);
            return i;
        }

        i++;
    }

    fclose(arq);
    return -1;
}


int PesquisarEndereco(struct dados *pRegistro)
{
    int cont;


    FILE *arq;
    if((arq = fopen("Registro.txt","r"))==NULL)
	{
        printf("\nErro na abertura do arquivo \n");
        exit(0);
	}

    int achou = 1;
    int i = -1;
    char vetorPalavra[31];

    printf("Digite o que deseja procurar: ");
    gets(vetorPalavra);


    for ( ; ; )
    {


        fread(pRegistro,sizeof(*pRegistro),1,arq);

        if(feof(arq))
        {
            fclose(arq);
            break;
        }

        achou =1;

        for (cont=0;pRegistro->endereco[cont]!='\0';cont++)
        {
            if ( pRegistro->endereco[cont] != vetorPalavra[cont] )
            {
                achou = 0;
                break;
            }
        }

        if (achou == 1)
        {
            if (pRegistro->nome[0] != '*' )
            {
                ExibirPrintf(pRegistro);
                i++;
            }
        }

    }

    return i;
}

int ListarContatosPorMes(struct dados *pRegistro)
{

    FILE *arq;
    if((arq = fopen("Registro.txt","r"))==NULL)
	{
        printf("\nErro na abertura do arquivo \n");
        exit(0);
	}

    char mesProcurar[3];

    printf("Digite o mes: ");
    gets(mesProcurar);

    if ( mesProcurar[1] == '\0')
    {
        mesProcurar[2] = '\0';
        mesProcurar[1] = mesProcurar[0];
        mesProcurar[0] = '0';
    }

    int temAniv = 0;

    for ( ; ; )
    {
        fread(pRegistro,sizeof(*pRegistro),1,arq);

        if(feof(arq))
        {
            fclose(arq);
            break;
        }

        if (pRegistro->nome[0] != '*' )
        {
            char mes[3] = {pRegistro->dataNascimento[3], pRegistro->dataNascimento[4] };

            if (mesProcurar[0] == mes[0] && mesProcurar[1] == mes[1])
            {
                if (pRegistro->nome[0] != '*' )
                {
                    ExibirPrintf(pRegistro);
                    temAniv++;
                }
            }
        }
    }
    if ( temAniv == 0 )
    {
        return -1;
    }
    else
    {
        return 0;
    }

}

void PesquisaFaixaSalarial(struct dados *pRegistro)
{
    float isalario = 0.0;
    float fsalario = 0.0;
    int naotem=0;
    int tem=0;

    FILE *arq;
    if((arq = fopen("Registro.txt","r"))==NULL)
	{
        printf("\nErro na abertura do arquivo \n");
        exit(0);
	}

	printf("Digite o valor inicial de salario que deseja procurar procurar: ");
    scanf("%f",&isalario);
    printf("Digite o valor final de salario que deseja procurar procurar: ");
    scanf("%f",&fsalario);
    getchar();

    for ( ; ; )
    {
        fread(pRegistro,sizeof(*pRegistro),1,arq);

        if(feof(arq))
        {
            fclose(arq);
            break;
        }

        if ((pRegistro->salario >= isalario) && (pRegistro->salario <= fsalario))
        {
            if (pRegistro->nome[0] != '*' )
                {
                    ExibirPrintf(pRegistro);
                    tem++;
                }
                else
                {
                    naotem++;
                }
        }
        else
        {
            naotem++;
        }
    }

    if ((naotem != 0) && (tem==0))
    {
        printf("\nNao ha registros cadastrados nessa faixa de salario");
    }
}

void AlterarSalario(struct dados *pRegistro)
{
    FILE *arq;
    int indice = 0;

    indice = PesquisarNome(pRegistro);

    if (indice < 0)
    {
        printf("O registro nao existe na Struct Dados para poder alterar!");
    }
    else
    {
        ExibirPrintf(pRegistro);

        printf("\nPode alterar o salario: \n");

        printf("Digite o novo salario: ");
        scanf("%f",&pRegistro->salario);

        if((arq = fopen("Registro.txt","r+"))==NULL)
        {
            printf("\nErro na abertura do arquivo \n");
            exit(0);
        }

        long localParaGravacao = indice * sizeof(*pRegistro);
        fseek(arq,localParaGravacao,0);
        fwrite(pRegistro,sizeof(*pRegistro),1,arq);

        fclose(arq);

        printf("\nRegistro alterado com sucesso.");
    }
}

void AlterarDados(struct dados *pRegistro)
{
    FILE *arq;
    int indice = 0;

    indice = PesquisarNome(pRegistro);

    if (indice < 0)
    {
        printf("O registro nao existe na Struct Dados para poder alterar!");
    }
    else
    {
        ExibirPrintf(pRegistro);

        printf("\nPode alterar: \n");

        printf("Nome: ");
        gets(pRegistro->nome);

        printf("Endereco: ");
        gets(pRegistro->endereco);

        printf("Dia e mes do aniversario - [dia com dois digitos]/[mes com dois digitos]: ");
        scanf("%s",&pRegistro->dataNascimento);

        printf("Digite o salario: ");
        scanf("%f",&pRegistro->salario);


        if((arq = fopen("Registro.txt","r+"))==NULL)
        {
            printf("\nErro na abertura do arquivo \n");
            exit(0);
        }

        long localParaGravacao = indice * sizeof(*pRegistro);
        fseek(arq,localParaGravacao,0);
        fwrite(pRegistro,sizeof(*pRegistro),1,arq);

        fclose(arq);

        printf("\nRegistro alterado com sucesso.");
    }
}

void Excluir(struct dados *pRegistro)
{
    FILE *arq;
    int indice = 0;

    indice = PesquisarNome(pRegistro);
    if (indice < 0)
    {
        printf("O registro nao existe na Struct Dados para poder excluir!");
    }
    else
    {
        if((arq = fopen("Registro.txt","r+"))==NULL)
        {
            printf("\nErro na abertura do arquivo \n");
            exit(0);
        }

        pRegistro->nome[0]='*';

        long localParaGravacao = indice * sizeof(*pRegistro);
        fseek(arq,localParaGravacao,0);
        fwrite(pRegistro,sizeof(*pRegistro),1,arq);

        fclose(arq);

        printf("Registro excluido com sucesso.");
    }
}

int main()
{
    static struct dados Registro;
    struct dados *pRegistro;
    pRegistro = &Registro;
    int opcao = 0;
    int sair =0;
    int ret = 0;

    for ( ; ; )
	{

        system("cls");

        printf("\n--- MENU -----------------------------------------------------");
        printf("\nEscolha uma das opcoes abaixo: \n");
        printf("1 - entrar dados.\n");
        printf("2 - listar todos os dados na tela.\n");
        printf("3 - pesquisar um registro pelo nome completo.\n");
        printf("4 - pesquisar por endereco completo.\n");
        printf("5 - pesquisar os aniversariantes de um determinado mes.\n");
        printf("6 - pesquisar por faixa salarial.\n");
        printf("7 - alterar valor do salario, pesquisado pelo nome completo.\n");
        printf("8 - alterar dados, pesquisado pelo nome completo.\n");
        printf("9 - excluir dados, pesquisado pelo nome completo.\n");
        printf("10 - sair\n");
        scanf("%d",&opcao);

        getchar();

        switch (opcao)
        {
            case 1:
            {
                Incluir(pRegistro);
                break;
            }
            case 2:
            {
                ListarTodosProdutosDoArq(pRegistro);
                break;
            }
            case 3:
            {
                ret = PesquisarNome(pRegistro);
                if (ret < 0)
                    printf("O nome nao existe no arquivo!");
                else
                {
                    printf("O nome existe no arquivo!");
                    ExibirPrintf(pRegistro);
                }
                break;
            }
            case 4:
            {
                ret = PesquisarEndereco(pRegistro);
                if (ret < 0)
                    printf("O endereco nao existe no arquivo!");

                break;
            }
            case 5:
            {
                ret = ListarContatosPorMes(pRegistro);
                if (ret < 0)
                    printf("Nenhum contato salvo que faz aniversario neste mes!");
                break;
            }
            case 6:
            {
                PesquisaFaixaSalarial(pRegistro);
                break;
            }
            case 7:
            {
                AlterarSalario(pRegistro);
                break;
            }
            case 8:
            {
                AlterarDados(pRegistro);
                break;
            }
            case 9:
            {
                Excluir(pRegistro);
                break;
            }
            case 10:
            {
                sair=1;
                break;
            }
            default:
            {
                printf("opcao invalida. Escolha novamente.\n");
            }
        }

        if (sair==1)
            break;

        printf("\n[Tecle qualquer tecla para continuar.]");
        char espera = getchar();

	}
}
