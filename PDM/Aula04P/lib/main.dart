import 'package:flutter/material.dart';

class MyApp extends StatelessWidget {
  const MyApp({super.key});
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Basic Flutter App',
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
        useMaterial3: true,
      ),
      home: const MyHomeScreen(),
    );
  }
}

class MyHomeScreen extends StatelessWidget {
  const MyHomeScreen({super.key});
  
  @override
  Widget build(BuildContext context) {
    return Container(
      color: Theme.of(context).primaryColor,
    );
  }
}
// UMA FORMA DE FAZER
//void main() {
  //runApp(
    //MyApp()
  //);
//}

//class MyApp extends StatelessWidget {
  //const MyApp({
    //super.key,
  //});

  //@override
  //Widget build(BuildContext context) {
    //return MaterialApp(
      //title: 'Praticando flutter pela primeira vez',
      //home: Container(
        //color: Colors.orange
     // ),
      //debugShowCheckedModeBanner: false,
    //);
  //}
//}