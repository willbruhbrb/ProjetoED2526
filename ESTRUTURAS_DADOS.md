# Estruturas de Dados - Justificação e Design

## Contexto
O projeto trabalha com grandes volumes de dados:
- **Clientes**: ~100.000 registos
- **Empregados**: ~100.000 registos
- **Caixas**: 6 (número fixo)
- **Produtos**: dinâmico (pode ser otimizado depois)

## Decisões de Design

### 1. Clientes → Árvore Binária de Pesquisa (ABP)

**Estrutura**: `NóCliente` com filhos esquerdo e direito

**Justificação**:
- Pesquisa frequente por ID de cliente
- Com 100.000 clientes:
  - Array: O(n) = até 50.000 comparações em média
  - Árvore balanceada: O(log n) ≈ 16 comparações
- Inserção: O(log n)
- Remoção: O(log n)
- Iteração in-order: O(n), mantendo ordem por ID

**Operações esperadas**:
- Procurar cliente por ID: frequente
- Inserir cliente: ocasional
- Remover cliente: raro
- Listar clientes: ocasional

---

### 2. Empregados → Lista Ligada

**Estrutura**: `NóEmpregado` com ponteiro para próximo

**Justificação**:
- Inserção/remoção frequentes (contratações, demissões)
- Com 100.000 empregados:
  - Array: Inserção/remoção no meio = O(n) (até 100k movimentos)
  - Lista ligada: Inserção/remoção = O(1) (só mudar ponteiros)
- Pesquisa: O(n), mas menos frequente que clientes
- Iteração: O(n), linear em qualquer caso

**Operações esperadas**:
- Adicionar empregado: frequente
- Remover empregado: frequente
- Listar empregados: ocasional
- Procurar empregado: menos frequente que clientes

---

### 3. Caixas → Array Dinâmico

**Estrutura**: Array de `Caixa` com alocação dinâmica

**Justificação**:
- Número limitado de caixas (N_CAIXAS = 6)
- Acesso direto por número: `caixas[i]`
- Performance não é crítica para poucos elementos
- Simplicidade de implementação

**Operações esperadas**:
- Acesso direto por número de caixa
- Iteração sobre todas as caixas
- Gestão de filas em cada caixa

---

### 4. Produtos → Array Dinâmico (atual)

**Estrutura**: Array de `Produto` com capacidade dinâmica

**Justificação Temporária**:
- Implementação inicial simplificada
- Pode ser otimizado em iterações futuras (ex: hash table, árvore)

**Nota**: Revisar se performance for limitante

---

## Complexidade Comparativa

| Operação | Clientes (Array) | Clientes (ABP) | Empregados (Array) | Empregados (Lista) |
|----------|------------------|----------------|--------------------|--------------------|
| Pesquisa | O(n) - 50.000 | O(log n) - 16 | O(n) - 50.000 | O(n) - 50.000 |
| Inserção | O(n) - 50.000 | O(log n) - 16 | O(n) - 100.000 | O(1) - 1 |
| Remoção | O(n) - 50.000 | O(log n) - 16 | O(n) - 100.000 | O(1) - 1 |
| Iteração | O(n) | O(n) | O(n) | O(n) |

---

## Impacto de Performance

### Cenário: 100.000 clientes, pesquisa por ID
- **Array**: 50.000 comparações em média (inaceitável para UI interativa)
- **Árvore**: 16 comparações (aceitável, < 1ms)

### Cenário: Adicionar 1.000 empregados
- **Array**: 1.000 × 50.000 = 50 milhões de movimentos
- **Lista ligada**: 1.000 × 1 operação = 1.000 operações (50.000× mais rápido)

---

## Implementação Futura

- [ ] Considerar árvore balanceada (AVL ou Red-Black) para clientes
- [ ] Otimizar pesquisa de empregados se necessário (hash table?)
- [ ] Benchmark com 100k registos reais
- [ ] Considerar persistência eficiente (serialização binária vs CSV)
