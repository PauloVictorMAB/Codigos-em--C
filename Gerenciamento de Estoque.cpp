#include <stdio.h>
#include <stdlib.h>

typedef struct Estoque{
   
	int codigo;
	int quant;
	char nome[50];
    float preco;
       
}Estoque;

typedef struct Venda {
    int cod, qtd;
    char nome[50];
    float valor;
} Venda;

typedef struct Node {
    Estoque produto;
    struct Node* Prox;
} Node;

Node* createNode(Estoque produto) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->produto = produto;
    newNode->Prox = NULL;
    return newNode;
}

void insertAtEnd(Node** head, Estoque produto) {
   
    Node* newNode = createNode(produto);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* current = *head;
    while (current->Prox != NULL) {
        current = current->Prox;
    }
    current->Prox = newNode;
}

void displayList(Node* head) {
    Node* current = head;

    if (current == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    printf("Elementos da lista: \n");
    while (current != NULL) {
        printf("%d     - %s   - %.2f  - %d \n", current->produto.codigo, current->produto.nome, current->produto.preco, current->produto.quant);
        current = current->Prox;
    }
    printf("\n");
}

void Cadastro(Node** head){
	
	Estoque produto;
	int sair = 1;

	do{
						
			printf("Informe o codigo do produto :");
			scanf("%d", &produto.codigo);
						
			printf("Informe o nome do produto :");
			scanf("%s", &produto.nome);
					
			printf("Informe o valor do produto :");
			scanf("%f", &produto.preco);
			
			printf("Informe o estoque inicial do produto :");
			scanf("%d", &produto.quant);

			insertAtEnd(head, produto);
			
			printf("\n Deseja cadastrar outro produto?  1 - Sim    2 - Nao");
			scanf("%d", &sair);
			}while(sair ==1);
			
}

void Remover(Node** head) {
   
    //A Lista está vazia, então não há o que remover
    if (*head == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    Node* current = *head;
    Node* prevNode = NULL;

   int cod;
    ///Se o dado estiver na cabeça da lista ele será removido
    printf("Informe o codigo do produto: ");
    scanf("%d", &cod);
    if (current->produto.codigo == cod) {
        *head = current->Prox;
        free(current);
        printf("Produto %s removido\n", current->produto.nome );
        return;
    }
   
    //Percorre a lista até encontrar o dado
    while (current != NULL && current->produto.codigo != cod) {
        prevNode = current;
        current = current->Prox;
    }
   
    //Não Encontra
   
    if (current == NULL) {
        printf("Dado nao encontrado");
        return;
    }

    prevNode->Prox = current->Prox;
    free(current);
    printf("Elemento %s removido: %d\n", current->produto.nome);
}


Node* search(Node* head) {
    Node* current = head;
	
	int cod;
        printf("Informe o codigo do produto :");
		scanf("%d", &cod);
	
    //percorre toda a lista
    while (current != NULL) {
        if (current->produto.codigo == cod) {
        	printf("%d     - %s   - %.2f  - %d \n", current->produto.codigo, current->produto.nome, current->produto.preco, current->produto.quant);
            return current;
        }
        current = current->Prox;
    }    
    //caso não encontre o valor, retorna nulo
    return NULL;
}

typedef struct NodeVenda {
    Venda data;
    struct NodeVenda* Prox;
} NodeVenda;

//Definindo a Pilha
typedef struct Stack {
    NodeVenda* top;
} Stack;

//Criando uma Pilha
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

//Verifica se a pilha está vazia se re
int isEmpty(Stack* stack) {
    return (stack->top == NULL);
}

//Empilhar
void push(Stack* stack, Venda* data) {
    NodeVenda* newNode = (NodeVenda*)malloc(sizeof(NodeVenda));
    newNode->data = *data;
    newNode->Prox = stack->top;
    stack->top = newNode;
}


//Desmpilhar
Venda pop(Stack* stack) {
   
    if (isEmpty(stack)) {
        printf("A pilha está vazia!\n");
        Venda venda_vazia = { 0, 0, "", 0.0 };
        return venda_vazia;
         }
   
    NodeVenda* temp = stack->top;
    // o dado que ele retirou da pilha
    Venda data = temp->data;
    //Proximo vai ser o topo
    stack->top = temp->Prox;
    //limpar
    free(temp);
    //retornando o dado que eu desempilhei
    return data;
}

void saidas(Node** head, Stack* stack){
		Venda venda;
		
		 if (*head == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    	}
    		
		int cod, qtd;
		float precoV;
		
		printf("Informe o codigo do produto :");
		scanf("%d", &cod);
		printf("\nInforme a quantidade : ");
		scanf("%d", &qtd);
		
		Node* current = *head;

		while (current != NULL) {
        if (current->produto.codigo == cod) {
            if (current->produto.quant >= qtd) {
                precoV = current->produto.preco * qtd;
                current->produto.quant -= qtd;
                printf("\nValor da venda: R$%.2f\n", precoV);
                printf("Sobraram %d no estoque.\n", current->produto.quant);
				
				venda.cod = cod;
                venda.qtd = qtd;
                venda.valor = precoV;
                push(stack, &venda);
			}
	else{
		printf("ESTOQUE INDISPONIVEL");
	} break;
}
current = current->Prox;
	}
	if(current == NULL){
		printf("Produto não cadastrado\n");
		return;
	}


}

int cancelarVenda(Stack* stack, Node* head) {
    if (isEmpty(stack)) {
        printf("Nenhuma venda encontrada.\n");
        return 0;
    }

    Venda venda = pop(stack);

    Node* current = head;
    while (current != NULL) {
        if (current->produto.codigo == venda.cod) {
            current->produto.quant = current-> produto.quant + venda.qtd;

            printf("Venda cancelada.\n");
            return 1;
        }
        current = current->Prox;
    }}

int main() {
	
	int menu, sair = 1;
	Node* head = NULL;
	Venda venda;
	Stack* stack = createStack();


	do{
		printf("Informe a opcao desejada:\n 1- Cadastrar Produto \n 2- Estoque \n 3- Buscar Produto \n 4- Realizar Venda \n 5- Remover Produto do Estoque\n 6- Cancelar Ultima Venda");
		scanf("%d", &menu);
		system("cls");
	switch(menu){
	
		case 1:
			Cadastro(&head);
			break;
		case 2:
			displayList(head);
			break;
		case 3:
			search(head);
			break;
		case 4:
			saidas(&head, stack);
			break;
		case 5:
			Remover(&head);
			break;
		case 6:
			int cancelado = cancelarVenda(stack, head);
            if (!cancelado) {
                printf("Nenhuma venda cancelada.\n");}
			break;
	}
	
					
		printf("\nDeseja retornar ao menu? 1- SIM   2- Nao :");	
		scanf("%d", &sair);
		system("cls");
	}while(sair ==1);

    return 0;
}

