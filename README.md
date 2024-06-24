# Sistema de Gerenciamento de Hotel

Este projeto implementa um sistema de gerenciamento de hotel em C, permitindo o cadastro de clientes, funcionários, quartos e estadias, além de funcionalidades adicionais como pesquisa, baixa em estadia e cálculo de pontos de fidelidade. Abaixo estão detalhadas as funcionalidades principais e como utilizar o sistema.

---

## Funcionalidades Implementadas

1. **Cadastro de Clientes**
   - Permite cadastrar novos clientes com informações como nome, endereço e telefone. O código do cliente é gerado automaticamente e único.

2. **Cadastro de Funcionários**
   - Permite cadastrar novos funcionários com informações como nome, telefone, cargo e salário. O código do funcionário é gerado automaticamente e único.

3. **Cadastro de Quartos**
   - Permite cadastrar novos quartos com informações como número, capacidade de hóspedes e valor da diária. O status do quarto pode ser "ocupado" ou "desocupado".

4. **Cadastro de Estadias**
   - Permite cadastrar estadias para os clientes, associando um cliente a um quarto para um período específico. A quantidade de diárias é calculada automaticamente.

5. **Pesquisa por Clientes**
   - Permite buscar clientes pelo código ou nome, exibindo todas as informações cadastradas.

6. **Pesquisa por Funcionários**
   - Permite buscar funcionários pelo código ou nome, exibindo todas as informações cadastradas.

7. **Mostrar Estadias de um Cliente**
   - Exibe todas as estadias cadastradas para um cliente específico, com detalhes como data de entrada, data de saída e número do quarto.

8. **Baixa em Estadia**
   - Dá baixa em uma estadia específica, calculando o valor total a ser pago pelo cliente e marcando o quarto como "desocupado".

9. **Calcular Pontos de Fidelidade**
   - Calcula os pontos de fidelidade de um cliente com base nas diárias pagas no hotel (10 pontos por diária).

---

## Instruções de Uso

1. **Compilação**
   - Compile o programa utilizando um compilador C padrão. Por exemplo, no Linux você pode usar o GCC:
     ```
     gcc hotel.c -o hotel
     ```

2. **Execução**
   - Execute o programa compilado:
     ```
     ./hotel
     ```

3. **Menu do Sistema**
   - O sistema exibirá um menu com as opções disponíveis. Utilize os números correspondentes às opções para navegar e utilizar as funcionalidades do sistema.

4. **Interatividade**
   - Siga as instruções fornecidas pelo sistema para cada funcionalidade selecionada. Insira os dados solicitados conforme as mensagens exibidas.

---

## Observações

- **Validações**: O sistema realiza validações para garantir a consistência dos dados, como a não duplicidade de códigos de clientes, funcionários e quartos, além de verificar a disponibilidade de quartos para novas estadias.

- **Persistência de Dados**: Este projeto não implementa persistência de dados em arquivo ou banco de dados. Os dados são armazenados apenas na memória durante a execução do programa.

- **Desenvolvimento**: O sistema foi desenvolvido em C por Henrique como parte de um projeto de gerenciamento de hotel.

---

## Conclusão

Este sistema de gerenciamento de hotel oferece um conjunto de funcionalidades essenciais para operar um hotel, desde o cadastro de clientes e funcionários até o gerenciamento de estadias e cálculo de pontos de fidelidade. Para qualquer dúvida ou problema, entre em contato com Henrique via e-mail: henrique@example.com.

