import 'package:flutter/material.dart';
import 'dashboard.dart';

void main() => runApp(new MyApp());

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return new MaterialApp(
      title: 'Automail2',
      theme: new ThemeData(
        primarySwatch: Colors.grey,
      ),
      home: Dashboard(),
      debugShowCheckedModeBanner: false,
    );
  }
}
