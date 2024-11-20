import 'package:flutter/material.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
        useMaterial3: true,
      ),
      home: const MyHomePage(title: 'Flutter Demo Home Page'),
    );
  }
}

class MyHomePage extends StatelessWidget {
  const MyHomePage({super.key, required this.title});

  final String title;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text(title)),
      body: const Row(
        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
        children: <Widget>[
          // Primeira coluna com ícone de chamada
          Column(
            children: <Widget>[
              Icon(Icons.call),
              Text('Call'),
            ],
          ),
          // Segunda coluna com ícone de rota
          Column(
            children: <Widget>[
              Icon(Icons.near_me),
              Text('Route'),
            ],
          ),
          // Terceira coluna com ícone de compartilhamento
          Column(
            children: <Widget>[
              Icon(Icons.share),
              Text('Share'),
            ],
          ),
        ],
      ), 
    ); 
  }
}