import 'dart:io';

String alterarVogais(String palavra, {bool contarAlteracoes = false}) {
  final vogais = ['a', 'e', 'i', 'o', 'u'];
  int alteracoes = 0;

  // Transforma as vogais em maiúsculas e conta as alterações
  String palavraAlterada = palavra.split('').map((letra) {
    if (vogais.contains(letra.toLowerCase())) {
      alteracoes++;
      return letra.toUpperCase();
    }
    return letra;
  }).join('');

  if (contarAlteracoes) {
    return '$palavraAlterada (Alterações: $alteracoes)';
  } else {
    return palavraAlterada;
  }
}

// Uma melhoria feita além do esperado do desafio
void chama() {
  print('Digite uma palavra para alterar as vogais:');
  String? entrada = stdin.readLineSync();

  if (entrada != null && entrada.isNotEmpty) {
    print('Resultado: ${alterarVogais(entrada, contarAlteracoes: true)}');
  } else {
    print('Nenhuma palavra foi inserida.');
  }
}

void main() {
  // O que foi solicitado 
  print('Teste com palavra fixa:');
  String palavra = "dezembro";
  print(alterarVogais(palavra));
  print(alterarVogais(palavra, contarAlteracoes: true));

  // Melhorando o código
  print('\nAgora é a sua vez:');
  chama();
}
