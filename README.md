# Árvore AVL
Uma árvore AVL é uma árvore de busca binária onde nenhum dos nós possui o módulo do fator de balanceamento maior que 1.

Esta implementação verifica o balanceamento da árvore a cada inserção de nó folha pelo usuário, corrigindo a estrutura quando necessário. As operações de balanceamento, bem como a estrutura resultante, são descritas no terminal para fins didáticos.

![imagem](img/autoAVL.png)

Para compilar no GCC:

```gcc -Wall main.c arvore.c lista.c -o teste```