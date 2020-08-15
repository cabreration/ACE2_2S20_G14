import 'package:flutter/rendering.dart';

import 'Slider/Slider.dart' as mySlider;
/*import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;

void main() => runApp(MaterialApp(home: MyApp()));


class MyApp extends StatelessWidget{

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text("Un texto")
      ), body: miprueba(),
    );
  }
}

class miprueba extends StatelessWidget {
  var url = "URL de la peticion";

  Future<String> pedirDatos() async{
    var respuesta = await http.get(url);
    print(respuesta.body);
  }

/*
  @override
  Widget build(BuildContext context) {
    return Center(
      child: RaisedButton(child: Text("obtener datos"), onPressed: (){pedirDatos(); } ),);
  }
*/

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
        child: RangeSlider(
          min: 1,
          max: 100,
          divisions: 2,
        ),
      )
    );
  }
}
*/
// Flutter code sample for Slider

// ![A slider widget, consisting of 5 divisions and showing the default value
// indicator.](https://flutter.github.io/assets-for-api-docs/assets/material/slider.png)
//
// The Sliders value is part of the Stateful widget subclass to change the value
// setState was called.
import 'dart:math';

import 'package:flutter/material.dart';

import 'Slider/Slider.dart';

List<int> bars = [];
const barWidth = 5.0;
double screenWidth;
int numberOfBars;

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: "Automail",
      home: Scaffold(
        appBar: AppBar(
          title: Text("Automail"),
        ),
        body: Column(
          children: [Body()],
        ),
      ),
    );
  }
}

class Body extends StatefulWidget {
  @override
  State<StatefulWidget> createState() {
    return PageBody();
    //throw UnimplementedError();
  }
}

class PageBody extends State<Body> {
  @override
  Widget build(BuildContext context) {
    mySlider.WaveSlider().generateBar(MediaQuery.of(context).size.width);
    //return Container(child: mySlider.WaveSlider());
    //return Cards();
    return Container(
        child: Column(
      children: [
        Text(""),
        Text(""),
        Text(""),
        Text(""),
        Text(
          "50%",
          style: TextStyle(fontStyle: FontStyle.italic),
        ),
        mySlider.WaveSlider(),
        Text(""),
        Text(""),
        Text(""),
        Text(""),
        Text(""),
        Text(""),
        Text(
          "50",
          style: TextStyle(fontStyle: FontStyle.italic),
        ),
        Text(""),
        Ink(
          decoration: const ShapeDecoration(
            color: Colors.lightBlue,
            shape: CircleBorder(),
          ),
          child: IconButton(
            icon: Icon(Icons.shopping_basket),
            color: Colors.lightBlue,
            onPressed: () {},
          ),
        ),
      ],
    ));

    //throw UnimplementedError();
  }
}
