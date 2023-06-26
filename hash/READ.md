
Com o objetivo de explorar o comportamento de uma grande quantidade de dados através de uma estrutura de dados, foi implementado nesse projeto uma tabela hash capaz de ler um arquivo txt com 100.000 nomes cujo objetivo final é testar a capacidade dessa estrutura de dados, desde performance de busca até nível de espalhamento dentro dos buckets da tabela.

O grande volume de dados fez com que a possibilidade de colisão aumentasse consideravelmente, afim de contornar isso foi utilizado a técnica de chaining, dentro do código isso foi implementado utilizando uma Struct Hash onde cada posição dessa lista encadeada levava a outra Struct Bucket, essa por sua vez contendo os nodos que levam as informações e que serão adicionados gradualmente conforme demanda do sistema. Isso justifica a utilização de listas encadeadas duplas para desenvolver a tabela hash.

Para que o tratamento de colisão estivesse completo foi necessário implementar uma funçao hashing para identificar em qual bucket cada nome deveria ser armazenado, portanto como se tratavam de strings o cálculo utilizou como base o fundamento de ASCII que trata a conversão de strings para inteiros, a função hashing também tem um papel muito importante pois é por meio dela que vamos espalhar de forma uniforme os dados entre os buckets: 

![[Pasted image 20230624211250.png]]

Mais detalhadamente, na função hashing o nome recebido foi iterado utilizando a técnica de hashing modular, isso permite realizar um cálculo baseado nos caracteres do nome, o multiplicador 5 foi utilizado por conta de ser um número baixo e um número primo evitando que exista algum overflow, e para finalizar o retorno do valor da chave, pegamos o resto da divisão entre a iteração e o número total de buckets, nesse caso 53.

Ao vencer os desafios de resolução de colisão e de espalhamento, foi hora de adicionar as funções que preenchem a tabela hash e que permitissem realizar consultas, remoções, etc.

Após realizar a inserção dos mais de 100.000 nomes na tabela hash, conseguimos observar a seguinte distribuição através dos buckets:

![[Pasted image 20230624212152.png]]

Adicionando esses valores em um histograma é possível visualizar o seguinte resultado: 

![[Pasted image 20230624213006.png]]

Podemos notar a constância na quantidade de nomes por buckets onde a média foi de 1.901,68, o máximo de nomes em um bucket foi de 2 008 e o mínimo de 1 761.
Mesmo tendo um bom resultado no espalhamento dos dados, não foi alcançado um hashing uniforme, mas sim aproximadamente uniforme.

Para finalizar o projeto com o último desafio, foi implementado um método de ordenação por bucket onde informado o bucket, seus elementos seriam ordenados pelo método quicksort, que possui um ótimo desempenho para essas situações. A ordenação foi feita utilizando pivôs que inicialmente foram definidos através dos valores inicias e finais do bucket, onde percorreram a lista realizando as devidas trocas quando submetida uma comparação sobre os valores dos mesmos utilizando recursividade até que todos os elementos do bucket estivessem ordenados de forma alfabética.

O projeto ainda conta com outras funcionalidades além dessas revisadas aqui, que são elas:

Inserir nome;
Remover nome;
Imprimir todas as primeiras letras dos nomes dos buckets;
Pesquisar nome;
Imprimir todos os nomes.


